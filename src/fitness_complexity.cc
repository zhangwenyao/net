#include "fitness_complexity.h"
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
    _ERR(common_save1(name, deg, '\n'));
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
    _ERR(common_save1(name, deg, '\n'));
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
// _ERR(common_save2(name, newScale));
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
    _ERR(common_save2(name, newRank));
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
    _ERR(common_save2(name, newRemainRank));
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
int fitness_complexity::trade_name(const char* tradeFilename,
    const char* countryFilename, const char* productFilename)
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
  _ERR(common_save(countryFilename, cChar, nc, '\n'));

  common_save_bool(productFilename, &pVal[0], 9999, '\n');

  return 0;
}

int fitness_complexity::trade_name_OEC(const char* tradeFilename,
    const char* cIsoFile, const char* cIso3cFile, const char* codeFile,
    const char* countryFilename, const char* productFilename,
    const NodeType YEAR1, const NodeType YEAR2)
{
  ifstream is(tradeFilename);
  _ERR(!is);
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
  _ERR(common_save(countryFilename, cChar, nc, '\n'));
  INFORM(nc);
  _ERR(common_save_bool(productFilename, &pVal[0], 9999, '\n'));
  NodeType _s = 0;
  common_total_bool(&pVal[0], 9999, _s);
  INFORM(_s);
  VNodeType cIso, code;
  VString cIso3c, c3c;
  _ERR(common_read1_0(cIsoFile, cIso));
  _ERR(common_read1_0(cIso3cFile, cIso3c));
  c3c.resize(nc);
  code.assign(nc, 0);
  for (NodeType i = 0; i < nc; ++i) {
    c3c[i] = cChar[i];
    transform(c3c[i].begin(), c3c[i].end(), c3c[i].begin(), ::toupper);
    for (NodeType j = 0; j < cIso3c.size(); ++j)
      if (c3c[i] == cIso3c[j])
        code[i] = cIso[j];
  }
  _ERR(common_save1(codeFile, code, '\n'));
  return 0;
}

// count world
int fitness_complexity::trade_name_NBERUN_wtf(const char* tradeFilename,
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
    _INF(0 != common_read1_0(countryFilename0, cVal));
  if (productFilename0 == NULL)
    productFilename0 = productFilename;
  if (productFilename0 != NULL && productFilename0[0] != '\0')
    _INF(0 != common_read1_0(productFilename0, pVal));
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
  _ERR(common_save1(countryFilename, cVal, '\n'));
  sort(pVal.begin(), pVal.end());
  _ERR(common_save1(productFilename, pVal, '\n'));
  return 0;
}

// sum all country
int fitness_complexity::trade_name_NBERUN_wtf2(const char* tradeFilename,
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
    _INF(0 != common_read1_0(countryFilename0, cVal));
  if (productFilename0 == NULL)
    productFilename0 = productFilename;
  if (productFilename0 != NULL && productFilename0[0] != '\0')
    _INF(0 != common_read1_0(productFilename0, pVal));
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
  _ERR(common_save1(countryFilename, cVal, '\n'));
  sort(pVal.begin(), pVal.end());
  _ERR(common_save1(productFilename, pVal, '\n'));
  return 0;
}

int fitness_complexity::read_country_names(
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

int fitness_complexity::read_product_names(
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

int fitness_complexity::sum_trade(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const char* dirSave)
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
        // _ERR(common_save2(s, expts));
        _ERR(save_export_data(s, expts));
        expts.assign(NC, VDouble(NP, 0));
        expts[cVal[common_atoi<size_t>(origin)]][pVal[pd]] = v;
        year0 = year;
      } else { // year==year0
        expts[cVal[common_atoi<size_t>(origin)]][pVal[pd]] += v;
      }
    }
    cout << l << "\t" << year0 << endl;
    sprintf(s, "%s%u.export.txt", dirSave, year0);
    _ERR(common_save2(s, expts));
    fclose(fp);
  }

  return 0;
}

int fitness_complexity::sum_trade_OEC(const char* tradeFilename,
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
        _ERR(common_save2((name + to_string(year0) + ".txt").c_str(), expts));
        expts.assign(NC, VLinkType(NP, 0));
        year0 = year;
      }
      size_t c = cVal[common_atoi<size_t>(origin)], p = pVal[pd];
      _INF(expts[c][p] != 0);
      expts[c][p] = v;
    }
  }
  INFORM(l, "\t", year0);
  _ERR(common_save2((name + to_string(year0) + ".txt").c_str(), expts));
  is.close();

  return 0;
}

