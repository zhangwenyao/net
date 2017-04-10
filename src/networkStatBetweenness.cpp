#include "StatBetweenness.h"
#include "networkStatBetweenness.h"
#ifdef STAT_BETWEENNESS

#include "common.h"
using namespace std;
//**//****************************************************//*
int net_read_params_betweenness(istream& is, Network& net)
{
    for(string s; is >> s;){
        if (s == "--stat_betweenness.meanNode") {
            is >> net.stat_betweenness.meanNode;
            cout << s << '\t'   << net.stat_betweenness.meanNode << endl;
            continue;
        }
        if (s == "--stat_betweenness.meanEdge") {
            is >> net.stat_betweenness.meanEdge;
            cout << s << '\t'   << net.stat_betweenness.meanEdge << endl;
            continue;
        }
    }
    return 0;
}

int net_save_params_betweenness(ostream& os, const Network& net)
{
    if(!os) return -1;
    os  << "--stat_betweenness.meanNode\t"     << net.stat_betweenness.meanNode
        << "\n--stat_betweenness.meanEdge\t"   << net.stat_betweenness.meanEdge
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
    if(!net.stat_betweenness.betwNode.empty()) f |= common_save1((fn + "_stat_betweenness.betwNode.txt").c_str(), net.stat_betweenness.betwNode, net.priChar);
    if(!net.stat_betweenness.betwEdge.empty()) f |= common_save2((fn + "_stat_betweenness.betwEdge.txt").c_str(), net.stat_betweenness.betwEdge, net.priChar2);
    if(!net.stat_betweenness.minDistMatr.empty()) f |= common_save2((fn + "_minDistMatr.txt").c_str(), net.stat_betweenness.minDistMatr, net.priChar2);
    if(!net.stat_betweenness.minDistMean.empty()) f |= common_save1((fn + "_minDistMean.txt").c_str(), net.stat_betweenness.minDistMean, net.priChar);
    return f;
}
//**//****************************************************//*
int net_clear_betweenness(Network& net)
{
    net.stat_betweenness.betwNode.clear();
    net.stat_betweenness.betwEdge.clear();
    net.stat_betweenness.minDistMatr.clear();
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
    if(net.dirFlag) f = cal_betweenness0(net.stat_betweenness.betwNode, net.stat_betweenness.betwEdge, net.stat_betweenness.meanNode, net.stat_betweenness.meanEdge, net.stat_betweenness.minDistMatr, net.stat_betweenness.minDistMean, net.p2p, net.p2pIn);
    else f = cal_betweenness0(net.stat_betweenness.betwNode, net.stat_betweenness.betwEdge, net.stat_betweenness.meanNode, net.stat_betweenness.meanEdge, net.stat_betweenness.minDistMatr, net.stat_betweenness.minDistMean, net.p2p, net.p2p);
    return f;
}

int net_cal_betweenness(Network &net)
{
    if(net.p2p.empty()) {
        linkMatr_2_p2p(net.p2p, net.linkMatr);
        if(net.dirFlag) p2p_2_p2pIn(net.p2pIn, net.p2p);
    }
    int f = 0;
    if(net.dirFlag) f = cal_betweenness(net.stat_betweenness.betwNode, net.stat_betweenness.betwEdge, net.stat_betweenness.meanNode, net.stat_betweenness.meanEdge, net.stat_betweenness.minDistMatr, net.stat_betweenness.minDistMean, net.p2p, net.p2pIn, net.linkMatr);
    else f = cal_betweenness(net.stat_betweenness.betwNode, net.stat_betweenness.betwEdge, net.stat_betweenness.meanNode, net.stat_betweenness.meanEdge, net.stat_betweenness.minDistMatr, net.stat_betweenness.minDistMean, net.p2p, net.p2p, net.linkMatr);
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

