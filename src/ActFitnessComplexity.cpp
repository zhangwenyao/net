#include "ActFitnessComplexity.h"
#ifdef ACT_FITNESS_COMPLEXITY

#include "common.h"
#include <algorithm>
using namespace std;

// *******************************************************
int count_k1(const VVNodeType& mcp, VNodeType& k1, const char* name)
{
  const NodeType NC = mcp.size(), NP = mcp[0].size();
  k1.assign(NP, 0);
  for (NodeType c = 0; c < NC; ++c) {
    for (NodeType p = 0; p < NP; ++p) {
      if (mcp[c][p])
        k1[c]++;
    }
  }
  if (name != NULL && name[0] != '\0')
    common_save1(name, k1, '\n');
  return 0;
}

int count_product_k1(const VVNodeType& mcp, VNodeType& k1, const char* name)
{
  const NodeType NC = mcp.size(), NP = mcp[0].size();
  k1.assign(NP, 0);
  for (NodeType c = 0; c < NC; ++c) {
    for (NodeType p = 0; p < NP; ++p) {
      if (mcp[c][p])
        k1[p]++;
    }
  }
  if (name != NULL && name[0] != '\0')
    common_save1(name, k1, '\n');
  return 0;
}

int count_mcpNew(const NodeType NC, const NodeType NP, const VVNodeType& mcp,
    const VVNodeType& mcp2, VVNodeType& mcpNew, const char* name)
{
  mcpNew.resize(NC);
  for (size_t c = 0; c < NC; c++) {
    mcpNew[c].clear();
    for (size_t p = 0; p < NP; p++) {
      if (mcp[c][p] == 0 && mcp2[c][p] != 0)
        mcpNew[c].push_back(p);
    }
  }
  if (name != NULL && name[0] != '\0')
    common_save2(name, mcpNew);
  return 0;
}

int count_kNew(VNodeType& kNew, const VVNodeType& mcpNew, const char* name)
{
  kNew.resize(mcpNew.size());
  for (size_t c = 0; c < mcpNew.size(); c++) {
    kNew[c] = mcpNew[c].size();
  }
  if (name != NULL && name[0] != '\0')
    common_save1(name, kNew, '\n');
  return 0;
}

int count_pcNewRank(const VDouble& pc, const size_t NC, const size_t NP,
    const VVNodeType& mcpNew, VVNodeType& pcNewRank, const char* name)
{
  pcNewRank.resize(NC);
  VNodeType rk(NP, 0), rk2(NP, 0);
  for (size_t p = 0; p < NP; p++)
    rk[p] = p;
  common_sort_p_val_less(&rk[0], &rk[NP], &pc[0]); // pc[rk[i]]<=pc[rk[i+1]]
  for (size_t p = 0; p < NP; p++)                  // pc[i]'s rank is rk2[i]
    rk2[rk[p]] = p;
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < mcpNew[c].size(); p++)
      pcNewRank[c].push_back(rk2[mcpNew[c][p]]);
    break;
  }
  if (name != NULL && name[0] != '\0')
    common_save2(name, pcNewRank);
  return 0;
}

int count_pcNewRemainRank(const VDouble& pc, const size_t NC, const size_t NP,
    const VVNodeType& mcp, const VVNodeType& mcpNew,
    VVNodeType& pcNewRemainRank, const char* name)
{
  pcNewRemainRank.resize(NC);
  VNodeType rk(NP, 0), rk2(NP, 0);
  for (size_t c = 0; c < NC; c++) {
    pcNewRemainRank[c].clear();
    size_t NN = mcpNew[c].size(), NR = 0;
    if (NN <= 0)
      continue;
    for (size_t p = 0; p < NP; p++)
      if (mcp[c][p] == 0)
        rk[NR++] = p;
    INFORM(NR);
    common_sort_p_val_less(&rk[0], &rk[NR], &pc[0]);
    for (size_t p = 0; p < NR; p++)
      rk2[rk[p]] = p;
    for (size_t p = 0; p < NN; p++)
      pcNewRemainRank[c].push_back(rk2[mcpNew[c][p]]);
    break;
  }
  if (name != NULL && name[0] != '\0')
    common_save2(name, pcNewRemainRank);
  return 0;
}

