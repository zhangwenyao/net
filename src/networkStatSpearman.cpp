#include "net.h"
#ifdef STAT_SPEARMAN

#include "common.h"
#include "NetRandom.h"
#include "StatSpearman.h"
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
int net_clear_spearman(Network& net) {
  nodeNeiAveDeg2.clear();
  neiAveDeg2.clear();
  if (dirFlag) {
    nodeNeiAveDeg2In.clear();
    neiAveDeg2InOut.clear();
    neiAveDeg2InIn.clear();
    nodeNeiAveDeg2Out.clear();
    neiAveDeg2OutIn.clear();
    neiAveDeg2OutOut.clear();
  }
#ifdef MODEL_GAUSS
  params_spearman.GaussS2.clear();
#endif
  return 0;
}

//**//****************************************************//*
int net_cal_spearman(Network& net) {
  if (!dirFlag) {
    if (!lkk.empty() && !weightFlag)
      cal_spearman_lkk(params_spearman.spearman, lkk, deg2ArrVal,
                       linkSize);
    if (!p2p.empty()) {
      cal_nodeNeiAveDeg2_weight(nodeNeiAveDeg2, p2p, nodeDeg,
                                deg2ArrVal, degArrNo, vvweight,
                                nodeWeight, weightFlag);
      cal_neiAveDeg2_weight(neiAveDeg2, nodeNeiAveDeg2, nodeDeg,
                            degArrSize, degArrNo, degArrVal,
                            degArrWeight, nodeWeight, weightFlag);
      if (!weightFlag) {
        if (lkk.empty())
          cal_spearman(params_spearman.spearman, p2p, deg2ArrVal,
                       degArrNo, linkSize);
      } else
        cal_spearman_dir_weight(params_spearman.spearman,
                                params_spearman.rho, p2p, vvweight,
                                netWeight, nodeDeg, degArrNo,
                                deg2ArrVal, nodeDeg, degArrNo,
                                deg2ArrVal, weightFlag);
    }

  } else {  // dirFlag
    // AllAll
    cal_nodeNeiAveDeg2_AllAll(nodeNeiAveDeg2, p2p, nodeDeg,
                              deg2ArrVal, degArrNo, vvweight,
                              nodeWeight, weightFlag);
    cal_neiAveDeg2_weight(neiAveDeg2, nodeNeiAveDeg2, nodeDeg,
                          degArrSize, degArrNo, degArrVal,
                          degArrWeight, nodeWeight, weightFlag);
    cal_spearman_dir_weight(
        params_spearman.spearman, params_spearman.rho, p2p,
        vvweight, (weightFlag ? netWeightOut : linkSize),
        nodeDeg, degArrNo, deg2ArrVal, nodeDeg, degArrNo,
        deg2ArrVal, weightFlag);

    // OutIn
    cal_nodeNeiAveDeg2_weight(nodeNeiAveDeg2In, p2p, nodeDegIn,
                              deg2ArrValIn, degArrNoIn, vvweight,
                              nodeWeightOut, weightFlag);
    cal_neiAveDeg2_weight(neiAveDeg2OutIn, nodeNeiAveDeg2In,
                          nodeDegOut, degArrSizeOut, degArrNoOut,
                          degArrValOut, degArrWeightOut,
                          nodeWeightOut, weightFlag);
    cal_spearman_dir_weight(
        params_spearman.OutIn, params_spearman.rhoOutIn, p2p,
        vvweight, (weightFlag ? netWeightOut : linkSize),
        nodeDegOut, degArrNoOut, deg2ArrValOut, nodeDegIn,
        degArrNoIn, deg2ArrValIn, weightFlag);

    if (STAT_TYPE_DIRAA) {
      // OutOut
      cal_nodeNeiAveDeg2_weight(
          nodeNeiAveDeg2Out, p2p, nodeDegOut, deg2ArrValOut,
          degArrNoOut, vvweight, nodeWeightOut, weightFlag);
      cal_neiAveDeg2_weight(neiAveDeg2OutOut, nodeNeiAveDeg2Out,
                            nodeDegOut, degArrSizeOut, degArrNoOut,
                            degArrValOut, degArrWeightOut,
                            nodeWeightOut, weightFlag);
      cal_spearman_dir_weight(
          params_spearman.OutOut, params_spearman.rhoOutOut, p2p,
          vvweight, (weightFlag ? netWeightOut : linkSize),
          nodeDegOut, degArrNoOut, deg2ArrValOut, nodeDegOut,
          degArrNoOut, deg2ArrValOut, weightFlag);

      // InIn
      cal_neiAveDeg2_weight(neiAveDeg2InIn, nodeNeiAveDeg2In,
                            nodeDegIn, degArrSizeIn, degArrNoIn,
                            degArrValIn, degArrWeightOut,
                            nodeWeightOut, weightFlag);
      cal_spearman_dir_weight(
          params_spearman.InIn, params_spearman.rhoInIn, p2p,
          vvweight, (weightFlag ? netWeightOut : linkSize),
          nodeDegIn, degArrNoIn, deg2ArrValIn, nodeDegIn,
          degArrNoIn, deg2ArrValIn, weightFlag);

      // InOut
      cal_neiAveDeg2_weight(neiAveDeg2InOut, nodeNeiAveDeg2Out,
                            nodeDegIn, degArrSizeIn, degArrNoIn,
                            degArrValIn, degArrWeightOut,
                            nodeWeightOut, weightFlag);
      cal_spearman_dir_weight(
          params_spearman.InOut, params_spearman.rhoInOut, p2p,
          vvweight, (weightFlag ? netWeightOut : linkSize),
          nodeDegIn, degArrNoIn, deg2ArrValIn, nodeDegOut,
          degArrNoOut, deg2ArrValOut, weightFlag);
    }
  }

  return 0;
}

