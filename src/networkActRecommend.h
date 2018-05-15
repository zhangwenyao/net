#ifndef NETWORK_ACT_RECOMMEND_H
#define NETWORK_ACT_RECOMMEND_H
#include "ActRecommend.h"
#ifdef ACT_RECOMMEND

#include <iostream>

//**//****************************************************//*
// 参数：   mass
//          heat

class Act_recommend {
  public:
  VDouble user, object;
  VVDouble rcm;
  const VVNodeType* user_p_user;
  const VVNodeType* user_p_object;
  const VVNodeType* object_p_user;
  const VVNodeType* object_p_object;
  double lambda;

  Act_recommend(void);
  friend std::ostream& operator<<(
      std::ostream& os, const Act_recommend& recommend);
  int save_params(std::ostream& os) const;
  int save_params(const char* name = NULL) const;
  int save_data(const char* name = NULL, const char priChar = '\n',
      const char priChar2 = '\t') const;
  int save(const char* name = NULL, const char priChar = '\n',
      const char priChar2 = '\n') const;
  int read_params_1(std::string& s, std::istream& is);
  Act_recommend& clear(void);
};
std::ostream& operator<<(std::ostream& os, const Act_recommend& recommend);

//**//****************************************************//*
#endif // ACT_RECOMMEND
#endif // NETWORK_ACT_RECOMMEND_H
