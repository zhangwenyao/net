#include "ActFitnessComplexity.h"
#ifdef ACT_FITNESS_COMPLEXITY

#include "common.h"
#include <algorithm>
#include <iomanip>
using namespace std;

// *******************************************************
int count_deg(const VVNodeType& mcp, VNodeType& deg, const char* name)
{
  const NodeType NC = mcp.size(), NP = mcp[0].size();
  deg.assign(NC, 0);
  for (NodeType c = 0; c < NC; ++c) {
    for (NodeType p = 0; p < NP; ++p) {
      if (mcp[c][p])
        deg[c]++;
    }
  }
  if (name != NULL && name[0] != '\0')
    ERROR_TEST(common_save1(name, deg, '\n'));
  return 0;
}

int count_product_deg(const VVNodeType& mcp, VNodeType& deg, const char* name)
{
  const NodeType NC = mcp.size(), NP = mcp[0].size();
  deg.assign(NP, 0);
  for (NodeType p = 0; p < NP; ++p) {
    for (NodeType c = 0; c < NC; ++c) {
      if (mcp[c][p])
        deg[p]++;
    }
  }
  if (name != NULL && name[0] != '\0')
    ERROR_TEST(common_save1(name, deg, '\n'));
  return 0;
}

int count_mcpMcp(const VVNodeType& mcp, VVNodeType& mcpMcp)
{
  NodeType NC = mcp.size(), NP = mcp[0].size();
  mcpMcp.resize(NC);
  for (size_t c = 0; c < NC; c++) {
    mcpMcp[c].clear();
    for (size_t p = 0; p < NP; p++) {
      if (mcp[c][p] != 0)
        mcpMcp[c].push_back(p);
    }
  }
  return 0;
}

int count_mcpNew(const VVNodeType& mcp0, const VVNodeType& mcp,
    VVNodeType& mcpNew, VVNodeType& mcpRemain)
{
  NodeType NC = mcp.size(), NP = mcp[0].size();
  mcpNew.resize(NC);
  mcpRemain.resize(NC);
  for (size_t c = 0; c < NC; c++) {
    mcpNew[c].clear();
    mcpRemain[c].clear();
    for (size_t p = 0; p < NP; p++) {
      if (mcp[c][p] != 0) {
        if (mcp0[c][p] == 0)
          mcpNew[c].push_back(p);
        else
          mcpRemain[c].push_back(p);
      }
    }
  }
  return 0;
}

int count_pcNewRankV2(const VNodeType& pcRankV2, const VVNodeType& mcpNew,
    VVNodeType& pcNewRankV2)
{
  const size_t NC = mcpNew.size();
  pcNewRankV2.clear();
  pcNewRankV2.resize(NC);
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < mcpNew[c].size(); p++)
      pcNewRankV2[c].push_back(pcRankV2[mcpNew[c][p]]);
    break;
  }
  return 0;
}

int count_pcNewRemainRankV2(const VNodeType& pcRankV2, const VVNodeType& mcp,
    const VVNodeType& mcpNew, VVNodeType& pcNewRemainRankV2)
{
  const size_t NC = mcp.size(), NP = mcp[0].size();
  pcNewRemainRankV2.clear();
  pcNewRemainRankV2.resize(NC);
  for (size_t c = 0; c < NC; c++) {
    VNodeType rk = mcp[c];
    for (auto p : mcpNew[c])
      rk[p] = 0;
    for (size_t p = 0; p < NP; ++p)
      if (rk[p] != 0)
        pcNewRemainRankV2[c].push_back(pcRankV2[p]);
  }
  return 0;
}

// int count_newScale(const VNodeType& deg, const VVNodeType& newRemainRankV2,
// VVDouble& newScale)
//{
// const size_t NC = deg.size(), NP, newScale.resize(NC);
// for (size_t c = 0; c < NC; c++) {
// newScale[c].clear();
// if (NP == deg[c] + 1 && newRemainRank[c].size() == 1) {
// newScale[c].push_back(0.5);
// continue;
//}
// double x = 1.0 / (NP - deg[c] - 1);
// for (size_t p = 0; p < newRemainRank[c].size(); p++)
// newScale[c].push_back(newRemainRank[c][p] * x);
// break;
//}
// if (name != NULL && name[0] != '\0')
// ERROR_TEST(common_save2(name, newScale));
// return 0;
//}

int count_newRank(const VVDouble& rcm, const size_t NC, const size_t NP,
    const VVNodeType& cpNew, VVNodeType& newRank, const char* name)
{
  newRank.resize(NC);
  VNodeType rk(NP, 0), rk2(NP, 0);
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < NP; p++)
      rk[p] = p;
    common_sort_p_val_less(&rk[0], &rk[NP], &rcm[c][0]);
    for (size_t p = 0; p < NP; p++)
      rk2[rk[p]] = p;
    for (size_t p = 0; p < cpNew[c].size(); p++)
      newRank[c].push_back(rk2[cpNew[c][p]]);
  }
  if (name != NULL && name[0] != '\0')
    ERROR_TEST(common_save2(name, newRank));
  return 0;
}

int count_newRemainRank(const VVDouble& rcm, const size_t NC, const size_t NP,
    const VVNodeType& mcp, const VVNodeType& mcpNew,
    VVNodeType& newRemainRank, const char* name)
{
  newRemainRank.resize(NC);
  VNodeType rk(NP, 0), rk2(NP, 0);
  for (size_t c = 0; c < NC; c++) {
    newRemainRank[c].clear();
    size_t NN = mcpNew[c].size(), NR = 0;
    if (NN <= 0)
      continue;
    for (size_t p = 0; p < NP; p++)
      if (mcp[c][p] == 0)
        rk[NR++] = p;
    common_sort_p_val_less(&rk[0], &rk[NR], &rcm[c][0]);
    for (size_t p = 0; p < NR; p++)
      rk2[rk[p]] = p;
    for (size_t p = 0; p < NN; p++)
      newRemainRank[c].push_back(rk2[mcpNew[c][p]]);
    break;
  }
  if (name != NULL && name[0] != '\0')
    ERROR_TEST(common_save2(name, newRemainRank));
  return 0;
}

