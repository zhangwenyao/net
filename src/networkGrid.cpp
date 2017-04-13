#include "networkGrid.h"
#include "NetGrid.h"
#ifdef NET_GRID

#include <iostream>
#include <string>
using namespace std;

//**//****************************************************//*
int net_Grid_new(Network& net) {
  return Grid_new(net.params_grid.NX, net.params_grid.NY, net.kMin, net.kMax,
                  net.nodeSize, net.p2p);
}

//**//****************************************************//*
int net_read_params_Grid(istream& is, Network& net) {
  for (string s; is >> s;) {
    if (s == "--params_grid.NX") {
      is >> net.params_grid.NX;
      cout << s << '\t' << net.params_grid.NX << endl;
      continue;
    }
    if (s == "--params_grid.NY") {
      is >> net.params_grid.NY;
      cout << s << '\t' << net.params_grid.NY << endl;
      continue;
    }
  }
  return 0;
}

int net_save_params_Grid(ostream& os, const Network& net) {
  if (!os) return -1;
  os << "--params_grid.NX\t" << net.params_grid.NX << "\n--params_grid.NY\t"
     << net.params_grid.NY << '\n';
  return 0;
}

//**//****************************************************//*
#endif  // NET_GRID
