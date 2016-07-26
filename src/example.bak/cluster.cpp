// g++ -o main.exe *.cpp -O3 -Wall
#include "common.h"
#include "networks.h"
using namespace std;

int main(int argc, char **argv)
{
    SHOW_TIME(cout);    // ��ʾϵͳʱ��

    do{
        Network net;
        net.seed = 1;
        net.readName = "../data/test/test0";
        net.saveName = "../data/test/test";
        net.argv = "init_seed cal_p2p read_weight_0 stat save0 print"; //" stat save0 print";

        // ����������
        if (argc > 1 && 0 != net_read_params(net, argc - 1, argv + 1)) {
            ERROR("net_read(argc, argv)");
            break;
        }

        // ����ģ��
        if (0 != net_new(net) || net.status < 0){
            ERROR("net_new");
        }
    }while(0);

    SHOW_TIME(cout);    // ��ʾϵͳʱ��
    return 0;
}

