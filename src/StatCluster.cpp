#include "StatCluster.h"
#ifdef STAT_CLUSTER

#include "common.h"
using namespace std;

//**//****************************************************//*
int cal_cluster_directed_weight(double &cluster_c, VDouble &cluster,
                                VVWeightType &weightMatr,
                                const VVDistType &linkMatr) {
  const NodeType nodeSize = linkMatr.size();
  VVNodeType p2p(nodeSize);
  VNodeType K(nodeSize, 0);   // nodeDeg = Out + In
  VNodeType A2(nodeSize, 0);  // A^2
  VVDouble S(nodeSize);       // S = W^1/3 + W'^1/3
  for (NodeType j = 1; j < nodeSize; j++) {
    S[j].assign(j, 0);
    for (NodeType i = 0; i < j; i++) {
      if (linkMatr[i][j] != 0 || linkMatr[j][i] != 0) p2p[i].push_back(j);
      if (linkMatr[i][j] != 0 && linkMatr[j][i] != 0) {
        A2[i]++;
        A2[j]++;
      }
      if (linkMatr[i][j] != 0) {
        S[j][i] = pow((double)weightMatr[i][j], 1 / 3.);
        K[i]++;
        K[j]++;
      }
      if (linkMatr[j][i] != 0) {
        S[j][i] += pow((double)weightMatr[j][i], 1 / 3.);
        K[i]++;
        K[j]++;
      }
    }
  }

  // cluster : diag(S^3) / 2
  cluster.resize(nodeSize, 0);
  cluster_c = 0;
  for (NodeType nodeI = 0; nodeI < nodeSize; nodeI++) {
    if (K[nodeI] < 2) continue;
    for (VNodeTypeCItr j = p2p[nodeI].begin(), end = p2p[nodeI].end(); j != end;
         j++) {
      const NodeType nodeJ = *j;
      for (VNodeTypeCItr jj = j + 1; jj != end; jj++) {
        if (S[*jj][nodeJ] != 0) {
          const double t = S[nodeJ][nodeI] * S[*jj][nodeJ] * S[*jj][nodeI];
          cluster[nodeI] += t;
          cluster[nodeJ] += t;
          cluster[*jj] += t;
        }
      }
    }
  }

  // cluster : diag(S^3) / (K.*(K-1) - 2*diag(A^2))
  for (NodeType i = 0; i < nodeSize; i++)
    if (cluster[i] != 0)
      cluster_c += cluster[i] /= K[i] * (K[i] - 1.) - 2 * A2[i];
  cluster_c /= nodeSize;

  return 0;
}

int cal_cluster_directed_unweight(double &cluster_c, VDouble &cluster,
                                  const VVDistType &linkMatr) {
  const NodeType nodeSize = linkMatr.size();
  VVNodeType p2p(nodeSize);
  VNodeType K(nodeSize, 0);   // nodeDeg = Out + In
  VNodeType A2(nodeSize, 0);  // A^2
  VVChar S(nodeSize);         // S = W^1/3 + W'^1/3
  for (NodeType j = 1; j < nodeSize; j++) {
    S[j].assign(j, 0);
    for (NodeType i = 0; i < j; i++) {
      if (linkMatr[i][j] != 0 || linkMatr[j][i] != 0) p2p[i].push_back(j);
      if (linkMatr[i][j] != 0 && linkMatr[j][i] != 0) {
        A2[i]++;
        A2[j]++;
      }
      if (linkMatr[i][j] != 0) {
        S[j][i] = 1;
        K[i]++;
        K[j]++;
      }
      if (linkMatr[j][i] != 0) {
        S[j][i]++;
        K[i]++;
        K[j]++;
      }
    }
  }

  // cluster : diag(S^3) / 2
  cluster.resize(nodeSize, 0);
  cluster_c = 0;
  NodeType nodeI = 0;
  for (VVNodeTypeCItr i = p2p.begin(); i != p2p.end(); nodeI++, i++) {
    for (VNodeTypeCItr j = i->begin(); j != i->end(); j++) {
      const NodeType nodeJ = *j;
      for (VNodeTypeCItr jj = p2p[nodeJ].begin(); jj != p2p[nodeJ].end();
           jj++) {
        if (S[*jj][nodeI] != 0) {
          const double t = S[nodeJ][nodeI] * S[*jj][nodeJ] * S[*jj][nodeI];
          cluster[nodeI] += t;
          cluster[nodeJ] += t;
          cluster[*jj] += t;
        }
      }
    }
  }

  // cluster : diag(S^3) / (K.*(K-1) - 2*diag(A^2))
  for (NodeType i = 0; i < nodeSize; i++)
    if (cluster[i] != 0)
      cluster_c += cluster[i] /= (K[i] * (K[i] - 1.) - 2 * A2[i]);
  cluster_c /= nodeSize;

  return 0;
}

//**//*******************************************************//*
#endif  // STAT_CLUSTER
