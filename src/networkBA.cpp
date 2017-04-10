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
    if(0 != BA_new(net.net_BA.M, net.net_BA.M0, net.nodeSize, net.p2p, net.kMin, net.kMax)) return net.status = -1;
    net.status = 1;
    return 0;
}

//**//****************************************************//*
int net_read_params_BA(istream& is, Network& net)
{
    for(string s; is >> s;){
        if (s == "--net_BA.M") {
            is >> net.net_BA.M;
            cout << s << '\t'   << net.net_BA.M << endl;
            continue;
        }
        if (s == "--net_BA.M0") {
            is >> net.net_BA.M0;
            cout << s << '\t'   << net.net_BA.M0 << endl;
            continue;
        }
    }
    return 0;
}

int net_save_params_BA(ostream& os , const Network& net)
{
    if (!os)    return -1;
    os  << "--net_BA.M\t"     << net.net_BA.M
        << "\n--net_BA.M0\t"    << net.net_BA.M0
        << '\n';
    return 0;
}
//**//****************************************************//*
#endif  // NET_BA

