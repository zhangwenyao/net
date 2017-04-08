// g++ -o main.exe *.cpp -O3 -Wall
#include "common.h"
#include "networks.h"
using namespace std;

int main(int argc, char **argv)
{
    SHOW_TIME(cout);    // 显示系统时间

    //**//****************************************************//*
    do{
        Network net, net2;
        net.saveName = net.readName = "data/random-power2.5";
        net.dirFlag = 0;
        net.nodeSize = 1000;
        net.Pow_gamma = 2.5;
        net.kMin = 2;
        net.kMax = sqrt(net.nodeSize);

        ParamsSIS params;
        net.params = &params;
        params.M = 70;
        params.p0 = 0.1;
        params.p = 0.01;
        params.lambda = 0.16;
        params.t_r = 800;
        params.t_av = 1000;

        //while(0 == (net.seed = RAND2_INIT(net.seed)));    // 初始化随机数种子
        net.seed = RAND2_INIT(1);    // 初始化随机数种子
        if(0 != net_run(net, "cal_deg power cal_p2p random stat") || 0 != net_p2p_2_degArr(net)){
            ERROR();
            break;
        }
        if(0 != net_act_SIS(net, params)){
            ERROR();
            break;
        }
        if(0 != net_save(net)){
            ERROR();
            break;
        }
    }while(0);

    SHOW_TIME(cout);    // 显示系统时间
    return 0;
}

