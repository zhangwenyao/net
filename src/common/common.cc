#include "common.h"
#include <cstring>

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#define ACCESS _access
#define MKDIR(a) _mkdir((a))
#else // _LINUX
#include <sys/stat.h>
#include <unistd.h>
#define ACCESS access
#define MKDIR(a) mkdir((a), 0755)
#endif

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
int common::mkdirs(const char* dirname)
{
  int i = 0;
  int iRet;
  char dir[1000];
  int iLen = strlen(dirname);
  if (iLen <= 0 || iLen >= 998)
    return -1;
  strcpy(dir, dirname);
  //在末尾加/
  if (dir[iLen - 1] != '\\' && dir[iLen - 1] != '/') {
    dir[iLen] = '/';
    dir[iLen + 1] = '\0';
  }

  // 创建目录
  for (i = 0; i < iLen; i++) {
    if (dir[i] == '\\' || dir[i] == '/') {
      dir[i] = '\0';

      //如果不存在,创建
      iRet = ACCESS(dir, 0);
      if (iRet != 0) {
        iRet = MKDIR(dir);
        if (iRet != 0) {
          return -1;
        }
      }
      //支持linux,将所有\换成/
      dir[i] = '/';
    }
  }

  return 0;
}
// *************************************************************
