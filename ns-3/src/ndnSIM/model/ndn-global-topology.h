/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/*
 * Global topology setup and calculation module
 * Added for topology experiment
 *
 */

#ifndef NDN_GLOBAL_TOPOLOGY_H
#define NDN_GLOBAL_TOPOLOGY_H

#include "ndn-spt.h"

namespace ns3 {
namespace ndn {

class GlobalTopology
{
public:
  /* Singleton */
  static GlobalTopology *getGlobalTopology();

private:
  /* Constructor */
  GlobalTopology();

public:
  virtual ~GlobalTopology();

  /* Spt tables */
  spt::Spt m_sptTables[];
};

} // namespace ndn
} // namespace ns3

#endif // NDN_GLOBAL_TOPOLOGY_H
