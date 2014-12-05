#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ndnSIM-module.h"
#include "ns3/ndn-cs-tracer.h"

namespace ns3 {
namespace ndn {
  void InitSpt();
  void SetSource(std::string prefix, int sourceId);
  void SetBetweeness(int nodeId, int sourceId, double bc);
}
}

using namespace ns3;

struct MetaInfo {
  std::string name;
  std::string prefix;
};

int
main (int argc, char *argv[])
{
  // setting default parameters for PointToPoint links and channels
  Config::SetDefault ("ns3::PointToPointNetDevice::DataRate", StringValue ("1Mbps"));
  Config::SetDefault ("ns3::PointToPointChannel::Delay", StringValue ("10ms"));
  Config::SetDefault ("ns3::DropTailQueue::MaxPackets", StringValue ("20"));

  // Read optional command-line parameters (e.g., enable visualizer with ./waf --run=<> --visualize
  CommandLine cmd;
  cmd.Parse (argc, argv);

  // Creating nodes
  NodeContainer nodes;
  nodes.Create (3);

  // Connecting nodes using two links
  PointToPointHelper p2p;
  p2p.Install (nodes.Get (0), nodes.Get (1));
  p2p.Install (nodes.Get (1), nodes.Get (2));

  // Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
  ndnHelper.SetDefaultRoutes (true);
  //ndnHelper.SetContentStore("ns3::ndn::cs::Lru", "MaxSize", "10000");
  ndnHelper.SetContentStore("ns3::ndn::cs::Topology", "MaxSize", "5");
  ndnHelper.InstallAll ();


  ns3::ndn::CsTracer::InstallAll("topolog.txt",Seconds(20));

  // Installing applications

  // Consumer
  ndn::AppHelper consumerHelper ("ns3::ndn::ConsumerCbr");
  // Consumer will request /prefix/0, /prefix/1, ...
  consumerHelper.SetPrefix ("/prefix");
  consumerHelper.SetAttribute ("Frequency", StringValue ("10")); // 10 interests a second
  consumerHelper.Install (nodes.Get (0)); // first node

  // Producer
  ndn::AppHelper producerHelper ("ns3::ndn::Producer");
  // Producer will reply to all requests starting with /prefix
  producerHelper.SetPrefix ("/prefix");
  producerHelper.SetAttribute ("PayloadSize", StringValue("1024"));
  producerHelper.Install (nodes.Get (2)); // last node


  // build consumer and producer
  int consumerMetaLen = 2;
  int producerMetaLen = 2;

  MetaInfo consumerMeta[] = {
    {"Node1", "/prefixA"},
    {"Node2", "/prefixB"},
  };

  MetaInfo producerMeta[] = {
    {"Node3", "/prefixA"},
    {"Node4", "/prefixB"},
  };

  for (int i = 0; i < consumerMetaLen; i++) {
    ndn::AppHelper consumerHelper ("ns3::ndn::ConsumerZipfMandelbrot");
    consumerHelper.SetPrefix (consumerMeta[i].prefix);
    consumerHelper.SetAttribute ("NumberOfContents", UintegerValue (200));
    consumerHelper.Install(Names::Find<Node> (consumerMeta[i].name));
  }

  for (int i = 0; i < producerMetaLen; i++) {
    ndn::AppHelper producerHelper ("ns3::ndn::Producer");
    producerHelper.SetPrefix (producerMeta[i].prefix);
    producerHelper.SetAttribute ("PayloadSize", StringValue("1024"));
    producerHelper.Install (Names::Find<Node> (producerMeta[i].name));
  }


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

  Simulator::Stop (Seconds (20.0));

  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
