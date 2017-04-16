#include "net.h"
#ifdef STAT_SIMILARITY

#include "common.h"
#include "StatSimilarity.h"
#include "networks.h"
using namespace std;
//**//****************************************************//*
Stat_cluster::Stat_cluster(void) : coef(0) {}

ostream& operator<<(ostream& os, const Stat_cluster& cluster) {
  if (!os) {
    ERROR();
    return os;
  }
  os << "--cluster.coef\t" << cluster.coef << '\n';
  return os;
}

int Stat_cluster::save_params(ostream& os) const {
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int Stat_cluster::save_params(const char* name) const {
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

int Stat_cluster::save_data(const char* name, const char priChar, const char priChar2) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  return 0;
}

int Stat_cluster::save(const char* name, const char priChar, const char priChar2) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + ".cluster.params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 != save_data((fn + ".cluster").c_str(), priChar, priChar2)) {
    ERROR();
    return -1;
  }
  return 0;
}

int Stat_cluster::read_params_1(string& s, istream& is) {
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = 1;
  do {
    if (s == "--cluster.coef") {
      is >> coef;
      cout << s << '\t' << coef << endl;
      break;
    }
    flag = 0;
  } while (0);
  if (flag) s.clear();
  return 0;
}

Stat_cluster& Stat_cluster::clear(void) {
  coef = 0;
  Node.clear();
  return *this;
}

//**//****************************************************//*
Networks& Networks::stat_cluster(void) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (linkMatr.empty() && weightFlag) {
    if (weightMatr.empty()) {
      ERROR();
      runStatus = -1;
      return *this;
    }
    weightMatr_2_linkMatr(linkMatr, weightMatr);
  }
  if (weightFlag)
    runStatus = cal_cluster_directed_weight(cluster.coef, cluster.Node,
                                            weightMatr, linkMatr);
  else
    runStatus =
        cal_cluster_directed_unweight(cluster.coef, cluster.Node, linkMatr);
  if (0 != runStatus) ERROR();
  return *this;
}

//**//****************************************************//*
int net_read_params_similarity(istream& is, Network& net) { return 0; }

int net_save_params_similarity(ostream& os, const Network& net) {
  if (!os) return -1;
  return 0;
}

int net_save_similarity(const Network& net, const char* name) {
  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else {
    stringstream ss;
    ss << seed;
    fn = saveName + '_' + ss.str();
  }
  int f = 0;
  if (!params_similarity.NodeCoef.empty())
    f |= common_save2((fn + "_stat_similarity.NodeCoef.txt").c_str(),
                      params_similarity.NodeCoef, priChar2);
  if (!params_similarity.EdgeCoef.empty())
    f |= common_save2((fn + "_stat_similarity.EdgeCoef.txt").c_str(),
                      params_similarity.EdgeCoef, priChar2);
  return f;
}

//**//****************************************************//*
int net_clear_similarity(Network& net) {
  params_similarity.NodeCoef.clear();
  params_similarity.EdgeCoef.clear();
  return 0;
}

//**//****************************************************//*
#include "h"
int net_similarity(Network& net, Network& net2) {
  if (dirFlag != net2.dirFlag) {
    ERROR();
    return -1;
  }
  if (link.empty()) p2p_2_link(link, p2p, dirFlag);
  if (net2.link.empty()) p2p_2_link(net2.link, net2.p2p, net2.dirFlag);
  int f = 0;
  params_similarity.NodeCoef.resize(nodeSize);
  params_similarity.NodeCoef[0].resize(net2.nodeSize);
  f = cal_similarity(params_similarity.NodeCoef,
                     params_similarity.EdgeCoef, link, net2.link,
                     dirFlag);
  return f;
}

//**//****************************************************//*
#endif  // STAT_SIMILARITY
