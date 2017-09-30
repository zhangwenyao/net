#include "commonRandom.h"
#include <chrono>
#include <climits>
#include <iostream>
#include <random>

using namespace std;

default_random_engine rand2;
// uniform_real_distribution<double> dis_real(0, std::nextafter(1, DBL_MAX));
// // [0,1]
uniform_real_distribution<double> dis_real(0, 1); // [0,1)
auto rand_double = bind(dis_real, rand2);

long rand_seed(long seed)
{
  if (seed <= 0) {
    uniform_int_distribution<long> ra(0, LONG_MAX);
    seed = -seed;
    rand2.seed(seed);
    seed = ra(rand2) ^ random_device {}();
    rand2.seed(seed);
    seed = ra(rand2)
        ^ chrono::high_resolution_clock::now().time_since_epoch().count();
  }
  rand2.seed(seed);
  return seed;
}
