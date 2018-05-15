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
  const string methods[] = { "mass", "heat", "hybrid" };
  //const string methods[] = { "mass" };
  const size_t NMETHOD = sizeof(methods) / sizeof(methods[0]);
  const int YEAR1 = 1995, YEAR2 = 2010;
  //const int YEAR1 = 2000, YEAR2 = 2000;

  for (int year = YEAR1; year < YEAR2; year++) {
    string y1;
    stringstream ss;
    ss.clear();
    ss.str("");
    ss << year;
    y1 = ss.str();

    /*
    VVNodeType cpNew, cpNewRank, newRank[NMETHOD];
    common_read2_0((DIR2 + y1 + ".country.product.new.txt").c_str(), cpNew);
    common_read2_0((DIR2 + y1 + ".country.product.new.rank.txt").c_str(), cpNewRank);
    for (size_t i = 0; i < NMETHOD; i++) {
      string method = methods[i];
      common_read2_0((DIR2 + y1 + "." + method + ".new.rank.txt").c_str(), newRank[i]);
    }
    const size_t NC = cpNew.size();

    ofstream os((DIR_PLOT + y1 + ".plot.rank.txt").c_str());
    for (size_t c = 0; c < NC; c++)
      for (size_t p = 0; p < cpNew[c].size(); p++) {
        os << c << '\t' << cpNew[c][p] << '\t' << cpNewRank[c][p];
        for (size_t i = 0; i < NMETHOD; i++) {
          os << '\t' << newRank[i][c][p];
        }
        os << '\n';
      }
    os.close();
    */

    VVNodeType cpNew;
    VDouble pc;
    VVDouble rcm[NMETHOD];
    common_read2_0((DIR2 + y1 + ".country.product.new.txt").c_str(), cpNew);
    common_read1_0((DIR2 + y1 + ".product.complexity.txt").c_str(), pc);
    for (size_t i = 0; i < NMETHOD; i++) {
      string method = methods[i];
      common_read2_0((DIR2 + y1 + "." + method + ".rcm.txt").c_str(), rcm[i]);
    }
    const size_t NC = cpNew.size();

    ofstream os((DIR_PLOT + y1 + ".plot.val.txt").c_str());
    for (size_t c = 0; c < NC; c++)
      for (size_t p = 0; p < cpNew[c].size(); p++) {
        size_t ii = cpNew[c][p];
        os << c << '\t' << ii << '\t' << pc[ii];
        for (size_t i = 0; i < NMETHOD; i++) {
          os << '\t' << rcm[i][c][ii];
        }
        os << '\n';
      }
    os.close();
  } // year

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}

//**//**************************************************//**//*
#endif
