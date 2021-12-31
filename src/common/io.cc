#include "io.h"

#include <iostream>
#include <string>

#include "debug.h"
using namespace std;

// *************************************************************
int save_string(std::ostream& os, const std::string& s) {
  os << s;
  return 0;
}

int save_string(const char* const name, const std::string& s) {
  if (name == NULL || name[0] == '\0') return -1;
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  os << s;
  os.close();
  return 0;
}

int common::check_filename(const char* const name) {
  if (name == NULL || name[0] == '\0')
    return -1;
  else
    return 0;
}

int common::save(const char* name, const string& s) {
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  os << s;
  os.close();
  return 0;
}

int common::save(const char* name, const char* s) {
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  os << s;
  os.close();
  return 0;
}

int common::get_string(istream& is, string& s) {
  if (is >> s && !s.empty() && s[0] == '\"') {
    string t;
    if (s.size() == 1 && is >> t) s += move(t);
    while (*s.rend() != '\"' && is >> t) {
      s += '\t';
      s += move(t);
    }
  }
  if (s.size() == 1 || (s.size() >= 2 && s[0] == '\"' && (*s.rend()) == '\"')) {
    ERROR();
    return -1;
  }
  return 0;
}

// VString
int common::save_VString(std::ostream& os, const std::vector<std::string>& vs) {
  for (std::vector<std::string>::const_iterator i = vs.begin(); i != vs.end();
       ++i)
    os << *i << '\n';
  return 0;
}

int common::save_VString(const char* name, const std::vector<std::string>& vs) {
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  int flag = common::save_VString(os, vs);
  os.close();
  return flag;
}

int common::read_VString(std::istream& is, std::vector<std::string>& vs) {
  for (string s; getline(is, s);) vs.push_back(move(s));
  return 0;
}

int common::read_VString(const char* name, std::vector<std::string>& vs) {
  ifstream is(name);
  if (!is) {
    ERROR(name);
    return -1;
  }
  int flag = common::read_VString(is, vs);
  is.close();
  return flag;
}

// *************************************************************
