#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "common.debug.h"

// *****************************
std::string GET_TIME(void)
{
  time_t timeNow = time(NULL);
  struct tm* timeLocal = localtime(&timeNow);
  char buffer[20];
  strftime(buffer, 20, "%F %T", timeLocal);
  return std::string(buffer);
}

void SHOW_TIME(std::ostream& os)
{
  (os ? os : std::cerr) << GET_TIME() << std::endl;
  return;
}

void INFO(std::ostream& os) { return; }
