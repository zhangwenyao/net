#include "network.h"
#ifdef STAT_SPEARMAN

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
network::spearman::Spearman::Spearman(void)
    : spearman(0)
    , InIn(0)
    , InOut(0)
    , OutIn(0)
    , OutOut(0)
    , rho(0)
    , rhoInIn(0)
    , rhoInOut(0)
    , rhoOutIn(0)
    , rhoOutOut(0)
    ,
#ifdef MODEL_GAUSS
    r0(0)
    ,
#endif // MODEL_GAUSS
    deg2WeightMean(0)
    , deg2WeightMeanOut(0)
    , deg2WeightMeanIn(0)
{
}

ostream& operator<<(ostream& os, const network::spearman::Spearman& spearman)
{
  if (!os || 0 != spearman.save_params(os))
    ERROR();
  return os;
}

int network::spearman::Spearman::save_params(
    ostream& os, const int dirFlag) const
{
  if (!os) {
    ERROR();
    return -1;
  }
#ifdef MODEL_GAUSS
  os << "--spearman.r0\t" << r0 << '\n';
#endif

  os << "--spearman.spearman\t" << spearman << '\n';
  if (dirFlag) {
    os << "--spearman.rho\t" << rho << "\n--spearman.OutIn\t" << OutIn
       << "\n--spearman.rhoOutIn\t" << rhoOutIn << '\n';
    if (STAT_TYPE_DIRAA) {
      os << "--spearman.OutOut\t" << OutOut << "\n--spearman.rhoOutOut\t"
         << rhoOutOut << "\n--spearman.InIn\t" << InIn
         << "\n--spearman.rhoInIn\t" << rhoInIn << "\n--spearman.InOut\t"
         << InOut << "\n--spearman.rhoInOut\t" << rhoInOut << '\n';
    }
  }
  return 0;
}

int network::spearman::Spearman::save_params(
    const char* name, const int dirFlag) const
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
  save_params(os, dirFlag);
  os.close();
  return 0;
}

int network::spearman::Spearman::save_data(const char* name,
    const int dirFlag, const char priChar, const char priChar2) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  int f = 0;

  // if(!deg2ArrVal.empty())
  // f |= save1((fn + "_deg2ArrVal.txt").c_str(), deg2ArrVal, priChar);
  // if(!nodeNeiAveDeg2.empty()) f |= save1((fn +
  // "_nodeNeiAveDeg2.txt").c_str(), nodeNeiAveDeg2, priChar);
  // if(!neiAveDeg2.empty()) f |= save1((fn +
  // "_neiAveDeg2.txt").c_str(), neiAveDeg2, priChar);

  // if(dirFlag){
  // if(!deg2ArrValIn.empty()) f |= save1((fn +
  // "_deg2ArrValIn.txt").c_str(), deg2ArrValIn, priChar);
  // if(!deg2ArrValOut.empty()) f |= save1((fn +
  // "_deg2ArrValOut.txt").c_str(), deg2ArrValOut, priChar);
  // if(!nodeNeiAveDeg2In.empty()) f |= save1((fn +
  // "_nodeNeiAveDeg2In.txt").c_str(), nodeNeiAveDeg2In, priChar);
  // if(!nodeNeiAveDeg2Out.empty()) f |= save1((fn +
  // "_nodeNeiAveDeg2Out.txt").c_str(), nodeNeiAveDeg2Out, priChar);
  // if(!neiAveDeg2InIn.empty()) f |= save1((fn +
  // "_neiAveDeg2InIn.txt").c_str(), neiAveDeg2InIn, priChar);
  // if(!neiAveDeg2InOut.empty()) f |= save1((fn +
  // "_neiAveDeg2InOut.txt").c_str(), neiAveDeg2InOut, priChar);
  // if(!neiAveDeg2OutIn.empty()) f |= save1((fn +
  // "_neiAveDeg2OutIn.txt").c_str(), neiAveDeg2OutIn, priChar);
  // if(!neiAveDeg2OutOut.empty()) f |= save1((fn +
  // "_neiAveDeg2OutOut.txt").c_str(), neiAveDeg2OutOut, priChar);
  //}

#ifdef MODEL_GAUSS
// if(GaussS2.size() > 0) f |= save1((fn +
// "_SGaussS2.txt").c_str(), GaussS2, priChar);
// if (lkkProb.size() > 0)
// f |= save2((fn + "_lkkProb.txt").c_str(), lkkProb, priChar);
#endif // MODEL_GAUSS

  return f;
}

