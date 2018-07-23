// g++ -o main.exe *.cpp -O3 -Wall
#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY_PLOTDATA

#include "common.h"
#include "networks.h"
using namespace std;
// ********************************************************

int main(int argc, char** argv)
{
  SHOW_TIME(cout); // 显示系统时间

  const string DIR0 = "data/complexity/", DIR_DATA = DIR0 + "data/",
               DIR_PLOT_DATA = DIR0 + "plot/data/";
  const string methods[] = { "mass", "heat", "hybrid" };
  // const string methods[] = { "mass" };
  const size_t NMETHOD = sizeof(methods) / sizeof(methods[0]);
  const int YEAR1 = 1995, YEAR2 = 2014, NYEAR = YEAR2 - YEAR1 + 1;

  const size_t NC = 237, NP = 1241;
  for (int year = YEAR1; year < YEAR2; year++) {
    string y1;
    stringstream ss;
    ss.clear();
    ss.str("");
    ss << year;
    y1 = ss.str();
    cout << y1 << endl;

    VNodeType fullIndex;
    common_read1_0(
        (DIR0 + "1995-2010.info/GDP.1995-2010.full.index.txt").c_str(),
        fullIndex);
    const size_t NCF = fullIndex.size();

    VVDouble gdp;
    common_read2_0(
        (DIR0 + "1995-2010.info/GDP.1995-2010.full.val.txt").c_str(), gdp);
    VNodeType rk;
    {
      VDouble g;
      for (size_t c = 0; c < NCF; c++) {
        g.push_back(gdp[c][year - YEAR1]);
        rk.push_back(c);
      }
      common_sort_p_val_less(&rk[0], &rk[NCF], &g[0]);
      common_save1((DIR_DATA + y1 + ".gdp.full.rank.txt").c_str(), rk, '\n');
    }

    const size_t N = 10;
    VVNodeType rks;
    rks.resize(N);
    for (size_t i = 0; i < NCF; i++) {
      size_t j = int(1.0 * N * i / NCF);
      rks[j].push_back(rk[i]);
    }
    common_save2((DIR_DATA + y1 + ".gdp.full.rank10.txt").c_str(), rks);

    VVNodeType cpNew;
    common_read2_0(
        (DIR_DATA + y1 + ".country.product.new.txt").c_str(), cpNew);
    cpNew.resize(NC);

    VVDouble cpNewScale, newScale[NMETHOD];
    common_read2_0((DIR_DATA + y1 + ".country.product.new.scale.txt").c_str(),
        cpNewScale);
    cpNewScale.resize(NC);
    for (size_t i = 0; i < NMETHOD; i++) {
      string method = methods[i];
      common_read2_0(
          (DIR_DATA + y1 + "." + method + ".new.scale.txt").c_str(),
          newScale[i]);
      newScale[i].resize(NC);
    }
    {
      ofstream os((DIR_PLOT_DATA + "data/" + y1 + ".full.scale.txt").c_str());
      for (size_t cc = 0, c; cc < NCF; cc++) {
        c = fullIndex[cc];
        for (size_t j = 0; j < cpNew[c].size(); j++) {
          size_t p = cpNew[c][j];
          os << c << '[t' << p << '\t' << cpNewScale[c][j];
          for (size_t ii = 0; ii < NMETHOD; ii++) {
            os << '[t' << newScale[ii][c][j];
          }
          os << '\n';
        }
      }
      os.close();

      for (size_t i = 0; i < N; i++) {
        ss.clear();
        ss.str("");
        ss << DIR_PLOT_DATA << "data/" << y1 << ".full.scale.rank10." << i;
        string s = ss.str();
        ofstream os((s + ".txt").c_str());
        for (size_t cc = 0, c; cc < rks[i].size(); cc++) {
          c = rks[i][cc];
          for (size_t j = 0; j < cpNew[c].size(); j++) {
            size_t p = cpNew[c][j];
            os << c << '[t' << p << '\t' << cpNewScale[c][j];
            for (size_t ii = 0; ii < NMETHOD; ii++) {
              os << '[t' << newScale[ii][c][j];
            }
            os << '\n';
          }
        }
        os.close();
      }
    }

    VDouble pc;
    VVDouble rcm[NMETHOD];
    cpNew.resize(NC);
    common_read1_0((DIR_DATA + y1 + ".product.complexity.txt").c_str(), pc);
    for (size_t i = 0; i < NMETHOD; i++) {
      string method = methods[i];
      common_read2_0(
          (DIR_DATA + y1 + "." + method + ".rcm.txt").c_str(), rcm[i]);
    }
    {
      ofstream os((DIR_PLOT_DATA + "data/" + y1 + ".full.val.txt").c_str());
      for (size_t cc = 0, c; cc < NCF; cc++) {
        c = fullIndex[cc];
        for (size_t j = 0; j < cpNew[c].size(); j++) {
          size_t p = cpNew[c][j];
          os << c << '\t' << p << '\t' << pc[p];
          for (size_t ii = 0; ii < NMETHOD; ii++) {
            os << '[t' << rcm[ii][c][p];
          }
          os << '\n';
        }
      }
      os.close();

      for (size_t i = 0; i < N; i++) {
        ss.clear();
        ss.str("");
        ss << DIR_PLOT_DATA << "data/" << y1 << ".full.val.rank10." << i;
        string s = ss.str();
        ofstream os((s + ".txt").c_str());
        for (size_t cc = 0, c; cc < rks[i].size(); cc++) {
          c = rks[i][cc];
          for (size_t j = 0; j < cpNew[c].size(); j++) {
            size_t p = cpNew[c][j];
            os << c << '\t' << p << '\t' << pc[p];
            for (size_t ii = 0; ii < NMETHOD; ii++) {
              os << '[t' << rcm[ii][c][p];
            }
            os << '\n';
          }
        }
        os.close();
      }
    }

  } // year

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}

// ********************************************************
#endif
