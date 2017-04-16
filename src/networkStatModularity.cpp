#include "net.h"
#ifdef STAT_MODULARITY

#include "common.h"
#include "StatModularity.h"
#include "networks.h"
using namespace std;
//**//****************************************************//*
Stat_cluster::Stat_cluster(void) : coef(0) {}

ostream& operator<<(ostream& os, const Stat_cluster& cluster) {
  if (!os) {
    ERROR();
    return os;
  }
  os << "--cluster.coef\t" << cluster.coef << '\n';
  return os;
}

int Stat_cluster::save_params(ostream& os) const {
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int Stat_cluster::save_params(const char* name) const {
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

int Stat_cluster::save_data(const char* name) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  return 0;
}

int Stat_cluster::save(const char* name) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + "_cluster_params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 != save_data((fn + "_cluster").c_str())) {
    ERROR();
    return -1;
  }
  return 0;
}

int Stat_cluster::read_params_1(string& s, istream& is) {
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = 1;
  do {
    if (s == "--cluster.coef") {
      is >> coef;
      cout << s << '\t' << coef << endl;
      break;
    }
    flag = 0;
  } while (0);
  if (flag) s.clear();
  return 0;
}

Stat_cluster& Stat_cluster::clear(void) {
  coef = 0;
  Node.clear();
  return *this;
}

//**//****************************************************//*
Networks& Networks::stat_cluster(void) {
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
  if (weightFlag)
    runStatus = cal_cluster_directed_weight(cluster.coef, cluster.Node,
                                            weightMatr, linkMatr);
  else
    runStatus =
        cal_cluster_directed_unweight(cluster.coef, cluster.Node, linkMatr);
  if (0 != runStatus) ERROR();
  return *this;
}

//**//****************************************************//*
int net_read_params_modularity(istream& is, Network& net) { return 0; }

int net_save_params_modularity(ostream& os, const Network& net) {
  if (!os) return -1;
  os << "--params_modularity.Coef\t" << params_modularity.Coef
     << "\n--params_modularity.Size\t" << params_modularity.Range.size()
     << '\n';
  return 0;
}

int net_save_modularity(const Network& net, const char* name) {
  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else {
    stringstream ss;
    ss << seed;
    fn = saveName + '_' + ss.str();
  }
  int f = 0;
  if (!params_modularity.Range.empty())
    f |= common_save1((fn + "_stat_modularity.Range.txt").c_str(),
                      params_modularity.Range, '\n');
  if (!params_modularity.Val.empty())
    f |= common_save1((fn + "_stat_modularity.Val.txt").c_str(),
                      params_modularity.Val, priChar);
  if (!params_modularity.LKK.empty())
    f |= common_save2((fn + "_stat_modularity.LKK.txt").c_str(),
                      params_modularity.LKK, priChar2);
  if (!params_modularity.Stk.empty())
    f |= net_save_stat_modularity.Stk(
        net, (fn + "_stat_modularity.Stk.txt").c_str(), priChar2);
  if (!params_modularity.NodeCoef.empty())
    f |= common_save1((fn + "_stat_modularity.NodeCoef.txt").c_str(),
                      params_modularity.NodeCoef, priChar);
  return f;
}
//**//****************************************************//*
int net_clear_modularity(Network& net) {
  params_modularity.NodeCoef.clear();
  params_modularity.Val.clear();
  params_modularity.Stk.clear();
  params_modularity.Num.clear();
  params_modularity.Range.clear();
  for (VVLinkTypeItr i = params_modularity.LKK.begin();
       i != params_modularity.LKK.end(); i++)
    i->clear();
  params_modularity.LKK.clear();
  return 0;
}

//**//****************************************************//*
int net_save_moduStk(const Network& net, ostream& os, const char c) {
  return save_moduStk(os, params_modularity.Stk,
                      params_modularity.Range, c);
}

int net_save_moduStk(const Network& net, const char* name, const char c) {
  return save_moduStk(params_modularity.Stk, params_modularity.Range,
                      name, c);
}

//**//****************************************************//*
int net_modularity(Network& net) {
  int f = 0;
  f = cal_modularity(params_modularity.Val, params_modularity.Stk,
                     params_modularity.Num, params_modularity.Range,
                     p2p, p2pIn, dirFlag);
  f |= moduStk_sort(params_modularity.Stk, params_modularity.Range,
                    params_modularity.Num);
  f |=
      cal_moduLKK(params_modularity.LKK, params_modularity.Range.size(),
                  params_modularity.Val, p2p, dirFlag);
  f |= cal_moduCoef(params_modularity.Coef, params_modularity.LKK,
                    dirFlag);
  f |= cal_moduNodeCoef(params_modularity.NodeCoef,
                        params_modularity.Range.size(),
                        params_modularity.Val, p2p);
  return f;
}

int net_cal_modularity(Network& net) {
  return cal_modularity(params_modularity.Val, params_modularity.Stk,
                        params_modularity.Num, params_modularity.Range,
                        p2p, p2pIn, dirFlag);
}

//**//****************************************************//*
#ifdef STAT_BETWEENNESS
#include "StatBetweenness.h"
#include "networkStatBetweenness.h"
int net_newman_modularity(double& qMax, Network& net, NodeType mSize) {
  if (mSize <= 0) mSize = nodeSize;
  qMax = 0;
  if (mSize <= 1) {
    qMax = 1;
    ERROR();
    return 0;
  }
  const VVNodeType p2p = p2p;
  if (link.empty()) p2p_2_link(link, p2p, dirFlag);
  net_modularity(net);
  if (params_modularity.Coef > qMax) qMax = params_modularity.Coef;
  for (LinkType l = linkSize;
       l > 0 && params_modularity.Range.size() < mSize;) {
    net_betweenness(net);
    sort_link_betwEdge(link, params_betweenness.betwEdge,
                       l--);  // 按介数排序边link
    del_pij(link[l * 2], link[l * 2 + 1], p2p, p2pIn,
            dirFlag);  // 删除连边p2p中介数最大的边
    cal_modularity(params_modularity.Val, params_modularity.Stk,
                   params_modularity.Num, params_modularity.Range,
                   p2p, p2pIn, dirFlag);
    moduStk_sort(params_modularity.Stk, params_modularity.Range,
                 params_modularity.Num);
    cal_moduLKK(params_modularity.LKK, params_modularity.Range.size(),
                params_modularity.Val, p2p,
                dirFlag);  // 统计原网络在新分组下的不同组之间的连边数
    cal_moduCoef(params_modularity.Coef, params_modularity.LKK,
                 dirFlag);  // 新分组系数
    if (params_modularity.Coef > qMax) qMax = params_modularity.Coef;
  }
  return 0;
}
#endif

//**//****************************************************//*
#endif  // STAT_MODULARITY
