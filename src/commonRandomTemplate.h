#ifndef COMMON_RANDOM_TEMPLATE_H
#define COMMON_RANDOM_TEMPLATE_H

#include <algorithm>
#include <vector>
#include "commonRandom.h"

#ifdef RAND16807
extern int rand16807_val;
inline int rand16807(void) {
  const int m = 2147483647, a = 16807, q = 127773, r = 2836;
  rand16807_val = a * (rand16807_val % q) - r * (rand16807_val / q);
  if (rand16807_val < 0) {
    rand16807_val += m;
  }
  return rand16807_val;
}
#endif

//**//********************************************************//*
template <typename T>
int random_new_randKArr(T *a, const size_t n, const double *p,
                        const size_t size) {
  for (size_t i = 0, k; i < n; i++) {
    do {
      k = RAND2() % size;
    } while (FRAND2() > p[k]);
    *a++ = k;
  }
  return 0;
}

template <typename T>
int random_new_randKArr2(T *a, const size_t n, const double *p,
                         const size_t size) {
  typedef struct {
    double val;
    size_t left, right;
  } tree_data;
  if (size < 2) return -1;
  std::vector<tree_data> tree(size - 1);
  tree_data *tb = &tree[0], *ti = tb, *te = tb + size - 1;
  ti->val = p[0] + p[1];
  ti->left = size;
  ti->right = size + 1;
  for (const double *pe = p + size; p != pe;) {
    if (p[1] <= tb->val) {
      ti++->val = *p + p[1];
      p += 2;
    } else {
      ti->left = ti++->val = *p++ + tb++->val;
    }
  }

  for (size_t i = 0, k; i < n; i++) {
    do {
      k = RAND2() % size;
    } while (FRAND2() > p[k]);
    *a++ = k;
  }
  return 0;
}

template <typename T>
int random_new_randKArr(T *a, const size_t n, const double *p, const T *val,
                        const size_t size) {
  for (size_t i = 0, k; i < n; i++) {
    do {
      k = RAND2() % size;
    } while (FRAND2() > p[k]);
    *a++ = val[k];
  }
  return 0;
}

template <typename T>
int random_new_rankKArr(T *a, const size_t n, const double *p,
                        const size_t size) {
  T t;
  for (size_t i = 0, k; i < n; i++) {
    do {
      k = RAND2() % (size - i) + i;
      t = a[k];
    } while (FRAND2() > p[t]);
    a[k] = a[i];
    a[i] = t;
  }
  return 0;
}

template <typename T>
int random_new_rankKArrAll(T *a, const double *p, const size_t size) {
  T t;
  if (size < 2) return 0;
  for (size_t i = 0, k; i < size - 1; i++) {
    do {
      k = RAND2() % (size - i) + i;
      t = a[k];
    } while (FRAND2() > p[t]);
    a[k] = a[i];
    a[i] = t;
  }
  return 0;
}

// a[n]中，产生m个不同的随机数
template <typename T>
int random_new_randArr(T *a, const size_t n, const size_t m) {
  if (m <= 0) return 0;
  if (m > n) return -1;
  for (size_t i = 0; i < m; i++) {
    int r = RAND2() % (n - i) + i;
    if (i != r) {
      T t = a[r];
      a[r] = a[i];
      a[i] = t;
    }
  }
  return 0;
}

template <typename T>
int random_new_randArrAll(T *a, const size_t n) {
  if (n <= 1) return 0;
  for (size_t i = 0; i < n - 1; i++) {
    size_t r = RAND2() % (n - i) + i;
    if (i != r) {
      T t = a[r];
      a[r] = a[i];
      a[i] = t;
    }
  }
  return 0;
}

template <typename T>
int random_new_rankArr(T *a, const size_t n, const size_t m) {
  if (m <= 0) return 0;
  if (m > n) return -1;
  for (size_t i = 0; i < m; i++) {
    int r = RAND2() % (n - i) + i;
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

//**//********************************************************//*
#endif  // COMMON_RANDOM_TEMPLATE_H
