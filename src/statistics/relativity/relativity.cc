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
    relativity = (2.0 * n * sxy - sx * sx) / (n * sxx - sx * sx);
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
int network::relativity::alphas_sum(const char* prename, const char* sufname,
    const int seed_min, const int seed_max, VDouble& sx, VDouble& sx2,
    size_t& n)
{
  string s, fn0 = prename, fn_full;
  VVDouble dbs, results;
  const size_t alphas_size = sx.size();
  for (int seed = seed_min; seed <= seed_max; ++seed) {
    fn_full = fn0 + to_string(seed) + sufname;
    dbs.clear();
    _ERR(0 != common::read2_0(fn_full.c_str(), dbs) || dbs.size() != 3);
    for (int i = 0; i < 3; ++i)
      _ERR(dbs[i].size() != alphas_size);
    for (size_t i = 0; i < alphas_size; ++i) {
      const double x1 = dbs[0][i] - dbs[1][i] * dbs[1][i],
                   x2 = dbs[2][i] - dbs[1][i] * dbs[1][i],
                   x = x2 == 0 ? 0 : x1 / x2;
      sx[i] += x;
      sx2[i] += x * x;
    }
    ++n;
  }
  return EXIT_SUCCESS;
}
// ******************************************************
#endif // STAT_PEARSON
