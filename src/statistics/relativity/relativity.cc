#include "relativity.h"
#ifdef STAT_RELATIVITY

#include "../../common/common.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
int network::relativity::cal_relativity_lkk(double& relativity,
    const VVLinkType& lkk, const VNodeType& degArrVal,
    const LinkType& linkSize, const double alpha)
{
  const NodeType degSize = degArrVal.size();
  if (degSize <= 1) {
    relativity = 0;
    return 0;
  }
  double sx = 0., sxx = 0., sxy = 0.;
  for (NodeType i = 0; i < degSize; i++) {
    const double ki = pow(degArrVal[i], alpha), ki2 = ki * ki;
    for (NodeType j = 0; j <= i; j++) {
      const double l = lkk[i][j], kj = pow(degArrVal[j], alpha),
                   kj2 = kj * kj;
      if (l <= 0)
        continue;
      sx += l * (ki + kj);
      sxx += l * (ki2 + kj2);
      sxy += l * ki * kj;
    }
  }
  const LinkType n = linkSize * 2;
  if (n * sxx - sx * sx == 0)
    relativity = 0;
  else
    relativity = (2.0 * n * sxy - sx * sx) / (n * sxx - sx * sx);
  return 0;
}

int network::relativity::cal_relativity_lkk3(double& relativity,
    const VLkk3LinkType& lkk3, const VNodeType& degArrVal,
    const LinkType& linkSize, const double alpha)
{
  const NodeType degSize = degArrVal.size();
  if (degSize <= 1) {
    relativity = 0;
    return 0;
  }
  double sx = 0., sxx = 0., sxy = 0.;
  for (auto& li : lkk3) {
    if (li.val <= 0)
      continue;
    const NodeType i = li.x, j = li.y;
    const double l = li.val, ki = pow(degArrVal[i], alpha),
                 kj = pow(degArrVal[j], alpha), ki2 = ki * ki, kj2 = kj * kj;
    sx += l * (ki + kj);
    sxx += l * (ki2 + kj2);
    sxy += l * ki * kj;
  }
  const LinkType n = linkSize * 2;
  if (n * sxx == sx * sx)
    relativity = 0;
  else
    relativity = (2.0*n * sxy - sx * sx) / (n * sxx - sx * sx);
  return 0;
}

int network::relativity::cal_relativity_p2p(double& relativity,
    const VVNodeType& p2p, const LinkType linkSize, const double alpha)
{
  const LinkType n = linkSize * 2;
  double sx = 0., sxx = 0., sxy = 0.;
  for (NodeType i = 0, k; i < p2p.size(); i++) {
    if ((k = p2p[i].size()) <= 0)
      continue;
    const double x = pow(k, alpha), x2 = x * x;
    for (NodeType j = 0; j < k; j++) {
      sx += x;
      sxx += x2;
      sxy += x * pow(p2p[p2p[i][j]].size(), alpha);
    }
  }
  if (n * sxx - sx * sx == 0)
    relativity = 0;
  else
    relativity = (n * sxy - sx * sx) / (n * sxx - sx * sx);
  return 0;
}

int network::relativity::cal_relativity_link(double& relativity,
    const VNodeType& link, const VNodeType& nodeDeg, const double alpha)
{
  const LinkType n = link.size();
  double sx = 0., sxx = 0., sxy = 0.;
  for (LinkType i = 0; i < n; i += 2) {
    double x = pow(nodeDeg[link[i]], alpha),
           y = pow(nodeDeg[link[i + 1]], alpha);
    sx += x + y;
    sxx += x * x + y * y;
    sxy += x * y;
  }
  if (n * sxx - sx * sx == 0)
    relativity = 0;
  else
    relativity = (n * 2.0 * sxy - sx * sx) / (n * sxx - sx * sx);
  return 0;
}

// ******************************************************
#endif // STAT_PEARSON
