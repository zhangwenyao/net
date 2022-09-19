#ifndef STATISTICS__STAT_TEMPLATE_H_
#define STATISTICS__STAT_TEMPLATE_H_

#include "../common/common.h"
#include "stat.h"
#include <iostream>
#include <string>
#include <vector>
#ifdef STAT_STAT

// ******************************************************
template <typename T>
int network::statistics::mean(const char* prename, const char* sufname,
    const int seed_min, const int seed_max, const char* save_prename)
{
  std::string fn0 = prename, fn_full;
  std::vector<T> v;
  std::vector<double> m, m2;
  size_t l = 0, n = 0;
  if (seed_min <= seed_max) {
    int seed = seed_min;
    fn_full = fn0 + std::to_string(seed) + sufname;
    _ERR(0 != common::read1_0(fn_full.c_str(), v));
    l = v.size();
    m.assign(l, 0);
    m2.assign(l, 0);
    for (size_t i = 0; i < l; ++i) {
      m[i] = v[i];
      m2[i] = v[i] * v[i];
    }
    ++n;
  }
  for (int seed = seed_min + 1; seed <= seed_max; ++seed) {
    fn_full = fn0 + std::to_string(seed) + sufname;
    _ERR(0 != common::read1(fn_full.c_str(), v));
    for (size_t i = 0; i < l; ++i) {
      m[i] += v[i];
      m2[i] += v[i] * v[i];
    }
    ++n;
  }
  if (n > 0) {
    for (size_t i = 0; i < l; ++i) {
      m[i] /= n;
      m2[i] = sqrt(m2[i] / n - m[i] * m[i]);
    }
    fn_full = save_prename;
    common::save1((fn_full + ".mean.txt").c_str(), m);
    common::save1((fn_full + ".stdDev.txt").c_str(), m2);
  }
  return EXIT_SUCCESS;
}

template <typename T>
int network::statistics::mean2(const char* prename, const char* sufname,
    const int seed_min, const int seed_max, const char* save_prename)
{
  std::string fn0 = prename, fn_full;
  std::vector<std::vector<T>> v;
  std::vector<std::vector<T>> m, m2;
  size_t l = 0, n = 0;
  if (seed_min <= seed_max) {
    int seed = seed_min;
    fn_full = fn0 + std::to_string(seed) + sufname;
    _ERR(0 != common::read2_0(fn_full.c_str(), v));
    l = v.size();
    m.resize(l);
    for (size_t i = 0; i < l; ++i)
      m[i].assign(v[i].size(), 0);
    m2 = m;
  }
  for (int seed = seed_min; seed <= seed_max; ++seed) {
    fn_full = fn0 + std::to_string(seed) + sufname;
    _ERR(0 != common::read2(fn_full.c_str(), v));
    for (size_t i = 0; i < l; ++i) {
      for (size_t j = 0; j < v[i].size(); ++j) {
        m[i][j] += v[i][j];
        m2[i][j] += v[i][j] * v[i][j];
      }
    }
    ++n;
  }
  if (n > 0) {
    for (size_t i = 0; i < l; ++i) {
      for (size_t j = 0; j < v[i].size(); ++j) {
        m[i][j] /= n;
        m2[i][j] = sqrt(m2[i][j] / n - m[i][j] * m[i][j]);
      }
    }
    fn_full = save_prename;
    common::save2((fn_full + ".mean.txt").c_str(), m);
    common::save2((fn_full + ".stdDev.txt").c_str(), m2);
  }
  return EXIT_SUCCESS;
}

// ******************************************************
#endif
#endif // _H_
