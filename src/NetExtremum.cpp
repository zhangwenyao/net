#include "NetExtremum.h"
#ifdef NET_EXTREMUM

#include "common.h"
using namespace std;

//**//*****************************************************************//*
int lkk_new_p2p(VVNodeType& p2p, const VVLinkType& lkk,
    const VNodeType& nodeDeg, const VNodeType& degArrSize,
    const VNodeType& degArrSum)
{
  if (degArrSize.size() <= 0) {
    ERROR();
    return -1;
  }
  const NodeType nodeSize = nodeDeg.size(), degSize = lkk.size();
  p2p.clear();
  p2p.resize(nodeSize);
  for (NodeType i = 0; i < nodeSize; i++)
    p2p[i].reserve(nodeDeg[i]);
  VNodeType stk(degArrSize);
  for (NodeType sI = 0; sI < degSize; sI++) {
    for (NodeType sJ = 0; sJ <= sI; sJ++) {
      if (lkk[sI][sJ] <= 0)
        continue;
      NodeType iSize = degArrSize[sI], i0 = (sI ? degArrSum[sI - 1] : 0),
               iStart = stk[sI];
      if (iStart <= 0)
        iStart = iSize;

      if (sJ == sI) { // 同度点间连接
        LinkType iLink = lkk[sI][sI] * 2;
        NodeType dSize = iLink / iSize;
        iLink %= iSize;

        // 连接 dSize > 0

        if (dSize == iSize - 1 && iSize % 2 == 0) { // j2 == iSize / 2.
          for (NodeType l = iSize / 2, i = i0, j = i0 + iSize - l; l > 0;
               l--) {
            p2p[i].push_back(j);
            p2p[j++].push_back(i++);
          }
          dSize--;
        }

        for (NodeType j2 = dSize / 2 + (iLink > 0); dSize > 1;
             dSize -= 2, j2--) { // j2 < iSize / 2.
          for (NodeType l = iSize, i = i0, j = i0 + iSize - j2; l > 0; l--) {
            if (j == i0 + iSize)
              j -= iSize;
            p2p[i].push_back(j);
            p2p[j++].push_back(i++);
          }
        }

        if (dSize == 1) {       // j2 == -1
          if (iSize % 2 == 0) { // 间隔连接 1-2 3-4 ... x-0
            for (NodeType l = iSize / 2, i = i0 + iStart % 2, j; l > 0;
                 i += 2, l--) {
              j = i + 1;
              if (j == i0 + iSize)
                j -= iSize;
              p2p[i].push_back(j);
              p2p[j].push_back(i);
            }
            dSize--;
          } else {
            iLink += iSize;
          }
        }

        // 连接剩余部分 j2 == 1 :  0-1 2-3 ...
        if (iLink > 0) {
          stk[sI] += iSize - iLink % iSize;
          if (stk[sI] > iSize)
            stk[sI] -= iSize;
          iLink /= 2;
          for (NodeType i = i0 + iStart + 1, j; iLink > 0; iLink--) {
            if (i <= i0 + 1)
              i += iSize - 2;
            else
              i -= 2;
            if (i == i0)
              j = i + iSize - 1;
            else
              j = i - 1;
            p2p[i].push_back(j);
            p2p[j].push_back(i);
          }
        }
      } else { // 不同度点间连接
        NodeType j0 = (sJ ? degArrSum[sJ - 1] : 0), jSize = degArrSize[sJ],
                 jStart = stk[sJ];
        if (jStart <= 0)
          jStart = jSize;

        LinkType links = lkk[sI][sJ],
                 lcmSize = (LinkType)iSize / common_GCD(iSize, jSize) * jSize;
        NodeType dSize = (NodeType)(links / lcmSize);
        links %= lcmSize;

        // 连接循环部分
        for (NodeType i = i0 + iStart, j; dSize > 0; dSize--) {
          j = j0 + (jStart + dSize - (links == 0)) % jSize;
          for (LinkType l = 0; l < lcmSize; l++) {
            if (i == i0)
              i += iSize - 1;
            else
              i--;
            if (j == j0)
              j += jSize - 1;
            else
              j--;
            p2p[i].push_back(j);
            p2p[j].push_back(i);
          }
        }

        // 连接剩余部分
        if (links > 0) {
          stk[sI] += iSize - links % iSize;
          if (stk[sI] > iSize)
            stk[sI] -= iSize;
          stk[sJ] += jSize - links % jSize;
          if (stk[sJ] > jSize)
            stk[sJ] -= jSize;
          for (NodeType i = i0 + iStart, j = j0 + jStart; links > 0; links--) {
            if (i <= i0)
              i += iSize - 1;
            else
              i--;
            if (j <= j0)
              j += jSize - 1;
            else
              j--;
            p2p[i].push_back(j);
            p2p[j].push_back(i);
          }
        }
      } // 不同度节点间连边
    }   // sJ
  }     // sI
  return check_p2p_nodeDeg(p2p, nodeDeg);
}

