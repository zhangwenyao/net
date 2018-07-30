#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY

#include "common.h"
#include "networks.h"
using namespace std;
// ******************************************************
int main_fitness_complexity(int argc, char** argv)
{
  const string DIR0 = "data/complexity/OEC.sitc_rev2/",
               DIR_DATA0 = DIR0 + "data0/", DIR_DATA = DIR0 + "data/",
               DIR_INFO = DIR0 + "info/";
  const size_t YEAR1 = 2001, YEAR2 = 2014 + 1;

  size_t NC, NP;
  for (size_t year = YEAR1; year < YEAR2; year++) {
    // export to mcp
    VVLinkType e;
    ERROR_TEST(common_read2_0(
        (DIR_DATA + to_string(year) + ".export.txt").c_str(), e));
    NC = e.size();
    NP = e[0].size();
    INFORM(year, "\t", NC, "\t", NP);

    VVNodeType mcp;
    ERROR_TEST(export_2_Mcp(e, mcp));
    ERROR_TEST(
        common_save2((DIR_DATA + to_string(year) + ".mcp.txt").c_str(), mcp));
    // common_read2_0((DIR_DATA + y + ".mcp.txt").c_str(), mcp);

    VNodeType deg, product_deg;
    ERROR_TEST(count_deg(mcp, deg,
        (DIR_DATA + to_string(year) + ".country.product.mcp.deg.txt").c_str()));
    ERROR_TEST(count_product_deg(mcp, product_deg,
        (DIR_DATA + to_string(year) + ".product.country.mcp.deg.txt").c_str()));

    // Mcp to country fitness & product complexity
    VDouble cf, pc;
    ERROR_TEST(Mcp_2_FC(cf, pc, mcp));
    ERROR_TEST(common_save1(
        (DIR_DATA + to_string(year) + ".country.fitness.txt").c_str(), cf,
        '\n'));
    ERROR_TEST(common_save1(
        (DIR_DATA + to_string(year) + ".product.complexity.txt").c_str(), pc,
        '\n'));
    // break;

  } // year

  return 0;
}

// ******************************************************
#endif
