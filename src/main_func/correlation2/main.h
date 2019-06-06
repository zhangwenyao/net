#ifndef MAIN__CORRELATION2__MAIN_H_
#define MAIN__CORRELATION2__MAIN_H_
#include "../../main.h"
#ifdef MAIN_CORRELATION2

#include "../../network/net.h"

#include <string>
// ******************************************************
namespace main_func {
int main_correlation2(int argc, char** argv);
namespace correlation2 {
  const std::string dirData = "data/DataSet/0directed_unweight/www/";
  const std::string dirStat = "data/DataSet/0directed_unweight/";
}
}

// ******************************************************
#endif // MAIN
#endif // _H_
