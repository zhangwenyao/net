// g++ -o main.exe *.cpp -O3 -Wall
#include "net.h"
#ifdef NET_ACTOR

#include "NetActor.h"
#include "common.h"
#include "networks.h"
using namespace std;
//**//****************************************************//*
int main(int argc, char **argv) {
  SHOW_TIME(cout);  // ��ʾϵͳʱ��

  do {
    Networks net;
    net.saveName = net.readName = "../netDataSet/undirected_weight/actor/actor";
    net.weightFlag = 1;
    if (0 != data_read_actor_p2p(net.p2p, (net.readName + ".dat").c_str())) {
      ERROR();
      break;
    }
    sort_p2p(net.p2p);
    p2p_2_vvweight_sort(net.vvweight, net.p2p);
    net.argv = "cal_p2p p2p_fix stat save0 print";

    // ����������
    if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
      ERROR("net.read_params(argc, argv)");
      break;
    }

    // ����ģ��
    if (0 != net.run().runStatus) {
      ERROR("net.run");
      cerr << net << endl;
      break;
    }
  } while (0);

  SHOW_TIME(cout);  // ��ʾϵͳʱ��
  return 0;
}
//**//****************************************************//*
#endif