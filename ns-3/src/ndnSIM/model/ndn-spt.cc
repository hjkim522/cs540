#include "ndn-spt.h"
#include "ndn-name.h"
#include "cs/ndn-content-store.h"
#include <stdio.h>
#include <map>

namespace ns3 {
namespace ndn {

std::map<std::string, int> s_sourceMap;
int s_prefixLen = 7;

#define NODE_MAX 100
double s_bc[NODE_MAX][NODE_MAX]; //bc[nodeId][sourceId]

/**
 * Interface to ndnSIM
 */

void InitSpt() {
  printf("init spt\n");

  /* Initialize bc */
  for(int i = 0; i < NODE_MAX; i++)
    for(int j = 0; j < NODE_MAX; j++)
      s_bc[i][j] = 2;

  s_sourceMap.insert(std::map<std::string, int>::value_type("/prefix", 9));

  int src = s_sourceMap.find("/prefix")->second;
  printf("src %d\n", src);
}

void SetSource(std::string prefix, int sourceId) {
  s_prefixLen = prefix.length();
  s_sourceMap.insert(std::map<std::string, int>::value_type(prefix, sourceId));
}

void SetBetweeness(int nodeId, int sourceId, double bc) {
  s_bc[nodeId][sourceId] = bc;
}

/**
 * Internal functions
 */

void testWithEntry(Ptr<cs::Entry> entry) {
  //nodeId
  //entry->m_nodeId

  printf("entry->GetName(); %s\n", entry->GetName ().toUri().c_str());
  //printf("prefix %s\n", entry->GetName().getPrefix().toUri().c_str());
}

//XXX: not work... srcid need to be hard copied
//XXX: modify pkt...
double getBetweenessCentrality(int nodeId, int sourceId) {
  printf("node %d, source %d\n", nodeId, sourceId);
  return s_bc[nodeId][sourceId];
}

double getWeight(int nodeId, name::Component key) {
  //TODO:
  //printf("nodeid %d, key %s\n", nodeId, key.toUri().c_str());
  printf("nodeid %d, key %d\n", nodeId, key.toSeqNum ());

  //printf("prefix : %s\n", key.)

  // TODO: convert key to sourceId
  // get betweeness centrality
  int sourceId = 0;

  return getBetweenessCentrality(nodeId, sourceId);
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
