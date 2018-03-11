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
int act_recommend_mass_1(const VNodeType& p2p, const double t, VDouble& v)
{
  for (VNodeTypeCItr p = p2p.begin(); p != p2p.end(); p++)
    v[*p] += t;
  return 0;
}

int act_recommend_mass(
    ostream& os, const VVNodeType& uP2p, const VVNodeType& oP2p)
{
  if (!os) {
    ERROR();
    return -1;
  }
  const NodeType NU = uP2p.size(), NO = oP2p.size();
  VDouble u2(NU, 0), o2(NO, 0);
  for (NodeType i = 0; i < NU; i++) {
    u2.assign(NU, 0);
    o2.assign(NO, 0);

    // o -> u2
    for (VNodeTypeCItr pj = uP2p[i].begin(); pj != uP2p[i].end(); pj++) {
      NodeType j = *pj;
      if (oP2p[j].size() <= 0)
        continue;
      const double t = 1.0 / oP2p[j].size();
      act_recommend_mass_1(oP2p[j], t, u2);
    }

    // u2 -> o2
    for (NodeType i2 = 0; i2 < NU; i2++) {
      if (uP2p[i2].size() <= 0 || u2[i2] <= 0)
        continue;
      const double t2 = u2[i2] / uP2p[i2].size();
      act_recommend_mass_1(uP2p[i2], t2, o2);
    }

    os << o2 << '\n';
  }
  return 0;
}

int act_recommend_mass(
    const char* name, const VVNodeType& uP2p, const VVNodeType& oP2p)
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
  int flag = act_recommend_mass(os, uP2p, oP2p);
  os.close();
  return flag;
}

//**//*****************************************************//*
int act_recommend_heat_1(
    const VNodeType& p2p1, const VVNodeType& p2p2, const double t, VDouble& v)
{
  for (VNodeTypeCItr p = p2p1.begin(); p != p2p1.end(); p++) {
    const NodeType i = *p, s = p2p2[i].size();
    if (s > 0)
      v[i] += t / s;
  }
  return 0;
}

int act_recommend_heat(
    ostream& os, const VVNodeType& uP2p, const VVNodeType& oP2p)
{
  if (!os) {
    ERROR();
    return -1;
  }
  const NodeType NU = uP2p.size(), NO = oP2p.size();
  VDouble u2(NU, 0), o2(NO, 0);
  for (NodeType i = 0; i < NU; i++) {
    u2.assign(NU, 0);
    o2.assign(NO, 0);

    // o -> u2
    for (VNodeTypeCItr pj = uP2p[i].begin(); pj != uP2p[i].end(); pj++) {
      NodeType j = *pj;
      if (oP2p[j].size() <= 0)
        continue;
      act_recommend_heat_1(oP2p[j], uP2p, 1.0, u2);
    }

    // u2 -> o2
    for (NodeType i2 = 0; i2 < NU; i2++) {
      if (uP2p[i2].size() <= 0 || u2[i2] <= 0)
        continue;
      act_recommend_heat_1(uP2p[i2], uP2p, u2[i2], o2);
    }

    os << o2 << '\n';
  }
  return 0;
}

int act_recommend_heat(
    const char* name, const VVNodeType& uP2p, const VVNodeType& oP2p)
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
  int flag = act_recommend_heat(os, uP2p, oP2p);
  os.close();
  return flag;
}

//**//*****************************************************//*
int act_recommend_pagerank(ofstream& os, const VVNodeType& p2p, VDouble& v)
{
  if (!os) {
    ERROR();
    return -1;
  }

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
  int flag = act_recommend_mass(os, p2p, v);
  os.close();
  return flag;
}

//**//*****************************************************//*

#endif // ACT_RECOMMEND
