#ifndef NETWORK__NET_TRANSFORM_TEMPLATE_H_
#define NETWORK__NET_TRANSFORM_TEMPLATE_H_

#include "net_transform.h"
#include <algorithm>
#include <functional>
#include <random>
#include <vector>

// **********************************************************
template <typename T, typename T2>
int network::linkMatr_2_nodeDeg(
    std::vector<T>& nodeDeg, const std::vector<std::vector<T2>>& linkMatr)
{
  const size_t iSize = linkMatr.size(), jSize = linkMatr[0].size();
  nodeDeg.assign(iSize, 0);
  for (size_t i = 0; i < iSize; i++) {
    for (size_t j = 0; j < jSize; j++) {
      if (linkMatr[i][j] != 0)
        ++nodeDeg[i];
    }
  }
  return 0;
}

template <typename T, typename T2>
int network::linkMatr_2_p2p(std::vector<std::vector<T2>>& p2p,
    const std::vector<std::vector<T>>& linkMatr)
{
  const size_t iSize = linkMatr.size(), jSize = linkMatr[0].size();
  p2p.clear();
  p2p.resize(iSize);
  for (size_t i = 0; i < iSize; i++) {
    for (size_t j = 0; j < jSize; j++) {
      if (linkMatr[i][j] != 0) {
        p2p[i].push_back(j);
      }
    }
  }
  return 0;
}

template <typename T, typename T2>
int network::linkMatr_2_p2pIn(std::vector<std::vector<T2>>& p2pIn,
    const std::vector<std::vector<T>>& linkMatr)
{
  const size_t iSize = linkMatr.size(), jSize = linkMatr[0].size();
  p2pIn.clear();
  p2pIn.resize(jSize);
  for (size_t j = 0; j < jSize; j++) {
    for (size_t i = 0; i < iSize; i++) {
      if (linkMatr[i][j] != 0) {
        p2pIn[j].push_back(i);
      }
    }
  }
  return 0;
}



template <typename T>
int network::lkk_dir_2_nDir(std::vector<std::vector<T>>& lkk, const int dir)
{
  if (lkk.empty())
    return 0;
  const NodeType degSize = lkk.size();
  for (NodeType i = 0; i < degSize; i++) {
    if (lkk[i].size() != degSize) {
      ERROR();
      return -1;
    }
    if (dir)
      for (NodeType j = i; j < degSize; ++j)
        lkk[j][i] += lkk[i][j];
    lkk[i].resize(i + 1);
  }
  return 0;
}

template <typename T>
int network::lkk_nDir_2_dir(std::vector<std::vector<T>>& lkk, const int dir)
{
  if (lkk.empty())
    return 0;
  const NodeType degSize = lkk.size();
  for (NodeType i = 0; i < degSize; i++) {
    if (lkk[i].size() > degSize) {
      ERROR();
      return -1;
    }
    if (dir)
      for (NodeType j = 0; j < lkk[i].size(); j++)
        lkk[i][j] /= 2;
    if (lkk[i].size() < degSize)
      lkk[i].resize(degSize, 0);
    for (NodeType j = i + 1; j < degSize; j++) {
      if (lkk[i][j] != 0) {
        ERROR();
        return -1;
      }
      lkk[i][j] = lkk[j][i];
    }
  }
  return 0;
}


// **********************************************************
#endif
