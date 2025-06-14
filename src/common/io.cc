#include "io.h"

#include <iostream>
#include <string>

#include "debug.h"
using namespace std;
using nlohmann::json;

// *************************************************************
int common::check_filename(const string& name) {
  if (name.empty())
    return -1;
  else
    return 0;
}

int common::check_filename(const char* const name) {
  if (name == NULL || name[0] == '\0')
    return -1;
  else
    return 0;
}

int common::save_string(std::ostream& os, const std::string& s) {
  os << s;
  return 0;
}

int common::save_string(const char* name, const std::string& s) {
  if (name == NULL || name[0] == '\0') return -1;
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  os << s;
  os.close();
  return 0;
}

int common::save(const char* name, const string& s) {
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  os << s;
  os.close();
  return 0;
}

int common::save(const char* name, const char* s) {
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  os << s;
  os.close();
  return 0;
}

int common::read(const char* name, string& s) {
  ifstream is(name);
  if (!is) {
    ERROR();
    return -1;
  }
  is >> s;
  is.close();
  return 0;
}

int common::get_string(istream& is, string& s) {
  if (is >> s && !s.empty() && s[0] == '\"') {
    string t;
    if (s.size() == 1 && is >> t) s += std::move(t);
    while (*s.rend() != '\"' && is >> t) {
      s += '\t';
      s += std::move(t);
    }
  }
  if (s.size() == 1 || (s.size() >= 2 && s[0] == '\"' && (*s.rend()) == '\"')) {
    ERROR();
    return -1;
  }
  return 0;
}

// VString
int common::save_VString(std::ostream& os, const std::vector<std::string>& vs) {
  for (std::vector<std::string>::const_iterator i = vs.begin(); i != vs.end();
       ++i)
    os << *i << '\n';
  return 0;
}

int common::save_VString(const char* name, const std::vector<std::string>& vs) {
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  int flag = common::save_VString(os, vs);
  os.close();
  return flag;
}

int common::read_VString(std::istream& is, std::vector<std::string>& vs) {
  for (string s; getline(is, s);) vs.push_back(std::move(s));
  return 0;
}

int common::read_VString(const char* name, std::vector<std::string>& vs) {
  ifstream is(name);
  if (!is) {
    ERROR(name);
    return -1;
  }
  int flag = common::read_VString(is, vs);
  is.close();
  return flag;
}

int common::save(const char* name, const json& j) {
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  os << j;
  os.close();
  return 0;
}

int common::read(const char* name, json& j) {
  ifstream is(name);
  if (!is) {
    ERROR();
    return -1;
  }
  is >> j;
  is.close();
  return 0;
}

int common::save_json(ostream& os, const json& j) {
  os << setw(4) << j;
  return 0;
}

int common::save_json(const char* name, const json& j) {
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  save_json(os, j);
  os.close();
  return 0;
}

// *************************************************************
int common::check_args_config(int argc, char** argv) {
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      if (0 == strcmp(argv[i], "--config")) {
        if (i + 1 < argc) {
          cout << argv[i] << " " << argv[i + 1] << "\n";
          ifstream is(argv[i + 1]);
          if (!is.is_open()) {
            cout << "Error: config file " << argv[i + 1] << " not found!\n";
            return EXIT_FAILURE;
          }
          is >> configs;
          is.close();
          i++;
        }
      }
    }
  }
  return EXIT_SUCCESS;
}

// *************************************************************
