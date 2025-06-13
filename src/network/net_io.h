#ifndef NETWORK__NET_IO_H_
#define NETWORK__NET_IO_H_

#include "type.h"

namespace network {
// *******************************************************
template <typename LinknameType = std::string>
int read_link_name(std::map<LinknameType, NodeType>& mp, const char* name);
template <typename LinknameType = std::string>
int read_link_name_weight(std::map<LinknameType, NodeType>& mp,
                          const char* name);
template <typename LinknameType = std::string>
int linkname_2_link0(const char* linkfile0, const char* linkfile,
                     const char* namefile);
template <typename LinknameType = std::string>
int linkname_2_link(const char* link_name, const char* namefile0,
                    const char* linkfile0, const char* namefile,
                    const char* linkfile, const bool is_weight = false);
// *******************************************************
int read0_link(VNodeType& link, const char* name, const unsigned n);
int save_link(std::ostream& os, const VNodeType& link);
int save_link(const char* name, const VNodeType& link);
int read_link(VNodeType& link, const char* name);
int read_link_unique(VNodeType& link, const char* name,
                     const bool is_dircted = false);
int read_weight_link(VVWeightType& vvweight, VVWeightType& vvweightIn,
                     const LinkType linkSize, const char* name,
                     const unsigned weight_m = 2, const unsigned weight_n = 3,
                     const int dirFlag = 0);
int read_link_weight_0(VNodeType& link, LinkType& linkSize,
                       VVWeightType& vvweight, VVWeightType& vvweightIn,
                       const char* name, const unsigned weight_m = 2,
                       const unsigned weight_n = 3, const int dirFlag = 0);

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

int read_lkk2compress(std::istream& is, VVLkk2LinkType& lkk2);
int read_lkk2compress(const char* name, VVLkk2LinkType& lkk2);
int save_lkk2compress(std::ostream& os, const VVLkk2LinkType& lkk2,
                      const char pri2 = '\t', const char pri = '\n');
int save_lkk2compress(const char* name, const VVLkk2LinkType& lkk2,
                      const char pri2 = '\t', const char pri = '\n');

int read_lkk3(std::istream& is, VLkk3LinkType& lkk3);
int read_lkk3(const char* name, VLkk3LinkType& lkk3);
int save_lkk3(std::ostream& os, const VLkk3LinkType& lkk3,
              const char pri2 = '\t', const char pri = '\n');
int save_lkk3(const char* name, const VLkk3LinkType& lkk3,
              const char pri2 = '\t', const char pri = '\n');
int save_lkk3reverse(const char* filename, const VLkk3LinkType& lkk3,
                     const NodeType max_index, const char priChar2,
                     const char priChar);
int read_lkk3reverse(const char* filename, const NodeType max_index,
                     VLkk3LinkType& lkk3);

// *******************************************************
}  // end namespace network
#include "net_io_template.h"
#endif  // NET_H
