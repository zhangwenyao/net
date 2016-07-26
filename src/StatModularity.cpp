#include "StatModularity.h"
#ifdef STAT_MODULARITY

#include "common.h"
using namespace std;

//**//****************************************************//*
int save_moduStk(ostream& os, const VNodeType& moduStk, const VRNodeType& moduRange)
{
    if(!os) return -1;
    const NodeType size = moduRange.size() - 1;
    for(NodeType i = 1; i <= size; i++){
        common_save(os, &moduStk[moduRange[i].start], moduRange[i].end - moduRange[i].start);
        if(i < size) os << '\n';
    }
    return 0;
}

int save_moduStk(const VNodeType& moduStk, const VRNodeType& moduRange, const char *name)
{
    if(name == NULL || name[0] == '\0') return -1;
    ofstream os(name);
    if(!os) return -1;
    save_moduStk(os, moduStk, moduRange);
    os.close();
    return 0;
}

//**//****************************************************//*
int modularity_move(const NodeType a, const NodeType b, VNodeType& moduVal, VNodeType& moduStk, VNodeType& moduNum, VRNodeType& moduRange)  // b组移到a组后面
{
    if(a == b || moduRange[a].end != moduRange[b].start)    return 0;
    RNodeType ra = moduRange[a], rb = moduRange[b], r1, r2;
    NodeType a1, a2;
    if(a < b)   a1 = a, a2 = b, r1 = ra, r2 = rb;
    else        a1 = b, a2 = a, r1 = rb, r2 = ra;
    VNodeType tmp(moduStk.begin() + r2.start, moduStk.begin() + r2.end);
    for(NodeType iStart = (a < b ? r1.end : r1.start), iEnd = r2.start, pos = r2.end; iStart < iEnd;){ // a、b间元素后移
        NodeType k = moduStk[--iEnd];
        moduStk[--pos] = k;
        moduNum[k] = pos;
    }
    for(NodeType pos = (a < b ? r1.end : r1.start), i = 0; i < tmp.size();){ // r2前移
        NodeType k = tmp[i++];
        moduStk[pos] = k;
        moduNum[k] = pos++;
    }
    for(NodeType num = a1 + 1, r2size = r2.end - r2.start; num < a2; num++){ //更新a、b间分组位置的范围
        moduRange[num].start += r2size;
        moduRange[num].end += r2size;
    }
    //更新a、b分组位置的范围
    if(a > b)   moduRange[a].start = rb.start, moduRange[a].end = rb.start + ra.start - ra.end;
    moduRange[b].start = moduRange[a].end, moduRange[b].end = moduRange[a].end + rb.end - rb.start;
    return 0;
}

int modularity_merge(const NodeType a, const NodeType b, VNodeType& moduVal, VNodeType& moduStk, VNodeType& moduNum, VRNodeType& moduRange) // b组移到a组后面、合并
{
    if(a == b)  return 0;
    modularity_move(a, b, moduVal, moduStk, moduNum, moduRange);  // 移动
    //合并
    RNodeType ra = moduRange[a], rb = moduRange[b], r1, r2;
    NodeType a1, a2;
    if(a < b)   a1 = a, a2 = b, r1 = ra, r2 = rb;
    else        a1 = b, a2 = a, r1 = rb, r2 = ra;
    moduRange[a1].end += r2.end - r2.start;
    moduRange.erase(moduRange.begin() + a2);
    // 更新的组号
    for(NodeType i = r2.start; i < r2.end; i++) moduVal[moduStk[i]] = a1;
    for(NodeType num = a2; num <= moduRange.size() - 1; num++){
        for(NodeType i = moduRange[num].start; i < moduRange[num].end; i++){
            moduVal[moduStk[i]] = num;
        }
    }
    return 0;
}

int moduStk_sort(VNodeType& moduStk, VRNodeType& moduRange, VNodeType& moduNum)
{
    const NodeType moduSize = moduRange.size();
    for(NodeType i = 1; i < moduSize; i++) sort(moduStk.begin() + moduRange[i].start, moduStk.begin() + moduRange[i].end);
    for(NodeType i = 0; i < moduStk.size(); i++) moduNum[moduStk[i]] = i;
    return 0;
}

