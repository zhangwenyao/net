#include "StatModularity.h"
#ifdef STAT_MODULARITY

#include "common.h"
using namespace std;

// ******************************************************
int save_moduStk(ostream& os, const VNodeType& moduStk,
                 const VRNodeType& moduRange, const char c) {
  if (!os) return -1;
  const NodeType size = moduRange.size();
  for (NodeType i = 0; i < size;) {
    common_save(os, &moduStk[moduRange[i].start],
                moduRange[i].end - moduRange[i].start, c);
    if (++i < size) os << '\n';
  }
  return 0;
}

int save_moduStk(const VNodeType& moduStk, const VRNodeType& moduRange,
                 const char* name, const char c) {
  if (name == NULL || name[0] == '\0') return -1;
  ofstream os(name);
  if (!os) return -1;
  save_moduStk(os, moduStk, moduRange, c);
  os.close();
  return 0;
}

// ******************************************************
int modularity_move(const NodeType a, const NodeType b, VNodeType& moduStk,
                    VNodeType& moduNum,
                    VRNodeType& moduRange)  // b组移到a组后面
{
  if (a == b || moduRange[a].end == moduRange[b].start) return 0;
  RNodeType ra = moduRange[a], rb = moduRange[b], r1, r2;
  NodeType a1, a2;
  if (a < b)
    a1 = a, a2 = b, r1 = ra, r2 = rb;
  else
    a1 = b, a2 = a, r1 = rb, r2 = ra;
  VNodeType tmp(moduStk.begin() + r2.start, moduStk.begin() + r2.end);
  for (NodeType iStart = (a < b ? r1.end : r1.start), iEnd = r2.start,
                pos = r2.end;
       iStart < iEnd;) {  // a、b间元素后移
    NodeType k = moduStk[--iEnd];
    moduStk[--pos] = k;
    moduNum[k] = pos;
  }
  for (NodeType pos = (a < b ? r1.end : r1.start), i = 0;
       i < tmp.size();) {  // r2前移
    NodeType k = tmp[i++];
    moduStk[pos] = k;
    moduNum[k] = pos++;
  }
  for (NodeType num = a1 + 1, r2size = r2.end - r2.start; num < a2;
       num++) {  //更新a、b间分组位置的范围
    moduRange[num].start += r2size;
    moduRange[num].end += r2size;
  }
  //更新a、b分组位置的范围
  if (a > b)
    moduRange[a].start = rb.start,
    moduRange[a].end = rb.start + ra.start - ra.end;
  moduRange[b].start = moduRange[a].end,
  moduRange[b].end = moduRange[a].end + rb.end - rb.start;
  return 0;
}

int modularity_merge(const NodeType a, const NodeType b, VNodeType& moduVal,
                     VNodeType& moduStk, VNodeType& moduNum,
                     VRNodeType& moduRange)  // b组移到a组后面、合并
{
  if (a == b) return 0;
  modularity_move(a, b, moduStk, moduNum, moduRange);  // 移动
  //合并
  RNodeType ra = moduRange[a], rb = moduRange[b], r1, r2;
  NodeType a1, a2;
  if (a < b)
    a1 = a, a2 = b, r1 = ra, r2 = rb;
  else
    a1 = b, a2 = a, r1 = rb, r2 = ra;
  moduRange[a1].end += r2.end - r2.start;
  moduRange.erase(moduRange.begin() + a2);
  // 更新的组号
  for (NodeType i = r2.start; i < r2.end; i++) moduVal[moduStk[i]] = a1;
  for (NodeType num = a2; num < moduRange.size(); num++) {
    for (NodeType i = moduRange[num].start; i < moduRange[num].end; i++) {
      moduVal[moduStk[i]] = num;
    }
  }
  return 0;
}

int moduStk_sort(VNodeType& moduStk, VRNodeType& moduRange,
                 VNodeType& moduNum) {
  const NodeType moduSize = moduRange.size();
  for (NodeType i = 0; i < moduSize; i++)
    sort(moduStk.begin() + moduRange[i].start,
         moduStk.begin() + moduRange[i].end);
  for (NodeType i = 0; i < moduStk.size(); i++) moduNum[moduStk[i]] = i;
  return 0;
}

