#include "ActFitnessComplexity.h"
#ifdef ACT_FITNESS_COMPLEXITY

#include "common.h"
//**//*****************************************************//*
template <typename T, typename T2>
int exp_2_Mcp(const std::vector<std::vector<T> >& e, std::vector<std::vector<T2> >& mcp)
{
  // cal Qp Qc Qsum
  const size_t NC = e.size(), NP = e[0].size();
  VDouble Qc(NC, 0), Qp(NP, 0);
  double Qsum = 0;
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < NP; p++) {
      Qp[p] += e[c][p];
      Qc[c] += e[c][p];
    }
    Qsum += Qp[c];
  }

  // cal Mcp
  mcp.assign(NC, std::vector<T2>(NP, (T2)0));
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < NP; p++) {
      mcp[c][p] = (T2)(e[c][p] * Qsum >= Qc[c] * Qp[p] ? 1 : 0);
    }
  }

  return 0;
}

template <typename T>
int Mcp_2_C_P(const std::vector<std::vector<T> >& mcp, VVNodeType& pc, VVNodeType& pp)
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

//**/ /*****************************************************//*
#endif // ACT_FITNESS_COMPLEXITY
