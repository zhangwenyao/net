#include "NetActor.h"
#ifdef NET_ACTOR

#include <algorithm>
#include <fstream>
#include <iostream>
#include "common.h"
using namespace std;
// *******************************************************
int data_read_actor_p2p(VVNodeType& p2p, const char* name) {
  if (name == NULL || name[0] == '\0') {
    return -1;
  }
  ifstream is(name);
  if (!is) {
    return -1;
  }
  VNodeType v;
  LinkType c = 0;
  while (common_read1_0(is, v) == 0) {  // ���ж�ȡ
    c++;
    if (v.size() < 2) continue;
    sort(v.begin(), v.end());
    if (p2p.size() <= v.back()) p2p.resize(v.back() + 1);
    // ͬһ��Ӱ���У���Ӧ������Ա���ڵ㣩˫������
    for (VNodeTypeCItr i = v.begin(); i < v.end(); i++)
      for (VNodeTypeCItr j = i + 1; j != v.end(); j++) {
        if (*i != *j) {
          p2p[*i].push_back(*j);
          p2p[*j].push_back(*i);
        }
      }
  }
  is.close();
  cout << name << "\t" << c << '\n';
  return 0;
}
// *******************************************************
#endif
