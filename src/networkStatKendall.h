#ifndef NETWORK_STAT_KENDALL_H
#define NETWORK_STAT_KENDALL_H
#include "StatKendall.h"
#ifdef STAT_KENDALL

#include <iostream>

// ******************************************************
class Stat_kendall {
  public:
    double tau, OutIn;

    Stat_kendall(void);
    friend std::ostream& operator<<(std::ostream& os,
        const Stat_kendall& kendall);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\t') const;
    int save(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\n') const;
    int read_params_1(std::string& s, std::istream& is);
    Stat_kendall& clear(void);
};
std::ostream& operator<<(std::ostream& os, const Stat_kendall& kendall);

// ******************************************************
#endif  // STAT_KENDALL
#endif  // NETWORK_STAT_KENDALL_H

