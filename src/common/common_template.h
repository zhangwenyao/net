#ifndef COMMON__TEMPLATE_H_
#define COMMON__TEMPLATE_H_

#include "common.h"
#include "debug.h"
#include "io.h"
#include <algorithm>
#include <stack>
#include <vector>

// **********************************************************
template <typename T1, typename T2, typename T3> struct common::Struct3 {
  T1 x;
  T2 y;
  T3 val;
};

template <typename T1, typename T2, typename T3>
std::ostream& operator<<(
    std::ostream& os, const common::Struct3<T1, T2, T3>& r)
{
  os << r.x << '\t' << r.y << '\t' << r.val;
  return os;
};

template <typename T1, typename T2, typename T3>
std::istream& operator>>(std::istream& is, common::Struct3<T1, T2, T3>& r)
{
  is >> r.x >> r.y >> r.val;
  return is;
};

// *************************************************************
template <typename T> struct common::Range {
  explicit Range(T s = 0, T e = 0)
      : start(s)
      , end(e)
  {
  }
  T start, end;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const common::Range<T>& r)
{
  os << r.start << '\t' << r.end;
  return os;
};

template <typename T>
std::istream& operator>>(std::istream& is, common::Range<T>& r)
{
  is >> r.x >> r.y;
  return is;
};

template <typename Tp> struct common::RangeP {
  explicit RangeP(Tp s = NULL, Tp e = NULL)
      : start(s)
      , end(e)
  {
  }
  Tp start, end;
};

template <typename T> bool common::find(const std::vector<T>& v, const T& t)
{
  return v.end() != find(v.begin(), v.end(), t);
}

