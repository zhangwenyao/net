#include "config.h"

using namespace std;
using json = nlohmann::json;

namespace common {
json configs;
string config_file = "config/config.json";
}  // namespace common

int common::init_config(fstream& is) {
  if (!is) return EXIT_FAILURE;
  common::configs = json::parse(is);
  return EXIT_SUCCESS;
}

int common::init_config(const char* config_file) {
  if (NULL == config_file) config_file = common::config_file.c_str();
  ifstream is(config_file);
  if (!is) return EXIT_FAILURE;
  common::configs = json::parse(is);
  is.close();
  return EXIT_SUCCESS;
}