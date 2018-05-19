#ifndef NET_TYPE_H
#define NET_TYPE_H

#include <cfloat>
#include <climits>
#include <map>
#include <string>
#include <vector>

// *******************************************************
typedef unsigned NodeType;         // 节点编号类型
typedef int NodeSType;             // 节点数目有符号类型
const NodeType NodeMax = UINT_MAX; // 最大编号节点、空节点，不用
const NodeType NodeNULL = UINT_MAX;

// typedef unsigned long LinkType;
// typedef long LinkSType;
typedef unsigned long long LinkType;
typedef long long LinkSType;

typedef unsigned DistType;         // 节点间距离类型
typedef int DistSType;             // 节点间距离类型
const DistType DistMax = UINT_MAX; // 距离无穷大的值
// typedef double    DistType;     // 节点间距离类型
// typedef double    DistSType;    // 节点间距离类型
// const DistType      DistMax = DBL_MAX; // 距离无穷大的值

typedef double WeightType;            // 边权
typedef double WeightSType;           // 边权
typedef double WeightSumType;         // 边权求和
typedef double WeightSumSType;        // 边权求和
const WeightType WeightMax = DBL_MAX; // 距离无穷大的值

typedef std::vector<std::string> VString;
typedef std::vector<VString> VVString;
typedef std::string* PString;
typedef VString::iterator VStringItr;
typedef VString::const_iterator VStringCItr;
typedef VVString::iterator VVStringItr;
typedef VVString::const_iterator VVStringCItr;

typedef std::vector<char> VChar;
typedef std::vector<VChar> VVChar;
typedef char* PChar;
typedef VChar::iterator VCharItr;
typedef VChar::const_iterator VCharCItr;
typedef VVChar::iterator VVCharItr;
typedef VVChar::const_iterator VVCharCItr;

typedef std::vector<bool> VBool;
typedef std::vector<VBool> VVBool;
typedef bool* PBool;
typedef VBool::iterator VBoolItr;
typedef VBool::const_iterator VBoolCItr;
typedef VVBool::iterator VVBoolItr;
typedef VVBool::const_iterator VVBoolCItr;

typedef std::vector<short> VShort;
typedef std::vector<VShort> VVShort;
typedef short* PShort;
typedef VShort::iterator VShortItr;
typedef VShort::const_iterator VShortCItr;
typedef VVShort::iterator VVShortItr;
typedef VVShort::const_iterator VVShortCItr;

typedef std::vector<int> VInt;
typedef std::vector<VInt> VVInt;
typedef int* PInt;
typedef VInt::iterator VIntItr;
typedef VInt::const_iterator VIntCItr;
typedef VVInt::iterator VVIntItr;
typedef VVInt::const_iterator VVIntCItr;

typedef std::vector<unsigned> VUnsigned;
typedef std::vector<VUnsigned> VVUnsigned;
typedef unsigned* PUnsigned;
typedef VUnsigned::iterator VUnsignedItr;
typedef VUnsigned::const_iterator VUnsignedCItr;
typedef VVUnsigned::iterator VVUnsignedItr;
typedef VVUnsigned::const_iterator VVUnsignedCItr;

typedef std::vector<double> VDouble;
typedef std::vector<VDouble> VVDouble;
typedef double* PDouble;
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

std::ostream& operator<<(std::ostream& os, const RNodeType& r);
std::istream& operator>>(std::istream& is, RNodeType& r);
int save_VRNodeType_start(std::ostream& os, const VRNodeType& v, const char c);
int save_VRNodeType_start(
    const char* name, const VRNodeType& v, const char c = '\t');
int save_VRNodeType_end(std::ostream& os, const VRNodeType& v, const char c);
int save_VRNodeType_end( const char* name, const VRNodeType& v, const char c = '\t');

bool cmp_RNodeType_start(const RNodeType& a, const RNodeType& b);
bool cmp_RNodeType_end(const RNodeType& a, const RNodeType& b);

// *******************************************************
#endif