int fitness_complexity::trade_gdp_country_code_OEC(
    const char* eCodeFile, const char* gCodeFile, const char* codeFile)
{
  VNodeType eCode, gCode, code;
  _ERR(common_read1_0(eCodeFile, eCode));
  _ERR(common_read1_0(gCodeFile, gCode));
  sort(eCode.begin(), eCode.end());
  sort(gCode.begin(), gCode.end());
  common_find_common(eCode, gCode, code);
  _ERR(common_save1(codeFile, code, '\n'));
  INFORM(code.size());
  return 0;
}

int fitness_complexity::sum_trade_NBER_wtf(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const char* saveName)
{
  VString cVal, pVal;
  _ERR(common_read1_0(countryFilename, cVal));
  _ERR(common_read1_0(productFilename, pVal));
  const NodeType NC = cVal.size(), NP = pVal.size();
  cout << NC << "\t" << NP << endl;

  VVDouble expts(NC, VDouble(NP, 0));
  ifstream is(tradeFilename);
  _ERR(!is);
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
  _ERR(!os);
  os << fixed << setprecision(3);
  _ERR(common_save2(os, expts));
  os.close();

  return 0;
}

int fitness_complexity::sum_trade_NBER_wtf2(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const char* saveName)
{
  VString cVal, pVal;
  _ERR(common_read1_0(countryFilename, cVal));
  _ERR(common_read1_0(productFilename, pVal));
  const NodeType NC = cVal.size(), NP = pVal.size();

  VVDouble expts(NC, VDouble(NP, 0));
  ifstream is(tradeFilename);
  _ERR(!is);
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
  _ERR(common_save2(saveName, expts));

  return 0;
}

int fitness_complexity::export_gdp_country_name(const char* exportName,
    const char* gdpName, const char* commonName, const char* diffExportname,
    const char* diffGdpName)
{
  VString vept, vgdp, same, diffGdp, diffEpt;
  _ERR(common_read_VString(exportName, vept));
  _ERR(common_read_VString(gdpName, vgdp));
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
  _ERR(common_save_VString(commonName, same));
  _ERR(common_save_VString(diffGdpName, diffGdp));
  _ERR(common_save_VString(diffExportname, diffEpt));
  return 0;
}

int fitness_complexity::trade_gdp_country_code(const char* tradeName,
    const char* gdpName, const char* commonName, const char* diffTradeName,
    const char* diffGdpName)
{
  VUnsigned vept, vgdp, same, diffGdp, diffEpt;
  _ERR(common_read1_0(tradeName, vept));
  _ERR(common_read1_0(gdpName, vgdp));
  VUnsignedCItr ie, ig;
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
  sort(same.begin(), same.end());
  _ERR(common_save1(commonName, same, '\n'));
  sort(diffGdp.begin(), diffGdp.end());
  _ERR(common_save1(diffGdpName, diffGdp, '\n'));
  sort(diffEpt.begin(), diffEpt.end());
  _ERR(common_save1(diffTradeName, diffEpt, '\n'));
  return 0;
}

int fitness_complexity::index_same_all(
    const char* namesFull, const char* sameAll)
{
  {
    VString vept, veptAll;
    string s = namesFull;
    _ERR(common_read_VString((s + ".export.txt").c_str(), veptAll));
    _ERR(common_read_VString((s + ".same.common.txt").c_str(), vept));
    _ERR(common_read_VString((s + ".same.export.txt").c_str(), vept));
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
    _ERR(common_save1((s + ".export.txt").c_str(), cIndex, '\n'));
  }

  {
    VString vgdp, vgdpAll;
    string s = namesFull;
    _ERR(common_read_VString((s + ".gdp.txt").c_str(), vgdpAll));
    _ERR(common_read_VString((s + ".same.common.txt").c_str(), vgdp));
    _ERR(common_read_VString((s + ".same.gdp.txt").c_str(), vgdp));
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
    _ERR(common_save1((s + ".gdp.txt").c_str(), cIndex, '\n'));
  }
  return 0;
}

