#include "netStatSpread.h"
#include "networkStatSpread.h"
#ifdef STAT_SPREAD

#include <iostream>
#include <string>
using namespace std;

//**//*******************************************************
int net_clear_spread(Network& net) {
  net.source.clear();
  net.nei.clear();
  net.num.clear();
  net.stk.clear();
  net.time.clear();
  net.prob_rand.clear();

  net.data_node.clear();
  net.data_time.clear();
  return 0;
}

//**//*******************************************************
int net_read_params_spread(istream& is, Network& net) {
  for (string s; is >> s;) {
    // TODO
    continue;
  }
  return 0;
}

int net_save_params_spread(ostream& os, const Network& net) {
  if (!os) return -1;
  os << "--SOURCE_HEAD\t" << net.SOURCE_HEAD << "\n--SOURCE_NULL\t"
     << net.SOURCE_NULL << "\n--spread_mode\t" << net.mode << "\n--head\t"
     << net.head << "\n--nei1\t" << net.nei1 << "\n--nei0\t" << net.nei0
     << "\n--neiCountSize\t" << net.neiCountSize << "\n--prob\t" << net.prob
     << "\n--spreadSize\t" << net.spreadSize << "\n--dataSize\t" << net.dataSize
     << '\n';
  return 0;
}

//**//*******************************************************

int Spread::init(const Network& net) {
  clear();
  const NodeType kMax = net.kMax;
  nodeSize = net.nodeSize;
  SOURCE_NULL = nodeSize;
  SOURCE_HEAD = nodeSize + 1;
  nei1 = nei0 = 0;
  neiCountSize = 0;
  if (nodeSize <= 0 || head >= nodeSize) return -1;
  if (0 > prob || prob > 1 || spreadSize > nodeSize) return -1;
  if (mode != "same" && mode != "diff") return -1;
  source.assign(nodeSize, SOURCE_NULL);
  nei.assign(nodeSize, 0);
  num.resize(nodeSize);
  stk.resize(nodeSize);
  time.assign(nodeSize, 0);
  prob_rand.resize(kMax + 1);
  if (source.size() != nodeSize || num.size() != nodeSize ||
      nei.size() != nodeSize || stk.size() != nodeSize ||
      prob_rand.size() != kMax + 1) {
    return -1;
  }
  for (NodeType i = 0; i < nodeSize; i++) {
    num[i] = i;
    stk[i] = i;
  }
  for (NodeType i = 0; i <= kMax; i++) {
    prob_rand[i] = (1. - pow(1. - prob, i)) * RAND2_MAX;
  }
  return 0;
}

int Spread::check(const Network& net) {
  const NodeType nodeSize = net.nodeSize;
  if (head < nodeSize && (SOURCE_HEAD == SOURCE_NULL ||
                          SOURCE_HEAD < nodeSize || SOURCE_NULL < nodeSize)) {
    return -1;
  }
  return 0;
}

int Spread::save(const Network& net) {
  saveParams(net);
  saveData(net);
#ifndef NET_GRID_SAVE
  saveSpread(net);
#else
  const Grid *grid = static_cast<const Grid *>(&net);
  saveSpread(*grid);
#endif
  return 0;
}

int Spread::cal(const Network& net) {
  if (init(net) != 0) {
    ERROR("init");
    return -1;
  }
  if (mode == "same") {
    if (spread_same(net) != 0) return -1;
  } else if (mode == "diff") {
    if (spread_diff(net) != 0) return -1;
  } else
    return -1;
  if (calData() != 0) return -1;
  return 0;
}