template <typename T>
void common::find_common(
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
void common::sort_p_val_greater(Tp p, Tp p2, const T2* const val)
{
  if (p + 1 >= p2)
    return;
  std::stack<common::RangeP<Tp>> st;
  st.push(common::RangeP<Tp>(p, p2 - 1));
  while (!st.empty()) {
    common::RangeP<Tp> range = st.top();
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
      st.push(common::RangeP<Tp>(range.start, start));
    if (end + 1 <= range.end)
      st.push(common::RangeP<Tp>(end, range.end));
  }
}

template <typename Tp, typename T2>
void common::sort_p_val_less(Tp p, Tp p2, const T2* const val)
{
  if (p + 1 >= p2)
    return;
  std::stack<common::RangeP<Tp>> st;
  st.push(common::RangeP<Tp>(p, p2 - 1));
  while (!st.empty()) {
    common::RangeP<Tp> range = st.top();
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
      st.push(common::RangeP<Tp>(range.start, start));
    if (end + 1 <= range.end)
      st.push(common::RangeP<Tp>(end, range.end));
  }
}

template <typename T, typename T2, typename T3>
int common::sort_rankV2(const T* const ranks, const T2 b, const T2 e, T3* v2)
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
int common::get_index(T b, const T e, T2* index)
{
  for (size_t i = 0; b < e;)
    index[*b++] = i++;
  return 0;
}

template <typename T, typename T2, typename T3>
int common::get_index_val(T b, const T e, T2* index, const T3* val)
{
  for (size_t i = 0; b < e;)
    index[*b++] = val[i++];
  return 0;
}

template <typename T, typename T2> // a[id] != 0 ==> id
void common::bool_2_index(const T* a, const size_t n, std::vector<T2>& id)
{
  for (size_t i = 0; i < n; i++) {
    if (*a++)
      id.push_back(i);
  }
}

template <typename T, typename T2>
void common::change_type_vector(const std::vector<T> v, std::vector<T2>& v2)
{
  v2.resize(v.size());
  for (size_t i = 0; i < v.size(); ++i)
    v2[i] = (T2)v[i];
  return;
}

template <typename T, typename T2>
void common::change_type_vector2(
    const std::vector<std::vector<T>> v, std::vector<std::vector<T2>>& v2)
{
  v2.resize(v.size());
  for (size_t i = 0; i < v.size(); ++i)
    common::change_type_vector(v[i], v2[i]);
  return;
}

// *************************************************************
template <typename T, typename T2>
void common::total(const T* a, const size_t n, T2& s)
{
  for (size_t i = 0; i < n; ++i)
    s += *a++;
}

template <typename T, typename T2, typename T3>
void common::total_p(const T* a, const T2* p, const size_t n, T3& s)
{
  for (size_t i = 0; i < n; i++)
    s += a[*p++];
}

template <typename T, typename T2>
void common::total_bool(const std::vector<T>& a, T2& s)
{
  for (typename std::vector<T>::const_iterator i = a.begin(); i != a.end();
       i++)
    if (*i)
      s++;
}

template <typename T, typename T2>
void common::total_bool(const T* a, size_t n, T2& s)
{
  while (n-- > 0)
    if (*a++)
      s++;
}

template <typename T, typename T2, typename T3>
void common::total_p_bool(const T* a, const T2* p, size_t n, T3 s) // 求和
{
  while (n-- > 0)
    if (a[*p++])
      s++;
}

template <typename T, typename T2>
void common::sum_vector(
    const std::vector<T>& a, std::vector<T2>& s, const int fix)
{
  s.resize(a.size());
  T2 sum = 0;
  auto j = s.begin();
  for (auto i = a.begin(); i != a.end(); ++i, ++j) {
    sum += *i;
    *j = sum;
  }
  if (fix and sum != 0) {
    for (auto j = s.begin(); j != s.end(); ++j)
      *j /= sum;
  }
}
// *************************************************************
template <typename T> T common::GCD(T a, T b)
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
bool common::compare_vector(const std::vector<T>& a, const std::vector<T>& b)
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
size_t common::vector_count_same(
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
size_t common::vector_count_same_sort(
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
int common::matrixCross(const std::vector<std::vector<T>>& a,
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
int common::matrixCross_p2p(const std::vector<std::vector<T2>>& p2p,
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
int common::matrixCross1_p2p(const std::vector<std::vector<T2>>& p2p,
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
template <typename T1, typename T2, typename T3, typename T4>
int common::histogram(std::vector<double>& val, std::vector<double>& mean,
    std::vector<double>& deviation, std::vector<T1>& size,
    const std::vector<T2>& val_count, const std::vector<T3>& val0,
    const std::vector<T4>& size0, const double val_min, const double val_max,
    const size_t val_n)
{
  if (val_n <= 0 || val_min >= val_max)
    return -1;
  val.resize(val_n);
  mean.assign(val_n, 0);
  deviation.assign(val_n, 0);
  size.assign(val_n, 0);
  const double len = (val_max - val_min) / val_n;
  for (size_t i = 0; i < val_n; ++i)
    val[i] = val_min + len * (i + 0.5);
  size_t data_size = val0.size();
  if (data_size != size0.size() || data_size != val_count.size())
    return -1;
  if (data_size <= 0)
    return 0;
  for (size_t i = 0; i < data_size; ++i) {
    const T3 v = val0[i];
    if (val_min > v || v > val_max)
      continue;
    size_t n = (v - val_min) / len;
    if (n >= val_n)
      --n;
    const T4 s = size0[i];
    const double x = val_count[i];
    mean[n] += x * s;
    deviation[n] += x * x * s;
    size[n] += s;
  }
  for (size_t i = 0; i < val_n; ++i) {
    if (size[i] > 0) {
      mean[i] /= size[i];
      deviation[i] = deviation[i] / size[i] - mean[i] * mean[i];
      if (deviation[i] <= 0)
        deviation[i] = 0;
      else
        deviation[i] = sqrt(deviation[i]);
    }
  }
  return 0;
}

template <typename T1, typename T2, typename T3, typename T4>
int common::histogram_lg2(std::vector<double>& val, std::vector<double>& mean,
    std::vector<double>& deviation, std::vector<T1>& size,
    const std::vector<T2>& val_count, const std::vector<T3>& val0,
    const std::vector<T4>& size0)
{
  val.clear();
  mean.clear();
  deviation.clear();
  size.clear();
  size_t data_size = val0.size();
  if (data_size != size0.size() || data_size != val_count.size())
    return -1;
  if (data_size <= 0)
    return 0;
  size_t len = 1;
  T3 v0 = val0[0], v_max = v0 + len - 1;
  double sum = 0, sum2 = 0;
  size_t size_i = 0;
  for (size_t i = 0; i < data_size; ++i) {
    const T3 v = val0[i];
    const T4 s = size0[i];
    const double x = val_count[i];
    if (v <= v_max) {
      sum += x * s;
      sum2 += x * x * s;
      size_i += s;
    }
    if (v >= v_max || i + 1 >= data_size) {
      if (size_i > 0) {
        sum /= size_i;
        sum2 = sum2 / size_i - sum * sum;
        sum2 = sum2 <= 0 ? 0 : sqrt(sum2);
      }
      val.push_back(sqrt(double(v0) * v_max));
      mean.push_back(sum);
      deviation.push_back(sum2);
      size.push_back(size_i);
      v0 += len;
      len *= 2;
      v_max = v0 + len - 1;
      sum = 0;
      sum2 = 0;
      size_i = 0;
    }
  }
  return 0;
}

// *************************************************************
#endif //_H
