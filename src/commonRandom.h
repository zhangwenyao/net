#ifndef COMMON_RANDOM_H
#define COMMON_RANDOM_H

#include <iostream>
#include <cstdlib>

//#define RAND16807 //采用16807随机数时，取消此行注释即可，否则默认采用系统随机数

//**//********************** rand: RAND2_INIT(seed), RAND2(), FRAND(), FRAND2()*************************************//*
//系统随机数
unsigned srand_init (const int seed);   // 随机数种子初始化，正数:直接初始化，0:采用系统微秒时间，负数:绝对值&系统时间

#ifdef RAND16807
//16807随机数产生器
const int RAND16807_MAX = 2147483647;
unsigned rand16807_init(const int seed);
inline int rand16807(void);
#define RAND2_INIT rand16807_init
#define RAND2() (rand16807() - 1)
const int RAND2_MAX = RAND16807_MAX - 1;
#endif

#ifndef RAND2
#define RAND2_INIT srand_init
#if RAND_MAX > 32767
#define RAND2() rand()
const int  RAND2_MAX = RAND_MAX;
#else   //RAND_MAX <= 32767
#if RAND_MAX == 32767
#define RAND2() ((rand() << 15) + rand()) //rand()*32768+rand()
const int RAND2_MAX = 1073741823;	//((RAND_MAX << 15) + RAND_MAX)
#else   //RAND_MAX < 32767
#define RAND2() (rand() * (RAND_MAX + 1) + rand())
const int RAND2_MAX = RAND_MAX * (2 + RAND_MAX);
#endif  //RAND_MAX == 32767
#endif  //RAND_MAX > 32767
#endif  //RAND2

#ifndef RAND2L
#define RAND2L() (((long long)1 + RAND2_MAX) * RAND2() + RAND2())
const long long  RAND2L_MAX = ((long long)2 + RAND2_MAX) * RAND2_MAX;
#endif


//浮点随机小数
#ifndef FRAND2
const double FRAND2_MAX0 = 1. / RAND2_MAX;
#define FRAND2() (FRAND2_MAX0 * RAND2())
#endif
#ifndef DRAND2
const double DRAND2_MAX0 = FRAND2_MAX0 / (2. + RAND2_MAX);
#define DRAND2() (DRAND2_MAX0 * (RAND2() * (RAND2_MAX + 1.) + RAND2()))
#endif

//**//*********************************************************//*
template <typename T> int random_new_randKArr (T *a, const size_t n, const double *p, const size_t size);  // 按概率产生随机序列
template <typename T> int random_new_randKArr (T *a, const size_t n, const double *p, const T *val, const size_t size);  // 按概率产生随机序列
template <typename T> int random_new_rankKArr (T *a, const size_t n, const double *p, const size_t size);  // a[n]中，按概率产生随机序列
template <typename T> int random_new_rankKArrAll (T *a, const double *p, const size_t size);
template <typename T> inline int random_new_randArr (T *a, const size_t n, const size_t m);  // a[n]中，产生m个不同的随机数
template <typename T> int random_new_randArrAll (T *a, const size_t n);
template <typename T> int random_new_rankArr (T *a, const size_t n, const size_t m);  // a[n]中，产生m个不同的随机数并排序

//**//*********************************************************//*

#include "commonRandomTemplate.h"

#endif

