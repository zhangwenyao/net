#ifndef MAIN__SPREADER__MAIN_H_
#define MAIN__SPREADER__MAIN_H_
#include "../../main.h"
#ifdef MAIN_SPREADER

#include <string>

#include "../../common/common.h"
#include "../../network/net.h"
#define MAIN_FUNC main_func::main_spreader

// #define MAIN_SPREADER_DATA
#define MAIN_SPREADER_CALC
#define MAIN_SPREADER_STAT
// #define MAIN_SPREADER_TEST

// ******************************************************
namespace main_func {
int main_spreader(int argc, char** argv);
namespace spreader {
extern int kSeedMin, kSeedMax;
extern std::string kDataDir, kStatDir, kStatDir2;
extern std::vector<std::string> kDatasetNames;
extern double kBeta, kGamma, kLambdac;
extern bool kCalcFlag, kStatFlag;
}  // namespace spreader
}  // namespace main_func

// ******************************************************
#endif  // MAIN
#endif  // _H_
