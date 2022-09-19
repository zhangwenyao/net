#ifndef COMMON__COMMON_IO_H_
#define COMMON__COMMON_IO_H_

#include "common.h"
#include <iostream>
#include <string>
#include <vector>

namespace common {
// *********************************************************************
template <typename T>
inline T atoi(const char* s, const char c = 'a', const char base = 26);
template <typename T>
inline size_t itoa(
    T i, char* s, const char c = 'a', const char base = 26, size_t n = 0);
template <typename T> inline std::string dtoa(const T i);

int get_string(std::istream& is, std::string& s);

int save_string(std::ostream& os, const std::string& s);
int save_string(const char* const name, const std::string& s);

// ********************* print, save ************************
int check_filename(const char* const name = NULL);

// string
int save(const char* name, const std::string& s);
int save(const char* name, const char* s);

// 一维数组 a[n]
template <typename T, const size_t n>
int save(std::ostream& os, T (&a)[n], const char c = '\t');
template <typename T, const size_t n>
int save(const char* name, T (&a)[n], const char c = '\t');
template <typename T, const size_t n> int read(std::istream& is, T (&a)[n]);
template <typename T, const size_t n> int read(const char* name, T (&a)[n]);

// *a, n
template <typename T>
int save(std::ostream& os, T* a, const size_t n, const char c = '\t');
template <typename T>
int save(const char* name, T* a, const size_t n, const char c = '\t');
template <typename T> int read(std::istream& is, T* a, const size_t n);
template <typename T> int read(const char* name, T* a, const size_t n);
template <typename T, typename T2> int read0(std::istream& is, T* a, T2& n);
template <typename T, typename T2> int read0(const char* name, T* a, T2& n);
// if a[i], os << i
template <typename T>
int save_bool(
    std::ostream& os, const T* a, const size_t n, const char c = '\t');
template <typename T>
int save_bool(
    const char* name, const T* a, const size_t n, const char c = '\t');

// a[p[i]]
template <typename T, typename T2>
int save1_p(
    std::ostream& os, T* a, T2* p, const size_t n, const char c = '\t');
template <typename T, typename T2>
int save1_p(
    const char* name, T* a, T2* p, const size_t n, const char c = '\t');
template <typename T, typename T2>
int read1_p(std::istream& is, T* a, T2* p, const size_t n);
template <typename T, typename T2>
int read1_p(const char* name, T* a, T2* p, const size_t n);

// 二维数组*p, p[n1][n2]
template <typename T>
int save2(std::ostream& os, T* p, const size_t n1, const size_t n2,
    const char c = '\t');
template <typename T>
int save2(const char* name, T* p, const size_t n1, const size_t n2,
    const char c = '\t');
template <typename T>
int read2(std::istream& is, T* p, const size_t n1, const size_t n2);
template <typename T>
int read2(const char* name, T* p, const size_t n1, const size_t n2);

// a[n1][n2]
// template <typename T, const size_t n1, const size_t n2>
// std::ostream& operator<<(std::ostream& os, T (&a)[n1][n2]);
template <typename T, const size_t n1, const size_t n2>
int save2(std::ostream& os, T (&a)[n1][n2], const char c = '\t');
template <typename T, const size_t n1, const size_t n2>
int save2(const char* name, T (&a)[n1][n2], const char c = '\t');
// template <typename T, const size_t n1, const size_t n2>
// std::istream& operator>>(std::istream& is, T (&a)[n1][n2]);
template <typename T, const size_t n1, const size_t n2>
int read2(const char* name, T (&a)[n1][n2]);
template <typename T, const size_t n1, const size_t n2>
int read2(std::istream& is, T (&a)[n1][n2]);

// a[n][size[n]], size[n]
template <typename T, typename T2, const size_t n>
int save2_size(
    std::ostream& os, T* (&a)[n], T2 (&size)[n], const char c = '\t');
template <typename T, typename T2, const size_t n>
int save2_size(
    const char* name, T* (&a)[n], T2 (&size)[n], const char c = '\t');
template <typename T, typename T2, const size_t n>
int read2_size(std::istream& is, T* (&a)[n], T2 (&size)[n]);
template <typename T, typename T2, const size_t n>
int read2_size(const char* name, T* (&a)[n], T2 (&size)[n]);

// a, size[n], n
template <typename T, typename T2>
int save2_size(
    std::ostream& os, T** a, T2* size, const size_t n, const char c = '\t');
template <typename T, typename T2>
int save2_size(
    const char* name, T** a, T2* size, const size_t n, const char c = '\t');
template <typename T, typename T2>
int read2_size(std::istream& is, T** a, T2* size, const size_t n);
template <typename T, typename T2>
int read2_size(const char* name, T** a, T2* size, const size_t n);
template <typename T, typename T2>
int read2_0_size(std::istream& is, T* a, T2* size, T2* n);
template <typename T, typename T2>
int read2_0_size(const char* name, T* a, T2* size, T2* n);
template <typename T, typename T2>
int read2_0_size(std::istream& is, T** a, T2* size, T2* n);
template <typename T, typename T2>
int read2_0_size(const char* name, T** a, T2* size, T2* n);

// **a, n1, n2
template <typename T>
int save2(std::ostream& os, T** a, const size_t n1, const size_t n2,
    const char c = '\t');
template <typename T>
int save2(const char* name, T** a, const size_t n1, const size_t n2,
    const char c = '\t');
template <typename T>
int read2(std::istream& is, T** a, const size_t n1, const size_t n2);
template <typename T>
int read2(const char* name, T** a, const size_t n1, const size_t n2);

// vector<> v
// template <typename T>
// std::ostream& operator<<(std::ostream& os, const std::vector<T>& v);
template <typename T>
int save1(std::ostream& os, const std::vector<T>& v, const char c = '\t');
template <typename T>
int save1(const char* name, const std::vector<T>& v, const char c = '\t');
// template <typename T>
// std::istream& operator>>(std::istream& is, std::vector<T>& v);
template <typename T> int read1(std::istream& is, std::vector<T>& v);
template <typename T> int read1(const char* name, std::vector<T>& v);
template <typename T>
int read1_0(std::istream& is, std::vector<T>& v, unsigned n = 0);
template <typename T>
int read1_0(const char* name, std::vector<T>& v, unsigned n = 0);

// vv
// template <typename T>
// std::ostream& operator<<(
// std::ostream& os, const std::vector<const std::vector<T>>& v);
template <typename T>
int save2(std::ostream& os, const std::vector<std::vector<T>>& v,
    const char c = '\t');
template <typename T>
int save2(const char* name, const std::vector<std::vector<T>>& v,
    const char c = '\t');
// template <typename T>
// std::istream& operator>>(std::istream& is, std::vector<std::vector<T>>& v);
template <typename T>
int read2(std::istream& is, std::vector<std::vector<T>>& v);
template <typename T>
int read2(const char* name, std::vector<std::vector<T>>& v);
template <typename T>
int read2_0(std::istream& is, std::vector<std::vector<T>>& v);
template <typename T>
int read2_0(const char* name, std::vector<std::vector<T>>& v);

// VString
int save_VString(std::ostream& os, const std::vector<std::string>& vs);
int save_VString(const char* name, const std::vector<std::string>& vs);
int read_VString(std::istream& is, std::vector<std::string>& vs);
int read_VString(const char* name, std::vector<std::string>& vs);

template <typename T>
int save_double(
    std::ostream& os, const T& ds, const int l = 18, const char c = '\t');
template <typename T>
int save_double(
    const char* name, const T& ds, const int l = 18, const char c = '\t');
template <typename T>
int save_double1(
    std::ostream& os, const T& ds, const int l = 18, const char c = '\t');
template <typename T>
int save_double1(
    const char* name, const T& ds, const int l = 18, const char c = '\t');
template <typename T>
int save_double2(
    std::ostream& os, const T& ds, const int l = 18, const char c = '\t');
template <typename T>
int save_double2(
    const char* name, const T& ds, const int l = 18, const char c = '\t');
} // end namespace common

// *************************************************************
template <typename T, const size_t n1, const size_t n2>
std::ostream& operator<<(std::ostream& os, const T (&a)[n1][n2]);
template <typename T, const size_t n1, const size_t n2>
std::istream& operator>>(std::istream& is, T (&a)[n1][n2]);

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v);
template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v);

template <typename T>
std::ostream& operator<<(
    std::ostream& os, const std::vector<const std::vector<T>>& v);
template <typename T>
std::istream& operator>>(std::istream& is, std::vector<std::vector<T>>& v);

template <typename T1, typename T2, typename T3>
std::ostream& operator<<(
    std::ostream& os, const std::vector<common::Struct3<T1, T2, T3>>& vs);

// *************************************************************
#include "io_template.h"
#endif //_H
