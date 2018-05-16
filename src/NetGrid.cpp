#include "NetGrid.h"
#ifdef NET_GRID

#include "common.h"
using namespace std;

//**//************************************************************//*
int Grid_new(const NodeType NX, const NodeType NY, NodeType& kMin,
    NodeType& kMax, NodeType& nodeSize, VVNodeType& p2p)
{
  if (NX <= 0 || NY <= 0)
    return -1;
  kMin = 2;
  kMax = 4;
  nodeSize = NX * NY;
  p2p.resize(nodeSize);
  for (VVNodeTypeItr itr = p2p.begin(); itr != p2p.end(); itr++) {
    itr->reserve(4);
  }
  VVNodeTypeItr itr = p2p.begin();
  for (NodeType i = 0; i < nodeSize; itr++, i++) {
    if (i / NX != NY - 1) {
      itr->push_back(i + NX); // y+
    }
    if (i / NX != 0) {
      itr->push_back(i - NX); // y-
    }
    if (i % NX != 0) {
      itr->push_back(i - 1); // x-
    }
    if (i % NX != NX - 1) {
      itr->push_back(i + 1); // x+
    }
  }
  return 0;
}

int Grid_check(const NodeType NX, const NodeType NY, const NodeType nodeSize,
    const VVNodeType& p2p)
{
  if (NX <= 0 || NY <= 0 || nodeSize != NX * NY || p2p.size() != nodeSize) {
    return -1;
  }
  return 0;
}

//!<*********************************************************
NodeType Grid_get_distance(const NodeType ni, const NodeType nj,
    const NodeType NX, const NodeType NY)
{
  NodeType xi = ni % NX, yi = ni / NX, xj = nj % NX, yj = nj / NX;
  return (xi >= xj ? xi - xj : xj - xi) + (yi >= yj ? yi - yj : yj - yi);
}

int Grid_get_path(VNodeType& path, const NodeType ni, const NodeType nj,
    const NodeType nodeSize, const VVNodeType& p2p,
    const NodeType NX, const NodeType NY)
{
  if (ni >= nodeSize || nj >= nodeSize) {
    path.clear();
    return -1;
  }
  if (ni == nj) {
    path.assign(1, ni);
    return 0;
  }
  NodeType xi = ni % NX, yi = ni / NX, xj = nj % NX, yj = nj / NX;
  NodeType dx, dy, d, xDir, yDir;
  if (xj >= xi) {
    dx = xj - xi;
    xDir = 1; //'R';
  } else {
    dx = xi - xj;
    xDir = -1; //'L';
  }
  if (yj >= yi) {
    dy = yj - yi;
    yDir = NX; //'U';
  } else {
    dy = yi - yj;
    yDir = -NX; //'D';
  }
  d = dx + dy;
  path.resize(d + 1);
  path[0] = ni;
  NodeType* p = &path[1];
  for (NodeType i = 0; i < dx; i++)
    *p++ = xDir;
  for (NodeType i = 0; i < dy; i++)
    *p++ = yDir;
  if (dx > 0 && dy > 0)
    random_new_randArrAll(&path[1], d); //每一步的可能方向均随机取
  for (NodeType i = 0, now = ni, *p = &path[1]; i < d; i++) {
    now += *p;
    *p++ = now;
  }
  return 0;
}

int Grid_get_shortPath(VNodeType& path, const NodeType ni, const NodeType nj,
    const NodeType nodeSize, const VVNodeType& p2p,
    const NodeType NX, const NodeType NY)
{
  if (ni >= nodeSize || nj >= nodeSize) {
    path.clear();
    return -1;
  }
  if (ni == nj) {
    path.assign(1, ni);
    return 0;
  }
  NodeType xi = ni % NX, yi = ni / NX, xj = nj % NX, yj = nj / NX;
  NodeType dx, dy, d, xDir, yDir;
  if (xj >= xi) {
    dx = xj - xi;
    xDir = 1; //'R';
  } else {
    dx = xi - xj;
    xDir = -1; //'L';
  }
  if (yj >= yi) {
    dy = yj - yi;
    yDir = NX; //'U';
  } else {
    dy = yi - yj;
    yDir = -NX; //'D';
  }
  d = dx + dy;
  path.resize(d + 1);
  path[0] = ni;
  std::uniform_int_distribution<NodeType> dis(0, 1);
  for (NodeType i = 0, x = 0, y = 0, now = ni, *p = &path[1]; i < d; i++) {
    if (y == dy || (x != dx && (x * dy < y * dx || (x * dy == y * dx && (dis(rand2) & 1))))) {
      x++;
      now += xDir;
      *p++ = now;
    } else {
      y++;
      now += yDir;
      *p++ = now;
    }
  }
  return 0;
}

NodeType Grid_get_maxDistance(const NodeType NX, const NodeType NY)
{
  if (NX <= 0 || NY <= 0)
    return 0;
  return NX + NY - 2;
}

//**//************************************************************//*
#endif // NET_GRID
