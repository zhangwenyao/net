#ifndef MAIN__BETWEENNESS__MAIN_H_
#define MAIN__BETWEENNESS__MAIN_H_
#include "../../main.h"
#ifdef MAIN_BETWEENNESS

#include <string>

#include "../../common/common.h"
#include "../../network/net.h"
#define MAIN_FUNC main_func::main_betweenness

#define MAIN_BETWEENNESS_DATA
#define MAIN_BETWEENNESS_STAT
#define MAIN_BETWEENNESS_STAT_BOOST
// #define MAIN_BETWEENNESS_STAT_BOOST_NODE
// #define MAIN_BETWEENNESS_STAT_BOOST_EDGE
#define MAIN_BETWEENNESS_STAT_BOOST_NODE_EDGE
// #define MAIN_BETWEENNESS_TEST

// ******************************************************
namespace main_func {
int main_betweenness(int argc, char** argv);
int check_args(int argc, char** argv);
namespace betweenness {
constexpr int kSeed0 = 1;
constexpr int kSeedMin = 1, kSeedMax = 300;

const std::string kDataDir = std::string("data/DataSet/"),
                  kStatDir = std::string("data/DataSet/");
const std::string DATASET_NAMES[] = {"example", "CondMat", "Email-Enron",
                                     "Facebook", "Amazon"};
const size_t DATASET_SIZE = sizeof(DATASET_NAMES) / sizeof(DATASET_NAMES[0]);
}  // namespace betweenness
}  // namespace main_func

// ******************************************************
#endif  // MAIN
#endif  // _H_
