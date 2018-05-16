#include "StatModularity.h"
#ifdef STAT_MODULARITY

#include "common.h"
#include "networks.h"
using namespace std;

//**//****************************************************//*
Stat_modularity::Stat_modularity(void) : coef(0) {}

ostream& operator<<(ostream& os, const Stat_modularity& modularity) {
  if (!os) {
    ERROR();
    return os;
  }
  os << "--modularity.coef\t" << modularity.coef << "\n--modularity.Size\t"
     << modularity.Range.size() << '\n';
  return os;
}

int Stat_modularity::save_params(ostream& os) const {
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int Stat_modularity::save_params(const char* name) const {
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

int Stat_modularity::save_data(const char* name, const char priChar,
                               const char priChar2) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  int f = 0;
  if (!Range.empty())
    f |= common_save1((fn + ".Range.txt").c_str(), Range, '\n');
  if (!Val.empty()) f |= common_save1((fn + ".Val.txt").c_str(), Val, priChar);
  if (!LKK.empty()) f |= common_save2((fn + ".LKK.txt").c_str(), LKK, priChar2);
  if (!Stk.empty()) f |= save_Stk((fn + ".Stk.txt").c_str(), priChar2);
  if (!NodeCoef.empty())
    f |= common_save1((fn + ".NodeCoef.txt").c_str(), NodeCoef, priChar);
  return f;
}

int Stat_modularity::save_Stk(const char* name, const char priChar2) const {
  return save_moduStk(Stk, Range, name, priChar2);
}

int Stat_modularity::save(const char* name, const char priChar,
                          const char priChar2) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + ".modularity.params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 != save_data((fn + ".modularity").c_str(), priChar, priChar2)) {
    ERROR();
    return -1;
  }
  return 0;
}

int Stat_modularity::read_params_1(string& s, istream& is) {
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
  if (flag) s.clear();
  return 0;
}

Stat_modularity& Stat_modularity::clear(void) {
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

//**//****************************************************//*
Networks& Networks::stat_modularity(void) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  int f = 0;
  f = ::cal_modularity(modularity.Val, modularity.Stk, modularity.Num,
                       modularity.Range, p2p, p2pIn, dirFlag);
  f |= moduStk_sort(modularity.Stk, modularity.Range, modularity.Num);
  f |= cal_moduLKK(modularity.LKK, modularity.Range.size(), modularity.Val, p2p,
                   dirFlag);
  f |= cal_moduCoef(modularity.coef, modularity.LKK, dirFlag);
  f |= cal_moduNodeCoef(modularity.NodeCoef, modularity.Range.size(),
                        modularity.Val, p2p);
  runStatus = f;
  if (0 != runStatus) ERROR();
  return *this;
}

Networks& Networks::cal_modularity(void) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  runStatus = ::cal_modularity(modularity.Val, modularity.Stk, modularity.Num,
                               modularity.Range, p2p, p2pIn, dirFlag);
  if (0 != runStatus) ERROR();
  return *this;
}

//**//****************************************************//*
#ifdef STAT_BETWEENNESS
#include "StatBetweenness.h"
Networks& Networks::stat_modularity_newman(double& qMax, NodeType mSize) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (mSize <= 0) mSize = nodeSize;
  qMax = 0;
  if (mSize <= 1) {
    qMax = 1;
    ERROR();
    runStatus = -1;
    return *this;
  }
  if (link.empty()) p2p_2_link(link, p2p, dirFlag);
  stat_modularity();
  if (0 != runStatus) {
    ERROR();
    return *this;
  }

  if (modularity.coef > qMax) qMax = modularity.coef;
  for (LinkType l = linkSize; l > 0 && modularity.Range.size() < mSize;) {
    stat_betweenness();
    sort_link_betwEdge(link, betweenness.betwEdge, l--);  // 按介数排序边link
    del_pij(link[l * 2], link[l * 2 + 1], p2p, p2pIn,
            dirFlag);  // 删除连边p2p中介数最大的边
    ::cal_modularity(modularity.Val, modularity.Stk, modularity.Num,
                     modularity.Range, p2p, p2pIn, dirFlag);
    moduStk_sort(modularity.Stk, modularity.Range, modularity.Num);
    cal_moduLKK(modularity.LKK, modularity.Range.size(), modularity.Val, p2p,
                dirFlag);  // 统计原网络在新分组下的不同组之间的连边数
    cal_moduCoef(modularity.coef, modularity.LKK, dirFlag);  // 新分组系数
    if (modularity.coef > qMax) qMax = modularity.coef;
  }

  if (0 != runStatus) ERROR();
  return *this;
}
#endif

//**//****************************************************//*
#endif  // STAT_MODULARITY
