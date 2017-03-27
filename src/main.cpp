// g++ -o main.exe *.cpp -O3 -Wall
#include "common.h"
#include "networks.h"
using namespace std;

int main(int argc, char **argv)
{
    SHOW_TIME(cout);    // 显示系统时间

    //**//****************************************************//*
    do{
        Network net;
        net.saveName = net.readName = "data/link-matrix2";
        //net.nodeSize = 1024;    // 节点数
        //net.Pow_gamma = 2.5;    // 度分布幂律分布的幂指数
        //net.kMin = 4;   // 最小度
        //net.kMax = net.kMin + sqrt(net.nodeSize) - 1;   // 最大度
        //while(0 == (net.seed = RAND2_INIT(net.seed)));    // 初始化随机数种子
        //net.seed = RAND2_INIT(1);    // 初始化随机数种子
        if(0 != net_read_linkMatr_0(net, "data/link-matrix2.txt") || 0 != linkMatr_2_p2p(net.p2p, net.linkMatr) || 0 != net_p2p_2_degArr(net)){
            ERROR();
            break;
        }
        if(0 != net_betweenness(net) || 0 != net_newman_modularity(net)){
        //if(0 != net_newman_modularity(net)){
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