//**//*******************************************************
int Spread::saveSpread(const Network& net) {
  stringstream fileName("");
  fileName.clear();
  fileName << net.outName << '_' << net.seed
           << "_spread_stk.txt";  // fileName.str().c_str()
  if (::save(fileName.str().c_str(), stk, net.priChar) != 0) return -1;
  fileName.str("");
  fileName.clear();
  fileName << net.outName << '_' << net.seed << "_spread_num.txt";
  if (::save(fileName.str().c_str(), num, net.priChar) != 0) return -1;
  fileName.str("");
  fileName.clear();
  fileName << net.outName << '_' << net.seed << "_spread_source.txt";
  if (::save(fileName.str().c_str(), source, net.priChar) != 0) return -1;
  fileName.str("");
  fileName.clear();
  fileName << net.outName << '_' << net.seed << "_spread_nei.txt";
  if (::save(fileName.str().c_str(), nei, net.priChar) != 0) return -1;
  return 0;
}

#ifdef NET_GRID_SAVE
int Spread::saveSpread(const Grid& net) {
  stringstream fileName("");
  fileName.clear();
  fileName << net.outName << '_' << net.seed
           << "_spread_stk.txt";  // fileName.str().c_str()
  if (::save(fileName.str().c_str(), stk, net.priChar) != 0) return -1;
  fileName.str("");
  fileName.clear();
  fileName << net.outName << '_' << net.seed << "_spread_num.txt";
  if (::save(fileName.str().c_str(), &num[0], net.NX, net.NY, net.priChar) != 0)
    return -1;
  fileName.str("");
  fileName.clear();
  fileName << net.outName << '_' << net.seed << "_spread_source.txt";
  if (::save(fileName.str().c_str(), &source[0], net.NX, net.NY, net.priChar) !=
      0)
    return -1;
  fileName.str("");
  fileName.clear();
  fileName << net.outName << '_' << net.seed << "_spread_nei.txt";
  if (::save(fileName.str().c_str(), &nei[0], net.NX, net.NY, net.priChar) != 0)
    return -1;
  return 0;
}
#endif  // NET_GRID_SAVE

int Spread::spread_same(const Network& net) {
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
      int r = RAND2();
      if (r <= prob_rand[iNei]) {  // spread to ni
        r %= iNei;                 // source : No. r neighbour
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
        if (++step >= spreadSize) break;
      }
    }
    for (NodeType iNum = nei1; iNum < nei0_tmp; iNum++) {
      NodeType ni = stk[iNum];
      if (source[ni] != SOURCE_NULL) update_nei(net, ni);
    }
  }
  return 0;
}

int Spread::spread_diff(const Network& net) {
  nei1 = 0;
  nei0 = 1;
  source[head] = SOURCE_HEAD;
  time[head] = 0;
  update_nei(net, head);
  for (NodeType step = 1; step < spreadSize && nei1 < nei0;) {
    NodeType iNum = RAND2() % (nei0 - nei1) + nei1, ni = stk[iNum],
             iNei = nei[ni], r = RAND2() % net.kMax;
    if (r < iNei) {  // spread to ni
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

inline void Spread::update_nei(const Network& net, const NodeType ni) {
  NodeType inum = num[ni];
  if (inum != nei1) {  //交换stk[nei1-inum]
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

inline void Spread::update_nei1(const NodeType nj) {
  neiCountSize++;
  if (nei[nj]++ == 0) {
    NodeType jNum = num[nj];
    if (jNum != nei0) {  //交换stk[nei0-jnum]
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

//**//*******************************************************
int Spread::calData() {
  if (dataSize > spreadSize) return -1;
  vector<NodeType> stk_tmp(stk.begin(), stk.begin() + spreadSize);
  vector<NodeType> t(spreadSize);
  for (NodeType i = 0; i < spreadSize; i++) t[i] = i;
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

int Spread::saveData(const Network& net) {
  stringstream fileName("");
  fileName.clear();
  fileName << net.outName << '_' << net.seed << "_spread_dataNode.txt";
  if (::save(fileName.str().c_str(), data_node, net.priChar) != 0) return -1;
  fileName.str("");
  fileName.clear();
  fileName << net.outName << '_' << net.seed
           << "_spread_dataTime.txt";  // fileName.str().c_str()
  if (::save(fileName.str().c_str(), data_time, net.priChar) != 0) return -1;
  return 0;
}

//**//****************************************************************
#endif  // NET_GRID
