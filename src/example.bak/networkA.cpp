#include "netA.h"
#include "networkA.h"

#ifdef NET_A

#include <iostream>
#include <string>
using namespace std;

//**//*******************************************************
int net_A(Network& net)
{
    if(0 != A_new(net.nodeSize, net.p2p)) return net.status = -1;
    return net.status = 1;
}

//**//*******************************************************
int net_read_params_A(istream& is, Network& net)
{
    for(string s; is >> s;){
        if (s == "--A_a") {
            is >> net.A_a;
            cout << s << '\t'   << net.A_a << endl;
            continue;
        }
    }
    return 0;
}

int net_save_params_A(ostream& os, const Network& net)
{
    if(!os) return -1;
    os << "--A_a\t" << net.A_a
        << '\n';
    return 0;
}

int net_clear_A(Network& net)
{
    return 0;
}
//**//*******************************************************
#endif  // NET_A