int net_degArr_2_deg2ArrVal_weight(Network& net) {
  if (degArrVal.empty() || degArrVal.size() != degArrSize.size()) {
    ERROR();
    return -1;
  }

  // deg2ArrVal All
  if (deg2ArrVal.empty()) {
    if (!weightFlag) {
      if (0 != degArrVal_2_deg2ArrVal(deg2ArrVal, degArrSize,
                                      degArrVal, linkSize,
                                      dirFlag)) {
        ERROR();
        return -1;
      }

    } else {  // weightFlag
      if (0 != degArrWeight_2_deg2ArrVal(deg2ArrVal, degArrWeight,
                                         netWeight)) {
        ERROR();
        return -1;
      }
    }
  }

  if (dirFlag) {       // dirFlag
    if (weightFlag) {  // dirFlag weightFlag
      // Out
      if (deg2ArrValOut.empty() &&
          0 != degArrWeight_2_deg2ArrVal(deg2ArrValOut, degArrWeightOut,
                                         netWeightOut)) {
        ERROR();
        return -1;
      }

      // In
      if (deg2ArrValIn.empty() &&
          0 != degArrWeight_2_deg2ArrVal(deg2ArrValIn, degArrWeightIn,
                                         netWeightIn)) {
        ERROR();
        return -1;
      }

    } else {  // dirFlag !weightFlag
      // Out
      if (deg2ArrValOut.empty() &&
          0 != degArrVal_2_deg2ArrVal(deg2ArrValOut, degArrSizeOut,
                                      degArrValOut, linkSize,
                                      dirFlag)) {
        ERROR();
        return -1;
      }

      // In
      if (deg2ArrValIn.empty() &&
          0 != degArrVal_2_deg2ArrVal(deg2ArrValIn, degArrSizeIn,
                                      degArrValIn, linkSize,
                                      dirFlag)) {
        ERROR();
        return -1;
      }
    }
  }

  return 0;
}

//**//****************************************************//*
int net_read_params_spearman(istream& is, Network& net) {
  for (string s; is >> s;) {
    if (s == "--params_spearman.spearman") {
      is >> params_spearman.spearman;
      cout << s << '\t' << params_spearman.spearman << endl;
      continue;
    }
    if (dirFlag) {
      if (s == "--params_spearman.InIn") {
        is >> params_spearman.InIn;
        cout << s << '\t' << params_spearman.InIn << endl;
        continue;
      }
      if (s == "--params_spearman.InOut") {
        is >> params_spearman.InOut;
        cout << s << '\t' << params_spearman.InOut << endl;
        continue;
      }
      if (s == "--params_spearman.OutIn") {
        is >> params_spearman.OutIn;
        cout << s << '\t' << params_spearman.OutIn << endl;
        continue;
      }
      if (s == "--params_spearman.OutOut") {
        is >> params_spearman.OutOut;
        cout << s << '\t' << params_spearman.OutOut << endl;
        continue;
      }
    }
#ifdef MODEL_GAUSS
    if (s == "--params_spearman.r0") {
      is >> params_spearman.r0;
      cout << s << '\t' << params_spearman.r0 << endl;
      continue;
    }
#endif
  }
  return 0;
}

