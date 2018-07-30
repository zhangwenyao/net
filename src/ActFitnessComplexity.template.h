#include "ActFitnessComplexity.h"
#ifdef ACT_FITNESS_COMPLEXITY

#include "ActFitnessComplexity.h"
#include "common.h"
#include "cstdlib"
#include <cstring>

// *******************************************************
template <typename T, typename T2>
int export_2_Mcp(
    const std::vector<std::vector<T> >& e, std::vector<std::vector<T2> >& mcp)
{
  // cal Qp Qc Qsum
  const size_t NC = e.size(), NP = e[0].size();
  std::vector<T> Qc(NC, 0), Qp(NP, 0);
  T Qsum = 0;
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < NP; p++) {
      Qp[p] += e[c][p];
      Qc[c] += e[c][p];
    }
    Qsum += Qc[c];
  }

  // cal Mcp
  mcp.assign(NC, std::vector<T2>(NP, (T2)0));
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < NP; p++) {
      mcp[c][p] = (T2)(
          e[c][p] > 0 && (double)e[c][p] * Qsum >= (double)Qc[c] * Qp[p] ? 1
                                                                         : 0);
    }
  }

  return 0;
}

template <typename T>
int Mcp_2_C_P(
    const std::vector<std::vector<T> >& mcp, VVNodeType& pc, VVNodeType& pp)
{
  const size_t NC = mcp.size(), NP = mcp[0].size();
  pc.clear();
  pc.resize(NC);
  pp.clear();
  pp.resize(NP);
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < mcp[c].size(); p++) {
      if (mcp[c][p] != 0) {
        pc[c].push_back(p);
        if (p >= NP) {
          ERROR();
          return -1;
        }
        pp[p].push_back(c);
      }
    }
  }
  return 0;
}

template <typename T>
int Mcp_2_FC(
    VDouble& Fc, VDouble& Cp, const std::vector<std::vector<T> >& Mcp)
{
  int flag = 0;
  const double delta = 1.0e-8;
  const size_t NC = Mcp.size(), NP = Mcp[0].size();
  Fc.assign(NC, 1);
  Cp.assign(NP, 1);
  VDouble iFc = Fc, iCp = Cp;
  double fMean = 1, cMean = 1, ifMean, icMean;
  for (int count = 1; 1; count++) {
    iFc.assign(NC, -1);
    ifMean = 0;
    size_t n = 0;
    for (size_t c = 0; c < NC; c++) {
      for (size_t p = 0; p < NP; p++)
        if (Mcp[c][p]) {
          if (iFc[c] < 0)
            iFc[c] = 0;
          iFc[c] += Cp[p];
        }
      if (iFc[c] >= 0) {
        ifMean += iFc[c];
        ++n;
      }
    }
    if (n <= 0 || ifMean <= 0) {
      flag = -1;
      ERROR("ifMean = ", ifMean, "\t", count);
      break;
    }
    ifMean /= n;
    // ifMean /= NC;

    iCp.assign(NP, -1);
    icMean = 0;
    n = 0;
    for (size_t p = 0; p < NP; p++) {
      for (size_t c = 0; c < NC; c++) {
        if (Mcp[c][p]) {
          if (iCp[p] < 0)
            iCp[p] = 0;
          iCp[p] += 1 / Fc[c];
        }
      }
      if (iCp[p] >= 0) {
        iCp[p] = 1 / iCp[p];
        icMean += iCp[p];
        ++n;
      }
    }
    if (n <= 0 || icMean <= 0) {
      flag = -1;
      ERROR("icMean = ", icMean, "\t", count);
      break;
    }
    icMean /= n;
    // icMean /= NP;

    // INFORM(count, "\t", ifMean, "\t", icMean);
    for (size_t c = 0; c < NC; c++)
      Fc[c] = iFc[c] < 0 ? -1 : iFc[c] / ifMean;
    for (size_t p = 0; p < NP; p++)
      Cp[p] = iCp[p] < 0 ? -1 : iCp[p] / icMean;

    if ((1.0 - delta) * cMean <= icMean && icMean <= (1.0 + delta) * cMean
        && (1.0 - delta) * fMean <= ifMean
        && ifMean <= (1.0 + delta) * fMean) {
      // DBG(count);
      break;
    }
    fMean = ifMean;
    cMean = icMean;
    // if (count % 1000 == 0)
    // DBG(count, "\tfm ", fMean, "\tcm ", cMean);
  }
  for (size_t c = 0; c < NC; c++)
    if (iFc[c] < 0)
      Fc[c] = 0;
  for (size_t p = 0; p < NP; p++)
    if (iCp[p] < 0)
      Cp[p] = 0;

  return flag;
}

// rs : not in L0 && in L && rank/size(~L0)
template <typename T>
int recommend_rankingScore(const VNodeType& rk, const std::vector<T>& L0,
    const std::vector<T>& L, double& rs)
{
  rs = 0;
  const size_t N = rk.size();
  if (L0.size() < N || L.size() < N) {
    ERROR();
    return -1;
  }
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
        INFORM(p);
      }
      n0++;
    }
  }
  INFORM(n0);
  INFORM(n);
  if (n0 > 1 && n >= 1)
    rs /= (n0 - 1.0) * n;
  else
    rs = 0.5;
  return 0;
}

template <typename T>
int count_rankingScore(const VVDouble& rcm, const size_t NC, const size_t NP,
    const std::vector<std::vector<T> >& mcp,
    const std::vector<std::vector<T> >& mcp2, VDouble& rankingScore,
    const char* name)
{
  rankingScore.assign(NC, 0);
  VNodeType rk(NP, 0);
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < NP; p++)
      rk[p] = p;
    common_sort_p_val_less(&rk[0], &rk[NP], &rcm[c][0]);
    recommend_rankingScore(rk, mcp[c], mcp2[c], rankingScore[c]);
    break;
  }
  if (name != NULL && name[0] != '\0')
    common_save1(name, rankingScore, '\n');
  return 0;
}

// ********************************************************
#endif // ACT_FITNESS_COMPLEXITY
