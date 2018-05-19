#include "StatBetweenness.h"
#ifdef STAT_BETWEENNESS

#include "common.h"
#include "networks.h"
using namespace std;

// ******************************************************
Stat_betweenness::Stat_betweenness(void)
    : meanNode(0)
    , meanEdge(0)
{
}

ostream& operator<<(ostream& os, const Stat_betweenness& betweenness)
{
  if (!os) {
    ERROR();
    return os;
  }
  os << "--betweenness.meanNode\t" << betweenness.meanNode
     << "\n--betweenness.meanEdge\t" << betweenness.meanEdge << '\n';
  return os;
}

int Stat_betweenness::save_params(ostream& os) const
{
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int Stat_betweenness::save_params(const char* name) const
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

int Stat_betweenness::save_data(
    const char* name, const char priChar, const char priChar2) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  int f = 0;
  if (!betwNode.empty())
    f |= common_save1((fn + ".betwNode.txt").c_str(), betwNode, priChar);
  if (!betwEdge.empty())
    f |= common_save2((fn + ".betwEdge.txt").c_str(), betwEdge, priChar2);
  if (!minDistMatr.empty())
    f |= common_save2(
        (fn + ".minDistMatr.txt").c_str(), minDistMatr, priChar2);
  if (!minDistMean.empty())
    f |= common_save1((fn + ".minDistMean.txt").c_str(), minDistMean, priChar);
  if (0 != f)
    ERROR();
  return f;
}

int Stat_betweenness::save(
    const char* name, const char priChar, const char priChar2) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + ".betweenness.params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 != save_data((fn + ".betweenness").c_str(), priChar, priChar2)) {
    ERROR();
    return -1;
  }
  return 0;
}

int Stat_betweenness::read_params_1(string& s, istream& is)
{
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = 1;
  do {
    if (s == "--betweenness.meanNode") {
      is >> meanNode;
      cout << s << '\t' << meanNode << endl;
      break;
    }
    if (s == "--betweenness.meanEdge") {
      is >> meanEdge;
      cout << s << '\t' << meanEdge << endl;
      break;
    }
    flag = 0;
  } while (0);
  if (flag)
    s.clear();
  return 0;
}

Stat_betweenness& Stat_betweenness::clear(void)
{
  meanNode = 0;
  meanEdge = 0;
  betwNode.clear();
  betwEdge.clear();
  minDistMatr.clear();
  minDistMean.clear();
  return *this;
}

// ******************************************************
Networks& Networks::stat_betweenness(void)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (p2p.empty()) {
    if (linkMatr.empty()) {
      ERROR();
      runStatus = -1;
      return *this;
    }
    linkMatr_2_p2p(p2p, linkMatr);
    if (dirFlag)
      p2p_2_p2pIn(p2pIn, p2p);
  }

  if (distFlag) {
    if (dirFlag)
      runStatus = cal_betweenness(betweenness.betwNode, betweenness.betwEdge,
          betweenness.meanNode, betweenness.meanEdge, betweenness.minDistMatr,
          betweenness.minDistMean, p2p, p2pIn, linkMatr);
    else
      runStatus = cal_betweenness(betweenness.betwNode, betweenness.betwEdge,
          betweenness.meanNode, betweenness.meanEdge, betweenness.minDistMatr,
          betweenness.minDistMean, p2p, p2p, linkMatr);
  } else {
    if (dirFlag)
      runStatus = cal_betweenness0(betweenness.betwNode, betweenness.betwEdge,
          betweenness.meanNode, betweenness.meanEdge, betweenness.minDistMatr,
          betweenness.minDistMean, p2p, p2pIn);
    else
      runStatus = cal_betweenness0(betweenness.betwNode, betweenness.betwEdge,
          betweenness.meanNode, betweenness.meanEdge, betweenness.minDistMatr,
          betweenness.minDistMean, p2p, p2p);
  }
  if (0 != runStatus)
    ERROR();
  return *this;
}

// ******************************************************
#endif // STAT_BETWEENNESS
