#include "spearman.h"
#ifdef STAT_SPEARMAN

#include "../../common/common.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
int network::spearman::cal_lkkProb_gauss_sum(double& sum, VDouble& deg2ArrVal,
    VNodeType& degArrVal, VNodeType& degArrSize, const double s2,
    const NodeType xi, const double r)
{
  const NodeType degSize = degArrVal.size();
  sum = 0.;
  if (degArrSize[xi] <= 0)
    return 0;
  double xi0 = deg2ArrVal[xi], temp = -0.5 / s2;
  if (r < 0)
    xi0 = 1 - xi0;
  degArrSize[xi]--;
  for (NodeType i = 0; i < degSize; i++) {
    double t = xi0 - deg2ArrVal[i];
    sum += exp(t * t * temp) * degArrVal[i] * degArrSize[i];
  }
  degArrSize[xi]++;
  return 0;
}

int network::spearman::cal_lkkProb_gaussS2(double& s2, VDouble& deg2ArrVal,
    VNodeType& degArrVal, VNodeType& degArrSize, const NodeType xi,
    const double r)
{
  const NodeType degSize = degArrVal.size();
  if (degArrSize[xi] <= 0)
    return 0;
  double ds, sum, sum2, xi0 = deg2ArrVal[xi], *pd, temp;
  const double exi = r * (xi0 - 0.5) + 0.5;
  if (r < 0)
    xi0 = 1 - xi0;
  ds = s2 = 0.01;
  degArrSize[xi]--;
  while (ds < 1.E9) {
    sum = sum2 = 0.;
    pd = &deg2ArrVal[0];
    temp = -0.5 / s2;
    for (NodeType i = 0, *ps = &degArrSize[0], *pk = &degArrVal[0];
         i < degSize; i++) {
      double t = xi0 - *pd;
      sum += t = exp(t * t * temp) * *ps++ * *pk++;
      sum2 += t * *pd++;
    }
    sum2 = sum2 / sum - exi;
    if ((exi <= 0.5 && sum2 >= 1.E-9) || (exi >= 0.5 && sum2 <= -1.E-9))
      break;
    ds *= 2;
    s2 += ds;
  }
  while (ds > 1.E-9) {
    ds /= 2;
    if ((exi <= 0.5 && sum2 >= 1.E-9) || (exi >= 0.5 && sum2 <= -1.E-9))
      s2 -= ds;
    else if ((exi <= 0.5 && sum2 <= -1.E-9) || (exi >= 0.5 && sum2 >= 1.E-9))
      s2 += ds;
    else
      break;
    sum = sum2 = 0.;
    pd = &deg2ArrVal[0];
    temp = -0.5 / s2;
    for (NodeType i = 0, *ps = &degArrSize[0], *pk = &degArrVal[0];
         i < degSize; i++) {
      double t = xi0 - *pd;
      sum += t = exp(t * t * temp) * *ps++ * *pk++;
      sum2 += t * *pd++;
    }
    sum2 = sum2 / sum - exi;
  }
  degArrSize[xi]++;
  return 0;
}

int network::spearman::cal_lkkProb_gauss(VVDouble& lkkProb, const VDouble& s2,
    const VDouble& deg2ArrVal, const double r)
{
  const NodeType degSize = deg2ArrVal.size();
  for (NodeType i = 0; i < degSize; i++) {
    double xi = deg2ArrVal[i], temp = -0.5 / s2[i];
    if (r < 0)
      xi = 1 - xi;
    for (NodeType j = 0; j < degSize; j++) {
      double t = xi - deg2ArrVal[j];
      lkkProb[i][j] = exp(t * t * temp);
    }
  }
  return 0;
}

