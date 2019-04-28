#include "network.h"
#ifdef NET_RANDOM

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
network::random::Random::Random(void)
    : p(0)
{
}

std::ostream& operator<<(
    std::ostream& os, const network::random::Random& random)
{
  if (!os) {
    ERROR();
    return os;
  }
  os << "--random.p\t" << random.p << '\n';
  return os;
}

int network::random::Random::save_params(std::ostream& os) const
{
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int network::random::Random::save_params(const char* name) const
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

int network::random::Random::save_data(const char* name) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  return 0;
}

int network::random::Random::save(const char* name) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + ".random.params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 != save_data((fn + ".random").c_str())) {
    ERROR();
    return -1;
  }
  return 0;
}

int network::random::Random::read_params_1(string& s, istream& is)
{
  if (!is) {
    ERROR();
    return -1;
  }
  if (s == "--random.p") {
    is >> p;
    cout << s << '\t' << p << endl;
    s.clear();
  }
  return 0;
}

// ******************************************************
Networks& Networks::net_random_clear(void)
{
  linkSize = 0;
  linkRemain = 0;
  status = 0;
  return *this;
}

Networks& Networks::net_random_init(void)
{
  net_random_clear();
  if (kMin > kMax || kMax >= nodeSize
      || (kMin == kMax && nodeSize % 2 == 1 && kMin % 2 == 1) || random.p < 0.
      || random.p > 1.)
    runStatus = status = -1;
  return *this;
}

// ******************************************************
// ER随机网络参数
//      p           连边概率p
//      nodeSize    节点数目
Networks& Networks::net_ER(void)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  // 初始化连边信息
  p2p.clear();
  p2p.resize(nodeSize);
  for (NodeType i = 0; i < nodeSize; i++)
    for (NodeType j = i + 1; j < nodeSize; j++) {
      if (rand_double() <= random.p) {
        p2p[i].push_back(j);
        p2p[j].push_back(i);
      }
    }
  status = 1;
  return *this;
}

// ******************************************************
/*
    ranLink_ranNode     // 直接随机选点连边；用到linkMatr,p2p
    ranLink_proNode     // 所有点按概率连边；用到linkMatr,p2p
    ranLink_remDeg      // 随机选取剩余度连边；用到p2p,link
    ranLink_remDegGauss //
   随机选剩余度按点的度之差的相应高斯概率连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranLink_remDegExp   //
   随机选剩余度按点的度之差的相应指数概率连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranLink_remDegExp0  //
   随机选剩余度按点的度之差的相应指数概率连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranNode_link        //
   随机选点连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranNode_deg         //
   随机按度选点连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranNode_node        // 随机选点连边、重连时随机选点；用到p2p,remNodeNum
    ranNode_nodeM       //
   随机选点连边、重连时随机选点；用到linkMatr,p2p,remNodeNum
    ranNode_Gauss       //
   随机选点按点的度之差的相应高斯概率连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranNode_node        //
   随机选点连边、重连时随机选点再选边；用到p2p,remNodeNum
*/
// ******************************************************
Networks& Networks::net_random_ranNode_link(
    void) // 随机选点连边，重连时所有边中随机选
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  // 初始化连边信息
  p2p.clear();
  p2p.resize(nodeSize);
  link.clear();
  link.resize(linkSize * 2);
  remNodeNum.clear();
  remNodeNum.resize(nodeSize);
  for (NodeType i = 0, *p = &link[0]; i < nodeSize; i++) {
    p2p[i].reserve(nodeDeg[i]);
    remNodeNum[i] = i;
    for (NodeType j = nodeDeg[i]; j > 0; j--)
      *p++ = i; // 记录各点剩余度和网络所有连边情况
  }
  linkRemain = linkSize;
  LinkType linkRemain0 = linkRemain;
  // 随机连边
  for (size_t count = 0, iDel = 1; linkRemain > 0 && remNodeNum.size() > 0;) {
    if (0
        == addLink_p2p_ranNode0(
               p2p, link, nodeDeg, remNodeNum, linkRemain, 1000))
      break; // 随机选点连边
    if (linkRemain < linkRemain0) {
      count = 0;
      iDel = 1;
      linkRemain0 = linkRemain;
    } else if (++count >= 1000) {
      count = 0;
      if (++iDel > 5)
        break;
    }
    network::random::delLink_p2p_ranLink(p2p, nodeDeg, remNodeNum, linkRemain,
        link,
        iDel); // 随机删iDel条边
  }

  if (linkRemain > 0) {
    ERROR();
    status = -2;
    runStatus = -1;
  } else
    status = 1;
  return *this;
}

Networks& Networks::net_random_node_prob(void) // 所有点按概率p连边
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  // 初始化连接矩阵
  linkMatr.clear();
  linkMatr.assign(nodeSize, VNodeType(nodeSize, 0));

  // 连边
  linkSize = 0;
  network::random::addLink_linkMatr_proNode(
      linkMatr, linkSize, random.p, dirFlag); // 连边
  linkRemain = 0;
  linkMatr_2_p2p(p2p, linkMatr);

  status = 1;
  return *this;
}

Networks& Networks::net_random_remDeg(void) // 随机抽取剩余度连边
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  // 初始化连边信息
  p2p.clear();
  p2p.resize(nodeSize);
  link.resize(linkSize * 2);
  remNodeNum.resize(nodeSize);
  for (NodeType i = 0, *p = &link[0]; i < nodeSize; i++) {
    remNodeNum[i] = i;
    for (NodeType j = 0; j < nodeDeg[i]; j++)
      *p++ = i; // 记录各点剩余度和网络所有连边情况
  }
  linkRemain = linkSize;
  LinkType linkRemain0 = linkRemain;
  // 随机连边
  for (LinkType iDel = 1;
       iDel <= 5 && linkRemain > 0 && remNodeNum.size() > 0;) {
    for (size_t count = 1000; count > 0; count--) {
      network::random::delLink_p2p_ranLink(p2p, nodeDeg, remNodeNum,
          linkRemain, link,
          iDel); // 随机删iDel条边
      if (0
          == network::random::addLink_p2p_remDeg(
                 p2p, nodeDeg, remNodeNum, linkRemain, link, 1000))
        break; // 随机抽取剩余度连边
    }
    if (linkRemain <= 0)
      break;
    cout << "linkRemain:\t" << linkRemain << '\n';
    if (linkRemain < linkRemain0) {
      linkRemain0 = linkRemain;
      iDel = 1;
    } else
      iDel++;
  }
  cout << "\taddLink end\n";

  if (linkRemain > 0) {
    linkSize -= linkRemain;
    ERROR();
    status = -2;
    runStatus = -1;
  } else
    status = 1;

  return *this;
}

// ******************************************************
Networks& Networks::net_random_ranNode(void) // 每次直接随机抽取两个点连边
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  // 初始化连接矩阵
  init_linkMatrC(linkMatrC, nodeSize);

  // 连边
  linkRemain = linkSize = random.p * (nodeSize - 1) * nodeSize / 2;
  addLink_linkMatrC_ranNode(linkMatrC,
      linkRemain); // 每次直接随机抽取两个点连边
  linkMatrC_2_p2p(p2p, linkMatrC);
  for (NodeType i = 0; i < nodeSize; i++)
    nodeDeg[i] = p2p[i].size();

  // 统计实际度分布
  nodeDeg_2_degArr(nodeDeg, degArrVal, degArrSize, degArrSum);
  p2p_2_link(link, p2p, dirFlag);

  status = 1;
  return *this;
}

// ******************************************************
#endif // NET_RANDOM
