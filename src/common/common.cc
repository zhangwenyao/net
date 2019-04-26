#include "common.h"
#include <cstring>
using namespace std;

// *************************************************************
void common::cstring_swap(char* a, char* b)
{
  if (a == b || (*a == '\0' && *b == '\0'))
    return;
  char t, *c;
  while (*a && *b) {
    t = *b;
    *b++ = *a;
    *a++ = t;
  }
  if (*a) {
    c = b;
  } else {
    c = a;
    a = b;
  }
  if (*a) {
    *c++ = *a;
    *a++ = '\0';
    while ((*c++ = *a++))
      continue;
  }
  return;
}

void common::cstring_reverse(char* a)
{
  if (*a == '\0')
    return;
  char c, *p = a;
  while (*++p)
    continue;
  while (a < --p) {
    c = *p;
    *p = *a;
    *a++ = c;
  }
  return;
}

// *************************************************************