//**//*****************************************************************//*
int lkk_extreme_pearson(VVLinkType& lkk, const VNodeType& degArrVal,
    const VNodeType& degArrSize, const int extrMax, const unsigned countN)
{
  const NodeType degSize = lkk.size();
  if (degSize <= 1)
    return 0;
  for (unsigned flag = 1, count = 0; flag || count < countN; count++) {
    if (flag) {
      count = 0;
      flag = 0;
    }
    for (NodeType i1 = 0; i1 < degSize; i1++) {
      for (NodeType j1 = 0; j1 <= i1; j1++) {
        LinkType n1 = lkk[i1][j1];
        if (n1 <= 0)
          continue;
        const LinkType si1 = degArrSize[i1], sj1 = degArrSize[j1],
                       ki1 = degArrVal[i1], kj1 = degArrVal[j1],
                       sij1 = ki1 * kj1;
        for (NodeType i2 = 0; i2 <= i1; i2++) {
          for (NodeType j2 = 0; j2 <= i2; j2++) {
            const LinkType n2 = lkk[i2][j2];
            if (n2 <= 0)
              continue;
            const LinkType si2 = degArrSize[i2], sj2 = degArrSize[j2],
                           ki2 = degArrVal[i2], kj2 = degArrVal[j2],
                           sij12 = sij1 + ki2 * kj2;
            LinkType l = n1 < n2 ? n1 : n2;

            int extrFlag;
            if (sij12 == ki1 * kj2 + ki2 * kj1)
              extrFlag = 0;
            else if (sij12 > ki1 * kj2 + ki2 * kj1)
              extrFlag = 1;
            else
              extrFlag = -1;
            if ((extrMax && extrFlag <= 0) || (!extrMax && extrFlag >= 0)) {
              LinkType t, t2;
              if (i1 != j2) {
                t = si1 * (sj2 < ki1 ? sj2 : ki1);
                t2 = sj2 * (si1 < kj2 ? si1 : kj2);
                if (t > t2)
                  t = t2;
              } else {
                t = si1 * (ki1 < si1 ? ki1 : si1 - 1) / 2;
              }
              t -= i1 < j2 ? lkk[j2][i1] : lkk[i1][j2];
              if (l > t)
                l = t;
              if (i2 != j1) {
                t = si2 * (sj1 < ki2 ? sj1 : ki2);
                t2 = sj1 * (si2 < kj1 ? si2 : kj1);
                if (t > t2)
                  t = t2;
              } else {
                t = si2 * (ki2 < si2 ? ki2 : si2 - 1) / 2;
              }
              t -= i2 < j1 ? lkk[j1][i2] : lkk[i2][j1];
              if (l > t)
                l = t;
              if (l > 0) {
                if (extrFlag)
                  flag = 1;
                else
                  l = (l + 1) / 2;
                if (l > 0) {
                  n1 = lkk[i1][j1] -= l;
                  lkk[i2][j2] -= l;
                  if (i1 > j2)
                    lkk[i1][j2] += l;
                  else
                    lkk[j2][i1] += l;
                  if (i2 > j1)
                    lkk[i2][j1] += l;
                  else
                    lkk[j1][i2] += l;
                  continue;
                }
              }
            }

            if (sij12 == ki1 * ki2 + kj1 * kj2)
              extrFlag = 0;
            else if (sij12 > ki1 * ki2 + kj1 * kj2)
              extrFlag = 1;
            else
              extrFlag = -1;
            if ((extrMax && extrFlag <= 0) || (!extrMax && extrFlag >= 0)) {
              LinkType t, t2;
              if (i1 != i2) {
                t = si1 * (si2 < ki1 ? si2 : ki1);
                t2 = si2 * (si1 < ki2 ? si1 : ki2);
                if (t > t2)
                  t = t2;
              } else {
                t = si1 * (ki1 < si1 ? ki1 : si1 - 1) / 2;
              }
              t -= i1 < i2 ? lkk[i2][i1] : lkk[i1][i2];
              if (l > t)
                l = t;
              if (j2 != j1) {
                t = sj2 * (sj1 < kj2 ? sj1 : kj2);
                t2 = sj1 * (sj2 < kj1 ? sj2 : kj1);
                if (t > t2)
                  t = t2;
              } else {
                t = (LinkType)sj2 * (kj2 < sj2 ? kj2 : sj2 - 1) / 2;
              }
              t -= j2 < j1 ? lkk[j1][j2] : lkk[j2][j1];
              if (l > t)
                l = t;
              if (l > 0) {
                if (extrFlag)
                  flag = 1;
                else
                  l = (l + 1) / 2;
                n1 = lkk[i1][j1] -= l;
                lkk[i2][j2] -= l;
                if (i1 > i2)
                  lkk[i1][i2] += l;
                else
                  lkk[i2][i1] += l;
                if (j2 > j1)
                  lkk[j2][j1] += l;
                else
                  lkk[j1][j2] += l;
                continue;
              }
            }
          } // j2
        }   // i2
      }     // j1
    }       // j2
  }         // count
  return 0;
}