int cal_val_2_rankScale(const VDouble& val, VNodeType& rk, VNodeType& rkIndex,
    VNodeType& rkV2, VNodeType& rkV2Index, VDouble& rkScale, const size_t N)
{
  rk.resize(N);
  rkIndex.resize(N);
  rkV2.resize(N);
  rkV2Index.resize(N);
  rkScale.resize(N);
  for (size_t i = 0; i < N; ++i)
    rk[i] = i;
  common_sort_p_val_less(rk.begin(), rk.end(), &val.front());
  common_get_index(rk.begin(), rk.end(), &rkIndex.front());
  common_sort_rankV2(&val.front(), rk.begin(), rk.end(), &rkV2.front());
  common_get_index_val(
      rk.begin(), rk.end(), &rkV2Index.front(), &rkV2.front());
  if (N > 1)
    for (size_t i = 0; i < N; ++i)
      rkScale[i] = (double)rkV2Index[i] / 2 / (N - 1);
  else
    rkScale.assign(N, 0.5);
  return 0;
}

int cal_val_2_rankScale(const VDouble& pc, VDouble& scale)
{
  const size_t NP = pc.size();
  VNodeType pcRank(NP), pcRankIndex(NP), pcRankV2(NP), pcRankV2Index(NP);
  scale.resize(NP);
  cal_val_2_rankScale(
      pc, pcRank, pcRankIndex, pcRankV2, pcRankV2Index, scale, NP);
  return 0;
}

int save_val_2_rankScale(const VDouble& pc, const char* dir)
{
  const size_t NP = pc.size();
  VNodeType pcRank(NP), pcRankIndex(NP), pcRankV2(NP), pcRankV2Index(NP);
  VDouble pcRankScale(NP);
  cal_val_2_rankScale(
      pc, pcRank, pcRankIndex, pcRankV2, pcRankV2Index, pcRankScale, NP);
  string s = dir;
  save_rankScale((s + ".rankLess").c_str(), pcRank, pcRankIndex, pcRankV2,
      pcRankV2Index, pcRankScale);
  return 0;
}

int cal_val_2_rankScale_p(const VDouble& val, const NodeType* p,
    VNodeType& rk, VNodeType& rkIndex, VNodeType& rkV2, VNodeType& rkV2Index,
    VDouble& rkScale, const size_t N)
{
  VDouble v(N);
  for (size_t i = 0; i < N; ++i)
    v[i] = val[*p++];
  return cal_val_2_rankScale(val, rk, rkIndex, rkV2, rkV2Index, rkScale, N);
}

int save_rankScale(const char* dir, const VNodeType& rk,
    const VNodeType& rkIndex, const VNodeType& rkV2,
    const VNodeType& rkV2Index, const VDouble& rkScale)
{
  string s = dir;
  common_save1((s + ".txt").c_str(), rk, '\n');
  common_save1((s + ".index.txt").c_str(), rkIndex, '\n');
  common_save1((s + "V2.txt").c_str(), rkV2, '\n');
  common_save1((s + "V2.index.txt").c_str(), rkV2Index, '\n');
  common_save1((s + "V2.scale.txt").c_str(), rkScale, '\n');
  return 0;
}

int save_rankScale2(const char* dir, const VVNodeType& rk,
    const VVNodeType& rkIndex, const VVNodeType& rkV2,
    const VVNodeType& rkV2Index, const VVDouble& rkScale)
{
  string s = dir;
  common_save2((s + ".txt").c_str(), rk);
  common_save2((s + ".index.txt").c_str(), rkIndex);
  common_save2((s + "V2.txt").c_str(), rkV2);
  common_save2((s + "V2.index.txt").c_str(), rkV2Index);
  common_save2((s + "V2.scale.txt").c_str(), rkScale);
  return 0;
}

int save_rankScale_val(const char* dir, const VDouble& val)
{
  VNodeType rk, rkIndex, rkV2, rkV2Index;
  VDouble rkScale;
  cal_val_2_rankScale(val, rk, rkIndex, rkV2, rkV2Index, rkScale, val.size());
  save_rankScale(dir, rk, rkIndex, rkV2, rkV2Index, rkScale);
  return 0;
}

int save_rankScale2_val(const char* dir, const VVDouble& val)
{
  const size_t N = val.size();
  VVNodeType rk(N), rkIndex(N), rkV2(N), rkV2Index(N);
  VVDouble rkScale(N);
  for (size_t i = 0; i < N; ++i)
    cal_val_2_rankScale(val[i], rk[i], rkIndex[i], rkV2[i], rkV2Index[i],
        rkScale[i], val[i].size());
  save_rankScale2(dir, rk, rkIndex, rkV2, rkV2Index, rkScale);
  return 0;
}

int save_rankScale2_val_p(
    const char* dir, const VVDouble& val, const VVNodeType p)
{
  const size_t N = val.size();
  VVNodeType rk(N), rkIndex(N), rkV2(N), rkV2Index(N);
  VVDouble rkScale(N);
  for (size_t i = 0; i < N; ++i) {
    size_t NN = p[i].size();
    VDouble v(NN);
    for (size_t j = 0; j < NN; ++j)
      v[j] = val[i][p[i][j]];
    cal_val_2_rankScale(
        v, rk[i], rkIndex[i], rkV2[i], rkV2Index[i], rkScale[i], NN);
  }
  save_rankScale2(dir, rk, rkIndex, rkV2, rkV2Index, rkScale);
  return 0;
}

