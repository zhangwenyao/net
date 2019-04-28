#ifndef NETWORK__TYPE_H_
#define NETWORK__TYPE_H_

#include <cfloat>
#include <climits>
#include <map>
#include <string>
#include <vector>

namespace network {
// *******************************************************
// typedef unsigned NodeType;         // 节点编号类型
// typedef int NodeSType;             // 节点数目有符号类型
// typedef unsigned long LinkType;
// typedef long LinkSType;
// const NodeType NodeMax = UINT_MAX; // 最大编号节点、空节点，不用
// const NodeType NodeNULL = UINT_MAX;
// const LinkType LinkMax = ULONG_MAX;
// typedef unsigned DistType;         // 节点间距离类型
// typedef int DistSType;             // 节点间距离类型
// const DistType DistMax = UINT_MAX; // 距离无穷大的值

// typedef double    DistType;     // 节点间距离类型
// typedef double    DistSType;    // 节点间距离类型
// const DistType    DistMax = DBL_MAX; // 距离无穷大的值

typedef unsigned long NodeType; // 节点编号类型
typedef long int NodeSType;     // 节点数目有符号类型
typedef unsigned long long LinkType;
typedef long long LinkSType;
const NodeType NodeMax = ULONG_MAX; // 最大编号节点、空节点，不用
const NodeType NodeNULL = ULONG_MAX;
const LinkType LinkMax = ULLONG_MAX;
typedef long unsigned DistType;     // 节点间距离类型
typedef long int DistSType;         // 节点间距离类型
const DistType DistMax = ULONG_MAX; // 距离无穷大的值

typedef double WeightType;            // 边权
typedef double WeightSType;           // 边权
typedef double WeightSumType;         // 边权求和
typedef double WeightSumSType;        // 边权求和
const WeightType WeightMax = DBL_MAX; // 距离无穷大的值

typedef std::string String;
typedef std::vector<String> VString;
typedef std::vector<VString> VVString;
typedef std::string* PString;
typedef VString::iterator VStringItr;
typedef VString::const_iterator VStringCItr;
typedef VVString::iterator VVStringItr;
typedef VVString::const_iterator VVStringCItr;

typedef char Char;
typedef std::vector<Char> VChar;
typedef std::vector<VChar> VVChar;
typedef char* PChar;
typedef VChar::iterator VCharItr;
typedef VChar::const_iterator VCharCItr;
typedef VVChar::iterator VVCharItr;
typedef VVChar::const_iterator VVCharCItr;

typedef bool Bool;
typedef std::vector<Bool> VBool;
typedef std::vector<VBool> VVBool;
typedef bool* PBool;
typedef VBool::iterator VBoolItr;
typedef VBool::const_iterator VBoolCItr;
typedef VVBool::iterator VVBoolItr;
typedef VVBool::const_iterator VVBoolCItr;

typedef short Short;
typedef std::vector<Short> VShort;
typedef std::vector<VShort> VVShort;
typedef short* PShort;
typedef VShort::iterator VShortItr;
typedef VShort::const_iterator VShortCItr;
typedef VVShort::iterator VVShortItr;
typedef VVShort::const_iterator VVShortCItr;

typedef int Int;
typedef std::vector<Int> VInt;
typedef std::vector<VInt> VVInt;
typedef int* PInt;
typedef VInt::iterator VIntItr;
typedef VInt::const_iterator VIntCItr;
typedef VVInt::iterator VVIntItr;
typedef VVInt::const_iterator VVIntCItr;

typedef unsigned Unsigned;
typedef std::vector<Unsigned> VUnsigned;
typedef std::vector<VUnsigned> VVUnsigned;
typedef unsigned* PUnsigned;
typedef VUnsigned::iterator VUnsignedItr;
typedef VUnsigned::const_iterator VUnsignedCItr;
typedef VVUnsigned::iterator VVUnsignedItr;
typedef VVUnsigned::const_iterator VVUnsignedCItr;

typedef double Double;
typedef std::vector<Double> VDouble;
typedef std::vector<VDouble> VVDouble;
typedef Double* PDouble;
typedef VDouble::iterator VDoubleItr;
typedef VDouble::const_iterator VDoubleCItr;
typedef VVDouble::iterator VVDoubleItr;
typedef VVDouble::const_iterator VVDoubleCItr;

typedef std::vector<NodeType> VNodeType;
typedef std::vector<VNodeType> VVNodeType;
typedef NodeType* PNodeType;
typedef VNodeType::iterator VNodeTypeItr;
typedef VNodeType::const_iterator VNodeTypeCItr;
typedef VVNodeType::iterator VVNodeTypeItr;
typedef VVNodeType::const_iterator VVNodeTypeCItr;

typedef std::vector<LinkType> VLinkType;
typedef std::vector<VLinkType> VVLinkType;
typedef LinkType* PLinkType;
typedef VLinkType::iterator VLinkTypeItr;
typedef VLinkType::const_iterator VLinkTypeCItr;
typedef VVLinkType::iterator VVLinkTypeItr;
typedef VVLinkType::const_iterator VVLinkTypeCItr;

typedef std::vector<DistType> VDistType;
typedef std::vector<VDistType> VVDistType;
typedef DistType* PDistType;
typedef VDistType::iterator VDistTypeItr;
typedef VDistType::const_iterator VDistTypeCItr;
typedef VVDistType::iterator VVDistTypeItr;
typedef VVDistType::const_iterator VVDistTypeCItr;

typedef std::vector<WeightType> VWeightType;
typedef std::vector<VWeightType> VVWeightType;
typedef WeightType* PWeightType;
typedef VWeightType::iterator VWeightTypeItr;
typedef VWeightType::const_iterator VWeightTypeCItr;
typedef VVWeightType::iterator VVWeightTypeItr;
typedef VVWeightType::const_iterator VVWeightTypeCItr;

typedef std::vector<WeightSumType> VWeightSumType;
typedef std::vector<VWeightSumType> VVWeightSumType;
typedef WeightSumType* PWeightSumType;
typedef VWeightSumType::iterator VWeightSumTypeItr;
typedef VWeightSumType::const_iterator VWeightSumTypeCItr;
typedef VVWeightSumType::iterator VVWeightSumTypeItr;
typedef VVWeightSumType::const_iterator VVWeightSumTypeCItr;

template <typename T1, typename T2, typename T3> struct Struct3 {
  T1 x;
  T2 y;
  T3 val;
};

typedef struct Struct3<NodeType, NodeType, NodeType> Lkk3NodeType;
typedef Lkk3NodeType* PLkk3NodeType;
typedef struct Struct3<NodeType, NodeType, LinkType> Lkk3LinkType;
typedef Lkk3LinkType* PLkk3LinkType;
typedef struct Struct3<NodeType, NodeType, Double> Lkk3Double;
typedef Lkk3Double* PLkk3Double;

typedef std::vector<Lkk3Double> VLkk3Double;
typedef VLkk3Double::iterator VLkk3DoubleItr;
typedef VLkk3Double::const_iterator VLkk3DoubleCItr;

typedef std::vector<Lkk3NodeType> VLkk3NodeType;
typedef VLkk3NodeType::iterator VLkk3NodeTypeItr;
typedef VLkk3NodeType::const_iterator VLkk3NodeTypeCItr;

typedef std::vector<Lkk3LinkType> VLkk3LinkType;
typedef VLkk3LinkType::iterator VLkk3LinkTypeItr;
typedef VLkk3LinkType::const_iterator VLkk3LinkTypeCItr;

struct RNodeType {
  explicit RNodeType(NodeType s = 0, NodeType e = 0)
      : start(s)
      , end(e)
  {
  }
  NodeType start, end;
};
typedef std::vector<RNodeType> VRNodeType;
typedef RNodeType* PRNodeType;
typedef VRNodeType::iterator VRNodeTypeItr;
typedef VRNodeType::const_iterator VRNodeTypeCItr;

typedef std::map<const NodeType, NodeType> MNodeType;
typedef MNodeType::iterator MNodeTypeItr;
typedef MNodeType::const_iterator MNodeTypeCItr;

int save_VRNodeType_start(
    std::ostream& os, const VRNodeType& v, const char c);
int save_VRNodeType_start(
    const char* name, const VRNodeType& v, const char c = '\t');
int save_VRNodeType_end(std::ostream& os, const VRNodeType& v, const char c);
int save_VRNodeType_end(
    const char* name, const VRNodeType& v, const char c = '\t');

bool cmp_RNodeType_start(const RNodeType& a, const RNodeType& b);
bool cmp_RNodeType_end(const RNodeType& a, const RNodeType& b);

// *******************************************************
}
std::ostream& operator<<(std::ostream& os, const network::RNodeType& r);
std::istream& operator>>(std::istream& is, network::RNodeType& r);
#include "type_template.h"
#endif