//**//*****************************************************************//*
int cal_Min_lkk(VVLinkType& lkk, const VNodeType& degArrVal,
    const VNodeType& degArrSize, const VLinkType& linkSum, const int fix)
{
  const NodeType degSize = degArrVal.size();
  lkk.clear();
  lkk.resize(degSize);
  VLinkType vlink(degSize);
  for (NodeType i = 0; i < degSize; i++) {
    lkk[i].assign(i + 1, 0);
    vlink[i] = (LinkType)degArrSize[i] * degArrVal[i];
  }
  NodeType head = 0, end = degSize - 1, mid = 0;
  const LinkType linkSize = linkSum.back() / 2;
  while (linkSum[mid] < linkSize)
    mid++;
  LinkType linkMid = linkSize - (mid > 0 ? linkSum[mid - 1] : 0);

  // sJ <= mid < sI
  for (NodeType sI = end; mid < sI; sI--) {
    if (vlink[sI] <= 0)
      continue;
    while (vlink[head] == 0)
      head++;
    for (NodeType sJ = head; vlink[sI] && sJ < mid; sJ++) { // sJ < mid < sI
      LinkType links = (LinkType)degArrSize[sI] * degArrSize[sJ];
      if (links > vlink[sI])
        links = vlink[sI];
      if (links > vlink[sJ])
        links = vlink[sJ];
      vlink[sI] -= lkk[sI][sJ] = links;
      vlink[sJ] -= links;
    }
    if (vlink[sI] && linkMid) { // sJ = mid < sI
      LinkType links = (LinkType)degArrSize[sI] * degArrSize[mid];
      if (links > vlink[sI])
        links = vlink[sI];
      if (links > linkMid)
        links = linkMid;
      vlink[sI] -= lkk[sI][mid] = links;
      vlink[mid] -= links;
      linkMid -= links;
    }
  }

  // sI == mid
  if (linkMid < vlink[mid]) {
    LinkType linkRight = vlink[mid] - linkMid;
    for (NodeType sJ = head; linkRight && sJ < mid; sJ++) { // sJ < mid = sI
      LinkType links = (LinkType)degArrSize[sJ] * degArrSize[mid];
      if (links > vlink[sJ])
        links = vlink[sJ];
      if (links > linkRight)
        links = linkRight;
      vlink[mid] -= lkk[mid][sJ] = links;
      vlink[sJ] -= links;
      linkRight -= links;
    }

    if (linkRight && linkMid) { // sJ = mid = sI
      LinkType links = (LinkType)degArrSize[mid] * (degArrSize[mid] - 1) / 2;
      if (links > linkRight)
        links = linkRight;
      if (links > linkMid)
        links = linkMid;
      linkMid -= lkk[mid][mid] = links;
      vlink[mid] -= links * 2;
    }
  }

  for (NodeType left = mid - (linkMid == 0 && mid > 0),
                right = mid + (linkMid == vlink[mid] && mid < end);
       right <= end; right++) {
    while (vlink[right] == 0 && right < end)
      ++right;
    while (vlink[left] == 0 && left > head)
      --left;
    if (vlink[right] == 0 && vlink[left] == 0)
      break;
    if (vlink[right] == 0 || vlink[left] == 0) {
      ERROR();
      return -1;
    }
    if (!fix) {
      ERROR();
      return -1;
    }
    // 从中间mid往两端修正
    if (cal_Min_lkk_fix(lkk, degArrVal, degArrSize, degSize, vlink, left,
            right, mid, linkMid)
        == -1) {
      ERROR();
      return -1;
    }
  }

  return 0;
}

