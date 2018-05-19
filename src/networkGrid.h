#ifndef NETWORK_GRID_H
#define NETWORK_GRID_H
#include "NetGrid.h"
#ifdef NET_GRID

#include <iostream>

// **************************************************************
class Net_grid {
  public:
    int NX, NY;

    Net_grid(void);
    friend std::ostream& operator<<(std::ostream& os, const Net_grid& grid);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL) const;
    int save(const char* name = NULL) const;
    int read_params_1(std::string& s, std::istream& is);
};
std::ostream& operator<<(std::ostream& os, const Net_grid& grid);

// **************************************************************
#endif  // NET_GRID
#endif  // NETWORK_GRID_H

