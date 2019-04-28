#ifndef NETWORK__TYPE_TEMPLATE_H_
#define NETWORK__TYPE_TEMPLATE_H_

#include "type.h"
#include <iostream>

// **********************************************************
template <typename T1, typename T2, typename T3>
std::ostream& operator<<(
    std::ostream& os, const network::Struct3<T1, T2, T3>& r)
{
  os << r.x << '\t' << r.y << '\t' << r.val;
  return os;
};

template <typename T1, typename T2, typename T3>
std::istream& operator>>(
    std::istream& is, const network::Struct3<T1, T2, T3>& r)
{
  is >> r.x >> r.y >> r.val;
  return is;
};

// **********************************************************
#endif
