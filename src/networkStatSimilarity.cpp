#include "net.h"
#ifdef STAT_SIMILARITY

#include "StatSimilarity.h"
#include "common.h"
#include "networks.h"
using namespace std;
//**//****************************************************//*
Stat_similarity::Stat_similarity(void) : nodeCoef(0), edgeCoef(0) {}

ostream& operator<<(ostream& os, const Stat_similarity& similarity) {
  if (!os) {
    ERROR();
    return os;
  }
  // os << "--similarity.nodeCoef\t" << similarity.nodeCoef
  //<< "--\nsimilarity.edgeCoef\t" << similarity.edgeCoef << '\n';
  return os;
}

int Stat_similarity::save_params(ostream& os) const {
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int Stat_similarity::save_params(const char* name) const {
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

int Stat_similarity::save_data(const char* name, const char priChar,
                               const char priChar2) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  int f = 0;
  if (!nodeCoef.empty())
    f |= common_save2((fn + ".nodeCoef.txt").c_str(), nodeCoef, priChar2);
  if (!edgeCoef.empty())
    f |= common_save2((fn + ".edgeCoef.txt").c_str(), edgeCoef, priChar2);
  return f;
}

int Stat_similarity::save(const char* name, const char priChar,
                          const char priChar2) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + ".params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 != save_data(fn.c_str(), priChar, priChar2)) {
    ERROR();
    return -1;
  }
  return 0;
}

int Stat_similarity::read_params_1(string& s, istream& is) {
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = 1;
  do {
    // if (s == "--similarity.nodeCoef") {
    // is >> nodeCoef;
    // cout << s << '\t' << nodeCoef << endl;
    // break;
    //}
    flag = 0;
  } while (0);
  if (flag) s.clear();
  return 0;
}

Stat_similarity& Stat_similarity::clear(void) {
  nodeCoef.clear();
  edgeCoef.clear();
  return *this;
}

//**//****************************************************//*
Networks& Networks::stat_similarity(Networks& net2) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (dirFlag != net2.dirFlag) {
    ERROR();
    runStatus = -1;
    return *this;
  }
  if (link.empty()) p2p_2_link(link, p2p, dirFlag);
  if (net2.link.empty()) p2p_2_link(net2.link, net2.p2p, net2.dirFlag);
  similarity.nodeCoef.resize(nodeSize);
  similarity.nodeCoef[0].resize(net2.nodeSize);
  runStatus = cal_similarity(similarity.nodeCoef, similarity.edgeCoef, link,
                             net2.link, dirFlag);
  if (0 != runStatus) ERROR();
  return *this;
}

//**//****************************************************//*
#endif  // STAT_SIMILARITY
