#include "net.h"
#ifdef STAT_PEARSON

#include "common.h"
#include "StatPearson.h"
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

int Stat_cluster::save_data(const char* name) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  return 0;
}

int Stat_cluster::save(const char* name) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + "_cluster_params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 != save_data((fn + "_cluster").c_str())) {
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
int net_clear_pearson(Network& net) {
  nodeNeiAveDeg.clear();
  neiAveDeg.clear();
  if (dirFlag) {
    nodeNeiAveDegIn.clear();
    neiAveDegInOut.clear();
    neiAveDegInIn.clear();
    nodeNeiAveDegOut.clear();
    neiAveDegOutIn.clear();
    neiAveDegOutOut.clear();
  }
  return 0;
}

//**//****************************************************//*
int net_cal_pearson(Network& net) {
  if (!dirFlag) {
    if (!lkk.empty() && !weightFlag)
      cal_pearson_lkk(params_pearson.pearson, lkk, degArrVal,
                      linkSize);
    if (!p2p.empty()) {
      cal_nodeNeiAveDeg_weight(nodeNeiAveDeg, p2p, nodeDeg,
                               vvweight, nodeWeight, weightFlag);
      cal_neiAveDeg_weight(neiAveDeg, nodeNeiAveDeg, nodeDeg,
                           degArrSize, degArrNo, degArrVal,
                           degArrWeight, nodeWeight, weightFlag);
      if (!weightFlag) {
        if (lkk.empty())
          cal_pearson(params_pearson.pearson, p2p, linkSize);
      } else
        cal_pearson_dir_weight(params_pearson.pearson,
                               params_pearson.rho, p2p, vvweight,
                               netWeight, nodeDeg, nodeDeg,
                               weightFlag);
    }

  } else {
    // AllAll
    cal_nodeNeiAveDeg_AllAll_weight(nodeNeiAveDeg, p2p, nodeDeg,
                                    vvweight, nodeWeight,
                                    weightFlag);
    cal_neiAveDeg_weight(neiAveDeg, nodeNeiAveDeg, nodeDeg,
                         degArrSize, degArrNo, degArrVal,
                         degArrWeight, nodeWeight, weightFlag);
    cal_pearson_dir_weight(params_pearson.pearson, params_pearson.rho,
                           p2p, vvweight,
                           (weightFlag ? netWeightOut : linkSize),
                           nodeDeg, nodeDeg, weightFlag);

    // OutIn
    cal_nodeNeiAveDeg_weight(nodeNeiAveDegIn, p2p, nodeDegIn,
                             vvweight, nodeWeightOut, weightFlag);
    cal_neiAveDeg_weight(neiAveDegOutIn, nodeNeiAveDegIn,
                         nodeDegOut, degArrSizeOut, degArrNoOut,
                         degArrValOut, degArrWeightOut,
                         nodeWeightOut, weightFlag);
    cal_pearson_dir_weight(params_pearson.OutIn,
                           params_pearson.rhoOutIn, p2p, vvweight,
                           (weightFlag ? netWeightOut : linkSize),
                           nodeDegOut, nodeDegIn, weightFlag);

    if (STAT_TYPE_DIRAA) {
      // OutOut
      cal_nodeNeiAveDeg_weight(nodeNeiAveDegOut, p2p, nodeDegOut,
                               vvweight, nodeWeightOut, weightFlag);
      cal_neiAveDeg_weight(neiAveDegOutOut, nodeNeiAveDegOut,
                           nodeDegOut, degArrSizeOut, degArrNoOut,
                           degArrValOut, degArrWeightOut,
                           nodeWeightOut, weightFlag);
      cal_pearson_dir_weight(
          params_pearson.OutOut, params_pearson.rhoOutOut, p2p,
          vvweight, (weightFlag ? netWeightOut : linkSize),
          nodeDegOut, nodeDegOut, weightFlag);

      // InIn
      cal_neiAveDeg_weight(neiAveDegInIn, nodeNeiAveDegIn,
                           nodeDegIn, degArrSizeIn, degArrNoIn,
                           degArrValIn, degArrWeightOut,
                           nodeWeightOut, weightFlag);
      cal_pearson_dir_weight(params_pearson.InIn,
                             params_pearson.rhoInIn, p2p, vvweight,
                             (weightFlag ? netWeightOut : linkSize),
                             nodeDegIn, nodeDegIn, weightFlag);

      // InOut
      cal_neiAveDeg_weight(neiAveDegInOut, nodeNeiAveDegOut,
                           nodeDegIn, degArrSizeIn, degArrNoIn,
                           degArrValIn, degArrWeightOut,
                           nodeWeightOut, weightFlag);
      cal_pearson_dir_weight(params_pearson.InOut,
                             params_pearson.rhoInOut, p2p, vvweight,
                             (weightFlag ? netWeightOut : linkSize),
                             nodeDegIn, nodeDegOut, weightFlag);
    }
  }

  return 0;
}