int net_save_params_spearman(ostream& os, const Network& net) {
  if (!os) return -1;

#ifdef MODEL_GAUSS
  os << "--params_spearman.r0\t" << params_spearman.r0 << '\n';
#endif

  os << "--params_spearman.spearman\t" << params_spearman.spearman << '\n';
  if (dirFlag) {
    os << "--params_spearman.rho\t" << params_spearman.rho
       << "\n--params_spearman.OutIn\t" << params_spearman.OutIn
       << "\n--params_spearman.rhoOutIn\t" << params_spearman.rhoOutIn
       << '\n';
    if (STAT_TYPE_DIRAA) {
      os << "--params_spearman.OutOut\t" << params_spearman.OutOut
         << "\n--params_spearman.rhoOutOut\t" << params_spearman.rhoOutOut
         << "\n--params_spearman.InIn\t" << params_spearman.InIn
         << "\n--params_spearman.rhoInIn\t" << params_spearman.rhoInIn
         << "\n--params_spearman.InOut\t" << params_spearman.InOut
         << "\n--params_spearman.rhoInOut\t" << params_spearman.rhoInOut
         << '\n';
    }
  }
  return 0;
}

int net_save_spearman(const Network& net, const char* name) {
  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else {
    stringstream ss;
    ss << seed;
    fn = saveName + '_' + ss.str();
  }
  int f = 0;
// if(!deg2ArrVal.empty()) f |= common_save1((fn +
// "_deg2ArrVal.txt").c_str(), deg2ArrVal, priChar);
// if(!nodeNeiAveDeg2.empty()) f |= common_save1((fn +
// "_nodeNeiAveDeg2.txt").c_str(), nodeNeiAveDeg2, priChar);
// if(!neiAveDeg2.empty()) f |= common_save1((fn +
// "_neiAveDeg2.txt").c_str(), neiAveDeg2, priChar);

// if(dirFlag){
// if(!deg2ArrValIn.empty()) f |= common_save1((fn +
// "_deg2ArrValIn.txt").c_str(), deg2ArrValIn, priChar);
// if(!deg2ArrValOut.empty()) f |= common_save1((fn +
// "_deg2ArrValOut.txt").c_str(), deg2ArrValOut, priChar);
// if(!nodeNeiAveDeg2In.empty()) f |= common_save1((fn +
// "_nodeNeiAveDeg2In.txt").c_str(), nodeNeiAveDeg2In, priChar);
// if(!nodeNeiAveDeg2Out.empty()) f |= common_save1((fn +
// "_nodeNeiAveDeg2Out.txt").c_str(), nodeNeiAveDeg2Out, priChar);
// if(!neiAveDeg2InIn.empty()) f |= common_save1((fn +
// "_neiAveDeg2InIn.txt").c_str(), neiAveDeg2InIn, priChar);
// if(!neiAveDeg2InOut.empty()) f |= common_save1((fn +
// "_neiAveDeg2InOut.txt").c_str(), neiAveDeg2InOut, priChar);
// if(!neiAveDeg2OutIn.empty()) f |= common_save1((fn +
// "_neiAveDeg2OutIn.txt").c_str(), neiAveDeg2OutIn, priChar);
// if(!neiAveDeg2OutOut.empty()) f |= common_save1((fn +
// "_neiAveDeg2OutOut.txt").c_str(), neiAveDeg2OutOut, priChar);
//}

#ifdef MODEL_GAUSS
// if(params_spearman.GaussS2.size() > 0) f |= common_save1((fn +
// "_SGaussS2.txt").c_str(), params_spearman.GaussS2, priChar);
#endif  // MODEL_GAUSS
  return f;
}
//**//****************************************************//*

#ifdef MODEL_GAUSS
//**//****************************************************//*
int net_save_gauss(const Network& net, const char* name) {
  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else {
    stringstream ss;
    ss.clear();
    ss << seed;
    fn = saveName + '_' + ss.str();
  }

  int f = 0;
  f |= net_save_params_0(net, fn.c_str());
  if (status == 0) return 0;
  if (status != 1 && status != -2) return -1;
  if (status == -2)
    f |= common_save1((fn + "_p2pSize.txt").c_str(), p2pSize);
  if (nodeDeg.size() > 0)
    f |= common_save1((fn + "_nodeDeg.txt").c_str(), nodeDeg, priChar);
  if (degArrVal.size() > 0)
    f |= common_save1((fn + "_degArrVal.txt").c_str(), degArrVal,
                      priChar);
  if (degArrSize.size() > 0)
    f |= common_save1((fn + "_degArrSize.txt").c_str(), degArrSize,
                      priChar);
  if (p2p.size() > 0)
    f |= common_save2((fn + "_p2p.txt").c_str(), p2p, priChar);

  if (nodeNeiAveDeg.size() > 0)
    f |= common_save1((fn + "_nodeNeiAveDeg.txt").c_str(), nodeNeiAveDeg,
                      priChar);
  if (neiAveDeg.size() > 0)
    f |= common_save1((fn + "_neiAveDeg.txt").c_str(), neiAveDeg,
                      priChar);
  if (nodeNeiAveNo.size() > 0)
    f |= common_save1((fn + "_nodeNeiAveNo.txt").c_str(), nodeNeiAveNo,
                      priChar);
  if (neiAveNo.size() > 0)
    f |=
        common_save1((fn + "_neiAveNo.txt").c_str(), neiAveNo, priChar);

  if (deg2ArrVal.size() > 0)
    f |= common_save1((fn + "_deg2ArrVal.txt").c_str(), deg2ArrVal,
                      priChar);
  if (nodeNeiAveDeg2.size() > 0)
    f |= common_save1((fn + "_nodeNeiAveDeg2.txt").c_str(), nodeNeiAveDeg2,
                      priChar);
  if (neiAveDeg2.size() > 0)
    f |= common_save1((fn + "_neiAveDeg2.txt").c_str(), neiAveDeg2,
                      priChar);

  if (params_spearman.GaussS2.size() > 0)
    f |= common_save1((fn + "_SGaussS2.txt").c_str(),
                      params_spearman.GaussS2, priChar);
  if (lkkProb.size() > 0)
    f |= common_save2((fn + "_lkkProb.txt").c_str(), lkkProb, priChar);

  return f;
}

