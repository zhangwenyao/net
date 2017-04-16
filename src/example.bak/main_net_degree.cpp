// g++ -o main.exe *.cpp -O3 -Wall
#include "net.h
#ifdef NET_DEGREE

#include "common.h"
#include "networks.h"
using namespace std;
//**//**************************************************//**//*
int main(int argc, char **argv) {
  SHOW_TIME(cout);  // ��ʾϵͳʱ��

  do {
    Networks net;
    net.saveName = net.readName = "data/degree";
    net.nodeSize = 1000;            // �ڵ���
    net.degree.power_gamma = 2.7;  // �ȷֲ����ɷֲ�����ָ��
    net.kMin = 3;
    net.seed = 1;
    net.argv = "init_seed0 cal_deg power print save";

    // ����������
    if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
      ERROR("net.read_params(argc, argv)");
      break;
    }

    net.kMax = net.kMin * pow(net.nodeSize, 1 / (net.degree.power_gamma - 1.));
    if (net.kMax < net.kMin) net.kMax = net.kMin;
    if (net.kMax >= net.nodeSize) net.kMax = net.nodeSize - 1;

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
//**//**************************************************//**//*
#endif