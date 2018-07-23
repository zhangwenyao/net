#ifndef COMMON_DEBUG_TEMPLATE_H
#define COMMON_DEBUG_TEMPLATE_H

#include "common.debug.h"
#include "common.io.h"
#include <cstdlib>
#include <iostream>

// ************* INFO ****************
template <typename T, typename... Args>
void INFO(std::ostream& os, T x, Args... args)
{
  os << x;
  INFO(os, args...);
  return;
}

template <typename... Args> void ERROR_INFO(Args... args)
{
  INFO(std::cerr, args...);
  return;
}

template <typename... Args> void INFORM_INFO(Args... args)
{
  INFO(std::cout, args...);
  return;
}

template <typename... Args> void DEBUG_INFO(Args... args)
{
  INFO(std::clog, args...);
  return;
}

// *****************************************************
#endif //_H
