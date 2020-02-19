#ifndef NETWORK__NET_IO_H_
#define NETWORK__NET_IO_H_

#include "type.h"

namespace network {
// *******************************************************
int read0_link(VNodeType& link, const char* name, const unsigned n);
int read_link(VNodeType& link, const char* name);
int read_weight_link(VVWeightType& vvweight, VVWeightType& vvweightIn,
    const LinkType linkSize, const char* name, const unsigned weight_m = 2,
    const unsigned weight_n = 3, const int dirFlag = 0);
int read_link_weight_0(VNodeType& link, LinkType& linkSize,
    VVWeightType& vvweight, VVWeightType& vvweightIn, const char* name,
    const unsigned weight_m = 2, const unsigned weight_n = 3,
    const int dirFlag = 0);

// *******************************************************
int read_lkk_3(std::istream& is, VVLinkType& lkk, const NodeType degSize = 0,
    const int rv = 0);
int read_lkk_3(const char* name, VVLinkType& lkk, const NodeType degSize = 0,
    const int rv = 0);
int save_lkk_3(std::ostream& os, const VVLinkType& lkk, const int rv = 0,
    const char pri2 = '\t', const char pri = '\n');
int save_lkk_3(const char* name, const VVLinkType& lkk, const int rv = 0,
    const char pri2 = '\t', const char pri = '\n');

int read_lkk2(std::istream& is, VVLkk2LinkType& lkk2);
int read_lkk2(const char* name, VVLkk2LinkType& lkk2);
int save_lkk2(std::ostream& os, const VVLkk2LinkType& lkk2,
    const char pri2 = '\t', const char pri = '\n');
int save_lkk2(const char* name, const VVLkk2LinkType& lkk2,
    const char pri2 = '\t', const char pri = '\n');

int read_lkk3(std::istream& is, VLkk3LinkType& lkk3);
int read_lkk3(const char* name, VLkk3LinkType& lkk3);
int save_lkk3(std::ostream& os, const VLkk3LinkType& lkk3,
    const char pri2 = '\t', const char pri = '\n');
int save_lkk3(const char* name, const VLkk3LinkType& lkk3,
    const char pri2 = '\t', const char pri = '\n');
int save_lkk3reverse(const char* filename, const VLkk3LinkType& lkk3,
    const NodeType max_index, const char priChar2, const char priChar);
int read_lkk3reverse(
    const char* filename, const NodeType max_index, VLkk3LinkType& lkk3);

// *******************************************************
} // end namespace network
#endif // NET_H
