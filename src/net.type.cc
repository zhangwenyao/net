#include "net.type.h"
#include "common.io.h"

#include <fstream>
#include <iostream>
#include "common.io.h"

using namespace std;

// ******************************************************
ostream& operator<<(ostream& os, const RNodeType& r)
{
  os << r.start << '\t' << r.end;
  return os;
}

istream& operator>>(istream& is, RNodeType& r)
{
  is >> r.start >> r.end;
  return is;
}

int save_VRNodeType_start(ostream& os, const VRNodeType& v, const char c)
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

int save_VRNodeType_start(const char* name, const VRNodeType& v, const char c)
{
  if (name == NULL || name[0] == '\0')
    return -1;
  ofstream os(name);
  if (!os)
    return -1;
  save_VRNodeType_start(os, v, c);
  os.close();
  return 0;
}

int save_VRNodeType_end(ostream& os, const VRNodeType& v, const char c)
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

int save_VRNodeType_end(const char* name, const VRNodeType& v, const char c)
{
  if (name == NULL || name[0] == '\0')
    return -1;
  ofstream os(name);
  if (!os)
    return -1;
  save_VRNodeType_end(os, v, c);
  os.close();
  return 0;
}

// ******************************************************
