// g++ -o main.exe *.cpp -O3 -Wall
#include "common.h"
#include "networks.h"
#ifdef NET_ACTOR

using namespace std;
//**//****************************************************//*
int main(int argc, char **argv)
{
    SHOW_TIME(cout);    // 显示系统时间

    do {
        Network net;
        net.saveName = net.readName = "../netDataSet/undirected_weight/actor/actor";
        net.weightFlag = 1;
        if(0 != data_read_actor_p2p(net.p2p, (net.readName + ".dat").c_str())){
            ERROR();
            break;
        }
        sort_p2p(net.p2p);
        p2p_2_vvweight_sort(net.vvweight, net.p2p);
        net.argv = "cal_p2p p2p_fix stat save0 print";


        // 带参数运行
        if (argc > 1 && 0 != net_read_params(net, argc - 1, argv + 1)) {
            ERROR("net_read(argc, argv)");
            break;
        }

        // 功能模块
        if (0 != net_run(net) || net.status < 0) {
            ERROR("net_new");
            break;
        }
    } while (0);

    SHOW_TIME(cout);    // 显示系统时间
    return 0;
}

#endif
