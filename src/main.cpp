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
        net.saveName = net.readName = "data/random-power2";
        net.dirFlag = 0;
        net.nodeSize = 1000;
        net.net_degree.power_gamma = 2;
        net.kMin = 2;
        net.kMax = sqrt(net.nodeSize);

        net.act_SIS.M = 70;
        net.act_SIS.p0 = 0.1;
        net.act_SIS.p = 0.01;
        net.act_SIS.lambda = 0.11;
        net.act_SIS.t_r = 80;
        net.act_SIS.t_av = 10;

        //while(0 == (net.seed = RAND2_INIT(net.seed)));    // 初始化随机数种子
        net.seed = RAND2_INIT(1);    // 初始化随机数种子
        if(0 != net_run(net, "cal_deg power cal_p2p random stat") || 0 != net_p2p_2_degArr(net)){
            ERROR();
            break;
        }
        if(0 != net_act_SIS(net)){
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

