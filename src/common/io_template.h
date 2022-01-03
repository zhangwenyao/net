#ifndef COMMON__IO_TEMPLATE_H_
#define COMMON__IO_TEMPLATE_H_

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "debug.h"
#include "io.h"
#include "json.hpp"

// *********************************************************************
template <typename T>
inline T common::atoi(const char *s, const char c, const char base) {
  T t = 0;
  while (*s) t = t * base + *s++ - c;
  return t;
}

template <typename T>
inline size_t common::itoa(T i, char *s, const char c, const char base,
                           size_t n) {
  size_t l = 0;
  do {
    *s++ = c + i % base;
    i /= base;
    l++;
  } while (i);
  while (l < n--) *s++ = c;
  *s = '\0';
  return l;
}

template <typename T>
inline std::string dtoa(const T i) {
  std::stringstream ss;
  ss << i;
  return ss.str();
}

// *********************** common::save, common::read **********************
inline int common::read(const std::string &name, nlohmann::json &j) {
  return read(name.c_str(), j);
}

inline int common::save_json(const std::string &name, const nlohmann::json &j) {
  return save_json(name.c_str(), j);
}

// 一维数组 a[n]
template <typename T, const size_t n>
int common::save(std::ostream &os, T (&a)[n], const char c) {
  _ERR(!os);
  if (n > 0) {
    os << a[0];
    for (size_t i = 1; i < n; i++) os << c << a[i];
  }
  return 0;
}

template <typename T, const size_t n>
int common::save(const char *name, T (&a)[n], const char c) {
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::save(os, a, c);
  _ERR(0 != status);
  os.close();
  return status;
}

template <typename T, const size_t n>
int common::read(std::istream &is, T (&a)[n]) {
  _ERR(!is);
  size_t i = 0;
  while (i < n && is >> a[i]) i++;
  _ERR(i < n);
  return 0;
}

template <typename T, const size_t n>
int common::read(const char *name, T (&a)[n]) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read(is, a);
  _ERR(0 != status);
  is.close();
  return status;
}

// *a, n
template <typename T>
int common::save(std::ostream &os, T *a, const size_t n, const char c) {
  _ERR(!os);
  if (n > 0) {
    os << *a;
    for (size_t i = 1; i < n; i++) os << c << *++a;
  }
  return 0;
}

template <typename T>
int common::save(const char *name, T *a, const size_t n, const char c) {
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::save(os, a, n, c);
  _ERR(0 != status);
  os.close();
  return status;
}

template <typename T>
int common::read(std::istream &is, T *a, const size_t n) {
  _ERR(!is);
  size_t i = 0;
  while (i < n && is >> *a++) i++;
  _ERR(i < n);
  return 0;
}

template <typename T>
int common::read(const char *name, T *a, const size_t n) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read(is, a, n);
  _ERR(0 != status);
  is.close();
  return status;
}

template <typename T, typename T2>
int common::read0(std::istream &is, T *a, T2 &n) {
  _ERR(!is);
  n = 0;
  while (is >> *a++) n++;
  return 0;
}

template <typename T, typename T2>
int common::read0(const char *name, T *a, T2 &n) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read0(is, a, n);
  _ERR(0 != status);
  is.close();
  return status;
}

// a[p[i]]
template <typename T, typename T2>
int common::save1_p(std::ostream &os, T *a, T2 *p, const size_t n,
                    const char c) {
  _ERR(!os);
  if (n > 0) {
    os << a[p[0]];
    for (size_t i = 1; i < n; i++) os << c << a[p[i]];
  }
  return 0;
}

template <typename T, typename T2>
int common::save1_p(const char *name, T *a, T2 *p, const size_t n,
                    const char c) {
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::save1_p(os, a, p, n, c);
  _ERR(0 != status);
  os.close();
  return status;
}

template <typename T, typename T2>
int common::read1_p(std::istream &is, T *a, T2 *p, const size_t n) {
  _ERR(!is);
  size_t i = 0;
  while (i < n && is >> a[p[i]]) i++;
  _ERR(i < n);
  return 0;
}

template <typename T, typename T2>
int common::read1_p(const char *name, T *a, T2 *p, const size_t n) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read1_p(is, a, p, n);
  is.close();
  return status;
}

