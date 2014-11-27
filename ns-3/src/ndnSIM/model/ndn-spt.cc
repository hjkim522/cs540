#include "ndn-spt.h"
#include "ndn-name.h"
#include <stdio.h>

namespace ns3 {
namespace ndn {

double getWeight(int nodeId, name::Component key) {
  //TODO:
  printf("key %s\n", key.toUri().c_str());
  return 0;
}

namespace spt {

#define MAX_SPT 10

/* Shotest path tables  */
//XXX: use list
Spt s_spt[MAX_SPT];

Spt *getSpt(int nodeId)
{
  s_spt[0].m_nodeId = 1212;
  return &s_spt[nodeId];
}

Spt::Spt ()
{
  //TODO:
}

Spt::~Spt ()
{
  //TODO:
}

} // namespace spt
} // namespace ndn
} // namespace ns
