#include "net.h"
#ifdef STAT_KENDALL

#include "common.h"
#include "StatKendall.h"
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
  if (0 != save_data((fn + ".cluster").c_str()), priChar, priChar2) {
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
int net_clear_kendallTau(Network& net) { return 0; }

//**//****************************************************//*
int net_cal_kendallTau(Network& net) {
  if (lkkSum.empty() &&
      0 != lkk_2_lkkSum(lkkSum, lkk, dirFlag)) {
    ERROR();
    return -1;
  }
  cal_kendallTau_lkkSum(params_kendall.tau, lkk, lkkSum,
                        dirFlag);
  // al_kendallTau_lkk(params_kendall.tau, lkk, linkSize,
  // dirFlag);
  if (dirFlag) {
    if (lkkSumOutIn.empty() &&
        0 != lkk_2_lkkSum(lkkSumOutIn, lkkOutIn, dirFlag)) {
      ERROR();
      return -1;
    }
    cal_kendallTau_lkkSum(params_kendall.OutIn, lkkOutIn,
                          lkkSumOutIn, dirFlag);
  }
  return 0;
}

//**//****************************************************//*
int net_read_params_kendallTau(istream& is, Network& net) {
  for (string s; is >> s;) {
    if (s == "--params_kendall.tau") {
      is >> params_kendall.tau;
      cout << s << '\t' << params_kendall.tau << endl;
      continue;
    }
    if (s == "--params_kendall.OutIn") {
      is >> params_kendall.OutIn;
      cout << s << '\t' << params_kendall.OutIn << endl;
      continue;
    }
  }
  return 0;
}

int net_save_params_kendallTau(ostream& os, const Network& net) {
  if (!os) return -1;
  os << "--params_kendall.tau\t" << params_kendall.tau << '\n';
  if (dirFlag)
    os << "--params_kendall.OutIn\t" << params_kendall.OutIn << '\n';
  return 0;
}

int net_save_kendallTau(const Network& net, const char* name) {
  // string fn;
  // if(name != NULL && name[0] != '\0') fn = name;
  // else{
  // stringstream ss;
  // ss << seed;
  // fn = saveName + '_' + ss.str();
  //}
  int f = 0;
  return f;
}
//**//****************************************************//*
#endif  // STAT_KENDALL