// a[0..n]
template <typename T>
int common::save1_head(std::ostream &os, T &a, const size_t n, const char c) {
  _ERR(!os);
  if (n > 0) {
    os << a[0];
    for (size_t i = 1; i < n; i++) os << c << a[i];
  }
  return 0;
}

template <typename T>
int common::save1_head(const char *name, T &a, const size_t n, const char c) {
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::save1_head(os, a, n, c);
  _ERR(0 != status);
  os.close();
  return status;
}

// *p, p[n1][n2]
template <typename T>
int common::save2(std::ostream &os, T *p, const size_t n1, const size_t n2,
                  const char c) {
  _ERR(!os);
  for (size_t i = 0; i < n1; i++) {
    if (n2 > 0) {
      os << *p++;
      for (size_t j = 1; j < n2; j++) os << c << *p++;
    }
    os << '\n';
  }
  return 0;
}

template <typename T>
int common::save2(const char *name, T *p, const size_t n1, const size_t n2,
                  const char c) {
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::save2(os, p, n1, n2, c);
  _ERR(0 != status);
  os.close();
  return status;
}

template <typename T>
int common::read2(const char *name, T *p, const size_t n1, const size_t n2) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read2(is, p, n1, n2);
  is.close();
  return status;
}

// 二维数组 a[n1][n2]
template <typename T, const size_t n1, const size_t n2>
std::ostream &operator<<(std::ostream &os, const T (&a)[n1][n2]) {
  if (!os) {
    ERROR();
    return os;
  }
  T(*pp)
  [n2] = a;
  for (size_t i = 0; i < n1; i++) {
    if (n2 > 0) {
      T *p = *pp++;
      os << *p;
      for (size_t j = 1; j < n2; j++) {
        os << '\t' << *++p;
      }
    }
    os << '\n';
  }
  return os;
}

template <typename T, const size_t n1, const size_t n2>
int common::save2(std::ostream &os, T (&a)[n1][n2], const char c) {
  _ERR(!os);
  T(*pp)
  [n2] = a;
  for (size_t i = 0; i < n1; i++) {
    if (n1 > 0) {
      T *p = *pp++;
      os << *p;
      for (size_t j = 1; j < n2; j++) os << c << *++p;
    }
    os << '\n';
  }
  return 0;
}

template <typename T, const size_t n1, const size_t n2>
int common::save2(const char *name, T (&a)[n1][n2], const char c) {
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::save2(os, a, c);
  _ERR(0 != status);
  os.close();
  return status;
}

template <typename T, const size_t n1, const size_t n2>
std::istream &operator>>(std::istream &is, T (&a)[n1][n2]) {
  if (!is) {
    ERROR();
    return is;
  }
  T(*pp)
  [n2] = a;
  size_t i = 0;
  for (; i < n1 && is; i++) {
    T *p = *pp++;
    size_t j = 0;
    while (j < n2 && is >> *p++) j++;
    _INF(j < n2);
  }
  _INF(i < n1);
  return is;
}

template <typename T, const size_t n1, const size_t n2>
int common::read2(std::istream &is, T (&a)[n1][n2]) {
  _ERR(!is);
  T(*pp)
  [n2] = a;
  size_t i = 0;
  for (; i < n1 && is; i++) {
    T *p = *pp++;
    size_t j = 0;
    while (j < n2 && is >> *p++) j++;
    _INF(j < n2);
  }
  _INF(i < n1);
  return 0;
}

template <typename T, const size_t n2, const size_t n1>
int common::read2(const char *name, T (&a)[n2][n1]) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read2(is, a);
  is.close();
  return status;
}

// a[n][size[n]], size[n]
template <typename T, typename T2, const size_t n>
int common::save2_size(std::ostream &os, T *(&a)[n], T2 (&size)[n],
                       const char c) {
  _ERR(!os);
  T **pa = a;
  T2 *ps = size;
  for (size_t i = 0; i < n; ps++, pa++, i++) {
    if (*ps > 0) {
      T *t = *pa;
      os << *t;
      for (size_t j = 1; j < *ps; j++) os << c << *++t;
    }
    os << '\n';
  }
  return 0;
}

