#include "StatCluster.h"
#include "networkStatCluster.h"
#ifdef STAT_CLUSTER

#include "common.h"
using namespace std;
//**//****************************************************//*
int net_read_params_cluster(std::istream& is, Network& net)
{
    for(string s; is >> s;){
        if (s == "--params_cluster.coef") {
            is >> net.params_cluster.Node;
            cout << s << '\t'   << net.params_cluster.coef << endl;
            continue;
        }
    }
    return 0;
}

int net_save_params_cluster(std::ostream& os, const Network& net)
{
    if(!os) return -1;
    os  << "--params_cluster.coef\t"       << net.params_cluster.coef
        << '\n';
    return 0;
}

int net_save_cluster(const Network& net, const char *name)
{
    string fn;
    if(name != NULL && name[0] != '\0') fn = name;
    else{
        stringstream ss;
        ss << net.seed;
        fn = net.saveName + '_' + ss.str();
    }
    int f = 0;
    if(!net.params_cluster.Node.empty()) f |= common_save1((fn + "_cluster.txt").c_str(), net.params_cluster.Node, net.priChar);
    return f;
}

int net_clear_cluster(Network& net)
{
    net.params_cluster.Node.clear();
    net.params_cluster.coef = 0;
    return 0;
}

int net_cal_cluster(Network& net)
{
    if(net.linkMatr.empty() && net.weightFlag){
        if(net.weightMatr.empty()){
            ERROR();
            return -1;
        }
        weightMatr_2_linkMatr(net.linkMatr, net.weightMatr);
    }
    if(net.weightFlag) return cal_cluster_directed_weight(net.params_cluster.coef, net.params_cluster.Node, net.weightMatr, net.linkMatr);
    else return cal_cluster_directed_unweight(net.params_cluster.coef, net.params_cluster.Node, net.linkMatr);
}

//**//****************************************************//*
#endif  // STAT_CLUSTER

