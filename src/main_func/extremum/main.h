#ifndef MAIN__EXTREMUM__MAIN_H_
#define MAIN__EXTREMUM__MAIN_H_
#include "../../main.h"
#ifdef MAIN_EXTREMUM

//#define MAIN_EXTREMUM_NEW
#define MAIN_EXTREMUM_STAT

// ******************************************************
namespace main_func {
int main_extremum(int argc, char** argv);
}

// ******************************************************
#ifdef MAIN_EXTREMUM_NEW
#include "new.h"
#endif

#ifdef MAIN_EXTREMUM_STAT
#include "stat.h"
#endif

// ******************************************************
#endif // MAIN
#endif // _H_
