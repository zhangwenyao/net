#include "test.h"
#ifdef MAIN_TEST

#include "common/common.h"
#include <iostream>
#include <vector>

using namespace std;

// ******************************************************
int main_func::test(int argc, char** argv)
{
  vector<int> a(3, 2);
  cout << "test" << endl;
  cout << a << endl;
  return 0;
}

// ******************************************************
#endif
