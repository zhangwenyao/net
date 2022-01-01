#ifndef COMMON__DEBUG_H_
#define COMMON__DEBUG_H_

#include <cstdlib>
#include <ctime>
#include <iostream>

//#define DEBUG

// ************* INFORM, DBG, ERROR, SHOW_TIME ****************
namespace common {
std::string GET_TIME(void);
void SHOW_TIME(std::ostream& os);

void _INFO();
template <typename T, typename... Args>
void _INFO(T x, Args... args);

void INFO(std::ostream& os);
template <typename T, typename... Args>
void INFO(std::ostream& os, T x, Args... args);
template <typename... Args>
void ERROR_INFO(Args... args);
template <typename... Args>
void INFORM_INFO(Args... args);
template <typename... Args>
void DEBUG_INFO(Args... args);
}  // namespace common

#ifndef ERROR
#define ERROR(...)                                                    \
  do {                                                                \
    std::cerr << common::GET_TIME() << " ERROR: " << __FILE__ << '\t' \
              << __FUNCTION__ << " (Line " << __LINE__ << ")\t";      \
    common::ERROR_INFO(__VA_ARGS__);                                  \
    std::cerr << std::endl;                                           \
  } while (0)
#endif  // ERROR

#ifndef INFORM
#define INFORM(...)                                                    \
  do {                                                                 \
    std::cout << common::GET_TIME() << " INFORM: " << __FILE__ << '\t' \
              << __FUNCTION__ << " (Line " << __LINE__ << ")\t";       \
    common::INFORM_INFO(__VA_ARGS__);                                  \
    std::cout << std::endl;                                            \
  } while (0)
#endif  // INFORM

#ifndef DBG
#ifdef DEBUG
#define DBG(...)                                                      \
  do {                                                                \
    std::cerr << common::GET_TIME() << " DEBUG: " << __FILE__ << '\t' \
              << __FUNCTION__ << " (Line " << __LINE__ << ")\t";      \
    common::DEBUG_INFO(__VA_ARGS__);                                  \
    std::clog << std::endl;                                           \
  } while (0)
#else  // !DEBUG
#define DBG(...) \
  do {           \
  } while (0)
#endif  // DEBUG
#endif  // DBG

#ifndef _ERR
#define _ERR(x)  \
  do {           \
    if ((x)) {   \
      ERROR();   \
      return -1; \
    }            \
  } while (0)
#endif

#ifndef _INF
#define _INF(x)        \
  do {                 \
    if ((x)) INFORM(); \
  } while (0)
#endif

#ifndef _DBG
#define _DBG(x)     \
  do {              \
    if ((x)) DBG(); \
  } while (0)
#endif

// *************************************************************
#include "debug_template.h"
#endif  //_H
