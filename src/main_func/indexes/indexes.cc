#include "indexes.h"
#ifdef MAIN_INDEXES

#include "../../common/common.h"
#include "../../network/networks.h"
#include "../../statistics/indexes/indexes.h"
using namespace std;
using namespace common;
using namespace network;
using namespace network::indexes;

//**//**************************************************//**//*
#ifdef MAIN_INDEXES_DATA
int main_func::indexes::networks_data(int argc, char** argv) {
  return EXIT_SUCCESS;
}
#endif  // MAIN_INDEXES_DATA

#ifdef MAIN_INDEXES_STAT
int main_func::indexes::networks_stat(int argc, char** argv) {
  for (auto& dataset : kDatasetNames) {
    string data_dir = kDataDir + "/" + dataset + "/",
           stat_dir = kStatDir + '/' + dataset + "/";
    INFORM(dataset, " in ", data_dir);
    mkdirs(stat_dir.c_str());

    Networks net;
    net.readName = data_dir + dataset;
    net.saveName = stat_dir + dataset;
    net.dirFlag = 0;
    net.argv =
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
      _ERR(read_link(net.link, (net.readName + ".link.txt").c_str()));
      net.linkSize = net.link.size() / 2;
      link_2_nodeSize(net.nodeSize, net.link);

      _ERR(link_2_p2p(net.p2p, net.link, net.nodeSize));
      _ERR(net.p2p_2_degArr().runStatus);
      net.kMin = net.degArrVal.front();
      net.kMax = net.degArrVal.back();
      net.status = 1;
      INFORM("nodeSize: ", net.nodeSize, "\tlinkSize: ", net.linkSize);
    }

    {  // stat indexes
      INFORM("stat indexes");
      mkdirs(stat_dir.c_str());
      string filename, filename2, filename3;
      // local_index1
      filename = net.saveName + ".local_index1.txt";
      filename2 = net.saveName + ".neibor_communities.txt";
      if (kClean || !is_exist(filename.c_str()) ||
          !is_exist(filename2.c_str())) {
        VLinkType local_index1;
        VNodeType neibor_communities;
        cal_local_index1(local_index1, neibor_communities, net.p2p);
        save1(filename.c_str(), local_index1, '\n');
        save1(filename2.c_str(), neibor_communities, '\n');
        INFORM("save file: ", filename);
        INFORM("save file: ", filename2);
      }
      // local_index2
      filename = net.saveName + ".local_index2.txt";
      filename2 = net.saveName + ".neibor2_numbers.txt";
      filename3 = net.saveName + ".neibor2_communities.txt";
      if (kClean || !is_exist(filename.c_str()) ||
          !is_exist(filename2.c_str()) || !is_exist(filename3.c_str())) {
        VLinkType local_index2;
        VNodeType neibor2_numbers, neibor2_communities;
        cal_local_index2(local_index2, neibor2_numbers, neibor2_communities,
                         net.p2p);
        save1(filename.c_str(), local_index2, '\n');
        save1(filename2.c_str(), neibor2_numbers, '\n');
        save1(filename3.c_str(), neibor2_communities, '\n');
        INFORM("save file: ", filename);
        INFORM("save file: ", filename2);
        INFORM("save file: ", filename3);
      }
    }
    // _ERR(net.save_params().runStatus);
  }
  return EXIT_SUCCESS;
}
#endif  // MAIN_INDEXES_STAT

//**//****************************************************//*
#endif