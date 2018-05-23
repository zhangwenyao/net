#include "ActFitnessComplexity.h"
#ifdef ACT_FITNESS_COMPLEXITY

#include "common.h"
using namespace std;

// *******************************************************
int count_k1(const NodeType NC, const NodeType NP, const VVNodeType& mcp,
    VNodeType& k1, const char* name)
{
  k1.assign(NC, 0);
  for (NodeType c = 0; c < NC; c++) {
    for (NodeType p = 0; p < NP; p++) {
      if (mcp[c][p])
        k1[c]++;
    }
  }
  if (name != NULL && name[0] != '\0')
    common_save1(name, k1, '\n');
  return 0;
}

int count_cpNew(const NodeType NC, const NodeType NP, const VVNodeType& mcp,
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
  const unsigned NC = 26 * 26 * 26, NP = 9999;
  unsigned cVal[NC] = { 0 }, pVal[NP] = { 0 };
  char origin[9], s[999];
  unsigned nc = 0, np = 0;
  fgets(s, 999, fp);
  for (unsigned t, hs92; 2 == fscanf(fp, "%*s%s%u%*s", origin, &hs92);) {
    if (!cVal[t = common_atoi<unsigned>(origin)])
      cVal[t] = ++nc;
    if (!pVal[hs92])
      pVal[hs92] = ++np;
  }
  fclose(fp);

  char cChar[300][4] = { { 0 } };
  for (unsigned i = 0, c = 0; i < NC && c < nc; ++i) {
    if (cVal[i]) {
      common_itoa(i, cChar[c], 'a', 26, 3);
      common_cstring_reverse(cChar[c++]);
    }
  }
  common_save(countryFilename, cChar, nc, '\n');

  common_save_bool(productFilename, &pVal[0], 9999, '\n');

  return 0;
}

int read_country_names(
    const char* countryFilename, NodeType& NC, VNodeType& cVal)
{
  ifstream is(countryFilename);
  if (!is) {
    ERROR();
    return -1;
  }
  NC = 0;
  for (string s; is >> s;)
    cVal[common_atoi<unsigned>(s.c_str())] = NC++;
  is.close();
  return 0;
}

int read_product_names(
    const char* productFilename, NodeType& NP, VNodeType& pVal)
{
  ifstream is(productFilename);
  if (!is) {
    ERROR();
    return -1;
  }
  NP = 0;
  for (NodeType v; is >> v;)
    pVal[v] = NP++;
  is.close();
  return 0;
}

int filter_sum_trade(const char* tradeFilename, const char* countryFilename,
    const char* productFilename, const char* dirSave)
{
  VNodeType cVal(26 * 26 * 26, 0);
  NodeType NC = 0;
  read_country_names(countryFilename, NC, cVal);
  cout << NC << endl;

  VNodeType pVal(9999, 0);
  NodeType NP = 0;
  read_product_names(productFilename, NP, pVal);
  cout << NP << endl;

  VVDouble expts(NC, VDouble(NP, 0));
  {
    FILE* fp = fopen(tradeFilename, "r");
    if (NULL == fp) {
      ERROR();
      return -1;
    }
    char origin[4], s[999];
    unsigned year, pd, YEAR1 = 1995, year0 = YEAR1;
    long long unsigned l = 1;
    fgets(s, 999, fp);
    for (double v; 4 == fscanf(fp, "%u%s%u%lf", &year, origin, &pd, &v);
         ++l) {
      if (year < year0) {
        ERROR();
        break;
      }
      if (year > year0) {
        cout << l << "\t" << year0 << endl;
        sprintf(s, "%s%u.export.txt", dirSave, year0);
        common_save2(s, expts);
        expts.assign(NC, VDouble(NP, 0));
        expts[cVal[common_atoi<size_t>(origin)]][pVal[pd]] = v;
        year0 = year;
      } else { // year==year0
        expts[cVal[common_atoi<size_t>(origin)]][pVal[pd]] += v;
      }
    }
    cout << l << "\t" << year0 << endl;
    sprintf(s, "%s%u.export.txt", dirSave, year0);
    common_save2(s, expts);
    fclose(fp);
  }

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
