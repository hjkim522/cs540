#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ndnSIM-module.h"
#include "ns3/netanim-module.h"
#include "ns3/ndn-cs-tracer.h"
#include <iostream>


namespace ns3 {
namespace ndn {
  void InitSpt();
  void SetSource(std::string prefix, int sourceId);
  void SetBetweeness(int nodeId, int sourceId, double bc);
}
}
using namespace ns3;
using namespace std;
std::string file = "gotosleep.xml";
string filename="expResult/bestroute-lru-";


#define MAXSEQ1 200
#define MAXSEQ2 200
#define MAXSEQ3 200
#define MAXSEQ4 200
#define MAXSEQ5 200
#define MAXSEQ6 200

//void ndn::initSpt();

int
main (int argc, char *argv[])
{
  const char*  cacheSize = "500"; //100 ~ 500 incr by 50
  const char* freq1 = "23";
  const char* freq2 = "12";
  const char* freq3 = "57";
  const char* freq4 = "35";
  const char* freq5 = "40";

  // Global topology setup
  //ndn::GlobalTopology *topology = ndn::GlobalTopology::getGlobalTopology();

  // setting default parameters for PointToPoint links and channels
  Config::SetDefault ("ns3::PointToPointNetDevice::DataRate", StringValue ("1Mbps"));
  Config::SetDefault ("ns3::PointToPointChannel::Delay", StringValue ("10ms"));
  Config::SetDefault ("ns3::DropTailQueue::MaxPackets", StringValue ("20"));

  // Read optional command-line parameters (e.g., enable visualizer with ./waf --run=<> --visualize
  CommandLine cmd;
  cmd.Parse (argc, argv);

  AnnotatedTopologyReader topologyReader ("", 25);
  topologyReader.SetFileName ("src/ndnSIM/examples/topologies/topo-grid-5x5-linkdelay.txt");
  topologyReader.Read ();


  // Creating nodes
//  NodeContainer nodes;
//  nodes.Create (3);

  // Connecting nodes using two links
//  PointToPointHelper p2p;
//  p2p.Install (nodes.Get (0), nodes.Get (1));
//  p2p.Install (nodes.Get (1), nodes.Get (2));

  // Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
  ndnHelper.SetDefaultRoutes (true);
  ndnHelper.SetContentStore("ns3::ndn::cs::Lru", "MaxSize", cacheSize);
  //ndnHelper.SetContentStore("ns3::ndn::cs::Topology", "MaxSize", cacheSize);

  //ndnHelper.SetForwardingStrategy ("ns3::ndn::fw::Flooding");
  ndnHelper.SetForwardingStrategy ("ns3::ndn::fw::BestRoute");

  ndnHelper.InstallAll ();
  filename+=string(cacheSize);
  filename+=".ods";
  ndn::CsTracer::InstallAll(filename.c_str(),Seconds(30.0));

  // enable global router
  ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
  ndnGlobalRoutingHelper.InstallAll ();
  ndnGlobalRoutingHelper.AddOrigins ("/prefixA", Names::Find<Node> ("Node16"));
  ndnGlobalRoutingHelper.AddOrigins ("/prefixB", Names::Find<Node> ("Node2"));
  ndnGlobalRoutingHelper.AddOrigins ("/prefixC", Names::Find<Node> ("Node13"));
  ndnGlobalRoutingHelper.AddOrigins ("/prefixD", Names::Find<Node> ("Node24"));

  // Installing applications

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
ndn::AppHelper consumerHelperA_0 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperA_0.SetPrefix (prefixA);
//consumerHelperA_0.SetAttribute ("Frequency", StringValue (freq4)); // 100 interests $
//consumerHelperA_0.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperA_0.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ6)); // 100 interests $
consumerHelperA_0.Install(Names::Find<Node> ("Node0"));

ndn::AppHelper consumerHelperB_0 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperB_0.SetPrefix (prefixB);
//consumerHelperB_0.SetAttribute ("Frequency", StringValue (freq2)); // 100 interests $
//consumerHelperB_0.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperB_0.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ6)); // 100 interests $
consumerHelperB_0.Install(Names::Find<Node> ("Node0"));

ndn::AppHelper consumerHelperC_0 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperC_0.SetPrefix (prefixC);
//consumerHelperC_0.SetAttribute ("Frequency", StringValue (freq3)); // 100 interests $
//consumerHelperC_0.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperC_0.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ2)); // 100 interests $
consumerHelperC_0.Install(Names::Find<Node> ("Node0"));

ndn::AppHelper consumerHelperD_0 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperD_0.SetPrefix (prefixD);
//consumerHelperD_0.SetAttribute ("Frequency", StringValue (freq1)); // 100 interests $
//consumerHelperD_0.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperD_0.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ2)); // 100 interests $
consumerHelperD_0.Install(Names::Find<Node> ("Node0"));

/* Node 3 */
ndn::AppHelper consumerHelperA_3 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperA_3.SetPrefix (prefixA);
//consumerHelperA_3.SetAttribute ("Frequency", StringValue (freq4)); // 100 interests $
//consumerHelperA_3.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperA_3.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ4)); // 100 interests $
consumerHelperA_3.Install(Names::Find<Node> ("Node3"));

ndn::AppHelper consumerHelperC_3 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperC_3.SetPrefix (prefixC);
//consumerHelperC_3.SetAttribute ("Frequency", StringValue (freq1)); // 100 interests $
//consumerHelperC_3.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperC_3.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ4)); // 100 interests $
consumerHelperC_3.Install(Names::Find<Node> ("Node3"));

ndn::AppHelper consumerHelperD_3 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperD_3.SetPrefix (prefixD);
//consumerHelperD_3.SetAttribute ("Frequency", StringValue (freq2)); // 100 interests $
//consumerHelperD_3.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperD_3.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ6)); // 100 interests $
consumerHelperD_3.Install(Names::Find<Node> ("Node3"));

/* Node 4 */
ndn::AppHelper consumerHelperA_4 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperA_4.SetPrefix (prefixA);
//consumerHelperA_4.SetAttribute ("Frequency", StringValue (freq5)); // 100 interests $
//consumerHelperA_4.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperA_4.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ4)); // 100 interests $
consumerHelperA_4.Install(Names::Find<Node> ("Node4"));

ndn::AppHelper consumerHelperB_4 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperB_4.SetPrefix (prefixB);
//consumerHelperB_4.SetAttribute ("Frequency", StringValue (freq2)); // 100 interests $
//consumerHelperB_4.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperB_4.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ5)); // 100 interests $
consumerHelperB_4.Install(Names::Find<Node> ("Node4"));

ndn::AppHelper consumerHelperC_4 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperC_4.SetPrefix (prefixC);
//consumerHelperC_4.SetAttribute ("Frequency", StringValue (freq3)); // 100 interests $
//consumerHelperC_4.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperC_4.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ1)); // 100 interests $
consumerHelperC_4.Install(Names::Find<Node> ("Node4"));

ndn::AppHelper consumerHelperD_4 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperD_4.SetPrefix (prefixD);
//consumerHelperD_4.SetAttribute ("Frequency", StringValue (freq3)); // 100 interests $
//consumerHelperD_4.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperD_4.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ1)); // 100 interests $
consumerHelperD_4.Install(Names::Find<Node> ("Node4"));

/* Node 5 */
ndn::AppHelper consumerHelperA_5 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperA_5.SetPrefix (prefixA);
//consumerHelperA_5.SetAttribute ("Frequency", StringValue (freq1)); // 100 interests $
//consumerHelperA_5.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperA_5.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ1)); // 100 interests $
consumerHelperA_5.Install(Names::Find<Node> ("Node5"));

ndn::AppHelper consumerHelperB_5 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperB_5.SetPrefix (prefixB);
//consumerHelperB_5.SetAttribute ("Frequency", StringValue (freq5)); // 100 interests $
//consumerHelperB_5.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperB_5.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ4)); // 100 interests $
consumerHelperB_5.Install(Names::Find<Node> ("Node5"));

ndn::AppHelper consumerHelperC_5 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperC_5.SetPrefix (prefixC);
//consumerHelperC_5.SetAttribute ("Frequency", StringValue (freq4)); // 100 interests $
//consumerHelperC_5.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperC_5.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ3)); // 100 interests $
consumerHelperC_5.Install(Names::Find<Node> ("Node5"));

ndn::AppHelper consumerHelperD_5 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperD_5.SetPrefix (prefixD);
//consumerHelperD_5.SetAttribute ("Frequency", StringValue (freq2)); // 100 interests $
//consumerHelperD_5.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperD_5.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ2)); // 100 interests $
consumerHelperD_5.Install(Names::Find<Node> ("Node5"));

/* Node 6 */
ndn::AppHelper consumerHelperA_6 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperA_6.SetPrefix (prefixA);
//consumerHelperA_6.SetAttribute ("Frequency", StringValue (freq1)); // 100 interests $
//consumerHelperA_6.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperA_6.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ1)); // 100 interests $
consumerHelperA_6.Install(Names::Find<Node> ("Node6"));

ndn::AppHelper consumerHelperB_6 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperB_6.SetPrefix (prefixB);
//consumerHelperB_6.SetAttribute ("Frequency", StringValue (freq2)); // 100 interests $
//consumerHelperB_6.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperB_6.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ6)); // 100 interests $
consumerHelperB_6.Install(Names::Find<Node> ("Node6"));

ndn::AppHelper consumerHelperD_6 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperD_6.SetPrefix (prefixD);
//consumerHelperD_6.SetAttribute ("Frequency", StringValue (freq3)); // 100 interests $
//consumerHelperD_6.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperD_6.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ1)); // 100 interests $
consumerHelperD_6.Install(Names::Find<Node> ("Node6"));

/* Node 9 */
ndn::AppHelper consumerHelperA_9 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperA_9.SetPrefix (prefixA);
//consumerHelperA_9.SetAttribute ("Frequency", StringValue (freq2)); // 100 interests $
//consumerHelperA_9.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperA_9.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ5)); // 100 interests $
consumerHelperA_9.Install(Names::Find<Node> ("Node9"));

ndn::AppHelper consumerHelperB_9 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperB_9.SetPrefix (prefixB);
//consumerHelperB_9.SetAttribute ("Frequency", StringValue (freq4)); // 100 interests $
//consumerHelperB_9.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperB_9.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ2)); // 100 interests $
consumerHelperB_9.Install(Names::Find<Node> ("Node9"));

ndn::AppHelper consumerHelperC_9 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperC_9.SetPrefix (prefixC);
//consumerHelperC_9.SetAttribute ("Frequency", StringValue (freq3)); // 100 interests $
//consumerHelperC_9.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperC_9.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ2)); // 100 interests $
consumerHelperC_9.Install(Names::Find<Node> ("Node9"));

ndn::AppHelper consumerHelperD_9 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperD_9.SetPrefix (prefixD);
//consumerHelperD_9.SetAttribute ("Frequency", StringValue (freq5)); // 100 interests $
//consumerHelperD_9.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperD_9.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ4)); // 100 interests $

consumerHelperD_9.Install(Names::Find<Node> ("Node9"));


/* Node 10 */
ndn::AppHelper consumerHelperA_10 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperA_10.SetPrefix (prefixA);
//consumerHelperA_10.SetAttribute ("Frequency", StringValue (freq3)); // 100 interests $
//consumerHelperA_10.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperA_10.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ2)); // 100 interests $
consumerHelperA_10.Install(Names::Find<Node> ("Node10"));

ndn::AppHelper consumerHelperB_10 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperB_10.SetPrefix (prefixB);
//consumerHelperB_10.SetAttribute ("Frequency", StringValue (freq1)); // 100 interests $
//consumerHelperB_10.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperB_10.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ5)); // 100 interests $
consumerHelperB_10.Install(Names::Find<Node> ("Node10"));

ndn::AppHelper consumerHelperD_10 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperD_10.SetPrefix (prefixD);
//consumerHelperD_10.SetAttribute ("Frequency", StringValue (freq3)); // 100 interests $
//consumerHelperD_10.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperD_10.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ2)); // 100 interests $
consumerHelperD_10.Install(Names::Find<Node> ("Node10"));

/* Node 14 */
ndn::AppHelper consumerHelperA_14 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperA_14.SetPrefix (prefixA);

//consumerHelperA_14.SetAttribute ("Frequency", StringValue (freq4)); // 100 interests $
//consumerHelperA_14.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperA_14.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ5)); // 100 interests $
consumerHelperA_14.Install(Names::Find<Node> ("Node14"));

ndn::AppHelper consumerHelperB_14 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperB_14.SetPrefix (prefixB);
//consumerHelperB_14.SetAttribute ("Frequency", StringValue (freq3)); // 100 interests $
//consumerHelperB_14.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperB_14.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ5)); // 100 interests $
consumerHelperB_14.Install(Names::Find<Node> ("Node14"));

ndn::AppHelper consumerHelperD_14 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperD_14.SetPrefix (prefixD);
//consumerHelperD_14.SetAttribute ("Frequency", StringValue (freq1)); // 100 interests $
//consumerHelperD_14.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperD_14.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ1)); // 100 interests $
consumerHelperD_14.Install(Names::Find<Node> ("Node14"));

/* Node 17 */
ndn::AppHelper consumerHelperB_17 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperB_17.SetPrefix (prefixB);
//consumerHelperB_17.SetAttribute ("Frequency", StringValue (freq5)); // 100 interests $
//consumerHelperB_17.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperB_17.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ1)); // 100 interests $
consumerHelperB_17.Install(Names::Find<Node> ("Node17"));

ndn::AppHelper consumerHelperC_17 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperC_17.SetPrefix (prefixC);
//consumerHelperC_17.SetAttribute ("Frequency", StringValue (freq3)); // 100 interests $
//consumerHelperC_17.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperC_17.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ6)); // 100 interests $
consumerHelperC_17.Install(Names::Find<Node> ("Node17"));

ndn::AppHelper consumerHelperD_17 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperD_17.SetPrefix (prefixD);
//consumerHelperD_17.SetAttribute ("Frequency", StringValue (freq3)); // 100 interests $
//consumerHelperD_17.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperD_17.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ1)); // 100 interests $
consumerHelperD_17.Install(Names::Find<Node> ("Node17"));

/* Node 20 */
ndn::AppHelper consumerHelperA_20 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperA_20.SetPrefix (prefixA);
//consumerHelperA_20.SetAttribute ("Frequency", StringValue (freq4)); // 100 interests $
//consumerHelperA_20.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperA_20.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ4)); // 100 interests $
consumerHelperA_20.Install(Names::Find<Node> ("Node20"));

ndn::AppHelper consumerHelperB_20 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperB_20.SetPrefix (prefixB);
//consumerHelperB_20.SetAttribute ("Frequency", StringValue (freq5)); // 100 interests $
//consumerHelperB_20.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperB_20.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ3)); // 100 interests $
consumerHelperB_20.Install(Names::Find<Node> ("Node20"));

ndn::AppHelper consumerHelperC_20 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperC_20.SetPrefix (prefixC);
//consumerHelperC_20.SetAttribute ("Frequency", StringValue (freq3)); // 100 interests $
//consumerHelperC_20.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperC_20.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ2)); // 100 interests $
consumerHelperC_20.Install(Names::Find<Node> ("Node20"));

ndn::AppHelper consumerHelperD_20 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperD_20.SetPrefix (prefixD);
//consumerHelperD_20.SetAttribute ("Frequency", StringValue (freq4)); // 100 interests $
//consumerHelperD_20.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperD_20.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ3)); // 100 interests $
consumerHelperD_20.Install(Names::Find<Node> ("Node20"));

/* Node 21 */
ndn::AppHelper consumerHelperB_21 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperB_21.SetPrefix (prefixB);
//consumerHelperB_21.SetAttribute ("Frequency", StringValue (freq2)); // 100 interests $
//consumerHelperB_21.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperB_21.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ6)); // 100 interests $
consumerHelperB_21.Install(Names::Find<Node> ("Node21"));

ndn::AppHelper consumerHelperC_21 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperC_21.SetPrefix (prefixC);
//consumerHelperC_21.SetAttribute ("Frequency", StringValue (freq2)); // 100 interests $
//consumerHelperC_21.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperC_21.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ5)); // 100 interests $
consumerHelperC_21.Install(Names::Find<Node> ("Node21"));

ndn::AppHelper consumerHelperD_21 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperD_21.SetPrefix (prefixD);
//consumerHelperD_21.SetAttribute ("Frequency", StringValue (freq3)); // 100 interests $
//consumerHelperD_21.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperD_21.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ2)); // 100 interests $
consumerHelperD_21.Install(Names::Find<Node> ("Node21"));

/* Node 23 */
ndn::AppHelper consumerHelperA_23 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperA_23.SetPrefix (prefixA);
//consumerHelperA_23.SetAttribute ("Frequency", StringValue (freq1)); // 100 interests $
//consumerHelperA_23.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperA_23.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ1)); // 100 interests $
consumerHelperA_23.Install(Names::Find<Node> ("Node23"));

ndn::AppHelper consumerHelperB_23 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperB_23.SetPrefix (prefixB);
//consumerHelperB_23.SetAttribute ("Frequency", StringValue (freq5)); // 100 interests $
//consumerHelperB_23.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperB_23.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ2)); // 100 interests $
consumerHelperB_23.Install(Names::Find<Node> ("Node23"));

ndn::AppHelper consumerHelperC_23 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperC_23.SetPrefix (prefixC);
//consumerHelperC_23.SetAttribute ("Frequency", StringValue (freq3)); // 100 interests $
//consumerHelperC_23.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperC_23.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ5)); // 100 interests $
consumerHelperC_23.Install(Names::Find<Node> ("Node23"));

/* Node 24 */
ndn::AppHelper consumerHelperA_24 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperA_24.SetPrefix (prefixA);
//consumerHelperA_24.SetAttribute ("Frequency", StringValue (freq3)); // 100 interests $
//consumerHelperA_24.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperA_24.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ6)); // 100 interests $
consumerHelperA_24.Install(Names::Find<Node> ("Node24"));

ndn::AppHelper consumerHelperB_24 ("ns3::ndn::ConsumerZipfMandelbrot");
consumerHelperB_24.SetPrefix (prefixB);
//consumerHelperB_24.SetAttribute ("Frequency", StringValue (freq2)); // 100 interests $
//consumerHelperB_24.SetAttribute ("Randomize", StringValue ("uniform")); // 100 interests $
consumerHelperB_24.SetAttribute ("NumberOfContents", UintegerValue (MAXSEQ2)); // 100 interests $
consumerHelperB_24.Install(Names::Find<Node> ("Node24"));
  // Node config test
  //Ptr<Node> node = nodes.Get (1);
  //Ptr<ndn::ContentStore> cs = node->GetObject<ndn::ContentStore> ();
  //cs->m_nodeId = 3;
  //!fw->m_nodeId was not necessary

  // we can use /prefix
  // we have to use fixed length prefix
  // we need /prefix to sourceId map
  ndn::InitSpt();
  ndn::SetSource("/prefixA", 16);
  ndn::SetSource("/prefixB", 2);
  ndn::SetSource("/prefixC", 13);
  ndn::SetSource("/prefixD", 24);

ndn::SetBetweeness(0,2,0.125);
ndn::SetBetweeness(1,2,0.16666667);
ndn::SetBetweeness(3,2,0.083333336);
ndn::SetBetweeness(4,2,0.041666668);
ndn::SetBetweeness(5,2,0.083333336);
ndn::SetBetweeness(6,2,0.25);
ndn::SetBetweeness(7,2,0.75);
ndn::SetBetweeness(8,2,0.33333334);
ndn::SetBetweeness(9,2,0.16666667);
ndn::SetBetweeness(10,2,0.041666668);
ndn::SetBetweeness(11,2,0.20833333);
ndn::SetBetweeness(12,2,0.125);
ndn::SetBetweeness(13,2,0.125);
ndn::SetBetweeness(14,2,0.125);
ndn::SetBetweeness(15,2,0.083333336);
ndn::SetBetweeness(16,2,0.16666667);
ndn::SetBetweeness(17,2,0.083333336);
ndn::SetBetweeness(18,2,0.083333336);
ndn::SetBetweeness(19,2,0.083333336);
ndn::SetBetweeness(20,2,0.041666668);
ndn::SetBetweeness(21,2,0.041666668);
ndn::SetBetweeness(22,2,0.041666668);
ndn::SetBetweeness(23,2,0.041666668);
ndn::SetBetweeness(24,2,0.041666668);
ndn::SetBetweeness(0,13,0.041666668);
ndn::SetBetweeness(1,13,0.083333336);
ndn::SetBetweeness(2,13,0.125);
ndn::SetBetweeness(3,13,0.041666668);
ndn::SetBetweeness(4,13,0.041666668);
ndn::SetBetweeness(5,13,0.041666668);
ndn::SetBetweeness(6,13,0.083333336);
ndn::SetBetweeness(7,13,0.25);
ndn::SetBetweeness(8,13,0.33333334);
ndn::SetBetweeness(9,13,0.083333336);
ndn::SetBetweeness(10,13,0.041666668);
ndn::SetBetweeness(11,13,0.25);
ndn::SetBetweeness(12,13,0.33333334);
ndn::SetBetweeness(14,13,0.125);
ndn::SetBetweeness(15,13,0.083333336);
ndn::SetBetweeness(16,13,0.16666667);
ndn::SetBetweeness(17,13,0.041666668);
ndn::SetBetweeness(18,13,0.20833333);
ndn::SetBetweeness(19,13,0.041666668);
ndn::SetBetweeness(20,13,0.041666668);
ndn::SetBetweeness(21,13,0.041666668);
ndn::SetBetweeness(22,13,0.041666668);
ndn::SetBetweeness(23,13,0.125);
ndn::SetBetweeness(24,13,0.041666668);
ndn::SetBetweeness(0,16,0.041666668);
ndn::SetBetweeness(1,16,0.041666668);
ndn::SetBetweeness(2,16,0.041666668);
ndn::SetBetweeness(3,16,0.041666668);
ndn::SetBetweeness(4,16,0.041666668);
ndn::SetBetweeness(5,16,0.083333336);
ndn::SetBetweeness(6,16,0.33333334);
ndn::SetBetweeness(7,16,0.25);
ndn::SetBetweeness(8,16,0.16666667);
ndn::SetBetweeness(9,16,0.083333336);
ndn::SetBetweeness(10,16,0.125);
ndn::SetBetweeness(11,16,0.5833333);
ndn::SetBetweeness(12,16,0.083333336);
ndn::SetBetweeness(13,16,0.041666668);
ndn::SetBetweeness(14,16,0.041666668);
ndn::SetBetweeness(15,16,0.083333336);
ndn::SetBetweeness(17,16,0.16666667);
ndn::SetBetweeness(18,16,0.125);
ndn::SetBetweeness(19,16,0.083333336);
ndn::SetBetweeness(20,16,0.041666668);
ndn::SetBetweeness(21,16,0.16666667);
ndn::SetBetweeness(22,16,0.125);
ndn::SetBetweeness(23,16,0.083333336);
ndn::SetBetweeness(24,16,0.041666668);
ndn::SetBetweeness(0,24,0.041666668);
ndn::SetBetweeness(1,24,0.083333336);
ndn::SetBetweeness(2,24,0.125);
ndn::SetBetweeness(3,24,0.041666668);
ndn::SetBetweeness(4,24,0.083333336);
ndn::SetBetweeness(5,24,0.041666668);
ndn::SetBetweeness(6,24,0.083333336);
ndn::SetBetweeness(7,24,0.25);
ndn::SetBetweeness(8,24,0.29166666);
ndn::SetBetweeness(9,24,0.41666666);
ndn::SetBetweeness(10,24,0.041666668);
ndn::SetBetweeness(11,24,0.041666668);
ndn::SetBetweeness(12,24,0.041666668);
ndn::SetBetweeness(13,24,0.083333336);
ndn::SetBetweeness(14,24,0.45833334);
ndn::SetBetweeness(15,24,0.083333336);
ndn::SetBetweeness(16,24,0.083333336);
ndn::SetBetweeness(17,24,0.041666668);
ndn::SetBetweeness(18,24,0.16666667);
ndn::SetBetweeness(19,24,0.5);
ndn::SetBetweeness(20,24,0.125);
ndn::SetBetweeness(21,24,0.25);
ndn::SetBetweeness(22,24,0.29166666);
ndn::SetBetweeness(23,24,0.5);


  ndn::GlobalRoutingHelper::CalculateRoutes ();

  Simulator::Stop (Seconds (30.0));

  AnimationInterface anim (file);
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}

