#include "ActFitnessComplexity.h"
#ifdef ACT_FITNESS_COMPLEXITY

#include "common.h"
//**//*****************************************************//*
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
