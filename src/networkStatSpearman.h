#ifndef NETWORK_STAT_SPEARMAN_H
#define NETWORK_STAT_SPEARMAN_H
#include "StatSpearman.h"
#ifdef STAT_SPEARMAN

#include <iostream>

//**//****************************************************//*
class Stat_spearman {
  public:
    double spearman, InIn, InOut, OutIn, OutOut, rho, rhoInIn, rhoInOut, rhoOutIn,
           rhoOutOut;
#ifdef MODEL_GAUSS
    // gauss模型
    double r0;
    VDouble GaussS2;  // [nodeSize]   模型的联合概率的方差
#endif              // MODEL_GAUSS

    VDouble deg2ArrVal, deg2ArrValIn,
            deg2ArrValOut;  // [degSize]    归一化后的度分布序列 k
    VDouble nodeNeiAveDeg2, nodeNeiAveDeg2In, nodeNeiAveDeg2Out;  // [nodeSize]
    VDouble neiAveDeg2, neiAveDeg2InIn, neiAveDeg2InOut, neiAveDeg2OutIn,
            neiAveDeg2OutOut;  // [degSize]
    VDouble deg2ArrWeight, deg2ArrWeightOut,
            deg2ArrWeightIn;  // 同度节点连边总权重
    double deg2WeightMean, deg2WeightMeanOut, deg2WeightMeanIn;

    Stat_spearman(void);
    friend std::ostream& operator<<(std::ostream& os,
        const Stat_spearman& spearman);
    int save_params(std::ostream& os, const int dirFlag = 0) const;
    int save_params(const char* name = NULL, const int dirFlag = 0) const;
    int save_data(const char* name = NULL, const int dirFlag = 0, const char priChar = '\n',
        const char priChar2 = '\t') const;
    int save(const char* name = NULL, const int dirFlag = 0, const char priChar = '\n',
        const char priChar2 = '\n') const;
    int read_params_1(std::string& s, std::istream& is);
    Stat_spearman& clear(void);
};
std::ostream& operator<<(std::ostream& os, const Stat_spearman& spearman);

//**//****************************************************//*
#endif  // STAT_SPEARMAN
#endif  // NETWORK_STAT_SPEARMAN_H

