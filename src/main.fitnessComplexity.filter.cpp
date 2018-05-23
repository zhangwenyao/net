// g++ -o main.exe *.cpp -O3 -Wall
#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY_FILTER

#include "common.h"
#include "networks.h"
using namespace std;
// *****************************************************
int main(int argc, char** argv)
{
  SHOW_TIME(cout); // 显示系统时间

  const string DIR0 = "data/complexity/", DIR_DATA0 = DIR0 + "data0/",
               DIR_DATA = DIR0 + "data/", DIR_INFO = DIR0 + "info/";

  //// fileter country and product name
  // filter_trade_name((DIR_DATA0 + "year_origin_hs92_4.export.txt").c_str(),
  //(DIR_DATA0 + "country.names.export.txt").c_str(),
  //(DIR_DATA0 + "product.names.export.txt").c_str());

  //// sum export data
  // filter_sum_trade((DIR_DATA0 + "year_origin_hs92_4.export.txt").c_str(),
  //(DIR_DATA0 + "country.names.export.txt").c_str(),
  //(DIR_DATA0 + "product.names.export.txt").c_str(),
  //(DIR_DATA0 + "hs92.export/").c_str());

  // NodeType NC;
  // VNodeType cVal(26 * 26 * 26, 0);
  // read_country_names(
  //(DIR_DATA0 + "country.names.export.txt").c_str(), NC, cVal);
  // unsigned NP = 0;
  // VUnsigned pVal(9999, 0);
  // read_product_names(
  //(DIR_DATA0 + "product.names.export.txt").c_str(), NP, pVal);

  const NodeType YEAR1 = 1995, YEAR2 = 2014, NC = 237, NP = 1241;
  for (NodeType year = YEAR1; year <= YEAR2; year++) {
    string y;
    stringstream ss;
    ss.clear();
    ss.str("");
    ss << year;
    y = ss.str();

    VVDouble e;
    common_read2_0(
        (DIR_DATA0 + "hs92.export/" + y + ".export.txt").c_str(), e);
    cout << "" << year << "\t" << e.size() << "\t" << e[0].size() << endl;
    if (e.size() != NC || e[0].size() != NP) {
      ERROR();
      return -1;
    }

    VVBool mcp(NC, VBool(NP, false));
    exp_2_Mcp(e, mcp);
    common_save2((DIR_DATA + y + ".mcp.txt").c_str(), mcp);

  } // year

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}

// ******************************************************
#endif
