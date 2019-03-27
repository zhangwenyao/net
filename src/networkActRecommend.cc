#include "ActRecommend.h"
#ifdef ACT_RECOMMEND

#include "common.h"
#include "networks.h"
using namespace std;

// ******************************************************
Act_recommend::Act_recommend(void)
    : rcmP(&rcm)
    , uu(&user_user)
    , uo(&user_object)
    , ou(&object_user)
    , oo(&object_object)
    , uuP2p(&user_p_user)
    , uoP2p(&user_p_object)
    , ouP2p(&object_p_user)
    , ooP2p(&object_p_object)
{
}

ostream& operator<<(ostream& os, const Act_recommend& recommend)
{
  if (!os) {
    ERROR();
    return os;
  }
  return os;
}

int Act_recommend::save_params(std::ostream& os) const
{
  os << *this;
  return 0;
}

int Act_recommend::save_params(const char* name) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  os.close();
  return 0;
}

int Act_recommend::save_data(
    const char* name, const char priChar, const char priChar2) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  common_save2((fn + ".rcm.txt").c_str(), rcm, priChar2);
  return 0;
}

int Act_recommend::save(
    const char* name, const char priChar, const char priChar2) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + ".recommend.params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 != save_data((fn + ".recommend").c_str(), priChar, priChar2)) {
    ERROR();
    return -1;
  }
  return 0;
}

int Act_recommend::read_params_1(string& s, istream& is) { return 0; }

Act_recommend& Act_recommend::clear(void)
{
  user.clear();
  object.clear();
  return *this;
}

// ******************************************************
Networks& Networks::act_recommend(std::string s, const char* name)
{
  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else
    fn = saveName;

  if (s == "mass") {
    status = ::act_recommend_mass(
        recommend.rcm, *recommend.uoP2p, *recommend.ouP2p);
  } else if (s == "heat") {
    status = act_recommend_heat(
        recommend.rcm, *recommend.uoP2p, *recommend.ouP2p);
  } else if (s == "hybrid") {
    status = act_recommend_hybrid_matrix(
        recommend.rcm, *recommend.uoP2p, *recommend.ouP2p, recommend.lambda);
  } else if (s == "pagerank") {
    status = act_recommend_pagerank(p2p, recommend.user);
  } else if (s == "commonNeighbour_object") {
    status = act_recommend_commonNeighbour_object(
        recommend.rcm, *recommend.ooP2p);
  } else if (s == "proximity_wcp") {
    status
        = act_recommend_proximity_wcp(recommend.rcm, recommend.user_object);
  } else if (s == "proximity_phi") {
    status
        = act_recommend_proximity_phi(recommend.rcm, recommend.user_object);
  } else {
    status = -1;
  }
  return *this;
}

// ******************************************************

#endif // ACT_RECOMMEND
