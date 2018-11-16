#ifndef COMMON_H
#define COMMON_H

// g++ -std=c++11

#include "common.debug.h"
#include "common.io.h"
#include "common.random.h"
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

//#define TOSTRING(x) TOSTRING1(x)
//#define TOSTRING1(x) #x

// *************************************************************
template <typename Tp> struct Common_RangeP; // 范围结构

template <typename T> bool common_find(const std::vector<T>& v, const T& t);
template <typename T>
void common_find_common(
    const std::vector<T>& v1, const std::vector<T>& v2, std::vector<T>& v);

// 按 val[p[i]] 大小对 p[i] 排序 [i<=i+1]
template <typename Tp, typename T2>
void common_sort_p_val_greater(Tp p, Tp p2, const T2* const val);

// 按 val[p[i]] 大小对 p[i] 排序 [i>=i+1]
template <typename Tp, typename T2>
void common_sort_p_val_less(Tp p, Tp p2, const T2* const val);

#ifndef common_sort_p_val
#define common_sort_p_val common_sort_p_val_greater
#endif

template <typename T, typename T2, typename T3>
int common_sort_rankV2(const T* const ranks, const T2 b, const T2 e, T3* v2);

template <typename T, typename T2>
int common_get_index(T b, const T e, T2* index);
template <typename T, typename T2, typename T3>
int common_get_index_val(T b, const T e, T2* index, const T3* val);

template <typename T, typename T2> // a[id] != 0 ==> id
void common_bool_2_index(const T* a, const size_t n, std::vector<T2>& id);

void common_cstring_swap(char* a, char* b);
void common_cstring_reverse(char* a);

template <typename T, typename T2>
void common_change_type_vector(const std::vector<T> v, std::vector<T2>& v2);
template <typename T, typename T2>
void common_change_type_vector2(
    const std::vector<std::vector<T>> v, std::vector<std::vector<T2>>& v2);

// *************************************************************
// s += a[p[i]] for i..n
template <typename T, typename T2, typename T3>
void common_total_p(const T* a, const T2* p, const size_t n, T3& s);

// for i, if a[i], s++
template <typename T, typename T2>
void common_total_bool(const std::vector<T>& a, T2& s);
template <typename T, typename T2>
void common_total_bool(const T* a, size_t n, T2& s);
// for i, if a[p[i] s++
template <typename T, typename T2, typename T3>
void common_total_p_bool(const T* a, const T2* p, size_t n, T3 s);

// *************************************************************
template <typename T>
bool common_compare_vector(const std::vector<T>& a, const std::vector<T>& b);

template <typename T>
size_t common_vector_count_same(
    const std::vector<T>& a, const std::vector<T>& b);
template <typename T>
size_t common_vector_count_same_sort(
    const std::vector<T>& a, const std::vector<T>& b);

template <typename T> T common_GCD(T a, T b); // 最大公约数

template <typename T>
int common_matrixCross(const std::vector<std::vector<T>>& a,
    const std::vector<std::vector<T>>& b,
    std::vector<std::vector<T>>& c); // c = a.b

template <typename T, typename T2>
int common_matrixCross_p2p(const std::vector<std::vector<T2>>& p2p,
    const std::vector<std::vector<T>>& a,
    const std::vector<std::vector<T>>& b,
    std::vector<std::vector<T>>& c); // c = a . p2p . b

template <typename T, typename T2>
int common_matrixCross1_p2p(const std::vector<std::vector<T2>>& p2p,
    const std::vector<T>& a, std::vector<T>& c); // c = p2p . a

// *****************************************************
#include "common.template.h"
#endif
