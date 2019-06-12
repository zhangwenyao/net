#ifndef MAIN__CORRELATION2__MAIN_H_
#define MAIN__CORRELATION2__MAIN_H_
#include "../../main.h"
#ifdef MAIN_CORRELATION2

#include "../../network/net.h"
#include <string>

#define MAIN_FUNC main_func::main_correlation2

// ******************************************************
namespace main_func {
int main_correlation2(int argc, char** argv);
namespace correlation2 {
  extern std::string name, dirData, dirStat;
#define dirData0 ("data/DataSet/0undirected_unweight_all/" + name + "/")
#define dirStat0 dirData0
  const std::string names[] = {
    "ER", "BA", // model
    "adjnoun", "as-22july06", "CElegansMetabolic", "dolphins", "email",
    "football", "jazz", "karate", "PGPgiantcompo", "polbooks", "power",
    "Protein", // undirected_unweighted
    "Grassland", "LittleRock", "p2p-Gnutella04", "p2p-Gnutella05",
    "p2p-Gnutella06", "p2p-Gnutella08", "p2p-Gnutella09", "p2p-Gnutella24",
    "p2p-Gnutella25", "p2p-Gnutella30", "p2p-Gnutella31", "polblogs",
    "Seagrass", "SilwoodPark", "StMartinIsland", "www",
    "Ythan",          // directed _unweighted
    "celegansneural", // directed_weighted
    "astro-ph", "cond-mat", "cond-mat-2003", "cond-mat-2005", "hep-th",
    "lesmis", "netscience", "actor" // undirected_weight
  };
}
}

// ******************************************************
#endif // MAIN
#endif // _H_
