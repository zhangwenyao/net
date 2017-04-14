#include "networkRandom.h"
#ifdef NET_RANDOM

#include "NetRandom.h"
#include "common.h"
using namespace std;

//**//****************************************************//*
Net_random::Net_random(void) : p(0.1) {}

std::ostream& operator<<(std::ostream& os, const Net_random& random) {
  if (!os) {
    ERROR();
    return os;
  }
  os << "--random.p\t" << random.p << '\n';
  return os;
}

int Net_random::save_params(std::ostream& os) const {
  os << *this;
  return 0;
}

int Net_random::save_params(const char* name) const { return 0; }
int Net_random::save_data(const char* name) { return 0; }
int Net_random::save(const char* name) { return 0; }

int Net_random::read_params_1(string& s, istream& is) { return 0; }

//**//****************************************************//*
int net_random_clear(Networks& net) {
  net.linkSize = 0;
  net.linkRemain = 0;
  net.status = 0;
  return 0;
}

int net_random_init(Networks& net) {
  net_random_clear(net);
  if (net.kMin > net.kMax || net.kMax >= net.nodeSize ||
      (net.kMin == net.kMax && net.nodeSize % 2 == 1 && net.kMin % 2 == 1) ||
      net.random.p < 0. || net.random.p > 1.)
    return net.status = -1;
  return 0;
}

//**//****************************************************//*
Networks& Networks::net_ER(void) {
  // 初始化连边信息
  int p = random.p * RAND2_MAX;
  p2p.clear();
  p2p.resize(nodeSize);
  for (NodeType i = 0; i < nodeSize; i++)
    for (NodeType j = i + 1; j < nodeSize; j++) {
      if (RAND2() <= p) {
        p2p[i].push_back(j);
        p2p[j].push_back(i);
      }
    }
  status = 1;
  return *this;
}

//**//****************************************************//*
int net_read_params_ER(istream& is, Networks& net) {
  for (string s; is >> s;) {
    if (s == "--random.p") {
      is >> net.random.p;
      cout << s << '\t' << net.random.p << endl;
      continue;
    }
  }
  return 0;
}

int net_save_params_ER(ostream& os, const Networks& net) {
  if (!os) return -1;
  os << "--random.p\t" << net.random.p << '\n';
  return 0;
}

//**//****************************************************//*
int net_random_ranNode_link(
    Networks& net)  // 随机选点连边，重连时所有边中随机选
{
  // 初始化连边信息
  const NodeType nodeSize = net.nodeSize;
  net.p2p.clear();
  net.p2p.resize(nodeSize);
  net.link.clear();
  net.link.resize(net.linkSize * 2);
  net.remNodeNum.clear();
  net.remNodeNum.resize(nodeSize);
  for (NodeType i = 0, *p = &net.link[0]; i < net.nodeSize; i++) {
    net.p2p[i].reserve(net.nodeDeg[i]);
    net.remNodeNum[i] = i;
    for (NodeType j = net.nodeDeg[i]; j > 0; j--)
      *p++ = i;  // 记录各点剩余度和网络所有连边情况
  }
  net.linkRemain = net.linkSize;
  LinkType linkRemain0 = net.linkRemain;
  // 随机连边
  for (size_t count = 0, iDel = 1;
       net.linkRemain > 0 && net.remNodeNum.size() > 0;) {
    if (0 == addLink_p2p_ranNode0(net.p2p, net.link, net.nodeDeg,
                                  net.remNodeNum, net.linkRemain, 1000))
      break;  // 随机选点连边
    if (net.linkRemain < linkRemain0) {
      count = 0;
      iDel = 1;
      linkRemain0 = net.linkRemain;
    } else if (++count >= 1000) {
      count = 0;
      if (++iDel > 5) break;
    }
    delLink_p2p_ranLink(net.p2p, net.nodeDeg, net.remNodeNum, net.linkRemain,
                        net.link, iDel);  // 随机删iDel条边
  }

  if (net.linkRemain > 0) {
    return net.status = -2;
  } else
    net.status = 1;
  return 0;
}

int net_random_node_prob(Networks& net)  // 所有点按概率p连边
{
  // 初始化连接矩阵
  const NodeType nodeSize = net.nodeSize;
  net.linkMatr.clear();
  net.linkMatr.assign(nodeSize, VNodeType(nodeSize, 0));

  // 连边
  net.linkSize = 0;
  addLink_linkMatr_proNode(net.linkMatr, net.linkSize, net.random.p,
                           net.dirFlag);  // 连边
  net.linkRemain = 0;
  linkMatr_2_p2p(net.p2p, net.linkMatr);

  net.status = 1;
  return 0;
}

Networks& Networks::net_random_remDeg(void)  // 随机抽取剩余度连边
{
  // 初始化连边信息
  p2p.clear();
  p2p.resize(nodeSize);
  link.resize(linkSize * 2);
  remNodeNum.resize(nodeSize);
  for (NodeType i = 0, *p = &link[0]; i < nodeSize; i++) {
    remNodeNum[i] = i;
    for (NodeType j = 0; j < nodeDeg[i]; j++)
      *p++ = i;  // 记录各点剩余度和网络所有连边情况
  }
  linkRemain = linkSize;
  LinkType linkRemain0 = linkRemain;
  // 随机连边
  for (LinkType iDel = 1;
       iDel <= 5 && linkRemain > 0 && remNodeNum.size() > 0;) {
    for (size_t count = 1000; count > 0; count--) {
      delLink_p2p_ranLink(p2p, nodeDeg, remNodeNum, linkRemain, link,
                          iDel);  // 随机删iDel条边
      if (0 ==
          addLink_p2p_remDeg(p2p, nodeDeg, remNodeNum, linkRemain, link, 1000))
        break;  // 随机抽取剩余度连边
    }
    if (linkRemain <= 0) break;
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
    status = -2;
  } else
    status = 1;

  runStatus = status >= 0 ? 0 : -1;
  return *this;
}

//**//****************************************************//*
int net_random_ranNode(Networks& net)  // 每次直接随机抽取两个点连边
{
  // 初始化连接矩阵
  init_linkMatrC(net.linkMatrC, net.nodeSize);

  // 连边
  net.linkRemain = net.linkSize =
      net.random.p * (net.nodeSize - 1) * net.nodeSize / 2;
  addLink_linkMatrC_ranNode(net.linkMatrC,
                            net.linkRemain);  // 每次直接随机抽取两个点连边
  linkMatrC_2_p2p(net.p2p, net.linkMatrC);
  for (NodeType i = 0; i < net.nodeSize; i++)
    net.nodeDeg[i] = net.p2p[i].size();

  // 统计实际度分布
  nodeDeg_2_degArr(net.nodeDeg, net.degArrVal, net.degArrSize, net.degArrSum);
  p2p_2_link(net.link, net.p2p, net.dirFlag);

  net.status = 1;
  return 0;
}

//**//****************************************************//*
#endif  // NET_RANDOM
