#ifndef NET_H
#define NET_H

#include <cfloat>
#include <climits>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "commonRandom.h"

const std::string NET_VERSION = "net2.0: " __DATE__ ", " __TIME__;
//**//*****************************************************//*
//#define NET_DEGREE  // 节点度分布
//#define DEG_POISSON // 泊松分布
//#define DEG_POWER  // 幂律分布

//#define NET_EXTREMUM  // 特例网络
//#define NET_RANDOM  // 随机网络
//#define NET_BA          // BA网络
//#define NET_GRID        // 网格网络
//#define NET_ACTOR
//#define NET_FOODWEB

// const bool STAT_TYPE_DIRAA = 0;  // 0:OutIn, 1: OutIn OutOut InOut InIn
//#define STAT_PEARSON
//#define STAT_SPEARMAN
//#define MODEL_GAUSS
//#define MODEL_EXP

//#define STAT_KENDALL
#define STAT_BETWEENNESS
//#define STAT_MODULARITY
//#define STAT_CLUSTER
//#define STAT_SIMILARITY

//#define ACT_RECOMMEND
//#define ACT_FITNESS_COMPLEXITY
//#define ACT_SIS

//**//*****************************************************//*
typedef unsigned NodeType;          // 节点编号类型
typedef int NodeSType;              // 节点数目有符号类型
const NodeType NodeMax = UINT_MAX;  // 最大编号节点、空节点，不用
const NodeType NodeNULL = UINT_MAX;

#if RAND2_MAX <= 32768
typedef unsigned long LinkType;
typedef long LinkSType;
#else
typedef unsigned long long LinkType;
typedef long long LinkSType;
#endif

typedef unsigned DistType;          // 节点间距离类型
typedef int DistSType;              // 节点间距离类型
const DistType DistMax = UINT_MAX;  // 距离无穷大的值
// typedef unsigned    DistType;   // 节点间距离类型
// typedef unsigned    DistSType;   // 节点间距离类型
// const DistType      DistMax = DBL_MAX; // 距离无穷大的值

typedef double WeightType;             // 边权
typedef double WeightSType;            // 边权
typedef double WeightSumType;          // 边权
typedef double WeightSumSType;         // 边权
const WeightType WeightMax = DBL_MAX;  // 距离无穷大的值

typedef std::vector<char> VChar;
typedef std::vector<VChar> VVChar;
typedef char* PChar;
typedef std::vector<char>::iterator VCharItr;
typedef std::vector<char>::const_iterator VCharCItr;
typedef std::vector<VChar>::iterator VVCharItr;
typedef std::vector<VChar>::const_iterator VVCharCItr;

typedef std::vector<bool> VBool;
typedef std::vector<VBool> VVBool;
typedef bool* PBool;
typedef std::vector<bool>::iterator VBoolItr;
typedef std::vector<bool>::const_iterator VBoolCItr;
typedef std::vector<VBool>::iterator VVBoolItr;
typedef std::vector<VBool>::const_iterator VVBoolCItr;

typedef std::vector<short> VShort;
typedef std::vector<VShort> VVShort;
typedef short* PShort;
typedef std::vector<short>::iterator VShortItr;
typedef std::vector<short>::const_iterator VShortCItr;
typedef std::vector<VShort>::iterator VVShortItr;
typedef std::vector<VShort>::const_iterator VVShortCItr;

typedef std::vector<int> VInt;
typedef std::vector<VInt> VVInt;
typedef int* PInt;
typedef std::vector<int>::iterator VIntItr;
typedef std::vector<int>::const_iterator VIntCItr;
typedef std::vector<VInt>::iterator VVIntItr;
typedef std::vector<VInt>::const_iterator VVIntCItr;

typedef std::vector<unsigned> VUnsigned;
typedef std::vector<VUnsigned> VVUnsigned;
typedef unsigned* PUnsigned;
typedef std::vector<unsigned>::iterator VUnsignedItr;
typedef std::vector<unsigned>::const_iterator VUnsignedCItr;
typedef std::vector<VUnsigned>::iterator VVUnsignedItr;
typedef std::vector<VUnsigned>::const_iterator VVUnsignedCItr;

typedef std::vector<double> VDouble;
typedef std::vector<VDouble> VVDouble;
typedef double* PDouble;
typedef std::vector<double>::iterator VDoubleItr;
typedef std::vector<double>::const_iterator VDoubleCItr;
typedef std::vector<VDouble>::iterator VVDoubleItr;
typedef std::vector<VDouble>::const_iterator VVDoubleCItr;

