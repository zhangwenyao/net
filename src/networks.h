#ifndef NETWORKS_H
#define NETWORKS_H

#include "network.h"

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
#ifdef DEG_POISSON
  Networks& deg_poisson(void);
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

#ifdef ACT_SIS
  Act_SIS sis;
  int act_SIS();
  int cal_SIS_tau();
#endif
};

std::ostream& operator<<(std::ostream& os, Networks& net);

//**//************************************************************//*
#endif  // NETWOKS_H