template <typename T, typename T2, const size_t n>
int common::save2_size(const char *name, T *(&a)[n], T2 (&size)[n],
                       const char c) {
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::save2_size(os, a, size, c);
  os.close();
  return status;
}

template <typename T, typename T2, const size_t n>
int common::read2_size(std::istream &is, T *(&a)[n], T2 (&size)[n]) {
  T **pa = a;
  T2 *ps = size;
  size_t i;
  for (i = 0; i < n && is; ps++, pa++, i++) {
    T *t = *pa;
    for (size_t j = 0; j < *ps && is; j++) {
      is >> *t++;
    }
  }
  if (i < n || !is) {
    return -1;
  }
  return 0;
}

template <typename T, typename T2, const size_t n>
int common::read2_size(const char *name, T *(&a)[n], T2 (&size)[n]) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read2_size(is, a, size);
  is.close();
  return status;
}

// *a, *size, n
template <typename T, typename T2>
int common::save2_size(std::ostream &os, T **a, T2 *size, const size_t n,
                       const char c) {
  _ERR(!os);
  for (size_t i = 0; i < n; size++, a++, i++) {
    if (*size > 0) {
      T *t = *a;
      os << *t;
      for (size_t j = 1; j < *size; j++) os << c << *++t;
    }
    os << '\n';
  }
  return 0;
}

template <typename T, typename T2>
int common::save2_size(const char *name, T **a, T2 *size, const size_t n,
                       const char c) {
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::save2_size(os, a, size, n, c);
  _ERR(0 != status);
  os.close();
  return status;
}

template <typename T, typename T2>
int common::read2_size(std::istream &is, T **a, T2 *size, const size_t n) {
  _ERR(!is);
  size_t i;
  for (i = 0; i < n && is; size++, a++, i++) {
    T *t = *a;
    size_t j = 0;
    while (j < *size && is >> *t++) j++;
    _ERR(j < *size);
  }
  _ERR(i < n);
  return 0;
}

template <typename T, typename T2>
int common::read2_size(const char *name, T **a, T2 *size, const size_t n) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read2_size(is, a, size, n);
  is.close();
  return status;
}

template <typename T, typename T2>
int common::read2_0_size(std::istream &is, T *a, T2 *size, T2 *n) {
  _ERR(!is);
  std::string s;
  std::istringstream istr;
  T t;
  *n = 0;
  while (is) {
    getline(is, s);
    if (!is) {
      break;
    }
    istr.clear();
    for (istr.str(s), *size = 0; istr; (*size)++) {
      istr >> t;
      if (!istr) {
        break;
      }
      *a++ = t;
    }
    (*n)++;
    size++;
  }
  return 0;
}

template <typename T, typename T2>
int common::read2_0_size(const char *name, T *a, T2 *size, T2 *n) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read2_0_size(is, a, size, n);
  is.close();
  return status;
}

template <typename T, typename T2>
int common::read2_0_size(std::istream &is, T **a, T2 *size, T2 *n) {
  _ERR(!is);
  std::string s;
  std::istringstream istr;
  T t, *p;
  *n = 0;
  while (is) {
    getline(is, s);
    if (!is) {
      break;
    }
    p = a[*n];
    istr.clear();
    for (istr.str(s), *size = 0; istr; (*size)++) {
      istr >> t;
      if (!istr) {
        break;
      }
      *p++ = t;
    }
    (*n)++;
    size++;
  }
  return 0;
}

template <typename T, typename T2>
int common::read2_0_size(const char *name, T **a, T2 *size, T2 *n) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read2_0_size(is, a, size, n);
  is.close();
  return status;
}

// *a, n1, n2
template <typename T>
int common::save2_1(std::ostream &os, const T &a, const size_t n1,
                    const size_t n2, const char c) {
  auto *p = &a[0];
  for (size_t i = 0; i < n1; i++) {
    if (n2 > 0) {
      os << *p++;
      for (size_t j = 1; j < n2; j++) os << c << *p++;
    }
    os << '\n';
  }
  return 0;
}
template <typename T>
int common::save2_1(const char *name, const T &a, const size_t n1,
                    const size_t n2, const char c) {
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::save2_1(os, a, n1, n2, c);
  _ERR(0 != status);
  os.close();
  return status;
}

