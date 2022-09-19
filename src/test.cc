#include "test.h"
#ifdef MAIN_TEST

#include "common/common.h"
#include "network/networks.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace common;
using namespace network;

// ******************************************************
int main_func::main_test(int argc, char** argv)
{
  cout << "test" << endl;
  Networks net;
  cout << net << endl;
  cout << net.lkk3 << endl;
  operator<<(cout, net.lkk3);
  Struct3<int, int, int> l3;
  l3.x = 1;
  l3.y = 2;
  l3.val = 11;
  cout << l3 << endl;
  vector<Struct3<int, int, int>> l2(2, l3);
  cout << l2 << endl;
  // save_VStruct3(cout, l2);
  vector<int> a(3, 22);
  vector<vector<int>> aa(2, a);
  cout << aa << endl;
  return 0;
}

// ******************************************************
#endif
