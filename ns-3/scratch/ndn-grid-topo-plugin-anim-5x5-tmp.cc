/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011-2012 University of California, Los Angeles
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 */
// ndn-grid-topo-plugin.cc
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"
#include "ns3/netanim-module.h"
using namespace ns3;
std::string file ="lru-grid-5x5.xml";
/**
 * This scenario simulates a grid topology (using topology reader module)
 *
 * (consumer) -- ( ) ----- ( )
 *     |          |         |
 *    ( ) ------ ( ) ----- ( )
 *     |          |         |
 *    ( ) ------ ( ) -- (producer)
 *
 * All links are 1Mbps with propagation 10ms delay. 
 *
 * FIB is populated using NdnGlobalRoutingHelper.
 *
 * Consumer requests data from producer with frequency 10 interests per second
 * (interests contain constantly increasing sequence number).
 *
 * For every received interest, producer replies with a data packet, containing
 * 1024 bytes of virtual payload.
 *
 * To run scenario and see what is happening, use the following command:
 *
 *     NS_LOG=ndn.Consumer:ndn.Producer ./waf --run=ndn-grid-topo-plugin
 */

int
main (int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);

  AnnotatedTopologyReader topologyReader ("", 25);
  topologyReader.SetFileName ("src/ndnSIM/examples/topologies/topo-grid-5x5.txt");
  topologyReader.Read ();

  // Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
  ndnHelper.SetForwardingStrategy ("ns3::ndn::fw::BestRoute");
  ndnHelper.SetContentStore ("ns3::ndn::cs::Lru", "MaxSize", "3");
  ndnHelper.InstallAll ();

  // Installing global routing interface on all nodes
  ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
  ndnGlobalRoutingHelper.InstallAll ();

std::string prefixA = "/prefixA";
std::string prefixB = "/prefixB";
std::string prefixC = "/prefixC";
std::string prefixD = "/prefixD";

/* Producer */
ndn::AppHelper producerHelperA_16 ("ns3::ndn::Producer");
producerHelperA_16.SetPrefix (prefixA);
producerHelperA_16.SetAttribute ("PayloadSize", StringValue("1024"));
producerHelperA_16.Install (Names::Find<Node> ("Node16"));

ndn::AppHelper producerHelperB_2 ("ns3::ndn::Producer");
producerHelperB_2.SetPrefix (prefixB);
producerHelperB_2.SetAttribute ("PayloadSize", StringValue("1024"));
producerHelperB_2.Install (Names::Find<Node> ("Node2"));

ndn::AppHelper producerHelperC_13 ("ns3::ndn::Producer");
producerHelperC_13.SetPrefix (prefixC);
producerHelperC_13.SetAttribute ("PayloadSize", StringValue("1024"));
producerHelperC_13.Install (Names::Find<Node> ("Node13"));

ndn::AppHelper producerHelperD_24 ("ns3::ndn::Producer");
producerHelperD_24.SetPrefix (prefixD);
producerHelperD_24.SetAttribute ("PayloadSize", StringValue("1024"));
producerHelperD_24.Install (Names::Find<Node> ("Node24"));

/* Consumer */
/* Node 0 */
ndn::AppHelper consumerHelperA_0 ("ns3::ndn::ConsumerCbr");
consumerHelperA_0.SetPrefix (prefixA);
consumerHelperA_0.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperA_0.Install(Names::Find<Node> ("Node0"));

ndn::AppHelper consumerHelperB_0 ("ns3::ndn::ConsumerCbr");
consumerHelperB_0.SetPrefix (prefixB);
consumerHelperB_0.SetAttribute ("Frequency", StringValue ("5")); // 100 interests $
consumerHelperB_0.Install(Names::Find<Node> ("Node0"));

ndn::AppHelper consumerHelperC_0 ("ns3::ndn::ConsumerCbr");
consumerHelperC_0.SetPrefix (prefixC);
consumerHelperC_0.SetAttribute ("Frequency", StringValue ("4")); // 100 interests $
consumerHelperC_0.Install(Names::Find<Node> ("Node0"));

