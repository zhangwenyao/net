#ifndef NET_EXTREMUM_H
#define NET_EXTREMUM_H

#include "net.h"

#ifdef NET_EXTREMUM
// ******************************************************
int lkk_new_p2p(VVNodeType& p2p, const VVLinkType& lkk,
    const VNodeType& nodeDeg, const VNodeType& degArrSize,
    const VNodeType& degArrSum);

int lkk_extreme_pearson(VVLinkType& lkk, const VNodeType& degArrVal,
    const VNodeType& degArrSize, const int extrMax, const unsigned countN = 3);

int cal_Max_lkk(VVLinkType& lkk, const VNodeType& degArrVal,
    const VNodeType& degArrSize, const int fix = 1);

int cal_Min_lkk_side2mid(VVLinkType& lkk, const VNodeType& degArrVal,
    const VNodeType& degArrSize, const int fix = 1);
int cal_Min_lkk_side2mid_fix(VVLinkType& lkk, const VNodeType& degArrVal,
    const VNodeType& degArrSize, const NodeType degSize, VLinkType& vlink,
    const NodeType& left, const NodeType& right, const NodeType& mid,
    LinkType& linkMid);
int cal_Min_lkk_mid2side(VVLinkType& lkk, const VNodeType& degArrVal,
    const VNodeType& degArrSize, const int fix = 1);

int Max_new(VVNodeType& p2p, const VNodeType& nodeDeg,
    const VNodeType& degArrVal, const VNodeType& degArrSize,
    const VNodeType& degArrSum); // 最大相关网络，按度安排
int Max_new_lkk(VVLinkType& lkk, const VNodeType& degArrVal,
    const VNodeType& degArrSize, const int fix = 1);

int Min_new(VVNodeType& p2p, const VNodeType& nodeDeg,
    const VNodeType& degArrVal, const VNodeType& degArrSize,
    const VNodeType& degArrSum); // 最小相关网络，按度安排
int Min_new_lkk(VVLinkType& lkk, const VNodeType& degArrVal,
    const VNodeType& degArrSize, const int fix = 1);
int Min_new_lkk_p2p(VVNodeType& p2p, VVLinkType& lkk, const VNodeType& nodeDeg,
    const VNodeType& degArrVal, const VNodeType& degArrSize,
    const VNodeType& degArrSum, const int fix
    = 0); // 最小相关网络，先生成lkk连接矩阵，再生成网络；按度从大到小，再从中间往连边修正

// ******************************************************
#endif // NET_EXTREMUM
#endif // NET_EXTREMUM_H
