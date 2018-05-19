// g++ -o main.exe *.cpp -O3 -Wall
#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY_FILTER

#include "common.h"
#include "networks.h"
using namespace std;
// *************************************************//*****
int main(int argc, char** argv)
{
  SHOW_TIME(cout); // 显示系统时间

  const string DIR0 = "data/complexity/", DIR_DATA0 = DIR0 + "data0/",
               DIR_DATA = DIR0 + "1995-2010.data/",
               DIR_INFO = DIR0 + "1995-2010.info/";

  // fileter country and product name
  // filter_trade_name(
  //(DIR_DATA0 + "year_origin_destination_sitc_rev2.tsv").c_str(),
  //(DIR_DATA0 + "country.names.all.txt").c_str(),
  //(DIR_DATA0 + "product.names.txt").c_str());

  filter_sum_trade(
      (DIR_DATA0 + "year_origin_destination_sitc_rev2.tsv").c_str(),
      (DIR_DATA0 + "country.names.origin.txt").c_str(),
      (DIR_DATA0 + "product.names.txt").c_str());

  /*
  const NodeType NC = 300;
  VNodeType ci(NC, 0), t;
  VVNodeType c;
  common_read2_0((DIR_INFO + "country-1995-2010.txt").c_str(), c);
  cout << c.size() << endl;
  filter_index(NC, c, ci);
  t.clear();
  for (NodeType i = 0; i < NC; i++)
    if (ci[i])
      t.push_back(i);
  common_save1((DIR_INFO + "country-1995-2010.index.txt").c_str(), t, '\n');
  VNodeType ci;
  common_read1_0((DIR_INFO + "country-1995-2010.index.txt").c_str(), ci);
  const size_t NC = ci.size();
  cout << NC << endl;

  const NodeType NP = 999;
  VNodeType pi(NP, 0);
  VVNodeType p;
  common_read2_0((DIR_INFO + "product-1995-2010.txt").c_str(), p);
  cout << p.size() << endl;
  filter_index(NP, p, pi);
  t.clear();
  for (NodeType i = 0; i < NP; i++)
    if (pi[i])
      t.push_back(i);
  common_save1((DIR_INFO + "product-1995-2010.index.txt").c_str(), t, '\n');
  VNodeType pi;
  common_read1_0((DIR_INFO + "product-1995-2010.index.txt").c_str(), pi);
  const size_t NP = pi.size();
  cout << NP << endl;

  const int YEAR1 = 1995, YEAR2 = 2010;
  for (int year = YEAR1; year <= YEAR2; year++) {
    string y;
    stringstream ss;
    ss.clear();
    ss.str("");
    ss << year;
    y = ss.str();

    VVLinkType e0, e;
    common_read2_0((DIR_DATA0 + y + ".export.txt").c_str(), e0);
    cout << "" << year << "\t" << e0.size() - 1 << "\t" << e0[0].size() - 1
         << endl;
    e.resize(NC);
    for (size_t c = 1, i; c < e0[0].size(); c++) {
      for (i = 0; i < NC; i++)
        if (e0[0][c] == ci[i])
          break;
      if (i >= NC)
        continue;
      for (size_t p = 1, j; p < e0.size(); p++) {
        for (j = 0; j < NP; j++)
          if (e0[p][0] == pi[j])
            break;
        if (j >= NP)
          continue;
        e[i].push_back(e0[p][c]);
      }
    }
    common_save2((DIR_DATA + y + ".export.txt").c_str(), e);
    VVLinkType e(NC, VLinkType(NP, 0));
    common_read2((DIR_DATA + y + ".export.txt").c_str(), e);

    VVBool mcp(NC, VBool(NP, false));
    // exp_2_Mcp(e, mcp);
    // common_save2((DIR_DATA + y + ".mcp.txt").c_str(), mcp);
    common_read2((DIR_DATA + y + ".mcp.txt").c_str(), mcp);

  } // year

*/

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}

// *************************************************//*****
#endif
