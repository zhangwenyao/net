#ifndef MAIN__SPREADER__MAIN_H_
#define MAIN__SPREADER__MAIN_H_
#include "../../main.h"
#ifdef MAIN_SPREADER

#include <string>

#include "../../common/common.h"
#include "../../network/net.h"
#define MAIN_FUNC main_func::main_spreader

// #define MAIN_SPREADER_DATA
// #define MAIN_SPREADER_CALC
#define MAIN_SPREADER_STAT
// #define MAIN_SPREADER_TEST

// ******************************************************
namespace main_func {
int main_spreader(int argc, char** argv);
int check_args(int argc, char** argv);
namespace spreader {
constexpr int kSeedMin = 1, kSeedMax = 1000;

const std::string kDataDir = std::string("data/spreader/"), kStatDir = kDataDir;
//   kStatDir = std::string("data/spreader/");
const std::string DATASET_NAMES[] = {
    // "example"
    "CondMat"
    // "Email-Enron"
    // "Facebook"
};
const int DATASET_SIZE = sizeof(DATASET_NAMES) / sizeof(DATASET_NAMES[0]);
}  // namespace spreader
}  // namespace main_func

// ******************************************************
#endif  // MAIN
#endif  // _H_
