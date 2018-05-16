#ifndef COMMON_H
#define COMMON_H

// g++ -std=c++11

#include "commonRandom.h"
#include <algorithm>
#include <cmath>
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

//#define DEBUG
#define STD_CPP11

#define TOSTRING(x) TOSTRING1(x)
#define TOSTRING1(x) #x

//**//************** INFORM, DBG, ERROR, SHOW_TIME *************//*
//#define SHOW_TIME(fp) do{ time_t timeNow = time(NULL); struct tm *timeLocal =
// localtime(&timeNow); fp << asctime(timeLocal); }while(0)
inline void SHOW_TIME(std::ostream& os);

#ifdef STD_CPP11
inline void ERRINFO();
template <typename T, typename... Args>
inline void ERRINFO(T x, Args... args);
inline void INFO();
template <typename T, typename... Args>
inline void INFO(T x, Args... args);
#else
#define INFO(...) \
  do {            \
  } while (0)
#define ERRINFO(...) \
  do {               \
  } while (0)
#endif

#ifndef ERROR
#define ERROR(...)                                                          \
  do {                                                                      \
    std::cerr << "ERROR : " << __FILE__ << '\t' << __FUNCTION__ << "(Line " \
              << __LINE__ << ")\t";                                         \
    ERRINFO(__VA_ARGS__);                                                   \
    std::cerr << std::endl;                                                 \
  } while (0)
#endif

#ifndef INFORM
#define INFORM(...)                                                         \
  do {                                                                      \
    std::cout << "INFORM: " << __FILE__ << '\t' << __FUNCTION__ << "(Line " \
              << __LINE__ << ")\t";                                         \
    INFO(__VA_ARGS__);                                                      \
    std::cout << std::endl;                                                 \
  } while (0)
#endif

#ifndef DBG
#ifdef DEBUG
#define DBG(...)                                                            \
  do {                                                                      \
    std::cerr << "DEBUG : " << __FILE__ << '\t' << __FUNCTION__ << "(Line " \
              << __LINE__ << ")\t";                                         \
    ERRINFO(__VA_ARGS__);                                                   \
    std::cerr << std::endl;                                                 \
  } while (0)
#else // DEBUG
#define DBG(...) \
  do {           \
  } while (0)
#endif // DEBUG
#endif // DBG

//**//********************** print, common_save *********************//*
// 一维数组a[n]
// template <typename T, const size_t n> std::ostream& operator<<(std::ostream&
// os, T(&a)[n]);
// template <typename T, const size_t n> std::istream& operator>>(std::istream&
// is, T(&a)[n]);
template <typename T, const size_t n>
int common_save(std::ostream& os, T (&a)[n], const char c = '\t');
template <typename T, const size_t n>
int common_save(const char* name, T (&a)[n], const char c = '\t');
template <typename T, const size_t n>
int common_read(std::istream& is, T (&a)[n]);
template <typename T, const size_t n>
int common_read(const char* name, T (&a)[n]);

// *p, n
template <typename T>
int common_save(std::ostream& os, T* p, const size_t n, const char c = '\t');
template <typename T>
int common_save(const char* name, T* p, const size_t n, const char c = '\t');
template <typename T>
int common_read(std::istream& is, T* p, const size_t n);
template <typename T>
int common_read(const char* name, T* p, const size_t n);
template <typename T, typename T2>
int common_read0(std::istream& is, T* p, T2* n);
template <typename T, typename T2>
int common_read0(const char* name, T* p, T2* n);

// 二维数组*p, p[n1][n2]
template <typename T>
int common_save2(std::ostream& os, T* p, const size_t n1, const size_t n2,
    const char c = '\t');
template <typename T>
int common_save2(const char* name, T* p, const size_t n1, const size_t n2,
    const char c = '\t');
template <typename T>
int common_read2(std::istream& is, T* p, const size_t n1, const size_t n2);
template <typename T>
int common_read2(const char* name, T* p, const size_t n1, const size_t n2);

// a[n1][n2]
template <typename T, const size_t n1, const size_t n2>
std::ostream& operator<<(std::ostream& os, T (&a)[n1][n2]);
template <typename T, const size_t n1, const size_t n2>
int common_save2(std::ostream& os, T (&a)[n1][n2], const char c = '\t');
template <typename T, const size_t n1, const size_t n2>
int common_save2(const char* name, T (&a)[n1][n2]);
template <typename T, const size_t n1, const size_t n2>
std::istream& operator>>(std::istream& is, T (&a)[n1][n2]);
template <typename T, const size_t n1, const size_t n2>
int common_read2(const char* name, T (&a)[n1][n2]);
template <typename T, const size_t n1, const size_t n2>
int common_read2(std::istream& is, T (&a)[n1][n2]);

// a[n][size[n]], size[n]
template <typename T, typename T2, const size_t n>
int common_save2(
    std::ostream& os, T* (&a)[n], T2 (&size)[n], const char c = '\t');
template <typename T, typename T2, const size_t n>
int common_save2(
    const char* name, T* (&a)[n], T2 (&size)[n], const char c = '\t');
