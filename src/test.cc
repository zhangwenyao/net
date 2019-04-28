#include "test.h"
#ifdef MAIN_TEST

#include "common/common.h"
#include "network/networks.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace network;

// ******************************************************
int main_func::test(int argc, char** argv)
{
  cout << "test" << endl;
  Networks net;
  cout << net << endl;
  return 0;
}

// ******************************************************
#endif
