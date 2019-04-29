#include "network.h"
#ifdef ACT_SPREAD

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// *******************************************************
network::spread::Spread::Spread(void)
    : SOURCE_HEAD(0)
    , SOURCE_NULL(0)
    , spreadSize(0)
    , head(0)
    , nei1(0)
    , nei0(0)
    , neiCountSize(0)
    , prob(0)
    , dataSize(0)
{
}
network::spread::Spread& network::spread::Spread::clear(void)
{
  source.clear();
  nei.clear();
  num.clear();
  stk.clear();
  time.clear();
  prob_rand.clear();

  data_node.clear();
  data_time.clear();
  return *this;
}

// ******************************************************
int network::spread::Spread::read_params_1(string& s, istream& is)
{
  _ERR(!is);
  for (string s; is >> s;) {
    // TODO
    continue;
  }
  return 0;
}

ostream& operator<<(ostream& os, const network::spread::Spread& spread)
{
  if (!os) {
    ERROR();
    return os;
  }
  os << "--mode\t" << spread.mode << "\n--SOURCE_HEAD\t" << spread.SOURCE_HEAD
     << "\n--SOURCE_NULL\t" << spread.SOURCE_NULL << "\n--head\t"
     << spread.head << "\n--nei1\t" << spread.nei1 << "\n--nei0\t"
     << spread.nei0 << "\n--neiCountSize\t" << spread.neiCountSize
     << "\n--prob\t" << spread.prob << "\n--spreadSize\t" << spread.spreadSize
     << "\n--dataSize\t" << spread.dataSize << '\n';
  return os;
}