int network::spearman::cal_lkkProb_expS2(double& s2, VDouble& deg2ArrVal,
    VNodeType& degArrVal, VNodeType& degArrSize, const LinkType linkSize,
    const NodeType xi, const double r)
{
  const NodeType degSize = degArrVal.size();
  s2 = 10.;
  if (degArrSize[xi] <= 0)
    return 0;
  double ds = s2, sum, sum2 = 0., xi0 = deg2ArrVal[xi], *pxj, t2;
  const double exi = r * (xi0 - 0.5) + 0.5;
  if (r < 0)
    xi0 = 1 - xi0;
  degArrSize[xi]--;
  while (ds < 1.E9) {
    sum = sum2 = 0.;
    pxj = &deg2ArrVal[0];
    t2 = 1. / (2. * linkSize);
    for (NodeType j = 0, *pj = &degArrVal[0], *psj = &degArrSize[0];
         j < degSize; j++) {
      double t = (xi0 - *pxj) * s2;
      if (t > 0)
        t = -t;
      sum += t = exp(t) * *pj++ * t2 * *psj++;
      sum2 += t * *pxj++;
    }
    sum2 = sum2 / sum - exi;
    if ((exi <= 0.5 && sum2 <= 1.E-9) || (exi >= 0.5 && sum2 >= -1.E-9))
      break;
    ds *= 2;
    s2 += ds;
  }
  if (ds >= 1.E9) {
    degArrSize[xi]++;
    ERROR();
    return -1;
  }
  while (ds > 1.E-9) {
    ds /= 2;
    if ((exi <= 0.5 && sum2 < -1.E-9) || (exi >= 0.5 && sum2 > 1.E-9))
      s2 -= ds;
    else if ((exi <= 0.5 && sum2 > 1.E-9) || (exi >= 0.5 && sum2 < -1.E-9))
      s2 += ds;
    else
      break;
    sum = sum2 = 0.;
    pxj = &deg2ArrVal[0];
    t2 = 1. / (2. * linkSize);
    for (NodeType j = 0, *pj = &degArrVal[0], *psj = &degArrSize[0];
         j < degSize; j++) {
      double t = (xi0 - *pxj) * s2;
      if (t > 0)
        t = -t;
      sum += t = exp(t) * *pj++ * t2 * *psj++;
      sum2 += t * *pxj++;
    }
    sum2 = sum2 / sum - exi;
  }
  degArrSize[xi]++;
  if (ds <= 1.E-9) {
    ERROR("ds[", xi, "]=", ds, "\tsum2-exi=", sum2);
    return -1;
  }
  return 0;
}

int network::spearman::cal_lkkProb_exp(VVDouble& lkkProb, const VDouble& s2,
    const VDouble& deg2ArrVal, const VNodeType& degArrVal, const double r)
{
  const NodeType degSize = degArrVal.size();
  for (NodeType i = 0; i < degSize; i++) {
    double xi = deg2ArrVal[i];
    const double* xj = &deg2ArrVal[0];
    if (r < 0)
      xi = 1 - xi;
    for (NodeType j = 0; j < degSize; j++) {
      double t = (xi - *xj++) * s2[i];
      if (t > 0)
        t = -t;
      lkkProb[i][j] = exp(t);
    }
  }
  return 0;
}