int save_rankScale2_val_mcp(const char* dir, const VVDouble& val,
    const VVNodeType& mcp0, const VVNodeType& mcp, const VVNodeType& mcpMcp)
{
  string DIR = dir;
  const size_t NC = mcp.size(), NP = mcp[0].size();
  VVNodeType mcpPcRank(NC), mcpPcRankIndex(NC), mcpPcRankV2(NC),
      mcpPcRankV2Index(NC);
  VVDouble mcpPcRankScale(NC);
  VVNodeType mcpNewPcRank(NC), mcpNewPcRankIndex(NC), mcpNewPcRankV2(NC),
      mcpNewPcRankV2Index(NC);
  VVDouble mcpNewPcRankScale(NC);
  VVNodeType mcpRemainPcRank(NC), mcpRemainPcRankIndex(NC),
      mcpRemainPcRankV2(NC), mcpRemainPcRankV2Index(NC);
  VVDouble mcpRemainPcRankScale(NC);
  for (size_t c = 0; c < NC; ++c) {
    cal_val_2_rankScale_p(val[c], &mcpMcp[c][0], mcpPcRank[c],
        mcpPcRankIndex[c], mcpPcRankV2[c], mcpPcRankV2Index[c],
        mcpPcRankScale[c], mcpMcp[c].size());
    for (size_t p = 0, i = 0; p < NP; ++p)
      if (mcp[c][p] != 0) {
        if (mcp0[c][p] == 0) { // New
          mcpNewPcRank[c].push_back(mcpPcRank[c][i]);
          mcpNewPcRankIndex[c].push_back(mcpPcRankIndex[c][i]);
          mcpNewPcRankV2[c].push_back(mcpPcRankV2[c][i]);
          mcpNewPcRankV2Index[c].push_back(mcpPcRankV2Index[c][i]);
          mcpNewPcRankScale[c].push_back(mcpPcRankScale[c][i]);
        } else { // remain
          mcpRemainPcRank[c].push_back(mcpPcRank[c][i]);
          mcpRemainPcRankIndex[c].push_back(mcpPcRankIndex[c][i]);
          mcpRemainPcRankV2[c].push_back(mcpPcRankV2[c][i]);
          mcpRemainPcRankV2Index[c].push_back(mcpPcRankV2Index[c][i]);
          mcpRemainPcRankScale[c].push_back(mcpPcRankScale[c][i]);
        }
        ++i;
      }
  }

  save_rankScale2((DIR + ".mcp.rankLess").c_str(), mcpPcRank, mcpPcRankIndex,
      mcpPcRankV2, mcpPcRankV2Index, mcpPcRankScale);
  save_rankScale2((DIR + ".new.rankLess").c_str(), mcpNewPcRank,
      mcpNewPcRankIndex, mcpNewPcRankV2, mcpNewPcRankV2Index,
      mcpNewPcRankScale);
  save_rankScale2((DIR + ".remain.rankLess").c_str(), mcpRemainPcRank,
      mcpRemainPcRankIndex, mcpRemainPcRankV2, mcpRemainPcRankV2Index,
      mcpRemainPcRankScale);

  return 0;
}

//*******************************************************
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
  ERROR_TEST(common_save(countryFilename, cChar, nc, '\n'));

  common_save_bool(productFilename, &pVal[0], 9999, '\n');

  return 0;
}

int filter_trade_name_OEC(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const NodeType YEAR1, const NodeType YEAR2)
{
  ifstream is(tradeFilename);
  ERROR_TEST(!is);
  const NodeType NC = 26 * 26 * 26, NP = 9999;
  NodeType nc = 0, np = 0, cVal[NC] = { 0 }, pVal[NP] = { 0 }, year;
  char origin[9], s[999];
  is.getline(s, 999);
  for (NodeType t, pd; is >> year >> origin >> pd >> s;) {
    if (year < YEAR1 || year >= YEAR2)
      continue;
    if (!cVal[t = common_atoi<NodeType>(origin)])
      cVal[t] = ++nc;
    if (!pVal[pd])
      pVal[pd] = ++np;
  }
  is.close();

  char cChar[300][4] = { { 0 } };
  for (NodeType i = 0, c = 0; i < NC && c < nc; ++i) {
    if (cVal[i]) {
      common_itoa(i, cChar[c], 'a', 26, 3);
      common_cstring_reverse(cChar[c++]);
    }
  }
  ERROR_TEST(common_save(countryFilename, cChar, nc, '\n'));

  ERROR_TEST(common_save_bool(productFilename, &pVal[0], 9999, '\n'));

  return 0;
}

// count world
int filter_trade_name_NBERUN_wtf(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const char* countryFilename0, const char* productFilename0)
{
  if (tradeFilename == NULL || tradeFilename[0] == '\0') {
    ERROR();
    return -1;
  }
  ifstream is(tradeFilename);
  if (!is) {
    ERROR();
    return -1;
  }
  VString cVal, pVal;
  if (countryFilename0 == NULL)
    countryFilename0 = countryFilename;
  if (countryFilename0 != NULL && countryFilename0[0] != '\0')
    INFORM_TEST(0 != common_read1_0(countryFilename0, cVal));
  if (productFilename0 == NULL)
    productFilename0 = productFilename;
  if (productFilename0 != NULL && productFilename0[0] != '\0')
    INFORM_TEST(0 != common_read1_0(productFilename0, pVal));
  typedef char CS[99];
  CS node, year, importer, exporter, unit, dot, value, quantity;
  string icode, ecode, sitc4;
  char s[999];
  for (is.getline(s, 999); is >> node >> year >> icode >> importer >> ecode
       >> exporter >> sitc4 >> unit >> dot >> value >> quantity;) {
    if (icode != "100000" || ecode == "100000" || sitc4 == "0") // World
      continue;
    if (ecode.length() != 6 || sitc4.length() != 4) {
      ERROR(node, "\t", ecode, "\t", sitc4, "\t", tradeFilename);
      return -1;
    }
    if (find(cVal.begin(), cVal.end(), ecode) == cVal.end())
      cVal.push_back(ecode);
    if (find(pVal.begin(), pVal.end(), sitc4) == pVal.end())
      pVal.push_back(sitc4);
  }
  is.close();
  sort(cVal.begin(), cVal.end());
  ERROR_TEST(common_save1(countryFilename, cVal, '\n'));
  sort(pVal.begin(), pVal.end());
  ERROR_TEST(common_save1(productFilename, pVal, '\n'));
  return 0;
}

