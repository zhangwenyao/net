#ifndef NETWORKS_H
#define NETWORKS_H

#include "network.h"

//**//************************************************************//*
#ifdef NET_DEGREE
#include "NetDegree.h"
#include "networkDegree.h"
#endif

#ifdef NET_EXTREMUM
#include "NetExtremum.h"
#include "networkExtremum.h"
#endif

#ifdef NET_RANDOM
#include "NetRandom.h"
#include "networkRandom.h"
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

#ifdef ACT_SIS
#include "ActSIS.h"
#include "networkActSIS.h"
#endif

//**//************************************************************//*
std::ostream& operator<<(std::ostream& os, const Network& net);
int net_save_params(std::ostream& os, const Network& net);
int net_save_params(const Network& net, const char* name = NULL);
std::istream& operator>>(std::istream& is, Network& net);
int net_read_params(std::istream& is, Network& net);
int net_read_params(Network& net, const char* name = NULL);
int net_read_params(Network& net, int argc, char** argv);

int net_save0(const Network& net);
int net_save(const Network& net, const char* name = NULL);

//**//************************************************************//*
int net_run(Network& net, const std::string& argv = "");
int net_clear(Network& net);
int net_cal_params(Network& net, const std::string& s);
int net_init_seed(Network& net);
int net_init_seed(Network& net, const int seed);
int net_cal_nodeDeg(Network& net, const std::string& s);
int net_cal_p2p(Network& net, const std::string& s);
int net_stat(Network& net);

//**//************************************************************//*
#endif  // NETWOKS_H
