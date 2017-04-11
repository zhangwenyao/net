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
    os  << "--params_modularity.Coef\t" << net.params_modularity.Coef
        << "\n--params_modularity.Size\t" << net.params_modularity.Range.size()
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
    if(!net.params_modularity.Range.empty()) f |= common_save1((fn + "_stat_modularity.Range.txt").c_str(), net.params_modularity.Range, '\n');
    if(!net.params_modularity.Val.empty()) f |= common_save1((fn + "_stat_modularity.Val.txt").c_str(), net.params_modularity.Val, net.priChar);
    if(!net.params_modularity.LKK.empty()) f |= common_save2((fn + "_stat_modularity.LKK.txt").c_str(), net.params_modularity.LKK, net.priChar2);
    if(!net.params_modularity.Stk.empty()) f |= net_save_stat_modularity.Stk(net, (fn + "_stat_modularity.Stk.txt").c_str(), net.priChar2);
    if(!net.params_modularity.NodeCoef.empty()) f |= common_save1((fn + "_stat_modularity.NodeCoef.txt").c_str(), net.params_modularity.NodeCoef, net.priChar);
    return f;
}
//**//****************************************************//*
int net_clear_modularity(Network& net)
{
    net.params_modularity.NodeCoef.clear();
    net.params_modularity.Val.clear();
    net.params_modularity.Stk.clear();
    net.params_modularity.Num.clear();
    net.params_modularity.Range.clear();
    for(VVLinkTypeItr i = net.params_modularity.LKK.begin(); i != net.params_modularity.LKK.end(); i++)  i->clear();
    net.params_modularity.LKK.clear();
    return 0;
}

//**//****************************************************//*
int net_save_moduStk(const Network& net, ostream& os, const char c)
{
    return save_moduStk(os, net.params_modularity.Stk, net.params_modularity.Range, c);
}

int net_save_moduStk(const Network& net, const char *name, const char c)
{
    return save_moduStk(net.params_modularity.Stk, net.params_modularity.Range, name, c);
}

//**//****************************************************//*
int net_modularity(Network &net)
{
    int f = 0;
    f = cal_modularity(net.params_modularity.Val, net.params_modularity.Stk, net.params_modularity.Num, net.params_modularity.Range, net.p2p, net.p2pIn, net.dirFlag);
    f |= moduStk_sort(net.params_modularity.Stk, net.params_modularity.Range, net.params_modularity.Num);
    f |= cal_moduLKK(net.params_modularity.LKK, net.params_modularity.Range.size() , net.params_modularity.Val, net.p2p, net.dirFlag);
    f |= cal_moduCoef(net.params_modularity.Coef, net.params_modularity.LKK, net.dirFlag);
    f |= cal_moduNodeCoef(net.params_modularity.NodeCoef, net.params_modularity.Range.size(), net.params_modularity.Val, net.p2p);
    return f;
}

int net_cal_modularity(Network &net)
{
    return cal_modularity(net.params_modularity.Val, net.params_modularity.Stk, net.params_modularity.Num, net.params_modularity.Range, net.p2p, net.p2pIn, net.dirFlag);
}

//**//****************************************************//*
#ifdef STAT_BETWEENNESS
#include "StatBetweenness.h"
#include "networkStatBetweenness.h"
int net_newman_modularity(double &qMax, Network& net, NodeType mSize)
{
    if(mSize <= 0) mSize = net.nodeSize;
    qMax = 0;
    if(mSize <= 1){
        qMax = 1;
        ERROR();
        return 0;
    }
    const VVNodeType p2p = net.p2p;
    if(net.link.empty()) p2p_2_link(net.link, net.p2p, net.dirFlag);
    net_modularity(net);
    if(net.params_modularity.Coef > qMax) qMax = net.params_modularity.Coef;
    for(LinkType l = net.linkSize; l > 0 && net.params_modularity.Range.size() < mSize;){
        net_betweenness(net);
        sort_link_betwEdge(net.link, net.params_betweenness.betwEdge, l--); // 按介数排序边link
        del_pij(net.link[l*2], net.link[l*2+1], net.p2p, net.p2pIn, net.dirFlag);   // 删除连边p2p中介数最大的边
        cal_modularity(net.params_modularity.Val, net.params_modularity.Stk, net.params_modularity.Num, net.params_modularity.Range, net.p2p, net.p2pIn, net.dirFlag);
        moduStk_sort(net.params_modularity.Stk, net.params_modularity.Range, net.params_modularity.Num);
        cal_moduLKK(net.params_modularity.LKK, net.params_modularity.Range.size() , net.params_modularity.Val, p2p, net.dirFlag); // 统计原网络在新分组下的不同组之间的连边数
        cal_moduCoef(net.params_modularity.Coef, net.params_modularity.LKK, net.dirFlag);  // 新分组系数
        if(net.params_modularity.Coef > qMax) qMax = net.params_modularity.Coef;
    }
    return 0;
}
#endif

//**//****************************************************//*
#endif  // STAT_MODULARITY