// sum all country
int filter_trade_name_NBERUN_wtf2(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const char* countryFilename0, const char* productFilename0)
{
  if (tradeFilename == NULL || tradeFilename[0] == '\0') {
    ERROR();
    return -1;
  }
  ifstream is(tradeFilename);
  if (!is) {
    ERROR();
    return -1;
  }
  VString cVal, pVal;
  if (countryFilename0 == NULL)
    countryFilename0 = countryFilename;
  if (countryFilename0 != NULL && countryFilename0[0] != '\0')
    INFORM_TEST(0 != common_read1_0(countryFilename0, cVal));
  if (productFilename0 == NULL)
    productFilename0 = productFilename;
  if (productFilename0 != NULL && productFilename0[0] != '\0')
    INFORM_TEST(0 != common_read1_0(productFilename0, pVal));
  typedef char CS[99];
  CS node, year, importer, exporter, unit, dot, value, quantity;
  string icode, ecode, sitc4;
  char s[999];
  for (is.getline(s, 999); is >> node >> year >> icode >> importer >> ecode
       >> exporter >> sitc4 >> unit >> dot >> value >> quantity;) {
    if (icode == "100000" || ecode == "100000" || sitc4 == "0") // World
      continue;
    if (ecode.length() != 6 || sitc4.length() != 4) {
      ERROR(node, "\t", ecode, "\t", sitc4, "\t", tradeFilename);
      return -1;
    }
    if (find(cVal.begin(), cVal.end(), ecode) == cVal.end())
      cVal.push_back(ecode);
    if (find(pVal.begin(), pVal.end(), sitc4) == pVal.end())
      pVal.push_back(sitc4);
  }
  is.close();
  sort(cVal.begin(), cVal.end());
  ERROR_TEST(common_save1(countryFilename, cVal, '\n'));
  sort(pVal.begin(), pVal.end());
  ERROR_TEST(common_save1(productFilename, pVal, '\n'));
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

int save_export_data(const char* s, VVDouble expts)
{
  FILE* fp = fopen(s, "w");
  if (NULL == fp) {
    ERROR();
    return -1;
  }
  for (NodeType i = 0; i < expts.size(); ++i) {
    if (expts[i][0] <= 0.001)
      fprintf(fp, "0");
    else
      fprintf(fp, "%.2f", expts[i][0]);
    for (NodeType j = 1; j < expts[i].size(); ++j)
      if (expts[i][j] <= 0.001)
        fprintf(fp, "\t0");
      else
        fprintf(fp, "[t%.2f", expts[i][j]);
    fprintf(fp, "\n");
  }
  fclose(fp);
  return 0;
}

int filter_sum_trade(const char* tradeFilename, const char* countryFilename,
    const char* productFilename, const char* dirSave)
{
  VNodeType cVal(26 * 26 * 26, 0);
  NodeType NC = 0;
  read_country_names(countryFilename, NC, cVal);
  VNodeType pVal(9999, 0);
  NodeType NP = 0;
  read_product_names(productFilename, NP, pVal);
  cout << NC << "\t" << NP << endl;

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
        // ERROR_TEST(common_save2(s, expts));
        ERROR_TEST(save_export_data(s, expts));
        expts.assign(NC, VDouble(NP, 0));
        expts[cVal[common_atoi<size_t>(origin)]][pVal[pd]] = v;
        year0 = year;
      } else { // year==year0
        expts[cVal[common_atoi<size_t>(origin)]][pVal[pd]] += v;
      }
    }
    cout << l << "\t" << year0 << endl;
    sprintf(s, "%s%u.export.txt", dirSave, year0);
    ERROR_TEST(common_save2(s, expts));
    fclose(fp);
  }

  return 0;
}

int filter_sum_trade_OEC(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const char* dirSave, const NodeType YEAR1, const NodeType YEAR2)
{
  VNodeType cVal(26 * 26 * 26, 0);
  NodeType NC = 0;
  read_country_names(countryFilename, NC, cVal);
  VNodeType pVal(9999, 0);
  NodeType NP = 0;
  read_product_names(productFilename, NP, pVal);

  VVLinkType expts(NC, VLinkType(NP, 0));
  ifstream is(tradeFilename);
  if (!is) {
    ERROR();
    return -1;
  }
  char origin[4], s[999];
  string name = dirSave;
  NodeType year, pd, year0 = YEAR1;
  LinkType l = 1;
  is.getline(s, 999);
  for (double v; is >> year >> origin >> pd >> v; ++l) {
    if (YEAR1 > year || year >= YEAR2)
      continue;
    if (year < year0) {
      ERROR();
    } else {
      if (year > year0) {
        INFORM(l, "\t", year0);
        ERROR_TEST(common_save2(
            (name + to_string(year0) + ".export.txt").c_str(), expts));
        expts.assign(NC, VLinkType(NP, 0));
        year0 = year;
      }
      size_t c = cVal[common_atoi<size_t>(origin)], p = pVal[pd];
      INFORM_TEST(expts[c][p] != 0);
      expts[c][p] = v;
    }
  }
  INFORM(l, "\t", year0);
  ERROR_TEST(
      common_save2((name + to_string(year0) + ".export.txt").c_str(), expts));
  is.close();

  return 0;
}