int network::spearman::Spearman::save(const char* name, const int dirFlag,
    const char priChar, const char priChar2) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + ".params.txt").c_str(), dirFlag)) {
    ERROR();
    return -1;
  }
  if (0 != save_data(fn.c_str(), dirFlag, priChar, priChar2)) {
    ERROR();
    return -1;
  }
  return 0;
}

int network::spearman::Spearman::read_params_1(string& s, istream& is)
{
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = 1;
  do {
    if (s == "--spearman.spearman") {
      is >> spearman;
      cout << s << '\t' << spearman << endl;
      continue;
    }
    if (s == "--spearman.InIn") {
      is >> InIn;
      cout << s << '\t' << InIn << endl;
      continue;
    }
    if (s == "--spearman.InOut") {
      is >> InOut;
      cout << s << '\t' << InOut << endl;
      continue;
    }
    if (s == "--spearman.OutIn") {
      is >> OutIn;
      cout << s << '\t' << OutIn << endl;
      continue;
    }
    if (s == "--spearman.OutOut") {
      is >> OutOut;
      cout << s << '\t' << OutOut << endl;
      continue;
    }
#ifdef MODEL_GAUSS
    if (s == "--spearman.r0") {
      is >> r0;
      cout << s << '\t' << r0 << endl;
      continue;
    }
#endif
    flag = 0;
  } while (0);
  if (flag)
    s.clear();
  return 0;
}

network::spearman::Spearman& network::spearman::Spearman::clear(void)
{
  spearman = 0;
  InIn = 0;
  InOut = 0;
  OutIn = 0;
  OutOut = 0;
  rho = 0;
  rhoInIn = 0;
  rhoInOut = 0;
  rhoOutIn = 0;
  rhoOutOut = 0;
  deg2WeightMean = 0;
  deg2WeightMeanIn = 0;
  deg2WeightMeanOut = 0;

  deg2ArrVal.clear();
  deg2ArrValIn.clear();
  deg2ArrValOut.clear();
  nodeNeiAveDeg2.clear();
  nodeNeiAveDeg2In.clear();
  nodeNeiAveDeg2Out.clear();
  neiAveDeg2.clear();
  neiAveDeg2InOut.clear();
  neiAveDeg2InIn.clear();
  neiAveDeg2OutIn.clear();
  neiAveDeg2OutOut.clear();
#ifdef MODEL_GAUSS
  GaussS2.clear();
#endif
  return *this;
}

