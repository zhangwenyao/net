#include "main.h"
#ifdef MAIN_NET_BA

#include "common.h"
#include "networks.h"
using namespace std;

//**//**************************************************//**//*
int main_net_ba(int argc, char** argv)
{
  // SHOW_TIME(cout); // 显示系统时间
  string DATA_DIR = "data/BA/";

  do {
    Networks net;
    net.saveName = net.readName = DATA_DIR + "BA";
    net.nodeSize = 1000000; // 节点数
    net.ba.M0 = 3;
    net.ba.M = 2;
    net.seed = 1;
    net.argv = "--init_seed0 --cal_p2p BA --stat --print --save";

    // 带参数运行
    if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
      _ERR("net.read_params(argc, argv)");
      break;
    }

    // 功能模块
    if (0 != net.run().runStatus) {
      _ERR("net.run");
      cerr << net << endl;
      break;
    }

    /*
    p2p_2_link(net.link, net.p2p, 0);
    VVNodeType link(net.link.size() / 2, VNodeType(2, 0));
    for (size_t i = 0; i < link.size(); ++i) {
      link[i][0] = net.link[i * 2] + 1;
      link[i][1] = net.link[i * 2 + 1] + 1;
    }
    common_save2((DATA_DIR + "BA_N=1E4_M0=" + to_string(net.ba.M0)
                     + "_M=" + to_string(net.ba.M) + "_link.txt")
                     .c_str(),
        link);
    */
    double H = 0, sk2 = 0, sk = 0;
    for (size_t i = 0; i < net.nodeSize; ++i) {
      NodeType k = net.nodeDeg[i];
      sk += k;
      sk2 += (double)k * k;
    }
    sk2 /= net.nodeSize;
    sk /= net.nodeSize;
    H = sk2 / (sk * sk);
    INFORM(H);
  } while (0);

  return 0;
}
//**//**************************************************//**//*
#endif
