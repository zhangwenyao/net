#ifndef COMMON_TEMPLATE_H
#define COMMON_TEMPLATE_H

#include "common.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//**//************** INFO, SHOW_TIME *************//*
inline void SHOW_TIME(std::ostream& os)
{
  time_t timeNow = time(NULL);
  struct tm* timeLocal = localtime(&timeNow);
  (os ? os : std::cerr) << asctime(timeLocal);
  return;
}

#ifdef STD_CPP11
inline void ERRINFO()
{
  std::cerr << std::flush;
  return;
}

template <typename T, typename... Args>
inline void ERRINFO(T x, Args... args)
{
  std::cerr << x;
  ERRINFO(args...);
  return;
}

inline void INFO()
{
  std::cout << std::flush;
  return;
}

template <typename T, typename... Args>
inline void INFO(T x, Args... args)
{
  std::cout << x;
  INFO(args...);
  return;
}
#endif

//**//********************** common_save, common_read *********************//*
template <typename T, const size_t n>
int common_save(std::ostream& os, T (&a)[n], const char c)
{
  T* p = a;
  if (n > 0) {
    os << *p;
  }
  for (size_t i = 1; i < n; i++) {
    os << c << *++p;
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
  T* p = a;
  size_t i;
  for (i = 0; i < n && is; i++) {
    is >> *p++;
  }
  if (i < n || !is) {
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
    status = -1;
  }
  is.close();
  return status;
}

// *p, n
template <typename T>
int common_save(std::ostream& os, T* p, const size_t n, const char c)
{
  if (n > 0) {
    os << *p;
  }
  for (size_t i = 1; i < n; i++) {
    os << c << *++p;
  }
  return 0;
}

template <typename T>
int common_save(const char* name, T* p, const size_t n, const char c)
{
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  common_save(os, p, n, c);
  os.close();
  return 0;
}

template <typename T>
int common_read(std::istream& is, T* p, const size_t n)
{
  size_t i;
  for (i = 0; i < n && is; i++) {
    is >> *p++;
  }
  if (i < n || !is) {
    return -1;
  }
  return 0;
}

template <typename T>
int common_read(const char* name, T* p, const size_t n)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read(is, p, n);
  is.close();
  return status;
}

template <typename T, typename T2>
int common_read0(std::istream& is, T* p, T2* n)
{
  T t;
  *n = 0;
  while (is >> t) {
    *p++ = t;
    (*n)++;
  }
  return 0;
}

template <typename T, typename T2>
int common_read0(const char* name, T* p, T2* n)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read0(is, p, n);
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
    }
    for (size_t j = 1; j < n2; j++) {
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
  T(*pp)
  [n2] = a;
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

template <typename T, const size_t n2, const size_t n1>
int common_save2(std::ostream& os, T (&a)[n2][n1], const char c)
{
  T(*pp)
  [n2] = a;
  for (size_t i = 0; i < n1; i++) {
    if (n2 > 0) {
      T* p = *pp++;
      os << *p;
      for (size_t j = 1; j < n2; j++) {
        os << c << *++p;
      }
    }
    os << '\n';
  }
  return 0;
}

template <typename T, const size_t n2, const size_t n1>
int common_save2(const char* name, T (&a)[n2][n1], const char c)
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
  T(*pp)
  [n2] = a;
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
  T(*pp)
  [n2] = a;
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
int common_save2(std::ostream& os, T* (&a)[n], T2 (&size)[n], const char c)
{
  T** pa = a;
  T2* ps = size;
  for (size_t i = 0; i < n; ps++, pa++, i++) {
    T* t = *pa;
    if (*ps > 0) {
      os << *t;
    }
    for (size_t j = 1; j < *ps; j++) {
      os << c << *++t;
    }
    os << '\n';
  }
  return 0;
}

template <typename T, typename T2, const size_t n>
int common_save2(const char* name, T* (&a)[n], T2 (&size)[n], const char c)
{
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_save2(os, a, size, c);
  os.close();
  return status;
}

template <typename T, typename T2, const size_t n>
int common_read2(std::ostream& is, T* (&a)[n], T2 (&size)[n])
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
int common_read2(const char* name, T* (&a)[n], T2 (&size)[n])
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read2(is, a, size);
  is.close();
  return status;
}

//**a, *size, n
template <typename T, typename T2>
int common_save2(
    std::ostream& os, T** a, T2* size, const size_t n, const char c)
{
  for (size_t i = 0; i < n; size++, a++, i++) {
    T* t = *a;
    if (*size > 0) {
      os << *t;
    }
    for (size_t j = 1; j < *size; j++) {
      os << c << *++t;
    }
    os << '\n';
  }
  return 0;
}

