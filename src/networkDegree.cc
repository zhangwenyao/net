#include "networkDegree.h"
#ifdef NET_DEGREE

#include "common.h"
#include "networks.h"
using namespace std;
using namespace net_degree;

// ******************************************************
Net_degree::Net_degree(void)
{
#ifdef DEG_POISSON
  poisson_p = 0;
#endif

#ifdef DEG_POWER
  power_gamma = 0;
#endif
}

std::ostream& operator<<(std::ostream& os, const Net_degree& degree)
{
  if (!os) {
    ERROR();
    return os;
  }

#ifdef DEG_POISSON
  os << "--degree.poisson_p\t" << degree.poisson_p << '\n';
#endif

#ifdef DEG_POWER
  os << "--degree.power_gamma\t" << degree.power_gamma << '\n';
#endif

  return os;
}

int Net_degree::save_params(std::ostream& os) const
{
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int Net_degree::save_params(const char* name) const
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

int Net_degree::save_data(const char* name) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  return 0;
}

int Net_degree::save(const char* name) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + ".degree.params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 != save_data((fn + ".degree").c_str())) {
    ERROR();
    return -1;
  }
  return 0;
}

int Net_degree::read_params_1(string& s, istream& is)
{
  if (!is) {
    ERROR();
    return -1;
  }

  int flag = 1;
  do {
#ifdef DEG_POWER
    if (s == "--degree.power_gamma") {
      is >> power_gamma;
      cout << s << '\t' << power_gamma << endl;
      break;
    }
#endif

#ifdef DEG_POISSON
    if (s == "--degree.poisson_p") {
      is >> poisson_p;
      cout << s << '\t' << poisson_p << endl;
      break;
    }
#endif

    flag = 0;
  } while (0);
  if (flag)
    s.clear();

  return 0;
}

// ******************************************************
#ifdef DEG_POISSON
// Poisson度分布参数
//      poisson_p    连接概率p
//      nodeSize    网络节点数目
Networks& Networks::degree_poisson(void) // 生成度序列 各点均按概率取任意度
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  // 生成度分布概率
  ::poisson_cal_degArrProb(
      degree.poisson_p, degArrVal, degArrProb, kMin, kMax, nodeSize);
  nodeDeg.resize(nodeSize);
  ::random_new_randKArr(&nodeDeg[0], (size_t)nodeSize, &degArrProb[0],
      &degArrVal[0],
      degArrVal.size()); // 调用通用随机函数
  // 修正度序列使总数为偶数
  if (::nodeDeg_2_linkSize(linkSize, nodeDeg) != 0) {
    ::fix_nodeDeg(nodeDeg, degArrProb, degArrVal, linkSize);
    linkSize /= 2;
  }
  ::sort(nodeDeg.begin(),
      nodeDeg.end()); // 调用系统函数sort，对节点按度从小到大排序
  ::nodeDeg_2_degArr_Sort(nodeDeg, degArrVal, degArrSize, degArrSum);
  return *this;
}
#endif // DEG_POISSON

// ******************************************************
#ifdef DEG_POWER
// 幂律度分布参数
//      power_gamma 幂指数
//      nodeSize    节点数目
//      kMin        最小度
//      kMax        最大度
Networks& Networks::degree_power_check_params(void)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (kMin > kMax || kMax >= nodeSize
      || (kMin == kMax && nodeSize % 2 == 1 && kMin % 2 == 1)
      || degree.power_gamma < 0) {
    runStatus = -1;
  }
  return *this;
}

// 生成度分布联合矩阵lkk
Networks& Networks::degree_power(void)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  // 生成度分布概率
  ::power_cal_degArrProb(
      degree.power_gamma, degArrVal, degArrProb, kMin, kMax);
  nodeDeg.resize(nodeSize);
  ::random_new_randKArr(&nodeDeg[0], (size_t)nodeSize, &degArrProb[0],
      &degArrVal[0], degArrVal.size()); // 调用通用随机函数
  // 修正度序列使总数为偶数
  if (::nodeDeg_2_linkSize(linkSize, nodeDeg) != 0) {
    ::fix_nodeDeg(nodeDeg, degArrProb, degArrVal, linkSize);
    linkSize /= 2;
  }
  ::sort(nodeDeg.begin(),
      nodeDeg.end()); // 调用系统函数sort，对节点按度从小到大排序
  ::nodeDeg_2_degArr_Sort(nodeDeg, degArrVal, degArrSize, degArrSum);
  return *this;
}

// 生成度分布
Networks& Networks::degree_power_arr(void)
{
  if (0 != runStatus) {
    ERROR();
    runStatus = -1;
    return *this;
  }
  if (0 >= kMin || kMin >= nodeSize) {
    ERROR();
    runStatus = -1;
    return *this;
  }

  if (kMax <= 0 || kMax >= nodeSize) {
    if (0
        != power_nature_cutoff(
               kMax, nodeSize, kMin, degree.power_gamma)) { // 最大度
      ERROR();
      runStatus = -1;
      return *this;
    }
  } else {
    if (kMax >= nodeSize)
      kMax = nodeSize - 1;
  }

  INFORM(kMax);

  //// 生成度分布概率
  //::power_cal_degArrProb(
  // degree.power_gamma, degArrVal, degArrProb, kMin, kMax);
  // INFORM();

  // 生成度分布
  //::power_cal_deg_arr(degArrSize, degArrVal, degArrProb, nodeSize);
  // INFORM();
  //::fix_degArr_kExtremum(degArrSize, degArrVal, degArrProb); // 去除0
  // INFORM();

  //// 修正度序列使总数为偶数
  // if (::degArr_2_linkSize(linkSize, degArrVal, degArrSize, dirFlag) != 0) {
  // INFORM();
  ////::fix_degArr_linkSize(degArrSize, degArrVal, degArrProb, linkSize);
  ////::common_sum_vector(degArrProb, degArrProbSum);
  ////::fix_degArr_linkSize2(degArrSize, degArrVal, degArrProbSum, linkSize);
  //::fix_degArr_linkSize3(degArrSize, degArrVal, degArrProb, linkSize);
  // linkSize /= 2;
  //}
  // INFORM();

  // 生成度分布
  degProbSum = 0;
  for (NodeType k = kMin; k <= kMax; ++k)
    degProbSum += net_degree::power_prob(k, degree.power_gamma);
  INFORM(degProbSum);
  const auto& r = degree.power_gamma;
  std::function<double(const NodeType)> prob_func
      = [r](const NodeType n) { return net_degree::power_prob(n, r); };
  net_degree::power_cal_deg_arr_func(
      nodeSize, kMin, kMax, prob_func, degProbSum, degArrVal, degArrSize);
  INFORM(degArrVal.size(), "\t", degArrSize.size());

  // 修正度序列使总数为偶数
  if (::degArr_2_linkSize(linkSize, degArrVal, degArrSize, dirFlag) != 0) {
    INFORM(linkSize);
    net_degree::fix_degArr_linkSize_lkk3_fast(
        degArrVal, degArrSize, linkSize);
    linkSize /= 2;
  }
  INFORM(linkSize);

  if (!degArrVal.empty() && 0 != fix_degArrSize_0(degArrSize, degArrVal)) {
    ERROR();
    runStatus = -1;
    return *this;
  }
  INFORM(degArrVal.size(), "\t", degArrSize.size());

  degMean = nodeSize > 0 ? (double)linkSize / nodeSize : 0;
  if (!dirFlag)
    degMean *= 2;

  return *this;
}

#endif // DEG_POWER

// ******************************************************
#endif // NET_DEGREE
