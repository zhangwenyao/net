#ifndef NETWORK__TYPE_H_
#define NETWORK__TYPE_H_

#include <cfloat>
#include <climits>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../common/common.h"

namespace network {
// *******************************************************
// int:int32_t. long, long long: int64_t
typedef uint32_t NodeType;            // 节点编号类型
typedef int32_t NodeSType;            // 节点数目有符号类型
const NodeType NodeMax = UINT32_MAX;  // 最大编号节点、空节点，不用
const NodeType NodeNULL = UINT32_MAX;
typedef uint32_t LinkType;
typedef int32_t LinkSType;
typedef uint64_t LinkKeyType;
const LinkType LinkMax = UINT32_MAX;
typedef uint32_t DistType;            // 节点间距离类型
typedef int32_t DistSType;            // 节点间距离类型
const DistType DistMax = UINT32_MAX;  // 距离无穷大的值
inline LinkKeyType link_key(const NodeType i, const NodeType j) {
  return (LinkKeyType)i << 32 | j;
}

// typedef uint64_t NodeType; // 节点编号类型
// typedef int64_t NodeSType;     // 节点数目有符号类型
// const NodeType NodeMax =  UINT64_MAX; // 最大编号节点、空节点，不用
// const NodeType NodeNULL = UINT64_MAX;
// typedef uint64_t LinkType;
// typedef int64_t LinkSType;
// const LinkType LinkMax = UINT64_MAX;
// typedef uint64_t DistType;     // 节点间距离类型
// typedef int64_t DistSType;         // 节点间距离类型
// const DistType DistMax = UINT64_MAX; // 距离无穷大的值

// typedef double    DistType;     // 节点间距离类型
// typedef double    DistSType;    // 节点间距离类型
// const DistType    DistMax = DBL_MAX; // 距离无穷大的值

typedef double WeightType;             // 边权
typedef double WeightSType;            // 边权
typedef double WeightSumType;          // 边权求和
typedef double WeightSumSType;         // 边权求和
const WeightType WeightMax = DBL_MAX;  // 距离无穷大的值

typedef uint64_t IDType;
typedef std::vector<IDType> VIDType;
typedef std::vector<VIDType> VVIDType;
typedef std::string* PIDType;
typedef VIDType::iterator VIDTypeItr;
typedef VIDType::const_iterator VIDTypeCItr;
typedef VVIDType::iterator VVIDTypeItr;
typedef VVIDType::const_iterator VVIDTypeCItr;
typedef std::unordered_set<IDType> USIDType;
typedef std::set<IDType> SIDType;
typedef std::unordered_map<IDType, NodeType> UMIDType;
typedef std::map<IDType, NodeType> MIDType;

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

typedef int32_t Int;
typedef std::vector<Int> VInt;
typedef std::vector<VInt> VVInt;
typedef int* PInt;
typedef VInt::iterator VIntItr;
typedef VInt::const_iterator VIntCItr;
typedef VVInt::iterator VVIntItr;
typedef VVInt::const_iterator VVIntCItr;

typedef uint32_t Unsigned;
typedef std::vector<Unsigned> VUnsigned;
typedef std::vector<VUnsigned> VVUnsigned;
typedef unsigned* PUnsigned;
typedef VUnsigned::iterator VUnsignedItr;
typedef VUnsigned::const_iterator VUnsignedCItr;
typedef VVUnsigned::iterator VVUnsignedItr;
typedef VVUnsigned::const_iterator VVUnsignedCItr;

typedef int64_t Long;
typedef std::vector<Long> VLong;
typedef std::vector<VLong> VVLong;
typedef int* PLong;
typedef VLong::iterator VLongItr;
typedef VLong::const_iterator VLongCItr;
typedef VVLong::iterator VVLongItr;
typedef VVLong::const_iterator VVLongCItr;

typedef uint64_t ULong;
typedef std::vector<ULong> VULong;
typedef std::vector<VULong> VVULong;
typedef unsigned* PULong;
typedef VULong::iterator VULongItr;
typedef VULong::const_iterator VULongCItr;
typedef VVULong::iterator VVULongItr;
typedef VVULong::const_iterator VVULongCItr;

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

typedef struct common::Struct3<NodeType, NodeType, NodeType> Lkk3NodeType;
typedef Lkk3NodeType* PLkk3NodeType;
typedef std::vector<Lkk3NodeType> VLkk3NodeType;
typedef VLkk3NodeType::iterator VLkk3NodeTypeItr;
typedef VLkk3NodeType::const_iterator VLkk3NodeTypeCItr;

typedef struct common::Struct3<NodeType, NodeType, LinkType> Lkk3LinkType;
typedef Lkk3LinkType* PLkk3LinkType;
typedef std::vector<Lkk3LinkType> VLkk3LinkType;
typedef VLkk3LinkType::iterator VLkk3LinkTypeItr;
typedef VLkk3LinkType::const_iterator VLkk3LinkTypeCItr;

typedef struct common::Struct3<NodeType, NodeType, Double> Lkk3Double;
typedef Lkk3Double* PLkk3Double;
typedef std::vector<Lkk3Double> VLkk3Double;
typedef VLkk3Double::iterator VLkk3DoubleItr;
typedef VLkk3Double::const_iterator VLkk3DoubleCItr;

typedef struct common::Struct2<NodeType, LinkType> Lkk2LinkType;
typedef Lkk2LinkType* PLkk2LinkType2;
typedef std::vector<Lkk2LinkType> VLkk2LinkType;
typedef VLkk2LinkType::iterator VLkk2LinkTypeItr;
typedef VLkk2LinkType::const_iterator VLkk2LinkTypeCItr;
typedef std::vector<VLkk2LinkType> VVLkk2LinkType;
typedef VVLkk2LinkType::iterator VVLkk2LinkTypeItr;
typedef VVLkk2LinkType::const_iterator VVLkk2LinkTypeCItr;

typedef common::Range<NodeType> RNodeType;
typedef std::vector<RNodeType> VRNodeType;
typedef RNodeType* PRNodeType;
typedef VRNodeType::iterator VRNodeTypeItr;
typedef VRNodeType::const_iterator VRNodeTypeCItr;

typedef std::map<NodeType, NodeType> MNodeType;
typedef MNodeType::iterator MNodeTypeItr;
typedef MNodeType::const_iterator MNodeTypeCItr;
typedef std::vector<MNodeType> VMNodeType;

typedef std::unordered_map<NodeType, NodeType> UMNodeType;
typedef UMNodeType::iterator UMNodeTypeItr;
typedef UMNodeType::const_iterator UMNodeTypeCItr;
typedef std::vector<UMNodeType> VUMNodeType;

typedef std::set<NodeType> SNodeType;
typedef SNodeType::iterator SNodeTypeItr;
typedef SNodeType::const_iterator SNodeTypeCItr;
typedef std::vector<SNodeType> VSNodeType;

typedef std::unordered_set<NodeType> USNodeType;
typedef USNodeType::iterator USNodeTypeItr;
typedef USNodeType::const_iterator USNodeTypeCItr;
typedef std::vector<USNodeType> VUSNodeType;

int save_VRNodeType_start(std::ostream& os, const VRNodeType& v, const char c);
int save_VRNodeType_start(const char* name, const VRNodeType& v,
                          const char c = '\t');
int save_VRNodeType_end(std::ostream& os, const VRNodeType& v, const char c);
int save_VRNodeType_end(const char* name, const VRNodeType& v,
                        const char c = '\t');

bool cmp_RNodeType_start(const RNodeType& a, const RNodeType& b);
bool cmp_RNodeType_end(const RNodeType& a, const RNodeType& b);

// lkk var,save
enum Lkk_type {
  lkk_type_null = 0,
  lkk_lkk = 11,
  lkk_lkk3 = 13,
  lkk_lkk3reverse = 14,
  lkk2_lkk2 = 22,
  lkk2_lkk2compress = 25,
  lkk3_lkk = 31,
  lkk3_lkk3 = 33,
  lkk3_lkk3reverse = 34
};

const std::map<Lkk_type, std::string> kLkkTypeString = {
    {lkk_type_null, "NULL"},
    {lkk_lkk, "lkk_lkk"},
    {lkk_lkk3, "lkk_lkk3"},
    {lkk_lkk3reverse, "lkk_lkk3reverse"},
    {lkk2_lkk2, "lkk2_lkk2"},
    {lkk2_lkk2compress, "lkk2_lkk2compress"},
    {lkk3_lkk, "lkk3_lkk"},
    {lkk3_lkk3, "lkk3_lkk3"},
    {lkk3_lkk3reverse, "lkk3_lkk3reverse"}};

}  // end namespace network

// *******************************************************
std::istream& operator>>(std::istream& is, network::Lkk_type& lkk_type);
std::ostream& operator<<(std::ostream& os, const network::Lkk_type& lkk_type);

// *******************************************************
#endif
