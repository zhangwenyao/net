#include "StatSimilarity.h"
#ifdef STAT_SIMILARITY

#include "common.h"
using namespace std;

//**//****************************************************//*
int cal_similarity(VVDouble &simiNodeCoef, VVDouble &simiEdgeCoef, const VVNodeType& p2p1, const VVNodeType& p2pIn1, const VNodeType& link1, const VVLinkType& p2p1_linkPos, const VVLinkType& p2pIn1_linkPos, const VVNodeType& p2p2, const VVNodeType& p2pIn2, const VNodeType& link2, const VVLinkType& p2p2_linkPos, const VVLinkType& p2pIn2_linkPos, const int dirFlag)
{
    VVDouble x, y;
    double xSum0 = 1, xSum = 0, ySum0 = 1, ySum = 0;
    const NodeType n1 = simiNodeCoef.size(), n2 = simiNodeCoef[0].size();
    x.resize(n1, VDouble(n2, 1));
    const LinkType l1 = simiEdgeCoef.size(), l2 = simiEdgeCoef[0].size();
    y.assign(l1, VDouble(l2, 1));
    while(!(0.999 * xSum0 < xSum && xSum < 1.001 * xSum0) || !(0.999 * ySum0 < ySum && ySum < 1.001 * ySum0)){
        xSum0 = xSum;
        ySum0 = ySum;
        cal_similarity_update(simiNodeCoef, simiEdgeCoef, p2p1, p2pIn1, link1, p2p1_linkPos, p2pIn1_linkPos, p2p2, p2pIn2, link2, p2p2_linkPos, p2pIn2_linkPos, x, xSum, y, ySum, dirFlag);
    }
    return 0;
}

int cal_similarity_update(VVDouble &simiNodeCoef, VVDouble &simiEdgeCoef, const VVNodeType& p2p1, const VVNodeType& p2pIn1, const VNodeType& link1, const VVLinkType& p2p1_linkPos, const VVLinkType& p2pIn1_linkPos, const VVNodeType& p2p2, const VVNodeType& p2pIn2, const VNodeType& link2, const VVLinkType& p2p2_linkPos, const VVLinkType& p2pIn2_linkPos, VVDouble &x, double &xSum, VVDouble &y, double &ySum, const int dirFlag)
{
    const LinkType l1 = simiEdgeCoef.size(), l2 = simiEdgeCoef[0].size();
    for(NodeType p = 0; p < l1; ++p)
        for(NodeType q = 0; q < l2; ++q){
            y[p][q] = simiNodeCoef[link1[p*2]][link2[q*2]] + simiNodeCoef[link1[p*2 + 1]][link2[q*2 + 1]];
        }

    const NodeType n1 = simiNodeCoef.size(), n2 = simiNodeCoef[0].size();
    for(NodeType i = 0; i < n1; ++i)
        for(NodeType j = 0; j < n2; ++j){
            x[i][j] = 0;
            for(NodeType k = 0; k < p2p1[i].size(); ++k)
                for(NodeType l = 0; l < p2p2[j].size(); ++l){
                    x[i][j] += simiEdgeCoef[p2p1_linkPos[i][k]][p2p2_linkPos[j][l]];
                }
        }
    if(dirFlag){
        for(NodeType i = 0; i < n1; ++i)
            for(NodeType j = 0; j < n2; ++j){
                for(NodeType k = 0; k < p2pIn1[i].size(); ++k)
                    for(NodeType l = 0; l < p2pIn2[j].size(); ++l){
                        x[i][j] += simiEdgeCoef[p2pIn1_linkPos[i][k]][p2pIn2_linkPos[j][l]];
                    }
            }
    }

    ySum = 0;
    for(NodeType p = 0; p < l1; ++p)
        for(NodeType q = 0; q < l2; ++q)
            ySum += y[p][q];
    if(ySum > 0){
        for(NodeType p = 0; p < l1; ++p)
            for(NodeType q = 0; q < l2; ++q)
                simiEdgeCoef[p][q] = y[p][q] / ySum;
    }else{
        simiEdgeCoef = y;
    }

    xSum = 0;
    for(NodeType i = 0; i < n1; ++i)
        for(NodeType j = 0; j < n2; ++j)
            xSum += x[i][j];
    if(xSum > 0){
        for(NodeType i = 0; i < n1; ++i)
            for(NodeType j = 0; j < n2; ++j)
                simiNodeCoef[i][j] = x[i][j] / xSum;
    }else{
        simiNodeCoef = x;
    }

    return 0;
}
//**//****************************************************//*
#endif  // STAT_SIMILARITY
