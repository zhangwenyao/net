#ifndef STAT_KENDALL_H
#define STAT_KENDALL_H

#include "net.h"

#ifdef STAT_KENDALL
//**//****************************************************//*
int cal_kendallTau_lkk(double& stat_kendall.tau, const VVLinkType& lkk, const LinkType linkSize, const int dir);
int cal_kendallTau_lkkSum(double& stat_kendall.tau, const VVLinkType& lkk, const VVLinkType& lkkSum, const int dir);
int cal_kendallTau_p2p(double stat_kendall.tau, const VVNodeType& p2p, const VNodeType& nodeDegOut, const VNodeType& nodeDegIn, const LinkType linkSize, const int dir);

//**//****************************************************//*
#endif  // STAT_KENDALL
#endif  // STAT_KENDALL_H

