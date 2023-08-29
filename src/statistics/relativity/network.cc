#include "network.h"
#ifdef STAT_RELATIVITY

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
network::relativity::Relativity::Relativity(void)
    : relativity(0)
    , alpha(0)
{
}

ostream& operator<<(
    ostream& os, const network::relativity::Relativity& relativity)
{
  if (!os || 0 != relativity.save_params(os))
    ERROR();
  return os;
}

int network::relativity::Relativity::save_params(
    ostream& os, const int dirFlag) const
{
  _ERR(!os);
  os << "--relativity.relativity\t" << relativity << "\n--relativity.alpha\t"
     << alpha << '\n';
  return 0;
}

int network::relativity::Relativity::save_params(
    const char* name, const int dirFlag) const
{
  _ERR(name == NULL || name[0] == '\0');
  ofstream os(name);
  _ERR(!os);
  save_params(os, dirFlag);
  os.close();
  return 0;
}

int network::relativity::Relativity::save_data(const char* name,
    const int dirFlag, const char priChar, const char priChar2) const
{
  return 0;
}

int network::relativity::Relativity::save(const char* name, const int dirFlag,
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

int network::relativity::Relativity::read_params_1(string& s, istream& is)
{
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = 1;
  do {
    if (s == "--relativity.relativity") {
      is >> relativity;
      cout << s << '\t' << relativity << endl;
      break;
    }
    if (s == "--relativity.alpha") {
      is >> alpha;
      cout << s << '\t' << alpha << endl;
      break;
    }
    flag = 0;
  } while (0);
  if (flag)
    s.clear();
  return 0;
}

network::relativity::Relativity& network::relativity::Relativity::clear(void)
{
  relativity = 0;
  alpha = 0;
  return *this;
}

// ******************************************************
Networks& Networks::stat_relativity(void)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  do {
    if (!dirFlag && !weightFlag) {
      if (!lkk.empty()) {
        network::relativity::cal_relativity_lkk(relativity.relativity, lkk,
            degArrVal, linkSize, relativity.alpha);
        break;
      }
      if (!lkk3.empty()) {
        network::relativity::cal_relativity_lkk3(relativity.relativity, lkk3,
            degArrVal, linkSize, relativity.alpha);
        break;
      }
      if (!p2p.empty()) {
        network::relativity::cal_relativity_p2p(
            relativity.relativity, p2p, linkSize, relativity.alpha);
        break;
      }
      if (!link.empty()) {
        network::relativity::cal_relativity_link(
            relativity.relativity, link, nodeDeg, relativity.alpha);
        break;
      }
      ERROR();
      return *this;
    } else {
      // TODO
      ERROR();
      return *this;
    }
  } while (0);

  return *this;
}

// ******************************************************
#endif // STAT_RELATIVITY
