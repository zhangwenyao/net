#include "network.h"
#ifdef STAT_CLUSTER

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
network::cluster::Cluster::Cluster(void)
    : coef(0)
{
}

ostream& operator<<(ostream& os, const network::cluster::Cluster& cluster)
{
  if (!os) {
    ERROR();
    return os;
  }
  os << "--cluster.coef\t" << cluster.coef << '\n';
  return os;
}

int network::cluster::Cluster::save_params(ostream& os) const
{
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int network::cluster::Cluster::save_params(const char* name) const
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

int network::cluster::Cluster::save_data(const char* name, const int dirFlag,
    const char priChar, const char priChar2) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  return 0;
}

int network::cluster::Cluster::save(const char* name, const int dirFlag,
    const char priChar, const char priChar2) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + ".cluster.params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 != save_data((fn + ".cluster").c_str(), dirFlag, priChar, priChar2)) {
    ERROR();
    return -1;
  }
  return 0;
}

int network::cluster::Cluster::read_params_1(string& s, istream& is)
{
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
  if (flag)
    s.clear();
  return 0;
}

network::cluster::Cluster& network::cluster::Cluster::clear(void)
{
  coef = 0;
  Node.clear();
  return *this;
}

// ******************************************************
Networks& Networks::stat_cluster(void)
{
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
    runStatus = network::cluster::cal_cluster_directed_weight(
        cluster.coef, cluster.Node, weightMatr, linkMatr);
  else
    runStatus = network::cluster::cal_cluster_directed_unweight(
        cluster.coef, cluster.Node, linkMatr);
  if (0 != runStatus)
    ERROR();
  return *this;
}

// ******************************************************
#endif // STAT_CLUSTER
