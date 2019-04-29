#ifndef DYNAMICS__SIS__NETWORK_H_
#define DYNAMICS__SIS__NETWORK_H_
#include "sis.h"
#ifdef ACT_SIS

#include <iostream>

namespace network {
namespace sis {
  // ******************************************************
  class Sis {
public:
    unsigned M;
    double rho, p, lambda;
    double tau, t_av, ksi, lambda_c;
    LinkType nSum, n2Sum;
    NodeType nNum;
    VVNodeType statusSN, SN;
    VNodeType N_i;
    VLinkType NDeg_i;
    VDouble t;

    Sis(void);
    // friend std::ostream& operator<<(std::ostream& os, const Sis& sis);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\t') const;
    int save(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\n') const;
    int read_params_1(std::string& s, std::istream& is);
    Sis& clear(void);
  };
}
}
// ******************************************************
std::ostream& operator<<(std::ostream& os, const network::sis::Sis& sis);

#endif // ACT_SIS
#endif // NETWORK_ACT_SIS_H