// ******************************************************
int cal_modularity(VNodeType& moduVal, VNodeType& moduStk, VNodeType& moduNum,
                   VRNodeType& moduRange, const VVNodeType& p2p,
                   const VVNodeType& p2pIn, const int dirFlag) {
  const NodeType nodeSize = p2p.size();
  NodeType moduSize = nodeSize;
  moduVal.assign(nodeSize, nodeSize);
  moduRange.clear();
  moduStk.resize(nodeSize);
  moduNum.resize(nodeSize);
  if (nodeSize <= 0) return 0;
  for (NodeType i = 0; i < nodeSize; i++) {
    moduStk[i] = i;
    moduNum[i] = i;
  }

  moduRange.push_back(RNodeType(0, nodeSize));
  for (NodeType pos = 0, mEnd = 1; mEnd < nodeSize; pos++) {
    NodeType i = moduStk[pos];
    if (moduVal[i] == nodeSize) {
      // 新分组
      if (moduRange.rbegin()->start != pos) {
        moduRange.rbegin()->end = pos;
        moduRange.push_back(RNodeType(pos, nodeSize));
      } else {
        moduRange.rbegin()->end = nodeSize;
      }
      if (moduSize == nodeSize)
        moduSize = 0;
      else
        ++moduSize;
      moduVal[i] = moduSize;
      mEnd = pos + 1;
    }
    for (VNodeTypeCItr itr = p2p[i].begin(); itr != p2p[i].end(); itr++) {
      const NodeType j = *itr;
      if (moduVal[j] == nodeSize) {
        moduVal[j] = moduSize;
        if (moduNum[j] != mEnd) {
          NodeType jPos = moduNum[j],
                   k = moduStk[mEnd];  // j和moduStk[mEnd]调换位置
          moduStk[jPos] = k;
          moduNum[k] = jPos;
          moduStk[mEnd] = j;
          moduNum[j] = mEnd;
        }
        mEnd++;
      }
    }
    if (dirFlag) {
      for (VNodeTypeCItr itr = p2pIn[i].begin(); itr != p2pIn[i].end(); itr++) {
        const NodeType j = *itr;
        if (moduVal[j] == nodeSize) {
          moduVal[j] = moduSize;
          if (moduNum[j] != mEnd) {
            NodeType jPos = moduNum[j],
                     k = moduStk[mEnd];  // j和moduStk[mEnd]调换位置
            moduStk[jPos] = k;
            moduNum[k] = jPos;
            moduStk[mEnd] = j;
            moduNum[j] = mEnd;
          }
          mEnd++;
        }
      }
    }
  }
  return 0;
}

int update_modularity_iNode(const NodeType i, VNodeType& moduVal,
                            VNodeType& moduStk, VNodeType& moduNum,
                            VRNodeType& moduRange, const VVNodeType& p2p,
                            const VVNodeType& p2pIn, const int dirFlag) {
  NodeType iVal = moduVal[i], pos = moduRange[iVal].start, mEnd = pos + 1;
  if (moduNum[i] != pos) {  //移动节点i至其分组第一个
    NodeType iPos = moduNum[i], k = moduStk[pos];
    moduStk[iPos] = k;
    moduNum[k] = iPos;
    moduStk[pos] = i;
    moduNum[i] = pos;
  }
  while (pos < mEnd) {  // 搜索节点i所在分组节点
    NodeType ii = moduStk[pos];
    for (VNodeTypeCItr itr = p2p[ii].begin(); itr != p2p[ii].end(); itr++) {
      NodeType j = *itr;
      if (moduVal[j] != iVal) {  // 出现待合并分组
        modularity_merge(iVal, moduVal[j], moduVal, moduStk, moduNum,
                         moduRange);
        mEnd = moduNum[ii] + mEnd - pos;
        pos = moduNum[ii];
      }
      if (moduNum[j] >= mEnd) {  // 访问到新点，移动到i后面
        if (moduNum[j] > mEnd) {
          NodeType jPos = moduNum[j],
                   k = moduStk[mEnd];  // j和moduStk[mEnd]调换位置
          moduStk[jPos] = k;
          moduNum[k] = jPos;
          moduStk[mEnd] = j;
          moduNum[j] = mEnd;
        }
        mEnd++;
      }
    }
    if (dirFlag) {
      for (VNodeTypeCItr itr = p2pIn[ii].begin(); itr != p2pIn[ii].end();
           itr++) {
        const NodeType j = *itr;
        if (moduVal[j] != iVal) {  // 出现待合并分组
          modularity_merge(iVal, moduVal[j], moduVal, moduStk, moduNum,
                           moduRange);
          mEnd = moduNum[ii] + mEnd - pos;
          pos = moduNum[ii];
        }
        if (moduNum[j] >= mEnd) {  // 访问到新点，移动到i后面
          if (moduNum[j] > mEnd) {
            NodeType jPos = moduNum[j],
                     k = moduStk[mEnd];  // j和moduStk[mEnd]调换位置
            moduStk[jPos] = k;
            moduNum[k] = jPos;
            moduStk[mEnd] = j;
            moduNum[j] = mEnd;
          }
          mEnd++;
        }
      }
    }
  }

  if (mEnd < moduRange[i].end) {  // 出现新组
    moduRange.push_back(RNodeType(mEnd, moduRange[i].end));
    for (NodeType pos = mEnd, ms = moduRange.size() - 1; pos < moduRange[i].end;
         pos++)
      moduVal[moduStk[pos]] = ms;
    moduRange[i].end = mEnd;
    update_modularity_iNode(moduStk[mEnd], moduVal, moduStk, moduNum, moduRange,
                            p2p, p2p, dirFlag);  // 继续更新分划新组
  }

  return 0;
}

