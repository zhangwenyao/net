#include "ActFitnessComplexity.h"
#ifdef ACT_FITNESS_COMPLEXITY

#include "common.h"
using namespace std;

// *******************************************************
int Mcp_2_FC(VDouble& Fc, VDouble& Cp, const VVBool& Mcp)
{
  int flag = 0;
  const double delta = 1.0e-6;
  const size_t NC = Mcp.size(), NP = Mcp[0].size();
  Fc.assign(NC, 1);
  Cp.assign(NP, 1);
  VDouble iFc = Fc, iCp = Cp;
  double fMean = 1, cMean = 1, ifMean, icMean;
  for (int count = 1; 1; count++) {
    iFc.assign(NC, -1);
    ifMean = 0;
    for (size_t c = 0; c < NC; c++) {
      for (size_t p = 0; p < NP; p++)
        if (Mcp[c][p] && Cp[p] > 0) {
          if (iFc[c] < 0)
            iFc[c] = 0;
          iFc[c] += Cp[p];
        }
      if (iFc[c] >= 0)
        ifMean += iFc[c];
    }
    ifMean /= NC;
    if (ifMean <= 0) {
      flag = -1;
      ERROR("ifMean = ", ifMean, "\t", count);
      break;
    }

    iCp.assign(NP, -1);
    icMean = 0;
    for (size_t p = 0; p < NP; p++) {
      for (size_t c = 0; c < NC; c++) {
        if (Mcp[c][p]) {
          if (Fc[c] <= 0) {
            iCp[p] = -1;
            INFORM(p, "\t", c);
            break;
          }
          if (iCp[p] < 0)
            iCp[p] = 0;
          iCp[p] += 1 / Fc[c];
        }
      }
      if (iCp[p] >= 0) {
        iCp[p] = 1 / iCp[p];
        icMean += iCp[p];
      }
    }
    icMean /= NP;
    if (icMean <= 0) {
      flag = -1;
      ERROR("icMean = ", icMean, "\t", count);
      break;
    }

    for (size_t c = 0; c < NC; c++)
      Fc[c] = iFc[c] < 0 ? -1 : iFc[c] / ifMean;
    for (size_t p = 0; p < NP; p++)
      Cp[p] = iCp[p] < 0 ? -1 : iCp[p] / icMean;

    if ((1.0 - delta) * cMean <= icMean && icMean <= (1.0 + delta) * cMean
        && (1.0 - delta) * fMean <= ifMean
        && ifMean <= (1.0 + delta) * fMean) {
      // std::cout << count << std::endl;
      break;
    }
    fMean = ifMean;
    cMean = icMean;
    if (count % 1000 == 0)
      INFORM(count, "\tfm ", fMean, "\tcm ", cMean);
  }
  for (size_t c = 0; c < NC; c++)
    if (iFc[c] < 0)
      Fc[c] = 0;
  for (size_t p = 0; p < NP; p++)
    if (iCp[p] < 0)
      Cp[p] = 0;

  return flag;
}

// *******************************************************
int count_k1(const size_t NC, const size_t NP, const VVNodeType& mcp,
    VNodeType& k1, const char* name)
{
  k1.assign(NC, 0);
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < NP; p++) {
      if (mcp[c][p] != 0)
        k1[c]++;
    }
  }
  if (name != NULL && name[0] != '\0')
    common_save1(name, k1, '\n');
  return 0;
}

int count_cpNew(const size_t NC, const size_t NP, const VVNodeType& mcp,
    const VVNodeType& mcp2, VVNodeType& cpNew, const char* name)
{
  cpNew.resize(NC);
  for (size_t c = 0; c < NC; c++) {
    cpNew[c].clear();
    for (size_t p = 0; p < NP; p++) {
      if (mcp[c][p] == 0 && mcp2[c][p] != 0)
        cpNew[c].push_back(p);
    }
  }
  if (name != NULL && name[0] != '\0')
    common_save2(name, cpNew);
  return 0;
}

