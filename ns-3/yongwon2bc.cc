#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ndnSIM-module.h"
#include "ns3/netanim-module.h"
namespace ns3 {
namespace ndn {
  void InitSpt();
  void SetSource(std::string prefix, int sourceId);
  void SetBetweeness(int nodeId, int sourceId, double bc);
}
}
using namespace ns3;
std::string file = "testver.xml";

//void ndn::initSpt();

int
main (int argc, char *argv[])
{
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
  topologyReader.SetFileName ("src/ndnSIM/examples/topologies/topo-grid-2x2.txt");
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
  //ndnHelper.SetContentStore("ns3::ndn::cs::Lru", "MaxSize", "10000");
  ndnHelper.SetContentStore("ns3::ndn::cs::Topology", "MaxSize", "10");
  ndnHelper.InstallAll ();

  // Installing applications

  // Consumer
  ndn::AppHelper consumerHelper ("ns3::ndn::ConsumerCbr");
  // Consumer will request /prefix/0, /prefix/1, ...
  consumerHelper.SetPrefix ("/prefix");
  consumerHelper.SetAttribute ("Frequency", StringValue ("10")); // 10 interests a second
  consumerHelper.Install (Names::Find<Node> ("Node0")); // first node
  ndn::AppHelper consumerHelper1 ("ns3::ndn::ConsumerCbr");
  // Consumer will request /prefix/0, /prefix/1, ...
  consumerHelper1.SetPrefix ("/prefix");
  consumerHelper1.SetAttribute ("Frequency", StringValue ("5")); // 10 interests a second
  consumerHelper1.Install (Names::Find<Node> ("Node0")); // first node

  // Producer
  ndn::AppHelper producerHelper ("ns3::ndn::Producer");
  // Producer will reply to all requests starting with /prefix
  producerHelper.SetPrefix ("/prefix");
  producerHelper.SetAttribute ("PayloadSize", StringValue("1024"));
  producerHelper.Install (Names::Find<Node> ("Node3")); // last node

  // Node config test
  //Ptr<Node> node = nodes.Get (1);
  //Ptr<ndn::ContentStore> cs = node->GetObject<ndn::ContentStore> ();
  //cs->m_nodeId = 3;
  //!fw->m_nodeId was not necessary

  // we can use /prefix
  // we have to use fixed length prefix
  // we need /prefix to sourceId map
  ndn::InitSpt();
  ndn::SetSource("/prefix", 2);
  ndn::SetBetweeness(0,2,3);
  ndn::SetBetweeness(1,2,4);
  ndn::SetBetweeness(2,2,0);
  ndn::SetBetweeness(3,2,2);
  ndn::SetBetweeness(0,1,4);
  ndn::SetBetweeness(1,1,0);
  ndn::SetBetweeness(2,1,4);
  ndn::SetBetweeness(3,1,4);
  ndn::SetBetweeness(0,0,0);
  ndn::SetBetweeness(1,0,4);
  ndn::SetBetweeness(2,0,3);
  ndn::SetBetweeness(3,0,4);
  ndn::SetBetweeness(0,3,4);
  ndn::SetBetweeness(1,3,4);
  ndn::SetBetweeness(2,3,2);
  ndn::SetBetweeness(3,3,0);

  Simulator::Stop (Seconds (5.0));

  AnimationInterface anim (file);
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
