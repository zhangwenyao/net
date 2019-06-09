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
  const std::string names[] = { "www" };
  // const std::string names[] = { "adjnoun", "as-22july06",
  // "CElegansMetabolic", "dolphins", "email", "football", "jazz", "karate",
  //"PGPgiantcompo", "polbooks", "power", "Protein", "www" };
#define dirData0 ("data/DataSet/0undirected_unweight/" + name + "/")
//#define dirStat0 ("data/DataSet/0undirected_unweight/")
#define dirStat0 ("data/DataSet/0undirected_unweight/" + name + "/")
  extern std::string name, dirData, dirStat;
}
}

// ******************************************************
#endif // MAIN
#endif // _H_