int cal_Min_lkk_fix(VVLinkType& lkk, const VNodeType& degArrVal,
    const VNodeType& degArrSize, const NodeType degSize, VLinkType& vlink,
    const NodeType& left, const NodeType& right, const NodeType& mid,
    LinkType& linkMid)
{
  cout << "\tlkk_fix\tleft\t" << left << "\tright\t" << right << '\n';
  LinkType linkRight = right == mid ? vlink[mid] - linkMid : vlink[right];
  if (linkRight == 0)
    return 0;
  if (left == 0 || right + 1 >= degSize)
    return -1;
  for (NodeType l = left; linkRight && l > 0;) {
    l--;
    LinkType links
        = (LinkType)(degArrSize[l] < degArrVal[right] ? degArrSize[l]
                                                      : degArrVal[right])
        * degArrSize[right],
        t = (LinkType)degArrSize[l] * (degArrSize[right] < degArrVal[l]
                                              ? degArrSize[right]
                                              : degArrVal[l]);
    if (links > t)
      links = t;
    links -= lkk[right][l];
    if (links == 0)
      continue;
    if (links > linkRight)
      links = linkRight;
    linkRight -= links;
    for (NodeType r = right + 1; links && r < degSize; r++) {
      while (r < degSize && lkk[r][l] == 0)
        r++;
      if (r >= degSize) {
        ERROR("right\t", right);
        return -1;
      }

      // lkk[sI][l] -> lkk[right][l]
      LinkType t = links < lkk[r][l] ? links : lkk[r][l];
      lkk[r][l] -= t;
      lkk[right][l] += t;
      vlink[r] += t;
      vlink[right] -= t;
      links -= t;

      // lkk[r][*]
      for (NodeType sI = r; sI > right; sI--) {
        for (NodeType sJ = l + 1; vlink[sI] && sJ < mid; sJ++) { // sJ < mid
          LinkType links = (LinkType)degArrSize[sI] * degArrSize[sJ];
          if (links > vlink[sI])
            links = vlink[sI];
          if (links > vlink[sJ])
            links = vlink[sJ];
          vlink[sI] -= lkk[sI][sJ] = links;
          vlink[sJ] -= links;
        }
        if (vlink[sI] && linkMid) { // sJ == mid
          LinkType links = (LinkType)degArrSize[sI] * degArrSize[mid];
          if (links > vlink[sI])
            links = vlink[sI];
          if (links > linkMid)
            links = linkMid;
          vlink[sI] -= lkk[sI][mid] = links;
          vlink[mid] -= links;
          linkMid -= links;
        }
      }
    }
    linkRight += links;
  }
  if (linkRight) {
    ERROR("right\t", right);
    return -1;
  }
  return 0;
}

