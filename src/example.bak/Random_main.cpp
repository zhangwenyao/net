// g++ -o main.exe *.cpp -O3 -Wall
#include "common.h"
#include "networks.h"
using namespace std;

int main(int argc, char **argv)
{
    SHOW_TIME(cout);    // 显示系统时间

    do{
        Network net;
        net.seed = 4;
        net.saveName = net.readName = "data/random2.7_128";
        net.nodeSize = 128;     // 节点数
        net.net_random.power_gamma = 2.7;     // 度分布幂律分布的幂指数
        net.kMin = 6;
        net.argv = "init_seed cal_deg power cal_p2p random stat print save";

        // 带参数运行
        if (argc > 1 && 0 != net_read_params(net, argc - 1, argv + 1)) {
            ERROR("net_read(argc, argv)");
            break;
        }

        net.kMax = net.kMin * pow(net.nodeSize, 1 / (net.net_random.power_gamma - 1.));    // 最大度
        if(net.kMax < net.kMin) net.kMax = net.kMin;
        if(net.kMax >= net.nodeSize) net.kMax = net.nodeSize - 1;
       
        // 功能模块
        if (0 != net_run(net) || net.status < 0) {
            ERROR("net_run");
            cerr << net << endl;
            break;
        }
    }while(0);

    SHOW_TIME(cout);    // 显示系统时间
    return 0;
}