template <typename T>
int common::read2_1(std::istream &is, T &a, const size_t n1, const size_t n2) {
  _ERR(!is);
  size_t i;
  auto *p = &a[0];
  for (i = 0; i < n1 && is; i++) {
    size_t j = 0;
    while (j < n2 && is >> *p++) j++;
    _ERR(j < n2);
  }
  _ERR(i < n1);
  return 0;
}

template <typename T>
int common::read2_1(const char *name, T &a, const size_t n1, const size_t n2) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read2_1(is, a, n1, n2);
  is.close();
  return status;
}

// **a, n1, n2
template <typename T>
int common::save2(std::ostream &os, T **a, const size_t n1, const size_t n2,
                  const char c) {
  for (size_t i = 0; i < n1; i++) {
    if (n2 > 0) {
      T *p = a[i];
      os << *p++;
      for (size_t j = 1; j < n2; j++) os << c << *p++;
    }
    os << '\n';
  }
  return 0;
}
template <typename T>
int common::save2(const char *name, T **a, const size_t n1, const size_t n2,
                  const char c) {
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::save2(os, a, n1, n2, c);
  _ERR(0 != status);
  os.close();
  return status;
}

template <typename T>
int common::read2(std::istream &is, T **a, const size_t n1, const size_t n2) {
  _ERR(!is);
  size_t i;
  for (i = 0; i < n1 && is; i++) {
    T *p = a[i];
    size_t j = 0;
    while (j < n2 && is >> *p++) j++;
    _ERR(j < n2);
  }
  _ERR(i < n1);
  return 0;
}

template <typename T>
int common::read2(const char *name, T **a, const size_t n1, const size_t n2) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read2(is, a, n1, n2);
  is.close();
  return status;
}

// vector<> v
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
  if (!os) {
    ERROR();
    return os;
  }
  if (!v.empty()) {
    os << v[0];
    for (size_t i = 1; i < v.size(); i++) {
      os << '\t' << v[i];
    }
  }
  return os;
}

template <typename T>
int common::save1(std::ostream &os, const std::vector<T> &v, const char c) {
  _ERR(!os);
  if (!v.empty()) {
    os << v[0];
    for (size_t i = 1; i < v.size(); ++i) {
      os << c << v[i];
    }
  }
  return 0;
}

template <typename T>
int common::save1(const char *name, const std::vector<T> &v, const char c) {
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::save1(os, v, c);
  _ERR(0 != status);
  os.close();
  return status;
}

template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
  if (!is) {
    ERROR();
    return is;
  }
  for (auto &i : v) {
    is >> i;
  }
  return is;
}

template <typename T>
int common::read1(std::istream &is, std::vector<T> &v) {
  _ERR(!is);
  for (auto &i : v) is >> i;
  return 0;
}

template <typename T>
int common::read1(const char *name, std::vector<T> &v) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read1(is, v);
  is.close();
  return status;
}

template <typename T>
int common::read1_0(std::istream &is, std::vector<T> &v, unsigned n) {
  _ERR(!is);
  v.clear();
  if (n == 0) {
    for (T t; is >> t;) v.push_back(t);
  } else {
    for (T t; n > 0 && is >> t; --n) v.push_back(t);
  }
  return 0;
}

template <typename T>
int common::read1_0(const char *name, std::vector<T> &v, unsigned n) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read1_0(is, v, n);
  is.close();
  return status;
}

// vv
template <typename T>
std::ostream &operator<<(std::ostream &os,
                         const std::vector<std::vector<T>> &v) {
  if (!os) {
    ERROR();
    return os;
  }
  for (auto &i : v) os << i << '\n';
  return os;
}

template <typename T>
int common::save2(std::ostream &os, const std::vector<std::vector<T>> &v,
                  const char c) {
  _ERR(!os);
  for (auto &i : v) {
    common::save1(os, i, c);
    os << '\n';
  }
  return 0;
}