int count_kNew(VNodeType& kNew, const VVNodeType& cpNew, const char* name)
{
  kNew.resize(cpNew.size());
  for (size_t c = 0; c < cpNew.size(); c++) {
    kNew[c] = cpNew[c].size();
  }
  if (name != NULL && name[0] != '\0')
    common_save1(name, kNew, '\n');
  return 0;
}

int count_pcNewRemainRank(const VDouble& pc, const size_t NC, const size_t NP,
    const VVNodeType& mcp, const VVNodeType& cpNew, VVNodeType& rankNew,
    const char* name)
{
  rankNew.resize(NC);
  VDouble pc2(NP, 0);
  VNodeType rk(NP, 0), rk2(NP, 0);
  for (size_t c = 0; c < NC; c++) {
    rankNew[c].clear();
    size_t NN = cpNew[c].size(), NR = 0;
    if (NN <= 0)
      continue;
    for (size_t p = 0; p < NP; p++)
      if (mcp[c][p] == 0) {
        rk[NR] = p;
        pc2[NR++] = pc[p];
      }
    common_sort_p_val_less(&rk[0], &rk[NR], &pc2[0]);
    for (size_t p = 0; p < NR; p++)
      rk2[rk[p]] = p;
    for (size_t p = 0; p < NN; p++)
      rankNew[c].push_back(rk2[cpNew[c][p]]);
  }
  if (name != NULL && name[0] != '\0')
    common_save2(name, rankNew);
  return 0;
}

int count_pcNewScale(const size_t NC, const size_t NP, const VNodeType& k1,
    const VVNodeType& cpNewRemainRank, VVDouble& scale, const char* name)
{
  scale.resize(NC);
  for (size_t c = 0; c < NC; c++) {
    scale[c].clear();
    size_t NN = cpNewRemainRank[c].size();
    if (NN <= 0)
      continue;
    double x = 1.0 / (NP - k1[c]);
    for (size_t p = 0; p < NN; p++)
      scale[c].push_back(cpNewRemainRank[c][p] * x);
  }
  if (name != NULL && name[0] != '\0')
    common_save2(name, scale);
  return 0;
}

int count_pcNewRank(const VDouble& pc, const size_t NC, const size_t NP,
    const VVNodeType& cpNew, VVNodeType& rankNew, const char* name)
{
  rankNew.resize(NC);
  VNodeType rk(NP, 0), rk2(NP, 0);
  for (size_t p = 0; p < NP; p++)
    rk[p] = p;
  common_sort_p_val_less(&rk[0], &rk[NP], &pc[0]);
  for (size_t p = 0; p < NP; p++)
    rk2[rk[p]] = p;
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < cpNew[c].size(); p++)
      rankNew[c].push_back(rk2[cpNew[c][p]]);
  }
  if (name != NULL && name[0] != '\0')
    common_save2(name, rankNew);
  return 0;
}

int count_newRemainRank(const VVDouble& rcm, const size_t NC, const size_t NP,
    const VVNodeType& mcp, const VVNodeType& cpNew, VVNodeType& newRemainRank,
    const char* name)
{
  newRemainRank.resize(NC);
  VDouble pc2(NP, 0);
  VNodeType rk(NP, 0), rk2(NP, 0);
  for (size_t c = 0; c < NC; c++) {
    newRemainRank[c].clear();
    size_t NN = cpNew[c].size(), NR = 0;
    if (NN <= 0)
      continue;
    for (size_t p = 0; p < NP; p++)
      if (mcp[c][p] == 0) {
        rk[NR] = p;
        pc2[NR++] = rcm[c][p];
      }
    common_sort_p_val_less(&rk[0], &rk[NR], &pc2[0]);
    for (size_t p = 0; p < NR; p++)
      rk2[rk[p]] = p;
    for (size_t p = 0; p < NN; p++)
      newRemainRank[c].push_back(rk2[cpNew[c][p]]);
  }
  if (name != NULL && name[0] != '\0')
    common_save2(name, newRemainRank);
  return 0;
}

