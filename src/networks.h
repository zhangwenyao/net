#ifndef NETWORKS_H
#define NETWORKS_H

#include "network.h"

#ifdef NET_DEGREE
#include "networkDegree.h"
#endif

#ifdef NET_RANDOM
#include "networkRandom.h"
#endif

#ifdef NET_BA
#include "networkBA.h"
#endif

#ifdef NET_GRID
#include "networkGrid.h"
#endif

#ifdef NET_EXTREMUM
#include "networkExtremum.h"
#endif

#ifdef STAT_PEARSON
#include "networkStatPearson.h"
#endif

#ifdef STAT_SPEARMAN
#include "networkStatSpearman.h"
#endif

#ifdef STAT_KENDALL
#include "networkStatKendall.h"
#endif

#ifdef STAT_BETWEENNESS
#include "networkStatBetweenness.h"
#endif

#ifdef STAT_MODULARITY
#include "networkStatModularity.h"
#endif

#ifdef STAT_CLUSTER
#include "networkStatCluster.h"
#endif

#ifdef STAT_SIMILARITY
#include "networkStatSimilarity.h"
#endif

#ifdef ACT_SIS
#include "networkActSis.h"
#endif

#ifdef ACT_SPREAD
#include "networkActSpread.h"
#endif

#ifdef ACT_RECOMMEND
#include "networkActRecommend.h"
#endif

//**//************************************************************//*
class Networks : public Network {
  public:
  Networks* net2;

  Networks(void);
  //~Networks(void);
  Networks& clear(void);
  friend std::ostream& operator<<(std::ostream& os, Networks& net);
  Networks& save_params(std::ostream& os);
  Networks& save_params(const char* name = NULL);
  Networks& save_data(const char* name = NULL);
  Networks& save(const char* name = NULL);
  friend std::istream& operator>>(std::istream& is, Networks& net);
  Networks& read_params_1(std::string& s, std::istream& is);
  Networks& read_params(const char* name = NULL);
  Networks& read_params(int argc, char** argv);
  Networks& run(const std::string argv2 = "");
  Networks& stat(void);

  Networks& cal_params(const std::string& s = "");
  Networks& cal_nodeDeg(const std::string& s = "");
  Networks& cal_p2p(const std::string& s = "");
  Networks& fix_p2p_nodeDeg0(void);

#ifdef NET_DEGREE
  Net_degree degree;
#ifdef DEG_POWER
  Networks& degree_power_arr(void);
  Networks& degree_power(void);
  Networks& degree_power_check_params(void);
#endif
#ifdef DEG_POISSON
  Networks& degree_poisson(void);
#endif
#endif

#ifdef NET_RANDOM
  Net_random random;
  Networks& net_random_clear(void);
  Networks& net_random_init(void);
  Networks& net_ER(void);
  Networks& net_random_ranNode_link(void);
  Networks& net_random_node_prob(void);
  Networks& net_random_remDeg(void);
  Networks& net_random_ranNode(void);
#endif

#ifdef NET_BA
  Net_BA ba;
  Networks& net_BA(void);
#endif

#ifdef NET_GRID
  Net_grid grid;
  Networks& net_grid(void);
#endif

#ifdef NET_EXTREMUM
  Networks& net_Max(void);
  Networks& net_Max_new_lkk(const int fix = 1);
  Networks& net_Min(void);
  Networks& net_Min_new_lkk_p2p(const int fix = 1);
  Networks& net_Min_new_lkk(const int fix = 1);
  Networks& net_extremum_lkk(const int extrMax, const unsigned countN = 3);
  Networks& extremum_cal_lkk(std::string& s, std::istream& is);
#endif

#ifdef STAT_PEARSON
  Stat_pearson pearson;
  Networks& stat_pearson(void);
#endif

#ifdef STAT_SPEARMAN
  Stat_spearman spearman;
  Networks& stat_spearman(void);
  Networks& spearman_degArr_2_deg2ArrVal_weight(void);
#ifdef MODEL_GAUSS
  Networks& spearman_read_GaussS2(const char* name = NULL);
  Networks& spearman_cal_lkkProb_gauss(void);
  Networks& spearman_gauss_new_ranLink(
      void); // 随机选点按度之差的相应高斯概率连边，重连时随机选点再选边
#endif       // MODEL_GAUSS
#endif

#ifdef STAT_KENDALL
  Stat_kendall kendall;
  Networks& stat_kendall(void);
#endif

#ifdef STAT_BETWEENNESS
  Stat_betweenness betweenness;
  Networks& stat_betweenness(void);
#endif

#ifdef STAT_MODULARITY
  Stat_modularity modularity;
  Networks& cal_modularity(void);
  Networks& stat_modularity(void);
#ifdef STAT_BETWEENNESS
  Networks& stat_modularity_newman(double& qMax, NodeType mSize = 0);
#endif
#endif

#ifdef STAT_SIMILARITY
  Stat_similarity similarity;
  Networks& stat_similarity(Networks& net2);
#endif

#ifdef STAT_CLUSTER
  Stat_cluster cluster;
  Networks& stat_cluster(void);
#endif

#ifdef ACT_SPREAD
  Act_spread spread;
  Networks& stat_spread(void);
#endif

#ifdef ACT_SIS
  Act_sis sis;
  Networks& act_sis(void);
  Networks& act_sis_tau(void);
#endif

#ifdef ACT_RECOMMEND
  Act_recommend recommend;
  Networks& act_recommend(void);
  Networks& act_recommend_mass(void);
#endif
};

std::ostream& operator<<(std::ostream& os, Networks& net);

//**//************************************************************//*
#endif // NETWOKS_H
