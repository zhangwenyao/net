#ifndef COMMON_DEBUG_H
#define COMMON_DEBUG_H

#include <cstdlib>
#include <ctime>
#include <iostream>

//#define DEBUG

// ************* INFORM, DBG, ERROR, SHOW_TIME ****************
void SHOW_TIME(std::ostream& os);

void INFO(std::ostream& os);
template <typename T, typename... Args>
void INFO(std::ostream& os, T x, Args... args);
template <typename... Args> void ERROR_INFO(Args... args);
template <typename... Args> void INFORM_INFO(Args... args);
template <typename... Args> void DEBUG_INFO(Args... args);

#ifndef ERROR
#define ERROR(...)                                                           \
  do {                                                                       \
    std::cerr << "ERROR : " << __FILE__ << '\t' << __FUNCTION__ << " (Line " \
              << __LINE__ << ")\t";                                          \
    ERROR_INFO(__VA_ARGS__);                                                 \
    std::cerr << std::endl;                                                  \
  } while (0)
#endif // ERROR

#ifndef INFORM
#define INFORM(...)                                                          \
  do {                                                                       \
    std::cout << "INFORM: " << __FILE__ << '\t' << __FUNCTION__ << " (Line " \
              << __LINE__ << ")\t";                                          \
    INFORM_INFO(__VA_ARGS__);                                                \
    std::cout << std::endl;                                                  \
  } while (0)
#endif // INFORM

#ifndef DBG
#ifdef DEBUG
#define DBG(...)                                                             \
  do {                                                                       \
    std::cerr << "DEBUG : " << __FILE__ << '\t' << __FUNCTION__ << " (Line " \
              << __LINE__ << ")\t";                                          \
    DEBUG_INFO(__VA_ARGS__);                                                 \
    std::clog << std::endl;                                                  \
  } while (0)
#else // DEBUG
#define DBG(...)                                                             \
  do {                                                                       \
  } while (0)
#endif // DEBUG
#endif // DBG

#ifndef ERROR_TEST
#define ERROR_TEST(x)                                                        \
  do {                                                                       \
    if ((x)) {                                                               \
      ERROR();                                                               \
      return -1;                                                             \
    }                                                                        \
  } while (0)
#endif

#ifndef INFORM_TEST
#define INFORM_TEST(x)                                                       \
  do {                                                                       \
    if ((x))                                                                 \
      INFORM();                                                              \
  } while (0)
#endif

// *************************************************************
#include "common.debug.template.h"
#endif //_H
