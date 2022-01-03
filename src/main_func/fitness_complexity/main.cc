#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY

#include "../../common/common.h"
#include "../../network/networks.h"

#ifdef MAIN_FITNESS_COMPLEXITY_HOTEL
#ifdef MAIN_FITNESS_COMPLEXITY_HOTEL_FILTER
#include "hotel_filter.h"
#endif
#ifdef MAIN_FITNESS_COMPLEXITY_HOTEL_MAIN
#include "hotel_main.h"
#endif

#else
#ifdef MAIN_FITNESS_COMPLEXITY_FILTER
#include "filter_OEC_sitc_rev2.h"
#endif
#ifdef MAIN_FITNESS_COMPLEXITY_MAIN
#include "fitness_complexity_main.h"
#endif
#ifdef MAIN_FITNESS_COMPLEXITY_RECOMMEND
#include "recommend.h"
#endif
#ifdef MAIN_FITNESS_COMPLEXITY_COUNT
#include "count.h"
#endif
#ifdef MAIN_FITNESS_COMPLEXITY_PLOT_DATA
#include "plot_data.h"
#endif

#endif

using namespace std;
using namespace common;
using namespace network;
using namespace main_func::fitness_complexity;

// **********************************************************
int main_func::main_fitness_complexity(int argc, char** argv) {
#ifdef MAIN_FITNESS_COMPLEXITY_HOTEL
#ifdef MAIN_FITNESS_COMPLEXITY_HOTEL_FILTER
#ifdef MAIN_FITNESS_COMPLEXITY_HOTEL_FILTER0
  _ERR(fitness_complexity::hotel_filter(argc, argv));
#else
  _ERR(fitness_complexity::hotel_filter2(argc, argv));
#endif
#endif
#ifdef MAIN_FITNESS_COMPLEXITY_HOTEL_MAIN
  _ERR(fitness_complexity::hotel_main(argc, argv));
#endif
#else

#ifdef MAIN_FITNESS_COMPLEXITY_FILTER
  _ERR(fitness_complexity::filter(argc, argv));
#endif
#ifdef MAIN_FITNESS_COMPLEXITY_MAIN
  _ERR(fitness_complexity::fitness_complexity_main(argc, argv));
#endif
#ifdef MAIN_FITNESS_COMPLEXITY_RECOMMEND
  _ERR(fitness_complexity::recommend(argc, argv));
#endif
#ifdef MAIN_FITNESS_COMPLEXITY_COUNT
  _ERR(fitness_complexity::count(argc, argv));
#endif
#ifdef MAIN_FITNESS_COMPLEXITY_PLOT_DATA
  _ERR(fitness_complexity::plot_data(argc, argv));
#endif

#endif

  return 0;
}

#endif