int count_newScale(const size_t NC, const size_t NP, const VNodeType& k1,
    const VVNodeType& newRemainRank, VVDouble& newScale, const char* name)
{
  newScale.resize(NC);
  for (size_t c = 0; c < NC; c++) {
    newScale[c].clear();
    if (NP == k1[c] + 1 && newRemainRank[c].size() == 1) {
      newScale[c].push_back(0.5);
      continue;
    }
    double x = 1.0 / (NP - k1[c] - 1);
    for (size_t p = 0; p < newRemainRank[c].size(); p++)
      newScale[c].push_back(newRemainRank[c][p] * x);
    break;
  }
  if (name != NULL && name[0] != '\0')
    common_save2(name, newScale);
  return 0;
}

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
    common_save2(name, newRank);
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
    common_save2(name, newRemainRank);
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

int filter_trade_name_OEC(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const NodeType YEAR1, const NodeType YEAR2)
{
  ifstream is(tradeFilename);
  if (!is) {
    ERROR();
    return -1;
  }
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
  common_save(countryFilename, cChar, nc, '\n');

  common_save_bool(productFilename, &pVal[0], 9999, '\n');

  return 0;
}

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
  if (countryFilename0 != NULL && countryFilename0[0] != '\0')
    INFORM_TEST(0 != common_read1_0(countryFilename0, cVal));
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
  common_save1(countryFilename, cVal, '\n');
  sort(pVal.begin(), pVal.end());
  common_save1(productFilename, pVal, '\n');
  return 0;
}

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
  if (countryFilename0 != NULL && countryFilename0[0] != '\0')
    INFORM_TEST(0 != common_read1_0(countryFilename0, cVal));
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
  common_save1(countryFilename, cVal, '\n');
  sort(pVal.begin(), pVal.end());
  common_save1(productFilename, pVal, '\n');
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
        // common_save2(s, expts);
        save_export_data(s, expts);
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
  cout << NC << "\t" << NP << endl;

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
  for (LinkType v; is >> year >> origin >> pd >> v; ++l) {
    if (YEAR1 > year || year >= YEAR2)
      continue;
    if (year > year0) {
      cout << l << "\t" << year0 << endl;
      common_save2((name + to_string(year0) + ".export.txt").c_str(), expts);
      expts.assign(NC, VLinkType(NP, 0));
      expts[cVal[common_atoi<size_t>(origin)]][pVal[pd]] = v;
      year0 = year;
    } else if (year == year0) { // year==year0
      expts[cVal[common_atoi<size_t>(origin)]][pVal[pd]] += v;
    } else { // year<year0
      ERROR();
    }
  }
  cout << l << "\t" << year0 << endl;
  sprintf(s, "%s%u.export.txt", dirSave, year0);
  common_save2((name + to_string(year0) + ".export.txt").c_str(), expts);
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
    if (icode != "100000" || ecode == "100000" || sitc4 == "0") // World
      continue;
    c = find(cVal.begin(), cVal.end(), ecode) - cVal.begin();
    p = find(pVal.begin(), pVal.end(), sitc4) - pVal.begin();
    expts[c][p] += value;
  }
  is.close();
  common_save2(saveName, expts);

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
  common_save2(saveName, expts);

  return 0;
}

