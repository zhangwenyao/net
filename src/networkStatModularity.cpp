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
        << "\n--moduSize\t" << net.moduRange.size()
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
    if(!net.moduVal.empty()) f |= common_save1((fn + "_moduVal.txt").c_str(), net.moduVal, net.priChar);
    if(!net.moduLKK.empty()) f |= common_save2((fn + "_moduLKK.txt").c_str(), net.moduLKK, net.priChar2);
    if(!net.moduStk.empty()) f |= net_save_moduStk(net, (fn + "_moduStk.txt").c_str(), net.priChar2);
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
int net_save_moduStk(const Network& net, ostream& os, const char c)
{
    return save_moduStk(os, net.moduStk, net.moduRange, c);
}

int net_save_moduStk(const Network& net, const char *name, const char c)
{
    return save_moduStk(net.moduStk, net.moduRange, name, c);
}

//**//****************************************************//*
int net_modularity(Network &net)
{
    int f = 0;
    f = cal_modularity(net.moduVal, net.moduStk, net.moduNum, net.moduRange, net.p2p, net.p2pIn, net.dirFlag);
    f |= moduStk_sort(net.moduStk, net.moduRange, net.moduNum);
    f |= cal_moduLKK(net.moduLKK, net.moduRange.size() , net.moduVal, net.p2p, net.dirFlag);
    f |= cal_moduCoef(net.moduCoef, net.moduLKK, net.dirFlag);
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
int net_newman_modularity(Network& net, NodeType mSize)
{
    if(mSize <= 0) mSize = net.nodeSize;
    double qMax = 0;
    if(mSize <= 1){
        qMax = 1;
        ERROR();
        return 0;
    }
    const VVNodeType p2p = net.p2p;
    if(net.link.empty()) p2p_2_link(net.link, net.p2p, net.dirFlag);
    net_modularity(net);
    if(net.moduCoef > qMax) qMax = net.moduCoef;
    for(LinkType l = net.linkSize; l > 0 && net.moduRange.size() < mSize;){
        net_betweenness(net);
        sort_link_betwEdge(net.link, net.betwEdge, l--); // 按介数排序边link
        del_pij(net.link[l*2], net.link[l*2+1], net.p2p, net.p2pIn, net.dirFlag);   // 删除连边p2p中介数最大的边
        cal_modularity(net.moduVal, net.moduStk, net.moduNum, net.moduRange, net.p2p, net.p2pIn, net.dirFlag);
        moduStk_sort(net.moduStk, net.moduRange, net.moduNum);
        cal_moduLKK(net.moduLKK, net.moduRange.size() , net.moduVal, p2p, net.dirFlag); // 统计原网络在新分组下的不同组之间的连边数
        cal_moduCoef(net.moduCoef, net.moduLKK, net.dirFlag);  // 新分组系数
        if(net.moduCoef > qMax) qMax = net.moduCoef;
    }
    cout << qMax << endl;
    return 0;
}
#endif

//**//****************************************************//*
#endif  // STAT_MODULARITY

