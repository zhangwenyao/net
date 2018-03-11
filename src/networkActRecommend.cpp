#include "ActRecommend.h"
#ifdef ACT_RECOMMEND

#include "common.h"
#include "networks.h"
using namespace std;

//**//****************************************************//*
Act_recommend::Act_recommend(void)
    : user_p_object(NULL)
    , object_p_user(NULL)
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

int Act_recommend::save_params(const char* name) const { return 0; }
int Act_recommend::save_data(const char* name) const { return 0; }
int Act_recommend::save(const char* name) const { return 0; }

int Act_recommend::read_params_1(string& s, istream& is) { return 0; }

Act_recommend& Act_recommend::clear(void)
{
  user.clear();
  object.clear();
  return *this;
}

//**//****************************************************//*
Networks& Networks::act_recommend(std::string s, const char* name)
{
  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else
    fn = saveName;

  if (s == "mass") {
    status = act_recommend_mass((fn + "_mass.txt").c_str(),
        *recommend.user_p_object, *recommend.object_p_user);
  } else if (s == "heat") {
    status = act_recommend_heat((fn + "_heat.txt").c_str(),
        *recommend.user_p_object, *recommend.object_p_user);
  } else if (s == "pagerank") {
    status = act_recommend_pagerank(
        (fn + "_pagerank.txt").c_str(), p2p, recommend.user);
  } else {
    status = -1;
  }
  return *this;
}

//**//****************************************************//*
#endif // ACT_RECOMMEND
