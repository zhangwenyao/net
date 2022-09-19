#include "network.h"
#ifdef STAT_MODULARITY

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
network::modularity::Modularity::Modularity(void)
    : coef(0)
{
}

ostream& operator<<(
    ostream& os, const network::modularity::Modularity& modularity)
{
  if (!os) {
    ERROR();
    return os;
  }
  os << "--modularity.coef\t" << modularity.coef << "\n--modularity.Size\t"
     << modularity.Range.size() << '\n';
  return os;
}

int network::modularity::Modularity::save_params(ostream& os) const
{
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int network::modularity::Modularity::save_params(const char* name) const
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

int network::modularity::Modularity::save_data(const char* name,
    const int dirFlag, const char priChar, const char priChar2) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  int f = 0;
  if (!Range.empty())
    f |= save1((fn + ".Range.txt").c_str(), Range, '\n');
  if (!Val.empty())
    f |= save1((fn + ".Val.txt").c_str(), Val, priChar);
  if (!LKK.empty())
    f |= save2((fn + ".LKK.txt").c_str(), LKK, priChar2);
  if (!Stk.empty())
    f |= save_Stk((fn + ".Stk.txt").c_str(), priChar2);
  if (!NodeCoef.empty())
    f |= save1((fn + ".NodeCoef.txt").c_str(), NodeCoef, priChar);
  return f;
}

int network::modularity::Modularity::save_Stk(
    const char* name, const char priChar2) const
{
  return save_moduStk(Stk, Range, name, priChar2);
}

int network::modularity::Modularity::save(const char* name, const int dirFlag,
    const char priChar, const char priChar2) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + ".modularity.params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0
      != save_data(
             (fn + ".modularity").c_str(), dirFlag, priChar, priChar2)) {
    ERROR();
    return -1;
  }
  return 0;
}

int network::modularity::Modularity::read_params_1(string& s, istream& is)
{
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = 1;
  do {
    if (s == "--modularity.coef") {
      is >> coef;
      cout << s << '\t' << coef << endl;
      break;
    }
    flag = 0;
  } while (0);
  if (flag)
    s.clear();
  return 0;
}

network::modularity::Modularity& network::modularity::Modularity::clear(void)
{
  coef = 0;
  NodeCoef.clear();
  Val.clear();
  Stk.clear();
  Num.clear();
  Range.clear();
  // for (VVLinkTypeItr i = LKK.begin(); i != LKK.end(); i++) i->clear();
  LKK.clear();
  return *this;
}

// ******************************************************
Networks& Networks::stat_modularity(void)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  int f = 0;
  f = network::modularity::cal_modularity(modularity.Val, modularity.Stk,
      modularity.Num, modularity.Range, p2p, p2pIn, dirFlag);
  f |= network::modularity::moduStk_sort(
      modularity.Stk, modularity.Range, modularity.Num);
  f |= network::modularity::cal_moduLKK(
      modularity.LKK, modularity.Range.size(), modularity.Val, p2p, dirFlag);
  f |= network::modularity::cal_moduCoef(
      modularity.coef, modularity.LKK, dirFlag);
  f |= network::modularity::cal_moduNodeCoef(
      modularity.NodeCoef, modularity.Range.size(), modularity.Val, p2p);
  runStatus = f;
  if (0 != runStatus)
    ERROR();
  return *this;
}

Networks& Networks::cal_modularity(void)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  runStatus = network::modularity::cal_modularity(modularity.Val,
      modularity.Stk, modularity.Num, modularity.Range, p2p, p2pIn, dirFlag);
  if (0 != runStatus)
    ERROR();
  return *this;
}

// ******************************************************
#ifdef STAT_BETWEENNESS
#include "../betweenness/betweenness.h"
Networks& Networks::stat_modularity_newman(double& qMax, NodeType mSize)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (mSize <= 0)
    mSize = nodeSize;
  qMax = 0;
  if (mSize <= 1) {
    qMax = 1;
    ERROR();
    runStatus = -1;
    return *this;
  }
  if (link.empty())
    p2p_2_link(link, p2p, dirFlag);
  stat_modularity();
  if (0 != runStatus) {
    ERROR();
    return *this;
  }

  if (modularity.coef > qMax)
    qMax = modularity.coef;
  for (LinkType l = linkSize; l > 0 && modularity.Range.size() < mSize;) {
    stat_betweenness();
    sort_link_betwEdge(link, betweenness.betwEdge, l--); // 按介数排序边link
    del_pij(link[l * 2], link[l * 2 + 1], p2p, p2pIn,
        dirFlag); // 删除连边p2p中介数最大的边
    network::modularity::cal_modularity(modularity.Val, modularity.Stk,
        modularity.Num, modularity.Range, p2p, p2pIn, dirFlag);
    network::modularity::moduStk_sort(
        modularity.Stk, modularity.Range, modularity.Num);
    network::modularity::cal_moduLKK(modularity.LKK, modularity.Range.size(),
        modularity.Val, p2p,
        dirFlag); // 统计原网络在新分组下的不同组之间的连边数
    network::modularity::cal_moduCoef(
        modularity.coef, modularity.LKK, dirFlag); // 新分组系数
    if (modularity.coef > qMax)
      qMax = modularity.coef;
  }

  if (0 != runStatus)
    ERROR();
  return *this;
}
#endif

// ******************************************************
#endif // STAT_MODULARITY
