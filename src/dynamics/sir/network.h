#ifndef DYNAMICS__SIR__NETWORK_H_
#define DYNAMICS__SIR__NETWORK_H_
#include "sir.h"
#ifdef ACT_SIR

#include <iostream>

namespace network {
namespace sir {
enum STATUS { S = 0, I = 1, R = 2 };
typedef std::vector<STATUS> VStatus;
// ******************************************************
class Sir {
 public:
  double beta;   // 1v1感染概率
  double gamma;  // 恢复概率
  double ksi, lambda_c;
  NodeType id0;
  VNodeType R_nums_;
  VDouble Rs;
  VNodeType modularity_nums, modularity_nums2;

  Sir(void);
  // friend std::ostream& operator<<(std::ostream& os, const Sir& sir);
  int save_params(std::ostream& os) const;
  int save_params(const char* name = NULL) const;
  int save_data(const char* name = NULL, const long seed = 0,
                const char priChar = '\n', const char priChar2 = '\t') const;
  int save(const char* name = NULL, const char priChar = '\n',
           const char priChar2 = '\n') const;
  int read_params_1(std::string& s, std::istream& is);
  Sir& clear(void);

 private:
  VStatus status_;
};
}  // namespace sir
}  // namespace network
// ******************************************************
std::ostream& operator<<(std::ostream& os, const network::sir::Sir& sir);

#endif  // ACT_SIR
#endif  // NETWORK_ACT_SIR_H