int network::spearman::cal_lkkProb_exp0S2(double& s2, VDouble& deg2ArrVal,
    VNodeType& degArrVal, VNodeType& degArrSize, const LinkType linkSize,
    const NodeType xi, const double r)
{
  const NodeType degSize = degArrVal.size();
  s2 = 10.;
  if (degArrSize[xi] <= 0)
    return 0;
  double ds = s2, sum, sum2 = 0., xi0 = deg2ArrVal[xi], *pxj, t2;
  const double exi = r * (xi0 - 0.5) + 0.5;
  if (r < 0)
    xi0 = 1 - xi0;
  degArrSize[xi]--;
  while (ds < 1.E9) {
    sum = sum2 = 0.;
    pxj = &deg2ArrVal[0];
    t2 = -1. / (2. * linkSize);
    for (NodeType j = 0, *pj = &degArrVal[0], *psj = &degArrSize[0];
         j < degSize; j++) {
      double t = (xi0 - *pxj) * s2;
      if (t > 0)
        t = -t;
      sum += t = (1. - exp(exp(t) * *pj++ * t2)) * *psj++;
      sum2 += t * *pxj++;
    }
    sum2 = sum2 / sum - exi;
    if ((exi <= 0.5 && sum2 <= 1.E-9) || (exi >= 0.5 && sum2 >= -1.E-9))
      break;
    ds *= 2;
    s2 += ds;
  }
  if (ds >= 1.E9) {
    degArrSize[xi]++;
    ERROR("ds >= 1.E9");
    return -1;
  }
  while (ds > 1.E-9) {
    ds /= 2;
    if ((exi <= 0.5 && sum2 < -1.E-9) || (exi >= 0.5 && sum2 > 1.E-9))
      s2 -= ds;
    else if ((exi <= 0.5 && sum2 > 1.E-9) || (exi >= 0.5 && sum2 < -1.E-9))
      s2 += ds;
    else
      break;
    sum = sum2 = 0.;
    pxj = &deg2ArrVal[0];
    t2 = -1. / (2. * linkSize);
    for (NodeType j = 0, *pj = &degArrVal[0], *psj = &degArrSize[0];
         j < degSize; j++) {
      double t = (xi0 - *pxj) * s2;
      if (t > 0)
        t = -t;
      sum += t = (1. - exp(exp(t) * *pj++ * t2)) * *psj++;
      sum2 += t * *pxj++;
    }
    sum2 = sum2 / sum - exi;
  }
  degArrSize[xi]++;
  if (ds <= 1.E-9) {
    ERROR("\tds <= 1.E-9");
    return -1;
  }
  return 0;
}

int network::spearman::cal_lkkProb_exp0(VVDouble& lkkProb, const VDouble& s2,
    const VDouble& deg2ArrVal, const VNodeType& degArrVal, const double r)
{
  const NodeType degSize = degArrVal.size();
  for (NodeType i = 0; i < degSize; i++) {
    double xi = deg2ArrVal[i];
    const double* xj = &deg2ArrVal[0];
    if (r < 0)
      xi = 1 - xi;
    for (NodeType j = 0; j < degSize; j++) {
      double t = (xi - *xj++) * s2[i];
      if (t > 0)
        t = -t;
      lkkProb[i][j] = exp(t);
    }
  }
  return 0;
}

int network::spearman::cal_nodeNeiAveDeg2(VDouble& nodeNeiAveDeg2,
    const VVNodeType& p2p, const VDouble& deg2ArrVal, MNodeType& degArrNo)
{
  const NodeType nodeSize = p2p.size();
  nodeNeiAveDeg2.assign(nodeSize, 0);
  for (NodeType i = 0; i < nodeSize; i++) {
    if (p2p[i].size() <= 0)
      continue;
    for (VNodeTypeCItr n = p2p[i].begin(); n != p2p[i].end(); n++)
      nodeNeiAveDeg2[i] += deg2ArrVal[degArrNo[p2p[*n].size()]];
    nodeNeiAveDeg2[i] /= p2p[i].size();
  }
  return 0;
}

int network::spearman::cal_nodeNeiAveDeg2_nodeDeg(VDouble& nodeNeiAveDeg2,
    const VVNodeType& p2p, const VNodeType& nodeDeg,
    const VDouble& deg2ArrVal, MNodeType& degArrNo)
{
  const NodeType nodeSize = p2p.size();
  nodeNeiAveDeg2.assign(nodeSize, 0);
  for (NodeType i = 0; i < nodeSize; i++) {
    if (p2p[i].size() <= 0)
      continue;
    for (VNodeTypeCItr n = p2p[i].begin(); n != p2p[i].end(); n++)
      nodeNeiAveDeg2[i] += deg2ArrVal[degArrNo[nodeDeg[*n]]];
    nodeNeiAveDeg2[i] /= p2p[i].size();
  }
  return 0;
}

