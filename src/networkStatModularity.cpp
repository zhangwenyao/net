#include "StatModularity.h"
#include "networkStatModularity.h"
#ifdef STAT_MODULARITY

#include "common.h"
using namespace std;

//**//****************************************************//*
int net_read_params_modularity(istream& is, Network& net)
{
    return 0;
}

int net_save_params_modularity(ostream& os, const Network& net)
{
    if(!os) return -1;
    os  << "--moduCoef\t" << net.moduCoef
        << "\n--moduSize\t" << (net.moduRange.size() > 1 ? net.moduRange.size() - 1 : 0)
        << '\n';
    return 0;
}

int net_save_modularity(const Network& net, const char *name)
{
    string fn;
    if(name != NULL && name[0] != '\0') fn = name;
    else{
        stringstream ss;
        ss << net.seed;
        fn = net.saveName + '_' + ss.str();
    }
    int f = 0;
    if(!net.moduRange.empty()) f |= common_save1((fn + "_moduRange.txt").c_str(), net.moduRange, '\n');
    if(!net.moduVal.empty()) f |= common_save1((net.saveName + "_moduVal.txt").c_str(), net.moduVal, net.priChar);
    if(!net.moduLKK.empty()) f |= common_save2((net.saveName + "_moduLKK.txt").c_str(), net.moduLKK, net.priChar);
    if(!net.moduStk.empty()) f |= net_save_moduStk(net, (net.saveName + "_moduLKK.txt").c_str());
    return f;
}
//**//****************************************************//*
int net_clear_modularity(Network& net)
{
    net.moduVal.clear();
    net.moduStk.clear();
    net.moduNum.clear();
    net.moduRange.clear();
    for(VVLinkTypeItr i = net.moduLKK.begin(); i != net.moduLKK.end(); i++)  i->clear();
    net.moduLKK.clear();
    return 0;
}

//**//****************************************************//*
int net_save_moduStk(const Network& net, ostream& os)
{
    return save_moduStk(os, net.moduStk, net.moduRange);
}

int net_save_moduStk(const Network& net, const char *name)
{
    return save_moduStk(net.moduStk, net.moduRange, name);
}

//**//****************************************************//*
int net_modularity(Network &net)
{
    int f = 0;
    f = cal_modularity(net.moduVal, net.moduStk, net.moduNum, net.moduRange, net.p2p, net.p2pIn, net.dirFlag);
    f |= moduStk_sort(net.moduStk, net.moduRange, net.moduNum);
    f |= cal_moduLKK(net.moduLKK, net.moduRange.size() - 1 , net.moduVal, net.p2p);
    f |= cal_moduCoef(net.moduCoef, net.moduLKK, net.linkSize);
    return f;
}

int net_cal_modularity(Network &net)
{
    return cal_modularity(net.moduVal, net.moduStk, net.moduNum, net.moduRange, net.p2p, net.p2pIn, net.dirFlag);
}

//**//****************************************************//*
#ifdef STAT_BETWEENNESS
#include "StatBetweenness.h"
#include "networkStatBetweenness.h"
int net_fix_modularity(Network& net, const NodeType mSize)
{
    net_betweenness(net);
    net_modularity(net);
    p2p_2_link(net.link, net.p2p, net.dirFlag); // 连边p2p转为link
    net.linkSize = net.link.size() / 2;
    sort_link_betwEdge(net.link, net.betwEdge); // 按介数排序边link
    for(LinkType l = net.linkSize; net.moduRange.size() - 1 < mSize && l > 0;){
        l = --net.linkSize;
        del_pij(net.link[l*2], net.link[l*2+1], net.p2p, net.p2pIn, net.dirFlag);   // 删除连边p2p中介数最大的边
        net_cal_modularity(net);    // 更新分组情况
    }
    if(mSize > 0){
        net_betweenness(net);   // 计算新网络的介数
        net.linkSize = net.link.size() / 2;
        link_2_p2p(net.p2p, net.link, net.p2pIn, net.nodeSize, net.dirFlag);    // 通过link还原网络连边p2p
        cal_moduLKK(net.moduLKK, net.moduRange.size() - 1, net.moduVal, net.p2p);   // 统计原网络在新分组下的不同组之间的连边数
        cal_moduCoef(net.moduCoef, net.moduLKK, net.linkSize);  // 新分组系数
    }
    return 0;
}
#endif

//**//****************************************************//*
#endif  // STAT_MODULARITY

