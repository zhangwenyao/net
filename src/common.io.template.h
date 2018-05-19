#ifndef COMMON_IO_TEMPLATE_H
#define COMMON_IO_TEMPLATE_H

#include "common.debug.h"
#include "common.io.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// *********************************************************************
template <typename T>
inline T common_atoi(char* s, const char c, const char base)
{
  T t = 0;
  while (*s)
    t = t * base + *s++ - c;
  return t;
}

// *********************** common_save, common_read **********************
// 一维数组a[n]
template <typename T, const size_t n>
int common_save(std::ostream& os, T (&a)[n], const char c)
{
  if (n > 0) {
    os << a[0];
    for (size_t i = 1; i < n; i++)
      os << c << a[i];
  }
  return 0;
}

template <typename T, const size_t n>
int common_save(const char* name, T (&a)[n], const char c)
{
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  common_save(os, a, c);
  os.close();
  return 0;
}

template <typename T, const size_t n>
int common_read(std::istream& is, T (&a)[n])
{
  size_t i = 0;
  while (i < n && is >> a[i])
    i++;
  if (i < n) {
    ERROR();
    return -1;
  }
  return 0;
}

template <typename T, const size_t n>
int common_read(const char* name, T (&a)[n])
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  common_read(is, a);
  int status = 0;
  if (!is) {
    ERROR();
    status = -1;
  }
  is.close();
  return status;
}

// *a, n
template <typename T>
int common_save(std::ostream& os, T* a, const size_t n, const char c)
{
  if (n > 0) {
    os << *a;
    for (size_t i = 1; i < n; i++)
      os << c << *++a;
  }
  return 0;
}

template <typename T>
int common_save(const char* name, T* a, const size_t n, const char c)
{
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  common_save(os, a, n, c);
  os.close();
  return 0;
}

template <typename T> int common_read(std::istream& is, T* a, const size_t n)
{
  size_t i;
  for (i = 0; i < n && is; i++)
    is >> *a++;
  if (i < n) {
    ERROR();
    return -1;
  }
  return 0;
}

template <typename T> int common_read(const char* name, T* a, const size_t n)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read(is, a, n);
  is.close();
  return status;
}

template <typename T, typename T2>
int common_read0(std::istream& is, T* a, T2& n)
{
  n = 0;
  for (T t; is >> t; n++)
    *a++ = t;
  return 0;
}

template <typename T, typename T2>
int common_read0(const char* name, T* a, T2& n)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read0(is, a, n);
  is.close();
  return status;
}

template <typename T>
int common_save_bool(
    std::ostream& os, const T* a, const size_t n, const char c)
{
  for (size_t i = 0, flag = 0; i < n; i++)
    if (*a++) {
      if (flag)
        os << c << i;
      else {
        os << i;
        flag = 1;
      }
    }
  return 0;
}

template <typename T>
int common_save_bool(
    const char* name, const T* a, const size_t n, const char c)
{
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  common_save_bool(os, a, n, c);
  os.close();
  return 0;
}

// a[p[i]]
template <typename T, typename T2>
int common_save1_p(std::ostream& os, T* a, T2* p, const size_t n, const char c)
{
  if (n > 0) {
    os << a[p[0]];
    for (size_t i = 1; i < n; i++)
      os << c << a[p[i]];
  }
  return 0;
}

template <typename T, typename T2>
int common_save1_p(const char* name, T* a, T2* p, const size_t n, const char c)
{
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  common_save1_p(os, a, p, n, c);
  os.close();
  return 0;
}

template <typename T, typename T2>
int common_read1_p(std::istream& is, T* a, T2* p, const size_t n)
{
  size_t i;
  for (i = 0; i < n && is; i++)
    is >> a[p[i]];
  if (i < n || !is) {
    ERROR();
    return -1;
  }
  return 0;
}

template <typename T, typename T2>
int common_read1_p(const char* name, T* a, T2* p, const size_t n)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read1_p(is, a, p, n);
  is.close();
  return status;
}

// *p, p[n1][n2]
template <typename T>
int common_save2(
    std::ostream& os, T* p, const size_t n1, const size_t n2, const char c)
{
  for (size_t i = 0; i < n1; i++) {
    if (n2 > 0) {
      os << *p++;
      for (size_t j = 1; j < n2; j++)
        os << c << *p++;
    }
    os << '\n';
  }
  return 0;
}

template <typename T>
int common_save2(
    const char* name, T* p, const size_t n1, const size_t n2, const char c)
{
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  common_save2(os, p, n1, n2, c);
  os.close();
  return 0;
}

template <typename T>
int common_read2(const char* name, T* p, const size_t n1, const size_t n2)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read2(is, p, n1, n2);
  is.close();
  return status;
}

template <typename T, typename T2>
int common_read2(const char* name, T* p, T2* n)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read2(is, p, n);
  is.close();
  return status;
}