template <typename T, typename T2, const size_t n>
int common_read2(std::istream& is, T* (&a)[n], T2 (&size)[n]);
template <typename T, typename T2, const size_t n>
int common_read2(const char* name, T* (&a)[n], T2 (&size)[n]);

// a, size[n], n
template <typename T, typename T2>
int common_save2(
    std::ostream& os, T** a, T2* size, const size_t n, const char c = '\t');
template <typename T, typename T2>
int common_save2(
    const char* name, T** a, T2* size, const size_t n, const char c = '\t');
template <typename T, typename T2>
int common_read2(std::istream& is, T** a, T2* size, const size_t n);
template <typename T, typename T2>
int common_read2(const char* name, T** a, T2* size, const size_t n);
template <typename T, typename T2>
int common_read2_0(std::istream& is, T* a, T2* size, T2* n);
template <typename T, typename T2>
int common_read2_0(const char* name, T* a, T2* size, T2* n);
template <typename T, typename T2>
int common_read2_0(std::istream& is, T** a, T2* size, T2* n);
template <typename T, typename T2>
int common_read2_0(const char* name, T** a, T2* size, T2* n);

// **a, n1, n2
template <typename T>
int common_save2(std::ostream& os, T** a, const size_t n1, const size_t n2,
    const char c = '\t');
template <typename T>
int common_save2(const char* name, T** a, const size_t n1, const size_t n2,
    const char c = '\t');
template <typename T>
int common_read2(std::istream& is, T** a, const size_t n1, const size_t n2);
template <typename T>
int common_read2(const char* name, T** a, const size_t n1, const size_t n2);

// vector<> v
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v);
template <typename T>
int common_save1(
    std::ostream& os, const std::vector<T>& v, const char c = '\t');
template <typename T>
int common_save1(
    const char* name, const std::vector<T>& v, const char c = '\t');
template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v);
template <typename T>
int common_read1(std::istream& is, std::vector<T>& v);
template <typename T>
int common_read1(const char* name, std::vector<T>& v);
template <typename T>
int common_read1_0(std::istream& is, std::vector<T>& v, const unsigned n = 0);
template <typename T>
int common_read1_0(const char* name, std::vector<T>& v, const unsigned n = 0);

// vv
template <typename T>
std::ostream& operator<<(
    std::ostream& os, const std::vector<const std::vector<T> >& v);
template <typename T>
int common_save2(std::ostream& os, const std::vector<std::vector<T> >& v,
    const char c = '\t');
template <typename T>
int common_save2(const char* name, const std::vector<std::vector<T> >& v,
    const char c = '\t');
template <typename T>
std::istream& operator>>(std::istream& is, std::vector<std::vector<T> >& v);
template <typename T>
int common_read2(std::istream& is, std::vector<std::vector<T> >& v);
template <typename T>
int common_read2(const char* name, std::vector<std::vector<T> >& v);
template <typename T>
int common_read2_0(std::istream& is, std::vector<std::vector<T> >& v);
template <typename T>
int common_read2_0(const char* name, std::vector<std::vector<T> >& v);

//**//***********************************************************//*
template <typename Tp>
struct Common_RangeP; // 范围结构

template <typename Tp, typename T2>
void common_sort_p_val(Tp p, Tp p2, const T2* const val); // 按val[p[i]]大小对p[i]排序

template <typename Tp, typename T2>
void common_sort_p_val_less(Tp p, Tp p2, const T2* const val); // 按val[p[i]]大小对p[i]排序

template <typename T, typename T2>
void common_total(const std::vector<T>& a, T2& s); // 求和

template <typename T, typename T2, typename T3>
void common_total(const std::vector<T>& a, const std::vector<T2>& p, T3& s);

//**//***********************************************************//*
template <typename T>
T common_GCD(T a, T b); // 最大公约数

template <typename T>
bool common_compare_vector(const std::vector<T>& a, const std::vector<T>& b);

template <typename T>
size_t common_vector_count_same(
    const std::vector<T>& a, const std::vector<T>& b);
template <typename T>
size_t common_vector_count_same_sort(
    const std::vector<T>& a, const std::vector<T>& b);

template <typename T>
int common_matrixCross(const std::vector<std::vector<T> >& a,
    const std::vector<std::vector<T> >& b,
    std::vector<std::vector<T> >& c); // c = a.b

template <typename T, typename T2>
int common_matrixCross_p2p(const std::vector<std::vector<T2> >& p2p,
    const std::vector<std::vector<T> >& a,
    const std::vector<std::vector<T> >& b,
    std::vector<std::vector<T> >& c); // c = a . p2p . b

template <typename T, typename T2>
int common_matrixCross1_p2p(const std::vector<std::vector<T2> >& p2p,
    const std::vector<T>& a, std::vector<T>& c); // c = p2p . a

//**//***************************************************//*
int common_get_string(std::istream& is, std::string& s);

//**//***************************************************//*
#include "common.template.h"
#endif // COMMON_H