int count_rankNew(const VVDouble& rcm, const size_t NC, const size_t NP,
    const VVNodeType& cpNew, VVNodeType& rankNew, const char* name)
{
  rankNew.resize(NC);
  VNodeType rk(NP, 0), rk2(NP, 0);
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < NP; p++)
      rk[p] = p;
    common_sort_p_val_less(&rk[0], &rk[NP], &rcm[c][0]);
    for (size_t p = 0; p < NP; p++)
      rk2[rk[p]] = p;
    for (size_t p = 0; p < cpNew[c].size(); p++)
      rankNew[c].push_back(rk2[cpNew[c][p]]);
  }
  if (name != NULL && name[0] != '\0')
    common_save2(name, rankNew);
  return 0;
}

// *******************************************************
int filter_trade_name(const char* tradeFilename, const char* countryFilename,
    const char* productFilename)
{
  FILE* fp = fopen(tradeFilename, "r");
  if (NULL == fp) {
    ERROR();
    return -1;
  }
  size_t NC = 26 * 26 * 26, NP = 9999;
  VNodeType cVal(NC, 0), pVal(NP, 0);
  char cChar[300][4] = { { 0 } };
  char origin[9], dest[9], s[999];
  fgets(s, 999, fp);
  for (size_t t, sitc;
       3 == fscanf(fp, "%*s%s%s%zu%*s%*s", origin, dest, &sitc);) {
    if (!cVal[t = common_atoi<size_t>(origin)]) {
      cVal[t] = ++NC;
      strcpy(cChar[NC], origin);
    }
    if (!cVal[t = common_atoi<size_t>(dest)]) {
      cVal[t] = ++NC;
      strcpy(cChar[NC], dest);
    }
    if (!pVal[sitc]) {
      pVal[sitc] = ++NP;
    }
  }
  fclose(fp);
  common_save(countryFilename, cChar + 1, NC, '\n');
  common_save_bool(productFilename, &pVal[0], 9999, '\n');
  return 0;
}

int filter_sum_trade(const char* tradeFilename, const char* countryFilename,
    const char* productFilename)
{
  VNodeType cVal(26 * 26 * 26, 0), pVal(9999, 0);
  size_t NC = 0;
  {
    char s[4] = { 0 };
    ifstream is(countryFilename);
    for (size_t i; is >> i >> s;)
      cVal[common_atoi<size_t>(s)] = i;
    is.close();
  }
  size_t NP = 0;
  {
    ifstream is(productFilename);
    for (size_t i, p; is >> i >> p;)
      pVal[p] = i;
    is.close();
  }

  FILE* fp = fopen(tradeFilename, "r");
  if (NULL == fp) {
    ERROR();
    return -1;
  }
  char origin[9], dest[9], s[999];
  fgets(s, 999, fp);
  for (size_t t, sitc;
       3 == fscanf(fp, "%*s%s%s%zu%*s%*s", origin, dest, &sitc);) {
    if (!cVal[t = common_atoi<size_t>(origin)]) {
      cVal[t] = ++NC;
    }
    if (!pVal[sitc]) {
      pVal[sitc] = ++NP;
    }
  }
  fclose(fp);
  return 0;
}

int filter_index(const NodeType N, VVNodeType& indexs, VNodeType& index)
{
  index.assign(N, 0);
  for (size_t i = 0; i < indexs.size(); i++) {
    for (size_t j = 0; j < indexs[i].size(); j++)
      index[indexs[i][j]]++;
  }
  for (size_t j = 0; j < N; j++) {
    if (index[j] < indexs.size())
      index[j] = 0;
    else
      index[j] = 1;
  }
  return 0;
}

// *******************************************************
#endif // ACT_FITNESS_COMPLEXITY
