#include "network.h"
#ifdef NET_GRID

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
// 参数：    params_grid.NX X方向格点数目
//          params_grid.NY Y方向格点数目
// 节点i对应坐标（x，y）：i=x*NX+y

network::grid::Grid::Grid(void)
    : NX(0)
    , NY(0)
{
}

ostream& operator<<(ostream& os, const network::grid::Grid& grid)
{
  if (!os) {
    ERROR();
    return os;
  }
  os << "--grid.NX\t" << grid.NX << "\n--grid.NY\t" << grid.NY << '\n';
  return os;
}

int network::grid::Grid::save_params(ostream& os) const
{
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int network::grid::Grid::save_params(const char* name) const
{
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

int network::grid::Grid::save_data(const char* name) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  return 0;
}

int network::grid::Grid::save(const char* name) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + ".grid.params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 != save_data((fn + ".grid").c_str())) {
    ERROR();
    return -1;
  }
  return 0;
}

int network::grid::Grid::read_params_1(string& s, istream& is)
{
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
  if (flag)
    s.clear();
  return 0;
}

// ******************************************************
Networks& Networks::net_grid(void)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (0
      != network::grid::Grid_new(
             grid.NX, grid.NY, kMin, kMax, nodeSize, p2p)) {
    runStatus = -1;
    status = -1;
    ERROR();
  } else
    status = 1;
  return *this;
}

// ******************************************************
#endif // NET_GRID
