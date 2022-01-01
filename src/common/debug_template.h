#ifndef COMMON__DEBUG_TEMPLATE_H_
#define COMMON__DEBUG_TEMPLATE_H_

#include <cstdlib>
#include <iostream>

#include "debug.h"
#include "io.h"

// ************* INFO ****************
template <typename T, typename... Args>
void common::_INFO(T x, Args... args) {
  std::cout << '\t' << x;
  _INFO(args...);
  return;
}

template <typename T, typename... Args>
void common::INFO(std::ostream& os, T x, Args... args) {
  os << x;
  INFO(os, args...);
  return;
}

template <typename... Args>
void common::ERROR_INFO(Args... args) {
  INFO(std::cerr, args...);
  return;
}

template <typename... Args>
void common::INFORM_INFO(Args... args) {
  INFO(std::cout, args...);
  return;
}

template <typename... Args>
void common::DEBUG_INFO(Args... args) {
  INFO(std::clog, args...);
  return;
}

// *****************************************************
#endif  //_H
