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
string filename="expResult/ConSize200zipfBC-topo";


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
  const char*  cacheSize = "500";
  const char* freq1 = "23";
  const char* freq2 = "12";
  const char* freq3 = "57";
  const char* freq4 = "35";
  const char* freq5 = "40";

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

  // Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
  ndnHelper.SetDefaultRoutes (true);
  //ndnHelper.SetContentStore("ns3::ndn::cs::Lru", "MaxSize", cacheSize);
  ndnHelper.SetContentStore("ns3::ndn::cs::Topology", "MaxSize", cacheSize);
  ndnHelper.InstallAll ();
  filename+=string(cacheSize);
  filename+=".ods";
  ndn::CsTracer::InstallAll(filename.c_str(),Seconds(30.0));

  // Installing applications
  std::string prefixA = "/prefixA";
  std::string prefixB = "/prefixB";
  std::string prefixC = "/prefixC";
  std::string prefixD = "/prefixD";

  int consumerMetaLen = 2;
  int producerMetaLen = 5;

  MetaInfo consumerMeta[] = {
    {"Node1", "/prefixA"},
    {"Node2", "/prefixB"},
  };

  MetaInfo producerMeta[] = {
    {"Node16", "/prefixA"},
    {"Node18", "/prefixB"},
    {"Node21", "/prefixC"},
    {"Node27", "/prefixD"},
    {"Node43", "/prefixE"},
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


  // topology
  ndn::InitSpt();
  ndn::SetSource("/prefixA", 16);
  ndn::SetSource("/prefixB", 18);
  ndn::SetSource("/prefixC", 21);
  ndn::SetSource("/prefixD", 27);
  ndn::SetSource("/prefixD", 43);



  Simulator::Stop (Seconds (30.0));

  AnimationInterface anim (file);
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}

