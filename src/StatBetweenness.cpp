#include "StatBetweenness.h"
#ifdef STAT_BETWEENNESS

#include "common.h"
using namespace std;

//**//****************************************************//*
int cal_betweenness0(VDouble &betw, VVDouble &betwEdge, double &bt, double& btEdge, VVDistType& minDistMatr, VDistType& minDistMean, const VVNodeType& p2p, const VVNodeType& p2pIn)
{
    if(p2p.size() <= 0 || p2pIn.size() <= 0){
        ERROR();
        return -1;
    }

    const NodeType nodeSize = p2p.size() >= p2pIn.size() ? p2p.size() : p2pIn.size();
    bt = 0;
    btEdge = 0;
    betw.assign(nodeSize, 0);
    betwEdge.assign(nodeSize, VDouble(nodeSize, 0));
    minDistMatr.resize(nodeSize);
    minDistMean.assign(nodeSize, 0);
    if(nodeSize < 2) return 0;

    VDistType   d(nodeSize);
    VNodeType   nodeStk(nodeSize);
    VLinkType   wayNum(nodeSize); // i到j最短路径的数目
    VDouble     b(nodeSize);    // i节点出发的介数
    NodeType stk_end, stk_head;
    for(NodeType i = 0; i < nodeSize; i++){ // 计算从i节点出发的最短路径、介数
        // 广度搜索算法，计算最短距离、最短路径路径数目，按距离存储编号nodeStk数组中
        if(p2p[i].size() <= 0){
            minDistMatr[i].assign(nodeSize, 0);
            continue;
        }
        d.assign(nodeSize, DistMax);   // 最短距离
        wayNum.assign(nodeSize, 0);
        d[i] = 0;
        wayNum[i] = 1;
        nodeStk[0] = i;
        stk_head = 0;
        stk_end = 1;
        while(stk_head != stk_end){
            NodeType iTmp = nodeStk[stk_head];
            for(VNodeTypeCItr itr = p2p[iTmp].begin(); itr != p2p[iTmp].end(); itr++){
                NodeType j = *itr;
                if(d[j] > d[iTmp]){
                    wayNum[j] += wayNum[iTmp];
                    if(d[j] == nodeSize){
                        d[j] = d[iTmp] + 1;
                        nodeStk[stk_end++] = j;
                    }
                }
            }
            stk_head++;
        }
        minDistMatr[i] = d;
        for(VDistTypeItr t = minDistMatr[i].begin(); t != minDistMatr[i].end(); t++) if(*t == DistMax) *t = 0;
        for(NodeType t = 1; t < stk_end; t++) minDistMean[i] += d[ nodeStk[t] ];
        if(stk_end > 1) minDistMean[i] /= stk_end;

        // 计算i节点出发的介数
        b.assign(nodeSize, 0);  // 介数
        stk_head = 0;
        stk_end--;
        while(stk_end > stk_head){
            NodeType jTmp = nodeStk[stk_end--];
            DistType dTmp = d[jTmp];
            betw[jTmp] += b[jTmp];  // 累计介数
            b[jTmp] += 1;
            double t = b[jTmp] / wayNum[jTmp];
            for(VNodeTypeCItr itr = p2pIn[jTmp].begin(); itr != p2pIn[jTmp].end(); itr++){
                if(d[*itr] < dTmp){
                    double t2 = wayNum[*itr] * t;
                    b[*itr] += t2;
                    betwEdge[*itr][jTmp] += t2;
                }
            }
        }
    }

    // 归一化、统计介数
    double t = 1. / nodeSize / (nodeSize - 1);
    for(NodeType i = 0; i < nodeSize; i++)
        for(NodeType j = 0; j < nodeSize; j++)
            if(j != i) btEdge += betwEdge[i][j] *= t;
    btEdge /= (double)nodeSize * (nodeSize - 1);
    if(nodeSize > 2){
        t = 1. / ((nodeSize - 1.) * (nodeSize - 2));
        for(NodeType i = 0; i < nodeSize; i++) bt += betw[i] *= t;
        bt /= nodeSize;
    }

    return 0;
}


