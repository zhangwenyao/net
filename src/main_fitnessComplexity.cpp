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

  string dir = "../../swiss/economic-complexity/201803/";
  VVInt mcp, mcp2010;
  VVNodeType pc, pp;
  Networks net;
  net.saveName = dir + "2009";

  read_Mcp_C_P((dir + "Mcp2009.txt").c_str(), mcp, pc, pp);
  net.recommend.user_p_object = &pc;
  net.recommend.object_p_user = &pp;
  net.act_recommend("heat");

  // common_read2_0((dir + "Mcp2009.txt").c_str(), mcp);
  const NodeType nc = mcp.size(), np = mcp[0].size();
  common_read2_0((dir + "Mcp2010.txt").c_str(), mcp2010);
  VVDouble rcm;
  common_read2_0((dir + "2009_heat.txt").c_str(), rcm);
  if (mcp2010.size() != nc || rcm.size() != nc) {
    ERROR();
    return -1;
  }

  // enum country { chn = 72, idn = 78, us = 217 };
  // const int NC = 3;
  // int countries[NC] = { chn, idn, us };
  NodeType rk[np];
  ofstream os((dir + "2009_heat_static.txt").c_str());
  if (!os) {
    ERROR();
    return -1;
  }
  cout << nc << "\t" << np << "\t" << rcm.size() << endl;
  os << "ctr\tk2009\tk2010\tnleft\tnnew\tmean\n";
  for (NodeType c = 0; c < nc; c++) {
    // cout << c << endl;
    if (mcp[c].size() != np || mcp2010[c].size() != np
        || rcm[c].size() != np) {
      ERROR(mcp[c].size(), "\t", mcp2010.size(), "\t", rcm[c].size());
      break;
    }
    int k2009 = 0, k2010 = 0, pnew = 0;
    double val = 0;
    for (NodeType p = 0; p < np; p++) {
      if (mcp[c][p] != 0) {
        rcm[c][p] = 0;
        k2009++;
      }
      if (mcp2010[c][p] != 0)
        k2010++;
    }
    for (NodeType p = 0; p < np; p++)
      rk[p] = p;
    common_sort_p_val_less(&rk[0], &rk[np], &rcm[c][0]);
    for (NodeType r = 0; r < np; r++) {
      int p = rk[r];
      if (mcp[c][p] == 0 && mcp2010[c][p] != 0) {
        pnew++;
        val += r;
      }
    }
    // os << rk[0];
    // for (int p = 1; p < np; p++)
    // os << '\t' << rk[p] + 1;
    os << c + 1 << '\t' << k2009 << '\t' << k2010 << '\t' << np - k2009 << '\t'
       << pnew << '\t' << (pnew > 0 ? val / pnew : 0) << '\n';
  }
  os.close();

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}

//**//**************************************************//**//*
#endif