// 二维数组a[n1][n2]
template <typename T, const size_t n1, const size_t n2>
std::ostream& operator<<(std::ostream& os, T (&a)[n1][n2])
{
  T(*pp)[n2] = a;
  for (size_t i = 0; i < n1; i++) {
    if (n2 > 0) {
      T* p = *pp++;
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
int common_save2(std::ostream& os, T (&a)[n1][n2], const char c)
{
  T(*pp)[n2] = a;
  for (size_t i = 0; i < n1; i++) {
    if (n1 > 0) {
      T* p = *pp++;
      os << *p;
      for (size_t j = 1; j < n2; j++)
        os << c << *++p;
    }
    os << '\n';
  }
  return 0;
}

template <typename T, const size_t n1, const size_t n2>
int common_save2(const char* name, T (&a)[n1][n2], const char c)
{
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  common_save2(os, a, c);
  os.close();
  return 0;
}

template <typename T, const size_t n1, const size_t n2>
std::istream& operator>>(std::istream& is, T (&a)[n1][n2])
{
  T(*pp)[n2] = a;
  for (size_t i = 0; i < n1 && is; i++) {
    T* p = *pp++;
    for (size_t j = 0; j < n2 && is; j++) {
      is >> *p++;
    }
  }
  return is;
}

template <typename T, const size_t n1, const size_t n2>
int common_read2(std::istream& is, T (&a)[n1][n2])
{
  T(*pp)[n2] = a;
  for (size_t i = 0; i < n1 && is; i++) {
    T* p = *pp++;
    for (size_t j = 0; j < n2 && is; j++) {
      is >> *p++;
    }
  }
  return 0;
}

template <typename T, const size_t n2, const size_t n1>
int common_read2(const char* name, T (&a)[n2][n1])
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read2(is, a);
  if (!is) {
    status = -1;
  }
  is.close();
  return status;
}

// a[n][size[n]], size[n]
template <typename T, typename T2, const size_t n>
int common_save2_size(
    std::ostream& os, T* (&a)[n], T2 (&size)[n], const char c)
{
  T** pa = a;
  T2* ps = size;
  for (size_t i = 0; i < n; ps++, pa++, i++) {
    if (*ps > 0) {
      T* t = *pa;
      os << *t;
      for (size_t j = 1; j < *ps; j++)
        os << c << *++t;
    }
    os << '\n';
  }
  return 0;
}

template <typename T, typename T2, const size_t n>
int common_save2_size(
    const char* name, T* (&a)[n], T2 (&size)[n], const char c)
{
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_save2_size(os, a, size, c);
  os.close();
  return status;
}

template <typename T, typename T2, const size_t n>
int common_read2_size(std::ostream& is, T* (&a)[n], T2 (&size)[n])
{
  T** pa = a;
  T2* ps = size;
  size_t i;
  for (i = 0; i < n && is; ps++, pa++, i++) {
    T* t = *pa;
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
int common_read2_size(const char* name, T* (&a)[n], T2 (&size)[n])
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read2_size(is, a, size);
  is.close();
  return status;
}

// *a, *size, n
template <typename T, typename T2>
int common_save2_size(
    std::ostream& os, T** a, T2* size, const size_t n, const char c)
{
  for (size_t i = 0; i < n; size++, a++, i++) {
    if (*size > 0) {
      T* t = *a;
      os << *t;
      for (size_t j = 1; j < *size; j++)
        os << c << *++t;
    }
    os << '\n';
  }
  return 0;
}

template <typename T, typename T2>
int common_save2_size(
    const char* name, T** a, T2* size, const size_t n, const char c)
{
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  common_save2_size(os, a, size, n, c);
  os.close();
  return 0;
}

template <typename T, typename T2>
int common_read2_size(std::istream& is, T** a, T2* size, const size_t n)
{
  size_t i;
  for (i = 0; i < n && is; size++, a++, i++) {
    T* t = *a;
    for (size_t j = 0; j < *size && is; j++) {
      is >> *t++;
    }
  }
  if (i < n || !is) {
    return -1;
  }
  return 0;
}

template <typename T, typename T2>
int common_read2_size(const char* name, T** a, T2* size, const size_t n)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read2_size(is, a, size, n);
  is.close();
  return status;
}

template <typename T, typename T2>
int common_read2_0_size(std::istream& is, T* a, T2* size, T2* n)
{
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
int common_read2_0_size(const char* name, T* a, T2* size, T2* n)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read2_0_size(is, a, size, n);
  is.close();
  return status;
}

template <typename T, typename T2>
int common_read2_0_size(std::istream& is, T** a, T2* size, T2* n)
{
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
int common_read2_0_size(const char* name, T** a, T2* size, T2* n)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read2_0_size(is, a, size, n);
  is.close();
  return status;
}

// **a, n1, n2
template <typename T>
int common_save2(
    std::ostream& os, T** a, const size_t n1, const size_t n2, const char c)
{
  for (size_t i = 0; i < n1; i++) {
    if (n2 > 0) {
      T* p = a[i];
      os << *p++;
      for (size_t j = 1; j < n2; j++)
        os << c << *p++;
    }
    os << '\n';
  }
  return 0;
}
template <typename T>
int common_save2(
    const char* name, T** a, const size_t n1, const size_t n2, const char c)
{
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  common_save2(os, a, n1, n2, c);
  os.close();
  return 0;
}

template <typename T>
int common_read2(std::istream& is, T** a, const size_t n1, const size_t n2)
{
  size_t i;
  for (i = 0; i < n1 && is; i++) {
    T* p = a[i];
    for (size_t j = 0; j < n2 && is; j++) {
      is >> *p++;
    }
  }
  if (i < n1 || !is) {
    return -1;
  }
  return 0;
}

template <typename T>
int common_read2(const char* name, T** a, const size_t n1, const size_t n2)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read2(is, a, n1, n2);
  is.close();
  return status;
}

// vector<> v
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
  if (!v.empty()) {
    os << v[0];
    for (size_t i = 1; i < v.size(); i++) {
      os << '\t' << v[i];
    }
  }
  return os;
}

