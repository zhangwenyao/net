#include "common.io.h"
#include "common.debug.h"
#include <iostream>
#include <string>
using namespace std;

// *************************************************************
int common_check_filename(const char* const name)
{
  if (name == NULL || name[0] == '\0')
    return -1;
  else
    return 0;
}

int common_get_string(istream& is, string& s)
{
  if (is >> s && !s.empty() && s[0] == '\"') {
    string t;
    if (s.size() == 1 && is >> t)
      s += move(t);
    while (*s.rend() != '\"' && is >> t) {
      s += '\t';
      s += move(t);
    }
  }
  if (s.size() == 1
      || (s.size() >= 2 && s[0] == '\"' && (*s.rend()) == '\"')) {
    ERROR();
    return -1;
  }
  return 0;
}

// VString
int common_save_VString(std::ostream& os, const std::vector<std::string>& vs)
{
  for (std::vector<std::string>::const_iterator i = vs.begin(); i != vs.end();
       ++i)
    os << *i << '\n';
  return 0;
}

int common_save_VString(const char* name, const std::vector<std::string>& vs)
{
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  int flag = common_save_VString(os, vs);
  os.close();
  return flag;
}

int common_read_VString(std::istream& is, std::vector<std::string>& vs)
{
  for (string s; getline(is, s);)
    vs.push_back(move(s));
  return 0;
}

int common_read_VString(const char* name, std::vector<std::string>& vs)
{
  ifstream is(name);
  if (!is) {
    ERROR(name);
    return -1;
  }
  int flag = common_read_VString(is, vs);
  is.close();
  return flag;
}

// *************************************************************
