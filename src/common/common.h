#ifndef COMMON__COMMON_H_
#define COMMON__COMMON_H_

// g++ -std=c++11

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#define TOSTRING(x) _TOSTRING(x)
#define _TOSTRING(x) #x

namespace common {
// *************************************************************
template <typename T1, typename T2>
struct Struct2;
template <typename T1, typename T2, typename T3>
struct Struct3;

template <typename T>
struct Range;  // 范围结构
template <typename Tp>
struct RangeP;  // 范围结构

template <typename T, typename T2, typename T3>
int vector_2_map(const std::vector<T>& v, std::map<const T2, T3>& m);

// *************************************************************
template <typename T>
bool find(const std::vector<T>& v, const T& t);
template <typename T>
void find_common(const std::vector<T>& v1, const std::vector<T>& v2,
                 std::vector<T>& v);

// 按 val[p[i]] 大小对 p[i] 排序 [i<=i+1]
template <typename Tp, typename T2>
void sort_p_val_greater(Tp p, Tp p2, const T2* const val);

// 按 val[p[i]] 大小对 p[i] 排序 [i>=i+1]
template <typename Tp, typename T2>
void sort_p_val_less(Tp p, Tp p2, const T2* const val);

// #ifndef sort_p_val
// #define sort_p_val sort_p_val_greater
// #endif
template <typename... Args>
auto sort_p_val(Args&&... args)
    -> decltype(sort_p_val_greater(std::forward<Args>(args)...)) {
  return sort_p_val_greater(std::forward<Args>(args)...);
}

template <typename T, typename T2, typename T3>
int sort_rankV2(const T* const ranks, const T2 b, const T2 e, T3* v2);

template <typename T, typename T2>
int get_index(T b, const T e, T2* index);
template <typename T, typename T2, typename T3>
int get_index_val(T b, const T e, T2* index, const T3* val);

template <typename T, typename T2>  // a[id] != 0 ==> id
void bool_2_index(const T* a, const size_t n, std::vector<T2>& id);

void cstring_swap(char* a, char* b);
void cstring_reverse(char* a);

template <typename T, typename T2>
void change_type_vector(const std::vector<T> v, std::vector<T2>& v2);
template <typename T, typename T2>
void change_type_vector2(const std::vector<std::vector<T>> v,
                         std::vector<std::vector<T2>>& v2);

// *************************************************************
template <typename T, typename T2>
void total(const T* a, const size_t n, T2& s);

// s += a[p[i]] for i..n
template <typename T, typename T2, typename T3>
void total_p(const T* a, const T2* p, const size_t n, T3& s);

// for i, if a[i], s++
template <typename T, typename T2>
void total_bool(const std::vector<T>& a, T2& s);
template <typename T, typename T2>
void total_bool(const T* a, size_t n, T2& s);
// for i, if a[p[i] s++
template <typename T, typename T2, typename T3>
void total_p_bool(const T* a, const T2* p, size_t n, T3 s);

template <typename T, typename T2>
void sum_vector(const std::vector<T>& a, std::vector<T2>& s, const int fix = 1);

// *************************************************************
template <typename T>
bool compare_vector(const std::vector<T>& a, const std::vector<T>& b);

template <typename T>
size_t vector_count_same(const std::vector<T>& a, const std::vector<T>& b);
template <typename T>
size_t vector_count_same_sort(const std::vector<T>& a, const std::vector<T>& b);

template <typename T>
T GCD(T a, T b);  // 最大公约数

template <typename T>
int matrixCross(const std::vector<std::vector<T>>& a,
                const std::vector<std::vector<T>>& b,
                std::vector<std::vector<T>>& c);  // c = a.b

template <typename T, typename T2>
int matrixCross_p2p(const std::vector<std::vector<T2>>& p2p,
                    const std::vector<std::vector<T>>& a,
                    const std::vector<std::vector<T>>& b,
                    std::vector<std::vector<T>>& c);  // c = a . p2p . b

template <typename T, typename T2>
int matrixCross1_p2p(const std::vector<std::vector<T2>>& p2p,
                     const std::vector<T>& a,
                     std::vector<T>& c);  // c = p2p . a

// *************************************************************
template <typename T1, typename T2, typename T3, typename T4>
int histogram(std::vector<double>& val, std::vector<double>& mean,
              std::vector<double>& deviation, std::vector<T1>& size,
              const std::vector<T2>& val_count, const std::vector<T3>& val0,
              const std::vector<T4>& size0, const double val_min,
              const double val_max, const size_t val_n);
template <typename T1, typename T2, typename T3, typename T4>
int histogram_lg2(std::vector<double>& val, std::vector<double>& mean,
                  std::vector<double>& deviation, std::vector<T1>& size,
                  const std::vector<T2>& val_count, const std::vector<T3>& val0,
                  const std::vector<T4>& size0);

// *************************************************************
int mkdirs(const char* dirname = NULL);
}  // end namespace common

// *****************************************************
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const common::Struct2<T1, T2>& r);
template <typename T1, typename T2>
std::istream& operator>>(std::istream& is, common::Struct2<T1, T2>& r);

template <typename T1, typename T2, typename T3>
std::ostream& operator<<(std::ostream& os,
                         const common::Struct3<T1, T2, T3>& r);
template <typename T1, typename T2, typename T3>
std::istream& operator>>(std::istream& is, common::Struct3<T1, T2, T3>& r);

template <typename T>
std::ostream& operator<<(std::ostream& os, const common::Range<T>& r);
template <typename T>
std::istream& operator>>(std::istream& is, common::Range<T>& r);

// *****************************************************
#include "config.h"
#include "debug.h"
#include "io.h"
#include "random.h"
// *****************************************************
#include "common_template.h"
#endif
