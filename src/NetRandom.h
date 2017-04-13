#ifndef NET_RANDOM_H
#define NET_RANDOM_H

#include "net.h"

#ifdef NET_RANDOM
//**//*******************************************************;
int addLink_linkMatr_proNode(VVDistType& linkMatr, LinkType& linkSize,
                             const double p,
                             const int dirFlag = 0);  // 所有点按概率p连边
int addLink_linkMatrC_ranNode2(
    VVChar& linkMatrC, const VNodeType& nodeDeg, VNodeType& p2pSize,
    VNodeType& remNodeNum, LinkType& linkRemain,
    const LinkType tryCount);  // 每次直接随机抽取两个点连边
int addLink_linkMatr_ranNode2(
    VVDistType& linkMatr, const VNodeType& nodeDeg, VNodeType& p2pSize,
    VNodeType& remNodeNum, LinkType& linkRemain,
    const LinkType tryCount);  // 每次直接随机抽取两个点连边

int addLink_p2p_ranNode0(VVNodeType& p2p, VNodeType& link,
                         const VNodeType& nodeDeg, VNodeType& remNodeNum,
                         LinkType& linkRemain, const LinkType tryCount);
int addLink_p2p_ranNode(VVNodeType& p2p, const VNodeType& nodeDeg,
                        VNodeType& remNodeNum, LinkType& linkRemain,
                        const LinkType tryCount);
int addLink_p2p_remDeg(VVNodeType& p2p, const VNodeType& nodeDeg,
                       VNodeType& remNodeNum, LinkType& linkRemain,
                       VNodeType& link, const LinkType tryCount);
int addLink_p2p_ranLink_lkkProb(VVNodeType& p2p, const VNodeType& nodeDeg,
                                VVDouble& lkkProb, VNodeType& degArrNo,
                                VNodeType& remNodeNum, LinkType& linkRemain,
                                VNodeType& link, const LinkType tryCount);
int delLink_p2p_ranLink(VVNodeType& p2p, const VNodeType& nodeDeg,
                        VNodeType& remNodeNum, LinkType& linkRemain,
                        VNodeType& link, LinkType delCount);

int delLink_linkMatrC_ranNode(VVChar& linkMatrC, const NodeType nodeSize,
                              const VNodeType& nodeDeg, VNodeType& p2pSize,
                              VNodeType& remNodeNum, LinkType& linkRemain,
                              const LinkType linkSize,
                              LinkType delCount);  // 随机选点删边
int delLink_p2p_ranNode(VVNodeType& p2p, const NodeType nodeSize,
                        const VNodeType& nodeDeg, VNodeType& remNodeNum,
                        LinkType& linkRemain, const LinkType linkSize,
                        LinkType delCount);  // 随机选点删边
int delLink_p2p_ranNode1(VVNodeType& p2p, const NodeType nodeSize,
                         VNodeType& nodeDeg, VNodeType& remNodeNum,
                         LinkType& linkRemain, const LinkType linkSize,
                         LinkType delCount);  // 随机选点再选边删除

//**//****************************************************//*
#endif  // NET_RANDOM
#endif  // NET_RANDOM_H
