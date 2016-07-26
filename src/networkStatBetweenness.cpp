#include "StatBetweenness.h"
#include "networkStatBetweenness.h"
#ifdef STAT_BETWEENNESS

#include "common.h"
using namespace std;
//**//****************************************************//*
int net_read_params_betweenness(istream& is, Network& net)
{
    for(string s; is >> s;){
        if (s == "--bt") {
            is >> net.bt;
            cout << s << '\t'   << net.bt << endl;
            continue;
        }
        if (s == "--btEdge") {
            is >> net.btEdge;
            cout << s << '\t'   << net.btEdge << endl;
            continue;
        }
    }
    return 0;
}

int net_save_params_betweenness(ostream& os, const Network& net)
{
    if(!os) return -1;
    os  << "--bt\t"       << net.bt
        << "\n--btEdge\t"   << net.btEdge
        << '\n';
    return 0;
}

int net_save_betweenness(const Network& net, const char *name)
{
    string fn;
    if(name != NULL && name[0] != '\0') fn = name;
    else{
        stringstream ss;
        ss << net.seed;
        fn = net.saveName + '_' + ss.str();
    }
    int f = 0;
    if(!net.betw.empty()) f |= common_save1((fn + "_betw.txt").c_str(), net.betw, net.priChar);
    if(!net.betwEdge.empty()) f |= common_save2((fn + "_betwEdge.txt").c_str(), net.betwEdge, net.priChar2);
    if(!net.minDistMatr.empty()) f |= common_save2((fn + "_minDistMatr.txt").c_str(), net.minDistMatr, net.priChar2);
    if(!net.minDistMean.empty()) f |= common_save1((fn + "_minDistMean.txt").c_str(), net.minDistMean, net.priChar);
    return f;
}
//**//****************************************************//*
int net_clear_betweenness(Network& net)
{
    net.betw.clear();
    net.betwEdge.clear();
    net.minDistMatr.clear();
    return 0;
}

//**//****************************************************//*
int net_cal_betweenness0(Network &net)
{
    if(net.p2p.empty()) {
        linkMatr_2_p2p(net.p2p, net.linkMatr);
        if(net.dirFlag) p2p_2_p2pIn(net.p2pIn, net.p2p);
    }
    int f = 0;
    if(net.dirFlag) f = cal_betweenness0(net.betw, net.betwEdge, net.bt, net.btEdge, net.minDistMatr, net.minDistMean, net.p2p, net.p2pIn);
    else f = cal_betweenness0(net.betw, net.betwEdge, net.bt, net.btEdge, net.minDistMatr, net.minDistMean, net.p2p, net.p2p);
    return f;
}

int net_cal_betweenness(Network &net)
{
    if(net.p2p.empty()) {
        linkMatr_2_p2p(net.p2p, net.linkMatr);
        if(net.dirFlag) p2p_2_p2pIn(net.p2pIn, net.p2p);
    }
    int f = 0;
    if(net.dirFlag) f = cal_betweenness(net.betw, net.betwEdge, net.bt, net.btEdge, net.minDistMatr, net.minDistMean, net.p2p, net.p2pIn, net.linkMatr);
    else f = cal_betweenness(net.betw, net.betwEdge, net.bt, net.btEdge, net.minDistMatr, net.minDistMean, net.p2p, net.p2p, net.linkMatr);
    return f;
}

int net_betweenness(Network& net)
{
    if(net.linkMatr.empty()) p2p_2_linkMatr(net.linkMatr, net.p2p);
    if(net.distFlag) return net_cal_betweenness(net);
    else return net_cal_betweenness0(net);
}
//**//****************************************************//*
#endif  // STAT_BETWEENNESS

