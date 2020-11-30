#ifndef MAIN__DISTRIBUTION__MAIN_H_
#define MAIN__DISTRIBUTION__MAIN_H_
#include "../../main.h"
#ifdef MAIN_DISTRIBUTION

#include "../../network/net.h"
#include <string>
#define MAIN_FUNC main_func::main_distribution

//#define MAIN_DISTRIBUTION_NONE

// ******************************************************
namespace main_func {
int main_distribution(int argc, char** argv);
namespace distribution {
  const std::string kDataDir = std::string("data/distribution/100/");
  static constexpr int n = 100;
}
}

// ******************************************************
#endif // MAIN
#endif // _H_