//**//*****************************************************************//*
int cal_Max_lkk(VVLinkType& lkk, const VNodeType& degArrVal,
    const VNodeType& degArrSize, const VLinkType& linkSum, const int fix)
{
  // TODO
  const NodeType degSize = degArrVal.size();
  lkk.clear();
  lkk.resize(degSize);
  VLinkType vlink(degSize);
  for (NodeType i = 0; i < degSize; i++) {
    lkk[i].assign(i + 1, 0);
    vlink[i] = (LinkType)degArrSize[i] * degArrVal[i];
  }
  NodeType head = 0, end = degSize - 1, mid = 0;
  const LinkType linkSize = linkSum.back() / 2;
  while (linkSum[mid] < linkSize)
    mid++;
  LinkType linkMid = linkSize - (mid ? linkSum[mid - 1] : 0);
  // sJ <= mid < sI
  for (NodeType sI = end; mid < sI && vlink[sI]; sI--) {
    while (vlink[head] == 0)
      head++;
    for (NodeType sJ = head; vlink[sI] && sJ < mid; sJ++) { // sJ < mid
      LinkType links = (LinkType)degArrSize[sI] * degArrSize[sJ];
      if (links > vlink[sI])
        links = vlink[sI];
      if (links > vlink[sJ])
        links = vlink[sJ];
      vlink[sI] -= lkk[sI][sJ] = links;
      vlink[sJ] -= links;
    }
    if (vlink[sI] && linkMid) { // sJ == mid
      LinkType links = (LinkType)degArrSize[sI] * degArrSize[mid];
      if (links > vlink[sI])
        links = vlink[sI];
      if (links > linkMid)
        links = linkMid;
      vlink[sI] -= lkk[sI][mid] = links;
      vlink[mid] -= links;
      linkMid -= links;
    }
  }
  // sI == mid
  if (linkMid < vlink[mid]) {
    LinkType linkRight = vlink[mid] - linkMid;
    for (NodeType sJ = head; linkRight && sJ < mid; sJ++) { // sJ < mid
      LinkType links = (LinkType)degArrSize[sJ] * degArrSize[mid];
      if (links > vlink[sJ])
        links = vlink[sJ];
      if (links > linkRight)
        links = linkRight;
      vlink[mid] -= lkk[mid][sJ] = links;
      vlink[sJ] -= links;
      linkRight -= links;
    }
    if (linkRight) { // sJ == mid == sI
      LinkType links = (LinkType)degArrSize[mid] * (degArrSize[mid] - 1) / 2;
      if (links > linkRight)
        links = linkRight;
      linkMid -= lkk[mid][mid] = links;
      vlink[mid] -= links * 2;
    }
  }
  for (NodeType left = mid - (linkMid == 0 && mid > 0),
                right = mid + (linkMid == vlink[mid]);
       right < degSize; right++) {
    while (vlink[right] == 0 && right < degSize)
      right++;
    while (vlink[left] == 0 && left > 0)
      left--;
    if (right == degSize)
      break; // 全连完
    if (!fix) {
      ERROR();
      return -1;
    }
    // 从中间mid往两端修正
    if (cal_Min_lkk_fix(lkk, degArrVal, degArrSize, degSize, vlink, left,
            right, mid, linkMid)
        == -1) {
      ERROR();
      return -1;
    }
  }
  return 0;
}

//**//*****************************************************************//*
int Max_new_lkk(VVLinkType& lkk, const VNodeType& degArrVal,
    const VNodeType& degArrSize, VLinkType& linkSum, const int fix)
{
  if (degArrSize.empty()) {
    ERROR();
    return -1;
  }
  if (linkSum.empty()
      && 0 != degArr_2_linkSum(linkSum, degArrVal, degArrSize)) {
    ERROR();
    return -1;
  }
  if (0 != cal_Max_lkk(lkk, degArrVal, degArrSize, linkSum, fix)) {
    ERROR();
    return -1;
  }
  return 0;
}

