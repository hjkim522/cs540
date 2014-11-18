/* -*- Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil -*- */
/*
 * Shortest Path Table (SPT)
 *
 * Added for topology experiment
 * Per router table
 * XXX: modifying pit or simpler
 *
 * (src, face, bc) source, face, number of shortest path from source
 * (src, bc) source, betweenness centrality = sum of all bc
 */

#ifndef _NDN_SPT_H_
#define _NDN_SPT_H_

namespace ns3 {
namespace ndn {
namespace spt {

class Entry
{
public:
  int m_sourceId;
  int m_faceId;
  int m_bc;
};

class Spt
{
public:
  // constructor
  Spt ();

  // destructor
  virtual ~Spt ();

  // self node (router) id
  int m_nodeId;

  // entries
  Entry m_entries[];

  // total bc
  int m_bc;
};

} // namespace spt
} // namespace ndn
} // namespace ns3

#endif /* _NDN_SPT_H_ */
