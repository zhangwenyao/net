#ifndef ACT_FITNESS_COMPLEXITY_H
#define ACT_FITNESS_COMPLEXITY_H

#include "net.h"

#ifdef ACT_FITNESS_COMPLEXITY
//**//*****************************************************//*
int Mcp_2_FC(VDouble& Fc, VDouble& Cp, const VVBool& Mcp);
template <typename T>
int Mcp_2_C_P(const std::vector<std::vector<T> >& mcp, VVNodeType& pc, VVNodeType& pp);

//**//*****************************************************//*
#include "ActFitnessComplexity.template.h"
#endif // ACT_FITNESS_COMPLEXITY
#endif // ACT_FITNESS_COMPLEXITY_H
