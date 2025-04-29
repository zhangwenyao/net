#include "debug.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

// *****************************
std::string common::GET_TIME(void)
{
  time_t timeNow = time(NULL);
  struct tm* timeLocal = localtime(&timeNow);
  char buffer[20];
  strftime(buffer, 20, "%F %T", timeLocal);
  return std::string(buffer);
}

void common::SHOW_TIME(std::ostream& os)
{
  (os ? os : std::cerr) << GET_TIME() << std::endl;
  return;
}

void common::_INFO()
{
  std::cout << std::endl;
  return;
}

void common::INFO(std::ostream& os) { return; }
