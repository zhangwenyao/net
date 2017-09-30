#include "networkStatPearson.h"
#ifdef STAT_PEARSON

#include "common.h"
#include "networks.h"
using namespace std;

//**//****************************************************//*
Stat_pearson::Stat_pearson(void)
    : pearson(0)
    , No(0)
    , NoInIn(0)
    , NoInOut(0)
    , NoOutIn(0)
    , NoOutOut(0)
    , rho(0)
    , rhoInIn(0)
    , rhoInOut(0)
    , rhoOutIn(0)
    , rhoOutOut(0)
{
}

ostream& operator<<(ostream& os, const Stat_pearson& pearson)
{
  if (!os || 0 != pearson.save_params(os))
    ERROR();
  return os;
}

int Stat_pearson::save_params(ostream& os, const int dirFlag) const
{
  if (!os) {
    ERROR();
    return -1;
  }
  if (!dirFlag) {
    os << "--pearson.pearson\t" << pearson << '\n';
  } else {
    os << "--pearson.pearson\t" << pearson << "\n--pearson.rho\t" << rho
       << "\n--pearson.OutIn\t" << OutIn << "\n--pearson.rhoOutIn\t"
       << rhoOutIn << '\n';
    if (STAT_TYPE_DIRAA) {
      os << "--pearson.OutOut\t" << OutOut << "\n--pearson.rhoOutOut\t"
         << rhoOutOut << "\n--pearson.InIn\t" << InIn
         << "\n--pearson.rhoInIn\t" << rhoInIn << "\n--pearson.InOut\t"
         << InOut << "\n--pearson.rhoInOut\t" << rhoInOut << '\n';
    }
  }
  return 0;
}

int Stat_pearson::save_params(const char* name, const int dirFlag) const
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

int Stat_pearson::save_data(const char* name, const int dirFlag,
    const char priChar, const char priChar2) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  int f = 0;
  if (!nodeNeiAveDeg.empty())
    f |= common_save1(
        (fn + ".nodeNeiAveDeg.txt").c_str(), nodeNeiAveDeg, priChar);
  if (!neiAveDeg.empty())
    f |= common_save1((fn + ".neiAveDeg.txt").c_str(), neiAveDeg, priChar);

  if (dirFlag) {
    if (!nodeNeiAveDegIn.empty())
      f |= common_save1(
          (fn + ".nodeNeiAveDegIn.txt").c_str(), nodeNeiAveDegIn, priChar);
    if (!nodeNeiAveDegOut.empty())
      f |= common_save1(
          (fn + ".nodeNeiAveDegOut.txt").c_str(), nodeNeiAveDegOut, priChar);
    if (!neiAveDegInIn.empty())
      f |= common_save1(
          (fn + ".neiAveDegInIn.txt").c_str(), neiAveDegInIn, priChar);
    if (!neiAveDegInOut.empty())
      f |= common_save1(
          (fn + ".neiAveDegInOut.txt").c_str(), neiAveDegInOut, priChar);
    if (!neiAveDegOutIn.empty())
      f |= common_save1(
          (fn + ".neiAveDegOutIn.txt").c_str(), neiAveDegOutIn, priChar);
    if (!neiAveDegOutOut.empty())
      f |= common_save1(
          (fn + ".neiAveDegOutOut.txt").c_str(), neiAveDegOutOut, priChar);
  }
  return f;
}

int Stat_pearson::save(const char* name, const int dirFlag, const char priChar,
    const char priChar2) const
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

int Stat_pearson::read_params_1(string& s, istream& is)
{
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = 1;
  do {
    if (s == "--pearson.pearson") {
      is >> pearson;
      cout << s << '\t' << pearson << endl;
      break;
    }
    if (s == "--pearson.InIn") {
      is >> InIn;
      cout << s << '\t' << InIn << endl;
      break;
    }
    if (s == "--pearson.InOut") {
      is >> InOut;
      cout << s << '\t' << InOut << endl;
      break;
    }
    if (s == "--pearson.OutIn") {
      is >> OutIn;
      cout << s << '\t' << OutIn << endl;
      break;
    }
    if (s == "--pearson.OutOut") {
      is >> OutOut;
      cout << s << '\t' << OutOut << endl;
      break;
    }
    flag = 0;
  } while (0);
  if (flag)
    s.clear();
  return 0;
}

