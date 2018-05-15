// g++ -o main.exe *.cpp -O3 -Wall
#include "main.h"
#ifdef MAIN_PLOTDATA

#include "common.h"
#include "networks.h"
using namespace std;
//**//**************************************************//**//*

int main(int argc, char** argv)
{
  SHOW_TIME(cout); // 显示系统时间

  const string DIR = "../../swiss/economic-complexity/201803/", DIR2 = DIR + "1995-2010/", DIR_PLOT = DIR + "1995-2010-plot/";
  //const string methods[] = { "mass", "heat", "hybrid" };
  const string methods[] = { "mass" };
  const size_t NMETHOD = sizeof(methods) / sizeof(methods[0]);
  const int YEAR1 = 1995, YEAR2 = 2010;
  //const int YEAR1 = 2000, YEAR2 = 2000;
  for (size_t iMethod = 0; iMethod < NMETHOD; iMethod++) {
    string method = methods[iMethod];
    cout << method << endl;

    for (int year = YEAR1; year < YEAR2; year++) {
      string y1;
      stringstream ss;
      ss.clear();
      ss.str("");
      ss << year;
      y1 = ss.str();

      VVNodeType cpNew, cpNewRank, newRank;
      common_read2_0((DIR2 + y1 + ".country.product.new.txt").c_str(), cpNew);
      common_read2_0((DIR2 + y1 + ".country.product.new.rank.txt").c_str(), cpNewRank);
      common_read2_0((DIR2 + y1 + "." + method + ".new.rank.txt").c_str(), newRank);
      const size_t NC = cpNew.size();

      ofstream os((DIR_PLOT + y1 + "." + method + ".plot.rank.txt").c_str());
      for (size_t c = 0; c < NC; c++)
        for (size_t p = 0; p < cpNew[c].size(); p++)
          os << c << '\t' << cpNew[c][p] << '\t' << cpNewRank[c][p] << '\t' << newRank[c][p] << '\n';
      os.close();

    } // year
  }   // method

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}

//**//**************************************************//**//*
#endif
