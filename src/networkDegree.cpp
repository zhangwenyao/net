#include "net.h"
#ifdef NET_DEGREE

#include "common.h"
#include "NetDegree.h"
#include "networks.h"
using namespace std;

//**//****************************************************//*
Net_degree::Net_degree(void) {
#ifdef DEG_POISSON
  poisson_p = 0;
#endif

#ifdef DEG_POWER
  power_gamma = 0;
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
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int Net_degree::save_params(const char* name) const {
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

int Net_degree::save_data(const char* name) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  return 0;
}

int Net_degree::save(const char* name) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + "_degree_params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 != save_data((fn + "_degree").c_str())) {
    ERROR();
    return -1;
  }
  return 0;
}

int Net_degree::read_params_1(string& s, istream& is) {
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
  if (flag) s.clear();

  return 0;
}

//**//****************************************************//*
#ifdef DEG_POISSON
// Poisson度分布参数
//      poisson_p    连接概率p
//      nodeSize    网络节点数目
Networks& Networks::deg_poisson(void)  // 生成度序列 各点均按概率取任意度
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
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
  return *this;
}
#endif  // DEG_POISSON

//**//****************************************************//*
#ifdef DEG_POWER
// 幂律度分布参数
//      power_gamma 幂指数
//      nodeSize    节点数目
//      kMin        最小度
//      kMax        最大度
Networks& Networks::power_check_params(void) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (kMin > kMax || kMax >= nodeSize ||
      (kMin == kMax && nodeSize % 2 == 1 && kMin % 2 == 1) ||
      degree.power_gamma < 0) {
    runStatus = -1;
  }
  return *this;
}

// 生成度分布
Networks& Networks::deg_power(void) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
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
#endif  // DEG_POWER

//**//****************************************************//*
#endif  // NET_DEGREE
