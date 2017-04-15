// g++ -o main.exe *.cpp -O3 -Wall
#include "common.h"
#include "networks.h"
#ifdef STAT_CLUSTER

using namespace std;
//**//********************************************************************
int main(int argc, char **argv) {
  SHOW_TIME(cout);  // 显示系统时间

  Networks net;
  do {
    net.seed = 1;
    net.weightFlag = 1;
    net.dirFlag = 1;
    net.saveName = net.readName = "data/stat_cluster";
    if (0 != common_read2_0("data/example/linkMatr2.txt", net.weightMatr) ||
        net.weightMatr.size() <= 0 || net.weightMatr[0].size() <= 0) {
      ERROR();
      break;
    }
    weightMatr_2_linkMatr(net.linkMatr, net.weightMatr);
    net_cal_cluster(net);
    net_save0(net);
    cout << net << endl;
    break;
  } while (0);

  SHOW_TIME(cout);  // 显示系统时间
  return 0;
}
//**//********************************************************************
#endif
