#include "ActRecommend.h"
#ifdef ACT_RECOMMEND

#include "common.h"
using namespace std;

//**//*****************************************************//*
int act_recommend_readP2p(VVNodeType& pu, VVNodeType& po, std::istream& is)
{
  if (!is) {
    ERROR();
    return -1;
  }
  common_read2(is, pu);
  p2p_2_p2pIn(po, pu);
  return 0;
}

//**//*****************************************************//*
int act_recommend_mass_sum(const VNodeType& p2p, const double t, VDouble& v)
{
  for (VNodeTypeCItr p = p2p.begin(); p != p2p.end(); p++)
    v[*p] += t;
  return 0;
}

int act_recommend_mass_1(VDouble& o2, const VVNodeType& uP2p,
    const VVNodeType& oP2p, const NodeType i)
{
  const NodeType NU = uP2p.size(), NO = oP2p.size();
  VDouble u2(NU, 0);
  o2.assign(NO, 0);
  u2 = o2;

  // o -> u2
  for (VNodeTypeCItr pj = uP2p[i].begin(); pj != uP2p[i].end(); pj++) {
    NodeType j = *pj;
    if (oP2p[j].size() <= 0)
      continue;
    const double t = 1.0 / oP2p[j].size();
    act_recommend_mass_sum(oP2p[j], t, u2);
  }

  // u2 -> o2
  for (NodeType i2 = 0; i2 < NU; i2++) {
    if (uP2p[i2].size() <= 0 || u2[i2] <= 0)
      continue;
    const double t2 = u2[i2] / uP2p[i2].size();
    act_recommend_mass_sum(uP2p[i2], t2, o2);
  }

  return 0;
}

int act_recommend_mass(
    VVDouble& rcm, const VVNodeType& uP2p, const VVNodeType& oP2p)
{
  const NodeType NU = uP2p.size();
  rcm.resize(NU);
  for (NodeType i = 0; i < NU; i++) {
    act_recommend_mass_1(rcm[i], uP2p, oP2p, i);
  }
  return 0;
}

//**//*****************************************************//*
int act_recommend_heat_sum(
    const VNodeType& p2p1, const VVNodeType& p2p2, const double t, VDouble& v)
{
  for (VNodeTypeCItr p = p2p1.begin(); p != p2p1.end(); p++) {
    const NodeType i = *p, s = p2p2[i].size();
    if (s > 0)
      v[i] += t / s;
  }
  return 0;
}

int act_recommend_heat_1(VDouble& o2, const VVNodeType& uP2p,
    const VVNodeType& oP2p, const NodeType i)
{
  const NodeType NU = uP2p.size(), NO = oP2p.size();
  o2.assign(NO, 0);
  VDouble u2(NU, 0);

  // o -> u2
  for (VNodeTypeCItr pj = uP2p[i].begin(); pj != uP2p[i].end(); pj++) {
    NodeType j = *pj;
    if (oP2p[j].size() <= 0)
      continue;
    act_recommend_heat_sum(oP2p[j], uP2p, 1.0, u2);
  }

  // u2 -> o2
  for (NodeType i2 = 0; i2 < NU; i2++) {
    if (uP2p[i2].size() <= 0 || u2[i2] <= 0)
      continue;
    act_recommend_heat_sum(uP2p[i2], uP2p, u2[i2], o2);
  }

  return 0;
}

int act_recommend_heat(
    VVDouble& rcm, const VVNodeType& uP2p, const VVNodeType& oP2p)
{
  const NodeType NU = uP2p.size();
  rcm.resize(NU);
  for (NodeType i = 0; i < NU; i++)
    act_recommend_heat_1(rcm[i], uP2p, oP2p, i);
  return 0;
}

//**//*****************************************************//*
int act_recommend_pagerank(const VVNodeType& p2p, VDouble& v)
{
  const NodeType N = p2p.size();
  v.assign(N, 1);
  if (N <= 1)
    return 0;

  VVNodeType p2p2;
  const VVNodeType* p;
  int flag = 0;
  for (NodeType i = 0; i < N; i++) {
    if (p2p[i].size() > N) {
      ERROR();
      return -1;
    }
    if (p2p.size() <= 0) {
      flag = 1;
      break;
    }
  }
  if (flag) {
    p2p2 = p2p;
    for (NodeType i = 0; i < N; i++) {
      if (p2p2.size() <= 0) {
        for (NodeType j = 0; j < N; j++)
          p2p2[i].push_back(j);
      }
    }
    p = &p2p2;
  } else
    p = &p2p;

  VDouble v2;
  for (double e = 0, e2 = 1, s2 = N, t;
       s2 > 1e-6 && e2 * N <= e * e * (1 + 1e-4);) {
    e = 0;
    e2 = 0;
    s2 = 0;
    v2.assign(N, 0);
    // common_matrixCross1_p2p(p2p, v, v2);
    for (size_t i = 0; i < N; i++) {
      s2 += v[i] * v[i];
      t = v2[i] / v[i];
      e += t;
      e2 += t * t;
    }
    swap(v, v2);
  }

  return 0;
}

