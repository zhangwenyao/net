#include "common.h"
#include <cstring>
using namespace std;

// *************************************************************
void common_cstring_swap(char* a, char* b)
{
  if (a == b || (*a == '\0' && *b == '\0'))
    return;
  while (*a && *b) {
    *a ^= *b;
    *b ^= *a;
    *a++ ^= *b++;
  }
  char* c;
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

void common_cstring_reverse(char* a)
{
  if (*a == '\0')
    return;
  char* p = a;
  while (*++p)
    continue;
  while (a < --p) {
    *a ^= *p;
    *p ^= *a;
    *a++ ^= *p;
  }
  return;
}

// *************************************************************
