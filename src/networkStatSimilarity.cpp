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
    if(!net.simiNodeCoef.empty()) f |= common_save1((fn + "_simiNodeCoef.txt").c_str(), net.simiNodeCoef, net.priChar);
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
int net_similarity(Network &net)
{
    int f = 0;
    f = cal_similarity();
    cout << "TODO: similarity" << endl;
    return f;
}

//**//****************************************************//*
#endif  // STAT_SIMILARITY

