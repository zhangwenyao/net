#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include "commonRandom.h"

unsigned srand_init(const int seed) {
  if (seed <= 0) {
    unsigned t = -seed;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(t);
    srand(t += rand() + tv.tv_usec);
    srand(t += rand() + time(NULL));
    srand(t += rand() + clock());
    return t;
  }
  srand(seed);
  return seed;
}

#ifdef RAND16807
unsigned rand16807_val = 1;
unsigned rand16807_init(const int seed) {
  srand_init(seed);
  return rand16807_val = rand() % RAND16807_MAX + 1;
}
#endif
