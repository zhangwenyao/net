// g++ -o main.exe *.cpp -O3 -Wall
#include "common.h"
#include "networks.h"
using namespace std;

int main(int argc, char **argv)
{
    SHOW_TIME(cout);    // 显示系统时间
    
    Network net;
    do{
        net.seed = 1;
        net.weight = 1;
        net.dir = 1;
        net.readName = "test/matrix";
        net.saveName = "test/m";
        if(0 != common_read2_0("test/a.txt", net.weightMatr) || net.weightMatr.size() <= 0 || net.weightMatr[0].size() <= 0){
            ERROR();
            break;
        }
        weightMatr_2_linkMatr(net.linkMatr, net.weightMatr);
        net_cal_cluster(net);
        net_save0(net);
        cout << net << endl;
        break;

    }while(0);

    SHOW_TIME(cout);    // 显示系统时间
    return 0;
}

