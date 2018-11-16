#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY_COUNT

#include "common.h"
#include "networks.h"
using namespace std;
// ******************************************************

int main_fitness_complexity_count(int argc, char** argv)
{
  const string DIR0 = "data/complexity/OEC.sitc_rev2/",
               DIR_DATA0 = DIR0 + "data0/", DIR_DATA = DIR0 + "data/",
               DIR_INFO = DIR0 + "info/";
  const size_t YEAR1 = 2001, YEAR2 = 2014 + 1;
  //const string methods[] = { "mass", "heat", "hybrid", "proximity" };
  const string methods[] = { "proximity" };
  const size_t NMETHOD = sizeof(methods) / sizeof(methods[0]);

  VNodeType cIndex, pIndex;
  VString gNames;
  {
    _ERR(common_read1_0(
        (DIR_INFO + "country.index.export.not0.txt").c_str(), cIndex));
    _ERR(common_read1_0(
        (DIR_INFO + "product.index.export.not0.txt").c_str(), pIndex));
    _ERR(common_read1_0(
        (DIR_INFO + "country.namesFull.gdp.txt").c_str(), gNames));
  }
  const size_t NC = cIndex.size(), NP = pIndex.size(), NG = gNames.size();
  cout << NC << "\t" << NP << "\t" << NG << endl;

  VVLinkType gdps0;
  _ERR(
      common_read2_0((DIR_DATA0 + "2001-2014.gdps.txt").c_str(), gdps0));
  VVDouble gdpGrows0;
  _ERR(common_read2_0(
      (DIR_DATA0 + "2001-2016.gdpGrows.txt").c_str(), gdpGrows0));

  for (size_t year = YEAR1; year < YEAR2; year++) {
    INFORM(year);
    VVNodeType mcp, mcpMcp;
    VNodeType mcpDeg;
    VDouble pc, cf, gdp, gdpGrow;
    {
      _ERR(common_read2_0(
          (DIR_DATA + to_string(year) + ".mcp.txt").c_str(), mcp));
      _ERR(mcp.size() != NC);
      for (NodeType c = 0; c < NC; c++)
        _ERR(mcp[c].size() != NP);
      _ERR(common_read1_0(
          (DIR_DATA + to_string(year) + ".country.product.mcp.deg.txt")
              .c_str(),
          mcpDeg));
      _ERR(common_read1_0(
          (DIR_DATA + to_string(year) + ".product.complexity.txt").c_str(),
          pc));
      _ERR(common_read1_0(
          (DIR_DATA + to_string(year) + ".country.fitness.txt").c_str(), cf));

      for (size_t g = 0; g < NG; g++) {
        gdp.push_back(gdps0[g][year - 2001]);
        gdpGrow.push_back(gdpGrows0[g][year - 2001]);
      }
      _ERR(common_save1(
          (DIR_DATA + to_string(year) + ".gdp.txt").c_str(), gdp, '\n'));
      _ERR(
          common_save1((DIR_DATA + to_string(year) + ".gdpGrow.txt").c_str(),
              gdpGrow, '\n'));
      save_val_2_rankScale(
          gdp, (DIR_DATA + to_string(year) + ".gdp").c_str());

      save_val_2_rankScale(
          pc, (DIR_DATA + to_string(year) + ".product.complexity").c_str());
      save_val_2_rankScale(
          cf, (DIR_DATA + to_string(year) + ".country.fitness").c_str());

      mcpMcp.resize(NC);
      for (size_t c = 0; c < NC; ++c) {
        for (size_t p = 0; p < NP; ++p)
          if (mcp[c][p] != 0)
            mcpMcp[c].push_back(p);
      }
      _ERR(common_save2(
          (DIR_DATA + to_string(year) + ".country.product.mcp.txt").c_str(),
          mcpMcp));
    }

    if (year <= YEAR1)
      continue;
    //**********************************************************
    // count 2 var
    VVNodeType mcp0, mcpNew(NC);
    VNodeType mcpDeg0;
    {
      _ERR(common_read2_0(
          (DIR_DATA + to_string(year - 1) + ".mcp.txt").c_str(), mcp0));
      _ERR(common_read1_0(
          (DIR_DATA + to_string(year - 1) + ".country.product.mcp.deg.txt")
              .c_str(),
          mcpDeg0));

      for (size_t c = 0; c < NC; c++) {
        for (size_t i = 0, p; i < mcpMcp[c].size(); i++) {
          p = mcpMcp[c][i];
          if (mcp0[c][p] == 0)
            mcpNew[c].push_back(p);
        }
      }
      _ERR(common_save2(
          (DIR_DATA + to_string(year) + ".country.product.new.txt").c_str(),
          mcpNew));

      VDouble pcNewMean(NC, 0), pcNewMeanDev(NC, 0), pcMcpMean(NC, 0),
          pcMcpMeanDev(NC, 0);
      for (size_t c = 0; c < NC; c++) {
        double s = 0, s2 = 0, m = 0, m2 = 0;
        size_t ns = 0, nm = 0;
        for (size_t p = 0; p < NP; p++) {
          if (mcp[c][p] != 0) {
            double t = pc[p];
            m += t;
            m2 += t * t;
            nm++;
            if (mcp0[c][p] == 0) {
              s += t;
              s2 += t * t;
              ns++;
            }
          }
        }
        s /= mcpDeg[c];
        s2 = sqrt(s2 / ns - s * s);
        m /= mcpDeg[c];
        m2 = sqrt(m2 / nm - m * m);
        pcNewMean[c] = s;
        pcNewMeanDev[c] = s2;
        pcMcpMean[c] = m;
        pcMcpMeanDev[c] = m2;
      }
      common_save1((DIR_DATA + to_string(year)
                       + ".country.product.complexity.new.mean.txt")
                       .c_str(),
          pcNewMean, '\n');
      common_save1((DIR_DATA + to_string(year)
                       + ".country.product.complexity.new.dev.txt")
                       .c_str(),
          pcNewMeanDev, '\n');
      common_save1((DIR_DATA + to_string(year)
                       + ".country.product.complexity.mcp.mean.txt")
                       .c_str(),
          pcMcpMean, '\n');
      common_save1((DIR_DATA + to_string(year)
                       + ".country.product.complexity.mcp.dev.txt")
                       .c_str(),
          pcMcpMeanDev, '\n');
    }

    for (size_t iMethod = 0; iMethod < NMETHOD; iMethod++) {
      string method = methods[iMethod];
      cout << "\t" << method << endl;

      Networks net;
      net.saveName = DIR_DATA + to_string(year);
      common_read2_0(
          (DIR_DATA + to_string(year) + "." + method + ".rcm.txt").c_str(),
          net.recommend.rcm);
      if (net.recommend.rcm.size() != NC) {
        INFORM(NC, '\t', net.recommend.rcm.size());
        return -1;
      }
      _ERR(net.recommend.rcm.size() != NC);

      VDouble rs, rsDev;
      count_rankingScore(net.recommend.rcm, NC, NP, mcp0, mcp, rs, rsDev);
      _ERR(common_save1((DIR_DATA + to_string(year) + "." + method
                                  + ".country.rankingScore.txt")
                                  .c_str(),
          rs));
      _ERR(common_save1((DIR_DATA + to_string(year) + "." + method
                                  + ".country.rankingScoreDev.txt")
                                  .c_str(),
          rsDev));

      VVDouble rcmNewScale(NC);
      for (size_t c = 0; c < NC; ++c) {
        VDouble val, scale;
        VNodeType id;
        for (size_t p = 0; p < NP; p++) {
          if (mcp0[c][p] == 0) {
            val.push_back(net.recommend.rcm[c][p]);
            id.push_back(p);
          }
        }
        cal_val_2_rankScale(val, scale);
        rcmNewScale[c].assign(NP, 3);
        for (size_t i = 0; i < id.size(); i++) {
          rcmNewScale[c][id[i]] = scale[i];
        }
      }
      common_save2(
          (DIR_DATA + to_string(year) + "." + method + ".rcm.newScale.txt")
              .c_str(),
          rcmNewScale);
    } // method

  } // year

  return 0;
}

// ******************************************************
#endif
