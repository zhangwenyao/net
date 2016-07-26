// g++ -o main.exe *.cpp -O3 -Wall
#include "common.h"
#include "networks.h"
using namespace std;

int main(int argc, char **argv)
{
    SHOW_TIME(cout);    // ��ʾϵͳʱ��

    //**//****************************************************//*
    do{
        Network net;
        net.saveName = net.readName = "data/Max_power2.5";
        net.nodeSize = 1024;    // �ڵ���
        net.Pow_gamma = 2.5;    // �ȷֲ����ɷֲ�����ָ��
        net.kMin = 4;   // ��С��
        net.kMax = net.kMin + sqrt(net.nodeSize) - 1;   // ����
        //while(0 == (net.seed = RAND2_INIT(net.seed)));    // ��ʼ�����������
        net.seed = RAND2_INIT(1);    // ��ʼ�����������
        if(0 != net_run(net, "cal_deg power cal_p2p Max stat save")){
            ERROR();
            break;
        }
    }while(0);

    SHOW_TIME(cout);    // ��ʾϵͳʱ��
    return 0;
}

