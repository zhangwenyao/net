#include "networkExtremum.h"
#include "NetExtremum.h"
#ifdef NET_EXTREMUM

//**//****************************************************//*
// 最大相关网络
int net_Max_new(Network& net) {
  return Max_new(net.p2p, net.nodeDeg, net.degArrVal, net.degArrSize,
                 net.degArrSum);
}

// 最小相关网络
int net_Min_new(Network& net) {
  return Min_new(net.p2p, net.nodeDeg, net.degArrVal, net.degArrSize,
                 net.degArrSum);
}

int net_Min_new_lkk_p2p(Network& net, const int fix) {
  return Min_new_lkk_p2p(net.p2p, net.lkk, net.nodeDeg, net.degArrVal,
                         net.degArrSize, net.degArrSum, net.linkSum, fix);
}

int net_Min_new_lkk(Network& net, const int fix) {
  return Min_new_lkk(net.lkk, net.degArrVal, net.degArrSize, net.linkSum, fix);
}

int net_extreme_lkk(Network& net, const int extrMax, const unsigned countN) {
  return lkk_extreme_pearson(net.lkk, net.degArrVal, net.degArrSize, extrMax,
                             countN);
}

//**//****************************************************//*
#endif  // NET_EXTREMUM
