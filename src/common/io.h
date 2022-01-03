#ifndef COMMON__COMMON_IO_H_
#define COMMON__COMMON_IO_H_

#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "common.h"
#include "json.hpp"

namespace common {
// *********************************************************************
template <typename T>
inline T atoi(const char *s, const char c = 'a', const char base = 26);
template <typename T>
inline size_t itoa(T i, char *s, const char c = 'a', const char base = 26,
                   size_t n = 0);
template <typename T>
inline std::string dtoa(const T i);

// ********************* print, save ************************
int check_filename(const std::string &name);
int check_filename(const char *const name = NULL);

// string
int save_string(std::ostream &os, const std::string &s);
int save_string(const char *name, const std::string &s);
int save(const char *name, const std::string &s);
int save(const char *name, const char *s);
int read(const char *name, std::string &s);
int get_string(std::istream &is, std::string &s);  // 解析简单双引号
// VString
int save_VString(std::ostream &os, const std::vector<std::string> &vs);
int save_VString(const char *name, const std::vector<std::string> &vs);
int read_VString(std::istream &is, std::vector<std::string> &vs);
int read_VString(const char *name, std::vector<std::string> &vs);

// json
int save(const char *name, const nlohmann::json &j);
int read(const char *name, nlohmann::json &j);
inline int read(const std::string &name, nlohmann::json &j);
int save_json(std::ostream &os, const nlohmann::json &j);
int save_json(const char *name, const nlohmann::json &j);
inline int save_json(const std::string &name, const nlohmann::json &j);

// 一维数组 a[n]
template <typename T, const size_t n>
int save(std::ostream &os, T (&a)[n], const char c = '\t');
template <typename T, const size_t n>
int save(const char *name, T (&a)[n], const char c = '\t');
template <typename T, const size_t n>
int read(std::istream &is, T (&a)[n]);
template <typename T, const size_t n>
int read(const char *name, T (&a)[n]);

// *a, n
template <typename T>
int save(std::ostream &os, T *a, const size_t n, const char c = '\t');
template <typename T>
int save(const char *name, T *a, const size_t n, const char c = '\t');
template <typename T>
int read(std::istream &is, T *a, const size_t n);
template <typename T>
int read(const char *name, T *a, const size_t n);
template <typename T, typename T2>
int read0(std::istream &is, T *a, T2 &n);
template <typename T, typename T2>
int read0(const char *name, T *a, T2 &n);

// a[p[i]]
template <typename T, typename T2>
int save1_p(std::ostream &os, T *a, T2 *p, const size_t n, const char c = '\t');
template <typename T, typename T2>
int save1_p(const char *name, T *a, T2 *p, const size_t n, const char c = '\t');
template <typename T, typename T2>
int read1_p(std::istream &is, T *a, T2 *p, const size_t n);
template <typename T, typename T2>
int read1_p(const char *name, T *a, T2 *p, const size_t n);

// a[0..n]
template <typename T>
int save1_head(std::ostream &os, T &a, const size_t n, const char c = '\t');
template <typename T>
int save1_head(const char *name, T &a, const size_t n, const char c = '\t');

// 二维数组*p, p[n1][n2]
template <typename T>
int save2(std::ostream &os, T *p, const size_t n1, const size_t n2,
          const char c = '\t');
template <typename T>
int save2(const char *name, T *p, const size_t n1, const size_t n2,
          const char c = '\t');
template <typename T>
int read2(std::istream &is, T *p, const size_t n1, const size_t n2);
template <typename T>
int read2(const char *name, T *p, const size_t n1, const size_t n2);

// a[n1][n2]
// template <typename T, const size_t n1, const size_t n2>
// std::ostream& operator<<(std::ostream& os, T (&a)[n1][n2]);
template <typename T, const size_t n1, const size_t n2>
int save2(std::ostream &os, T (&a)[n1][n2], const char c = '\t');
template <typename T, const size_t n1, const size_t n2>
int save2(const char *name, T (&a)[n1][n2], const char c = '\t');
// template <typename T, const size_t n1, const size_t n2>
// std::istream& operator>>(std::istream& is, T (&a)[n1][n2]);
template <typename T, const size_t n1, const size_t n2>
int read2(const char *name, T (&a)[n1][n2]);
template <typename T, const size_t n1, const size_t n2>
int read2(std::istream &is, T (&a)[n1][n2]);

// a[n][size[n]], size[n]
template <typename T, typename T2, const size_t n>
int save2_size(std::ostream &os, T *(&a)[n], T2 (&size)[n],
               const char c = '\t');
template <typename T, typename T2, const size_t n>
int save2_size(const char *name, T *(&a)[n], T2 (&size)[n],
               const char c = '\t');
template <typename T, typename T2, const size_t n>
int read2_size(std::istream &is, T *(&a)[n], T2 (&size)[n]);
template <typename T, typename T2, const size_t n>
int read2_size(const char *name, T *(&a)[n], T2 (&size)[n]);

// a, size[n], n
template <typename T, typename T2>
int save2_size(std::ostream &os, T **a, T2 *size, const size_t n,
               const char c = '\t');
template <typename T, typename T2>
int save2_size(const char *name, T **a, T2 *size, const size_t n,
               const char c = '\t');
template <typename T, typename T2>
int read2_size(std::istream &is, T **a, T2 *size, const size_t n);
template <typename T, typename T2>
int read2_size(const char *name, T **a, T2 *size, const size_t n);
template <typename T, typename T2>
int read2_0_size(std::istream &is, T *a, T2 *size, T2 *n);
template <typename T, typename T2>
int read2_0_size(const char *name, T *a, T2 *size, T2 *n);
template <typename T, typename T2>
int read2_0_size(std::istream &is, T **a, T2 *size, T2 *n);
template <typename T, typename T2>
int read2_0_size(const char *name, T **a, T2 *size, T2 *n);

// *a, n1, n2
template <typename T>
int save2_1(std::ostream &os, const T &a, const size_t n1, const size_t n2,
            const char c = '\t');
template <typename T>
int save2_1(const char *name, const T &a, const size_t n1, const size_t n2,
            const char c = '\t');
template <typename T>
int read2_1(std::istream &is, T &a, const size_t n1, const size_t n2);
template <typename T>
int read2_1(const char *name, T &a, const size_t n1, const size_t n2);

// **a, n1, n2
template <typename T>
int save2(std::ostream &os, T **a, const size_t n1, const size_t n2,
          const char c = '\t');
template <typename T>
int save2(const char *name, T **a, const size_t n1, const size_t n2,
          const char c = '\t');
template <typename T>
int read2(std::istream &is, T **a, const size_t n1, const size_t n2);
template <typename T>
int read2(const char *name, T **a, const size_t n1, const size_t n2);

// vector<> v
// template <typename T>
// std::ostream& operator<<(std::ostream& os, const std::vector<T>& v);
template <typename T>
int save1(std::ostream &os, const std::vector<T> &v, const char c = '\t');
template <typename T>
int save1(const char *name, const std::vector<T> &v, const char c = '\t');
// template <typename T>
// std::istream& operator>>(std::istream& is, std::vector<T>& v);
template <typename T>
int read1(std::istream &is, std::vector<T> &v);
template <typename T>
int read1(const char *name, std::vector<T> &v);
template <typename T>
int read1_0(std::istream &is, std::vector<T> &v, unsigned n = 0);
template <typename T>
int read1_0(const char *name, std::vector<T> &v, unsigned n = 0);

// vv
// template <typename T>
// std::ostream& operator<<(
// std::ostream& os, const std::vector<const std::vector<T>>& v);
template <typename T>
int save2(std::ostream &os, const std::vector<std::vector<T>> &v,
          const char c = '\t');
template <typename T>
int save2(const char *name, const std::vector<std::vector<T>> &v,
          const char c = '\t');
// template <typename T>
// std::istream& operator>>(std::istream& is, std::vector<std::vector<T>>& v);
template <typename T>
int read2(std::istream &is, std::vector<std::vector<T>> &v);
template <typename T>
int read2(const char *name, std::vector<std::vector<T>> &v);
template <typename T>
int read2_0(std::istream &is, std::vector<std::vector<T>> &v);
template <typename T>
int read2_0(const char *name, std::vector<std::vector<T>> &v);
// vv: v
template <typename T, typename T2>
int read2_len_n(std::istream &is, T &vv, const T2 &l, const size_t n);
template <typename T, typename T2>
int read2_len_n(const char *name, T &vv, const T2 &l, const size_t n);

// Map
template <typename T1, typename T2>
int read0(std::istream &is, std::map<T1, T2> &m);
template <typename T1, typename T2>
int read0(const char *name, std::map<T1, T2> &m);
template <typename T1, typename T2>
int read0(std::istream &is, std::vector<std::set<T2>> &s,
          const std::map<T1, T2> &u, const std::map<T1, T2> &v);
template <typename T1, typename T2>
int read0(const char *name, std::vector<std::set<T2>> &s,
          const std::map<T1, T2> &u, const std::map<T1, T2> &v);
template <typename T1, typename T2>
int read0(std::istream &is, std::vector<std::vector<T2>> &s,
          const std::map<T1, T2> &u, const std::map<T1, T2> &v);
template <typename T1, typename T2>
int read0(const char *name, std::vector<std::vector<T2>> &s,
          const std::map<T1, T2> &u, const std::map<T1, T2> &v);

// double
template <typename T>
int save_double(std::ostream &os, const T &ds, const char c = '\t',
                const int l = std::numeric_limits<double>::digits10 + 1);
template <typename T>
int save_double(const char *name, const T &ds, const char c = '\t',
                const int l = std::numeric_limits<double>::digits10 + 1);
template <typename T>
int save1_double(std::ostream &os, const T &ds, const char c = '\t',
                 const int l = std::numeric_limits<double>::digits10 + 1);
template <typename T>
int save1_double(const char *name, const T &ds, const char c = '\t',
                 const int l = std::numeric_limits<double>::digits10 + 1);
template <typename T>
int save2_double(std::ostream &os, const T &ds, const char c = '\t',
                 const int l = std::numeric_limits<double>::digits10 + 1);
template <typename T>
int save2_double(const char *name, const T &ds, const char c = '\t',
                 const int l = std::numeric_limits<double>::digits10 + 1);

// ********************* print, save ************************
template <typename T, typename... Argv>
inline int ssave_string(const std::string &name, T &&a, Argv... argv);

template <typename T, typename... Argv>
inline int ssave(const std::string &name, T &&a, Argv... argv);
template <typename T, typename... Argv>
inline int sread(const std::string &name, T &&a, Argv... argv);
template <typename T, typename... Argv>
inline int sread0(const std::string &name, T &&a, Argv... argv);

template <typename T, typename... Argv>
inline int ssave1_p(const std::string &name, T &&a, Argv... argv);
template <typename T, typename... Argv>
inline int sread1_p(const std::string &name, T &&a, Argv... argv);

template <typename T, typename... Argv>
inline int ssave1(const std::string &name, T &&a, Argv... argv);
template <typename T, typename... Argv>
inline int sread1(const std::string &name, T &&a, Argv... argv);
template <typename T, typename... Argv>
inline int sread1_0(const std::string &name, T &&a, Argv... argv);
template <typename T, typename... Argv>
inline int ssave2(const std::string &name, T &&a, Argv... argv);
template <typename T, typename... Argv>
inline int sread2(const std::string &name, T &&a, Argv... argv);
template <typename T, typename... Argv>
inline int sread2_0(const std::string &name, T &&a, Argv... argv);

template <typename T, typename... Argv>
inline int ssave2_size(const std::string &name, T &&a, Argv... argv);
template <typename T, typename... Argv>
inline int sread2_size(const std::string &name, T &&a, Argv... argv);
template <typename T, typename... Argv>
inline int sread2_0_size(const std::string &name, T &&a, Argv... argv);
template <typename T, typename... Argv>
inline int ssave_VString(const std::string &name, T &&a, Argv... argv);
template <typename T, typename... Argv>
inline int sread_VString(const std::string &name, T &&a, Argv... argv);
template <typename T, typename... Argv>
inline int ssave_double(const std::string &name, T &&a, Argv... argv);
template <typename T, typename... Argv>
inline int ssave1_double(const std::string &name, T &&a, Argv... argv);
template <typename T, typename... Argv>
inline int ssave2_double(const std::string &name, T &&a, Argv... argv);

}  // end namespace common

// *************************************************************
template <typename T, const size_t n1, const size_t n2>
std::ostream &operator<<(std::ostream &os, const T (&a)[n1][n2]);
template <typename T, const size_t n1, const size_t n2>
std::istream &operator>>(std::istream &is, T (&a)[n1][n2]);

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v);
template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v);

template <typename T>
std::ostream &operator<<(std::ostream &os,
                         const std::vector<const std::vector<T>> &v);
template <typename T>
std::istream &operator>>(std::istream &is, std::vector<std::vector<T>> &v);

template <typename T1, typename T2, typename T3>
std::ostream &operator<<(std::ostream &os,
                         const std::vector<common::Struct3<T1, T2, T3>> &vs);

// *************************************************************
#include "io_template.h"
#endif  //_H
