#ifndef STATISTICS__BETWEENNESS__BETWEENNESS_H_
#define STATISTICS__BETWEENNESS__BETWEENNESS_H_
#include "../../network/net.h"
#ifdef STAT_BETWEENNESS

namespace network {
namespace betweenness {
// ******************************************************
int cal_betweenness0(VDouble& betwNode, VVDouble& betwEdge, double& meanNode,
                     double& meanEdge, VVDistType& minDistMatr,
                     VDouble& minDistMean, const VVNodeType& p2p,
                     const VVNodeType& p2pIn);  // 无权网络介数
int cal_betweenness(VDouble& betwNode, VVDouble& betwEdge, double& meanNode,
                    double& meanEdge, VVDistType& minDistMatr,
                    VDouble& minDistMean, const VVNodeType& p2p,
                    const VVNodeType& p2pIn,
                    const VVDistType& linkMatr);  // 加权网络介数
}  // namespace betweenness
}  // namespace network

// ******************************************************
#endif  // STAT_BETWEENNESS
#endif  // STAT_BETWEENNESS_H