// ******************************************************
Networks& Networks::stat_spearman(void)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  do {
    if (!dirFlag) {
      if (!lkk.empty() && !weightFlag) {
        network::spearman::cal_spearman_lkk(
            spearman.spearman, lkk, spearman.deg2ArrVal, linkSize);
        break;
      }
      if (!lkk3.empty() && !weightFlag) {
        network::spearman::cal_spearman_lkk3(
            spearman.spearman, lkk3, spearman.deg2ArrVal, linkSize);
        break;
      }
      if (!p2p.empty()) {
        network::spearman::cal_nodeNeiAveDeg2_weight(spearman.nodeNeiAveDeg2,
            p2p, nodeDeg, spearman.deg2ArrVal, degArrNo, vvweight, nodeWeight,
            weightFlag);
        network::spearman::cal_neiAveDeg2_weight(spearman.neiAveDeg2,
            spearman.nodeNeiAveDeg2, nodeDeg, degArrSize, degArrNo, degArrVal,
            degArrWeight, nodeWeight, weightFlag);
        if (!weightFlag) {
          if (lkk.empty())
            network::spearman::cal_spearman(spearman.spearman, p2p,
                spearman.deg2ArrVal, degArrNo, linkSize);
        } else
          network::spearman::cal_spearman_dir_weight(spearman.spearman,
              spearman.rho, p2p, vvweight, netWeight, nodeDeg, degArrNo,
              spearman.deg2ArrVal, nodeDeg, degArrNo, spearman.deg2ArrVal,
              weightFlag);
      }

    } else { // dirFlag
      // AllAll
      network::spearman::cal_nodeNeiAveDeg2_AllAll(spearman.nodeNeiAveDeg2,
          p2p, nodeDeg, spearman.deg2ArrVal, degArrNo, vvweight, nodeWeight,
          weightFlag);
      network::spearman::cal_neiAveDeg2_weight(spearman.neiAveDeg2,
          spearman.nodeNeiAveDeg2, nodeDeg, degArrSize, degArrNo, degArrVal,
          degArrWeight, nodeWeight, weightFlag);
      network::spearman::cal_spearman_dir_weight(spearman.spearman,
          spearman.rho, p2p, vvweight, (weightFlag ? netWeightOut : linkSize),
          nodeDeg, degArrNo, spearman.deg2ArrVal, nodeDeg, degArrNo,
          spearman.deg2ArrVal, weightFlag);

      // OutIn
      network::spearman::cal_nodeNeiAveDeg2_weight(spearman.nodeNeiAveDeg2In,
          p2p, nodeDegIn, spearman.deg2ArrValIn, degArrNoIn, vvweight,
          nodeWeightOut, weightFlag);
      network::spearman::cal_neiAveDeg2_weight(spearman.neiAveDeg2OutIn,
          spearman.nodeNeiAveDeg2In, nodeDegOut, degArrSizeOut, degArrNoOut,
          degArrValOut, degArrWeightOut, nodeWeightOut, weightFlag);
      network::spearman::cal_spearman_dir_weight(spearman.OutIn,
          spearman.rhoOutIn, p2p, vvweight,
          (weightFlag ? netWeightOut : linkSize), nodeDegOut, degArrNoOut,
          spearman.deg2ArrValOut, nodeDegIn, degArrNoIn,
          spearman.deg2ArrValIn, weightFlag);

      if (STAT_TYPE_DIRAA) {
        // OutOut
        network::spearman::cal_nodeNeiAveDeg2_weight(
            spearman.nodeNeiAveDeg2Out, p2p, nodeDegOut,
            spearman.deg2ArrValOut, degArrNoOut, vvweight, nodeWeightOut,
            weightFlag);
        network::spearman::cal_neiAveDeg2_weight(spearman.neiAveDeg2OutOut,
            spearman.nodeNeiAveDeg2Out, nodeDegOut, degArrSizeOut,
            degArrNoOut, degArrValOut, degArrWeightOut, nodeWeightOut,
            weightFlag);
        network::spearman::cal_spearman_dir_weight(spearman.OutOut,
            spearman.rhoOutOut, p2p, vvweight,
            (weightFlag ? netWeightOut : linkSize), nodeDegOut, degArrNoOut,
            spearman.deg2ArrValOut, nodeDegOut, degArrNoOut,
            spearman.deg2ArrValOut, weightFlag);

        // InIn
        network::spearman::cal_neiAveDeg2_weight(spearman.neiAveDeg2InIn,
            spearman.nodeNeiAveDeg2In, nodeDegIn, degArrSizeIn, degArrNoIn,
            degArrValIn, degArrWeightOut, nodeWeightOut, weightFlag);
        network::spearman::cal_spearman_dir_weight(spearman.InIn,
            spearman.rhoInIn, p2p, vvweight,
            (weightFlag ? netWeightOut : linkSize), nodeDegIn, degArrNoIn,
            spearman.deg2ArrValIn, nodeDegIn, degArrNoIn,
            spearman.deg2ArrValIn, weightFlag);

        // InOut
        network::spearman::cal_neiAveDeg2_weight(spearman.neiAveDeg2InOut,
            spearman.nodeNeiAveDeg2Out, nodeDegIn, degArrSizeIn, degArrNoIn,
            degArrValIn, degArrWeightOut, nodeWeightOut, weightFlag);
        network::spearman::cal_spearman_dir_weight(spearman.InOut,
            spearman.rhoInOut, p2p, vvweight,
            (weightFlag ? netWeightOut : linkSize), nodeDegIn, degArrNoIn,
            spearman.deg2ArrValIn, nodeDegOut, degArrNoOut,
            spearman.deg2ArrValOut, weightFlag);
      }
    }
  } while (0);

  return *this;
}

