#ifndef COMMON_DEBUG_H
#define COMMON_DEBUG_H

#include <cstdlib>
#include <ctime>
#include <iostream>

//#define DEBUG
#define STD_CPP11

// ************* INFORM, DBG, ERROR, SHOW_TIME ****************
#ifdef STD_CPP11
inline void SHOW_TIME(std::ostream& os);
inline void INFO();
template <typename T, typename... Args> inline void INFO(T x, Args... args);
inline void ERRINFO();
template <typename T, typename... Args> inline void ERRINFO(T x, Args... args);

#else
#define SHOW_TIME(fp)                                                         \
  do {                                                                        \
    time_t timeNow = time(NULL);                                              \
    struct tm* timeLocal = localtime(&timeNow);                               \
    fp << asctime(timeLocal);                                                 \
  } while (0)

#define INFO(...)                                                             \
  do {                                                                        \
  } while (0)

#define ERRINFO(...)                                                          \
  do {                                                                        \
  } while (0)

#endif // STD_CPP11

#ifndef ERROR
#define ERROR(...)                                                            \
  do {                                                                        \
    std::cerr << "ERROR : " << __FILE__ << '\t' << __FUNCTION__ << "(Line "   \
              << __LINE__ << ")\t";                                           \
    ERRINFO(__VA_ARGS__);                                                     \
    std::cerr << std::endl;                                                   \
  } while (0)
#endif // ERROR

#ifndef INFORM
#define INFORM(...)                                                           \
  do {                                                                        \
    std::cout << "INFORM: " << __FILE__ << '\t' << __FUNCTION__ << "(Line "   \
              << __LINE__ << ")\t";                                           \
    INFO(__VA_ARGS__);                                                        \
    std::cout << std::endl;                                                   \
  } while (0)
#endif // INFORM

#ifndef DBG
#ifdef DEBUG
#define DBG(...)                                                              \
  do {                                                                        \
    std::cerr << "DEBUG : " << __FILE__ << '\t' << __FUNCTION__ << "(Line "   \
              << __LINE__ << ")\t";                                           \
    ERRINFO(__VA_ARGS__);                                                     \
    std::cerr << std::endl;                                                   \
  } while (0)
#else // DEBUG
#define DBG(...)                                                              \
  do {                                                                        \
  } while (0)
#endif // DEBUG
#endif // DBG

// *************************************************************
#include "common.debug.template.h"
#endif //_H
