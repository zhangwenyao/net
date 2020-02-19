#ifndef DYNAMICS__CORRELATION__CORRELATION_H_
#define DYNAMICS__CORRELATION__CORRELATION_H_
#include "../../network/net.h"
#ifdef ACT_CORRELATION

namespace network {
namespace correlation {
  // *******************************************************
  template <typename T> int rewire(std::vector<T>& v, size_t L, const double p);
  int pearson(const VNodeType& v,double &p);
}
}
// *******************************************************
#include "correlation_template.h"
#endif // ACT
#endif // _H
