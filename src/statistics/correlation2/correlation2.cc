#include "correlation2.h"
#ifdef STAT_CORRELATION2

#include "../../common/common.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
int correlation2::cal_correlation2(
    double& correlation2, const VVNodeType& p2p)
{
  double sxy = 0, sx = 0, sx2 = 0;
  LinkType l = 0;
  correlation2 = 0;
  for (size_t i = 0; i < p2p.size(); ++i) {
    double id = i;
    for (size_t ii = 0; ii < p2p[i].size(); ++ii) {
      auto j = p2p[i][ii];
      for (size_t ji = 0; ji < p2p[j].size(); ++ji) {
        NodeType k = p2p[j][ji], ki = 0;
        if (k <= i)
          continue;
        for (; ki < p2p[k].size(); ++ki) {
          if (p2p[k][ki] == i)
            break;
        }
        if (ki < p2p[k].size())
          continue;
        sxy += 2.0 * id * k;
        sx += id + k;
        sx2 += id * id + (double)k * k;
        ++l;
      }
    }
  }
  if (l > 0)
    correlation2 = (2.0 * l * sxy - sx * sx) / (2.0 * l * sx2 - sx * sx);
  return 0;
}

// ******************************************************
#endif // STAT_CORRELATION2