// ******************************************************
int cal_moduLKK(VVLinkType& moduLKK, const NodeType moduSize,
                const VNodeType& moduVal, const VVNodeType& p2p,
                const int dirFlag) {
  moduLKK.resize(moduSize);
  moduLKK[0].assign(moduSize, 0);
  for (NodeType i = 1; i < moduSize; i++) moduLKK[i] = moduLKK[0];
  for (NodeType i = 0; i < p2p.size(); i++) {
    for (NodeType n = 0; n < p2p[i].size(); n++) {
      NodeType j = p2p[i][n];
      if (dirFlag || i > j) {
        moduLKK[moduVal[i]][moduVal[j]]++;
      }
    }
  }
  return 0;
}

int cal_moduCoef(double& moduCoef, const VVLinkType& moduLKK,
                 const int dirFlag) {
  const NodeType moduSize = moduLKK.size();
  if (moduSize <= 1) {
    moduCoef = 0;
    return 0;
  }
  if (!dirFlag) {
    double eii = 0, aii = 0;
    LinkType linkSize2 = 0;
    for (NodeType i = 0; i < moduSize; i++) {
      eii += (double)moduLKK[i][i];     // I
      LinkType ai = moduLKK[i][i] * 2;  // 2I + O
      for (NodeType j = 0; j < i; j++) ai += moduLKK[i][j];
      aii += ai * ai;
      linkSize2 += ai;
    }
    if (linkSize2 <= 0)
      moduCoef = 0;
    else
      moduCoef = 2. * eii / linkSize2 - aii / linkSize2 / linkSize2;
  } else {
    double eii = 0, aij = 0;
    LinkType linkSize = 0;
    for (NodeType i = 0; i < moduSize; i++) {
      eii += (double)moduLKK[i][i];  // I
      LinkType ai = 0, aj = 0;       // I + O
      for (NodeType j = 0; j < moduSize; j++) {
        ai += moduLKK[i][j];
        aj += moduLKK[j][i];
      }
      aij += ai * aj;
      linkSize += ai;
    }
    if (linkSize <= 0)
      moduCoef = 0;
    else
      moduCoef = eii / linkSize - aij / linkSize / linkSize;
  }
  return 0;
}

int cal_moduNodeCoef(VDouble& moduNodeCoef, const NodeType moduSize,
                     const VNodeType& moduVal, const VVNodeType& p2p) {
  const NodeType nodeSize = p2p.size();
  VNodeType s;
  moduNodeCoef.clear();
  if (nodeSize < 1) {
    return 0;
  }
  moduNodeCoef.assign(nodeSize, 0);
  for (NodeType i = 0, si; i < nodeSize; ++i) {
    si = p2p[i].size();
    if (si <= 0) continue;
    s.assign(moduSize, 0);
    for (VNodeTypeCItr itr = p2p[i].begin(); itr != p2p[i].end(); ++itr)
      ++s[moduVal[*itr]];
    double t = 0;
    for (NodeType n = 0; n < moduSize; ++n) t += (double)s[n] * s[n];
    moduNodeCoef[i] = 1 - t / si / si;
  }
  return 0;
}

// ******************************************************
#endif  // STAT_MODULARITY