Networks& Networks::spearman_degArr_2_deg2ArrVal_weight(void)
{
  if (degArrVal.empty() || degArrVal.size() != degArrSize.size()) {
    ERROR();
    runStatus = -1;
    return *this;
  }

  // deg2ArrVal All
  if (spearman.deg2ArrVal.empty()) {
    if (!weightFlag) {
      if (0
          != degArrVal_2_deg2ArrVal(spearman.deg2ArrVal, degArrSize,
                 degArrVal, linkSize, dirFlag)) {
        ERROR();
        runStatus = -1;
        return *this;
      }

    } else { // weightFlag
      if (0
          != degArrWeight_2_deg2ArrVal(
                 spearman.deg2ArrVal, degArrWeight, netWeight)) {
        ERROR();
        runStatus = -1;
        return *this;
      }
    }
  }

  if (dirFlag) {      // dirFlag
    if (weightFlag) { // dirFlag weightFlag
      // Out
      if (spearman.deg2ArrValOut.empty()
          && 0
              != degArrWeight_2_deg2ArrVal(
                     spearman.deg2ArrValOut, degArrWeightOut, netWeightOut)) {
        ERROR();
        runStatus = -1;
        return *this;
      }

      // In
      if (spearman.deg2ArrValIn.empty()
          && 0
              != degArrWeight_2_deg2ArrVal(
                     spearman.deg2ArrValIn, degArrWeightIn, netWeightIn)) {
        ERROR();
        runStatus = -1;
        return *this;
      }

    } else { // dirFlag !weightFlag
      // Out
      if (spearman.deg2ArrValOut.empty()
          && 0
              != degArrVal_2_deg2ArrVal(spearman.deg2ArrValOut, degArrSizeOut,
                     degArrValOut, linkSize, dirFlag)) {
        ERROR();
        runStatus = -1;
        return *this;
      }

      // In
      if (spearman.deg2ArrValIn.empty()
          && 0
              != degArrVal_2_deg2ArrVal(spearman.deg2ArrValIn, degArrSizeIn,
                     degArrValIn, linkSize, dirFlag)) {
        ERROR();
        runStatus = -1;
        return *this;
      }
    }
  }

  return *this;
}

// ******************************************************
#ifdef MODEL_GAUSS
Networks& Networks::spearman_read_GaussS2(const char* name)
{
  string fn;
  if (name != NULL)
    fn = name;
  else
    fn = readName;
  if (fn.size() <= 0) {
    ERROR();
    runStatus = -1;
    return *this;
  }
  if (0 != read1_0((fn + "_GaussS2.txt").c_str(), spearman.GaussS2)) {
    ERROR();
    runStatus = -1;
    return *this;
  }
  return *this;
}

// ******************************************************
Networks& Networks::spearman_cal_lkkProb_gauss(void)
{
  const NodeType degSize = degArrVal.size();
  if (argv.find("read_spearman.GaussS2") != string::npos) {
    spearman_read_GaussS2();
    return *this;
  }

  spearman.GaussS2.resize(degSize);
  for (NodeType i = 0; i < degSize; i++) {
    network::spearman::cal_lkkProb_gaussS2(spearman.GaussS2[i],
        spearman.deg2ArrVal, degArrVal, degArrSize, i, spearman.r0);
  }
  lkkProb.resize(degSize, VDouble(degSize));
  network::spearman::cal_lkkProb_gauss(
      lkkProb, spearman.GaussS2, spearman.deg2ArrVal, spearman.r0);
  return *this;
}

Networks& Networks::spearman_gauss_new_ranLink(
    void) // 随机选点按度之差的相应高斯概率连边，重连时随机选点再选边
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
      *p++ = i; // 记录各点剩余度和网络所有连边情况
  }
  if (spearman.deg2ArrVal.empty()
      && 0
          != degArrVal_2_deg2ArrVal(
                 spearman.deg2ArrVal, degArrSize, degArrVal, linkSize)) {
    ERROR();
    return *this;
  }
  if (degArrNo.empty() && 0 != degArrVal_2_degArrNo(degArrNo, degArrVal)) {
    ERROR();
    runStatus = -1;
    return *this;
  }
  linkRemain = linkSize;
  LinkType linkRemain0 = linkRemain;
  // 随机连边
  // 计算各度之差相应的高斯概率
  if (spearman_cal_lkkProb_gauss().runStatus != 0) {
    ERROR();
    return *this;
  }
  std::cout << "\tcal_lkkProb_gauss end\n";
  NodeType remPoiSize = nodeSize;
  for (size_t count = 0, iDel = 1; linkRemain > 0 && remPoiSize > 0;) {
    // delLink_p2p_randLink(p2p, nodeDeg, p2pSize, remNodeNum,
    // linkRemain, linkSize, link, iDel); // 随机删iDel条边
    if (0
        == addLink_p2p_ranLink_lkkProb(p2p, nodeDeg, lkkProb, degArrNo,
               remPoiSize, linkRemain, link, 100000))
      break; // 随机抽取剩余度连边
    std::cout << "\tlinkRemain:\t" << linkRemain << '\n';
    if (linkRemain < linkRemain0) {
      count = 0;
      iDel = 1;
      linkRemain0 = linkRemain;
    } else if (++count >= 1000) {
      count = 0;
      if (++iDel > 5)
        break;
    }
  }
  std::cout << "\tadd_link end\n";

  return *this;
}

// ******************************************************
#endif // MODEL_GAUSS

// ******************************************************
#endif // STAT_SPEARMAN