template <typename T>
int common::save2(const char *name, const std::vector<std::vector<T>> &v,
                  const char c) {
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::save2(os, v, c);
  os.close();
  return status;
}

template <typename T>
std::istream &operator>>(std::istream &is, std::vector<std::vector<T>> &v) {
  if (!is) {
    ERROR();
    return is;
  }
  for (auto &i : v) is >> i;
  return is;
}

template <typename T>
int common::read2(std::istream &is, std::vector<std::vector<T>> &v) {
  _ERR(!is);
  for (auto &i : v) common::read1(is, i);
  return 0;
}

template <typename T>
int common::read2(const char *name, std::vector<std::vector<T>> &v) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  for (auto &i : v) common::read1(is, i);
  is.close();
  return 0;
}

template <typename T>
int common::read2_0(std::istream &is, std::vector<std::vector<T>> &v) {
  _ERR(!is);
  std::string s;
  std::istringstream istr;
  T t;
  v.clear();
  while (1) {
    getline(is, s);
    if (!is) break;
    istr.clear();
    istr.str(s);
    v.push_back(std::vector<T>());
    for (auto p = v.rbegin(); istr >> t;) p->push_back(t);
  }
  return 0;
}

template <typename T>
int common::read2_0(const char *name, std::vector<std::vector<T>> &v) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read2_0(is, v);
  is.close();
  return status;
}

template <typename T, typename T2>
int common::read2_len_n(std::istream &is, T &vv, const T2 &l, const size_t n) {
  _ERR(!is);
  for (size_t i = 0; i < n; ++i) {
    vv[i].resize(l[i]);
    read1(is, vv[i]);
  }
  return 0;
}

template <typename T, typename T2>
int common::read2_len_n(const char *name, T &vv, const T2 &l, const size_t n) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  common::read2_len_n(is, vv, l, n);
  is.close();
  return 0;
}

template <typename T1, typename T2>
int common::read0(std::istream &is, std::map<T1, T2> &m) {
  _ERR(!is);
  T1 t1;
  T2 t2;
  m.clear();
  while (is >> t1 >> t2) {
    m[t1] = t2;
  }
  return 0;
}

template <typename T1, typename T2>
int common::read0(const char *name, std::map<T1, T2> &m) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read0<T1, T2>(is, m);
  is.close();
  return status;
}

template <typename T1, typename T2>
int common::read0(std::istream &is, std::vector<std::set<T2>> &s,
                  const std::map<T1, T2> &u, const std::map<T1, T2> &v) {
  _ERR(!is);
  T1 t1, t2;
  while (is >> t1 >> t2) {
    s[u.at(t1)].insert(v.at(t2));
  }
  return 0;
}

template <typename T1, typename T2>
int common::read0(const char *name, std::vector<std::set<T2>> &s,
                  const std::map<T1, T2> &u, const std::map<T1, T2> &v) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read0<T1, T2>(is, s, u, v);
  is.close();
  return status;
}
template <typename T1, typename T2>
int common::read0(std::istream &is, std::vector<std::vector<T2>> &s,
                  const std::map<T1, T2> &u, const std::map<T1, T2> &v) {
  _ERR(!is);
  T1 t1, t2;
  while (is >> t1 >> t2) {
    s[u.at(t1)].push_back(v.at(t2));
  }
  return 0;
}

template <typename T1, typename T2>
int common::read0(const char *name, std::vector<std::vector<T2>> &s,
                  const std::map<T1, T2> &u, const std::map<T1, T2> &v) {
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::read0<T1, T2>(is, s, u, v);
  is.close();
  return status;
}

template <typename T>
int common::save_double(std::ostream &os, const T &ds, const char c,
                        const int l) {
  os.precision(l);
  return common::save(os, ds, c);
}

template <typename T>
int common::save_double(const char *name, const T &ds, const char c,
                        const int l) {
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::save_double(os, ds, c, l);
  os.close();
  return status;
}

template <typename T>
int common::save1_double(std::ostream &os, const T &ds, const char c,
                         const int l) {
  os.precision(l);
  return common::save1(os, ds, c);
}

template <typename T>
int common::save1_double(const char *name, const T &ds, const char c,
                         const int l) {
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::save1_double(os, ds, c, l);
  os.close();
  return status;
}

