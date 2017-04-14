#include "networkDegree.h"
#ifdef NET_DEGREE

#include "NetDegree.h"
#include "common.h"
using namespace std;

//**//****************************************************//*
Net_degree::Net_degree(void) {
#ifdef DEG_POISSON
  poisson_p = 0.1;
#endif

#ifdef DEG_POWER
  power_gamma = 2.5;
#endif
}

std::ostream& operator<<(std::ostream& os, const Net_degree& degree) {
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

int Net_degree::save_params(std::ostream& os) const {
  os << *this;
  return 0;
}

int Net_degree::save_params(const char* name) const { return 0; }
int Net_degree::save_data(const char* name) { return 0; }
int Net_degree::save(const char* name) { return 0; }

int Net_degree::read_params_1(string& s, istream& is) { return 0; }

//**//****************************************************//*
#ifdef DEG_POISSON
Networks& Networks::deg_poisson(void)  // 生成度序列 各点均按概率取任意度
{
  // 生成度分布概率
  ::poisson_cal_degArr(degree.poisson_p, degArrVal, degArrProb, kMin, kMax,
                       nodeSize);
  nodeDeg.resize(nodeSize);
  ::random_new_randKArr(&nodeDeg[0], (size_t)nodeSize, &degArrProb[0],
                        &degArrVal[0],
                        degArrVal.size());  // 调用通用随机函数
  // 修正度序列使总数为偶数
  if (::nodeDeg_2_linkSize(linkSize, nodeDeg) != 0) {
    ::fix_nodeDeg(nodeDeg, degArrProb, degArrVal, linkSize);
    linkSize /= 2;
  }
  ::sort(nodeDeg.begin(),
         nodeDeg.end());  // 调用系统函数sort，对节点按度从小到大排序
  ::nodeDeg_2_degArr_Sort(nodeDeg, degArrVal, degArrSize, degArrSum);
  return 0;
}

//**//****************************************************//*
int net_read_params_poisson(istream& is, Networks& net) {
  for (string s; is >> s;) {
    if (s == "--degree.poisson_p") {
      is >> net.degree.poisson_p;
      cout << s << '\t' << net.degree.poisson_p << endl;
      continue;
    }
  }
  return 0;
}

int net_save_params_poisson(ostream& os, const Networks& net) {
  if (!os) return -1;
  os << "--degree.poisson_p\t" << net.degree.poisson_p << '\n';
  return 0;
}

#endif  // DEG_POISSON

//**//****************************************************//*
#ifdef DEG_POWER
Networks& Networks::power_check_params(void) {
  if (kMin > kMax || kMax >= nodeSize ||
      (kMin == kMax && nodeSize % 2 == 1 && kMin % 2 == 1) ||
      degree.power_gamma < 0) {
    runStatus = -1;
  }
  return *this;
}

// 生成度分布
Networks& Networks::deg_power(void) {
  // 生成度分布概率
  ::power_cal_degArr(degree.power_gamma, degArrVal, degArrProb, kMin, kMax);
  nodeDeg.resize(nodeSize);
  ::random_new_randKArr(&nodeDeg[0], (size_t)nodeSize, &degArrProb[0],
                        &degArrVal[0],
                        degArrVal.size());  // 调用通用随机函数
  // 修正度序列使总数为偶数
  if (::nodeDeg_2_linkSize(linkSize, nodeDeg) != 0) {
    ::fix_nodeDeg(nodeDeg, degArrProb, degArrVal, linkSize);
    linkSize /= 2;
  }
  ::sort(nodeDeg.begin(),
         nodeDeg.end());  // 调用系统函数sort，对节点按度从小到大排序
  ::nodeDeg_2_degArr_Sort(nodeDeg, degArrVal, degArrSize, degArrSum);
  return *this;
}

//**//****************************************************//*
int net_read_params_power(istream& is, Networks& net) {
  for (string s; is >> s;) {
    if (s == "--degree.power_gamma") {
      is >> net.degree.power_gamma;
      cout << s << '\t' << net.degree.power_gamma << endl;
      continue;
    }
  }
  return 0;
}

int net_save_params_power(ostream& os, const Networks& net) {
  if (!os) return -1;
  os << "--degree.power_gamma\t" << net.degree.power_gamma << '\n';
  return 0;
}

#endif  // DEG_POWER

//**//****************************************************//*
#endif  // NET_DEGREE