template <typename T>
int common_save1(std::ostream& os, const std::vector<T>& v, const char c)
{
  if (!v.empty()) {
    os << v[0];
    for (size_t i = 1; i < v.size(); ++i) {
      os << c << v[i];
    }
  }
  return 0;
}

template <typename T>
int common_save1(const char* name, const std::vector<T>& v, const char c)
{
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  common_save1(os, v, c);
  os.close();
  return 0;
}

template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v)
{
  for (typename std::vector<T>::iterator i = v.begin(); i != v.end() && is;
       i++) {
    is >> *i;
  }
  return is;
}

template <typename T> int common_read1(std::istream& is, std::vector<T>& v)
{
  if (!is) {
    ERROR();
    return -1;
  }
  for (typename std::vector<T>::iterator i = v.begin(); i != v.end() && is;
       i++)
    is >> *i;
  return 0;
}

template <typename T> int common_read1(const char* name, std::vector<T>& v)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  common_read1(is, v);
  is.close();
  return 0;
}

template <typename T>
int common_read1_0(std::istream& is, std::vector<T>& v, const unsigned n)
{
  v.clear();
  if (n == 0) {
    for (T t; is >> t;)
      v.push_back(t);
  } else {
    std::string s;
    std::istringstream istr;
    T t;
    for (unsigned i = 0; i < n; i++) {
      getline(is, s);
      if (!is)
        return -1;
      istr.clear();
      istr.str(s);
      while (istr >> t)
        v.push_back(t);
    }
  }
  return 0;
}

template <typename T>
int common_read1_0(const char* name, std::vector<T>& v, const unsigned n)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read1_0(is, v, n);
  is.close();
  return status;
}

// vv
template <typename T>
std::ostream& operator<<(
    std::ostream& os, const std::vector<std::vector<T> >& v)
{
  for (size_t i = 0; i < v.size(); i++)
    os << v[i] << '\n';
  return os;
}

template <typename T>
int common_save2(
    std::ostream& os, const std::vector<std::vector<T> >& v, const char c)
{
  for (size_t i = 0; i < v.size(); i++) {
    common_save1(os, v[i], c);
    os << '\n';
  }
  return 0;
}

template <typename T>
int common_save2(
    const char* name, const std::vector<std::vector<T> >& v, const char c)
{
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  common_save2(os, v, c);
  os.close();
  return 0;
}

template <typename T>
std::istream& operator>>(std::istream& is, std::vector<std::vector<T> >& v)
{
  for (typename std::vector<std::vector<T> >::iterator i = v.begin();
       i != v.end() && is; i++) {
    is >> *i;
  }
  return is;
}

template <typename T>
int common_read2(std::istream& is, std::vector<std::vector<T> >& v)
{
  if (!is) {
    ERROR();
    return -1;
  }
  for (typename std::vector<std::vector<T> >::iterator i = v.begin();
       i != v.end() && is; i++) {
    common_read1(is, *i);
  }
  return 0;
}

template <typename T>
int common_read2(const char* name, std::vector<std::vector<T> >& v)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  for (typename std::vector<std::vector<T> >::iterator i = v.begin();
       i != v.end() && is; i++)
    common_read1(is, *i);
  is.close();
  return 0;
}

template <typename T>
int common_read2_0(std::istream& is, std::vector<std::vector<T> >& v)
{
  if (!is)
    return -1;
  std::string s;
  std::istringstream istr;
  typename std::vector<std::vector<T> >::reverse_iterator p;
  T t;
  v.clear();
  while (1) {
    getline(is, s);
    if (!is)
      break;
    istr.clear();
    istr.str(s);
    v.push_back(std::vector<T>());
    p = v.rbegin();
    while (istr >> t) {
      p->push_back(t);
    }
  }
  return 0;
}

template <typename T>
int common_read2_0(const char* name, std::vector<std::vector<T> >& v)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read2_0(is, v);
  is.close();
  return status;
}

// *************************************************************
#endif //_H
