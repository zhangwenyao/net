#ifndef NETWORK_STAT_SIMILARITH_H
#define NETWORK_STAT_SIMILARITH_H
#include "similarity.h"
#ifdef STAT_SIMILARITY

#include <iostream>

namespace network {
namespace similarity {
  // ******************************************************
  class Similarity {
public:
    VVDouble nodeCoef; // 网络节点相似系数
    VVDouble edgeCoef; // 网络连边相似系数

    Similarity(void);
    // friend std::ostream& operator<<(std::ostream& os,
    // const Similarity& similarity);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\t') const;
    int save(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\n') const;
    int read_params_1(std::string& s, std::istream& is);
    Similarity& clear(void);
  };
}
}

// ******************************************************
std::ostream& operator<<(
    std::ostream& os, const network::similarity::Similarity& similarity);

#endif // STAT_SIMILARITY
#endif // NETWORK_STAT_SIMILARITH_H
