#ifndef NETWORK_STAT_SIMILARITH_H
#define NETWORK_STAT_SIMILARITH_H
#include "StatSimilarity.h"
#ifdef STAT_SIMILARITY

#include <iostream>

//**//****************************************************//*
class Stat_similarity {
  public:
    VVDouble nodeCoef;  // 网络节点相似系数
    VVDouble edgeCoef;  // 网络连边相似系数

    Stat_similarity(void);
    friend std::ostream& operator<<(std::ostream& os,
        const Stat_similarity& similarity);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\t') const;
    int save(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\n') const;
    int read_params_1(std::string& s, std::istream& is);
    Stat_similarity& clear(void);
};
std::ostream& operator<<(std::ostream& os, const Stat_similarity& similarity);

//**//****************************************************//*
#endif  // STAT_SIMILARITY
#endif  // NETWORK_STAT_SIMILARITH_H

