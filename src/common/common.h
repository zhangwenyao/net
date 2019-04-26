#ifndef COMMON__COMMON_H_
#define COMMON__COMMON_H_

// g++ -std=c++11

#include "debug.h"
#include "io.h"
#include "random.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#define TOSTRING(x) _TOSTRING(x)
#define _TOSTRING(x) #x

namespace common {
// *************************************************************
template <typename Tp> struct RangeP; // 范围结构

template <typename T> bool find(const std::vector<T>& v, const T& t);
template <typename T>
void find_common(
    const std::vector<T>& v1, const std::vector<T>& v2, std::vector<T>& v);

// 按 val[p[i]] 大小对 p[i] 排序 [i<=i+1]
template <typename Tp, typename T2>
void sort_p_val_greater(Tp p, Tp p2, const T2* const val);

// 按 val[p[i]] 大小对 p[i] 排序 [i>=i+1]
template <typename Tp, typename T2>
void sort_p_val_less(Tp p, Tp p2, const T2* const val);

#ifndef sort_p_val
#define sort_p_val sort_p_val_greater
#endif

template <typename T, typename T2, typename T3>
int sort_rankV2(const T* const ranks, const T2 b, const T2 e, T3* v2);

template <typename T, typename T2>
int get_index(T b, const T e, T2* index);
template <typename T, typename T2, typename T3>
int get_index_val(T b, const T e, T2* index, const T3* val);

template <typename T, typename T2> // a[id] != 0 ==> id
void bool_2_index(const T* a, const size_t n, std::vector<T2>& id);

void cstring_swap(char* a, char* b);
void cstring_reverse(char* a);

template <typename T, typename T2>
void change_type_vector(const std::vector<T> v, std::vector<T2>& v2);
template <typename T, typename T2>
void change_type_vector2(
    const std::vector<std::vector<T>> v, std::vector<std::vector<T2>>& v2);

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
void sum_vector(
    const std::vector<T>& a, std::vector<T2>& s, const int fix = 1);
// *************************************************************
template <typename T>
bool compare_vector(const std::vector<T>& a, const std::vector<T>& b);

template <typename T>
size_t vector_count_same(
    const std::vector<T>& a, const std::vector<T>& b);
template <typename T>
size_t vector_count_same_sort(
    const std::vector<T>& a, const std::vector<T>& b);

template <typename T> T GCD(T a, T b); // 最大公约数

template <typename T>
int matrixCross(const std::vector<std::vector<T>>& a,
    const std::vector<std::vector<T>>& b,
    std::vector<std::vector<T>>& c); // c = a.b

template <typename T, typename T2>
int matrixCross_p2p(const std::vector<std::vector<T2>>& p2p,
    const std::vector<std::vector<T>>& a,
    const std::vector<std::vector<T>>& b,
    std::vector<std::vector<T>>& c); // c = a . p2p . b

template <typename T, typename T2>
int matrixCross1_p2p(const std::vector<std::vector<T2>>& p2p,
    const std::vector<T>& a, std::vector<T>& c); // c = p2p . a

} // end namespace common

// *****************************************************
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#define MKDIR(a) _mkdir((a))
#else // _LINUX
#include <stdarg.h>
#include <sys/stat.h>
#define MKDIR(a) mkdir((a), 0755)
#endif

// *****************************************************
#include "common_template.h"
#endif
