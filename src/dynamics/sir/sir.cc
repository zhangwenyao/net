#include "sir.h"
#ifdef ACT_SIR

#include "../../common/common.h"
using namespace std;
using namespace common;
using namespace network;

// *******************************************************
int network::sir::act_sir_id0(VNodeType& R_nums_, const double beta,
                              const double gamma, const VVNodeType& p2p,
                              const NodeType nodeSize, const NodeType id0) {
  VNodeType S_ids, I_ids, S_ids_, I_ids_;
  VBool I_flag(nodeSize, 0), I_flag_;
  for (NodeType i = 0; i < nodeSize; ++i) {
    if (i == id0) {
      I_ids.push_back(id0);
    } else {
      S_ids.push_back(i);
    }
  }
  // I_nums.push_back(1);
  R_nums_.clear();
  R_nums_.push_back(0);

  while (I_ids.size()) {
    S_ids_.clear();
    I_ids_.clear();
    swap(S_ids, S_ids_);
    swap(I_ids, I_ids_);
    I_flag_ = I_flag;
    NodeType R_num = R_nums_.back();
    // S -> I
    for (auto i : S_ids_) {
      NodeType ni = 0;
      for (auto j : p2p[i]) ni += I_flag_[j];
      if (ni <= 0) continue;
      double r = 1 - pow(1 - beta, ni), ra = rand_double();
      if (ra >= r) {
        S_ids.push_back(i);
      } else {
        I_ids.push_back(i);
        I_flag[i] = true;
      }
    }
    // I -> R
    for (auto i : I_ids_) {
      if (rand_double() >= gamma) {
        I_ids.push_back(i);
      } else {
        I_flag[i] = false;
        R_num++;
      }
    }
    // update
    // I_nums.push_back(I_ids.size());
    R_nums_.push_back(R_num);
  }

  return EXIT_SUCCESS;
}

int network::sir::act_sir_beta_id0(VNodeType& R_nums_, const double beta,
                                   const VVNodeType& p2p,
                                   const NodeType nodeSize,
                                   const NodeType id0) {
  VNodeType S_ids, I_ids, S_ids_, I_ids_;
  VBool I_flag(nodeSize, 0), I_flag_;
  for (NodeType i = 0; i < nodeSize; ++i) {
    if (i == id0) {
      I_ids.push_back(id0);
      I_flag[i] = true;
    } else {
      S_ids.push_back(i);
    }
  }
  R_nums_.clear();
  R_nums_.push_back(0);

  while (I_ids.size()) {
    S_ids_.clear();
    I_ids_.clear();
    swap(S_ids, S_ids_);
    swap(I_ids, I_ids_);
    I_flag_ = I_flag;
    // S -> I
    for (auto i : S_ids_) {
      NodeType ni = 0;
      for (auto j : p2p[i]) ni += I_flag_[j];
      if (ni <= 0) continue;
      double r = 1 - pow(1 - beta, ni), ra = rand_double();
      if (ra >= r) {
        S_ids.push_back(i);
      } else {
        I_ids.push_back(i);
        I_flag[i] = true;
      }
    }
    // I -> R
    for (auto i : I_ids_) {
      I_flag[i] = false;
    }
    // update
    NodeType R_num = R_nums_.back() + I_ids_.size();
    R_nums_.push_back(R_num);
  }

  return EXIT_SUCCESS;
}

int network::sir::act_sir_cal_lambdac(double& lambda_c, const VVNodeType& p2p) {
  LinkType kSum = 0, k2Sum = 0;
  for (NodeType i = 0; i < p2p.size(); ++i) {
    NodeType k = p2p[i].size();
    kSum += k;
    k2Sum += k * k;
  }
  lambda_c = (double)kSum / (k2Sum - kSum);
  return 0;
}

NodeType get_father(unordered_map<NodeType, NodeType>& fa, const NodeType i) {
  NodeType& f = fa[i];
  if (f == i) return f;
  return f = get_father(fa, f);
}

NodeType join(unordered_map<NodeType, NodeType>& fa, const NodeType i,
              const NodeType j) {
  NodeType fi = get_father(fa, i), fj = get_father(fa, j);
  return fa[fi] = fa[fj] = min(fi, fj);
}

int act_sir_cal_modularity_i(const VVNodeType& p2p, const NodeType i) {
  unordered_map<NodeType, NodeType> fa;
  for (auto j : p2p[i]) {
    fa[j] = j;
  }
  for (auto it : fa) {
    auto j = it.first;
    for (auto k : p2p[j]) {
      if (fa.count(k)) {
        join(fa, k, j);
      }
    }
  }
  unordered_set<NodeType> modularity;
  for (auto i : fa) modularity.insert(i.second);
  return modularity.size();
}
int act_sir_cal_modularity_i2(const VVNodeType& p2p, const NodeType i) {
  unordered_map<NodeType, NodeType> fa;
  for (auto j : p2p[i]) {
    fa[j] = j;
    for (auto k : p2p[j]) {
      if (k != i) {
        fa[k] = k;
      }
    }
  }
  for (auto it : fa) {
    auto j = it.first;
    for (auto k : p2p[j]) {
      if (fa.count(k)) {
        join(fa, k, j);
      }
    }
  }
  unordered_set<NodeType> modularity;
  for (auto i : fa) modularity.insert(i.second);
  return modularity.size();
}

int network::sir::act_sir_cal_modularity(const VVNodeType& p2p,
                                         VNodeType& modularity_nums,
                                         VNodeType& modularity_nums2,
                                         const NodeType nodeSize) {
  modularity_nums.assign(nodeSize, 0);
  modularity_nums2.assign(nodeSize, 0);
  for (NodeType i = 0; i < nodeSize; i++) {
    modularity_nums[i] = act_sir_cal_modularity_i(p2p, i);
    modularity_nums2[i] = act_sir_cal_modularity_i2(p2p, i);
  }
  return EXIT_SUCCESS;
}

int network::sir::act_sir_cal_params(const VVNodeType& p2p, VDouble& Rs,
                                     const NodeType i, VNodeType& R_nums_) {
  // LinkType kSum = 0, k2Sum = 0;
  // for (NodeType i = 0; i < p2p.size(); ++i) {
  //   NodeType k = p2p[i].size();
  //   kSum += k;
  //   k2Sum += k * k;
  // }
  // lambda_c = (double)kSum / k2Sum;
  // LinkType r_sum = 0;
  // for(auto x: R_nums_) r_sum += x;
  // Rs[i] = (double)r_sum / R_nums_.size();
  Rs[i] = R_nums_.back();
  return 0;
}

int network::sir::act_sir_lambda(VDouble& Rs, const double beta,
                                 const VVNodeType& p2p,
                                 const NodeType nodeSize) {
  Rs.assign(nodeSize, 0);
  VNodeType R_nums_;
  for (NodeType i = 0; i < nodeSize; ++i) {
    // act_sir_id0(R_nums_, beta, gamma, p2p, nodeSize, i);
    act_sir_beta_id0(R_nums_, beta, p2p, nodeSize, i);
    Rs[i] = R_nums_.back();
    // act_sir_cal_params(Rs, R);
  }
  return EXIT_SUCCESS;
}
// *******************************************************
#endif  // ACT_SIR
