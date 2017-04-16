#include "StatSpearman.h"
#ifdef STAT_SPEARMAN

#include "common.h"
#include "NetRandom.h"
#include "networkStatSpearman.h"
using namespace std;

//**//****************************************************//*
int net_clear_spearman(Network& net) {
  net.nodeNeiAveDeg2.clear();
  net.neiAveDeg2.clear();
  if (net.dirFlag) {
    net.nodeNeiAveDeg2In.clear();
    net.neiAveDeg2InOut.clear();
    net.neiAveDeg2InIn.clear();
    net.nodeNeiAveDeg2Out.clear();
    net.neiAveDeg2OutIn.clear();
    net.neiAveDeg2OutOut.clear();
  }
#ifdef MODEL_GAUSS
  net.params_spearman.GaussS2.clear();
#endif
  return 0;
}

//**//****************************************************//*
int net_cal_spearman(Network& net) {
  if (!net.dirFlag) {
    if (!net.lkk.empty() && !net.weightFlag)
      cal_spearman_lkk(net.params_spearman.spearman, net.lkk, net.deg2ArrVal,
                       net.linkSize);
    if (!net.p2p.empty()) {
      cal_nodeNeiAveDeg2_weight(net.nodeNeiAveDeg2, net.p2p, net.nodeDeg,
                                net.deg2ArrVal, net.degArrNo, net.vvweight,
                                net.nodeWeight, net.weightFlag);
      cal_neiAveDeg2_weight(net.neiAveDeg2, net.nodeNeiAveDeg2, net.nodeDeg,
                            net.degArrSize, net.degArrNo, net.degArrVal,
                            net.degArrWeight, net.nodeWeight, net.weightFlag);
      if (!net.weightFlag) {
        if (net.lkk.empty())
          cal_spearman(net.params_spearman.spearman, net.p2p, net.deg2ArrVal,
                       net.degArrNo, net.linkSize);
      } else
        cal_spearman_dir_weight(net.params_spearman.spearman,
                                net.params_spearman.rho, net.p2p, net.vvweight,
                                net.netWeight, net.nodeDeg, net.degArrNo,
                                net.deg2ArrVal, net.nodeDeg, net.degArrNo,
                                net.deg2ArrVal, net.weightFlag);
    }

  } else {  // net.dirFlag
    // AllAll
    cal_nodeNeiAveDeg2_AllAll(net.nodeNeiAveDeg2, net.p2p, net.nodeDeg,
                              net.deg2ArrVal, net.degArrNo, net.vvweight,
                              net.nodeWeight, net.weightFlag);
    cal_neiAveDeg2_weight(net.neiAveDeg2, net.nodeNeiAveDeg2, net.nodeDeg,
                          net.degArrSize, net.degArrNo, net.degArrVal,
                          net.degArrWeight, net.nodeWeight, net.weightFlag);
    cal_spearman_dir_weight(
        net.params_spearman.spearman, net.params_spearman.rho, net.p2p,
        net.vvweight, (net.weightFlag ? net.netWeightOut : net.linkSize),
        net.nodeDeg, net.degArrNo, net.deg2ArrVal, net.nodeDeg, net.degArrNo,
        net.deg2ArrVal, net.weightFlag);

    // OutIn
    cal_nodeNeiAveDeg2_weight(net.nodeNeiAveDeg2In, net.p2p, net.nodeDegIn,
                              net.deg2ArrValIn, net.degArrNoIn, net.vvweight,
                              net.nodeWeightOut, net.weightFlag);
    cal_neiAveDeg2_weight(net.neiAveDeg2OutIn, net.nodeNeiAveDeg2In,
                          net.nodeDegOut, net.degArrSizeOut, net.degArrNoOut,
                          net.degArrValOut, net.degArrWeightOut,
                          net.nodeWeightOut, net.weightFlag);
    cal_spearman_dir_weight(
        net.params_spearman.OutIn, net.params_spearman.rhoOutIn, net.p2p,
        net.vvweight, (net.weightFlag ? net.netWeightOut : net.linkSize),
        net.nodeDegOut, net.degArrNoOut, net.deg2ArrValOut, net.nodeDegIn,
        net.degArrNoIn, net.deg2ArrValIn, net.weightFlag);

    if (STAT_TYPE_DIRAA) {
      // OutOut
      cal_nodeNeiAveDeg2_weight(
          net.nodeNeiAveDeg2Out, net.p2p, net.nodeDegOut, net.deg2ArrValOut,
          net.degArrNoOut, net.vvweight, net.nodeWeightOut, net.weightFlag);
      cal_neiAveDeg2_weight(net.neiAveDeg2OutOut, net.nodeNeiAveDeg2Out,
                            net.nodeDegOut, net.degArrSizeOut, net.degArrNoOut,
                            net.degArrValOut, net.degArrWeightOut,
                            net.nodeWeightOut, net.weightFlag);
      cal_spearman_dir_weight(
          net.params_spearman.OutOut, net.params_spearman.rhoOutOut, net.p2p,
          net.vvweight, (net.weightFlag ? net.netWeightOut : net.linkSize),
          net.nodeDegOut, net.degArrNoOut, net.deg2ArrValOut, net.nodeDegOut,
          net.degArrNoOut, net.deg2ArrValOut, net.weightFlag);

      // InIn
      cal_neiAveDeg2_weight(net.neiAveDeg2InIn, net.nodeNeiAveDeg2In,
                            net.nodeDegIn, net.degArrSizeIn, net.degArrNoIn,
                            net.degArrValIn, net.degArrWeightOut,
                            net.nodeWeightOut, net.weightFlag);
      cal_spearman_dir_weight(
          net.params_spearman.InIn, net.params_spearman.rhoInIn, net.p2p,
          net.vvweight, (net.weightFlag ? net.netWeightOut : net.linkSize),
          net.nodeDegIn, net.degArrNoIn, net.deg2ArrValIn, net.nodeDegIn,
          net.degArrNoIn, net.deg2ArrValIn, net.weightFlag);

      // InOut
      cal_neiAveDeg2_weight(net.neiAveDeg2InOut, net.nodeNeiAveDeg2Out,
                            net.nodeDegIn, net.degArrSizeIn, net.degArrNoIn,
                            net.degArrValIn, net.degArrWeightOut,
                            net.nodeWeightOut, net.weightFlag);
      cal_spearman_dir_weight(
          net.params_spearman.InOut, net.params_spearman.rhoInOut, net.p2p,
          net.vvweight, (net.weightFlag ? net.netWeightOut : net.linkSize),
          net.nodeDegIn, net.degArrNoIn, net.deg2ArrValIn, net.nodeDegOut,
          net.degArrNoOut, net.deg2ArrValOut, net.weightFlag);
    }
  }

  return 0;
}

