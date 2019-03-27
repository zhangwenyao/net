#ifndef ACT_RECOMMEND_TEMPLATE_H
#define ACT_RECOMMEND_TEMPLATE_H

#include "ActRecommend.h"
#ifdef ACT_RECOMMEND

#include "common.h"
#include "cstdlib"
#include <cstring>

// *******************************************************
template <typename T>
int cal_proximity_rca2phi(
    const std::vector<std::vector<T>>& rca_uo, VVDouble& phi_oo)
{
  const size_t NU = rca_uo.size(), NO = rca_uo[0].size();
  phi_oo.assign(NO, VDouble(NO, 1));
  for (size_t a = 0; a < NO; ++a) {
    for (size_t b = 0; b < a; ++b) {
      double phi_ab, phi_ba;
      size_t nb = 0, nba = 0, na = 0, nab = 0;
      for (size_t c = 0; c < NU; ++c) {
        if (rca_uo[c][a] >= 1) {
          na++;
          if (rca_uo[c][b] >= 1)
            nab++;
        }
        if (rca_uo[c][b] >= 1) {
          nb++;
          if (rca_uo[c][a] >= 1)
            nba++;
        }
      }
      phi_ab = na > 0 ? (double)nab / na : 0;
      phi_ba = nb > 0 ? (double)nba / nb : 0;
      phi_oo[a][b] = phi_oo[b][a] = phi_ab < phi_ba ? phi_ab : phi_ab;
    }
  }
  return 0;
}

template <typename T>
int act_recommend_proximity_wcp(
    VVDouble& rcm, const std::vector<std::vector<T>>& uo)
{
  const size_t NU = uo.size(), NO = uo[0].size();
  rcm.assign(NU, VDouble(NO, 0));
  VVDouble phi_oo;
  cal_proximity_rca2phi(uo, phi_oo);

  for (size_t c = 0; c < NU; ++c) {
    for (size_t a = 0; a < NO; ++a) {
      size_t k = 0;
      double phiSum = 0, phi = 0;
      for (size_t b = 0; b < NO; ++b) {
        phiSum += phi_oo[a][b];
        if (uo[c][b] >= 1) {
          k++;
          phi += phi_oo[a][b];
        }
      }
      rcm[c][a] = k > 0 ? phi / phiSum : 0;
    }
  }

  return 0;
}

template <typename T>
int act_recommend_proximity_phi(
    VVDouble& rcm, const std::vector<std::vector<T>>& uo)
{
  const size_t NU = uo.size(), NO = uo[0].size();
  rcm.assign(NU, VDouble(NO, 0));
  VVDouble phi_oo;
  cal_proximity_rca2phi(uo, phi_oo);

  for (size_t c = 0; c < NU; ++c) {
    for (size_t a = 0; a < NO; ++a) {
      size_t k = 0;
      double phi = 0;
      for (size_t b = 0; b < NO; ++b) {
        if (uo[c][b] >= 1) {
          k++;
          phi += phi_oo[a][b];
        }
      }
      rcm[c][a] = k > 0 ? phi / k : 0;
    }
  }

  return 0;
}

// *******************************************************
// rs : not in L0 && in L && rank/size(~L0)
template <typename T>
int recommend_rankingScore(const VNodeType& rk, const std::vector<T>& L0,
    const std::vector<T>& L, double& rs, double& rsDev)
{
  rs = 0;
  rsDev = 0;
  const size_t N = rk.size();
  _ERR(L0.size() < N || L.size() < N);
  if (N <= 1) {
    rs = 0.5;
    return 0;
  }
  size_t n0 = 0, n = 0;
  for (size_t i = 0; i < N; i++) {
    NodeType p = rk[i];
    if (L0[p] == 0) {
      if (L[p] != 0) {
        n++;
        rs += n0;
        rsDev += (double)n0 * n0;
      }
      n0++;
    }
  }
  // INFORM(N, "\t", n0, "\t", n);
  if (n0 > 1 && n >= 1) {
    rs /= (n0 - 1.0) * n;
    rsDev = sqrt(rsDev / ((n0 - 1.0) * (n0 - 1.0) * n) - rs * rs);
  } else {
    rs = 0.5;
    rsDev = 0;
  }
  return 0;
}

template <typename T>
int count_rankingScore(const VVDouble& rcm, const size_t NC, const size_t NP,
    const std::vector<std::vector<T>>& mcp,
    const std::vector<std::vector<T>>& mcp2, VDouble& rankingScore,
    VDouble& rankingScoreDev)
{
  rankingScore.assign(NC, 0);
  rankingScoreDev.assign(NC, 0);
  VNodeType rk(NP, 0);
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < NP; p++)
      rk[p] = p;
    common_sort_p_val_less(&rk[0], &rk[NP], &rcm[c][0]);
    recommend_rankingScore(
        rk, mcp[c], mcp2[c], rankingScore[c], rankingScoreDev[c]);
  }
  return 0;
}

// ********************************************************
#endif // ACT_RECOMMEND
#endif // _H
