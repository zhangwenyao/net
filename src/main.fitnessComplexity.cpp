// g++ -o main.exe *.cpp -O3 -Wall
#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY

#include "common.h"
#include "networks.h"
using namespace std;
// ******************************************************
int main(int argc, char** argv)
{
  SHOW_TIME(cout); // 显示系统时间

  const string DIR0 = "data/complexity/OEC.sitc_rev2/",
               DIR_DATA0 = DIR0 + "data0/", DIR_DATA = DIR0 + "data/",
               DIR_INFO = DIR0 + "info/";

  NodeType YEAR1 = 2000, YEAR2 = 2010, NC, NP;
  for (NodeType year = YEAR1; year <= YEAR2; year++) {
    string y;
    stringstream ss;
    ss.clear();
    ss.str("");
    ss << year;
    y = ss.str();

    // export to mcp
    VVDouble e;
    common_read2_0((DIR_DATA + y + ".export.txt").c_str(), e);
    cout << "" << year << "\t" << (NC = e.size()) << "\t"
         << (NP = e[0].size()) << endl;
    VVNodeType mcp(NC, VNodeType(NP, 0));
    export_2_Mcp(e, mcp);
    common_save2((DIR_DATA + y + ".mcp.txt").c_str(), mcp);
    // common_read2_0((DIR_DATA + y + ".mcp.txt").c_str(), mcp);

    VNodeType k1;
    count_k1(
        NC, NP, mcp, k1, (DIR_DATA + y + ".country.product.k.txt").c_str());

    // Mcp to country fitness & product complexity
    VDouble cf, pc;
    if (0 != Mcp_2_FC(cf, pc, mcp)) {
      ERROR();
      return -1;
    }
    common_save1((DIR_DATA + y + ".country.fitness.txt").c_str(), cf, '\n');
    common_save1(
        (DIR_DATA + y + ".product.complexity.txt").c_str(), pc, '\n');
    // break;

  } // year

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}

// ******************************************************
#endif