typedef std::vector<NodeType> VNodeType;
typedef std::vector<VNodeType> VVNodeType;
typedef NodeType* PNodeType;
typedef std::vector<NodeType>::iterator VNodeTypeItr;
typedef std::vector<NodeType>::const_iterator VNodeTypeCItr;
typedef std::vector<VNodeType>::iterator VVNodeTypeItr;
typedef std::vector<VNodeType>::const_iterator VVNodeTypeCItr;

typedef std::vector<LinkType> VLinkType;
typedef std::vector<VLinkType> VVLinkType;
typedef LinkType* PLinkType;
typedef std::vector<LinkType>::iterator VLinkTypeItr;
typedef std::vector<LinkType>::const_iterator VLinkTypeCItr;
typedef std::vector<VLinkType>::iterator VVLinkTypeItr;
typedef std::vector<VLinkType>::const_iterator VVLinkTypeCItr;

typedef std::vector<DistType> VDistType;
typedef std::vector<VDistType> VVDistType;
typedef DistType* PDistType;
typedef std::vector<DistType>::iterator VDistTypeItr;
typedef std::vector<DistType>::const_iterator VDistTypeCItr;
typedef std::vector<VDistType>::iterator VVDistTypeItr;
typedef std::vector<VDistType>::const_iterator VVDistTypeCItr;

typedef std::vector<WeightType> VWeightType;
typedef std::vector<VWeightType> VVWeightType;
typedef WeightType* PWeightType;
typedef std::vector<WeightType>::iterator VWeightTypeItr;
typedef std::vector<WeightType>::const_iterator VWeightTypeCItr;
typedef std::vector<VWeightType>::iterator VVWeightTypeItr;
typedef std::vector<VWeightType>::const_iterator VVWeightTypeCItr;

typedef std::vector<WeightSumType> VWeightSumType;
typedef std::vector<VWeightSumType> VVWeightSumType;
typedef WeightSumType* PWeightSumType;
typedef std::vector<WeightSumType>::iterator VWeightSumTypeItr;
typedef std::vector<WeightSumType>::const_iterator VWeightSumTypeCItr;
typedef std::vector<VWeightSumType>::iterator VVWeightSumTypeItr;
typedef std::vector<VWeightSumType>::const_iterator VVWeightSumTypeCItr;

struct RNodeType {
  explicit RNodeType(NodeType s = 0, NodeType e = 0) : start(s), end(e) {}
  NodeType start, end;
};
typedef std::vector<RNodeType> VRNodeType;
typedef RNodeType* PRNodeType;
typedef std::vector<RNodeType>::iterator VRNodeTypeItr;
typedef std::vector<RNodeType>::const_iterator VRNodeTypeCItr;

typedef std::map<const NodeType, NodeType> MNodeType;
typedef MNodeType::iterator MNodeTypeItr;
typedef MNodeType::const_iterator MNodeTypeCItr;

std::ostream& operator<<(std::ostream& os, const RNodeType& r);
std::istream& operator>>(std::istream& is, RNodeType& r);
int save_VRNodeType_start(std::ostream& os, const VRNodeType& v, const char c);
int save_VRNodeType_start(const char* name, const VRNodeType& v,
                          const char c = '\t');
int save_VRNodeType_end(std::ostream& os, const VRNodeType& v, const char c);
int save_VRNodeType_end(const char* name, const VRNodeType& v,
                        const char c = '\t');

bool cmp_RNodeType_start(const RNodeType& a, const RNodeType& b);
bool cmp_RNodeType_end(const RNodeType& a, const RNodeType& b);
int nodeDeg_update_nodeMap(VNodeType& nodeDeg, const VRNodeType& nodeMap);

//**//*****************************************************//*
#ifndef RAND2_LONG
#if RAND2_MAX <= 32768
#define RAND2_LONG() ((LinkType)RAND2())
#define RAND2_LONG_MAX ((LinkType)RAND2_MAX)
#else
#define RAND2_LONG() (((LinkType)RAND2_MAX + 1) * RAND2() + RAND2())
#define RAND2_LONG_MAX (((LinkType)RAND2_MAX + 2) * RAND2_MAX)
#endif  // RAND2_MAX
#endif  // RAND2_LONG

