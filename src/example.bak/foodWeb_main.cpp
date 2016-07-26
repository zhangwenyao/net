#include <iostream>
#include <fstream>
#include <algorithm>
#include "common.h"
#include "foodWeb.h"

using namespace std;

//**//************************** code example ******************************************
#ifdef NET_FOODWEB
do{
    Network net;
    net.readName = "database/foodWeb/Grassland/Grassland";
    net.saveName = net.readName + "_n0";
    net.dir = 1;
    net.argv = "cal_p2p read_link stat save0 print";
    if (0 != net_new(net) || net.status < 0) {
        ERROR("net_new");
        break;
    }
}while(0);
do{
    Network net;
    net.readName = "database/foodWeb/Grassland/Grassland";
    net.saveName = net.readName + "_n1";
    net.dir = 1;
    net.argv = "cal_p2p p2p stat save0 print";

    //net.argv = "init_seed0 cal_p2p p2p stat save print";
    // 带参数运行
    if (argc > 1 && 0 != net_read_params(net, argc - 1, argv + 1)) {
        ERROR("net_read(argc, argv)");
        break;
    }

    // 读取link -> p2p
    if(0 != data_read_foodWeb1(net.link, (net.readName + "_link.txt").c_str())){
        ERROR();
        break;
    }

    // 功能模块
    if (0 != net_new(net) || net.status < 0) {
        ERROR("net_new");
        break;
    }
}while(0);
#endif

//**//********************************************************************
int data_read_foodWeb1(VNodeType& link, const char *name)
{
    if(name == NULL || name[0] == '\0'){
        ERROR();
        return -1;
    }
    ifstream is(name);
    if(!is){
        ERROR(name);
        return -1;
    }
    LinkType c = 0;
    for(NodeType i, j; is >> i >> j; c++){
        if(i > 0 && j > 0){
            link.push_back(--i);
            link.push_back(--j);
        }
    }
    is.close();
    cout << name << '\t' << link.size() / 2 << "\tall:\t" << c << "\n";
    return 0;
}
//**//********************************************************************