int fitness_complexity::index_same_all_OEC(const char* tradeName,
    const char* gdpName, const char* sameName, const char* sameTradeName,
    const char* sameGdpName, const char* sameTradeAllName,
    const char* sameGdpAllName, const char* sameTradeAllIndexName,
    const char* sameGdpAllIndexName)
{
  VString ept, gdp;
  _ERR(common_read_VString(tradeName, ept));
  _ERR(common_read_VString(gdpName, gdp));

  VString c, cept, cgdp;
  _ERR(common_read_VString(sameName, c));
  _ERR(common_read_VString(sameTradeName, cept));
  _ERR(common_read_VString(sameGdpName, cgdp));
  for (VStringItr i = c.begin(); i != c.end(); i++) {
    cept.push_back(*i);
    cgdp.push_back(*i);
  }
  _ERR(common_save1(sameTradeAllName, cept, '\n'));
  _ERR(common_save1(sameGdpAllName, cgdp, '\n'));

  VNodeType iept, igdp;
  for (size_t i = 0; i < cept.size(); i++) {
    auto t = find(ept.begin(), ept.end(), cept[i]);
    if (t != ept.end())
      iept.push_back(t - ept.begin());
  }
  _ERR(common_save1(sameTradeAllIndexName, iept, '\n'));
  for (size_t i = 0; i < cgdp.size(); i++) {
    auto t = find(gdp.begin(), gdp.end(), cgdp[i]);
    if (t != gdp.end())
      igdp.push_back(t - gdp.begin());
  }
  _ERR(common_save1(sameGdpAllIndexName, igdp, '\n'));
  return 0;
}

int fitness_complexity::index_same_not0_OEC(const char* sameTradeAllIndexName,
    const char* sameGdpAllIndexName, const char* tradeNot0IndexName,
    const char* sameTradeNot0IndexName, const char* sameGdpNot0IndexName)
{
  VNodeType ep, gdp, epN0, e, eAll, g;
  _ERR(common_read1_0(sameTradeAllIndexName, ep));
  _ERR(common_read1_0(sameGdpAllIndexName, gdp));
  _ERR(common_read1_0(tradeNot0IndexName, epN0));
  for (size_t i = 0; i < ep.size(); ++i) {
    for (size_t j = 0; j < epN0.size(); ++j)
      if (ep[i] == epN0[j]) {
        e.push_back(j);
        eAll.push_back(ep[i]);
        g.push_back(gdp[i]);
        break;
      }
  }
  _ERR(common_save1(sameTradeNot0IndexName, e, '\n'));
  _ERR(common_save1(sameGdpNot0IndexName, g, '\n'));
  return 0;
}

int fitness_complexity::index_gdp_0(
    const char* gdpFile, const char* cIndexFile)
{
  VVString gdp;
  _ERR(common_read2_0(gdpFile, gdp));
  VNodeType cIndex;
  for (NodeType i = 0, j; i < gdp.size(); ++i) {
    for (j = 0; j < gdp[i].size(); ++j)
      if (gdp[i][j] == "0")
        break;
    if (j >= gdp[i].size()) {
      cIndex.push_back(i);
    }
  }
  _ERR(common_save1(cIndexFile, cIndex, '\n'));
  return -1;
}