ndn::AppHelper consumerHelperD_0 ("ns3::ndn::ConsumerCbr");
consumerHelperD_0.SetPrefix (prefixD);
consumerHelperD_0.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperD_0.Install(Names::Find<Node> ("Node0"));

/* Node 3 */
ndn::AppHelper consumerHelperA_3 ("ns3::ndn::ConsumerCbr");
consumerHelperA_3.SetPrefix (prefixA);
consumerHelperA_3.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperA_3.Install(Names::Find<Node> ("Node3"));

ndn::AppHelper consumerHelperC_3 ("ns3::ndn::ConsumerCbr");
consumerHelperC_3.SetPrefix (prefixC);
consumerHelperC_3.SetAttribute ("Frequency", StringValue ("4")); // 100 interests $
consumerHelperC_3.Install(Names::Find<Node> ("Node3"));

ndn::AppHelper consumerHelperD_3 ("ns3::ndn::ConsumerCbr");
consumerHelperD_3.SetPrefix (prefixD);
consumerHelperD_3.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperD_3.Install(Names::Find<Node> ("Node3"));

/* Node 4 */
ndn::AppHelper consumerHelperA_4 ("ns3::ndn::ConsumerCbr");
consumerHelperA_4.SetPrefix (prefixA);
consumerHelperA_4.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperA_4.Install(Names::Find<Node> ("Node4"));

ndn::AppHelper consumerHelperB_4 ("ns3::ndn::ConsumerCbr");
consumerHelperB_4.SetPrefix (prefixB);
consumerHelperB_4.SetAttribute ("Frequency", StringValue ("5")); // 100 interests $
consumerHelperB_4.Install(Names::Find<Node> ("Node4"));

ndn::AppHelper consumerHelperC_4 ("ns3::ndn::ConsumerCbr");
consumerHelperC_4.SetPrefix (prefixC);
consumerHelperC_4.SetAttribute ("Frequency", StringValue ("4")); // 100 interests $
consumerHelperC_4.Install(Names::Find<Node> ("Node4"));

ndn::AppHelper consumerHelperD_4 ("ns3::ndn::ConsumerCbr");
consumerHelperD_4.SetPrefix (prefixD);
consumerHelperD_4.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperD_4.Install(Names::Find<Node> ("Node4"));

/* Node 5 */
ndn::AppHelper consumerHelperA_5 ("ns3::ndn::ConsumerCbr");
consumerHelperA_5.SetPrefix (prefixA);
consumerHelperA_5.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperA_5.Install(Names::Find<Node> ("Node5"));

ndn::AppHelper consumerHelperB_5 ("ns3::ndn::ConsumerCbr");
consumerHelperB_5.SetPrefix (prefixB);
consumerHelperB_5.SetAttribute ("Frequency", StringValue ("5")); // 100 interests $
consumerHelperB_5.Install(Names::Find<Node> ("Node5"));

ndn::AppHelper consumerHelperC_5 ("ns3::ndn::ConsumerCbr");
consumerHelperC_5.SetPrefix (prefixC);
consumerHelperC_5.SetAttribute ("Frequency", StringValue ("4")); // 100 interests $
consumerHelperC_5.Install(Names::Find<Node> ("Node5"));

ndn::AppHelper consumerHelperD_5 ("ns3::ndn::ConsumerCbr");
consumerHelperD_5.SetPrefix (prefixD);
consumerHelperD_5.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperD_5.Install(Names::Find<Node> ("Node5"));

/* Node 6 */
ndn::AppHelper consumerHelperA_6 ("ns3::ndn::ConsumerCbr");
consumerHelperA_6.SetPrefix (prefixA);
consumerHelperA_6.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperA_6.Install(Names::Find<Node> ("Node6"));

ndn::AppHelper consumerHelperB_6 ("ns3::ndn::ConsumerCbr");
consumerHelperB_6.SetPrefix (prefixB);
consumerHelperB_6.SetAttribute ("Frequency", StringValue ("5")); // 100 interests $
consumerHelperB_6.Install(Names::Find<Node> ("Node6"));

ndn::AppHelper consumerHelperD_6 ("ns3::ndn::ConsumerCbr");
consumerHelperD_6.SetPrefix (prefixD);
consumerHelperD_6.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperD_6.Install(Names::Find<Node> ("Node6"));

