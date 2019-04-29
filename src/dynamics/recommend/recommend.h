#ifndef DYNAMICS__RECOMMEND__RECOMMEND_H_
#define DYNAMICS__RECOMMEND__RECOMMEND_H_
#include "../../network/net.h"
#ifdef ACT_RECOMMEND

namespace network {
namespace recommend {
  // *******************************************************
  int act_recommend_readP2p(VVNodeType& pu, VVNodeType& po, std::istream& is);
  int linkMatr_2_p2p2(VVNodeType& user_p_object, VVNodeType& object_p_user,
      const VVDistType& matr);
  int linkMatr_2_userP2p(const VVDistType& matr, VVNodeType& userP2p);
  int linkMatr_2_objectP2p(const VVDistType& matr, VVNodeType& objectP2p);

  int act_recommend_start(const VNodeType p2pI, VDouble& o);
  int act_recommend_mass_1(VDouble& o2, const VVNodeType& uP2p,
      const VVNodeType& oP2p, const NodeType i);
  int act_recommend_mass(
      VVDouble& rcm, const VVNodeType& uP2p, const VVNodeType& oP2p);
  int act_recommend_heat_1(VDouble& o2, const VVNodeType& uP2p,
      const VVNodeType& oP2p, const NodeType i);
  int act_recommend_heat(
      VVDouble& rcm, const VVNodeType& uP2p, const VVNodeType& oP2p);
  int act_recommend_pagerank(const VVNodeType& p2p, VDouble& v);
  int act_recommend_commonNeighbour_object(
      VVDouble& rcm, const VVNodeType& oo);
  int act_recommend_hybrid_matrix(VVDouble& rcm, const VVNodeType& uP2p,
      const VVNodeType& oP2p, const double lambda);
  template <typename T>
  int cal_proximity_rca2phi(
      const std::vector<std::vector<T>>& rca_uo, VVDouble& phi_oo);
  template <typename T>
  int act_recommend_proximity_wcp(
      VVDouble& rcm, const std::vector<std::vector<T>>& uo);
  template <typename T>
  int act_recommend_proximity_phi(
      VVDouble& rcm, const std::vector<std::vector<T>>& user_object);

  int recommend_RAC(const VDouble& v0, const VDouble& v, double& r);
  int recommend_RMAE(const VDouble& v0, const VDouble& v, double& r);
  int recommend_NMAE(const VDouble& v0, const VDouble& v, double& r);
  int recommend_F(const VNodeType& v0, const VNodeType& v, double& recall,
      double& precision, double& F);
  int recommend_rankingScore(
      const VNodeType& R, const VNodeType& L, double& rs);
  template <typename T>
  int recommend_rankingScore(const VNodeType& rk, const std::vector<T>& L0,
      const std::vector<T>& L, double& rs, double& rsDev);
  template <typename T>
  int count_rankingScore(const VVDouble& rcm, const size_t NC,
      const size_t NP, const std::vector<std::vector<T>>& mcp,
      const std::vector<std::vector<T>>& mcp2, VDouble& rankingScore,
      VDouble& rankingScoreDev);
}
}
// *******************************************************
#include "recommend_template.h"
#endif // ACT_RECOMMEND
#endif // ACT_RECOMMEND_H