int Max_new(VVNodeType& p2p, const VNodeType& nodeDeg,
    const VNodeType& degArrVal, const VNodeType& degArrSize,
    const VNodeType& degArrSum)
{
  if (degArrSize.empty()) {
    ERROR();
    return -1;
  }
  const NodeType nodeSize = nodeDeg.size();
  p2p.clear();
  p2p.resize(nodeSize);
  for (NodeType i = 0; i < nodeSize; i++)
    p2p[i].reserve(nodeDeg[i]);
  VNodeType stk(degArrSize);
  NodeType sI = stk.size() - 1;
  for (NodeType sJ = sI; 1;) {
    NodeType iSize = degArrSize[sI], iDeg = degArrVal[sI],
             i0 = (sI ? degArrSum[sI - 1] : 0);
    if (iSize <= 0 || p2p[i0].size() >= iDeg) {
      stk[sI] = 0;
      if (sI <= 0)
        break;
      sJ = --sI;
      continue;
    }
    NodeType iStart = stk[sI];
    if (iStart <= 0)
      iStart = iSize;
    LinkType iLink
        = (LinkType)iSize * (iDeg - p2p[i0].size()) - (iSize - iStart);

    if (sJ == sI) { // 同度点间连接
      if (iSize == 1) {
        if (sI <= 0) {
          ERROR(sI);
          break;
        }
        sJ = sI - 1;
        continue;
      }

      LinkType links = (LinkType)iSize * (iSize - 1);
      if (iLink > links)
        iLink = links;
      else if (iLink % 2 == 1)
        iLink--;
      NodeType dSize = iLink / iSize;
      iLink %= iSize;

      // 连接 dSize > 0

      if (dSize == iSize - 1 && iSize % 2 == 0) { // j2 == iSize / 2.
        for (NodeType l = iSize / 2, i = i0, j = i0 + iSize - l; l > 0; l--) {
          p2p[i].push_back(j);
          p2p[j++].push_back(i++);
        }
        dSize--;
      }

      for (NodeType j2 = dSize / 2 + (iLink > 0); dSize > 1;
           dSize -= 2, j2--) { // j2 < iSize / 2.
        for (NodeType l = iSize, i = i0, j = i0 + iSize - j2; l > 0; l--) {
          if (j == i0 + iSize)
            j -= iSize;
          p2p[i].push_back(j);
          p2p[j++].push_back(i++);
        }
      }

      if (dSize == 1) {       // j2 == -1
        if (iSize % 2 == 0) { // 间隔连接 1-2 3-4 ... x-0
          for (NodeType l = iSize / 2, i = i0 + iStart % 2, j; l > 0;
               i += 2, l--) {
            j = i + 1;
            if (j == i0 + iSize)
              j -= iSize;
            p2p[i].push_back(j);
            p2p[j].push_back(i);
          }
          dSize--;
        } else {
          iLink += iSize;
        }
      }

      // 连接剩余部分 j2 == 1 :  0-1 2-3 ...
      if (iLink > 0) {
        stk[sI] += iSize - iLink % iSize;
        if (stk[sI] > iSize)
          stk[sI] -= iSize;
        iLink /= 2;
        for (NodeType i = i0 + iStart + 1, j; iLink > 0; iLink--) {
          if (i <= i0 + 1)
            i += iSize - 2;
          else
            i -= 2;
          if (i == i0)
            j = i + iSize - 1;
          else
            j = i - 1;
          p2p[i].push_back(j);
          p2p[j].push_back(i);
        }
      }

      if (p2p[i0].size() < iDeg) {
        if (sI <= 0) {
          ERROR(sI);
          break;
        }
        sJ = sI - 1;
      }
      continue;

    } else { // 不同度点间连接
      //  更新 sJ
      NodeType j0 = (sJ ? degArrSum[sJ - 1] : 0), jDeg = degArrVal[sJ],
               jSize = degArrSize[sJ];
      if (jSize <= 0 || p2p[j0].size() >= jDeg) {
        stk[sJ] = 0;
        if (sJ <= 0) {
          ERROR(sI, "\t", sJ);
          break;
        }
        sJ--;
        continue;
      }
      NodeType jStart = stk[sJ];
      if (jStart <= 0)
        jStart = jSize;

      LinkType jLink
          = (LinkType)jSize * (jDeg - p2p[j0].size()) + jStart - jSize,
          links = (LinkType)iSize * jSize;
      if (links > iLink)
        links = iLink;
      if (links > jLink)
        links = jLink;
      LinkType lcmSize = (LinkType)iSize / common_GCD(iSize, jSize) * jSize;
      NodeType dSize = (NodeType)(links / lcmSize);
      links %= lcmSize;

      // 连接循环部分
      for (NodeType i = i0 + iStart, j; dSize > 0; dSize--) {
        j = j0 + (jStart + dSize - (links == 0)) % jSize;
        for (LinkType l = 0; l < lcmSize; l++) {
          if (i == i0)
            i += iSize - 1;
          else
            i--;
          if (j == j0)
            j += jSize - 1;
          else
            j--;
          p2p[i].push_back(j);
          p2p[j].push_back(i);
        }
      }

      // 连接剩余部分
      if (links > 0) {
        stk[sI] += iSize - links % iSize;
        if (stk[sI] > iSize)
          stk[sI] -= iSize;
        stk[sJ] += jSize - links % jSize;
        if (stk[sJ] > jSize)
          stk[sJ] -= jSize;
        for (NodeType i = i0 + iStart, j = j0 + jStart; links > 0; links--) {
          if (i <= i0)
            i += iSize - 1;
          else
            i--;
          if (j <= j0)
            j += jSize - 1;
          else
            j--;
          p2p[i].push_back(j);
          p2p[j].push_back(i);
        }
      }

      if (p2p[i0].size() < iDeg) {
        if (sJ <= 0) {
          ERROR(sI, "\t", sJ);
          break;
        }
        sJ--;
      }
      continue;

    } // 不同度节点间连边

  } // 所有度的连边

  if (sI > 0 || p2p[0].size() < nodeDeg[0])
    return -2;

  return 0;
}

