#ifndef COMMON__CONFIG_H_
#define COMMON__CONFIG_H_

#include <fstream>
#include <string>

#include "json.hpp"

// *******************************************************
namespace common {
extern nlohmann::json configs;
extern std::string config_file;
int init_config(std::fstream& is);
int init_config(const char* config_file = NULL);
}  // end namespace common
// *******************************************************
#endif
