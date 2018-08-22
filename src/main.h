#ifndef MAIN_H
#define MAIN_H
// g++ *.cpp -O3 -Wall -std=c++11 -o main.exe

// *******************************************************
//#define MAIN_TEST

//#define MAIN_NET_EXTREMUM

//#define MAIN_STAT_LKK_K
//#define MAIN_STAT_LKK_EXTREMUM
//#define MAIN_STAT_BETWEENNESS

//#define MAIN_FITNESS_COMPLEXITY_FILTER
//#define MAIN_FITNESS_COMPLEXITY
//#define MAIN_FITNESS_COMPLEXITY_RECOMMEND
#define MAIN_FITNESS_COMPLEXITY_COUNT
#define MAIN_FITNESS_COMPLEXITY_PLOTDATA

// *******************************************************
#ifdef MAIN_FITNESS_COMPLEXITY_FILTER
int main_fitness_complexity_filter(int argc, char** argv);
#endif

#ifdef MAIN_FITNESS_COMPLEXITY
int main_fitness_complexity(int argc, char** argv);
#endif

#ifdef MAIN_FITNESS_COMPLEXITY_RECOMMEND
int main_fitness_complexity_recommend(int argc, char** argv);
#endif

#ifdef MAIN_FITNESS_COMPLEXITY_COUNT
int main_fitness_complexity_count(int argc, char** argv);
#endif

#ifdef MAIN_FITNESS_COMPLEXITY_PLOTDATA
int main_fitness_complexity_plotdata(int argc, char** argv);
#endif

// *******************************************************
#endif
