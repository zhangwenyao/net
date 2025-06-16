#ifndef STATISTICS__INDEXES__INDEXES_H_
#define STATISTICS__INDEXES__INDEXES_H_
#include "../../network/net.h"
#ifdef STAT_INDEXES

namespace network {
namespace indexes {
// ******************************************************
int cal_local_index1(VLinkType &local_index1, VNodeType &neibor_communities,
                     const VVNodeType &p2p);
int cal_local_index2(VLinkType &local_index2, VNodeType &neibor2_numbers,
                     VNodeType &neibor2_communities, const VVNodeType &p2p);
}  // namespace indexes
}  // namespace network

// ******************************************************
#endif  // STAT_INDEXES
#endif  // STAT_INDEXES_H
