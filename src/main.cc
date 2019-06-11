#include "main.h"
#include "common/common.h"

using namespace std;
using namespace main_func;

// **********************************************************
int main(int argc, char** argv)
{
  common::SHOW_TIME(cout); // 显示系统时间

  _ERR(MAIN_FUNC(argc,argv));

  common::SHOW_TIME(cout); // 显示系统时间
  return 0;
}