int network::spearman::cal_nodeNeiAveDeg2_weight(VDouble& nodeNeiAveDeg2,
    const VVNodeType& p2p, const VNodeType& nodeDegIn,
    const VDouble& deg2ArrValIn, MNodeType& degArrNoIn,
    const VVWeightType& vvweight, const VWeightType& nodeWeightOut,
    const int weightFlag)
{
  if (!weightFlag)
    return cal_nodeNeiAveDeg2_nodeDeg(
        nodeNeiAveDeg2, p2p, nodeDegIn, deg2ArrValIn, degArrNoIn);
  if (p2p.empty() || !nodeNeiAveDeg2.empty()
      || vvweight.size() != p2p.size()) {
    ERROR();
    return -1;
  }
  const NodeType nodeSize = p2p.size();
  nodeNeiAveDeg2.assign(nodeSize, 0);
  for (NodeType i = 0; i < nodeSize; i++) {
    if (p2p[i].size() <= 0)
      continue;
    double l = 0;
    for (NodeType j = 0; j < p2p[i].size(); j++)
      l += (double)vvweight[i][j]
          * deg2ArrValIn[degArrNoIn[nodeDegIn[p2p[i][j]]]];
    nodeNeiAveDeg2[i] = l / nodeWeightOut[i];
  }
  return 0;
}

int network::spearman::cal_nodeNeiAveDeg2_AllAll(VDouble& nodeNeiAveDeg2,
    const VVNodeType& p2p, const VNodeType& nodeDeg,
    const VDouble& deg2ArrVal, MNodeType& degArrNo,
    const VVWeightType& vvweight, const VWeightType& nodeWeight,
    const int weightFlag)
{
  if (!weightFlag)
    return cal_nodeNeiAveDeg2_nodeDeg(
        nodeNeiAveDeg2, p2p, nodeDeg, deg2ArrVal, degArrNo);
  if (p2p.empty() || !nodeNeiAveDeg2.empty()
      || vvweight.size() != p2p.size()) {
    ERROR();
    return -1;
  }
  const NodeType nodeSize = p2p.size();
  nodeNeiAveDeg2.assign(nodeSize, 0);
  for (NodeType i = 0; i < nodeSize; i++) {
    if (p2p[i].size() <= 0)
      continue;
    for (NodeType j = 0; j < p2p[i].size(); j++) {
      nodeNeiAveDeg2[i] += (double)vvweight[i][j]
          * deg2ArrVal[degArrNo[nodeDeg[p2p[i][j]]]];
      nodeNeiAveDeg2[p2p[i][j]]
          += (double)vvweight[i][j] * deg2ArrVal[degArrNo[nodeDeg[i]]];
    }
  }
  for (NodeType i = 0; i < nodeSize; i++)
    if (nodeDeg[i] > 0)
      nodeNeiAveDeg2[i] /= nodeWeight[i];
  return 0;
}

int network::spearman::cal_neiAveDeg2(VDouble& neiAveDeg2,
    const VDouble& nodeNeiAveDeg2, const VNodeType& nodeDeg,
    const VNodeType& degArrSize, MNodeType& degArrNo,
    const VNodeType& degArrVal)
{
  const NodeType nodeSize = nodeDeg.size(), degSize = degArrSize.size();
  neiAveDeg2.assign(degSize, 0);
  for (NodeType i = 0; i < nodeSize; i++)
    neiAveDeg2[degArrNo[nodeDeg[i]]] += nodeNeiAveDeg2[i];
  for (NodeType i = 0; i < degSize; i++)
    if (degArrSize[i] > 0 && degArrVal[i] > 0)
      neiAveDeg2[i] /= degArrSize[i];
  return 0;
}

