#ifndef MAIN__BETWEENNESS__MAIN_H_
#define MAIN__BETWEENNESS__MAIN_H_
#include "../../main.h"
#ifdef MAIN_BETWEENNESS

#include <string>

#include "../../common/common.h"
#include "../../network/net.h"
#define MAIN_FUNC main_func::main_betweenness

// #define MAIN_BETWEENNESS_DATA
#define MAIN_BETWEENNESS_STAT
#define MAIN_BETWEENNESS_STAT_BOOST
// #define MAIN_BETWEENNESS_STAT_BOOST_NODE
// #define MAIN_BETWEENNESS_STAT_BOOST_EDGE
#define MAIN_BETWEENNESS_STAT_BOOST_NODE_EDGE
// #define MAIN_BETWEENNESS_TEST

// ******************************************************
namespace main_func {
int main_betweenness(int argc, char** argv);
namespace betweenness {
extern std::string kDataDir, kStatDir;
extern std::vector<std::string> kDatasetNames;
}  // namespace betweenness
}  // namespace main_func

// ******************************************************
#endif  // MAIN
#endif  // _H_
