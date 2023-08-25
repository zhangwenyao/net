#ifndef MODEL__GRID__NETWORK_H_
#define MODEL__GRID__NETWORK_H_
#include "grid.h"
#ifdef NET_GRID

#include <iostream>

// **************************************************************
namespace network {
namespace grid {
  class Grid {
public:
    int NX, NY;

    Grid(void);
    // friend std::ostream& operator<<(std::ostream& os, const Grid& grid);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL) const;
    int save(const char* name = NULL) const;
    int read_params_1(std::string& s, std::istream& is);
  };
}
}

// **************************************************************
std::ostream& operator<<(std::ostream& os, const network::grid::Grid& grid);

#endif // NET_GRID
#endif // NETWORK_GRID_H