int network::spearman::cal_neiAveDeg2_weight(VDouble& neiAveDeg2,
    const VDouble& nodeNeiAveDeg2, const VNodeType& nodeDeg,
    const VNodeType& degArrSize, MNodeType& degArrNo,
    const VNodeType& degArrVal, const VWeightSumType& degArrWeight,
    const VWeightType& nodeWeightOut, const int weightFlag)
{
  if (!weightFlag)
    return cal_neiAveDeg2(
        neiAveDeg2, nodeNeiAveDeg2, nodeDeg, degArrSize, degArrNo, degArrVal);
  const NodeType nodeSize = nodeDeg.size(), degSize = degArrSize.size();
  neiAveDeg2.assign(degSize, 0);
  for (NodeType i = 0; i < nodeSize; i++)
    neiAveDeg2[degArrNo[nodeDeg[i]]] += nodeNeiAveDeg2[i] * nodeWeightOut[i];
  for (NodeType i = 0; i < degSize; i++)
    if (degArrSize[i] > 0 && degArrVal[i] > 0)
      neiAveDeg2[i] /= degArrWeight[i];
  return 0;
}

int network::spearman::cal_spearman_lkk(double& spearman,
    const VVLinkType& lkk, const VDouble& deg2ArrVal, const LinkType linkSize)
{
  const NodeType degSize = lkk.size();
  if (degSize <= 0) {
    spearman = 0;
    return 0;
  }
  if (degSize == 1) {
    spearman = 1;
    return 0;
  }
  double sx = 0., sxx = 0., sxy = 0.;
  for (NodeType i = 0; i < degSize; i++) {
    const double xi = deg2ArrVal[i], xi2 = xi * xi;
    for (NodeType j = 0; j <= i; j++) {
      const double xj = deg2ArrVal[j], l = lkk[i][j];
      sx += l * (xi + xj);
      sxx += l * (xi2 + xj * xj);
      sxy += 2 * l * xi * xj;
    }
  }
  const LinkType n = linkSize * 2;
  if (n * sxx - sx * sx == 0)
    spearman = 0;
  else
    spearman = (n * sxy - sx * sx) / (n * sxx - sx * sx);
  return 0;
}

int network::spearman::cal_spearman(double& spearman, const VVNodeType& p2p,
    const VDouble& deg2ArrVal, MNodeType& degArrNo, const LinkType linkSize)
{
  if (deg2ArrVal.size() <= 1) {
    spearman = 0;
    return 0;
  }
  const LinkType n = linkSize * 2;
  double sx = 0., sxx = 0., sxy = 0.;
  for (NodeType i = 0, k, nodeSize = p2p.size(); i < nodeSize; i++) {
    if ((k = p2p[i].size()) <= 0)
      continue;
    double d = deg2ArrVal[degArrNo[k]];
    sx += d * k;
    sxx += d * d * k;
    for (NodeType j = 0; j < k; j++) {
      sxy += d * deg2ArrVal[degArrNo[p2p[p2p[i][j]].size()]];
    }
  }
  if (n * sxx - sx * sx == 0)
    spearman = 0;
  else
    spearman = (n * sxy - sx * sx) / (n * sxx - sx * sx);
  return 0;
}

