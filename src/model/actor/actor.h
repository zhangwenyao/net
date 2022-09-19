#ifndef MODEL__ACTOR__ACTOR_H_
#define MODEL__ACTOR__ACTOR_H_
#include "../../network/net.h"
#ifdef NET_ACTOR

namespace network {
namespace actor {
  // *******************************************************
  int data_read_actor_p2p(VVNodeType& p2p, const char* name);
}
}

// *******************************************************
#endif
#endif // _H_
