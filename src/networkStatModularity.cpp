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
    os  << "--stat_modularity.Coef\t" << net.stat_modularity.Coef
        << "\n--stat_modularity.Size\t" << net.stat_modularity.Range.size()
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
    if(!net.stat_modularity.Range.empty()) f |= common_save1((fn + "_stat_modularity.Range.txt").c_str(), net.stat_modularity.Range, '\n');
    if(!net.stat_modularity.Val.empty()) f |= common_save1((fn + "_stat_modularity.Val.txt").c_str(), net.stat_modularity.Val, net.priChar);
    if(!net.stat_modularity.LKK.empty()) f |= common_save2((fn + "_stat_modularity.LKK.txt").c_str(), net.stat_modularity.LKK, net.priChar2);
    if(!net.stat_modularity.Stk.empty()) f |= net_save_stat_modularity.Stk(net, (fn + "_stat_modularity.Stk.txt").c_str(), net.priChar2);
    if(!net.stat_modularity.NodeCoef.empty()) f |= common_save1((fn + "_stat_modularity.NodeCoef.txt").c_str(), net.stat_modularity.NodeCoef, net.priChar);
    return f;
}
//**//****************************************************//*
int net_clear_modularity(Network& net)
{
    net.stat_modularity.NodeCoef.clear();
    net.stat_modularity.Val.clear();
    net.stat_modularity.Stk.clear();
    net.stat_modularity.Num.clear();
    net.stat_modularity.Range.clear();
    for(VVLinkTypeItr i = net.stat_modularity.LKK.begin(); i != net.stat_modularity.LKK.end(); i++)  i->clear();
    net.stat_modularity.LKK.clear();
    return 0;
}

//**//****************************************************//*
int net_save_stat_modularity.Stk(const Network& net, ostream& os, const char c)
{
    return save_stat_modularity.Stk(os, net.stat_modularity.Stk, net.stat_modularity.Range, c);
}

int net_save_stat_modularity.Stk(const Network& net, const char *name, const char c)
{
    return save_stat_modularity.Stk(net.stat_modularity.Stk, net.stat_modularity.Range, name, c);
}

//**//****************************************************//*
int net_modularity(Network &net)
{
    int f = 0;
    f = cal_modularity(net.stat_modularity.Val, net.stat_modularity.Stk, net.stat_modularity.Num, net.stat_modularity.Range, net.p2p, net.p2pIn, net.dirFlag);
    f |= moduStk_sort(net.stat_modularity.Stk, net.stat_modularity.Range, net.stat_modularity.Num);
    f |= cal_moduLKK(net.stat_modularity.LKK, net.stat_modularity.Range.size() , net.stat_modularity.Val, net.p2p, net.dirFlag);
    f |= cal_moduCoef(net.stat_modularity.Coef, net.stat_modularity.LKK, net.dirFlag);
    f |= cal_moduNodeCoef(net.stat_modularity.NodeCoef, net.stat_modularity.Range.size(), net.stat_modularity.Val, net.p2p);
    return f;
}

int net_cal_modularity(Network &net)
{
    return cal_modularity(net.stat_modularity.Val, net.stat_modularity.Stk, net.stat_modularity.Num, net.stat_modularity.Range, net.p2p, net.p2pIn, net.dirFlag);
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
    if(net.stat_modularity.Coef > qMax) qMax = net.stat_modularity.Coef;
    for(LinkType l = net.linkSize; l > 0 && net.stat_modularity.Range.size() < mSize;){
        net_betweenness(net);
        sort_link_betwEdge(net.link, net.stat_betweenness.betwEdge, l--); // 按介数排序边link
        del_pij(net.link[l*2], net.link[l*2+1], net.p2p, net.p2pIn, net.dirFlag);   // 删除连边p2p中介数最大的边
        cal_modularity(net.stat_modularity.Val, net.stat_modularity.Stk, net.stat_modularity.Num, net.stat_modularity.Range, net.p2p, net.p2pIn, net.dirFlag);
        moduStk_sort(net.stat_modularity.Stk, net.stat_modularity.Range, net.stat_modularity.Num);
        cal_moduLKK(net.stat_modularity.LKK, net.stat_modularity.Range.size() , net.stat_modularity.Val, p2p, net.dirFlag); // 统计原网络在新分组下的不同组之间的连边数
        cal_moduCoef(net.stat_modularity.Coef, net.stat_modularity.LKK, net.dirFlag);  // 新分组系数
        if(net.stat_modularity.Coef > qMax) qMax = net.stat_modularity.Coef;
    }
    return 0;
}
#endif

//**//****************************************************//*
#endif  // STAT_MODULARITY

