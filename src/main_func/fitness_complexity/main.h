#ifndef MAIN__FITNESS_COMPLEXITY__MAIN_H_
#define MAIN__FITNESS_COMPLEXITY__MAIN_H_
#include "../../main.h"
#ifdef MAIN_FITNESS_COMPLEXITY

#include "../../network/net.h"
#include <string>

//#define FITNESS_COMPLEXITY_MAIN_FILTER
//#define FITNESS_COMPLEXITY_MAIN
//#define FITNESS_COMPLEXITY_MAIN_RECOMMEND
//#define FITNESS_COMPLEXITY_MAIN_COUNT
//#define FITNESS_COMPLEXITY_MAIN_PLOTDATA

// ******************************************************
namespace main_func {
int main_fitness_complexity(int argc, char** argv);

namespace fitness_complexity {

#ifdef FITNESS_COMPLEXITY_MAIN_FILTER
  int main_fitness_complexity_filter(int argc, char** argv);
#endif

#ifdef FITNESS_COMPLEXITY_MAIN
  int main_fitness_complexity(int argc, char** argv);
#endif

#ifdef FITNESS_COMPLEXITY_MAIN_RECOMMEND
  int main_fitness_complexity_recommend(int argc, char** argv);
#endif

#ifdef FITNESS_COMPLEXITY_MAIN_COUNT
  int main_fitness_complexity_count(int argc, char** argv);
#endif

#ifdef FITNESS_COMPLEXITY_MAIN_PLOTDATA
  int main_fitness_complexity_plotdata(int argc, char** argv);
#endif
}
}

// ******************************************************
#endif // MAIN
#endif // _H_
