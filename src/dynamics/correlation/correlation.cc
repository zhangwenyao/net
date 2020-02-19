#include "correlation.h"
#ifdef ACT_CORRELATION

#include "../../common/common.h"
using namespace std;
using namespace common;
using namespace network;

// *******************************************************
int network::correlation::pearson(const VNodeType& v, double& p)
{
  const NodeType N = v.size();
  if (N < 2)
    return -1;
  double mx = (N - 1) / 2.0, sxy = 0, mx2 = (N - 1.0) * (2 * N - 1) / 6;
  for (NodeType i = 0; i < N; ++i) {
    double vi = v[i];
    sxy += vi * i;
  }
  sxy /= N;
  p = (sxy - mx * mx) / (mx2 - mx * mx);
  return 0;
}

// *******************************************************
#endif // ACT