/* Node 9 */
ndn::AppHelper consumerHelperA_9 ("ns3::ndn::ConsumerCbr");
consumerHelperA_9.SetPrefix (prefixA);
consumerHelperA_9.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperA_9.Install(Names::Find<Node> ("Node9"));

ndn::AppHelper consumerHelperB_9 ("ns3::ndn::ConsumerCbr");
consumerHelperB_9.SetPrefix (prefixB);
consumerHelperB_9.SetAttribute ("Frequency", StringValue ("5")); // 100 interests $
consumerHelperB_9.Install(Names::Find<Node> ("Node9"));

ndn::AppHelper consumerHelperC_9 ("ns3::ndn::ConsumerCbr");
consumerHelperC_9.SetPrefix (prefixC);
consumerHelperC_9.SetAttribute ("Frequency", StringValue ("4")); // 100 interests $
consumerHelperC_9.Install(Names::Find<Node> ("Node9"));

ndn::AppHelper consumerHelperD_9 ("ns3::ndn::ConsumerCbr");
consumerHelperD_9.SetPrefix (prefixD);
consumerHelperD_9.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperD_9.Install(Names::Find<Node> ("Node9"));


/* Node 10 */
ndn::AppHelper consumerHelperA_10 ("ns3::ndn::ConsumerCbr");
consumerHelperA_10.SetPrefix (prefixA);
consumerHelperA_10.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperA_10.Install(Names::Find<Node> ("Node10"));

ndn::AppHelper consumerHelperB_10 ("ns3::ndn::ConsumerCbr");
consumerHelperB_10.SetPrefix (prefixB);
consumerHelperB_10.SetAttribute ("Frequency", StringValue ("5")); // 100 interests $
consumerHelperB_10.Install(Names::Find<Node> ("Node10"));

ndn::AppHelper consumerHelperD_10 ("ns3::ndn::ConsumerCbr");
consumerHelperD_10.SetPrefix (prefixD);
consumerHelperD_10.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperD_10.Install(Names::Find<Node> ("Node10"));

/* Node 14 */
ndn::AppHelper consumerHelperA_14 ("ns3::ndn::ConsumerCbr");
consumerHelperA_14.SetPrefix (prefixA);
consumerHelperA_14.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperA_14.Install(Names::Find<Node> ("Node14"));

ndn::AppHelper consumerHelperB_14 ("ns3::ndn::ConsumerCbr");
consumerHelperB_14.SetPrefix (prefixB);
consumerHelperB_14.SetAttribute ("Frequency", StringValue ("5")); // 100 interests $
consumerHelperB_14.Install(Names::Find<Node> ("Node14"));

ndn::AppHelper consumerHelperD_14 ("ns3::ndn::ConsumerCbr");
consumerHelperD_14.SetPrefix (prefixD);
consumerHelperD_14.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperD_14.Install(Names::Find<Node> ("Node14"));

/* Node 17 */
ndn::AppHelper consumerHelperB_17 ("ns3::ndn::ConsumerCbr");
consumerHelperB_17.SetPrefix (prefixB);
consumerHelperB_17.SetAttribute ("Frequency", StringValue ("5")); // 100 interests $
consumerHelperB_17.Install(Names::Find<Node> ("Node17"));

ndn::AppHelper consumerHelperC_17 ("ns3::ndn::ConsumerCbr");
consumerHelperC_17.SetPrefix (prefixC);
consumerHelperC_17.SetAttribute ("Frequency", StringValue ("4")); // 100 interests $
consumerHelperC_17.Install(Names::Find<Node> ("Node17"));

ndn::AppHelper consumerHelperD_17 ("ns3::ndn::ConsumerCbr");
consumerHelperD_17.SetPrefix (prefixD);
consumerHelperD_17.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperD_17.Install(Names::Find<Node> ("Node17"));

/* Node 20 */
ndn::AppHelper consumerHelperA_20 ("ns3::ndn::ConsumerCbr");
consumerHelperA_20.SetPrefix (prefixA);
consumerHelperA_20.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperA_20.Install(Names::Find<Node> ("Node20"));