int fitness_complexity::export_gdp_0_OEC(const char* epDIR,
    const NodeType YEAR1, const NodeType YEAR2, const char* p4dFile,
    const char* cCodeFile, const char* c3cCodeFile, const char* gFile,
    const NodeType YEAR0, const char* gCodeFile, const char* egCodeFile,
    const char* eg0CodeFile, const char* eg0P4dFile, const LinkType filter)
{
  const NodeType NYEAR = YEAR2 - YEAR1;
  VVLinkType epAll[NYEAR], gdpAll;
  VLinkType gdp;
  VString c3cCode;
  VNodeType p4d, cCode, gCode, egCode, eg0Code, egc0Code;

  for (NodeType i = 0; i < NYEAR; ++i)
    _ERR(common_read2_0(
        (string(epDIR) + to_string(YEAR1 + i) + ".txt").c_str(), epAll[i]));
  _ERR(common_read1_0(p4dFile, p4d));
  _ERR(common_read1_0(cCodeFile, cCode));
  _ERR(common_read1_0(c3cCodeFile, c3cCode));
  _ERR(common_read2_0(gFile, gdpAll));
  _ERR(common_read1_0(gCodeFile, gCode));
  _ERR(common_read1_0(egCodeFile, egCode));

  VNodeType cIndex;
  // exclude: wld xx.
  for (NodeType ci = 0; ci < c3cCode.size(); ++ci) {
    if (!common_find(egCode, cCode[ci]))
      continue;
    if (c3cCode[ci] == "wld"
        || (c3cCode[ci][0] == 'x' && c3cCode[ci][1] == 'x'))
      continue;
    cIndex.push_back(ci);
  }
  //INFORM(cIndex.size());
  // exclude: gdp <= 0
  for (NodeType ci = 0; ci < cIndex.size();) {
    bool flag0 = false;
    NodeType c = cIndex[ci];
    auto gi = find(gCode.begin(), gCode.end(), cCode[c]) - gCode.begin();
    for (NodeType yi = YEAR1 - YEAR0; yi < YEAR2 - YEAR0; ++yi) {
      if (gdpAll[gi][yi] <= 0) {
        flag0 = true;
        //INFORM(c, " ", c3cCode[c], " ", cCode[c], "\t", gi, " ", gCode[gi],
        //"\n", gdpAll[gi][yi]);
        break;
      }
    }
    if (flag0) {
      cIndex[ci] = cIndex.back();
      cIndex.pop_back();
    } else
      ++ci;
  }
  //INFORM(cIndex.size());

  VNodeType pIndex;
  // exclude: ...0
  for (NodeType pi = 0; pi < p4d.size(); ++pi) {
    //if (p4d[pi] % 10 != 0)
      pIndex.push_back(pi);
  }
  //INFORM(pIndex.size());

  for (bool flag = true; flag;) {
    flag = false;

    for (NodeType ci = 0; ci < cIndex.size();) { // filter country
      bool flag0 = false;
      NodeType c = cIndex[ci];
      for (NodeType yi = 0; yi < NYEAR; ++yi) {
        flag0 = true;
        for (NodeType pi = 0; pi < pIndex.size(); ++pi) {
          NodeType p = pIndex[pi];
          if (epAll[yi][c][p] > 0) {
            flag0 = false;
            break;
          }
        }
        if (flag0) {
          // INFORM(yi, "\t", cIndex[ci], "\t", cCode[cIndex[ci]]);
          break;
        }
      }
      if (flag0) {
        cIndex[ci] = cIndex.back();
        cIndex.pop_back();
        flag = true;
      } else
        ++ci;
    }

    for (NodeType pi = 0; pi < pIndex.size();) { // filter product
      bool flag0 = false;
      NodeType p = pIndex[pi];
      for (NodeType yi = 0; yi < NYEAR; ++yi) {
        LinkType s = 0;
        for (NodeType ci = 0; ci < cIndex.size(); ++ci) {
          NodeType c = cIndex[ci];
          s += epAll[yi][c][p];
        }
        if (s <= filter) {
          flag0 = true;
          //INFORM(yi, "\t", pIndex[pi], "\t", p4d[pIndex[pi]], "\t", s);
          break;
        }
      }
      if (flag0) {
        pIndex[pi] = pIndex.back();
        pIndex.pop_back();
        flag = true;
      } else
        ++pi;
    }
  }

  for (auto i = cIndex.begin(); i != cIndex.end(); ++i)
    eg0Code.push_back(cCode[*i]);
  sort(eg0Code.begin(), eg0Code.end());
  _ERR(common_save1(eg0CodeFile, eg0Code, '\n'));
  INFORM(cIndex.size());
  sort(pIndex.begin(), pIndex.end());
  _ERR(common_save1_p(eg0P4dFile, &p4d[0], &pIndex[0], pIndex.size(), '\n'));
  INFORM(pIndex.size());

  return 0;
}

