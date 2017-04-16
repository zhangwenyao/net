#include "NetFoodweb.h"
#ifdef NET_FOODWEB

#include <algorithm>
#include <fstream>
#include <iostream>
#include "common.h"
using namespace std;
//**//*****************************************************//*
int data_read_foodweb1(VNodeType& link, const char* name) {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  ifstream is(name);
  if (!is) {
    ERROR(name);
    return -1;
  }
  LinkType c = 0;
  for (NodeType i, j; is >> i >> j; c++) {
    if (i > 0 && j > 0) {
      link.push_back(--i);
      link.push_back(--j);
    }
  }
  is.close();
  cout << name << '\t' << link.size() / 2 << "\tall:\t" << c << "\n";
  return 0;
}
//**//*****************************************************//*
#endif
