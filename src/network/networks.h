#ifndef NETWORK__NETWORKS_H_
#define NETWORK__NETWORKS_H_

#include "network.h"

#ifdef NET_DEGREE
#include "../model/degree/network.h"
#endif

#ifdef NET_EXTREMUM
#include "../model/extremum/network.h"
#endif

#ifdef NET_RANDOM
#include "../model/random/network.h"
#endif

#ifdef NET_BA
#include "../model/BA/network.h"
#endif

#ifdef NET_GRID
#include "../model/grid/network.h"
#endif

#ifdef NET_ACTOR
#include "../model/actor/network.h"
#endif

#ifdef NET_FOODWEB
#include "../model/foodweb/network.h"
#endif

#ifdef STAT_STAT
#include "../statistics/stat.h"
#endif

#ifdef STAT_PEARSON
#include "../statistics/pearson/network.h"
#endif

#ifdef STAT_SPEARMAN
#include "../statistics/spearman/network.h"
#endif

#ifdef STAT_KENDALL
#include "../statistics/kendall/network.h"
#endif

#ifdef STAT_RELATIVITY
#include "../statistics/relativity/network.h"
#endif

#ifdef STAT_CORRELATION2
#include "../statistics/correlation2/network.h"
#endif

#ifdef STAT_BETWEENNESS
#include "../statistics/betweenness/network.h"
#endif

#ifdef STAT_MODULARITY
#include "../statistics/modularity/network.h"
#endif

#ifdef STAT_CLUSTER
#include "../statistics/cluster/network.h"
#endif

#ifdef STAT_SIMILARITY
#include "../statistics/similarity/network.h"
#endif

#ifdef ACT_SIS
#include "../dynamics/sis/network.h"
#endif

#ifdef ACT_SPREAD
#include "../dynamics/spread/network.h"
#endif

#ifdef ACT_FITNESS_COMPLEXITY
#include "../dynamics/fitness_complexity/network.h"
#endif

#ifdef ACT_RECOMMEND
#include "../dynamics/recommend/network.h"
#endif

#ifdef ACT_CORRELATION
#include "../dynamics/correlation/network.h"
#endif

// **************************************************************
namespace network {
class Networks : public Network {
  public:
  Networks* net2;

  Networks(void);
  //~Networks(void);
  Networks& clear(void);
  // friend std::ostream& operator<<(std::ostream& os, Networks& net);
  Networks& save_params(std::ostream& os);
  Networks& save_params(const char* name = NULL);
  Networks& save_data(const char* name = NULL);
  Networks& save(const char* name = NULL);
  // friend std::istream& operator>>(std::istream& is, Networks& net);
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
  network::degree::Degree degree;
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
  network::random::Random random;
  Networks& net_random_clear(void);
  Networks& net_random_init(void);
  Networks& net_ER(void);
  Networks& net_random_ranNode_link(void);
  Networks& net_random_node_prob(void);
  Networks& net_random_remDeg(void);
  Networks& net_random_remDeg_dir(void);
  Networks& net_random_ranNode(void);
#endif

#ifdef NET_BA
  network::ba::Ba ba;
  Networks& net_BA(void);
#endif

#ifdef NET_GRID
  network::grid::Grid grid;
  Networks& net_grid(void);
#endif

#ifdef NET_EXTREMUM
  Networks& net_Max(void);
  Networks& net_Max_new_lkk(const int fix = 1);
  Networks& net_Max_new_lkk2();
  Networks& net_Max_new_lkk3();
  Networks& net_Min(void);
  Networks& net_Min_new_lkk_p2p(const int fix = 1);
  Networks& net_Min_new_lkk(const int fix = 1);
  Networks& net_Min_new_lkk3(void);
  Networks& net_extremum_lkk(const int extrMax, const unsigned countN = 3);
  Networks& extremum_cal_lkk(std::string& s, std::istream& is);
#endif

#ifdef STAT_PEARSON
  network::pearson::Pearson pearson;
  Networks& stat_pearson(void);
#endif

#ifdef STAT_SPEARMAN
  network::spearman::Spearman spearman;
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
  network::kendall::Kendall kendall;
  Networks& stat_kendall(void);
#endif

#ifdef STAT_RELATIVITY
  network::relativity::Relativity relativity;
  Networks& stat_relativity(void);
#endif

#ifdef STAT_CORRELATION2
  network::correlation2::Correlation2 correlation2;
  Networks& stat_correlation2(void);
#endif

#ifdef STAT_BETWEENNESS
  network::betweenness::Betweenness betweenness;
  Networks& stat_betweenness(void);
#endif

#ifdef STAT_MODULARITY
  network::modularity::Modularity modularity;
  Networks& cal_modularity(void);
  Networks& stat_modularity(void);
#ifdef STAT_BETWEENNESS
  Networks& stat_modularity_newman(double& qMax, NodeType mSize = 0);
#endif
#endif

#ifdef STAT_SIMILARITY
  network::similarity::Similarity similarity;
  Networks& stat_similarity(Networks& net2);
#endif

#ifdef STAT_CLUSTER
  network::cluster::Cluster cluster;
  Networks& stat_cluster(void);
#endif

#ifdef ACT_SPREAD
  network::spread::Spread spread;
  Networks& stat_spread(void);
#endif

#ifdef ACT_SIS
  network::sis::Sis sis;
  Networks& act_sis(void);
  Networks& act_sis_tau(void);
#endif

#ifdef ACT_FITNESS_COMPLEXITY
#endif

#ifdef ACT_RECOMMEND
  network::recommend::Recommend recommend;
  Networks& act_recommend(std::string s = "mass", const char* name = NULL);
#endif

};

// **************************************************************
}
std::ostream& operator<<(std::ostream& os, network::Networks& net);
std::istream& operator>>(std::istream& is, network::Networks& net);

#endif // NETWOKS_H_