Stat_pearson& Stat_pearson::clear(void)
{
  pearson = 0;
  InIn = 0;
  InOut = 0;
  OutIn = 0;
  OutOut = 0;
  No = 0;
  NoInIn = 0;
  NoInOut = 0;
  NoOutIn = 0;
  NoOutOut = 0;
  rho = 0;
  rhoInIn = 0;
  rhoInOut = 0;
  rhoOutIn = 0;
  rhoOutOut = 0;

  nodeNeiAveDeg.clear();
  nodeNeiAveDegIn.clear();
  nodeNeiAveDegOut.clear();
  neiAveDeg.clear();
  neiAveDegInIn.clear();
  neiAveDegInOut.clear();
  neiAveDegOutIn.clear();
  neiAveDegOutOut.clear();
  nodeNeiAveNo.clear();
  nodeNeiAveNoInIn.clear();
  nodeNeiAveNoInOut.clear();
  nodeNeiAveNoOutIn.clear();
  nodeNeiAveNoOutOut.clear();
  neiAveNo.clear();
  neiAveNoInIn.clear();
  neiAveNoInOut.clear();
  neiAveNoOutIn.clear();
  neiAveNoOutOut.clear();

  return *this;
}

//**//****************************************************//*
Networks& Networks::stat_pearson(void)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  do {
    if (!dirFlag) {
      if (!lkk.empty() && !weightFlag) {
        cal_pearson_lkk(pearson.pearson, lkk, degArrVal, linkSize);
        break;
      }
      if (!p2p.empty()) {
        cal_nodeNeiAveDeg_weight(pearson.nodeNeiAveDeg, p2p, nodeDeg, vvweight,
            nodeWeight, weightFlag);
        cal_neiAveDeg_weight(pearson.neiAveDeg, pearson.nodeNeiAveDeg, nodeDeg,
            degArrSize, degArrNo, degArrVal, degArrWeight, nodeWeight,
            weightFlag);
        if (!weightFlag) {
          if (lkk.empty())
            cal_pearson(pearson.pearson, p2p, linkSize);
        } else
          cal_pearson_dir_weight(pearson.pearson, pearson.rho, p2p, vvweight,
              netWeight, nodeDeg, nodeDeg, weightFlag);
      }

    } else {
      // AllAll
      cal_nodeNeiAveDeg_AllAll_weight(pearson.nodeNeiAveDeg, p2p, nodeDeg,
          vvweight, nodeWeight, weightFlag);
      cal_neiAveDeg_weight(pearson.neiAveDeg, pearson.nodeNeiAveDeg, nodeDeg,
          degArrSize, degArrNo, degArrVal, degArrWeight, nodeWeight,
          weightFlag);
      cal_pearson_dir_weight(pearson.pearson, pearson.rho, p2p, vvweight,
          (weightFlag ? netWeightOut : linkSize), nodeDeg, nodeDeg,
          weightFlag);

      // OutIn
      cal_nodeNeiAveDeg_weight(pearson.nodeNeiAveDegIn, p2p, nodeDegIn,
          vvweight, nodeWeightOut, weightFlag);
      cal_neiAveDeg_weight(pearson.neiAveDegOutIn, pearson.nodeNeiAveDegIn,
          nodeDegOut, degArrSizeOut, degArrNoOut, degArrValOut,
          degArrWeightOut, nodeWeightOut, weightFlag);
      cal_pearson_dir_weight(pearson.OutIn, pearson.rhoOutIn, p2p, vvweight,
          (weightFlag ? netWeightOut : linkSize), nodeDegOut, nodeDegIn,
          weightFlag);

      if (STAT_TYPE_DIRAA) {
        // OutOut
        cal_nodeNeiAveDeg_weight(pearson.nodeNeiAveDegOut, p2p, nodeDegOut,
            vvweight, nodeWeightOut, weightFlag);
        cal_neiAveDeg_weight(pearson.neiAveDegOutOut, pearson.nodeNeiAveDegOut,
            nodeDegOut, degArrSizeOut, degArrNoOut, degArrValOut,
            degArrWeightOut, nodeWeightOut, weightFlag);
        cal_pearson_dir_weight(pearson.OutOut, pearson.rhoOutOut, p2p,
            vvweight, (weightFlag ? netWeightOut : linkSize), nodeDegOut,
            nodeDegOut, weightFlag);

        // InIn
        cal_neiAveDeg_weight(pearson.neiAveDegInIn, pearson.nodeNeiAveDegIn,
            nodeDegIn, degArrSizeIn, degArrNoIn, degArrValIn, degArrWeightOut,
            nodeWeightOut, weightFlag);
        cal_pearson_dir_weight(pearson.InIn, pearson.rhoInIn, p2p, vvweight,
            (weightFlag ? netWeightOut : linkSize), nodeDegIn, nodeDegIn,
            weightFlag);

        // InOut
        cal_neiAveDeg_weight(pearson.neiAveDegInOut, pearson.nodeNeiAveDegOut,
            nodeDegIn, degArrSizeIn, degArrNoIn, degArrValIn, degArrWeightOut,
            nodeWeightOut, weightFlag);
        cal_pearson_dir_weight(pearson.InOut, pearson.rhoInOut, p2p, vvweight,
            (weightFlag ? netWeightOut : linkSize), nodeDegIn, nodeDegOut,
            weightFlag);
      }
    }
  } while (0);

  return *this;
}

//**//****************************************************//*
#endif // STAT_PEARSON