//**//****************************************************//*
int cal_modularity(VNodeType& moduVal, VNodeType& moduStk, VNodeType& moduNum, VRNodeType& moduRange, const VVNodeType &p2p, const VVNodeType& p2pIn, const int dirFlag)
{
    const NodeType nodeSize = p2p.size();
    NodeType moduSize = 0;
    moduVal.assign(nodeSize, 0);
    moduRange.clear();
    moduStk.resize(nodeSize);
    moduNum.resize(nodeSize);
    if(nodeSize <= 0) return 0;
    for(NodeType i = 0; i < nodeSize; i++){
        moduStk[i] = i;
        moduNum[i] = i;
    }

    moduRange.push_back(RNodeType(0, nodeSize));
    for(NodeType pos = 0, mEnd = 1; mEnd < nodeSize; pos++){
        NodeType i = moduStk[pos];
        if(moduVal[i] == 0){
            moduRange.rbegin()->end = pos;
            moduRange.push_back(RNodeType(pos, nodeSize));
            moduVal[i] = ++moduSize;
            mEnd = pos + 1;
        }
        for(VNodeTypeCItr itr = p2p[i].begin(); itr != p2p[i].end(); itr++){
            const NodeType j = *itr;
            if(moduVal[j] == 0){
                moduVal[j] = moduSize;
                if(moduNum[j] != mEnd){
                    NodeType jPos = moduNum[j], k = moduStk[mEnd];  // j和moduStk[mEnd]调换位置
                    moduStk[jPos] = k;
                    moduNum[k] = jPos;
                    moduStk[mEnd] = j;
                    moduNum[j] = mEnd;
                }
                mEnd++;
            }
        }
        if(dirFlag){
            for(VNodeTypeCItr itr = p2pIn[i].begin(); itr != p2pIn[i].end(); itr++){
                const NodeType j = *itr;
                if(moduVal[j] == 0){
                    moduVal[j] = moduSize;
                    if(moduNum[j] != mEnd){
                        NodeType jPos = moduNum[j], k = moduStk[mEnd];  // j和moduStk[mEnd]调换位置
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

int update_modularity_iNode(const NodeType i, VNodeType& moduVal, VNodeType& moduStk, VNodeType& moduNum, VRNodeType& moduRange, const VVNodeType &p2p, const VVNodeType& p2pIn, const int dirFlag)
{
    NodeType iVal = moduVal[i], pos = moduRange[iVal].start, mEnd = pos + 1;
    if(moduNum[i] != pos){  //移动节点i至其分组第一个
        NodeType iPos = moduNum[i], k = moduStk[pos];
        moduStk[iPos] = k;
        moduNum[k] = iPos;
        moduStk[pos] = i;
        moduNum[i] = pos;
    }
    while(pos < mEnd){  // 搜索节点i所在分组节点
        NodeType ii = moduStk[pos];
        for(VNodeTypeCItr itr = p2p[ii].begin(); itr != p2p[ii].end(); itr++){
            NodeType j = *itr;
            if(moduVal[j] != iVal){ // 出现待合并分组
                modularity_merge(iVal, moduVal[j], moduVal, moduStk, moduNum, moduRange);
                mEnd = moduNum[ii] + mEnd - pos;
                pos = moduNum[ii];
            }
            if(moduNum[j] >= mEnd ){    // 访问到新点，移动到i后面
                if(moduNum[j] > mEnd){
                    NodeType jPos = moduNum[j], k = moduStk[mEnd];  // j和moduStk[mEnd]调换位置
                    moduStk[jPos] = k;
                    moduNum[k] = jPos;
                    moduStk[mEnd] = j;
                    moduNum[j] = mEnd;
                }
                mEnd++;
            }
        }
        if(dirFlag){
            for(VNodeTypeCItr itr = p2pIn[ii].begin(); itr != p2pIn[ii].end(); itr++){
                const NodeType j = *itr;
                if(moduVal[j] != iVal){ // 出现待合并分组
                    modularity_merge(iVal, moduVal[j], moduVal, moduStk, moduNum, moduRange);
                    mEnd = moduNum[ii] + mEnd - pos;
                    pos = moduNum[ii];
                }
                if(moduNum[j] >= mEnd ){    // 访问到新点，移动到i后面
                    if(moduNum[j] > mEnd){
                        NodeType jPos = moduNum[j], k = moduStk[mEnd];  // j和moduStk[mEnd]调换位置
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

    if(mEnd < moduRange[i].end){    // 出现新组
        moduRange.push_back(RNodeType(mEnd, moduRange[i].end));
        for(NodeType pos = mEnd, ms = moduRange.size() - 1; pos < moduRange[i].end; pos++) moduVal[moduStk[pos]] = ms;
        moduRange[i].end = mEnd;
        update_modularity_iNode(moduStk[mEnd], moduVal, moduStk, moduNum, moduRange, p2p, p2p, dirFlag);  // 继续更新分划新组
    }

    return 0;
}

//**//****************************************************//*
int cal_moduLKK(VVLinkType& moduLKK, const NodeType moduSize, const VNodeType& moduVal, const VVNodeType& p2p)
{
    moduLKK.resize(moduSize);
    moduLKK[0].assign(moduSize, 0);
    for(NodeType i = 0; i < moduSize; i++) moduLKK[i] = moduLKK[0];
    for(NodeType i = 0; i < p2p.size(); i++){
        for(NodeType n = 0, iVal = moduVal[i] - 1; n < p2p[i].size(); n++){
            NodeType jVal = moduVal[p2p[i][n]] - 1;
            moduLKK[iVal][jVal]++;
        }
    }
    return 0;
}

int cal_moduCoef(double& moduCoef, const VVLinkType& moduLKK, const LinkType& linkSize)
{
    const NodeType moduSize = moduLKK.size();
    if(moduSize <= 1){
        moduCoef = 1.;
        return 0;
    }
    double eii = 0, ab = 0;
    for(NodeType i = 0; i < moduSize; i++){
        eii += (double)moduLKK[i][i] * moduLKK[i][i];
        double ai = 0, bi = 0;
        for(NodeType j = 0; j < moduSize; j++){
            ai += moduLKK[i][j];
            bi += moduLKK[j][i];
        }
        ab += ai * bi;
    }
    moduCoef = eii - ab;
    ab = (double)linkSize * linkSize - ab;
    if(ab <= 0) moduCoef = 0;
    else moduCoef /= ab;
    return 0;
}

//**//****************************************************//*
#endif  // STAT_MODULARITY
