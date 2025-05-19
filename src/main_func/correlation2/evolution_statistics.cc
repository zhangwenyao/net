#include "evolution_statistics.h"
#ifdef MAIN_CORRELATION2_EVOLUTION_STATISTICS

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// **********************************************************
int main_func::correlation2::evolution_statistics(int argc, char** argv)
{
  Networks net;
  net.readName = dirData + name;
  net.argv = "--cal_params read";
  _ERR(0 != net.run().runStatus);

  const string kPStr = "d1000";
  const double kP = 1.0 / 1000;
  const string head = "#delPer"
                      "\tcorrelation2.pearson"
                      "\tpearson"
                      "\tcorrelation2.spearman"
                      "\tspearman"
                      "\tcorrelation2.pearson\tdeviation"
                      "\tpearson\tdeviation"
                      "\tcorrelation2.spearman\tdeviation"
                      "\tspearman\tdeviation"
                      "\tseed_size\n";
  const string coefficient_strings[]
      = { "--correlation2.node", "--pearson.pearson",
          "--correlation2.node_spearman", "--spearman.spearman" };
  ofstream os((dirData + name + ".statistics.txt").c_str());
  _ERR(!os);
  os << head;
  for (auto delPer : kDelPers) {
    cout << name << "\t" << delPer * kP << endl;
    os << delPer * kP << '\t' << net.correlation2.node << '\t'
       << net.pearson.pearson << '\t' << net.correlation2.node_spearman
       << '\t' << net.spearman.spearman;
    string prename = dirData + name + "_" + to_string(delPer) + kPStr + "_",
           sufname = ".params.txt";
    size_t n = 0;
    for (const auto& coefficient_string : coefficient_strings) {
      double sx = 0, sxx = 0;
      n = 0;
      statistics::sum(prename.c_str(), sufname.c_str(), kSeedMin, kSeedMax,
          coefficient_string.c_str(), sx, sxx, n);
      if (n > 0) {
        sx /= n;
        sxx = sxx / n - sx * sx;
        sxx = sxx > 0 ? sqrt(sxx) : 0;
      }
      os << '\t' << sx << '\t' << sxx;
    }
    os << '\t' << n << '\n';
  }
  os.close();
  return 0;
}

#endif