int filter_sum_trade_NBER_wtf(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const char* saveName)
{
  VString cVal, pVal;
  ERROR_TEST(common_read1_0(countryFilename, cVal));
  ERROR_TEST(common_read1_0(productFilename, pVal));
  const NodeType NC = cVal.size(), NP = pVal.size();
  cout << NC << "\t" << NP << endl;

  VVDouble expts(NC, VDouble(NP, 0));
  ifstream is(tradeFilename);
  ERROR_TEST(!is);
  typedef char CS[99];
  CS node, year, importer, exporter, unit, dot, quantity;
  char s[999];
  string icode, ecode, sitc4;
  double value;
  is.getline(s, 999);
  for (VStringItr c, p; is >> node >> year >> icode >> importer >> ecode
       >> exporter >> sitc4 >> unit >> dot >> value >> quantity;) {
    if (icode != "100000" || ecode == "100000" || sitc4 == "0") // World
      continue;
    c = find(cVal.begin(), cVal.end(), ecode);
    p = find(pVal.begin(), pVal.end(), sitc4);
    if (c == cVal.end() || p == pVal.end()) {
      INFORM();
      continue;
    }
    expts[c - cVal.begin()][p - pVal.begin()] += value;
  }
  is.close();
  ofstream os(saveName);
  ERROR_TEST(!os);
  os << fixed << setprecision(3);
  ERROR_TEST(common_save2(os, expts));
  os.close();

  return 0;
}

int filter_sum_trade_NBER_wtf2(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const char* saveName)
{
  VString cVal, pVal;
  ERROR_TEST(common_read1_0(countryFilename, cVal));
  ERROR_TEST(common_read1_0(productFilename, pVal));
  const NodeType NC = cVal.size(), NP = pVal.size();

  VVDouble expts(NC, VDouble(NP, 0));
  ifstream is(tradeFilename);
  ERROR_TEST(!is);
  typedef char CS[99];
  CS node, year, importer, exporter, unit, dot, quantity;
  char s[999];
  string icode, ecode, sitc4;
  double value;
  is.getline(s, 999);
  for (size_t c, p; is >> node >> year >> icode >> importer >> ecode
       >> exporter >> sitc4 >> unit >> dot >> value >> quantity;) {
    if (icode == "100000" || ecode == "100000" || sitc4 == "0") // World
      continue;
    c = find(cVal.begin(), cVal.end(), ecode) - cVal.begin();
    p = find(pVal.begin(), pVal.end(), sitc4) - pVal.begin();
    expts[c][p] += value;
  }
  is.close();
  ERROR_TEST(common_save2(saveName, expts));

  return 0;
}

int filter_export_gdp_country_name(
    const char* exportNames, const char* gdpNames, const char* savePrefix)
{
  VString vept, vgdp, same, diffGdp, diffEpt;
  ERROR_TEST(common_read_VString(exportNames, vept));
  ERROR_TEST(common_read_VString(gdpNames, vgdp));
  VStringCItr ie, ig;
  for (ie = vept.begin(); ie != vept.end(); ++ie) {
    for (ig = vgdp.begin(); ig != vgdp.end(); ++ig)
      if (*ig == *ie)
        break;
    if (ig != vgdp.end())
      same.push_back(*ie);
    else
      diffEpt.push_back(*ie);
  }
  for (ig = vgdp.begin(); ig != vgdp.end(); ++ig) {
    for (ie = vept.begin(); ie != vept.end(); ++ie)
      if (*ie == *ig)
        break;
    if (ie == vept.end())
      diffGdp.push_back(*ig);
  }
  string s = savePrefix;
  ERROR_TEST(common_save_VString((s + ".same.txt").c_str(), same));
  ERROR_TEST(common_save_VString((s + ".diff.gdp.txt").c_str(), diffGdp));
  ERROR_TEST(common_save_VString((s + ".diff.trade.txt").c_str(), diffEpt));
  return 0;
}

int filter_index_same_all(const char* namesFull, const char* sameAll)
{
  {
    VString vept, veptAll;
    string s = namesFull;
    ERROR_TEST(common_read_VString((s + ".export.txt").c_str(), veptAll));
    ERROR_TEST(common_read_VString((s + ".same.common.txt").c_str(), vept));
    ERROR_TEST(common_read_VString((s + ".same.export.txt").c_str(), vept));
    VNodeType cIndex;
    for (NodeType i = 0, j; i < vept.size(); ++i) {
      for (j = 0; j < veptAll.size(); ++j)
        if (vept[i] == veptAll[j])
          break;
      if (j < veptAll.size())
        cIndex.push_back(j);
      else
        ERROR(vept[i]);
    }
    s = sameAll;
    ERROR_TEST(common_save1((s + ".export.txt").c_str(), cIndex, '\n'));
  }

  {
    VString vgdp, vgdpAll;
    string s = namesFull;
    ERROR_TEST(common_read_VString((s + ".gdp.txt").c_str(), vgdpAll));
    ERROR_TEST(common_read_VString((s + ".same.common.txt").c_str(), vgdp));
    ERROR_TEST(common_read_VString((s + ".same.gdp.txt").c_str(), vgdp));
    VNodeType cIndex;
    for (NodeType i = 0, j; i < vgdp.size(); ++i) {
      for (j = 0; j < vgdpAll.size(); ++j)
        if (vgdp[i] == vgdpAll[j])
          break;
      if (j < vgdpAll.size())
        cIndex.push_back(j);
      else
        ERROR(vgdp[i]);
    }
    s = sameAll;
    ERROR_TEST(common_save1((s + ".gdp.txt").c_str(), cIndex, '\n'));
  }
  return 0;
}

