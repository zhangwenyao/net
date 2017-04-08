#ifndef ACT_SIS_H
#define ACT_SIS_H

#include "net.h"

#ifdef ACT_SIS
//**//*****************************************************//*
int act_SIS_init(VVNodeType &statusSN, VVNodeType &SN, VNodeType &N_i, VLinkType & NDeg_i, VDouble &t, const VVNodeType& p2p, const double p0, const unsigned M);
int act_SIS(VVNodeType &statusSN, VVNodeType &SN, VNodeType &N_i, VLinkType &NDeg_i, VDouble &t, LinkType &nSum, LinkType &n2Sum, NodeType &nNum, const double p, const double lambda, const double t_r, double t_av, const VVNodeType& p2p, const NodeType degMax);
int act_SIS_cal_params(double &ksi, double &lambda_c, const VVNodeType& p2p, const NodeType& nSum, const LinkType& n2Sum, const NodeType& nNum);
//**//*****************************************************//*
#endif  // ACT_SIS
#endif  // ACT_SIS_H

