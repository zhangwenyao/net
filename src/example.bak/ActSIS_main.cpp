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
        net.saveName = net.readName = "data/BA";
        net.dirFlag = 0;
        net.nodeSize = 100;
        net.BA_M = 4;
        net.BA_M0 = 5;
        ParamsSIS params;
        params.M = 70;
        params.p0 = 0.1;
        params.p = 0.01;
        params.lambda = 0.1;
        params.t_r = 80000;
        params.t_av = 100000;
        //while(0 == (net.seed = RAND2_INIT(net.seed)));    // 初始化随机数种子
        net.seed = RAND2_INIT(1);    // 初始化随机数种子
        if(0 != net_BA(net) || 0 != net_p2p_2_degArr(net)){
            ERROR();
            break;
        }
        if(0 != net_act_SIS(net, params)){
            ERROR();
            break;
        }
        cout << params.ksi << "\t" << params.nNum << "\t" << params.nSum << "\t" << params.n2Sum << endl;
        //if(0 != net_save(net)){
            //ERROR();
            //break;
        //}
    }while(0);

    SHOW_TIME(cout);    // 显示系统时间
    return 0;
}

