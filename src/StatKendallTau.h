#ifndef STAT_KENDALLTAU_H
#define STAT_KENDALLTAU_H

#include "net.h"

#ifdef STAT_KENDALLTAU
//**//****************************************************//*
int cal_kendallTau_lkk(double& kendallTau, const VVLinkType& lkk, const LinkType linkSize, const int dir);
int cal_kendallTau_lkkSum(double& kendallTau, const VVLinkType& lkk, const VVLinkType& lkkSum, const int dir);
int cal_kendallTau_p2p(double kendallTau, const VVNodeType& p2p, const VNodeType& nodeDegOut, const VNodeType& nodeDegIn, const LinkType linkSize, const int dir);

//**//****************************************************//*
#endif  // STAT_KENDALLTAU
#endif  // STAT_KENDALLTAU_H

