#include "sis.h"
#ifdef ACT_SIS

#include "../../common/common.h"
using namespace std;
using namespace common;
using namespace network;

// *******************************************************
int SIS_update(VNodeType& statusSN, VNodeType& SN, NodeType& N_i,
    LinkType& NDeg_i, const NodeType degMax, const VVNodeType& p2p,
    double& dt, const double lambda);
int SIS_update2(VVNodeType& statusSN, VVNodeType& SN, VNodeType& N_i,
    VLinkType& NDeg_i, VDouble& t, double& t2, const double p,
    const double lambda, const VVNodeType& p2p, const NodeType degMax);

// *******************************************************
int network::sis::act_SIS_init(VVNodeType& statusSN, VVNodeType& SN,
    VNodeType& N_i, VLinkType& NDeg_i, VDouble& t, const VVNodeType& p2p,
    const double p0, const unsigned M)
{
  t.assign(M + 1, 0);
  statusSN.resize(M + 1);
  SN.resize(M + 1);
  NodeType iN = 0, sN = 0;
  LinkType iD = 0;
  VNodeType &ssn = statusSN[M], &sn = SN[M];
  const NodeType nodeSize = p2p.size();
  ssn.resize(nodeSize);
  sn.resize(nodeSize);
  for (NodeType i = 0; i < nodeSize; ++i) {
    if (rand_double() < p0) {
      sn[i] = iN++;
      ssn[sn[i]] = i;
      iD += p2p[i].size();
    } else {
      sn[i] = nodeSize - ++sN;
      ssn[sn[i]] = i;
    }
  }
  for (unsigned i = 0; i < M; ++i) {
    statusSN[i] = statusSN[M];
    SN[i] = SN[M];
  }
  N_i.assign(M + 1, iN);
  NDeg_i.assign(M + 1, iD);
  return 0;
}

int SIS_update(VNodeType& statusSN, VNodeType& SN,
    NodeType& N_i, LinkType& NDeg_i, const NodeType degMax,
    const VVNodeType& p2p, double& dt, const double lambda)
{
  if (N_i <= 0 || NDeg_i <= 0) {
    dt = 0;
    return 0;
  }
  double all_i = N_i + lambda * NDeg_i;
  dt = 1. / all_i;
  if (rand_double() * all_i <= N_i) {
    // recover
    std::uniform_int_distribution<NodeType> dis(0, --N_i);
    NodeType ssn_i = dis(rand2), i = statusSN[ssn_i];
    if (ssn_i != N_i) {
      NodeType j = statusSN[N_i];
      statusSN[ssn_i] = j;
      SN[j] = ssn_i;
      statusSN[N_i] = i;
      SN[i] = N_i;
    }
    NDeg_i -= p2p[i].size();
  } else {
    // spread
    std::uniform_int_distribution<NodeType> dis(0, N_i - 1);
    for (NodeType i, j, k; 1;) {
      i = statusSN[dis(rand2)];
      std::uniform_int_distribution<NodeType> dis2(0, degMax - 1);
      if ((k = dis2(rand2)) < p2p[i].size()) {
        j = p2p[i][k];
        if (SN[j] >= N_i) {
          // infect
          NodeType ssn_j = SN[j], l = statusSN[N_i];
          if (ssn_j != N_i) {
            statusSN[N_i] = j;
            SN[j] = N_i;
            statusSN[ssn_j] = l;
            SN[l] = ssn_j;
          }
          N_i++;
          NDeg_i += p2p[j].size();
        }
        break;
      }
    }
  }
  return 0;
}

int SIS_update2(VVNodeType& statusSN, VVNodeType& SN,
    VNodeType& N_i, VLinkType& NDeg_i, VDouble& t, double& t2, const double p,
    const double lambda, const VVNodeType& p2p, const NodeType degMax)
{
  int flag = 0;
  const unsigned M = N_i.size() - 1;
  double dt = 0;
  SIS_update(statusSN[M], SN[M], N_i[M], NDeg_i[M], degMax, p2p, dt, lambda);
  t2 = t[M] + dt;
  std::uniform_int_distribution<NodeType> dis(0, M - 1);
  if (N_i[M] <= 0) { // all recovered
    NodeType i = dis(rand2);
    statusSN[M] = statusSN[i];
    SN[M] = SN[i];
    N_i[M] = N_i[i];
    NDeg_i[M] = NDeg_i[i];
    t[M] = t[i];
    flag = 1;
  } else {
    t[M] += dt;
    if (rand_double() < p * dt) { // renew status
      NodeType i = dis(rand2);
      statusSN[i] = statusSN[M];
      SN[i] = SN[M];
      N_i[i] = N_i[M];
      NDeg_i[i] = NDeg_i[M];
      t[i] = t[M];
    }
  }
  return flag;
}

int network::sis::act_sis(VVNodeType& statusSN, VVNodeType& SN,
    VNodeType& N_i, VLinkType& NDeg_i, VDouble& t, LinkType& nSum,
    LinkType& n2Sum, NodeType& nNum, const double p, const double lambda,
    const double tau, double t_av, const VVNodeType& p2p,
    const NodeType degMax)
{
  const unsigned M = N_i.size() - 1;
  for (double t2; t_av > 0;) {
    while (t[M] < tau)
      SIS_update2(statusSN, SN, N_i, NDeg_i, t, t2, p, lambda, p2p, degMax);
    double t0 = t[M];
    if (0
        == SIS_update2(
               statusSN, SN, N_i, NDeg_i, t, t2, p, lambda, p2p, degMax)) {
      t_av -= t[M] - t0;
      nNum++;
      nSum += N_i[M];
      n2Sum += (LinkType)N_i[M] * N_i[M];
    }
  }
  return 0;
}

int network::sis::act_SIS_tau(double& tau, VVNodeType& statusSN,
    VVNodeType& SN, VNodeType& N_i, VLinkType& NDeg_i, VDouble& t,
    LinkType& nSum, LinkType& n2Sum, NodeType& nNum, const double p,
    const double lambda, const VVNodeType& p2p, const NodeType degMax)
{
  const unsigned M = N_i.size() - 1;
  while (1) {
    if (0
            != SIS_update2(
                   statusSN, SN, N_i, NDeg_i, t, tau, p, lambda, p2p, degMax)
        || N_i[M] >= p2p.size() / 2)
      break;
    nNum++;
    nSum += N_i[M];
    n2Sum += (LinkType)N_i[M] * N_i[M];
  }
  return 0;
}

int network::sis::act_SIS_cal_params(double& ksi, double& lambda_c,
    const VVNodeType& p2p, const NodeType& nSum, const LinkType& n2Sum,
    const NodeType& nNum)
{
  ksi = ((double)n2Sum - ((double)nSum * nSum) / nNum) / nSum;
  LinkType kSum = 0, k2Sum = 0;
  for (NodeType i = 0; i < p2p.size(); ++i) {
    NodeType k = p2p[i].size();
    kSum += k;
    k2Sum += k * k;
  }
  lambda_c = (double)kSum / k2Sum;
  return 0;
}
// *******************************************************
#endif // ACT_SIS
