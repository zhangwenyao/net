#ifndef DYNAMICS__CORRELATION__CORRELATION_TEMPLATE_H_
#define DYNAMICS__CORRELATION__CORRELATION_TEMPLATE_H_
#include "correlation.h"
#ifdef ACT_CORRELATION

#include "../../common/common.h"
#include <algorithm>

// *******************************************************
template <typename T>
int network::correlation::rewire(std::vector<T>& v, size_t L, const double p)
{
  const size_t N = v.size();
  _ERR(N < 2);
  std::uniform_int_distribution<network::NodeType> ra(0, N - 1),
      ra2(0, N - 2);
  for (; L > 0; --L) {
    network::NodeType i = ra(common::rand2), j = ra2(common::rand2);
    if (j >= i)
      ++j;
    else
      std::swap(i, j);
    T &vi = v[i], &vj = v[j];
    if ((vi < vj) ^ (common::rand_double() <= p))
      std::swap(vi, vj);
  }
  return 0;
}

// ********************************************************
#endif // ACT
#endif // _H
