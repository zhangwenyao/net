#include <cstdlib>
#include <ctime>
#include <iostream>

#include "common.debug.h"

// *****************************
void SHOW_TIME(std::ostream& os)
{
  time_t timeNow = time(NULL);
  struct tm* timeLocal = localtime(&timeNow);
  (os ? os : std::cerr) << asctime(timeLocal);
  return;
}

void INFO(std::ostream& os) { return; }