//**//****************************************************//*
int cal_betweenness(VDouble  &betw, VVDouble &betwEdge, double &bt, double& btEdge, VVDistType& minDistMatr, VDistType& minDistMean, const VVNodeType& p2p, const VVNodeType& p2pIn, const VVDistType& linkMatr)
{
    if(p2p.size() <= 0 || p2pIn.size() <= 0 || linkMatr.size() <= 0 || linkMatr.size() != p2p.size()){
        ERROR();
        return -1;
    }

    const NodeType nodeSize = linkMatr.size();
    bt = 0;
    btEdge = 0;
    betw.assign(nodeSize, 0);
    betwEdge.clear();
    betwEdge.assign(nodeSize, VDouble(nodeSize, 0));
    minDistMatr.resize(nodeSize);
    minDistMean.assign(nodeSize, 0);
    if(nodeSize < 2) return 0;

    VNodeType   nodeStk(nodeSize), stkNum(nodeSize);    // nodeStk:按与节点i距离排序的节点j编号的堆栈，stkNum:j在堆栈中的位置
    VDistType   d(nodeSize); // d:i-j最短距离
    VLinkType   wayNum(nodeSize); // i到j最短路径的数目
    VDouble     b(nodeSize);    // i节点出发的介数
    NodeType    stk_end, stk_head;
    for(NodeType i = 0; i < nodeSize; i++){ // 计算从i节点出发的最短路径、介数
        if(p2p[i].size() <= 0){
            minDistMatr[i].assign(nodeSize, 0);
            continue;
        }
        // 初始化d、wayNum
        d.assign(nodeSize, DistMax);
        d[i] = 0;
        wayNum.assign(nodeSize, 0);
        wayNum[i] = 1;
        // 初始化nodeStk、stkNum
        for(NodeType j = 1; j < nodeSize; j++)  nodeStk[j] = j;
        nodeStk[0] = i;
        nodeStk[i] = 0;
        common_sort_p_val(&nodeStk[1], &nodeStk[nodeSize - 1], &linkMatr[i][0]);
        for(NodeType j = 0; j < nodeSize; j++)  stkNum[nodeStk[j]] = j;

        // 广度搜索算法，计算最短距离、最短路径路径数目
        stk_head = 0;
        stk_end = 1;
        while(stk_head != stk_end && stk_head < nodeSize){
            NodeType ii = nodeStk[stk_head];
            DistType dii = d[ii];
            for(VNodeTypeCItr itr = p2p[ii].begin(); itr != p2p[ii].end(); itr++){
                NodeType j = *itr;
                if(d[j] > dii + linkMatr[ii][j]){
                    if(d[j] == DistMax) stk_end++;
                    d[j] = dii + linkMatr[ii][j];
                    wayNum[j] = wayNum[ii];
                    // d[j]变小，同步更新nodeStk、stkNum
                    NodeType stk_jj = stkNum[j];
                    while(stk_jj > 0 && d[j] < d[nodeStk[stk_jj - 1]]){
                        nodeStk[stk_jj] = nodeStk[stk_jj - 1];
                        stkNum[nodeStk[stk_jj]] = stk_jj;
                        stk_jj--;
                    }
                    if(stkNum[j] != stk_jj){
                        nodeStk[stk_jj] = j;
                        stkNum[j] = stk_jj;
                    }
                }else if(d[j] == dii + linkMatr[ii][j]){
                    wayNum[j] += wayNum[ii];
                }
            }
            stk_head++;
        }
        minDistMatr[i] = d;
        for(VDistTypeItr t = minDistMatr[i].begin(); t != minDistMatr[i].end(); t++) if(*t == DistMax) *t = 0;
        for(NodeType t = 1; t < stk_end; t++) minDistMean[i] += d[ nodeStk[t] ];
        if(stk_end > 1) minDistMean[i] /= stk_end;

        // 计算i节点出发的介数
        b.assign(nodeSize, 0);  // 介数
        stk_head = 0;
        stk_end--;
        while(stk_end > stk_head){
            NodeType jTmp = nodeStk[stk_end--];
            DistType dTmp = d[jTmp];
            betw[jTmp] += b[jTmp];  // 累计介数
            b[jTmp] += 1;
            double t = b[jTmp] / wayNum[jTmp];
            for(VNodeTypeCItr itr = p2pIn[jTmp].begin(); itr != p2pIn[jTmp].end(); itr++){
                if(d[*itr] + linkMatr[*itr][jTmp] == dTmp) {    // *itr--jTmp在最短路径上
                    double t2 = wayNum[*itr] * t;
                    b[*itr] += t2;
                    betwEdge[*itr][jTmp] += t2;
                }
            }
        }
    }

    // 归一化、统计介数
    double t = 1. / nodeSize / (nodeSize - 1);
    for(NodeType i = 0; i < nodeSize; i++)
        for(NodeType j = 0; j < nodeSize; j++)
            if(j != i) btEdge += betwEdge[i][j] *= t;
    btEdge /= (double)nodeSize * (nodeSize - 1);
    if(nodeSize > 2){
        double t = 1. / ((nodeSize - 1.) * (nodeSize - 2));
        for(NodeType i = 0; i < nodeSize; i++) bt += betw[i] *= t;
        bt /= nodeSize;
    }

    return 0;
}

//**//****************************************************//*
#endif  // STAT_BETWEENNESS
