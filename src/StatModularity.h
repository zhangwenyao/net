#ifndef STAT_MODULARITY_H
#define STAT_MODULARITY_H

#include "net.h"

#ifdef STAT_MODULARITY
//**//****************************************************//*
int save_moduStk(std::ostream& os, const VNodeType& moduStk,
                 const VRNodeType& moduRange, const char c = '\t');
int save_moduStk(const VNodeType& moduStk, const VRNodeType& moduRange,
                 const char* name, const char c = '\t');

int modularity_move(const NodeType a, const NodeType b, VNodeType& moduStk,
                    VNodeType& moduNum,
                    VRNodeType& moduRange);  // b组移到a组后面
int modularity_merge(const NodeType a, const NodeType b, VNodeType& moduVal,
                     VNodeType& moduStk, VNodeType& moduNum,
                     VRNodeType& moduRange);  // b组移到a组后面、合并

int moduStk_sort(VNodeType& moduStk, VRNodeType& moduRange,
                 VNodeType& moduNum);  //各组按节点编号排序

int cal_modularity(VNodeType& moduVal, VNodeType& moduStk, VNodeType& moduNum,
                   VRNodeType& moduRange, const VVNodeType& p2p,
                   const VVNodeType& p2pIn, const int dirFlag = 0);  // 分组
int update_modularity_iNode(const NodeType i, VNodeType& moduVal,
                            VNodeType& moduStk, VNodeType& moduNum,
                            VRNodeType& moduRange, const VVNodeType& p2p,
                            const VVNodeType& p2pIn,
                            const int dirFlag = 0);  // 更新节点i所在分组

int cal_moduLKK(VVLinkType& moduLKK, const NodeType moduSize,
                const VNodeType& moduVal, const VVNodeType& p2p,
                const int dirFlag = 0);  // 统计不同组之间连边数
int cal_moduCoef(double& moduCoef, const VVLinkType& moduLKK,
                 const int dirFlag);  // 计算分组系数Q
int cal_moduNodeCoef(VDouble& moduNodeCoef, const NodeType moduSize,
                     const VNodeType& moduVal,
                     const VVNodeType& p2p);  // 计算节点分组系数P

//**//****************************************************//*
#endif  // STAT_MODULARITY
#endif  // STAT_MODULARITY_H
