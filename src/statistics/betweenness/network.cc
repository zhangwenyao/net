#include "network.h"
#ifdef STAT_BETWEENNESS

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
network::betweenness::Betweenness::Betweenness(void)
    : meanNode(0), meanEdge(0) {}

ostream& operator<<(ostream& os,
                    const network::betweenness::Betweenness& betweenness) {
  if (!os) {
    ERROR();
    return os;
  }
  os << "--betweenness.meanNode\t" << betweenness.meanNode
     << "\n--betweenness.meanEdge\t" << betweenness.meanEdge << '\n';
  return os;
}

int network::betweenness::Betweenness::save_params(ostream& os) const {
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int network::betweenness::Betweenness::save_params(const char* name) const {
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

int network::betweenness::Betweenness::save_data(const char* name,
                                                 const int dirFlag,
                                                 const char priChar,
                                                 const char priChar2) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  int f = 0;
  if (!betwNode.empty())
    f |= save1((fn + ".betwNode.txt").c_str(), betwNode, priChar);
  if (!betwEdge.empty())
    f |= save2((fn + ".betwEdge.txt").c_str(), betwEdge, priChar2);
  if (!betwLink.empty())
    f |= save1((fn + ".betwLink.txt").c_str(), betwLink, priChar);
  if (!minDistMatr.empty())
    f |= save2((fn + ".minDistMatr.txt").c_str(), minDistMatr, priChar2);
  if (!minDistMean.empty())
    f |= save1((fn + ".minDistMean.txt").c_str(), minDistMean, priChar);
  if (0 != f) ERROR();
  return f;
}

int network::betweenness::Betweenness::save(const char* name, const int dirFlag,
                                            const char priChar,
                                            const char priChar2) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + ".betweenness.params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 !=
      save_data((fn + ".betweenness").c_str(), dirFlag, priChar, priChar2)) {
    ERROR();
    return -1;
  }
  return 0;
}

int network::betweenness::Betweenness::read_params_1(string& s, istream& is) {
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = 1;
  do {
    if (s == "--betweenness.meanNode") {
      is >> meanNode;
      cout << s << '\t' << meanNode << endl;
      break;
    }
    if (s == "--betweenness.meanEdge") {
      is >> meanEdge;
      cout << s << '\t' << meanEdge << endl;
      break;
    }
    flag = 0;
  } while (0);
  if (flag) s.clear();
  return 0;
}

network::betweenness::Betweenness& network::betweenness::Betweenness::clear(
    void) {
  meanNode = 0;
  meanEdge = 0;
  betwNode.clear();
  betwEdge.clear();
  minDistMatr.clear();
  minDistMean.clear();
  return *this;
}

// ******************************************************
Networks& Networks::stat_betweenness(const bool is_large) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (p2p.empty()) {
    if (linkMatr.empty()) {
      ERROR();
      runStatus = -1;
      return *this;
    }
    linkMatr_2_p2p(p2p, linkMatr);
    if (dirFlag) p2pOut_2_p2pIn(p2pIn, p2p);
  }

  if (distFlag) {
    if (dirFlag)
      runStatus = network::betweenness::cal_betweenness(
          betweenness.betwNode, betweenness.betwEdge, betweenness.meanNode,
          betweenness.meanEdge, betweenness.minDistMatr,
          betweenness.minDistMean, p2p, p2pIn, linkMatr);
    else
      runStatus = network::betweenness::cal_betweenness(
          betweenness.betwNode, betweenness.betwEdge, betweenness.meanNode,
          betweenness.meanEdge, betweenness.minDistMatr,
          betweenness.minDistMean, p2p, p2p, linkMatr);
  } else {
    if (dirFlag)
      runStatus = network::betweenness::cal_betweenness0(
          betweenness.betwNode, betweenness.betwEdge, betweenness.meanNode,
          betweenness.meanEdge, betweenness.minDistMatr,
          betweenness.minDistMean, p2p, p2pIn);
    else {
      if (!is_large)
        runStatus = network::betweenness::cal_betweenness0(
            betweenness.betwNode, betweenness.betwEdge, betweenness.meanNode,
            betweenness.meanEdge, betweenness.minDistMatr,
            betweenness.minDistMean, p2p, p2p);
      else
        runStatus = network::betweenness::cal_betweenness0_large(
            betweenness.betwNode, betweenness.betwLink, betweenness.meanNode,
            betweenness.meanEdge, betweenness.minDistMean, p2p, p2p, link);
    }
  }
  if (0 != runStatus) ERROR();
  return *this;
}

// ******************************************************
#endif  // STAT_BETWEENNESS
