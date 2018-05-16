#include "networkBA.h"
#ifdef NET_BA

#include "common.h"
#include "networks.h"
using namespace std;

//**//****************************************************//*
// 参数：   M0  全连通子网络节点数目
//          M   新节点的度（M<=M0）
//          nodeize 网络总节点数

Net_BA::Net_BA(void) : M0(0), M(0) {}

ostream& operator<<(ostream& os, const Net_BA& ba) {
  if (!os) {
    ERROR();
    return os;
  }
  os << "--ba.M0\t" << ba.M0 << "\n--ba.M\t" << ba.M << '\n';
  return os;
}

int Net_BA::save_params(ostream& os) const {
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int Net_BA::save_params(const char* name) const {
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

int Net_BA::save_data(const char* name) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  return 0;
}

int Net_BA::save(const char* name) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + ".BA.params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 != save_data((fn + ".BA").c_str())) {
    ERROR();
    return -1;
  }
  return 0;
}

int Net_BA::read_params_1(string& s, istream& is) {
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = 1;
  do {
    if (s == "--ba.M0") {
      is >> M0;
      cout << s << '\t' << M0 << endl;
      break;
    }
    if (s == "--ba.M") {
      is >> M;
      cout << s << '\t' << M << endl;
      break;
    }
    flag = 0;
  } while (0);
  if (flag) s.clear();
  return 0;
}

//**//****************************************************//*
Networks& Networks::net_BA(void) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (0 != ::BA_new(ba.M, ba.M0, nodeSize, p2p, kMin, kMax)) {
    runStatus = -1;
    status = -1;
    ERROR();
  } else
    status = 1;
  return *this;
}

//**//****************************************************//*
#endif  // NET_BA
