/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * cs540
 * topology policy
 */

#ifndef TOPOLOGY_POLICY_H
#define TOPOLOGY_POLICY_H

#include <boost/intrusive/options.hpp>
#include <boost/intrusive/list.hpp>

#include <ns3/random-variable.h>

namespace ns3 {
namespace ndn {
namespace ndnSIM {

struct topology_policy_traits
{
  static std::string GetName () { return "TopologyImpl"; }

  //TODO:

};

} // ndnSIM
} // ndn
} // ns3

#endif // TOPOLOGY_POLICY_H