int fitness_complexity::population_OEC(const char* pFile,
    const NodeType YEAR_FILTER, const char* pIsoCodeFile,
    const char* c0IsoCodeFile, const LinkType filter, const char* pfFile)
{
  VVLinkType populations;
  VNodeType pIsoCode, c0IsoCode;
  _ERR(common_read2_0(pFile, populations));
  _ERR(common_read1_0(pIsoCodeFile, pIsoCode));
  _ERR(common_read1_0(c0IsoCodeFile, c0IsoCode));
  const NodeType NC = pIsoCode.size();
  VNodeType cIndex;
  for (NodeType ci = 0; ci < NC; ++ci) {
    if (common_find(c0IsoCode, pIsoCode[ci])
        && populations[ci][YEAR_FILTER] >= filter)
      cIndex.push_back(ci);

    // if (common_find(c0IsoCode, pIsoCode[ci])
    //&& populations[ci][2015-1950] >= filter)
    // cIndex.push_back(ci);

    // LinkType p = 0;
    // for (NodeType yi = YEAR_FILTER - 2; yi <= YEAR_FILTER; ++yi)
    // p += populations[ci][yi];
    // if (common_find(c0IsoCode, pIsoCode[ci]) && p >= filter * 3)
    // pIndex.push_back(ci);

    // bool flag = true;
    // for (NodeType yi = YEAR_FILTER - 2; yi <= YEAR_FILTER; ++yi)
    // if (populations[ci][yi] < filter) {
    // flag = false;
    // break;
    //}
    // if (flag && common_find(c0IsoCode, pIsoCode[ci]))
    // cIndex.push_back(ci);
  }
  _ERR(common_save1_p(pfFile, &pIsoCode[0], &cIndex[0], cIndex.size(), '\n'));
  INFORM(cIndex.size());
  return 0;
}

int fitness_complexity::trade_OEC(const char* epDir,
    const NodeType YEAR_FILTER1, const NodeType YEAR_FILTER2,
    const char* cIsoCodeFile, const char* c0IsoCodeFile,
    const LinkType filter, const char* cfFile)
{
  const NodeType NY = YEAR_FILTER2 - YEAR_FILTER1 + 1;
  VVLinkType ep[NY];
  VNodeType cIsoCode, c0IsoCode;
  for (NodeType yi = 0; yi < NY; ++yi)
    _ERR(common_read2_0(
        (string(epDir) + to_string(YEAR_FILTER1 + yi) + ".txt").c_str(),
        ep[yi]));
  _ERR(common_read1_0(cIsoCodeFile, cIsoCode));
  _ERR(common_read1_0(c0IsoCodeFile, c0IsoCode));
  const NodeType NC = cIsoCode.size();
  VNodeType cIndex;
  for (NodeType ci = 0; ci < NC; ++ci) {
    if (!common_find(c0IsoCode, cIsoCode[ci]))
      continue;
    LinkType e = 0;
    for (NodeType yi = 0; yi < NY; ++yi) {
      for (NodeType pi = 0; pi < ep[yi][ci].size(); ++pi)
        e += ep[yi][ci][pi];
    }
    // 剔除进出口小于 1E6 的国家 & Iraq(368),Chad(148),Macau(446)
    // if (e >= filter * NY && cIsoCode[ci] != 368 && cIsoCode[ci] != 148
    //&& cIsoCode[ci] != 446)
    if (e >= filter * NY)
      cIndex.push_back(ci);
  }
  _ERR(common_save1_p(cfFile, &cIsoCode[0], &cIndex[0], cIndex.size(), '\n'));
  INFORM(cIndex.size());
  return 0;
}

int fitness_complexity::index_export_0_OEC(const char* epDIR,
    const char* cIndexFile, const char* pIndexFile,
    const char* countryFilename, const char* productFilename,
    const NodeType YEAR1, const NodeType YEAR2)
{
  const NodeType NYEAR = YEAR2 - YEAR1;
  vector<VVLinkType> ep(NYEAR);
  for (NodeType i = 0; i < NYEAR; ++i)
    _ERR(common_read2_0(
        (string(epDIR) + to_string(YEAR1 + i) + ".txt").c_str(), ep[i]));

  NodeType NC = ep[0].size(), NP = ep[0][0].size();
  VNodeType cIndex, pIndex;
  {
    // exclude: wld xx.
    if (countryFilename != NULL || countryFilename[0] != '\0') {
      VString cNames;
      _ERR(common_read1_0(countryFilename, cNames));
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
      _ERR(common_read1_0(productFilename, pNames));
      for (NodeType pi = 0; pi < pNames.size(); ++pi) {
        if (pNames[pi] % 10 != 0) // exclude: xxx0
          pIndex.push_back(pi);
      }
      INFORM(pIndex.size());
    } else {
      pIndex.resize(NP);
      for (NodeType pi = 0; pi < pIndex.size(); ++pi)
        pIndex[pi] = pi;
    }
  }

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
  _ERR(common_save1(cIndexFile, cIndex, '\n'));
  sort(pIndex.begin(), pIndex.end());
  _ERR(common_save1(pIndexFile, pIndex, '\n'));

  return 0;
}

