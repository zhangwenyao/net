#ifndef COMMON__RANDOM_TEMPLATE_H_
#define COMMON__RANDOM_TEMPLATE_H_

#include "random.h"
#include <algorithm>
#include <functional>
#include <random>
#include <vector>

// **********************************************************
template <typename T>
int common::new_randKArr(
    T* a, const size_t n, const double* p, const size_t size)
{
  if (size <= 0)
    return -1;
  std::uniform_int_distribution<T> dis(0, size - 1);
  for (size_t i = 0, k; i < n; i++) {
    do {
      k = dis(rand2);
    } while (rand_double() > p[k]);
    *a++ = k;
  }
  return 0;
}

template <typename T>
int common::new_randKArr2(
    T* a, const size_t n, const double* p, const size_t size)
{
  typedef struct {
    double val;
    size_t left, right;
  } tree_data;
  if (size < 2)
    return -1;
  std::vector<tree_data> tree(size - 1);
  tree_data *tb = &tree[0], *ti = tb, *te = tb + size - 1;
  ti->val = p[0] + p[1];
  ti->left = size;
  ti->right = size + 1;
  for (const double* pe = p + size; p != pe;) {
    if (p[1] <= tb->val) {
      ti++->val = *p + p[1];
      p += 2;
    } else {
      ti->left = ti++->val = *p++ + tb++->val;
    }
  }

  std::uniform_int_distribution<T> dis(0, size - 1);
  for (size_t i = 0, k; i < n; i++) {
    do {
      k = dis(rand2);
    } while (rand_double() > p[k]);
    *a++ = k;
  }
  return 0;
}

template <typename T>
int common::new_randKArr(
    T* a, const size_t n, const double* p, const T* val, const size_t size)
{
  std::uniform_int_distribution<T> dis(0, size - 1);
  for (size_t i = 0, k; i < n; i++) {
    do {
      k = dis(rand2);
    } while (rand_double() > p[k]);
    *a++ = val[k];
  }
  return 0;
}

template <typename T>
int common::new_rankKArr(
    T* a, const size_t n, const double* p, const size_t size)
{
  T t;
  for (size_t i = 0, k; i < n; i++) {
    std::uniform_int_distribution<T> dis(i, size - 1);
    do {
      k = dis(rand2);
      t = a[k];
    } while (rand_double() > p[t]);
    a[k] = a[i];
    a[i] = t;
  }
  return 0;
}

template <typename T>
int common::new_rankKArrAll(T* a, const double* p, const size_t size)
{
  T t;
  if (size < 2)
    return 0;
  for (size_t i = 0, k; i < size - 1; i++) {
    std::uniform_int_distribution<T> dis(i, size - 1);
    do {
      k = dis(rand2);
      t = a[k];
    } while (rand_double() > p[t]);
    a[k] = a[i];
    a[i] = t;
  }
  return 0;
}

// a[n]中，产生m个不同的随机数
template <typename T>
int common::new_randArr(T* a, const size_t n, const size_t m)
{
  if (m <= 0)
    return 0;
  if (m > n)
    return -1;
  for (size_t i = 0; i < m; i++) {
    std::uniform_int_distribution<T> dis(i, n - 1);
    size_t r = dis(rand2);
    if (i != r) {
      T t = a[r];
      a[r] = a[i];
      a[i] = t;
    }
  }
  return 0;
}

template <typename T> int common::new_randArrAll(T* a, const size_t n)
{
  if (n <= 1)
    return 0;
  for (size_t i = 0; i < n - 1; i++) {
    std::uniform_int_distribution<T> dis(i, n - 1);
    size_t r = dis(rand2);
    if (i != r) {
      T t = a[r];
      a[r] = a[i];
      a[i] = t;
    }
  }
  return 0;
}

template <typename T>
int common::new_rankArr(T* a, const size_t n, const size_t m)
{
  if (m <= 0)
    return 0;
  if (m > n)
    return -1;
  for (size_t i = 0; i < m; i++) {
    std::uniform_int_distribution<T> dis(i, n - 1);
    size_t r = dis(rand2);
    if (i != r) {
      T t = a[r];
      a[r] = a[i];
      a[i] = t;
    }
  }
  std::sort(a, a + m);
  std::sort(a + m, a + n - m);
  return 0;
}

// **********************************************************
#endif // _H
