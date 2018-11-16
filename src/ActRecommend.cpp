#include "ActRecommend.h"
#ifdef ACT_RECOMMEND

#include "common.h"
using namespace std;

// *******************************************************
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

int linkMatr_2_p2p2(VVNodeType& user_p_object, VVNodeType& object_p_user,
    const VVDistType& matr)
{
  const NodeType NU = matr.size(), NO = matr[0].size();
  user_p_object.clear();
  user_p_object.resize(NU);
  object_p_user.clear();
  object_p_user.resize(NO);
  for (NodeType i = 0; i < NU; i++) {
    for (NodeType j = 0; j < NO; j++) {
      if (matr[i][j] != 0) {
        user_p_object[i].push_back(j);
        object_p_user[j].push_back(i);
      }
    }
  }
  return 0;
}

int linkMatr_2_userP2p(const VVDistType& matr, VVNodeType& userP2p)
{
  const NodeType NU = matr.size(), NO = matr[0].size();
  userP2p.clear();
  userP2p.resize(NU);
  for (NodeType i = 0; i < NU; i++) {
    for (NodeType j = i + 1; j < NU; j++) {
      for (NodeType k = 0; k < NO; k++) {
        if (matr[i][k] != 0 && matr[j][k] != 0) {
          userP2p[i].push_back(j);
          userP2p[j].push_back(i);
        }
        continue;
      }
    }
  }
  return 0;
}

int linkMatr_2_objectP2p(const VVDistType& matr, VVNodeType& objectP2p)
{
  const NodeType NU = matr.size(), NO = matr[0].size();
  objectP2p.clear();
  objectP2p.resize(NO);
  for (NodeType i = 0; i < NO; i++) {
    for (NodeType j = i + 1; j < NO; j++) {
      for (NodeType k = 0; k < NU; k++) {
        if (matr[k][i] != 0 && matr[k][j] != 0) {
          objectP2p[i].push_back(j);
          objectP2p[j].push_back(i);
        }
        continue;
      }
    }
  }
  return 0;
}

// *******************************************************
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

// *******************************************************
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
  // cout << "\n"
  //<< i << "\n"
  //<< u2 << endl;

  // u2 -> o2
  for (NodeType i2 = 0; i2 < NU; i2++) {
    if (uP2p[i2].size() <= 0 || u2[i2] <= 0)
      continue;
    act_recommend_heat_sum(uP2p[i2], oP2p, u2[i2], o2);
  }
  // cout << o2 << endl;

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

// *******************************************************
int act_recommend_hybrid_matrix(VVDouble& rcm, const VVNodeType& uP2p,
    const VVNodeType& oP2p, const double lambda)
{
  const NodeType NU = uP2p.size(), NO = oP2p.size();
  VVDouble w(NO, VDouble(NO, 0));
  for (NodeType i = 0; i < NU; i++) {
    NodeType ki = uP2p[i].size();
    double dki = 1.0 / ki;
    for (NodeType j = 0; j < ki; j++) {
      NodeType a = uP2p[i][j];
      for (NodeType k = 0; k < ki; k++) {
        NodeType b = uP2p[i][k];
        w[a][b] += dki
            / (pow(oP2p[a].size(), 1 - lambda) * pow(oP2p[b].size(), lambda));
      }
    }
  }
  rcm.assign(NU, VDouble(NO, 0));
  VVDouble r = rcm;
  for (NodeType i = 0; i < NU; i++) {
    for (NodeType j = 0; j < uP2p[i].size(); j++)
      r[i][uP2p[i][j]] = 1;
  }
  common_matrixCross(r, w, rcm);
  return 0;
}

// *******************************************************
int act_recommend_pagerank(const VVNodeType& p2p, VDouble& v)
{
  const NodeType N = p2p.size();
  v.assign(N, 1);
  if (N <= 1)
    return 0;

  VDouble v2;
  for (double e = 0, e2 = 1, s2 = N, t;
       s2 > 1e-6 && e2 * N <= e * e * (1 + 1e-4);) {
    e = 0;
    e2 = 0;
    s2 = 0;
    v2.assign(N, 0);
    common_matrixCross1_p2p(p2p, v, v2);
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

// *****************************************************
int act_recommend_commonNeighbour_object(VVDouble& rcm, const VVNodeType& oo)
{
  // TODO
  return 0;
}

// *******************************************************
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
  if (L.size() <= 1) {
    rs = 0.5;
    return 0;
  }
  common_total_p(&R[0], &L[0], L.size(), rs = 0);
  rs /= L.size() - 1;
  return 0;
}

// *******************************************************

#endif // ACT_RECOMMEND
