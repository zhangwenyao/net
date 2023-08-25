#ifndef COMMON__DEBUG_TEMPLATE_H_
#define COMMON__DEBUG_TEMPLATE_H_

#include "debug.h"
#include "io.h"
#include <cstdlib>
#include <iostream>

// ************* INFO ****************
template <typename T, typename... Args>
void common::INFO(std::ostream& os, T x, Args... args)
{
  os << x;
  INFO(os, args...);
  return;
}

template <typename... Args> void common::ERROR_INFO(Args... args)
{
  INFO(std::cerr, args...);
  return;
}

template <typename... Args> void common::INFORM_INFO(Args... args)
{
  INFO(std::cout, args...);
  return;
}

template <typename... Args> void common::DEBUG_INFO(Args... args)
{
  INFO(std::clog, args...);
  return;
}

// *****************************************************
#endif //_H
