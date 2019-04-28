#include "network.h"
#ifdef STAT_SIMILARITY

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;
using namespace network;

// ******************************************************
int network::similarity::cal_similarity(VVDouble &simiNodeCoef, VVDouble &simiEdgeCoef,
                   const VNodeType &link1, const VNodeType &link2,
                   const int dirFlag) {
  double x2Sum0 = 0.5, x2Sum = 1, y2Sum0 = 0.5, y2Sum = 1, delta = 1.0e-14;
  const NodeType n1 = simiNodeCoef.size(), n2 = simiNodeCoef[0].size();
  const LinkType l1 = link1.size() / 2, l2 = link2.size() / 2;
  VVDouble x, y;
  x.resize(n1);
  for (NodeType i = 0; i < n1; ++i) x[i].assign(n2, 1);
  simiNodeCoef = x;
  y.resize(l1);
  for (NodeType i = 0; i < l1; ++i) y[i].assign(l2, 1);
  simiEdgeCoef = y;
  for (const double d1 = 1 - delta, d2 = 1 + delta;
       x2Sum0 > 0 && y2Sum0 > 0 &&
       (d1 * x2Sum0 > x2Sum || x2Sum > d2 * x2Sum0 || d1 * y2Sum0 > y2Sum ||
        y2Sum > d2 * y2Sum0);) {
    x2Sum0 = x2Sum;
    y2Sum0 = y2Sum;
    cal_similarity_update(simiNodeCoef, simiEdgeCoef, link1, link2, x, x2Sum, y,
                          y2Sum, dirFlag);
  }
  return 0;
}

int network::similarity::cal_similarity_update(VVDouble &simiNodeCoef, VVDouble &simiEdgeCoef,
                          const VNodeType &link1, const VNodeType &link2,
                          VVDouble &x, double &x2Sum, VVDouble &y,
                          double &y2Sum, const int dirFlag) {
  const NodeType n1 = simiNodeCoef.size(), n2 = simiNodeCoef[0].size();
  const LinkType l1 = link1.size() / 2, l2 = link2.size() / 2;
  // double xSum = 0, ySum = 0;
  x2Sum = y2Sum = 0;
  for (NodeType i = 0; i < n1; ++i)
    for (NodeType j = 0; j < n2; ++j) x[i][j] = 0;
  if (dirFlag) {
    for (NodeType p = 0; p < l1; ++p) {
      const NodeType ps = link1[p * 2], pt = link1[p * 2 + 1];
      for (NodeType q = 0; q < l2; ++q) {
        const NodeType qs = link2[q * 2], qt = link2[q * 2 + 1];
        x[ps][qs] += simiEdgeCoef[p][q];
        x[pt][qt] += simiEdgeCoef[p][q];
        y[p][q] = simiNodeCoef[ps][qs] + simiNodeCoef[pt][qt];
        // ySum += y[p][q];
        y2Sum += y[p][q] * y[p][q];
      }
    }
  } else {
    for (NodeType p = 0; p < l1; ++p) {
      const NodeType ps = link1[p * 2], pt = link1[p * 2 + 1];
      for (NodeType q = 0; q < l2; ++q) {
        const NodeType qs = link2[q * 2], qt = link2[q * 2 + 1];
        const double x0 = simiEdgeCoef[p][q];
        x[ps][qs] += x0;
        x[ps][qt] += x0;
        x[pt][qs] += x0;
        x[pt][qt] += x0;
        y[p][q] = simiNodeCoef[ps][qs] + simiNodeCoef[pt][qt] +
                  simiNodeCoef[ps][qt] + simiNodeCoef[pt][qs];
        // ySum += y[p][q];
        y2Sum += y[p][q] * y[p][q];
      }
    }
  }

  if (y2Sum > 0) {
    const double t = sqrt(1. / y2Sum);
    for (NodeType p = 0; p < l1; ++p)
      for (NodeType q = 0; q < l2; ++q)
        simiEdgeCoef[p][q] = y[p][q] > 0 ? y[p][q] * t : 0;
  } else {
    simiEdgeCoef = y;
  }

  for (NodeType i = 0; i < n1; ++i)
    for (NodeType j = 0; j < n2; ++j) {
      // xSum += x[i][j];
      x2Sum += x[i][j] * x[i][j];
    }
  if (x2Sum > 0) {
    const double t = sqrt(1. / x2Sum);
    for (NodeType i = 0; i < n1; ++i)
      for (NodeType j = 0; j < n2; ++j)
        simiNodeCoef[i][j] = x[i][j] > 0 ? x[i][j] * t : 0;
  } else {
    simiNodeCoef = x;
  }

  return 0;
}
// ******************************************************
#endif  // STAT_SIMILARITY