int filter_index_same_all_OEC(const char* namesFull)
{
  VString c, cept, cgdp;
  string s = namesFull;
  s += ".common";
  ERROR_TEST(common_read_VString((s + ".same.txt").c_str(), c));
  ERROR_TEST(common_read_VString((s + ".same.trade.txt").c_str(), cept));
  ERROR_TEST(common_read_VString((s + ".same.gdp.txt").c_str(), cgdp));
  for (VStringItr i = c.begin(); i != c.end(); i++) {
    cept.push_back(*i);
    cgdp.push_back(*i);
  }
  ERROR_TEST(common_save1((s + ".trade.txt").c_str(), cept, '\n'));
  ERROR_TEST(common_save1((s + ".gdp.txt").c_str(), cgdp, '\n'));

  s = namesFull;
  VString ept, gdp;
  ERROR_TEST(common_read_VString((s + ".trade.txt").c_str(), ept));
  ERROR_TEST(common_read_VString((s + ".gdp.txt").c_str(), gdp));
  VNodeType iept, igdp;
  for (size_t i = 0; i < cept.size(); i++) {
    auto t = find(ept.begin(), ept.end(), cept[i]);
    if (t != ept.end())
      iept.push_back(t - ept.begin());
  }
  ERROR_TEST(
      common_save1((s + ".common.trade.index.txt").c_str(), iept, '\n'));
  for (size_t i = 0; i < cgdp.size(); i++) {
    auto t = find(gdp.begin(), gdp.end(), cgdp[i]);
    if (t != gdp.end())
      igdp.push_back(t - gdp.begin());
  }
  ERROR_TEST(common_save1((s + ".common.gdp.index.txt").c_str(), igdp, '\n'));
  return 0;
}

int filter_index_same_not0_OEC(const char* namesFull, const char* countryNot0)
{
  VNodeType ep, gdp, epN0, e, eAll, g;
  string s = namesFull;
  ERROR_TEST(common_read1_0((s + ".trade.index.txt").c_str(), ep));
  ERROR_TEST(common_read1_0((s + ".gdp.index.txt").c_str(), gdp));
  ERROR_TEST(common_read1_0(countryNot0, epN0));
  for (size_t i = 0; i < ep.size(); ++i) {
    for (size_t j = 0; j < epN0.size(); ++j)
      if (ep[i] == epN0[j]) {
        e.push_back(j);
        eAll.push_back(ep[i]);
        g.push_back(gdp[i]);
        break;
      }
  }
  // ERROR_TEST(
  // common_save1((s + ".trade.index.not0.all.txt").c_str(), eAll, '\n'));
  ERROR_TEST(common_save1((s + ".trade.index.not0.txt").c_str(), e, '\n'));
  ERROR_TEST(common_save1((s + ".gdp.index.not0.txt").c_str(), g, '\n'));
  return 0;
}

int filter_index_gdp_0(const char* gdpFile, const char* cIndexFile)
{
  VVString gdp;
  ERROR_TEST(common_read2_0(gdpFile, gdp));
  VNodeType cIndex;
  for (NodeType i = 0, j; i < gdp.size(); ++i) {
    for (j = 0; j < gdp[i].size(); ++j)
      if (gdp[i][j] == "0")
        break;
    if (j >= gdp[i].size()) {
      cIndex.push_back(i);
    }
  }
  ERROR_TEST(common_save1(cIndexFile, cIndex, '\n'));
  return -1;
}

