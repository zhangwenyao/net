#include "network.h"
#ifdef STAT_CORRELATION2

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
network::correlation2::Correlation2::Correlation2(void)
    : correlation2(0)
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
    os << "--correlation2.correlation2\t" << correlation2 << '\n';
  } else {
    os << "--correlation2.correlation2\t" << correlation2
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
    if (s == "--correlation2.correlation2") {
      is >> correlation2;
      cout << s << '\t' << correlation2 << endl;
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
  correlation2 = 0;
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

// ******************************************************
Networks& Networks::stat_correlation2(void)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  do {
    if (!dirFlag && !weightFlag && !p2p.empty()) {
      network::correlation2::cal_correlation2(correlation2.correlation2, p2p);
    } else {
      // TODO
      ERROR();
    }
  } while (0);

  return *this;
}

// ******************************************************
#endif // STAT_CORRELATION2