//**//*****************************************************************//*
int Min_new(VVNodeType& p2p, const VNodeType& nodeDeg,
    const VNodeType& degArrVal, const VNodeType& degArrSize,
    const VNodeType& degArrSum)
{
  if (degArrSize.empty()) {
    ERROR();
    return -1;
  }
  const NodeType nodeSize = nodeDeg.size();
  p2p.clear();
  p2p.resize(nodeSize);
  for (NodeType i = 0; i < nodeSize; i++)
    p2p[i].reserve(nodeDeg[i]);
  VNodeType stk(degArrSize);

  NodeType s0 = 0, sI = stk.size() - 1;
  for (NodeType sJ = s0; 1;) {
    NodeType iDeg = degArrVal[sI], i0 = (sI ? degArrSum[sI - 1] : 0);
    if (p2p[i0].size() >= iDeg) {
      stk[sI] = 0;
      if (s0 == sI) {
        s0++;
        break;
      }
      sJ = s0;
      sI--;
      continue;
    }
    NodeType iSize = degArrSize[sI], iStart = stk[sI];
    if (iStart <= 0)
      iStart = iSize;
    LinkType iLink
        = (LinkType)iSize * (iDeg - p2p[i0].size()) - (iSize - iStart);

    // 不同度点间连接
    if (sJ < sI) {
      NodeType j0 = (sJ ? degArrSum[sJ - 1] : 0), jDeg = degArrVal[sJ],
               jSize = degArrSize[sJ];
      if (jSize <= 0 || p2p[j0].size() >= jDeg) {
        stk[sJ] = 0;
        if (s0 == sJ)
          s0++;
        sJ++;
        continue;
      }
      NodeType jStart = stk[sJ];
      if (jStart <= 0)
        jStart = jSize;

      LinkType jLink
          = (LinkType)jSize * (jDeg - p2p[j0].size()) + jStart - jSize,
          links = (LinkType)iSize * jSize;
      if (links > iLink)
        links = iLink;
      if (links > jLink)
        links = jLink;
      LinkType lcmSize = (LinkType)iSize / common_GCD(iSize, jSize) * jSize;
      NodeType dSize = (NodeType)(links / lcmSize);
      links %= lcmSize;

      // 连接循环部分
      for (NodeType i = i0 + iStart, j; dSize > 0; dSize--) {
        j = j0 + (jStart + dSize - (links == 0)) % jSize;
        for (LinkType l = 0; l < lcmSize; l++) {
          if (i == i0)
            i += iSize - 1;
          else
            i--;
          if (j == j0)
            j += jSize - 1;
          else
            j--;
          p2p[i].push_back(j);
          p2p[j].push_back(i);
        }
      }

      // 连接剩余部分
      if (links > 0) {
        stk[sI] += iSize - links % iSize;
        if (stk[sI] > iSize)
          stk[sI] -= iSize;
        stk[sJ] += jSize - links % jSize;
        if (stk[sJ] > jSize)
          stk[sJ] -= jSize;
        for (NodeType i = i0 + iStart, j = j0 + jStart; links > 0; links--) {
          if (i <= i0)
            i += iSize - 1;
          else
            i--;
          if (j <= j0)
            j += jSize - 1;
          else
            j--;
          p2p[i].push_back(j);
          p2p[j].push_back(i);
        }
      }

      if (p2p[i0].size() >= iDeg) {
        sI--;
        sJ = s0;
      } else {
        if (p2p[j0].size() >= jDeg && s0 == sJ)
          s0++;
        sJ++;
      }
      continue;

    } else { // 同度点间连接
      if (iSize == 1) {
        ERROR(sI);
        break;
      }

      LinkType links = (LinkType)iSize * (iSize - 1);
      if (iLink > links)
        iLink = links;
      else if (iLink % 2 == 1)
        iLink--;
      NodeType dSize = iLink / iSize;
      iLink %= iSize;

      // 连接 dSize > 0

      if (dSize == iSize - 1 && iSize % 2 == 0) { // j2 == iSize / 2.
        for (NodeType l = iSize / 2, i = i0, j = i0 + iSize - l; l > 0; l--) {
          p2p[i].push_back(j);
          p2p[j++].push_back(i++);
        }
        dSize--;
      }

      for (NodeType j2 = dSize / 2 + (iLink > 0); dSize > 1;
           dSize -= 2, j2--) { // j2 < iSize / 2.
        for (NodeType l = iSize, i = i0, j = i0 + iSize - j2; l > 0; l--) {
          if (j == i0 + iSize)
            j -= iSize;
          p2p[i].push_back(j);
          p2p[j++].push_back(i++);
        }
      }

      if (dSize == 1) {       // j2 == -1
        if (iSize % 2 == 0) { // 间隔连接 1-2 3-4 ... x-0
          for (NodeType l = iSize / 2, i = i0 + iStart % 2, j; l > 0;
               i += 2, l--) {
            j = i + 1;
            if (j == i0 + iSize)
              j -= iSize;
            p2p[i].push_back(j);
            p2p[j].push_back(i);
          }
          dSize--;
        } else {
          iLink += iSize;
        }
      }

      // 连接剩余部分 j2 == 1 :  0-1 2-3 ...
      if (iLink > 0) {
        stk[sI] += iSize - iLink % iSize;
        if (stk[sI] > iSize)
          stk[sI] -= iSize;
        iLink /= 2;
        for (NodeType i = i0 + iStart + 1, j; iLink > 0; iLink--) {
          if (i <= i0 + 1)
            i += iSize - 2;
          else
            i -= 2;
          if (i == i0)
            j = i + iSize - 1;
          else
            j = i - 1;
          p2p[i].push_back(j);
          p2p[j].push_back(i);
        }
      }

      if (p2p[i0].size() < iDeg) {
        ERROR(sI);
        break;
      }
      continue;
    }
  }

  if (s0 <= sI)
    return -2;

  return 0;
}

