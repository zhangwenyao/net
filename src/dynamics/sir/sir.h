#ifndef DYNAMICS__SIR__SIR_H_
#define DYNAMICS__SIR__SIR_H_
#include "../../network/net.h"
#ifdef ACT_SIR

namespace network {
namespace sir {
// *******************************************************
int act_sir_id0(VNodeType& R_nums_, const double beta, const double gamma,
                const VVNodeType& p2p, const NodeType nodeSize,
                const NodeType id0);
int act_sir_beta_id0(VNodeType& R_nums_, const double beta,
                     const VVNodeType& p2p, const NodeType nodeSize,
                     const NodeType id0);
int act_sir_cal_lambdac(double& lambda_c, const VVNodeType& p2p);
int act_sir_cal_modularity(const VVNodeType& p2p, VNodeType& modularity_nums,
                           VNodeType& modularity_nums2,
                           const NodeType nodeSize);
int act_sir_cal_params(const VVNodeType& p2p, VDouble& Rs, const NodeType i,
                       VNodeType& R_nums_);
int act_sir_lambda(VDouble& Rs, const double beta, const VVNodeType& p2p,
                   const NodeType nodeSize);
}  // namespace sir
}  // namespace network
// *******************************************************
#endif  // ACT_SIR
#endif  // ACT_SIR_H
