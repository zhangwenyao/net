#ifndef COMMON_DEBUG_TEMPLATE_H
#define COMMON_DEBUG_TEMPLATE_H

#include "common.debug.h"
#include "common.io.h"
#include <cstdlib>
#include <iostream>

// ************* INFO, SHOW_TIME ****************
#ifdef STD_CPP11
inline void SHOW_TIME(std::ostream& os)
{
  time_t timeNow = time(NULL);
  struct tm* timeLocal = localtime(&timeNow);
  (os ? os : std::cerr) << asctime(timeLocal);
  return;
}

inline void ERRINFO()
{
  std::cerr << std::flush;
  return;
}

template <typename T, typename... Args> inline void ERRINFO(T x, Args... args)
{
  std::cerr << x;
  ERRINFO(args...);
  return;
}

inline void INFO()
{
  std::cout << std::flush;
  return;
}

template <typename T, typename... Args> inline void INFO(T x, Args... args)
{
  std::cout << x;
  INFO(args...);
  return;
}
#endif // STD_CPP11

// *****************************************************
#endif //_H