int fitness_complexity::index_export_0_NBER_wtf(const char* epDIR,
    const char* cIndexFile, const char* pIndexFile, const char* pIndexFileAll,
    const NodeType YEAR1, const NodeType YEAR2, const NodeType YEAR0)
{
  const NodeType NYEAR = YEAR2 - YEAR1;
  _ERR(YEAR1 > YEAR0 || YEAR0 > YEAR2);
  vector<VVDouble> ep(NYEAR);
  const double EP0 = 1e-5;
  string s = epDIR;
  for (NodeType year = YEAR1; year < YEAR2; ++year)
    _ERR(common_read2_0(
        (s + to_string(year) + ".export.txt").c_str(), ep[year - YEAR1]));

  NodeType NC = ep[0].size(), NP = ep[0][0].size();
  VNodeType cIndex(NC), pIndex;
  for (NodeType ci = 0; ci < cIndex.size(); ++ci)
    cIndex[ci] = ci;
  if (pIndexFileAll != NULL && pIndexFileAll[0] != '\0') {
    _ERR(common_read1_0(pIndexFileAll, pIndex));
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
  _ERR(common_save1(cIndexFile, cIndex, '\n'));
  sort(pIndex.begin(), pIndex.end());
  _ERR(common_save1(pIndexFile, pIndex, '\n'));

  return 0;
}

int fitness_complexity::index_export_gdp(const char* gdpIndexFile0,
    const char* gdpIndexFile, const char* gdpIndexFile2,
    const char* exportIndexFile0, const char* exportIndexFile,
    const char* exportIndexFile2)
{
  VNodeType g0, g, g2, e0, e, e2;
  _ERR(common_read1_0(gdpIndexFile0, g0));
  _ERR(common_read1_0(gdpIndexFile, g));
  _ERR(common_read1_0(exportIndexFile0, e0));
  _ERR(common_read1_0(exportIndexFile, e));
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
  _ERR(common_save1_p(gdpIndexFile2, &g0[0], &id[0], id.size(), '\n'));
  _ERR(common_save1_p(exportIndexFile2, &e0[0], &id[0], id.size(), '\n'));
  return 0;
}

int fitness_complexity::data_export(const char* exportDIR,
    const char* countryIndexFile, const char* productIndexFile,
    const char* DATA_DIR, const NodeType YEAR1, const NodeType YEAR2)
{
  VNodeType cIndex, pIndex;
  _ERR(common_read1_0(countryIndexFile, cIndex));
  _ERR(common_read1_0(productIndexFile, pIndex));
  for (NodeType year = YEAR1; year < YEAR2; ++year) {
    VVString epts;
    string s0 = exportDIR;
    _ERR(common_read2_0(
        (string(exportDIR) + to_string(year) + ".txt").c_str(), epts));
    VVString epts2(cIndex.size());
    for (NodeType ci = 0; ci < cIndex.size(); ++ci)
      for (NodeType pi = 0; pi < pIndex.size(); ++pi)
        epts2[ci].push_back(epts[cIndex[ci]][pIndex[pi]]);
    _ERR(common_save2(
        (string(DATA_DIR) + to_string(year) + ".txt").c_str(), epts2));
  }
  return 0;
}

int fitness_complexity::data(const char* gdpFile, const char* gdpIndexFile,
    const char* exportDIR, const char* countryIndexFile,
    const char* productIndexFile, const char* DATA_DIR)
{
  VVString gdp;
  _ERR(common_read2_0(gdpFile, gdp));
  VNodeType gIndex;
  _ERR(common_read1_0(gdpIndexFile, gIndex));
  VNodeType cIndex, pIndex;
  _ERR(common_read1_0(countryIndexFile, cIndex));
  _ERR(common_read1_0(productIndexFile, pIndex));
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
    _ERR(common_save1((s + y + ".gdp.txt").c_str(), g, '\n'));

    VVString epts;
    string s0 = exportDIR;
    _ERR(common_read2_0((s0 + y + ".export.txt").c_str(), epts));
    VVString epts2(cIndex.size());
    for (NodeType ci = 0; ci < cIndex.size(); ++ci)
      for (NodeType pi = 0; pi < pIndex.size(); ++pi)
        epts2[ci].push_back(epts[cIndex[ci]][pIndex[pi]]);
    _ERR(common_save2((s + y + ".export.txt").c_str(), epts2));
  }
  return 0;
}