int act_recommend_pagerank(ofstream& os, const VVNodeType& p2p, VDouble& v)
{
  if (!os) {
    ERROR();
    return -1;
  }

  int flag = act_recommend_pagerank(p2p, v);
  if (flag != 0) {
    ERROR(flag);
    return flag;
  }

  os << v;
  return 0;
}

int act_recommend_pagerank(const char* name, const VVNodeType& p2p, VDouble& v)
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  int flag = act_recommend_pagerank(os, p2p, v);
  os.close();
  return flag;
}

//**//*****************************************************//*
int act_recommend_commonNeighbour(const VVNodeType& p2p, VDouble& v)
{
  return 0;
}

//**//*****************************************************//*
int recommend_MAE(const VDouble& v0, const VDouble& v, double& r)
{
  r = 0;
  if (v.size() != v0.size()) {
    ERROR();
    return -1;
  }
  if (v.size() <= 0)
    return 0;
  for (NodeType i = 0; i < v.size(); i++)
    r += abs(v[i] - v0[i]);
  r /= v.size();
  return 0;
}

int recommend_RMAE(const VDouble& v0, const VDouble& v, double& r)
{
  r = 0;
  if (v.size() != v0.size()) {
    ERROR();
    return -1;
  }
  if (v.size() <= 0)
    return 0;
  double t;
  for (NodeType i = 0; i < v.size(); i++) {
    t = v[i] - v0[i];
    r += t * t;
  }
  r = sqrt(r / v.size());
  return 0;
}

int recommend_NMAE(const VDouble& v0, const VDouble& v, double& r)
{
  r = 0;
  if (v.size() != v0.size()) {
    ERROR();
    return -1;
  }
  if (v.size() <= 0)
    return 0;
  double vMax = v0[0], vMin = v0[0];
  for (NodeType i = 0; i < v.size(); i++) {
    r += abs(v[i] - v0[i]);
    if (v0[i] > vMax)
      vMax = v0[i];
    if (v0[i] < vMin)
      vMin = v0[i];
  }
  if (vMax > vMin)
    r /= v.size() * (vMax - vMin);
  else
    r = 0;
  return 0;
}

int recommend_F(const VNodeType& v0, const VNodeType& v, double& recall,
    double& precision, double& F)
{
  NodeType s = 0;
  if (v0.size() > 0 || v.size() > 0) {
    for (NodeType i = 0; i < v.size(); i++)
      for (NodeType j = 0, t = v[i]; j < v0.size(); j++)
        if (t == v0[j]) {
          s++;
          break;
        }
  }
  if (v0.size() <= 0)
    recall = 0;
  else
    recall = (double)s / v0.size();
  if (v.size() <= 0)
    precision = 0;
  else
    precision = (double)s / v.size();
  F = 2 * precision * recall / (precision + recall);
  return 0;
}

// rs = sum(R[L...] / L.size())
int recommend_rankingScore(const VNodeType& R, const VNodeType& L, double& rs)
{
  rs = 0;
  if (L.size() <= 0)
    return 0;
  common_total(R, L, rs);
  rs /= L.size();
  return 0;
}

// rs ~ L && !L0 && rank/L
int recommend_rankingScore(
    const VNodeType& rk, const VNodeType& L0, const VNodeType& L, double& rs)
{
  rs = 0;
  const size_t N = rk.size();
  if (L0.size() < N || L.size() < N) {
    ERROR();
    return -1;
  }
  if (N <= 0)
    return 0;
  size_t n0 = 0, n = 0;
  for (size_t i = 0; i < N; i++) {
    NodeType p = rk[i];
    if (L0[p] == 0) {
      if (L[p] != 0) {
        n++;
        rs += n0;
      }
      n0++;
    }
  }
  if (n > 0)
    rs = rs / n0 / n;
  return 0;
}

//**//*****************************************************//*

#endif // ACT_RECOMMEND
