#ifndef DYNAMICS__RECOMMEND__NETWORK_H_
#define DYNAMICS__RECOMMEND__NETWORK_H_
#include "recommend.h"
#ifdef ACT_RECOMMEND

#include <iostream>

namespace network {
namespace recommend {
  // ******************************************************
  // 参数：   mass
  //          heat

  class Recommend {
public:
    VDouble user, object;
    VVDouble rcm, *rcmP;
    VVNodeType user_user, user_object, object_user, object_object;
    const VVNodeType *uu, *uo, *ou, *oo;
    VVNodeType user_p_user, user_p_object, object_p_user, object_p_object;
    const VVNodeType *uuP2p, *uoP2p, *ouP2p, *ooP2p;
    double lambda;

    Recommend(void);
    //friend std::ostream& operator<<(
        //std::ostream& os, const Recommend& recommend);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\t') const;
    int save(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\n') const;
    int read_params_1(std::string& s, std::istream& is);
    Recommend& clear(void);
  };
}
}
// ******************************************************
std::ostream& operator<<(std::ostream& os, const network::recommend::Recommend& recommend);

#endif // ACT_RECOMMEND
#endif // NETWORK_ACT_RECOMMEND_H