// *******************************************************
int fitness_complexity::code2name(const char* nameFile, const char* codeFile,
    const char* code0File, const char* name0File)
{
  VString name, name0;
  VNodeType code, code0;
  _ERR(common_read_VString(nameFile, name));
  _ERR(common_read1_0(codeFile, code));
  _ERR(common_read1_0(code0File, code0));
  _ERR(name.size() != code.size());
  for (size_t j = 0; j < code0.size(); ++j) {
    bool flag = true;
    for (size_t i = 0; i < code.size(); ++i) {
      if (code0[j] == code[i]) {
        flag = false;
        name0.push_back(name[i]);
        break;
      }
    }
    _ERR(flag);
  }
  _ERR(common_save_VString(name0File, name0));
  return 0;
}

int fitness_complexity::sum_export(const char* epDir, const char* epName,
    const NodeType YEAR1, const NodeType YEAR2, const char* cFile,
    const char* cName, const char* pFile, const char* pName)
{
  for (NodeType y = YEAR1; y < YEAR2; ++y) {
    VVLinkType ep;
    _ERR(common_read2_0((string(epDir) + to_string(y) + epName).c_str(), ep));
    const NodeType NC = ep.size(), NP = ep[0].size();
    VLinkType sc(NC, 0), sp(NP, 0);
    for (NodeType i = 0; i < NC; ++i)
      for (NodeType j = 0; j < NP; ++j) {
        sc[i] += ep[i][j];
        sp[j] += ep[i][j];
      }
    _ERR(common_save1(
        (string(cFile) + to_string(y) + cName).c_str(), sc, '\n'));
    _ERR(common_save1(
        (string(pFile) + to_string(y) + pName).c_str(), sp, '\n'));
  }

  return 0;
}

int fitness_complexity::data_export_OEC(const char* cp0DIR,
    const char* c0CodeFile, const char* p4d0File, const char* cCodeFile,
    const char* p4dFile, const NodeType YEAR1, const NodeType YEAR2,
    const char* cpDIR, const char* cpName)
{
  VNodeType c0Code, p4d0, cCode, p4d, cIndex, pIndex;
  _ERR(common_read1_0(c0CodeFile, c0Code));
  _ERR(common_read1_0(p4d0File, p4d0));
  _ERR(common_read1_0(cCodeFile, cCode));
  _ERR(common_read1_0(p4dFile, p4d));
  cIndex.resize(cCode.size());
  for (NodeType ci = 0; ci < cCode.size(); ++ci)
    cIndex[ci]
        = find(c0Code.begin(), c0Code.end(), cCode[ci]) - c0Code.begin();
  pIndex.resize(p4d.size());
  for (NodeType pi = 0; pi < p4d.size(); ++pi)
    pIndex[pi] = find(p4d0.begin(), p4d0.end(), p4d[pi]) - p4d0.begin();
  for (NodeType year = YEAR1; year < YEAR2; ++year) {
    VVString epts;
    string s0 = cp0DIR;
    _ERR(common_read2_0(
        (string(cp0DIR) + to_string(year) + ".txt").c_str(), epts));
    VVString epts2(cCode.size());
    for (NodeType ci = 0; ci < cIndex.size(); ++ci)
      for (NodeType pi = 0; pi < pIndex.size(); ++pi)
        epts2[ci].push_back(epts[cIndex[ci]][pIndex[pi]]);
    _ERR(common_save2(
        (string(cpDIR) + to_string(year) + cpName).c_str(), epts2));
  }
  return 0;
}


// *******************************************************
#endif // ACT_FITNESS_COMPLEXITY
