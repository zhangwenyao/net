#ifndef COMMON_IO_H
#define COMMON_IO_H

#include <iostream>
#include <string>
#include <vector>

// *********************************************************************
template <typename T>
inline T common_atoi(const char* s, const char c = 'a', const char base = 26);
template <typename T>
inline size_t common_itoa(
    T i, char* s, const char c = 'a', const char base = 26, size_t n = 0);

int common_get_string(std::istream& is, std::string& s);

// ********************* print, common_save ************************
// 一维数组 a[n]
template <typename T, const size_t n>
int common_save(std::ostream& os, T (&a)[n], const char c = '\t');
template <typename T, const size_t n>
int common_save(const char* name, T (&a)[n], const char c = '\t');
template <typename T, const size_t n>
int common_read(std::istream& is, T (&a)[n]);
template <typename T, const size_t n>
int common_read(const char* name, T (&a)[n]);

// *a, n
template <typename T>
int common_save(std::ostream& os, T* a, const size_t n, const char c = '\t');
template <typename T>
int common_save(const char* name, T* a, const size_t n, const char c = '\t');
template <typename T> int common_read(std::istream& is, T* a, const size_t n);
template <typename T> int common_read(const char* name, T* a, const size_t n);
template <typename T, typename T2>
int common_read0(std::istream& is, T* a, T2& n);
template <typename T, typename T2>
int common_read0(const char* name, T* a, T2& n);
// if a[i], os << i
template <typename T>
int common_save_bool(
    std::ostream& os, const T* a, const size_t n, const char c = '\t');
template <typename T>
int common_save_bool(
    const char* name, const T* a, const size_t n, const char c = '\t');

// a[p[i]]
template <typename T, typename T2>
int common_save1_p(
    std::ostream& os, T* a, T2* p, const size_t n, const char c = '\t');
template <typename T, typename T2>
int common_save1_p(
    const char* name, T* a, T2* p, const size_t n, const char c = '\t');
template <typename T, typename T2>
int common_read1_p(std::istream& is, T* a, T2* p, const size_t n);
template <typename T, typename T2>
int common_read1_p(const char* name, T* a, T2* p, const size_t n);

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
int common_save2(const char* name, T (&a)[n1][n2], const char c = '\t');
template <typename T, const size_t n1, const size_t n2>
std::istream& operator>>(std::istream& is, T (&a)[n1][n2]);
template <typename T, const size_t n1, const size_t n2>
int common_read2(const char* name, T (&a)[n1][n2]);
template <typename T, const size_t n1, const size_t n2>
int common_read2(std::istream& is, T (&a)[n1][n2]);

// a[n][size[n]], size[n]
template <typename T, typename T2, const size_t n>
int common_save2_size(
    std::ostream& os, T* (&a)[n], T2 (&size)[n], const char c = '\t');
template <typename T, typename T2, const size_t n>
int common_save2_size(
    const char* name, T* (&a)[n], T2 (&size)[n], const char c = '\t');
template <typename T, typename T2, const size_t n>
int common_read2_size(std::istream& is, T* (&a)[n], T2 (&size)[n]);
template <typename T, typename T2, const size_t n>
int common_read2_size(const char* name, T* (&a)[n], T2 (&size)[n]);

// a, size[n], n
template <typename T, typename T2>
int common_save2_size(
    std::ostream& os, T** a, T2* size, const size_t n, const char c = '\t');
template <typename T, typename T2>
int common_save2_size(
    const char* name, T** a, T2* size, const size_t n, const char c = '\t');
template <typename T, typename T2>
int common_read2_size(std::istream& is, T** a, T2* size, const size_t n);
template <typename T, typename T2>
int common_read2_size(const char* name, T** a, T2* size, const size_t n);
template <typename T, typename T2>
int common_read2_0_size(std::istream& is, T* a, T2* size, T2* n);
template <typename T, typename T2>
int common_read2_0_size(const char* name, T* a, T2* size, T2* n);
template <typename T, typename T2>
int common_read2_0_size(std::istream& is, T** a, T2* size, T2* n);
template <typename T, typename T2>
int common_read2_0_size(const char* name, T** a, T2* size, T2* n);

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
template <typename T> int common_read1(std::istream& is, std::vector<T>& v);
template <typename T> int common_read1(const char* name, std::vector<T>& v);
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

// VString
int common_save_VString(std::ostream& os, const std::vector<std::string>& vs);
int common_save_VString(const char* name, const std::vector<std::string>& vs);
int common_read_VString(std::istream& is, std::vector<std::string>& vs);
int common_read_VString(const char* name, std::vector<std::string>& vs);

// *************************************************************
#include "common.io.template.h"
#endif //_H
