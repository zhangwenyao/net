#include "betweenness.h"
#ifdef MAIN_BETWEENNESS

#include <boost/graph/betweenness_centrality.hpp>

#include "../../common/common.h"
#include "../../network/networks.h"
#include "../../statistics/betweenness/betweenness.h"
#include "../../statistics/stat.h"
using namespace std;
using namespace common;
using namespace network;

//**//**************************************************//**//*
#ifdef MAIN_BETWEENNESS_DATA
int main_func::betweenness::networks_data(int argc, char **argv) {
  for (int i = 0; i < DATASET_SIZE; i++) {
    string dataset = DATASET_NAMES[i];
    string data_dir = kDataDir + dataset + "/";
    string link_file0 = data_dir + dataset + ".linkname.txt",
           link_file = data_dir + dataset + ".link0.txt",
           name_file = data_dir + dataset + ".name.txt";
    INFORM(dataset, ": ", link_file0);
    linkname_2_link<NodeType>(link_file0.c_str(), link_file.c_str(),
                              name_file.c_str());
  }
  return EXIT_SUCCESS;
}
#endif

#ifdef MAIN_BETWEENNESS_STAT
int main_func::betweenness::networks_stat(int argc, char **argv) {
  for (int i = 0; i < DATASET_SIZE; i++) {
    string dataset = DATASET_NAMES[i];
    string data_dir = kDataDir + dataset + "/", stat_dir = data_dir;
    INFORM(dataset, " in ", data_dir);
    mkdirs(stat_dir.c_str());

    Networks net;
    string fn_full = data_dir + dataset;
    net.readName = fn_full;
    net.saveName = fn_full;
    net.seed = kSeed0;
    net.dirFlag = 0;
    net.argv =
        // "--init_seed0"
        " --cal_p2p read_link"
        " --stat"
        " --save";

    // 带参数运行
    if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
      ERROR("net.read_params(argc, argv)");
      break;
    }

    // 功能模块
    // if (0 != net.run().runStatus) {
    //   ERROR("net.run");
    //   cerr << net << endl;
    //   net.saveName += "_error";
    //   net.save_params();
    // }

    {  // read links
      _ERR(read_link_unique(net.link, (fn_full + ".link0.txt").c_str()));
      net.linkSize = net.link.size() / 2;
      link_2_nodeSize(net.nodeSize, net.link);

      _ERR(link_2_p2p(net.p2p, net.link, net.nodeSize));
      _ERR(net.p2p_2_degArr().runStatus);
      net.kMin = net.degArrVal.front();
      net.kMax = net.degArrVal.back();
      net.status = 1;
    }

    {
      INFORM();
      // _ERR(net.stat_betweenness().runStatus);
      net.save_data();
    }
    INFORM();

    net.lkk.clear();
    net.nodeDeg.clear();
    _ERR(net.save_params().runStatus);
  }
  return EXIT_SUCCESS;
}
#endif
#ifdef MAIN_BETWEENNESS_BOOST
int main_func::betweenness::networks_stat_boost(int argc, char **argv) {
  // Graph g;
  // map<int, string> vertexName;
  // map<string, int> nameVertexMap;
  // load node from -> to
  // add edge (from, to)
  return EXIT_SUCCESS;
}
#endif

//**//****************************************************//*
#endif