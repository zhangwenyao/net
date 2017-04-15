#include "common.h"
#include "networks.h"
#ifdef NET_BA

//**//********************************************************************
int main() {
  do {
    Networks net;
    net.saveName = net.readName = "data/BA";
    net.nodeSize = 100;  // 节点数
    net.params_BA.M0 = 3;
    net.params_BA.M = 2;
    while (0 == (net.seed = RAND2_INIT(net.seed)))
      continue;  // 初始化随机数种子
    if (0 != net_run(net, "cal_p2p BA save")) {
      ERROR();
      break;
    }
  } while (0);
  return 0;
}
//**//********************************************************************
#endif
