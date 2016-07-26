#include "NetGrid.h"
#include "networkGrid.h"
#ifdef NET_GRID

#include <iostream>
#include <string>
using namespace std;

//**//****************************************************//*
int net_Grid_new(Network &net)
{
    return Grid_new(net.Grid_NX, net.Grid_NY, net.kMin, net.kMax, net.nodeSize, net.p2p);
}

//**//****************************************************//*
int net_read_params_Grid(istream& is, Network& net)
{
    for(string s; is >> s;){
        if (s == "--Grid_NX") {
            is >> net.Grid_NX;
            cout << s << '\t'   << net.Grid_NX << endl;
            continue;
        }
        if (s == "--Grid_NY") {
            is >> net.Grid_NY;
            cout << s << '\t'   << net.Grid_NY << endl;
            continue;
        }
    }
    return 0;
}

int net_save_params_Grid(ostream& os, const Network& net)
{
    if(!os) return -1;
    os  << "--Grid_NX\t"    << net.Grid_NX
        << "\n--Grid_NY\t"  << net.Grid_NY
        << '\n';
    return 0;
}

//**//****************************************************//*
#endif  // NET_GRID