template <typename T, typename T2>
int common_save2(
    const char* name, T** a, T2* size, const size_t n, const char c)
{
  std::ofstream os(name);
  if (!os) {
    ERROR("open file ", name);
    return -1;
  }
  common_save2(os, a, size, n, c);
  os.close();
  return 0;
}

template <typename T, typename T2>
int common_read2(std::istream& is, T** a, T2* size, const size_t n)
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
int common_read2(const char* name, T** a, T2* size, const size_t n)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read2(is, a, size, n);
  is.close();
  return status;
}

template <typename T, typename T2>
int common_read2_0(std::istream& is, T* a, T2* size, T2* n)
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
int common_read2_0(const char* name, T* a, T2* size, T2* n)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read2_0(is, a, size, n);
  is.close();
  return status;
}

template <typename T, typename T2>
int common_read2_0(std::istream& is, T** a, T2* size, T2* n)
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
int common_read2_0(const char* name, T** a, T2* size, T2* n)
{
  std::ifstream is(name);
  if (!is) {
    ERROR("open file ", name);
    return -1;
  }
  int status = common_read2_0(is, a, size, n);
  is.close();
  return status;
}

// **a, n1, n2
template <typename T>
int common_save2(
    std::ostream& os, T** a, const size_t n1, const size_t n2, const char c)
{
  for (size_t i = 0; i < n1; i++) {
    T* p = a[i];
    if (n2 > 0) {
      os << *p++;
    }
    for (size_t j = 1; j < n2; j++) {
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

template <typename T>
int common_read1(std::istream& is, std::vector<T>& v)
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

template <typename T>
int common_read1(const char* name, std::vector<T>& v)
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
  if (v.size() > 0)
    os << v[0];
  for (size_t i = 1; i < v.size(); i++) {
    os << '\n'
       << v[i];
  }
  return os;
}

template <typename T>
int common_save2(
    std::ostream& os, const std::vector<std::vector<T> >& v, const char c)
{
  if (v.size() > 0)
    common_save1(os, v[0], c);
  for (size_t i = 1; i < v.size(); i++) {
    os << '\n';
    common_save1(os, v[i], c);
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
//**//***********************************************************//*
template <typename Tp>
struct Common_RangeP {
  explicit Common_RangeP(Tp s = NULL, Tp e = NULL)
      : start(s)
      , end(e)
  {
  }
  Tp start, end;
};

template <typename Tp, typename T2>
void common_sort_p_val(Tp p, Tp p2, const T2* const val)
{
  if (p + 1 >= p2)
    return;
  std::stack<Common_RangeP<Tp> > st;
  st.push(Common_RangeP<Tp>(p, p2 - 1));
  while (!st.empty()) {
    Common_RangeP<Tp> range = st.top();
    st.pop();
    Tp start = range.start, end = range.end;
    if (val[*start] > val[*end])
      std::swap(*start, *end);
    if (start + 1 >= end)
      continue;
    T2 pivot = val[*(start + (end - start) / 2)];
    if (val[*start] > pivot)
      pivot = val[*start];
    else if (val[*end] < pivot)
      pivot = val[*end];
    while (start < end) {
      while (start < end && val[*start] <= pivot)
        start++;
      while (start < end && val[*end] >= pivot)
        end--;
      if (start < end)
        std::swap(*start++, *end--);
    }
    while (start > range.start && val[*start] >= pivot)
      start--;
    while (end < range.end && val[*end] <= pivot)
      end++;
    if (range.start + 1 <= start)
      st.push(Common_RangeP<Tp>(range.start, start));
    if (end + 1 <= range.end)
      st.push(Common_RangeP<Tp>(end, range.end));
  }
}

template <typename Tp, typename T2>
void common_sort_p_val_less(Tp p, Tp p2, const T2* const val)
{
  if (p + 1 >= p2)
    return;
  std::stack<Common_RangeP<Tp> > st;
  st.push(Common_RangeP<Tp>(p, p2 - 1));
  while (!st.empty()) {
    Common_RangeP<Tp> range = st.top();
    st.pop();
    Tp start = range.start, end = range.end;
    if (val[*start] < val[*end])
      std::swap(*start, *end);
    if (start + 1 >= end)
      continue;
    T2 pivot = val[*(start + (end - start) / 2)];
    if (val[*start] < pivot)
      pivot = val[*start];
    else if (val[*end] > pivot)
      pivot = val[*end];
    while (start < end) {
      while (start < end && val[*start] >= pivot)
        start++;
      while (start < end && val[*end] <= pivot)
        end--;
      if (start < end)
        std::swap(*start++, *end--);
    }
    while (start > range.start && val[*start] <= pivot)
      start--;
    while (end < range.end && val[*end] >= pivot)
      end++;
    if (range.start + 1 <= start)
      st.push(Common_RangeP<Tp>(range.start, start));
    if (end + 1 <= range.end)
      st.push(Common_RangeP<Tp>(end, range.end));
  }
}

//**//***********************************************************//*
template <typename T, typename T2>
// 求和
void common_total(const std::vector<T>& a, T2& s)
{
  s = 0;
  for (typename std::vector<T>::const_iterator i = a.begin(); i != a.end();
       i++)
    s += *i;
}

template <typename T, typename T2, typename T3>
// 求和
void common_total(const std::vector<T>& a, const std::vector<T2>& p, T3& s)
{
  s = 0;
  for (typename std::vector<T2>::const_iterator i = p.begin(); i != p.end();
       i++)
    s += a[*i];
}

//**//***********************************************************//*
template <typename T>
T common_GCD(T a, T b)
{
  if (a <= 0)
    return b;
  if (b <= 0)
    return a;
  if (a <= 1)
    return a;
  if (b <= 1)
    return b;
  while (1) {
    if ((a %= b) <= 0)
      return b;
    if ((b %= a) <= 0)
      return a;
  }
}

//**//***********************************************************//*
template <typename T>
bool common_compare_vector(const std::vector<T>& a, const std::vector<T>& b)
{ // a < b
  typename std::vector<T>::const_iterator ia = a.begin(), ib = b.begin();
  while (ia != a.end() && ib != b.end() && *ia == *ib) {
    ia++;
    ib++;
  }
  if (ia == a.end())
    return ib != b.end();
  return ib != b.end() && *ia < *ib;
}

template <typename T>
size_t common_vector_count_same(
    const std::vector<T>& a, const std::vector<T>& b)
{
  size_t n = 0;
  if (a.size() <= 0 || b.size() <= 0)
    return n;
  for (typename std::vector<T>::const_iterator i = a.begin(); i != a.end();
       i++) {
    const T iVal = *i;
    for (typename std::vector<T>::const_iterator j = b.begin(); j != b.end();
         j++) {
      if (*j == iVal)
        n++;
    }
  }
  return n;
}

template <typename T>
size_t common_vector_count_same_sort(
    const std::vector<T>& a, const std::vector<T>& b)
{
  size_t n = 0;
  if (a.size() <= 0 || b.size() <= 0)
    return n;
  for (typename std::vector<T>::const_iterator i = a.begin(), j = b.begin();
       i != a.end() && j != b.end();) {
    if (*i == *i) {
      i++;
      j++;
      n++;
    } else {
      if (*i < *j) {
        if (i + 1 != a.end())
          i++;
        else
          j++;
      } else {
        if (j + 1 != b.end())
          j++;
        else
          i++;
      }
    }
  }
  return n;
}

// c = a.b
template <typename T>
int common_matrixCross(const std::vector<std::vector<T> >& a,
    const std::vector<std::vector<T> >& b, std::vector<std::vector<T> >& c)
{
  const size_t NX = c.size(), NY = c[0].size();
  if (a.size() != NX || b.size() != NY) {
    ERROR();
    return -1;
  }
  for (size_t i = 0; i < NX; i++) {
    for (size_t j = 0; j < NY; j++) {
      c[i][j] = 0;
      for (size_t k = 0; k < a[i].size(); k++)
        c[i][j] += a[i][k] * b[k][j];
    }
  }
  return 0;
}

// c = a . p2p . b
template <typename T, typename T2>
int common_matrixCross_p2p(const std::vector<std::vector<T2> >& p2p, const std::vector<std::vector<T> >& a, const std::vector<std::vector<T> >& b, std::vector<std::vector<T> >& c)
{
  const size_t NX = c.size(), NY = c[0].size();
  if (p2p.size() < NX || a.size() < NX || b[0].size() < NY) {
    ERROR();
    return -1;
  }
  for (size_t i = 0; i < NX; i++) {
    for (size_t j = 0; j < NY; j++) {
      c[i][j] = 0;
      for (size_t kk = 0; kk < p2p[i].size(); kk++) {
        const size_t k = p2p[i][kk];
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return 0;
}

// c = p2p . a
template <typename T, typename T2>
int common_matrixCross1_p2p(const std::vector<std::vector<T2> >& p2p, const std::vector<T>& a, std::vector<T>& c)
{
  const size_t NX = c.size();
  if (p2p.size() < NX || a.size() < NX) {
    ERROR();
    return -1;
  }
  for (size_t i = 0; i < NX; i++) {
    c[i] = 0;
    for (size_t j = 0; j < p2p[i].size(); j++) {
      c[i] += a[p2p[i][j]];
    }
  }

  return 0;
}

//**//***********************************************************//*
#endif // COMMON_TEMPLATE_H