//**//****************************************************//*
int net_read_SGaussS2(Network& net, const char* name) {
  string fn;
  if (name != NULL)
    fn = name;
  else
    fn = readName;
  if (fn.size() <= 0) return -1;

  p2p.clear();
  if (0 != common_read1_0((fn + "_SGaussS2.txt").c_str(),
                          params_spearman.GaussS2)) {
    ERROR();
    return -1;
  }
  return 0;
}

//**//****************************************************//*
int net_cal_lkkProb_gauss(Network& net) {
  const NodeType degSize = degArrVal.size();
  if (argv.find("read_stat_spearman.GaussS2") != string::npos) {
    if (net_read_SGaussS2(net) != 0)
      return -1;
    else
      return 0;
  }

  params_spearman.GaussS2.resize(degSize);
  for (NodeType i = 0; i < degSize; i++) {
    cal_lkkProb_gaussS2(params_spearman.GaussS2[i], deg2ArrVal,
                        degArrVal, degArrSize, i,
                        params_spearman.r0);
  }
  lkkProb.resize(degSize, VDouble(degSize));
  cal_lkkProb_gauss(lkkProb, params_spearman.GaussS2, deg2ArrVal,
                    params_spearman.r0);
  return 0;
}

int net_gauss_new_ranLink(
    Network& net)  // 随机选点按度之差的相应高斯概率连边，重连时随机选点再选边
{
  // 初始化连边信息
  p2p.resize(nodeSize);
  remNodeNum.resize(nodeSize);
  link.resize(2 * linkSize);
  for (NodeType i = 0, *p = &link[0]; i < nodeSize; i++) {
    p2p[i].clear();
    p2p[i].reserve(nodeDeg[i]);
    remNodeNum[i] = i;
    for (NodeType j = 0; j < nodeDeg[i]; j++)
      *p++ = i;  // 记录各点剩余度和网络所有连边情况
  }
  if (deg2ArrVal.empty() &&
      0 != degArrVal_2_deg2ArrVal(deg2ArrVal, degArrSize, degArrVal,
                                  linkSize)) {
    ERROR();
    return -1;
  }
  if (degArrNo.empty() &&
      0 != degArrVal_2_degArrNo(degArrNo, degArrVal)) {
    ERROR();
    return -1;
  }
  linkRemain = linkSize;
  LinkType linkRemain0 = linkRemain;
  // 随机连边
  // 计算各度之差相应的高斯概率
  if (net_cal_lkkProb_gauss(net) != 0) {
    ERROR("net_cal_lkkProb_gauss");
    return status = -1;
  }
  std::cout << "\tcal_lkkProb_gauss end\n";
  NodeType remPoiSize = nodeSize;
  for (size_t count = 0, iDel = 1; linkRemain > 0 && remPoiSize > 0;) {
    // delLink_p2p_randLink(p2p, nodeDeg, p2pSize, remNodeNum,
    // linkRemain, linkSize, link, iDel); // 随机删iDel条边
    if (0 == addLink_p2p_ranLink_lkkProb(p2p, nodeDeg, lkkProb,
                                         degArrNo, remPoiSize,
                                         linkRemain, link, 100000))
      break;  // 随机抽取剩余度连边
    std::cout << "\tlinkRemain:\t" << linkRemain << '\n';
    if (linkRemain < linkRemain0) {
      count = 0;
      iDel = 1;
      linkRemain0 = linkRemain;
    } else if (++count >= 1000) {
      count = 0;
      if (++iDel > 5) break;
    }
  }
  std::cout << "\tadd_link end\n";

  return 0;
}

//**//****************************************************//*
#endif  // MODEL_GAUSS

//**//****************************************************//*
#endif  // STAT_SPEARMAN
