#ifndef MAIN__CORRELATION2__MAIN_H_
#define MAIN__CORRELATION2__MAIN_H_
#include "../../main.h"
#ifdef MAIN_CORRELATION2

#include "../../network/net.h"
#include <string>
#define MAIN_FUNC main_func::main_correlation2

#define MAIN_CORRELATION2_NEW_NETWORKS
//#define MAIN_CORRELATION2_STATISTICS_NETWORKS
//#define MAIN_CORRELATION2_EVOLUTION

// ******************************************************
namespace main_func {
int main_correlation2(int argc, char** argv);
namespace correlation2 {
  extern std::string name, dirData, dirStat;
/*
#define dirData0 ("data/DataSet/0undirected_unweight_all/" + name + "/")
const std::string names[] = {
"ER" , "BA", // model
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
   */
#define dirData0 ("data/DataSet/" + name + "/")
  const std::string names[] = { "BA" };
#define dirStat0 dirData0
}
}

// ******************************************************
#endif // MAIN
#endif // _H_