int filter_export_gdp_country_name(const char* exportNames,
    const char* exportNames3c, const char* gdpNames, const char* savePrefix)
{
  VString vept, vept3c, veptAll, vgdp, same, diffGdp, diffEpt;
  common_read_VString(exportNames, veptAll);
  common_read_VString(exportNames3c, vept3c);
  NodeType NE3 = vept3c.size(), NE = veptAll.size() / 2;
  for (NodeType i = 0, j; i < NE3; ++i) {
    for (j = 0; j < NE; ++j)
      if (vept3c[i] == veptAll[j * 2])
        break;
    if (j < NE) {
      vept.push_back(veptAll[j * 2 + 1]);
    } else {
      ERROR(vept3c[i]);
      return -1;
    }
  }
  string s = savePrefix;
  common_save_VString((s + ".export.txt").c_str(), vept);

  common_read_VString(gdpNames, vgdp);
  // NodeType NG = vgdp.size();
  VStringCItr ie, ig;
  for (ie = vept.begin(); ie != vept.end(); ++ie) {
    for (ig = vgdp.begin(); ig != vgdp.end(); ++ig)
      if (*ie == *ig)
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
  common_save_VString((s + ".same.common.txt").c_str(), same);
  sort(diffGdp.begin(), diffGdp.end());
  common_save_VString((s + ".diff.gdp.all.txt").c_str(), diffGdp);
  sort(diffEpt.begin(), diffEpt.end());
  common_save_VString((s + ".diff.export.all.txt").c_str(), diffEpt);
  return 0;
}

int filter_index_same_all(const char* namesFull, const char* sameAll)
{
  {
    VString vept, veptAll;
    string s = namesFull;
    common_read_VString((s + ".export.txt").c_str(), veptAll);
    common_read_VString((s + ".same.common.txt").c_str(), vept);
    common_read_VString((s + ".same.export.txt").c_str(), vept);
    VNodeType index;
    for (NodeType i = 0, j; i < vept.size(); ++i) {
      for (j = 0; j < veptAll.size(); ++j)
        if (vept[i] == veptAll[j])
          break;
      if (j < veptAll.size())
        index.push_back(j);
      else
        ERROR(vept[i]);
    }
    s = sameAll;
    common_save1((s + ".export.txt").c_str(), index, '\n');
  }

  {
    VString vgdp, vgdpAll;
    string s = namesFull;
    common_read_VString((s + ".gdp.txt").c_str(), vgdpAll);
    common_read_VString((s + ".same.common.txt").c_str(), vgdp);
    common_read_VString((s + ".same.gdp.txt").c_str(), vgdp);
    VNodeType index;
    for (NodeType i = 0, j; i < vgdp.size(); ++i) {
      for (j = 0; j < vgdpAll.size(); ++j)
        if (vgdp[i] == vgdpAll[j])
          break;
      if (j < vgdpAll.size())
        index.push_back(j);
      else
        ERROR(vgdp[i]);
    }
    s = sameAll;
    common_save1((s + ".gdp.txt").c_str(), index, '\n');
  }
  return 0;
}

int filter_index_gdp_0(const char* gdpFile, const char* indexFile)
{
  VVString gdp;
  common_read2_0(gdpFile, gdp);
  VNodeType index;
  for (NodeType i = 0, j; i < gdp.size(); ++i) {
    for (j = 0; j < gdp[i].size(); ++j)
      if (gdp[i][j] == "0")
        break;
    if (j >= gdp[i].size()) {
      index.push_back(i);
    }
  }
  common_save1(indexFile, index, '\n');
  return 0;
}

int filter_index_export_0(const char* epDIR, const char* indexFile,
    const char* pdIndexFile, const NodeType YEAR1, const NodeType YEAR2)
{
  const NodeType NYEAR = YEAR2 - YEAR1 + 1;
  vector<VVString> ep(NYEAR);
  for (NodeType i = 0; i < NYEAR; ++i) {
    string y;
    stringstream ss;
    ss << YEAR1 + i;
    y = ss.str();
    string s = epDIR;
    common_read2_0((s + y + ".export.txt").c_str(), ep[i]);
  }

  NodeType NC = ep[0].size(), NP = ep[0][0].size();
  VNodeType index(NC), pdIndex(NP);
  for (NodeType ci = 0; ci < index.size(); ++ci)
    index[ci] = ci;
  for (NodeType pi = 0; pi < pdIndex.size(); ++pi)
    pdIndex[pi] = pi;
  for (bool flag = 1; flag;) {
    flag = 0;
    for (NodeType ci = 0; ci < index.size(); ++ci) {
      NodeType c = index[ci];
      for (NodeType i = 0, pi; i < NYEAR; ++i) {
        for (pi = 0; pi < pdIndex.size(); ++pi) {
          NodeType p = pdIndex[pi];
          if (ep[i][c][p] != "0")
            break;
        }
        if (pi >= pdIndex.size()) {
          // INFORM(c, "\t", i + YEAR1);
          index[ci] = index.back();
          index.pop_back();
          flag = 1;
          break;
        }
      }
    }
    for (NodeType pi = 0; pi < pdIndex.size(); ++pi) {
      NodeType p = pdIndex[pi];
      for (NodeType i = 0, ci; i < NYEAR; ++i) {
        for (ci = 0; ci < index.size(); ++ci) {
          NodeType c = index[ci];
          if (ep[i][c][p] != "0") {
            break;
          }
        }
        if (ci >= index.size()) {
          // INFORM(p, "\t", i + YEAR1);
          pdIndex[pi] = pdIndex.back();
          pdIndex.pop_back();
          flag = 1;
          break;
        }
      }
    }
  }
  sort(index.begin(), index.end());
  common_save1(indexFile, index, '\n');
  sort(pdIndex.begin(), pdIndex.end());
  common_save1(pdIndexFile, pdIndex, '\n');

  return 0;
}

int filter_index_export_0_NBER_wtf(const char* epDIR, const char* indexFile,
    const char* pdIndexFile, const NodeType YEAR1, const NodeType YEAR2,
    const NodeType YEAR0)
{
  const NodeType NYEAR = YEAR2 - YEAR1 + 1;
  ERROR_TEST(YEAR1 > YEAR0 || YEAR0 > YEAR2);
  vector<VVString> ep(NYEAR);
  string s = epDIR;
  for (NodeType i = 0; i < NYEAR; ++i) {
    common_read2_0((s + to_string(i + YEAR1) + ".export.txt").c_str(), ep[i]);
    cout << i + YEAR1 << "\t" << ep[i].size() << "\t" << ep[i][0].size()
         << endl;
  }

  NodeType NC = ep[0].size(), NP = ep[0][0].size();
  VNodeType index(NC), pdIndex(NP);
  for (NodeType ci = 0; ci < index.size(); ++ci)
    index[ci] = ci;
  for (NodeType pi = 0; pi < pdIndex.size(); ++pi)
    pdIndex[pi] = pi;

  for (bool flag = true; flag;) {
    flag = false;

    for (NodeType ci = 0; ci < index.size();) { // filter country
      NodeType c = index[ci], year = YEAR1;
      for (NodeType pi; year <= YEAR2; ++year) {
        for (pi = 0;
             pi < pdIndex.size() && ep[year - YEAR1][c][pdIndex[pi]] == "0";
             ++pi)
          continue;
        if (pi >= pdIndex.size()) {
          flag = true;
          index[ci] = index.back();
          index.pop_back();
          break;
        }
      }
      if (year > YEAR2)
        ++ci;
    }

    for (NodeType pi = 0; pi < pdIndex.size();) { // filter product
      NodeType p = pdIndex[pi], year = YEAR1;
      for (NodeType ci; year <= YEAR2; ++year) {
        for (ci = 0;
             ci < index.size() && ep[year - YEAR1][index[ci]][p] == "0"; ++ci)
          continue;
        if (ci >= index.size()) {
          flag = true;
          pdIndex[pi] = pdIndex.back();
          pdIndex.pop_back();
          break;
        }
      }
      if (year > YEAR2)
        ++pi;
    }

    for (NodeType ci = 0; ci < index.size();) { // filter country
      for (NodeType pi = 0; pi < pdIndex.size(); ++pi) {
        NodeType p = pdIndex[pi], year = YEAR1;
        bool f1 = true, f2 = ep[year - YEAR1][index[ci]][p] == "0", f3;
        for (year = YEAR1 + 1; year <= YEAR2; ++year) { // cal f3
          f3 = ep[year - YEAR1][index[ci]][p] == "0";
          if (f1 && !f2 && f3) {
            flag = true;
            index[ci] = index.back();
            index.pop_back();
            break;
          }
          f1 = f2;
          f2 = f3;
        }
        if (year <= YEAR2)
          break;
      }
    }
  }

  sort(index.begin(), index.end());
  common_save1(indexFile, index, '\n');
  sort(pdIndex.begin(), pdIndex.end());
  common_save1(pdIndexFile, pdIndex, '\n');

  return 0;
}

int filter_index_export_gdp(const char* gdpIndexFile0,
    const char* gdpIndexFile, const char* gdpIndexFile2,
    const char* exportIndexFile0, const char* exportIndexFile,
    const char* exportIndexFile2)
{
  VNodeType g0, g, g2, e0, e, e2;
  common_read1_0(gdpIndexFile0, g0);
  common_read1_0(gdpIndexFile, g);
  common_read1_0(exportIndexFile0, e0);
  common_read1_0(exportIndexFile, e);
  if (g0.size() != e0.size()) {
    ERROR();
    return -1;
  }
  NodeType n = g0.size();
  VNodeType index(n, 0), id;
  for (NodeType i = 0; i < n; ++i)
    for (NodeType j = 0; j < g.size(); ++j) {
      if (g[j] == g0[i]) {
        ++index[i];
        break;
      }
    }
  for (NodeType i = 0; i < n; ++i)
    for (NodeType j = 0; j < e.size(); ++j) {
      if (e[j] == e0[i]) {
        ++index[i];
        break;
      }
    }
  for (NodeType i = 0; i < n; ++i)
    if (index[i] == 2)
      id.push_back(i);
  common_save1_p(gdpIndexFile2, &g0[0], &id[0], id.size(), '\n');
  common_save1_p(exportIndexFile2, &e0[0], &id[0], id.size(), '\n');
  return 0;
}

int filter_data_export(const char* exportDIR, const char* countryIndexFile,
    const char* productIndexFile, const char* DATA_DIR, const NodeType YEAR1,
    const NodeType YEAR2)
{
  VNodeType cIndex, pIndex;
  common_read1_0(countryIndexFile, cIndex);
  common_read1_0(productIndexFile, pIndex);
  const NodeType NYEAR = YEAR2 - YEAR1 + 1;
  for (NodeType i = 0; i < NYEAR; ++i) {
    string y;
    stringstream ss;
    ss << YEAR1 + i;
    y = ss.str();
    string s = DATA_DIR;

    VVString epts;
    string s0 = exportDIR;
    common_read2_0((s0 + y + ".export.txt").c_str(), epts);
    VVString epts2(cIndex.size());
    for (NodeType ci = 0; ci < cIndex.size(); ++ci)
      for (NodeType pi = 0; pi < pIndex.size(); ++pi)
        epts2[ci].push_back(epts[cIndex[ci]][pIndex[pi]]);
    common_save2((s + y + ".export.txt").c_str(), epts2);
  }
  return 0;
}

int filter_data(const char* gdpFile, const char* gdpIndexFile,
    const char* exportDIR, const char* countryIndexFile,
    const char* productIndexFile, const char* DATA_DIR)
{
  VVString gdp;
  common_read2_0(gdpFile, gdp);
  VNodeType gIndex;
  common_read1_0(gdpIndexFile, gIndex);
  VNodeType cIndex, pIndex;
  common_read1_0(countryIndexFile, cIndex);
  common_read1_0(productIndexFile, pIndex);
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
    common_save1((s + y + ".gdp.txt").c_str(), g, '\n');

    VVString epts;
    string s0 = exportDIR;
    common_read2_0((s0 + y + ".export.txt").c_str(), epts);
    VVString epts2(cIndex.size());
    for (NodeType ci = 0; ci < cIndex.size(); ++ci)
      for (NodeType pi = 0; pi < pIndex.size(); ++pi)
        epts2[ci].push_back(epts[cIndex[ci]][pIndex[pi]]);
    common_save2((s + y + ".export.txt").c_str(), epts2);
  }
  return 0;
}

// *******************************************************
#endif // ACT_FITNESS_COMPLEXITY