//**//*****************************************************//*
int init_linkMatrC(VVChar& linkMatrC, const NodeType nodeSize);
int linkMatr_fix_0(VVDistType& linkMatr, const DistType MaxDist = DistMax);
int linkMatr_fix_max(VVDistType& linkMatr, const DistType MaxDist = DistMax);

int linkMatr_2_p2p(VVNodeType& p2p, const VVDistType& linkMatr);
int linkMatrC_2_p2p(VVNodeType& p2p, const VVChar& linkMatrC);
int p2p_2_linkMatr(VVDistType& linkMatr, const VVNodeType& p2p);
int p2p_2_p2pIn(VVNodeType& p2pIn, const VVNodeType& p2p);
int p2p_2_vvweight_sort(VVWeightType& vvweight, const VVNodeType& p2p);

int p2p_2_nodeSize(NodeType& nodeSize, const VVNodeType& p2p);
int p2p_2_nodeDeg(VNodeType& nodeDeg, const VVNodeType& p2p);
int nodeDeg_2_degArr(const VNodeType& nodeDeg, VNodeType& degArrVal,
                     VNodeType& degArrSize, VNodeType& degArrSum);
int nodeDeg_2_degArr_Sort(const VNodeType& nodeDeg, VNodeType& degArrVal,
                          VNodeType& degArrSize, VNodeType& degArrSum);
int degArr_2_nodeSize(NodeType& nodeSize, const VNodeType& degArrSize);
int degArr_2_nodeDeg(VNodeType& nodeDeg, const VNodeType& degArrVal,
                     const VNodeType& degArrSize);
int degArrVal_2_degArrNo(MNodeType& degArrNo, const VNodeType& degArrVal);

int degArrSize_2_degArrSum(VNodeType& degArrSum, const VNodeType& degArrSize);
int degArr_2_linkSize(LinkType& linkSize, const VNodeType& degArrVal,
                      const VNodeType& degArrSize, const int dirFlag = 0);
int degArr_2_linkSum(VLinkType& linkSum, const VNodeType& degArrVal,
                     const VNodeType& degArrSize);
int nodeDeg_2_linkSize(LinkType& linkSize, const VNodeType& nodeDeg,
                       const int dirFlag = 0);
int check_nodeDeg0(const VNodeType& nodeDeg);
int fix_nodeDeg(VNodeType& nodeDeg, const VDouble& degArrProb,
                const VNodeType& degArrVal, LinkType& linkSize);

int p2p_2_lkk(VVLinkType& lkk, const VVNodeType& p2p, const VNodeType& degNum,
              const NodeType degSize);
int p2p_2_lkk_dir(VVLinkType& lkkOutIn, const VVNodeType& p2p,
                  const VNodeType& nodeDegOut, const VNodeType& nodeDegIn,
                  MNodeType& degArrNoOut, MNodeType& degArrNoIn,
                  const NodeType degOutSize, const NodeType degInSize);
int p2p_2_lkk(VVLinkType& lkk, const VVNodeType& p2p, MNodeType& degArrNo,
              const NodeType degSize);
int p2p_2_lkk_noDir(VVLinkType& lkk, const VVNodeType& p2p, MNodeType& degArrNo,
                    const VNodeType& nodeDeg, const NodeType degSize);
int lkk_dir_2_nDir(VVLinkType& lkk);
int lkk_nDir_2_dir(VVLinkType& lkk);
int lkk_2_lkkSum(VVLinkType& lkkSum, const VVLinkType& lkk, const int dir);
int link_2_nodeSize(NodeType& nodeSize, const VNodeType& link);
int link_2_p2p(VVNodeType& p2p, const VNodeType& link, VVNodeType& p2pIn,
               NodeType& nodeSize, const int dirFlag);
int link_2_p2p_out(VVNodeType& p2p, const VNodeType& link, NodeType& nodeSize,
                   const int dirFlag);
int link_2_p2p_out_linkSize(VVNodeType& p2p, const VNodeType& link,
                            NodeType& nodeSize, LinkType linkSize,
                            const int dirFlag);
int link_2_p2p_in(VVNodeType& p2pIn, const VNodeType& link, NodeType& nodeSize,
                  const int dirFlag);
int p2p_2_link(VNodeType& link, const VVNodeType& p2p, const int dirFlag);
int vvweight_2_vvweightIn(VVWeightType& vvweightIn,
                          const VVWeightType& vvweight, const VVNodeType& p2p);
