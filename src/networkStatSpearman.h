#ifndef NETWORK_STAT_SPEARMAN_H
#define NETWORK_STAT_SPEARMAN_H

#include "net.h"
#ifdef STAT_SPEARMAN

#include <iostream>
#include "network.h"
//**//****************************************************//*
int net_clear_spearman(Network& net);
int net_cal_spearman(Network& net);
int net_degArr_2_deg2ArrVal_weight(Network& net);
int net_read_params_spearman(std::istream& is, Network& net);
int net_save_params_spearman(std::ostream& os, const Network& net);
int net_save_spearman(const Network& net, const char* name = NULL);

#ifdef MODEL_GAUSS
int net_read_SGaussS2(Network& net, const char* name = NULL);
int net_save_gauss(const Network& net, const char* name = NULL);
int net_cal_lkkProb_gauss(Network& net);
int net_gauss_new_ranLink(
    Network& net);  // 随机选点按度之差的相应高斯概率连边，重连时随机选点再选边
#endif              // MODEL_GAUSS
//**//****************************************************//*
#endif  // STAT_SPEARMAN
#endif  // NETWORK_STAT_SPEARMAN_H