int network::spread::Spread::save_params(ostream& os) const
{
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int network::spread::Spread::save_params(const char* name) const
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

// ******************************************************

int network::spread::Spread::init(const Networks& net)
{
  clear();
  const NodeType kMax = net.kMax;
  NodeType nodeSize = net.nodeSize;
  SOURCE_NULL = nodeSize;
  SOURCE_HEAD = nodeSize + 1;
  nei1 = nei0 = 0;
  neiCountSize = 0;
  if (nodeSize <= 0 || head >= nodeSize)
    return -1;
  if (0 > prob || prob > 1 || spreadSize > nodeSize)
    return -1;
  if (mode != "same" && mode != "diff")
    return -1;
  source.assign(nodeSize, SOURCE_NULL);
  nei.assign(nodeSize, 0);
  num.resize(nodeSize);
  stk.resize(nodeSize);
  time.assign(nodeSize, 0);
  prob_rand.resize(kMax + 1);
  if (source.size() != nodeSize || num.size() != nodeSize
      || nei.size() != nodeSize || stk.size() != nodeSize
      || prob_rand.size() != kMax + 1) {
    return -1;
  }
  for (NodeType i = 0; i < nodeSize; i++) {
    num[i] = i;
    stk[i] = i;
  }
  for (NodeType i = 0; i <= kMax; i++) {
    prob_rand[i] = 1. - pow(1. - prob, i);
  }
  return 0;
}

int network::spread::Spread::check(const Networks& net)
{
  const NodeType nodeSize = net.nodeSize;
  if (head < nodeSize
      && (SOURCE_HEAD == SOURCE_NULL || SOURCE_HEAD < nodeSize
             || SOURCE_NULL < nodeSize)) {
    return -1;
  }
  return 0;
}

int network::spread::Spread::save(const char* name) const
{
  save_params();
  save_data(name);
  //#ifndef NET_GRID_SAVE
  // saveSpread(net);
  //#else
  // const Grid* grid = static_cast<const Grid*>(&net);
  // saveSpread(*grid);
  //#endif
  return 0;
}

// int network::spread::Spread::cal(const Networks& net)
//{
// if (init(net) != 0) {
// ERROR("init");
// return -1;
//}
// if (mode == "same") {
// if (spread_same(net) != 0)
// return -1;
//} else if (mode == "diff") {
// if (spread_diff(net) != 0)
// return -1;
//} else
// return -1;
// if (calData() != 0)
// return -1;
// return 0;
//}

// ******************************************************
// int network::spread::saveSpread(const Networks& net)
//{
// stringstream fileName("");
// fileName.clear();
// fileName << net.outName << '_' << net.seed
//<< "_spread_stk.txt"; // fileName.str().c_str()
// if (save(fileName.str().c_str(), stk, net.priChar) != 0)
// return -1;
// fileName.str("");
// fileName.clear();
// fileName << net.outName << '_' << net.seed << "_spread_num.txt";
// if (save(fileName.str().c_str(), num, net.priChar) != 0)
// return -1;
// fileName.str("");
// fileName.clear();
// fileName << net.outName << '_' << net.seed << "_spread_source.txt";
// if (save(fileName.str().c_str(), source, net.priChar) != 0)
// return -1;
// fileName.str("");
// fileName.clear();
// fileName << net.outName << '_' << net.seed << "_spread_nei.txt";
// if (save(fileName.str().c_str(), nei, net.priChar) != 0)
// return -1;
// return 0;
//}

//#ifdef NET_GRID_SAVE
// int network::spread::Spread::saveSpread(const Grid& net)
//{
// stringstream fileName("");
// fileName.clear();
// fileName << net.outName << '_' << net.seed
//<< "_spread_stk.txt"; // fileName.str().c_str()
// if (::save(fileName.str().c_str(), stk, net.priChar) != 0)
// return -1;
// fileName.str("");
// fileName.clear();
// fileName << net.outName << '_' << net.seed << "_spread_num.txt";
// if (::save(fileName.str().c_str(), &num[0], net.NX, net.NY, net.priChar)
//!= 0)
// return -1;
// fileName.str("");
// fileName.clear();
// fileName << net.outName << '_' << net.seed << "_spread_source.txt";
// if (::save(fileName.str().c_str(), &source[0], net.NX, net.NY, net.priChar)
//!= 0)
// return -1;
// fileName.str("");
// fileName.clear();
// fileName << net.outName << '_' << net.seed << "_spread_nei.txt";
// if (::save(fileName.str().c_str(), &nei[0], net.NX, net.NY, net.priChar)
//!= 0)
// return -1;
// return 0;
//}
//#endif // NET_GRID_SAVE

void network::spread::Spread::update_nei1(const NodeType nj)
{
  neiCountSize++;
  if (nei[nj]++ == 0) {
    NodeType jNum = num[nj];
    if (jNum != nei0) { //交换stk[nei0-jnum]
      NodeType t = stk[nei0];
      stk[nei0] = nj;
      stk[jNum] = t;
      num[t] = jNum;
      num[nj] = nei0;
    }
    nei0++;
  }
  return;
}

void network::spread::Spread::update_nei(
    const Networks& net, const NodeType ni)
{
  NodeType inum = num[ni];
  if (inum != nei1) { //交换stk[nei1-inum]
    NodeType nj = stk[nei1];
    stk[inum] = nj;
    stk[nei1] = ni;
    num[ni] = nei1;
    num[nj] = inum;
  }
  nei1++;
  neiCountSize -= nei[ni];
  for (vector<NodeType>::const_iterator itr = net.p2p[ni].begin();
       itr != net.p2p[ni].end(); itr++) {
    NodeType nj = *itr;
    if (source[nj] == SOURCE_NULL) {
      update_nei1(nj);
    }
  }
  return;
}

int network::spread::Spread::spread_same(const Networks& net)
{
  nei1 = 0;
  nei0 = 1;
  source[head] = SOURCE_HEAD;
  time[head] = 0;
  update_nei(net, head);
  for (NodeType step = 1, time0 = 1; step < spreadSize && nei1 < nei0;
       time0++) {
    NodeType nei0_tmp = nei0;
    for (NodeType iNum = nei1; iNum < nei0_tmp; iNum++) {
      NodeType ni = stk[iNum], iNei = nei[ni];
      double ra = rand_double();
      if (ra <= prob_rand[iNei]) {     // spread to ni
        int r = int(ra * iNei) % iNei; // source : No. r neighbour
        for (vector<NodeType>::const_iterator i = net.p2p[ni].begin();
             i != net.p2p[ni].end(); i++) {
          if (source[*i] != SOURCE_NULL && time[*i] != time0) {
            if (r == 0) {
              source[ni] = *i;
              break;
            } else
              r--;
          }
        }
        time[ni] = time0;
        if (++step >= spreadSize)
          break;
      }
    }
    for (NodeType iNum = nei1; iNum < nei0_tmp; iNum++) {
      NodeType ni = stk[iNum];
      if (source[ni] != SOURCE_NULL)
        update_nei(net, ni);
    }
  }
  return 0;
}

int network::spread::Spread::spread_diff(const Networks& net)
{
  nei1 = 0;
  nei0 = 1;
  source[head] = SOURCE_HEAD;
  time[head] = 0;
  update_nei(net, head);
  for (NodeType step = 1; step < spreadSize && nei1 < nei0;) {
    std::uniform_int_distribution<NodeType> dis(nei1, nei0 - 1);
    std::uniform_int_distribution<NodeType> dis2(0, net.kMax - 1);
    NodeType iNum = dis(rand2), ni = stk[iNum], iNei = nei[ni],
             r = dis2(rand2);
    if (r < iNei) { // spread to ni
      for (vector<NodeType>::const_iterator i = net.p2p[ni].begin();
           i != net.p2p[ni].end(); i++) {
        if (source[*i] != SOURCE_NULL) {
          if (r == 0) {
            source[ni] = *i;
            break;
          } else
            r--;
        }
      }
      time[ni] = step++;
      update_nei(net, ni);
    }
  }
  return 0;
}

// ******************************************************
int network::spread::Spread::calData(void)
{
  if (dataSize > spreadSize)
    return -1;
  vector<NodeType> stk_tmp(stk.begin(), stk.begin() + spreadSize);
  vector<NodeType> t(spreadSize);
  for (NodeType i = 0; i < spreadSize; i++)
    t[i] = i;
  new_randArr(&t[0], spreadSize, dataSize);
  sort(t.begin(), t.begin() + dataSize);
  data_node.resize(dataSize);
  data_time.resize(dataSize);
  for (NodeType i = 0; i < dataSize; i++) {
    NodeType ni = stk[t[i]];
    data_node[i] = ni;
    data_time[i] = time[ni];
  }
  return 0;
}

int network::spread::Spread::save_data(
    const char* name, const char priChar) const
{
  string fileName0(name), fileName;
  fileName = fileName0 + "_spread_dataNode.txt";
  if (save1(fileName.c_str(), data_node, priChar) != 0)
    return -1;
  fileName = fileName0 + "_spread_dataTime.txt";
  if (save1(fileName.c_str(), data_time, priChar) != 0)
    return -1;
  return 0;
}

// *******************************************************
#endif // NET_GRID