template <typename T>
int common::save2_double(std::ostream &os, const T &ds, const char c,
                         const int l) {
  os.precision(l);
  return common::save2(os, ds, c, l);
}

template <typename T>
int common::save2_double(const char *name, const T &ds, const char c,
                         const int l) {
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common::save2_double(os, ds, c, l);
  os.close();
  return status;
}

// *********************** common::save, common::read **********************
template <typename T, typename... Argv>
inline int common::ssave_string(const std::string &name, T &&a, Argv... argv) {
  return save_string(name.c_str(), a, argv...);
}

template <typename T, typename... Argv>
inline int common::ssave(const std::string &name, T &&a, Argv... argv) {
  return save(name.c_str(), a, argv...);
}
template <typename T, typename... Argv>
inline int common::sread(const std::string &name, T &&a, Argv... argv) {
  return read(name.c_str(), a, argv...);
}
template <typename T, typename... Argv>
inline int common::sread0(const std::string &name, T &&a, Argv... argv) {
  return read0(name.c_str(), a, argv...);
}

template <typename T, typename... Argv>
inline int common::ssave1_p(const std::string &name, T &&a, Argv... argv) {
  return save1_p(name.c_str(), a, argv...);
}
template <typename T, typename... Argv>
inline int common::sread1_p(const std::string &name, T &&a, Argv... argv) {
  return read1_p(name.c_str(), a, argv...);
}

template <typename T, typename... Argv>
inline int common::ssave1(const std::string &name, T &&a, Argv... argv) {
  return save1(name.c_str(), a, argv...);
}
template <typename T, typename... Argv>
inline int common::sread1(const std::string &name, T &&a, Argv... argv) {
  return read1(name.c_str(), a, argv...);
}
template <typename T, typename... Argv>
inline int common::sread1_0(const std::string &name, T &&a, Argv... argv) {
  return read1_0(name.c_str(), a, argv...);
}

template <typename T, typename... Argv>
inline int common::ssave2(const std::string &name, T &&a, Argv... argv) {
  return save2(name.c_str(), a, argv...);
}
template <typename T, typename... Argv>
inline int common::sread2(const std::string &name, T &&a, Argv... argv) {
  return read2(name.c_str(), a, argv...);
}
template <typename T, typename... Argv>
int read2_0(const std::string &name, T &&a, Argv... argv) {
  return read2_0(name.c_str(), a, argv...);
}

template <typename T, typename... Argv>
inline int common::ssave2_size(const std::string &name, T &&a, Argv... argv) {
  return save2_size(name.c_str(), a, argv...);
}
template <typename T, typename... Argv>
inline int common::sread2_size(const std::string &name, T &&a, Argv... argv) {
  return read2_size(name.c_str(), a, argv...);
}
template <typename T, typename... Argv>
inline int common::sread2_0_size(const std::string &name, T &&a, Argv... argv) {
  return read2_0_size(name.c_str(), a, argv...);
}
template <typename T, typename... Argv>
inline int common::ssave_VString(const std::string &name, T &&a, Argv... argv) {
  return save_VString(name.c_str(), a, argv...);
}
template <typename T, typename... Argv>
inline int common::sread_VString(const std::string &name, T &&a, Argv... argv) {
  return read_VString(name.c_str(), a, argv...);
}
template <typename T, typename... Argv>
inline int common::ssave_double(const std::string &name, T &&a, Argv... argv) {
  return save_double(name.c_str(), a, argv...);
}
template <typename T, typename... Argv>
inline int common::ssave1_double(const std::string &name, T &&a, Argv... argv) {
  return save1_double(name.c_str(), a, argv...);
}
template <typename T, typename... Argv>
inline int common::ssave2_double(const std::string &name, T &&a, Argv... argv) {
  return save2_double(name.c_str(), a, argv...);
}

// *************************************************************
template <typename T1, typename T2, typename T3>
std::ostream &operator<<(std::ostream &os,
                         const std::vector<common::Struct3<T1, T2, T3>> &vs) {
  for (auto &i : vs) os << i << '\n';
  return os;
}

// *************************************************************
#endif  //_H
