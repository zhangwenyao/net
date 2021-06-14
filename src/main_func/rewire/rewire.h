#ifndef MAIN__REWIRE_H_
#define MAIN__REWIRE_H_
#include "main.h"
#ifdef MAIN_REWIRE

#include "../../network/networks.h"

namespace main_func {
namespace rewire {
  // ******************************************************
  int distribution(int argc, char** argv);
  int distribution_stat(int argc, char** argv);
  int distribution_stat_all(int argc, char** argv);
  int networks_random_dir(int argc, char** argv);
  int networks_random(int argc, char** argv);
  int stat(int argc, char** argv);
  int stat_all(int argc, char** argv);
  int networks_random1(int argc, char** argv);
  int stat_all1(int argc, char** argv);

  // ******************************************************
}
}
#endif // MAIN
#endif // _H_
