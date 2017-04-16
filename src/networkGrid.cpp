#include "net.h"
#ifdef NET_GRID

#include "NetGrid.h"
#include "common.h"
#include "networks.h"
using namespace std;
//**//****************************************************//*
// 参数：    params_grid.NX X方向格点数目
//          params_grid.NY Y方向格点数目
// 节点i对应坐标（x，y）：i=x*NX+y

Net_grid::Net_grid(void) : NX(0), NY(0) {}

ostream& operator<<(ostream& os, const Net_grid& grid) {
  if (!os) {
    ERROR();
    return os;
  }
  os << "--grid.NX\t" << grid.NX << "\n--grid.NY\t" << grid.NY << '\n';
  return os;
}

int Net_grid::save_params(ostream& os) const {
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int Net_grid::save_params(const char* name) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  os.close();
  return 0;
}

int Net_grid::save_data(const char* name) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  return 0;
}

int Net_grid::save(const char* name) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + "_grid_params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 != save_data((fn + "_grid").c_str())) {
    ERROR();
    return -1;
  }
  return 0;
}

int Net_grid::read_params_1(string& s, istream& is) {
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = 1;
  do {
    if (s == "--grid.NX") {
      is >> NX;
      cout << s << '\t' << NX << endl;
      break;
    }
    if (s == "--grid.NY") {
      is >> NY;
      cout << s << '\t' << NY << endl;
      break;
    }
    flag = 0;
  } while (0);
  if (flag) s.clear();
  return 0;
}

//**//****************************************************//*
Networks& Networks::net_grid(void) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (0 != ::Grid_new(grid.NX, grid.NY, kMin, kMax, nodeSize, p2p)) {
    runStatus = -1;
    status = -1;
    ERROR();
  } else
    status = 1;
  return *this;
}

//**//****************************************************//*
#endif  // NET_GRID