int filter_index_export_0_OEC(const char* epDIR, const char* cIndexFile,
    const char* pIndexFile, const char* countryFilename,
    const char* productFilename, const NodeType YEAR1, const NodeType YEAR2)
{
  const NodeType NYEAR = YEAR2 - YEAR1;
  vector<VVLinkType> ep(NYEAR);
  for (NodeType i = 0; i < NYEAR; ++i)
    ERROR_TEST(common_read2_0(
        (string(epDIR) + to_string(YEAR1 + i) + ".export.txt").c_str(),
        ep[i]));

  NodeType NC = ep[0].size(), NP = ep[0][0].size();
  VNodeType cIndex, pIndex;
  {
    // exclude: wld xx.
    if (countryFilename != NULL || countryFilename[0] != '\0') {
      VString cNames;
      ERROR_TEST(common_read1_0(countryFilename, cNames));
      for (NodeType ci = 0; ci < cNames.size(); ++ci)
        if (cNames[ci] != "wld"
            && !(cNames[ci][0] == 'x' && cNames[ci][1] == 'x'))
          cIndex.push_back(ci);
      INFORM(cIndex.size());
    } else {
      cIndex.resize(NC);
      for (NodeType ci = 0; ci < cIndex.size(); ++ci)
        cIndex[ci] = ci;
    }
  }
  {
    if (productFilename != NULL || productFilename[0] != '\0') {
      VNodeType pNames;
      ERROR_TEST(common_read1_0(productFilename, pNames));
      for (NodeType pi = 0; pi < pNames.size(); ++pi) {
        // if (pNames[pi] % 10 != 0) // exclude: xxx0
        pIndex.push_back(pi);
      }
      INFORM(pIndex.size());
    } else {
      pIndex.resize(NP);
      for (NodeType pi = 0; pi < pIndex.size(); ++pi)
        pIndex[pi] = pi;
    }
  }

  if (0)
    for (bool flag = true; flag;) {
      flag = false;

      for (NodeType ci = 0; ci < cIndex.size();) { // filter country
        NodeType c = cIndex[ci], i = 0;
        for (i = 0; i < NYEAR; ++i) {
          NodeType pi = 0;
          while (pi < pIndex.size() && ep[i][c][pIndex[pi]] <= 0)
            ++pi;
          if (pi >= pIndex.size())
            break;
        }
        if (i < NYEAR) {
          flag = true;
          cIndex[ci] = cIndex.back();
          cIndex.pop_back();
        } else
          ++ci;
      }

      for (NodeType pi = 0; pi < pIndex.size();) { // filter product
        NodeType p = pIndex[pi], i = 0;
        for (i = 0; i < NYEAR; ++i) {
          NodeType ci = 0;
          while (ci < cIndex.size() && ep[i][cIndex[ci]][p] <= 0)
            ++ci;
          if (ci >= cIndex.size())
            break;
        }
        if (i < NYEAR) {
          flag = true;
          pIndex[pi] = pIndex.back();
          pIndex.pop_back();
        } else
          ++pi;
      }

      if (flag)
        continue;
      break;

      if (0)
        for (NodeType ci = 0; ci < cIndex.size();) { // filter country
          NodeType c = cIndex[ci], i = 0;
          bool f1 = true, f2 = true, f3 = true, vFlag = false;
          { // cal f2
            NodeType pi = 0;
            while (pi < pIndex.size() && ep[i][c][pIndex[pi]] <= 0)
              ++pi;
            f2 = pi < pIndex.size();
          }
          for (i = 1; i < NYEAR; ++i) { // cal f3
            NodeType pi = 0;
            while (pi < pIndex.size() && ep[i][c][pIndex[pi]] <= 0)
              ++pi;
            f3 = pi < pIndex.size();
            if ((vFlag = f1 && !f2 && f3))
              break;
          }
          if (vFlag) {
            flag = true;
            cIndex[ci] = cIndex.back();
            cIndex.pop_back();
          } else
            ++ci;
        }

      for (NodeType pi = 0; pi < pIndex.size();) { // filter product
        NodeType p = pIndex[pi], i = 0;
        bool f1 = true, f2 = true, f3 = true, vFlag = false;
        { // cal f2
          NodeType ci = 0;
          while (ci < cIndex.size() && ep[i][cIndex[ci]][p] <= 0)
            ++ci;
          f2 = ci < cIndex.size();
        }
        for (i = 1; i < NYEAR; ++i) { // cal f3
          NodeType ci = 0;
          while (ci < cIndex.size() && ep[i][cIndex[ci]][p] <= 0)
            ++ci;
          f3 = ci < cIndex.size();
          if ((vFlag = f1 && !f2 && f3))
            break;
        }
        if (vFlag) {
          flag = true;
          pIndex[pi] = pIndex.back();
          pIndex.pop_back();
        } else
          ++pi;
      }
    }

  sort(cIndex.begin(), cIndex.end());
  ERROR_TEST(common_save1(cIndexFile, cIndex, '\n'));
  sort(pIndex.begin(), pIndex.end());
  ERROR_TEST(common_save1(pIndexFile, pIndex, '\n'));

  return 0;
}

int filter_index_export_0_NBER_wtf(const char* epDIR, const char* cIndexFile,
    const char* pIndexFile, const char* pIndexFileAll, const NodeType YEAR1,
    const NodeType YEAR2, const NodeType YEAR0)
{
  const NodeType NYEAR = YEAR2 - YEAR1;
  ERROR_TEST(YEAR1 > YEAR0 || YEAR0 > YEAR2);
  vector<VVDouble> ep(NYEAR);
  const double EP0 = 1e-5;
  string s = epDIR;
  for (NodeType year = YEAR1; year < YEAR2; ++year)
    ERROR_TEST(common_read2_0(
        (s + to_string(year) + ".export.txt").c_str(), ep[year - YEAR1]));

  NodeType NC = ep[0].size(), NP = ep[0][0].size();
  VNodeType cIndex(NC), pIndex;
  for (NodeType ci = 0; ci < cIndex.size(); ++ci)
    cIndex[ci] = ci;
  if (pIndexFileAll != NULL && pIndexFileAll[0] != '\0') {
    ERROR_TEST(common_read1_0(pIndexFileAll, pIndex));
    cout << pIndexFileAll << "\t" << pIndex.size() << endl;
  } else {
    pIndex.resize(NP);
    for (NodeType pi = 0; pi < pIndex.size(); ++pi)
      pIndex[pi] = pi;
  }

  for (bool flag = true; flag;) {
    flag = false;

    for (NodeType ci = 0; ci < cIndex.size();) { // filter country
      NodeType c = cIndex[ci], year = YEAR1;
      for (NodeType pi; year < YEAR2; ++year) {
        for (pi = 0;
             pi < pIndex.size() && ep[year - YEAR1][c][pIndex[pi]] <= EP0;
             ++pi)
          continue;
        if (pi >= pIndex.size()) {
          flag = true;
          cIndex[ci] = cIndex.back();
          cIndex.pop_back();
          break;
        }
      }
      if (year >= YEAR2)
        ++ci;
    }

    for (NodeType pi = 0; pi < pIndex.size();) { // filter product
      NodeType p = pIndex[pi], year = YEAR1;
      for (NodeType ci; year < YEAR2; ++year) {
        for (ci = 0;
             ci < cIndex.size() && ep[year - YEAR1][cIndex[ci]][p] <= EP0;
             ++ci)
          continue;
        if (ci >= cIndex.size()) {
          flag = true;
          pIndex[pi] = pIndex.back();
          pIndex.pop_back();
          break;
        }
      }
      if (year >= YEAR2)
        ++pi;
    }
    if (flag)
      continue;
    break;

    for (NodeType ci = 0; ci < cIndex.size();) { // filter country
      NodeType c = cIndex[ci];
      bool flag2 = false;
      for (NodeType pi = 0; pi < pIndex.size(); ++pi) {
        NodeType p = pIndex[pi];
        NodeType year = YEAR0;
        bool f1 = true, f2 = ep[year - YEAR1][c][p] <= EP0, f3 = true;
        for (year = YEAR0 + 1; year <= YEAR2; ++year) { // cal f3
          f3 = ep[year - YEAR1][c][p] <= EP0;
          if ((flag2 = f1 && !f2 && f3)) {
            flag = true;
            pIndex[pi] = pIndex.back();
            pIndex.pop_back();
            break;
          }
          f1 = f2;
          f2 = f3;
        }
        if (flag2)
          break;
      }
      if (!flag2)
        ++ci;
    }
  }

  sort(cIndex.begin(), cIndex.end());
  ERROR_TEST(common_save1(cIndexFile, cIndex, '\n'));
  sort(pIndex.begin(), pIndex.end());
  ERROR_TEST(common_save1(pIndexFile, pIndex, '\n'));

  return 0;
}

