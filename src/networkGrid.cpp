#include "NetGrid.h"
#include "networkGrid.h"
#ifdef NET_GRID

#include <iostream>
#include <string>
using namespace std;

//**//****************************************************//*
int net_Grid_new(Network &net)
{
    return Grid_new(net.net_grid.NX, net.net_grid.NY, net.kMin, net.kMax, net.nodeSize, net.p2p);
}

//**//****************************************************//*
int net_read_params_Grid(istream& is, Network& net)
{
    for(string s; is >> s;){
        if (s == "--net_grid.NX") {
            is >> net.net_grid.NX;
            cout << s << '\t'   << net.net_grid.NX << endl;
            continue;
        }
        if (s == "--net_grid.NY") {
            is >> net.net_grid.NY;
            cout << s << '\t'   << net.net_grid.NY << endl;
            continue;
        }
    }
    return 0;
}

int net_save_params_Grid(ostream& os, const Network& net)
{
    if(!os) return -1;
    os  << "--net_grid.NX\t"    << net.net_grid.NX
        << "\n--net_grid.NY\t"  << net.net_grid.NY
        << '\n';
    return 0;
}

//**//****************************************************//*
#endif  // NET_GRID