int network::spearman::cal_spearman_dir(double& spearman, double& rho,
    const VVNodeType& p2p, const double linkSize, const VNodeType& nodeDeg1,
    MNodeType& degArrNo1, const VDouble& deg2ArrVal1,
    const VNodeType& nodeDeg2, MNodeType& degArrNo2,
    const VDouble& deg2ArrVal2)
{
  if (deg2ArrVal1.size() <= 1 || deg2ArrVal2.size() <= 1) {
    spearman = rho = 0;
    return 0;
  }
  double sx = 0., sxx = 0., sy = 0., syy = 0., sxy = 0.;
  for (NodeType i = 0; i < p2p.size(); i++) {
    const NodeType s = p2p[i].size();
    if (s <= 0)
      continue;
    const double ki = deg2ArrVal1[degArrNo1[nodeDeg1[i]]];
    for (NodeType j = 0; j < s; j++) {
      const double kj = deg2ArrVal2[degArrNo2[nodeDeg2[p2p[i][j]]]];
      sx += ki;
      sxx += ki * ki;
      sy += kj;
      syy += kj * kj;
      sxy += (double)ki * kj;
    }
  }
  if (linkSize * sxx - sx * sx == 0) {
    spearman = rho = 0;
  } else {
    if (linkSize * syy - sy * sy == 0)
      spearman = 0;
    else
      spearman = (linkSize * sxy - sx * sy)
          / sqrt((linkSize * sxx - sx * sx) * (linkSize * syy - sy * sy));
    rho = (linkSize * sxy - sx * sy) / (linkSize * sxx - sx * sx);
  }
  return 0;
}

int network::spearman::cal_spearman_dir_weight(double& spearman, double& rho,
    const VVNodeType& p2p, const VVWeightType& vvweight,
    const double netWeight, const VNodeType& nodeDeg1, MNodeType& degArrNo1,
    const VDouble& deg2ArrVal1, const VNodeType& nodeDeg2,
    MNodeType& degArrNo2, const VDouble& deg2ArrVal2, const int weightFlag)
{
  if (deg2ArrVal1.size() <= 1 || deg2ArrVal2.size() <= 1) {
    spearman = rho = 0;
    return 0;
  }
  if (!weightFlag)
    return cal_spearman_dir(spearman, rho, p2p, netWeight, nodeDeg1,
        degArrNo1, deg2ArrVal1, nodeDeg2, degArrNo2, deg2ArrVal2);
  double sx = 0., sxx = 0., sy = 0., syy = 0., sxy = 0.;
  for (NodeType i = 0; i < p2p.size(); i++) {
    const NodeType s = p2p[i].size();
    if (s <= 0)
      continue;
    const double ki = deg2ArrVal1[degArrNo1[nodeDeg1[i]]];
    for (NodeType j = 0; j < s; j++) {
      const double kj = deg2ArrVal2[degArrNo2[nodeDeg2[p2p[i][j]]]],
                   w = vvweight[i][j];
      sx += w * ki;
      sxx += w * ki * ki;
      sy += w * kj;
      syy += w * kj * kj;
      sxy += w * ki * kj;
    }
  }
  if (netWeight * sxx - sx * sx == 0) {
    spearman = rho = 0;
  } else {
    if (netWeight * syy - sy * sy == 0)
      spearman = 0;
    else
      spearman = (netWeight * sxy - sx * sy)
          / sqrt((netWeight * sxx - sx * sx) * (netWeight * syy - sy * sy));
    rho = (netWeight * sxy - sx * sy) / (netWeight * sxx - sx * sx);
  }
  return 0;
}

int network::spearman::cal_spearman_link(double& spearman, VNodeType& link,
    const VNodeType& nodeDeg, VDouble& deg2ArrVal, MNodeType& degArrNo)
{
  if (deg2ArrVal.size() <= 1) {
    spearman = 0;
    return 0;
  }
  const LinkType linkSize = link.size(), n = linkSize * 2;
  double sx = 0., sxx = 0., sxy = 0.;
  for (LinkType i = 0; i < linkSize; i++) {
    double x = deg2ArrVal[degArrNo[nodeDeg[link[i * 2]]]],
           y = deg2ArrVal[degArrNo[nodeDeg[link[i * 2 + 1]]]];
    sx += x + y;
    sxx += x * x + y * y;
    sxy += x * y;
  }
  if (n * sxx - sx * sx == 0)
    spearman = 0;
  else
    spearman = (n * 2. * sxy - sx * sx) / (n * sxx - sx * sx);
  return 0;
}

// ******************************************************
#endif // STAT_SPEARMAN