ndn::AppHelper consumerHelperB_20 ("ns3::ndn::ConsumerCbr");
consumerHelperB_20.SetPrefix (prefixB);
consumerHelperB_20.SetAttribute ("Frequency", StringValue ("5")); // 100 interests $
consumerHelperB_20.Install(Names::Find<Node> ("Node20"));

ndn::AppHelper consumerHelperC_20 ("ns3::ndn::ConsumerCbr");
consumerHelperC_20.SetPrefix (prefixC);
consumerHelperC_20.SetAttribute ("Frequency", StringValue ("4")); // 100 interests $
consumerHelperC_20.Install(Names::Find<Node> ("Node20"));

ndn::AppHelper consumerHelperD_20 ("ns3::ndn::ConsumerCbr");
consumerHelperD_20.SetPrefix (prefixD);
consumerHelperD_20.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperD_20.Install(Names::Find<Node> ("Node20"));

/* Node 21 */
ndn::AppHelper consumerHelperB_21 ("ns3::ndn::ConsumerCbr");
consumerHelperB_21.SetPrefix (prefixB);
consumerHelperB_21.SetAttribute ("Frequency", StringValue ("5")); // 100 interests $
consumerHelperB_21.Install(Names::Find<Node> ("Node21"));

ndn::AppHelper consumerHelperC_21 ("ns3::ndn::ConsumerCbr");
consumerHelperC_21.SetPrefix (prefixC);
consumerHelperC_21.SetAttribute ("Frequency", StringValue ("4")); // 100 interests $
consumerHelperC_21.Install(Names::Find<Node> ("Node21"));

ndn::AppHelper consumerHelperD_21 ("ns3::ndn::ConsumerCbr");
consumerHelperD_21.SetPrefix (prefixD);
consumerHelperD_21.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperD_21.Install(Names::Find<Node> ("Node21"));

/* Node 23 */
ndn::AppHelper consumerHelperA_23 ("ns3::ndn::ConsumerCbr");
consumerHelperA_23.SetPrefix (prefixA);
consumerHelperA_23.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperA_23.Install(Names::Find<Node> ("Node23"));

ndn::AppHelper consumerHelperB_23 ("ns3::ndn::ConsumerCbr");
consumerHelperB_23.SetPrefix (prefixB);
consumerHelperB_23.SetAttribute ("Frequency", StringValue ("5")); // 100 interests $
consumerHelperB_23.Install(Names::Find<Node> ("Node23"));

ndn::AppHelper consumerHelperC_23 ("ns3::ndn::ConsumerCbr");
consumerHelperC_23.SetPrefix (prefixC);
consumerHelperC_23.SetAttribute ("Frequency", StringValue ("4")); // 100 interests $
consumerHelperC_23.Install(Names::Find<Node> ("Node23"));

/* Node 24 */
ndn::AppHelper consumerHelperA_24 ("ns3::ndn::ConsumerCbr");
consumerHelperA_24.SetPrefix (prefixA);
consumerHelperA_24.SetAttribute ("Frequency", StringValue ("3")); // 100 interests $
consumerHelperA_24.Install(Names::Find<Node> ("Node24"));

ndn::AppHelper consumerHelperB_24 ("ns3::ndn::ConsumerCbr");
consumerHelperB_24.SetPrefix (prefixB);
consumerHelperB_24.SetAttribute ("Frequency", StringValue ("5")); // 100 interests $
consumerHelperB_24.Install(Names::Find<Node> ("Node24"));





  // Add /prefix origins to ndn::GlobalRouter
  ndnGlobalRoutingHelper.AddOrigins (prefixA, Names::Find<Node> ("Node16"));
  ndnGlobalRoutingHelper.AddOrigins (prefixB, Names::Find<Node> ("Node2"));
  ndnGlobalRoutingHelper.AddOrigins (prefixC, Names::Find<Node> ("Node13"));
  ndnGlobalRoutingHelper.AddOrigins (prefixD, Names::Find<Node> ("Node24"));

  // Calculate and install FIBs
  ndn::GlobalRoutingHelper::CalculateRoutes ();

  Simulator::Stop (Seconds (20.0));

  AnimationInterface anim (file);
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
