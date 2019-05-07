#include "stat.h"
#ifdef MAIN_EXTREMUM_STAT

#include "../../common/common.h"
#include "../../model/extremum/extremum.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;
using namespace network::extremum;

//**//****************************************************//*
int main_func::extremum_stat(int argc, char** argv)
{
  string stat_dir
      = "/media/yao/Server1T/net/data/extremum/nature/2.5_4/stat/";
  MKDIR(stat_dir.c_str());
  for (int e = 12; e <= 12; ++e) {
    cout << "e\t" << e << endl;
    string data_dir
        = string("/media/yao/Server1T/net/data/extremum/nature/2.5_4/") + "2^"
        + to_string(e) + "/",
        s;
    for (int seed = 1; seed <= 1; ++seed) {
      cout << "e\t" << e << "\tseed\t" << seed << endl;
      Networks net;
      // 带参数运行
      if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
        ERROR("net.read_params(argc, argv)");
        break;
      }

      _ERR(net.read_params(
                  (data_dir + "kMin4_" + to_string(seed) + ".Min.params.txt")
                      .c_str())
               .runStatus);
      net.readName = data_dir + "kMin4_" + to_string(seed);
      _ERR(net.read_degArr().runStatus);
      net.saveName = net.readName
          = data_dir + "kMin4_" + to_string(seed) + ".Min";
      _ERR(read_lkk3((net.readName + ".lkk3.txt").c_str(), net.lkk3));

      //功能模块
      net.argv = "--stat --print";
      if (0 != net.run().runStatus) {
        ERROR("net.run");
        // cerr << net << endl;
        net.saveName += "_error";
        net.save_params(net.saveName.c_str());
        break;
      } else {
        net.save_params(net.saveName.c_str());
      }

    } // for seed
  }   // for e

  return 0;
}
//**//****************************************************//*
#endif
