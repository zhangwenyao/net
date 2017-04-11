#include "NetBA.h"
#include "networkBA.h"
#ifdef NET_BA

#include <iostream>
#include <string>
#include "common.h"
using namespace std;
//**//****************************************************//*
int net_BA(Network &net)
{
    if(0 != BA_new(net.params_BA.M, net.params_BA.M0, net.nodeSize, net.p2p, net.kMin, net.kMax)) return net.status = -1;
    net.status = 1;
    return 0;
}

//**//****************************************************//*
int net_read_params_BA(istream& is, Network& net)
{
    for(string s; is >> s;){
        if (s == "--params_BA.M") {
            is >> net.params_BA.M;
            cout << s << '\t'   << net.params_BA.M << endl;
            continue;
        }
        if (s == "--params_BA.M0") {
            is >> net.params_BA.M0;
            cout << s << '\t'   << net.params_BA.M0 << endl;
            continue;
        }
    }
    return 0;
}

int net_save_params_BA(ostream& os , const Network& net)
{
    if (!os)    return -1;
    os  << "--params_BA.M\t"     << net.params_BA.M
        << "\n--params_BA.M0\t"    << net.params_BA.M0
        << '\n';
    return 0;
}
//**//****************************************************//*
#endif  // NET_BA

