#include "network.h"
#ifdef STAT_CORRELATION2

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
network::correlation2::Correlation2::Correlation2(void)
    : node(0)
    , link(0)
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

ostream& operator<<(
    ostream& os, const network::correlation2::Correlation2& correlation2)
{
  if (!os || 0 != correlation2.save_params(os))
    ERROR();
  return os;
}

int network::correlation2::Correlation2::save_params(
    ostream& os, const int dirFlag) const
{
  if (!os) {
    ERROR();
    return -1;
  }
  if (!dirFlag) {
    os << "--correlation2.node\t" << node << "\n--correlation2.link\t" << link
       << '\n';
  } else {
    os << "--correlation2.node\t" << node << "\n--correlation2.link\t" << link
       << "\n--correlation2.rho\t" << rho << "\n--correlation2.OutIn\t"
       << OutIn << "\n--correlation2.rhoOutIn\t" << rhoOutIn << '\n';
    if (STAT_TYPE_DIRAA) {
      os << "--correlation2.OutOut\t" << OutOut
         << "\n--correlation2.rhoOutOut\t" << rhoOutOut
         << "\n--correlation2.InIn\t" << InIn << "\n--correlation2.rhoInIn\t"
         << rhoInIn << "\n--correlation2.InOut\t" << InOut
         << "\n--correlation2.rhoInOut\t" << rhoInOut << '\n';
    }
  }
  return 0;
}

int network::correlation2::Correlation2::save_params(
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

int network::correlation2::Correlation2::save_data(const char* name,
    const int dirFlag, const char priChar, const char priChar2) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  int f = 0;
  if (!node_correlation2.empty())
    f |= save1(
        (fn + ".node_correlation2.txt").c_str(), node_correlation2, priChar);
  if (!node_correlation2_size.empty())
    f |= save1((fn + ".node_correlation2_size.txt").c_str(),
        node_correlation2_size, priChar);
  if (!nodeNeiAveDeg.empty())
    f |= save1((fn + ".nodeNeiAveDeg.txt").c_str(), nodeNeiAveDeg, priChar);
  if (!neiAveDeg.empty())
    f |= save1((fn + ".neiAveDeg.txt").c_str(), neiAveDeg, priChar);

  if (dirFlag) {
    if (!nodeNeiAveDegIn.empty())
      f |= save1(
          (fn + ".nodeNeiAveDegIn.txt").c_str(), nodeNeiAveDegIn, priChar);
    if (!nodeNeiAveDegOut.empty())
      f |= save1(
          (fn + ".nodeNeiAveDegOut.txt").c_str(), nodeNeiAveDegOut, priChar);
    if (!neiAveDegInIn.empty())
      f |= save1((fn + ".neiAveDegInIn.txt").c_str(), neiAveDegInIn, priChar);
    if (!neiAveDegInOut.empty())
      f |= save1(
          (fn + ".neiAveDegInOut.txt").c_str(), neiAveDegInOut, priChar);
    if (!neiAveDegOutIn.empty())
      f |= save1(
          (fn + ".neiAveDegOutIn.txt").c_str(), neiAveDegOutIn, priChar);
    if (!neiAveDegOutOut.empty())
      f |= save1(
          (fn + ".neiAveDegOutOut.txt").c_str(), neiAveDegOutOut, priChar);
  }
  return f;
}

int network::correlation2::Correlation2::save(const char* name,
    const int dirFlag, const char priChar, const char priChar2) const
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

int network::correlation2::Correlation2::read_params_1(string& s, istream& is)
{
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = 1;
  do {
    if (s == "--correlation2.node") {
      is >> node;
      cout << s << '\t' << node << endl;
      break;
    }
    if (s == "--correlation2.link") {
      is >> link;
      cout << s << '\t' << link << endl;
      break;
    }
    if (s == "--correlation2.InIn") {
      is >> InIn;
      cout << s << '\t' << InIn << endl;
      break;
    }
    if (s == "--correlation2.InOut") {
      is >> InOut;
      cout << s << '\t' << InOut << endl;
      break;
    }
    if (s == "--correlation2.OutIn") {
      is >> OutIn;
      cout << s << '\t' << OutIn << endl;
      break;
    }
    if (s == "--correlation2.OutOut") {
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

network::correlation2::Correlation2&
network::correlation2::Correlation2::clear(void)
{
  node = 0;
  link = 0;
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

  node_correlation2.clear();
  node_correlation2_size.clear();
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

// ******************************************************
Networks& Networks::stat_correlation2(void)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  do {
    if (!dirFlag && !weightFlag && !p2p.empty()) {
      network::correlation2::cal_correlation2_node(correlation2.node, p2p);
      network::correlation2::cal_correlation2_node_spearman(
          correlation2.node, p2p, degArrVal, spearman.deg2ArrVal);
      // network::correlation2::cal_correlation2_link(correlation2.link, p2p);
      // network::correlation2::cal_correlation2_link_spearman(correlation2.link,
      // p2p,degArrVal,spearman.deg2ArrVal);
      network::correlation2::cal_correlation2_node_k(
          correlation2.node_correlation2, correlation2.node_correlation2_size,
          p2p, degArrVal);
    } else {
      // TODO
      ERROR();
    }
  } while (0);

  return *this;
}

// ******************************************************
#endif // STAT_CORRELATION2