int filter_index_export_gdp(const char* gdpIndexFile0,
    const char* gdpIndexFile, const char* gdpIndexFile2,
    const char* exportIndexFile0, const char* exportIndexFile,
    const char* exportIndexFile2)
{
  VNodeType g0, g, g2, e0, e, e2;
  ERROR_TEST(common_read1_0(gdpIndexFile0, g0));
  ERROR_TEST(common_read1_0(gdpIndexFile, g));
  ERROR_TEST(common_read1_0(exportIndexFile0, e0));
  ERROR_TEST(common_read1_0(exportIndexFile, e));
  if (g0.size() != e0.size()) {
    ERROR();
    return -1;
  }
  NodeType n = g0.size();
  VNodeType cIndex(n, 0), id;
  for (NodeType i = 0; i < n; ++i)
    for (NodeType j = 0; j < g.size(); ++j) {
      if (g[j] == g0[i]) {
        ++cIndex[i];
        break;
      }
    }
  for (NodeType i = 0; i < n; ++i)
    for (NodeType j = 0; j < e.size(); ++j) {
      if (e[j] == e0[i]) {
        ++cIndex[i];
        break;
      }
    }
  for (NodeType i = 0; i < n; ++i)
    if (cIndex[i] == 2)
      id.push_back(i);
  ERROR_TEST(common_save1_p(gdpIndexFile2, &g0[0], &id[0], id.size(), '\n'));
  ERROR_TEST(
      common_save1_p(exportIndexFile2, &e0[0], &id[0], id.size(), '\n'));
  return 0;
}

int filter_data_export(const char* exportDIR, const char* countryIndexFile,
    const char* productIndexFile, const char* DATA_DIR, const NodeType YEAR1,
    const NodeType YEAR2)
{
  VNodeType cIndex, pIndex;
  ERROR_TEST(common_read1_0(countryIndexFile, cIndex));
  ERROR_TEST(common_read1_0(productIndexFile, pIndex));
  for (NodeType year = YEAR1; year < YEAR2; ++year) {
    VVString epts;
    string s0 = exportDIR;
    ERROR_TEST(common_read2_0(
        (string(exportDIR) + to_string(year) + ".export.txt").c_str(), epts));
    VVString epts2(cIndex.size());
    for (NodeType ci = 0; ci < cIndex.size(); ++ci)
      for (NodeType pi = 0; pi < pIndex.size(); ++pi)
        epts2[ci].push_back(epts[cIndex[ci]][pIndex[pi]]);
    ERROR_TEST(common_save2(
        (string(DATA_DIR) + to_string(year) + ".export.txt").c_str(), epts2));
  }
  return 0;
}

int filter_data(const char* gdpFile, const char* gdpIndexFile,
    const char* exportDIR, const char* countryIndexFile,
    const char* productIndexFile, const char* DATA_DIR)
{
  VVString gdp;
  ERROR_TEST(common_read2_0(gdpFile, gdp));
  VNodeType gIndex;
  ERROR_TEST(common_read1_0(gdpIndexFile, gIndex));
  VNodeType cIndex, pIndex;
  ERROR_TEST(common_read1_0(countryIndexFile, cIndex));
  ERROR_TEST(common_read1_0(productIndexFile, pIndex));
  const NodeType YEAR1 = 1995, YEAR2 = 2014, NYEAR = YEAR2 - YEAR1 + 1;
  for (NodeType i = 0; i < NYEAR; ++i) {
    string y;
    stringstream ss;
    ss << YEAR1 + i;
    y = ss.str();
    string s = DATA_DIR;
    VString g(gIndex.size());
    for (NodeType gi = 0; gi < gIndex.size(); ++gi)
      g[gi] = gdp[gIndex[gi]][i];
    ERROR_TEST(common_save1((s + y + ".gdp.txt").c_str(), g, '\n'));

    VVString epts;
    string s0 = exportDIR;
    ERROR_TEST(common_read2_0((s0 + y + ".export.txt").c_str(), epts));
    VVString epts2(cIndex.size());
    for (NodeType ci = 0; ci < cIndex.size(); ++ci)
      for (NodeType pi = 0; pi < pIndex.size(); ++pi)
        epts2[ci].push_back(epts[cIndex[ci]][pIndex[pi]]);
    ERROR_TEST(common_save2((s + y + ".export.txt").c_str(), epts2));
  }
  return 0;
}

// *******************************************************
#endif // ACT_FITNESS_COMPLEXITY