//**//****************************************************//*
int net_read_params_pearson(istream& is, Network& net) {
  for (string s; is >> s;) {
    if (s == "--params_pearson.pearson") {
      is >> params_pearson.pearson;
      cout << s << '\t' << params_pearson.pearson << endl;
      continue;
    }
    if (dirFlag) {
      if (s == "--params_pearson.InIn") {
        is >> params_pearson.InIn;
        cout << s << '\t' << params_pearson.InIn << endl;
        continue;
      }
      if (s == "--params_pearson.InOut") {
        is >> params_pearson.InOut;
        cout << s << '\t' << params_pearson.InOut << endl;
        continue;
      }
      if (s == "--params_pearson.OutIn") {
        is >> params_pearson.OutIn;
        cout << s << '\t' << params_pearson.OutIn << endl;
        continue;
      }
      if (s == "--params_pearson.OutOut") {
        is >> params_pearson.OutOut;
        cout << s << '\t' << params_pearson.OutOut << endl;
        continue;
      }
    }
  }
  return 0;
}

int net_save_params_pearson(ostream& os, const Network& net) {
  if (!os) return -1;
  if (!dirFlag) {
    os << "--params_pearson.pearson\t" << params_pearson.pearson << '\n';
  } else {
    os << "--params_pearson.pearson\t" << params_pearson.pearson
       << "\n--params_pearson.rho\t" << params_pearson.rho
       << "\n--params_pearson.OutIn\t" << params_pearson.OutIn
       << "\n--params_pearson.rhoOutIn\t" << params_pearson.rhoOutIn
       << '\n';
    if (STAT_TYPE_DIRAA) {
      os << "--params_pearson.OutOut\t" << params_pearson.OutOut
         << "\n--params_pearson.rhoOutOut\t" << params_pearson.rhoOutOut
         << "\n--params_pearson.InIn\t" << params_pearson.InIn
         << "\n--params_pearson.rhoInIn\t" << params_pearson.rhoInIn
         << "\n--params_pearson.InOut\t" << params_pearson.InOut
         << "\n--params_pearson.rhoInOut\t" << params_pearson.rhoInOut
         << '\n';
    }
  }
  return 0;
}

int net_save_pearson(const Network& net, const char* name) {
  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else {
    stringstream ss;
    ss << seed;
    fn = saveName + '_' + ss.str();
  }
  int f = 0;
  // if(!nodeNeiAveDeg.empty()) f |= common_save1((fn +
  // "_nodeNeiAveDeg.txt").c_str(), nodeNeiAveDeg, priChar);
  // if(!neiAveDeg.empty()) f |= common_save1((fn +
  // "_neiAveDeg.txt").c_str(), neiAveDeg, priChar);

  // if(dirFlag){
  // if(!nodeNeiAveDegIn.empty()) f |= common_save1((fn +
  // "_nodeNeiAveDegIn.txt").c_str(), nodeNeiAveDegIn, priChar);
  // if(!nodeNeiAveDegOut.empty()) f |= common_save1((fn +
  // "_nodeNeiAveDegOut.txt").c_str(), nodeNeiAveDegOut, priChar);
  // if(!neiAveDegInIn.empty()) f |= common_save1((fn +
  // "_neiAveDegInIn.txt").c_str(), neiAveDegInIn, priChar);
  // if(!neiAveDegInOut.empty()) f |= common_save1((fn +
  // "_neiAveDegInOut.txt").c_str(), neiAveDegInOut, priChar);
  // if(!neiAveDegOutIn.empty()) f |= common_save1((fn +
  // "_neiAveDegOutIn.txt").c_str(), neiAveDegOutIn, priChar);
  // if(!neiAveDegOutOut.empty()) f |= common_save1((fn +
  // "_neiAveDegOutOut.txt").c_str(), neiAveDegOutOut, priChar);
  //}
  return f;
}
//**//****************************************************//*
#endif  // STAT_PEARSON
