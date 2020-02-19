#include "evolution.h"
#ifdef MAIN_CORRELATION2_EVOLUTION

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// **********************************************************
int main_func::correlation2::evolution(int argc, char** argv)
{
  Networks net;
  net.readName = dirData + name;
  net.argv = "--cal_params read"
             " --cal_p2p read_p2p";
  _ERR(0 != net.run().runStatus);
  _ERR(p2p_2_link(net.link, net.p2p, net.dirFlag));
  net.linkSize = net.link.size() / 2;

  const string kPStr = "d1000";
  const double kP = 1.0 / 1000;
  for (long seed = kSeedMin; seed <= kSeedMax; ++seed) {
    rand_seed(seed);
    Networks net2;
    net2.link = net.link;
    for (auto delPer : kDelPers) {
      Networks net3;
      const LinkType delCount
          = net2.link.size() / 2 - net.linkSize * (1 - kP * delPer);
      net.saveName = dirData + name + "_" + to_string(delPer) + kPStr;
      _ERR(delLink_link_ranLink(net2.link, delCount));
      _ERR(link_2_p2p(net3.p2p, net2.link, net3.nodeSize));
      net3.saveName = net.saveName + "_" + to_string(seed);
      net3.argv = "--stat";
      _ERR(net3.run().runStatus);
      net3.save_params();
      cout << net3 << seed << "\t/ " << kSeedMax << endl;
    }
  }
  return 0;
}

#endif
