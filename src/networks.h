#ifndef NETWORKS_H
#define NETWORKS_H

#include "network.h"

//**//************************************************************//*

#ifdef NET_EXTREMUM
#include "NetExtremum.h"
#include "networkExtremum.h"
#endif

#ifdef NET_BA
#include "NetBA.h"
#include "networkBA.h"
#endif

#ifdef NET_GRID
#include "NetGrid.h"
#include "networkGrid.h"
#endif

#ifdef NET_ACTOR
#include "NetActor.h"
#endif

#ifdef NET_FOODWEB
#include "NetFoodweb.h"
#endif

#ifdef STAT_PEARSON
#include "StatPearson.h"
#include "networkStatPearson.h"
#endif

#ifdef STAT_SPEARMAN
#include "StatSpearman.h"
#include "networkStatSpearman.h"
#endif

#ifdef STAT_BETWEENNESS
#include "StatBetweenness.h"
#include "networkStatBetweenness.h"
#endif

#ifdef STAT_MODULARITY
#include "StatModularity.h"
#include "networkStatModularity.h"
#endif

#ifdef STAT_SIMILARITY
#include "StatSimilarity.h"
#include "networkStatSimilarity.h"
#endif

#ifdef STAT_CLUSTER
#include "StatCluster.h"
#include "networkStatCluster.h"
#endif

#ifdef STAT_KENDALL
#include "StatKendall.h"
#include "networkStatKendall.h"
#endif

#ifdef ACT_RECOMMEND
#include "ActRecommend.h"
#include "networkActRecommend.h"
#endif

#ifdef ACT_FITNESS_COMPLEXITY
#include "ActFitnessComplexity.h"
#endif

//**//************************************************************//*
class Networks : public Network {
 public:
  Networks* net2;

  Networks(void);
  //~Networks(void);
  Networks& clear(void);
  friend std::ostream& operator<<(std::ostream& os, const Networks& net);
  const Networks& save_params(std::ostream& os) const;
  const Networks& save_params(const char* name = NULL) const;
  Networks& save_data(const char* name = NULL);
  Networks& save(const char* name = NULL);
  friend std::istream& operator>>(std::istream& is, Networks& net);
  Networks& read_params_1(std::istream& is);
  Networks& run(const std::string argv2 = "");
  Networks& stat(void);

  Networks& cal_params(const std::string& s);
  Networks& cal_nodeDeg(const std::string& s);
  Networks& cal_p2p(const std::string& s);
  Networks& fix_p2p_nodeDeg0(void);

#ifdef NET_DEGREE
  Net_degree degree;
#ifdef DEG_POWER
  Networks& deg_power(void);
  Networks& power_check_params(void);
#endif
#ifdef DEF_POISSON
  Networks& deg_poisson(void);
#endif
#endif

#ifdef NET_RANDOM
  Net_random random;
  Networks& net_ER(void);
  Networks& net_random_remDeg(void);
#endif

#ifdef ACT_SIS
  Act_SIS sis;
  int act_SIS();
  int cal_SIS_tau();
#endif
};

std::ostream& operator<<(std::ostream& os, const Networks& net);

//**//************************************************************//*
#endif  // NETWOKS_H