int Min_new_lkk_p2p(VVNodeType& p2p, VVLinkType& lkk, const VNodeType& nodeDeg,
    const VNodeType& degArrVal, const VNodeType& degArrSize,
    const VNodeType& degArrSum, VLinkType& linkSum, const int fix)
{
  if (degArrSize.empty()) {
    ERROR();
    return -1;
  }
  if (linkSum.empty()
      && 0 != degArr_2_linkSum(linkSum, degArrVal, degArrSize)) {
    ERROR();
    return -1;
  }
  if (0 != cal_Min_lkk(lkk, degArrVal, degArrSize, linkSum, fix)) {
    ERROR();
    return -1;
  }
  if (0 != lkk_new_p2p(p2p, lkk, nodeDeg, degArrSize, degArrSum)) {
    ERROR();
    return -1;
  }
  return 0;
}

int Min_new_lkk(VVLinkType& lkk, const VNodeType& degArrVal,
    const VNodeType& degArrSize, VLinkType& linkSum, const int fix)
{
  if (degArrSize.empty()) {
    ERROR();
    return -1;
  }
  if (linkSum.empty()
      && 0 != degArr_2_linkSum(linkSum, degArrVal, degArrSize)) {
    ERROR();
    return -1;
  }
  if (0 != cal_Min_lkk(lkk, degArrVal, degArrSize, linkSum, fix)) {
    ERROR();
    return -1;
  }
  return 0;
}

//**//*****************************************************************//*
#endif // NET_EXTREMUM
