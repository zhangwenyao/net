#include "network.h"
#ifdef STAT_KENDALL

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
network::kendall::Kendall::Kendall(void)
    : kendall(0)
    , OutIn(0)
{
}

ostream& operator<<(ostream& os, const network::kendall::Kendall& kendall)
{
  if (!os) {
    ERROR();
    return os;
  }
  os << "--kendall.kendall\t" << kendall.kendall << '\n';
  return os;
}

int network::kendall::Kendall::save_params(ostream& os) const
{
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int network::kendall::Kendall::save_params(const char* name) const
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

int network::kendall::Kendall::save_data(
    const char* name, const int dirFlag ,
        const char priChar, const char priChar2) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  return 0;
}

int network::kendall::Kendall::save(const char* name, const int dirFlag,
    const char priChar, const char priChar2) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + ".kendall.params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 != save_data((fn + ".kendall").c_str(), dirFlag, priChar, priChar2)) {
    ERROR();
    return -1;
  }
  return 0;
}

int network::kendall::Kendall::read_params_1(string& s, istream& is)
{
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = 1;
  do {
    if (s == "--kendall.kendall") {
      is >> kendall;
      cout << s << '\t' << kendall << endl;
      break;
    }
    flag = 0;
  } while (0);
  if (flag)
    s.clear();
  return 0;
}

network::kendall::Kendall& network::kendall::Kendall::clear(void)
{
  kendall = 0;
  return *this;
}

// ******************************************************
Networks& Networks::stat_kendall(void)
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
  // TODO
  // if (weightFlag)
  // runStatus = network::kendall::cal_kendall_directed_weight(
  // kendall.kendall, weightMatr, linkMatr);
  // else
  // runStatus = network::kendall::cal_kendall_directed_unweight(
  // kendall.kendall, linkMatr);
  if (0 != runStatus)
    ERROR();
  return *this;
}

// ******************************************************
int net_cal_kendall(Networks& net)
{
  if (net.lkkSum.empty()
      && 0 != lkk_2_lkkSum(net.lkkSum, net.lkk, net.dirFlag)) {
    ERROR();
    return -1;
  }
  network::kendall::cal_kendall_lkkSum(
      net.kendall.kendall, net.lkk, net.lkkSum, net.dirFlag);
  // network::kendall::cal_kendall_lkk(params_kendall.kendall, lkk,
  // linkSize, dirFlag);
  if (net.dirFlag) {
    if (net.lkkSumOutIn.empty()
        && 0 != lkk_2_lkkSum(net.lkkSumOutIn, net.lkkOutIn, net.dirFlag)) {
      ERROR();
      return -1;
    }
    network::kendall::cal_kendall_lkkSum(
        net.kendall.OutIn, net.lkkOutIn, net.lkkSumOutIn, net.dirFlag);
  }
  return 0;
}

// ******************************************************
#endif // STAT_KENDALL
