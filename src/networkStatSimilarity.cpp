#include "StatSimilarity.h"
#include "networkStatSimilarity.h"
#ifdef STAT_SIMILARITY

#include "common.h"
using namespace std;

//**//****************************************************//*
int net_read_params_similarity(istream& is, Network& net)
{
    return 0;
}

int net_save_params_similarity(ostream& os, const Network& net)
{
    if(!os) return -1;
    return 0;
}

int net_save_similarity(const Network& net, const char *name)
{
    string fn;
    if(name != NULL && name[0] != '\0') fn = name;
    else{
        stringstream ss;
        ss << net.seed;
        fn = net.saveName + '_' + ss.str();
    }
    int f = 0;
    if(!net.simiNodeCoef.empty()) f |= common_save2((fn + "_simiNodeCoef.txt").c_str(), net.simiNodeCoef, net.priChar2);
    if(!net.simiEdgeCoef.empty()) f |= common_save2((fn + "_simiEdgeCoef.txt").c_str(), net.simiEdgeCoef, net.priChar2);
    return f;
}
//**//****************************************************//*
int net_clear_modularity(Network& net)
{
    net.simiNodeCoef.clear();
    net.simiEdgeCoef.clear();
    return 0;
}

//**//****************************************************//*
#include "net.h"
int net_similarity(Network &net, Network &net2)
{
    if(net.dirFlag != net2.dirFlag){
        ERROR();
        return -1;
    }
    if(net.link.empty()) p2p_2_link(net.link, net.p2p, net.dirFlag);
    if(net2.link.empty()) p2p_2_link(net2.link, net2.p2p, net2.dirFlag);
    int f = 0;
    net.simiNodeCoef.resize(net.nodeSize);
    net.simiNodeCoef[0].resize(net2.nodeSize);
    f = cal_similarity(net.simiNodeCoef, net.simiEdgeCoef, net.link, net2.link, net.dirFlag);
    return f;
}

//**//****************************************************//*
#endif  // STAT_SIMILARITY

