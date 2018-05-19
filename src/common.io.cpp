#include "common.io.h"
#include "common.debug.h"
#include <iostream>
#include <string>
using namespace std;

// *************************************************************
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
  if (s.size() == 1 || (s.size() > 0 && s[0] == '\"' && (*s.rend()) == '\"'))
    ERROR();
  return -1;
  return 0;
}

// *************************************************************
