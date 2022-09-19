#include "actor.h"
#ifdef NET_ACTOR

#include "../../common/common.h"
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;
using namespace common;
using namespace network;

// *******************************************************
int network::actor::data_read_actor_p2p(VVNodeType& p2p, const char* name)
{
  if (name == NULL || name[0] == '\0') {
    return -1;
  }
  ifstream is(name);
  if (!is) {
    return -1;
  }
  VNodeType v;
  LinkType c = 0;
  while (read1_0(is, v) == 0) { // 逐行读取
    c++;
    if (v.size() < 2)
      continue;
    sort(v.begin(), v.end());
    if (p2p.size() <= v.back())
      p2p.resize(v.back() + 1);
    // 同一电影（行）对应所有演员（节点）双向连边
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