int weightMatr_2_linkMatr(VVDistType& linkMatr, const VVWeightType& weightMatr);

int link_2_lkk(VVLinkType& lkk, const VNodeType& link, const VNodeType& nodeDeg,
               MNodeType& degArrNo, const LinkType linkSize,
               const NodeType degSize);

int vvweight_2_nodeWeight(VWeightType& nodeWeight, const VVNodeType& p2p,
                          const VVWeightType& vvweight,
                          WeightSumType& netWeight);
int nodeDegIO_2_nodeDeg(VNodeType& nodeDeg, const VNodeType& nodeDegOut,
                        const VNodeType& nodeDegIn);
int nodeWeightIO_2_nodeWeight(VWeightType& nodeWeight,
                              const VWeightType& nodeWeightOut,
                              const VWeightType& nodeWeightIn);
int nodeWeight_2_degArrWeight(VWeightSumType& degArrWeight,
                              const VWeightSumType& nodeWeight,
                              const VNodeType& nodeDeg, MNodeType& degArrNo,
                              const NodeType degSize);
int degArrWeight_2_degArrWeightSum(VWeightSumType& degArrWeightSum,
                                   const VWeightSumType& degArrWeight);

//**//*****************************************************//*
int sort_p2p(VVNodeType& p2p);
int fix_p2p(VVNodeType& p2p, const int dirFlag = 0);
int qsort_p2p(VVNodeType& p2p, const VVDistType& linkMatr);

int del_pij(const NodeType i, const NodeType j, VVNodeType& p2p,
            VVNodeType& p2pIn, const int dirFlag);
int add_pij(const NodeType i, const NodeType j, VVNodeType& p2p,
            VVNodeType& p2pIn, const int dirFlag);

int sort_link_betwEdge(VNodeType& link, VVDouble& betwEdge,
                       LinkType linkSize = 0);

//**//*****************************************************//*
int addLink_linkMatrC_ranNode(
    VVChar& linkMatrC, LinkType& linkRemain);  // 每次直接随机抽取两个点连边
int addLink_linkMatr_ranNode(
    VVDistType& linkMatr, LinkType& linkRemain);  // 每次直接随机抽取两个点连边
int addLink_linkMatrC_ranNode2(
    VVChar& linkMatrC, VNodeType& nodeDeg, VNodeType& p2pSize,
    VNodeType& remPoiNum, LinkType& linkRemain,
    const LinkType tryCount = 10);  // 每次直接随机抽取两个点连边
int addLink_linkMatr_ranNode2(
    VVDistType& linkMatr, VNodeType& nodeDeg, VNodeType& p2pSize,
    VNodeType& remPoiNum, LinkType& linkRemain,
    const LinkType tryCount = 10);  // 每次直接随机抽取两个点连边

int addLink_p2p_ranNode(VVNodeType& p2p, VNodeType& nodeDeg,
                        VNodeType& remPoiNum, LinkType& linkRemain,
                        const LinkType tryCount);  // 每次直接随机抽取两个点连边
int addLink_p2p_ranNode0(
    VVNodeType& p2p, VNodeType& link, VNodeType& nodeDeg, VNodeType& remPoiNum,
    LinkType& linkRemain,
    const LinkType tryCount);  // 每次直接随机抽取两个点连边

int addLink_linkMatrC_proNode(VVChar& linkMatrC, LinkType& linkSize,
                              const double p);  // 所有点按概率p连边
int addLink_linkMatr_proNode(VVDistType& linkMatr, LinkType& linkSize,
                             const double p);  // 所有点按概率p连边

int addLink_p2p_proDeg(
    VVNodeType& p2p, VNodeType& link, const VNodeType& nodeDeg,
    const NodeType kMax, VNodeType& remPoiNum, LinkType& linkRemain,
    const LinkType tryCount);  // 随机选节点，概率正比于节点度

int addLink_p2p_ranLink(VVNodeType& p2p, VNodeType& nodeDeg,
                        LinkType& linkRemain, VNodeType& link,
                        const LinkType tryCount);  // 所有度中随机选
int addLink_p2p_ranLink_lkkProb(
    VVNodeType& p2p, const VNodeType& nodeDeg, VVDouble& lkkProb,
    MNodeType& degArrNo, NodeType& remPoiSize, LinkType& linkRemain,
    VNodeType& link,
    const LinkType tryCount);  // 剩余度中随机选点，且概率正比于lkkProb

