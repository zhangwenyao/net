#ifndef STATISTICS__CORRELATION2__CORRELATION2_H_
#define STATISTICS__CORRELATION2__CORRELATION2_H_
#include "../../network/net.h"
#ifdef STAT_CORRELATION2

namespace network {
namespace correlation2 {
  // ******************************************************
  int cal_correlation2(double& correlation2, const VVNodeType& p2p);
}
}

// ******************************************************
#endif // STAT_CORRELATION2
#endif // STAT_CORRELATION2_H
