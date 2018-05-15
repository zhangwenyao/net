// g++ -o main.exe *.cpp -O3 -Wall
#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY

#include "common.h"
#include "networks.h"
using namespace std;
//**//**************************************************//**//*
int main(int argc, char** argv)
{
  SHOW_TIME(cout); // 显示系统时间

  const string DIR = "../../swiss/economic-complexity/201803/", DIR2 = DIR + "1995-2010/";
  const int YEAR1 = 1995, YEAR2 = 2010;
  for (int year = YEAR1; year <= YEAR2; year++) {
    string y;
    stringstream ss;
    ss.clear();
    ss.str("");
    ss << year;
    y = ss.str();

    VVBool mcp;
    common_read2_0((DIR2 + y + ".mcp.txt").c_str(), mcp);
    const size_t NC = mcp.size(), NP = mcp[0].size();
    cout << "\t" << year << "\t" << NC << "\t" << NP << endl;

    VDouble cf, pc;
    Mcp_2_FC(cf, pc, mcp);
    common_save1((DIR2 + y + ".country.fitness.txt").c_str(), cf, '\n');
    common_save1((DIR2 + y + ".product.complexity.txt").c_str(), pc, '\n');
  } // year

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}

//**//**************************************************//**//*
#endif