#ifndef COMMON_TEMPLATE_H
#define COMMON_TEMPLATE_H

#include "common.debug.h"
#include "common.h"
#include <algorithm>
#include <stack>
#include <vector>

// *************************************************************
template <typename Tp> struct Common_RangeP {
  explicit Common_RangeP(Tp s = NULL, Tp e = NULL)
      : start(s)
      , end(e)
  {
  }
  Tp start, end;
};

template <typename T> bool common_find(const std::vector<T>& v, const T& t)
{
  return v.end() != find(v.begin(), v.end(), t);
}

template <typename T>
void common_find_common(
    const std::vector<T>& v1, const std::vector<T>& v2, std::vector<T>& v)
{
  typename std::vector<T>::const_iterator i1, i2;
  for (i1 = v1.begin(); i1 != v1.end(); ++i1)
    for (i2 = v2.begin(); i2 != v2.end(); ++i2)
      if (*i1 == *i2)
        v.push_back(*i1);
  return;
}

template <typename Tp, typename T2>
void common_sort_p_val_greater(Tp p, Tp p2, const T2* const val)
{
  if (p + 1 >= p2)
    return;
  std::stack<Common_RangeP<Tp>> st;
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
  std::stack<Common_RangeP<Tp>> st;
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

template <typename T, typename T2, typename T3>
int common_sort_rankV2(const T* const ranks, const T2 b, const T2 e, T3* v2)
{
  if (b >= e)
    return 0;
  for (T2 i = b, j; i < e;) {
    j = i + 1;
    while (j < e && ranks[*i] == ranks[*j])
      ++j;
    T3 t = (i - b) + (j - 1 - b);
    while (i < j) {
      *v2++ = t;
      i++;
    }
  }
  return 0;
}

template <typename T, typename T2>
int common_get_index(T b, const T e, T2* index)
{
  for (size_t i = 0; b < e;)
    index[*b++] = i++;
  return 0;
}

template <typename T, typename T2, typename T3>
int common_get_index_val(T b, const T e, T2* index, const T3* val)
{
  for (size_t i = 0; b < e;)
    index[*b++] = val[i++];
  return 0;
}

template <typename T, typename T2> // a[id] != 0 ==> id
void common_bool_2_index(const T* a, const size_t n, std::vector<T2>& id)
{
  for (size_t i = 0; i < n; i++) {
    if (*a++)
      id.push_back(i);
  }
}

template <typename T, typename T2>
void common_change_type_vector(const std::vector<T> v, std::vector<T2>& v2)
{
  v2.resize(v.size());
  for (size_t i = 0; i < v.size(); ++i)
    v2[i] = (T2)v[i];
  return;
}

template <typename T, typename T2>
void common_change_type_vector2(
    const std::vector<std::vector<T>> v, std::vector<std::vector<T2>>& v2)
{
  v2.resize(v.size());
  for (size_t i = 0; i < v.size(); ++i)
    common_change_type_vector(v[i], v2[i]);
  return;
}

// *************************************************************
template <typename T, typename T2, typename T3>
void common_total_p(const T* a, const T2* p, const size_t n, T3& s)
{
  for (size_t i = 0; i < n; i++)
    s += a[*p++];
}

template <typename T, typename T2>
void common_total_bool(const std::vector<T>& a, T2& s)
{
  for (typename std::vector<T>::const_iterator i = a.begin(); i != a.end();
       i++)
    if (*i)
      s++;
}

template <typename T, typename T2>
void common_total_bool(const T* a, size_t n, T2& s)
{
  while (n-- > 0)
    if (*a++)
      s++;
}

template <typename T, typename T2, typename T3>
void common_total_p_bool(const T* a, const T2* p, size_t n, T3 s) // 求和
{
  while (n-- > 0)
    if (a[*p++])
      s++;
}

// *************************************************************
template <typename T> T common_GCD(T a, T b)
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

// *************************************************************
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
int common_matrixCross(const std::vector<std::vector<T>>& a,
    const std::vector<std::vector<T>>& b, std::vector<std::vector<T>>& c)
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
int common_matrixCross_p2p(const std::vector<std::vector<T2>>& p2p,
    const std::vector<std::vector<T>>& a,
    const std::vector<std::vector<T>>& b, std::vector<std::vector<T>>& c)
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
int common_matrixCross1_p2p(const std::vector<std::vector<T2>>& p2p,
    const std::vector<T>& a, std::vector<T>& c)
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

// *************************************************************
#endif //_H
