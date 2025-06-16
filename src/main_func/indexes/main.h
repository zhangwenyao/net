#ifndef MAIN__INDEXES__MAIN_H_
#define MAIN__INDEXES__MAIN_H_
#include "../../main.h"
#ifdef MAIN_INDEXES

#include <string>

#include "../../common/common.h"
#include "../../network/net.h"
#define MAIN_FUNC main_func::main_indexes

// #define MAIN_INDEXES_DATA
#define MAIN_INDEXES_STAT
// #define MAIN_INDEXES_TEST

// ******************************************************
namespace main_func {
int main_indexes(int argc, char** argv);
namespace indexes {
extern std::string kDataDir, kStatDir;
extern std::vector<std::string> kDatasetNames;
extern bool kClean;
}  // namespace indexes
}  // namespace main_func

// ******************************************************
#endif  // MAIN
#endif  // _H_