int delLink_p2p_ranLink(VVNodeType& p2p, VNodeType& nodeDeg,
                        VNodeType& remPoiNum, LinkType& linkRemain,
                        const LinkType linkSize, VNodeType& link,
                        LinkType delCount);  // 随机选边
int delLink_linkMatrC_randNode10(VVChar& linkMatrC, const NodeType nodeSize,
                                 VNodeType& nodeDeg, VNodeType& p2pSize,
                                 VNodeType& remPoiNum, LinkType& linkRemain,
                                 const LinkType linkSize,
                                 LinkType delCount);  // 随机选点删边
int delLink_p2p_randNode(VVNodeType& p2p, const NodeType nodeSize,
                         const VNodeType& nodeDeg, VNodeType& remPoiNum,
                         NodeType& remPoiSize, LinkType& linkRemain,
                         const LinkType linkSize,
                         LinkType delCount);  // 随机选点删边
int delLink_p2p_ranNode1(VVNodeType& p2p, const NodeType nodeSize,
                         VNodeType& nodeDeg, VNodeType& remPoiNum,
                         NodeType& remPoiSize, LinkType& linkRemain,
                         const LinkType linkSize,
                         LinkType delCount);  // 随机选点再选边删除

//**//*****************************************************//*
int check_p2pSize_linkSize(const VVNodeType& p2p, const LinkType linkSize);
int check_p2p(const VVNodeType& p2p);
int check_p2p_nodeDeg(const VVNodeType& p2p, const VNodeType& nodeDeg);
int check_link(VNodeType& link);

int sort_link_greater_1(VNodeType& link, const VNodeType& nodeDeg);
int sort_link_smaller_1(VNodeType& link, const VNodeType& nodeDeg);
int sort_link_num_greater_1(VNodeType& link);
int sort_link_num_smaller_1(VNodeType& link);
int sort_link_greater_all(VNodeType& link, const VNodeType& p2pSize);
int sort_link_num_greater_all(VNodeType& link);
int sort_link_smaller_all(VNodeType& link, const VNodeType& p2pSize);
int sort_link_num_smaller_all(VNodeType& link);

//**//***********************************************************//*
int exchange_linkC_deg_same(VVChar& linkMatrC, VNodeType& link,
                            const VNodeType& p2pSize, LinkType count);
int exchange_linkC_degDiff(VVChar& linkMatrC, VNodeType& link,
                           const VNodeType& p2pSize, LinkType count);
int exchange_link_deg_same(VVDistType& linkMatr, VNodeType& link,
                           const VNodeType& p2pSize, LinkType count);
int exchange_link_deg_diff(VVDistType& linkMatr, VNodeType& link,
                           const VNodeType& p2pSize, LinkType count);

int exchange_linkC_num_same(VVChar& linkMatrC, VNodeType& link, LinkType count);
int exchange_linkC_num_diff(VVChar& linkMatrC, VNodeType& link, LinkType count);
int exchange_link_num_same(VVDistType& linkMatr, VNodeType& link,
                           LinkType count);
int exchange_link_num_diff(VVDistType& linkMatr, VNodeType& link,
                           LinkType count);

int count_sameAdiff(LinkType& sum, LinkType& sum1, LinkType& sum3,
                    LinkType& sum4, VLinkType& link, VNodeType& nodeDeg);

//**//*****************************************************//*
int read0_link(VNodeType& link, const char* name, const unsigned n);
int read_link(VNodeType& link, const char* name);
int read_weight_link(VVWeightType& vvweight, VVWeightType& vvweightIn,
                     const LinkType linkSize, const char* name,
                     const unsigned weight_m = 2, const unsigned weight_n = 3,
                     const int dirFlag = 0);
int read_link_weight_0(VNodeType& link, LinkType& linkSize,
                       VVWeightType& vvweight, VVWeightType& vvweightIn,
                       const char* name, const unsigned weight_m = 2,
                       const unsigned weight_n = 3, const int dirFlag = 0);

//**//*****************************************************//*
int cal_kMax_PowerLaw_NatureCutoff(NodeType& kMax, const NodeType nodeSize,
                                   const NodeType kMin, const double gamma);

//**//*****************************************************//*
#endif  // NET_H
