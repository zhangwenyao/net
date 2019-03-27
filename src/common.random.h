#ifndef COMMON_RANDOM_H
#define COMMON_RANDOM_H

#include <cfloat>
#include <functional>
#include <random>

// ***** rand ****************
//系统随机数
extern std::default_random_engine rand2;
extern std::uniform_real_distribution<double> dis_real; // [0,1)
#define rand_double() dis_real(rand2)
// extern decltype(std::bind(std::uniform_real_distribution<double>(), rand2))
// rand_double;
long rand_seed(long
        seed); // 随机数种子初始化，正数:直接初始化，0:采用系统微秒时间，负数:绝对值&系统时间

// ***********************************************************
template <typename T>
int random_new_randKArr(T* a, const size_t n, const double* p,
    const size_t size); // 按概率产生随机序列
template <typename T>
int random_new_randKArr(T* a, const size_t n, const double* p, const T* val,
    const size_t size); // 按概率产生随机序列
template <typename T>
int random_new_rankKArr(T* a, const size_t n, const double* p,
    const size_t size); // a[n]中，按概率产生随机序列
template <typename T>
int random_new_rankKArrAll(T* a, const double* p, const size_t size);
template <typename T>
inline int random_new_randArr(
    T* a, const size_t n, const size_t m); // a[n]中，产生m个不同的随机数
template <typename T> int random_new_randArrAll(T* a, const size_t n);
template <typename T>
int random_new_rankArr(T* a, const size_t n,
    const size_t m); // a[n]中，产生m个不同的随机数并排序
size_t random_new_probSum(const double* a, const size_t s);
size_t random_new_prob_sum(
    const double* a, const size_t s, const double sum = 1);
// ***********************************************************
#include "common.random.template.h"
#endif
