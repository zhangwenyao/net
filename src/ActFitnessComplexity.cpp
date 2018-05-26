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

int filter_index_same_gdp(const char* dir)
{
  VVString gdp;
  string s = dir;
  common_read2_0((s + "gdp.1995-2014.txt").c_str(), gdp);
  VNodeType gindex0, gindex, eindex0, eindex;
  common_read1_0((s + "country.index.same.all.gdp.txt").c_str(), gindex0);
  common_read1_0((s + "country.index.same.all.export.txt").c_str(), eindex0);
  for (NodeType i = 0, j, t; i < gindex0.size(); ++i) {
    for (t = gindex0[i], j = 0; j < gdp[t].size(); ++j)
      if (gdp[t][j] == "0")
        break;
    if (j >= gdp[t].size()) {
      gindex.push_back(t);
      eindex.push_back(eindex0[i]);
    }
  }
  common_save1((s + "country.index.same.gdp.gdp.txt").c_str(), gindex, '\n');
  common_save1(
      (s + "country.index.same.gdp.export.txt").c_str(), eindex, '\n');
  return 0;
}

int filter_gdp(const char* DIR_DATA0, const char* DIR_DATA)
{
  VVString gdp;
  VNodeType gindex;
  string s = DIR_DATA0;
  common_read2_0((s + "gdp.1995-2014.txt").c_str(), gdp);
  common_read1_0((s + "country.index.same.gdp.gdp.txt").c_str(), gindex);
  const NodeType YEAR1 = 1995, YEAR2 = 2014;
  s = DIR_DATA;
  VString g(gindex.size());
  for (NodeType year = YEAR1; year <= YEAR2; ++year) {
    cout << year << endl;
    string ys;
    stringstream ss;
    ss << year;
    ys = ss.str();
    for (NodeType i = 0; i < gindex.size(); ++i)
      g[i] = move(gdp[gindex[i]][year - YEAR1]);
    common_save1((s + ys + ".gdp.txt").c_str(), g, '\n');
  }
  return 0;
}

// *******************************************************
#endif // ACT_FITNESS_COMPLEXITY
