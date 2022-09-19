#include "type.h"

#include "../common/common.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
int network::save_VRNodeType_start(
    ostream& os, const VRNodeType& v, const char c)
{
  if (!os)
    return -1;
  if (!v.empty()) {
    VRNodeTypeCItr i = v.begin();
    os << (i++)->start;
    while (i != v.end())
      os << c << (i++)->start;
  }
  return 0;
}

int network::save_VRNodeType_start(
    const char* name, const VRNodeType& v, const char c)
{
  if (name == NULL || name[0] == '\0')
    return -1;
  ofstream os(name);
  if (!os)
    return -1;
  network::save_VRNodeType_start(os, v, c);
  os.close();
  return 0;
}

int network::save_VRNodeType_end(
    ostream& os, const VRNodeType& v, const char c)
{
  if (!os)
    return -1;
  if (!v.empty()) {
    VRNodeTypeCItr i = v.begin();
    os << (i++)->end;
    while (i != v.end())
      os << c << (i++)->end;
  }
  return 0;
}

int network::save_VRNodeType_end(
    const char* name, const VRNodeType& v, const char c)
{
  if (name == NULL || name[0] == '\0')
    return -1;
  ofstream os(name);
  if (!os)
    return -1;
  network::save_VRNodeType_end(os, v, c);
  os.close();
  return 0;
}

// ******************************************************
std::istream& operator>>(std::istream& is, network::Lkk_type& lkk_type)
{
  string s;
  if (is >> s) {
    for (auto& i : network::kLkkTypeString) {
      if (s == i.second) {
        lkk_type = i.first;
        break;
      }
    }
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const network::Lkk_type& lkk_type)
{
  auto iter = network::kLkkTypeString.find(lkk_type);
  if (iter != network::kLkkTypeString.end())
    os << iter->second;
  else
    ERROR();
  return os;
}
