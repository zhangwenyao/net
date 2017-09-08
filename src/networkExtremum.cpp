#include "net.h"
#ifdef NET_EXTREMUM

#include "common.h"
#include "NetExtremum.h"
#include "networks.h"
using namespace std;

//**//****************************************************//*
// 特殊网络参数
//      nodeSize    网络节点数目
//      nodeDeg     节点度分布序列
// Max: 极大同配网络
// Min: 极小同配网络（极大异配网络）

// 最大相关网络
Networks& Networks::net_Max(void) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (0 != ::Max_new(p2p, nodeDeg, degArrVal, degArrSize, degArrSum)) {
    ERROR();
    runStatus = -1;
    status = -1;
  } else
    status = 1;
  return *this;
}

// 最小相关网络
Networks& Networks::net_Min(void) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (0 != ::Min_new(p2p, nodeDeg, degArrVal, degArrSize, degArrSum)) {
    ERROR();
    runStatus = -1;
    status = -1;
  } else
    status = 1;
  return *this;
}

Networks& Networks::net_Min_new_lkk_p2p(const int fix) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (0 != ::Min_new_lkk_p2p(p2p, lkk, nodeDeg, degArrVal, degArrSize,
                             degArrSum, linkSum, fix)) {
    ERROR();
    runStatus = -1;
    status = -1;
  } else
    status = 1;
  return *this;
}

Networks& Networks::net_Min_new_lkk(const int fix) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (0 != ::Min_new_lkk(lkk, degArrVal, degArrSize, linkSum, fix)) {
    ERROR();
    runStatus = -1;
    status = -1;
  } else
    status = 1;
  return *this;
}

Networks& Networks::net_extremum_lkk(const int extrMax, const unsigned countN) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (0 != ::lkk_extreme_pearson(lkk, degArrVal, degArrSize, extrMax, countN)) {
    ERROR();
    runStatus = -1;
  }
  return *this;
}

//**//****************************************************//*
Networks& Networks::extremum_cal_lkk(string& s, istream& is) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  do {
    if (s == "lkk_max") {
      if (0 != net_extremum_lkk(1).runStatus) {
        ERROR();
        runStatus = -1;
        return *this;
      }
      break;
    }
    if (s == "lkk_min") {
      if (0 != net_extremum_lkk(0).runStatus) {
        ERROR();
        runStatus = -1;
        return *this;
      }
      break;
    }
    if (s == "lkk_maxN") {
      unsigned t;
      if (!(is >> t) || 0 != net_extremum_lkk(1, t).runStatus) {
        ERROR();
        runStatus = -1;
        return *this;
      }
      break;
    }
    if (s == "lkk_minN") {
      unsigned t;
      if (!(is >> t) || 0 != net_extremum_lkk(0, t).runStatus) {
        ERROR();
        runStatus = -1;
        return *this;
      }
      break;
    }
    if (s == "MinLkk") {
      if (0 != net_Min_new_lkk(0).runStatus) {
        ERROR();
        runStatus = -1;
        return *this;
      }
      break;
    }
    if (s == "MinLkkFix") {
      if (0 != net_Min_new_lkk(1).runStatus) {
        ERROR();
        runStatus = -1;
        return *this;
      }
      break;
    }
    ERROR(s);
    runStatus = -1;
    return *this;
  } while (0);

  return *this;
}
//**//****************************************************//*
#endif
