#include "ndn-spt.h"
#include "ndn-name.h"
#include "cs/ndn-content-store.h"
#include <stdio.h>
#include <map>

namespace ns3 {
namespace ndn {

/**
 * Static variables
 */

std::map<std::string, int> s_sourceMap;
int s_prefixLen = 7;

#define NODE_MAX 100
double s_bc[NODE_MAX][NODE_MAX]; //s_bc[nodeId][sourceId]


/**
 * Interface to ndnSIM
 */

void InitSpt() {
  printf("init spt\n");

  /* Initialize bc */
  for(int i = 0; i < NODE_MAX; i++)
    for(int j = 0; j < NODE_MAX; j++)
      s_bc[i][j] = 2;
}

void SetSource(std::string prefix, int sourceId) {
  s_prefixLen = prefix.length();
  s_sourceMap.insert(std::map<std::string, int>::value_type(prefix, sourceId));
}

void SetBetweeness(int nodeId, int sourceId, double bc) {
  s_bc[nodeId][sourceId] = bc;
}


/**
 * Internal function
 */

double getBetweenessWithEntry(Ptr<cs::Entry> entry) {
  int nodeId = entry->m_nodeId;
  std::string prefix = entry->GetName().toUri().substr(0, s_prefixLen);
  int sourceId = s_sourceMap.find(prefix)->second;

  printf("nodeId %d, sourceId %d, prefix %s, bc %f\n", nodeId, sourceId, prefix.c_str(), s_bc[nodeId][sourceId]);
  return s_bc[nodeId][sourceId];
}


/**
 * SPT implementation
 * XXX: not used currently
 */

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