int net_degArr_2_deg2ArrVal_weight(Network& net) {
  if (net.degArrVal.empty() || net.degArrVal.size() != net.degArrSize.size()) {
    ERROR();
    return -1;
  }

  // deg2ArrVal All
  if (net.deg2ArrVal.empty()) {
    if (!net.weightFlag) {
      if (0 != degArrVal_2_deg2ArrVal(net.deg2ArrVal, net.degArrSize,
                                      net.degArrVal, net.linkSize,
                                      net.dirFlag)) {
        ERROR();
        return -1;
      }

    } else {  // net.weightFlag
      if (0 != degArrWeight_2_deg2ArrVal(net.deg2ArrVal, net.degArrWeight,
                                         net.netWeight)) {
        ERROR();
        return -1;
      }
    }
  }

  if (net.dirFlag) {       // dirFlag
    if (net.weightFlag) {  // dirFlag weightFlag
      // Out
      if (net.deg2ArrValOut.empty() &&
          0 != degArrWeight_2_deg2ArrVal(net.deg2ArrValOut, net.degArrWeightOut,
                                         net.netWeightOut)) {
        ERROR();
        return -1;
      }

      // In
      if (net.deg2ArrValIn.empty() &&
          0 != degArrWeight_2_deg2ArrVal(net.deg2ArrValIn, net.degArrWeightIn,
                                         net.netWeightIn)) {
        ERROR();
        return -1;
      }

    } else {  // dirFlag !weightFlag
      // Out
      if (net.deg2ArrValOut.empty() &&
          0 != degArrVal_2_deg2ArrVal(net.deg2ArrValOut, net.degArrSizeOut,
                                      net.degArrValOut, net.linkSize,
                                      net.dirFlag)) {
        ERROR();
        return -1;
      }

      // In
      if (net.deg2ArrValIn.empty() &&
          0 != degArrVal_2_deg2ArrVal(net.deg2ArrValIn, net.degArrSizeIn,
                                      net.degArrValIn, net.linkSize,
                                      net.dirFlag)) {
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
      is >> net.params_spearman.spearman;
      cout << s << '\t' << net.params_spearman.spearman << endl;
      continue;
    }
    if (net.dirFlag) {
      if (s == "--params_spearman.InIn") {
        is >> net.params_spearman.InIn;
        cout << s << '\t' << net.params_spearman.InIn << endl;
        continue;
      }
      if (s == "--params_spearman.InOut") {
        is >> net.params_spearman.InOut;
        cout << s << '\t' << net.params_spearman.InOut << endl;
        continue;
      }
      if (s == "--params_spearman.OutIn") {
        is >> net.params_spearman.OutIn;
        cout << s << '\t' << net.params_spearman.OutIn << endl;
        continue;
      }
      if (s == "--params_spearman.OutOut") {
        is >> net.params_spearman.OutOut;
        cout << s << '\t' << net.params_spearman.OutOut << endl;
        continue;
      }
    }
#ifdef MODEL_GAUSS
    if (s == "--params_spearman.r0") {
      is >> net.params_spearman.r0;
      cout << s << '\t' << net.params_spearman.r0 << endl;
      continue;
    }
#endif
  }
  return 0;
}

int net_save_params_spearman(ostream& os, const Network& net) {
  if (!os) return -1;

#ifdef MODEL_GAUSS
  os << "--params_spearman.r0\t" << net.params_spearman.r0 << '\n';
#endif

  os << "--params_spearman.spearman\t" << net.params_spearman.spearman << '\n';
  if (net.dirFlag) {
    os << "--params_spearman.rho\t" << net.params_spearman.rho
       << "\n--params_spearman.OutIn\t" << net.params_spearman.OutIn
       << "\n--params_spearman.rhoOutIn\t" << net.params_spearman.rhoOutIn
       << '\n';
    if (STAT_TYPE_DIRAA) {
      os << "--params_spearman.OutOut\t" << net.params_spearman.OutOut
         << "\n--params_spearman.rhoOutOut\t" << net.params_spearman.rhoOutOut
         << "\n--params_spearman.InIn\t" << net.params_spearman.InIn
         << "\n--params_spearman.rhoInIn\t" << net.params_spearman.rhoInIn
         << "\n--params_spearman.InOut\t" << net.params_spearman.InOut
         << "\n--params_spearman.rhoInOut\t" << net.params_spearman.rhoInOut
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
    ss << net.seed;
    fn = net.saveName + '_' + ss.str();
  }
  int f = 0;
// if(!net.deg2ArrVal.empty()) f |= common_save1((fn +
// "_deg2ArrVal.txt").c_str(), net.deg2ArrVal, net.priChar);
// if(!net.nodeNeiAveDeg2.empty()) f |= common_save1((fn +
// "_nodeNeiAveDeg2.txt").c_str(), net.nodeNeiAveDeg2, net.priChar);
// if(!net.neiAveDeg2.empty()) f |= common_save1((fn +
// "_neiAveDeg2.txt").c_str(), net.neiAveDeg2, net.priChar);

// if(net.dirFlag){
// if(!net.deg2ArrValIn.empty()) f |= common_save1((fn +
// "_deg2ArrValIn.txt").c_str(), net.deg2ArrValIn, net.priChar);
// if(!net.deg2ArrValOut.empty()) f |= common_save1((fn +
// "_deg2ArrValOut.txt").c_str(), net.deg2ArrValOut, net.priChar);
// if(!net.nodeNeiAveDeg2In.empty()) f |= common_save1((fn +
// "_nodeNeiAveDeg2In.txt").c_str(), net.nodeNeiAveDeg2In, net.priChar);
// if(!net.nodeNeiAveDeg2Out.empty()) f |= common_save1((fn +
// "_nodeNeiAveDeg2Out.txt").c_str(), net.nodeNeiAveDeg2Out, net.priChar);
// if(!net.neiAveDeg2InIn.empty()) f |= common_save1((fn +
// "_neiAveDeg2InIn.txt").c_str(), net.neiAveDeg2InIn, net.priChar);
// if(!net.neiAveDeg2InOut.empty()) f |= common_save1((fn +
// "_neiAveDeg2InOut.txt").c_str(), net.neiAveDeg2InOut, net.priChar);
// if(!net.neiAveDeg2OutIn.empty()) f |= common_save1((fn +
// "_neiAveDeg2OutIn.txt").c_str(), net.neiAveDeg2OutIn, net.priChar);
// if(!net.neiAveDeg2OutOut.empty()) f |= common_save1((fn +
// "_neiAveDeg2OutOut.txt").c_str(), net.neiAveDeg2OutOut, net.priChar);
//}

#ifdef MODEL_GAUSS
// if(net.params_spearman.GaussS2.size() > 0) f |= common_save1((fn +
// "_SGaussS2.txt").c_str(), net.params_spearman.GaussS2, net.priChar);
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
    ss << net.seed;
    fn = net.saveName + '_' + ss.str();
  }

  int f = 0;
  f |= net_save_params_0(net, fn.c_str());
  if (net.status == 0) return 0;
  if (net.status != 1 && net.status != -2) return -1;
  if (net.status == -2)
    f |= common_save1((fn + "_p2pSize.txt").c_str(), net.p2pSize);
  if (net.nodeDeg.size() > 0)
    f |= common_save1((fn + "_nodeDeg.txt").c_str(), net.nodeDeg, net.priChar);
  if (net.degArrVal.size() > 0)
    f |= common_save1((fn + "_degArrVal.txt").c_str(), net.degArrVal,
                      net.priChar);
  if (net.degArrSize.size() > 0)
    f |= common_save1((fn + "_degArrSize.txt").c_str(), net.degArrSize,
                      net.priChar);
  if (net.p2p.size() > 0)
    f |= common_save2((fn + "_p2p.txt").c_str(), net.p2p, net.priChar);

  if (net.nodeNeiAveDeg.size() > 0)
    f |= common_save1((fn + "_nodeNeiAveDeg.txt").c_str(), net.nodeNeiAveDeg,
                      net.priChar);
  if (net.neiAveDeg.size() > 0)
    f |= common_save1((fn + "_neiAveDeg.txt").c_str(), net.neiAveDeg,
                      net.priChar);
  if (net.nodeNeiAveNo.size() > 0)
    f |= common_save1((fn + "_nodeNeiAveNo.txt").c_str(), net.nodeNeiAveNo,
                      net.priChar);
  if (net.neiAveNo.size() > 0)
    f |=
        common_save1((fn + "_neiAveNo.txt").c_str(), net.neiAveNo, net.priChar);

  if (net.deg2ArrVal.size() > 0)
    f |= common_save1((fn + "_deg2ArrVal.txt").c_str(), net.deg2ArrVal,
                      net.priChar);
  if (net.nodeNeiAveDeg2.size() > 0)
    f |= common_save1((fn + "_nodeNeiAveDeg2.txt").c_str(), net.nodeNeiAveDeg2,
                      net.priChar);
  if (net.neiAveDeg2.size() > 0)
    f |= common_save1((fn + "_neiAveDeg2.txt").c_str(), net.neiAveDeg2,
                      net.priChar);

  if (net.params_spearman.GaussS2.size() > 0)
    f |= common_save1((fn + "_SGaussS2.txt").c_str(),
                      net.params_spearman.GaussS2, net.priChar);
  if (net.lkkProb.size() > 0)
    f |= common_save2((fn + "_lkkProb.txt").c_str(), net.lkkProb, net.priChar);

  return f;
}

//**//****************************************************//*
int net_read_SGaussS2(Network& net, const char* name) {
  string fn;
  if (name != NULL)
    fn = name;
  else
    fn = net.readName;
  if (fn.size() <= 0) return -1;

  net.p2p.clear();
  if (0 != common_read1_0((fn + "_SGaussS2.txt").c_str(),
                          net.params_spearman.GaussS2)) {
    ERROR();
    return -1;
  }
  return 0;
}

//**//****************************************************//*
int net_cal_lkkProb_gauss(Network& net) {
  const NodeType degSize = net.degArrVal.size();
  if (net.argv.find("read_stat_spearman.GaussS2") != string::npos) {
    if (net_read_SGaussS2(net) != 0)
      return -1;
    else
      return 0;
  }

  net.params_spearman.GaussS2.resize(degSize);
  for (NodeType i = 0; i < degSize; i++) {
    cal_lkkProb_gaussS2(net.params_spearman.GaussS2[i], net.deg2ArrVal,
                        net.degArrVal, net.degArrSize, i,
                        net.params_spearman.r0);
  }
  net.lkkProb.resize(degSize, VDouble(degSize));
  cal_lkkProb_gauss(net.lkkProb, net.params_spearman.GaussS2, net.deg2ArrVal,
                    net.params_spearman.r0);
  return 0;
}

int net_gauss_new_ranLink(
    Network& net)  // 随机选点按度之差的相应高斯概率连边，重连时随机选点再选边
{
  // 初始化连边信息
  net.p2p.resize(net.nodeSize);
  net.remNodeNum.resize(net.nodeSize);
  net.link.resize(2 * net.linkSize);
  for (NodeType i = 0, *p = &net.link[0]; i < net.nodeSize; i++) {
    net.p2p[i].clear();
    net.p2p[i].reserve(net.nodeDeg[i]);
    net.remNodeNum[i] = i;
    for (NodeType j = 0; j < net.nodeDeg[i]; j++)
      *p++ = i;  // 记录各点剩余度和网络所有连边情况
  }
  if (net.deg2ArrVal.empty() &&
      0 != degArrVal_2_deg2ArrVal(net.deg2ArrVal, net.degArrSize, net.degArrVal,
                                  net.linkSize)) {
    ERROR();
    return -1;
  }
  if (net.degArrNo.empty() &&
      0 != degArrVal_2_degArrNo(net.degArrNo, net.degArrVal)) {
    ERROR();
    return -1;
  }
  net.linkRemain = net.linkSize;
  LinkType linkRemain0 = net.linkRemain;
  // 随机连边
  // 计算各度之差相应的高斯概率
  if (net_cal_lkkProb_gauss(net) != 0) {
    ERROR("net_cal_lkkProb_gauss");
    return net.status = -1;
  }
  std::cout << "\tcal_lkkProb_gauss end\n";
  NodeType remPoiSize = net.nodeSize;
  for (size_t count = 0, iDel = 1; net.linkRemain > 0 && remPoiSize > 0;) {
    // delLink_p2p_randLink(net.p2p, net.nodeDeg, net.p2pSize, net.remNodeNum,
    // net.linkRemain, net.linkSize, net.link, iDel); // 随机删iDel条边
    if (0 == addLink_p2p_ranLink_lkkProb(net.p2p, net.nodeDeg, net.lkkProb,
                                         net.degArrNo, remPoiSize,
                                         net.linkRemain, net.link, 100000))
      break;  // 随机抽取剩余度连边
    std::cout << "\tlinkRemain:\t" << net.linkRemain << '\n';
    if (net.linkRemain < linkRemain0) {
      count = 0;
      iDel = 1;
      linkRemain0 = net.linkRemain;
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
