#ifndef ACT_RECOMMEND_TEMPLATE_H
#define ACT_RECOMMEND_TEMPLATE_H

#include "ActRecommend.h"
#ifdef ACT_RECOMMEND

#include "common.h"
#include "cstdlib"
#include <cstring>

// *******************************************************
// rs : not in L0 && in L && rank/size(~L0)
template <typename T>
int recommend_rankingScore(const VNodeType& rk, const std::vector<T>& L0,
    const std::vector<T>& L, double& rs, double& rsDev)
{
  rs = 0;
  rsDev = 0;
  const size_t N = rk.size();
  ERROR_TEST(L0.size() < N || L.size() < N);
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
    const std::vector<std::vector<T> >& mcp,
    const std::vector<std::vector<T> >& mcp2, VDouble& rankingScore,
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
