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

struct MetaInfo {
  std::string name;
  std::string prefix;
};

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
  topologyReader.SetFileName ("src/ndnSIM/examples/topologies/ndntopo1.txt");
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

  int consumerMetaLen = 24;
  int producerMetaLen = 5;

  struct MetaInfo consumerMeta[] = {
    {"15", "/prefixA"},
    {"17", "/prefixB"},
    {"29", "/prefixC"},
    {"30", "/prefixD"},
    {"32", "/prefixE"},
    {"34", "/prefixA"},
    {"35", "/prefixB"},
    {"36", "/prefixC"},
    {"37", "/prefixD"},
    {"38", "/prefixE"},
    {"31", "/prefixA"},
    {"39", "/prefixB"},
    {"40", "/prefixC"},
    {"41", "/prefixD"},
    {"42", "/prefixE"},
    {"44", "/prefixA"},
    {"19", "/prefixB"},
    {"20", "/prefixC"},
    {"22", "/prefixD"},
    {"23", "/prefixE"},
    {"24", "/prefixA"},
    {"25", "/prefixB"},
    {"27", "/prefixC"},
    {"28", "/prefixD"}
  };

  struct MetaInfo producerMeta[] = {
    {"16", "/prefixA"},
    {"18", "/prefixB"},
    {"21", "/prefixC"},
    {"27", "/prefixD"},
    {"43", "/prefixE"},
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

  ndn::SetBetweeness(0,16,1.0);
  ndn::SetBetweeness(1,16,0.6818182);
  ndn::SetBetweeness(2,16,0.47727272);
  ndn::SetBetweeness(3,16,0.1590909);
  ndn::SetBetweeness(4,16,0.27272728);
  ndn::SetBetweeness(5,16,0.06818182);
  ndn::SetBetweeness(6,16,0.045454547);
  ndn::SetBetweeness(7,16,0.13636364);
  ndn::SetBetweeness(8,16,0.045454547);
  ndn::SetBetweeness(9,16,0.022727273);
  ndn::SetBetweeness(10,16,0.4318182);
  ndn::SetBetweeness(11,16,0.045454547);
  ndn::SetBetweeness(12,16,0.1590909);
  ndn::SetBetweeness(13,16,0.045454547);
  ndn::SetBetweeness(14,16,0.3181818);
  ndn::SetBetweeness(15,16,0.022727273);
  ndn::SetBetweeness(17,16,0.022727273);
  ndn::SetBetweeness(18,16,0.022727273);
  ndn::SetBetweeness(19,16,0.022727273);
  ndn::SetBetweeness(20,16,0.022727273);
  ndn::SetBetweeness(21,16,0.022727273);
  ndn::SetBetweeness(22,16,0.022727273);
  ndn::SetBetweeness(23,16,0.022727273);
  ndn::SetBetweeness(24,16,0.022727273);
  ndn::SetBetweeness(25,16,0.022727273);
  ndn::SetBetweeness(26,16,0.022727273);
  ndn::SetBetweeness(27,16,0.022727273);
  ndn::SetBetweeness(28,16,0.022727273);
  ndn::SetBetweeness(29,16,0.022727273);
  ndn::SetBetweeness(30,16,0.022727273);
  ndn::SetBetweeness(31,16,0.022727273);
  ndn::SetBetweeness(32,16,0.022727273);
  ndn::SetBetweeness(33,16,0.022727273);
  ndn::SetBetweeness(34,16,0.022727273);
  ndn::SetBetweeness(35,16,0.022727273);
  ndn::SetBetweeness(36,16,0.022727273);
  ndn::SetBetweeness(37,16,0.022727273);
  ndn::SetBetweeness(38,16,0.022727273);
  ndn::SetBetweeness(39,16,0.022727273);
  ndn::SetBetweeness(40,16,0.022727273);
  ndn::SetBetweeness(41,16,0.022727273);
  ndn::SetBetweeness(42,16,0.022727273);
  ndn::SetBetweeness(43,16,0.022727273);
  ndn::SetBetweeness(44,16,0.022727273);
  ndn::SetBetweeness(0,18,0.06818182);
  ndn::SetBetweeness(1,18,0.4090909);
  ndn::SetBetweeness(2,18,1.0);
  ndn::SetBetweeness(3,18,0.29545453);
  ndn::SetBetweeness(4,18,0.13636364);
  ndn::SetBetweeness(5,18,0.06818182);
  ndn::SetBetweeness(6,18,0.045454547);
  ndn::SetBetweeness(7,18,0.13636364);
  ndn::SetBetweeness(8,18,0.045454547);
  ndn::SetBetweeness(9,18,0.022727273);
  ndn::SetBetweeness(10,18,0.5681818);
  ndn::SetBetweeness(11,18,0.045454547);
  ndn::SetBetweeness(12,18,0.1590909);
  ndn::SetBetweeness(13,18,0.045454547);
  ndn::SetBetweeness(14,18,0.45454547);
  ndn::SetBetweeness(15,18,0.022727273);
  ndn::SetBetweeness(16,18,0.022727273);
  ndn::SetBetweeness(17,18,0.022727273);
  ndn::SetBetweeness(19,18,0.022727273);
  ndn::SetBetweeness(20,18,0.022727273);
  ndn::SetBetweeness(21,18,0.022727273);
  ndn::SetBetweeness(22,18,0.022727273);
  ndn::SetBetweeness(23,18,0.022727273);
  ndn::SetBetweeness(24,18,0.022727273);
  ndn::SetBetweeness(25,18,0.022727273);
  ndn::SetBetweeness(26,18,0.022727273);
  ndn::SetBetweeness(27,18,0.022727273);
  ndn::SetBetweeness(28,18,0.022727273);
  ndn::SetBetweeness(29,18,0.022727273);
  ndn::SetBetweeness(30,18,0.022727273);
  ndn::SetBetweeness(31,18,0.022727273);
  ndn::SetBetweeness(32,18,0.022727273);
  ndn::SetBetweeness(33,18,0.022727273);
  ndn::SetBetweeness(34,18,0.022727273);
  ndn::SetBetweeness(35,18,0.022727273);
  ndn::SetBetweeness(36,18,0.022727273);
  ndn::SetBetweeness(37,18,0.022727273);
  ndn::SetBetweeness(38,18,0.022727273);
  ndn::SetBetweeness(39,18,0.022727273);
  ndn::SetBetweeness(40,18,0.022727273);
  ndn::SetBetweeness(41,18,0.022727273);
  ndn::SetBetweeness(42,18,0.022727273);
  ndn::SetBetweeness(43,18,0.022727273);
  ndn::SetBetweeness(44,18,0.022727273);
  ndn::SetBetweeness(0,21,0.06818182);
  ndn::SetBetweeness(1,21,0.09090909);
  ndn::SetBetweeness(2,21,0.045454547);
  ndn::SetBetweeness(3,21,0.27272728);
  ndn::SetBetweeness(4,21,1.0);
  ndn::SetBetweeness(5,21,0.11363637);
  ndn::SetBetweeness(6,21,0.045454547);
  ndn::SetBetweeness(7,21,0.5);
  ndn::SetBetweeness(8,21,0.045454547);
  ndn::SetBetweeness(9,21,0.022727273);
  ndn::SetBetweeness(10,21,0.06818182);
  ndn::SetBetweeness(11,21,0.045454547);
  ndn::SetBetweeness(12,21,0.1590909);
  ndn::SetBetweeness(13,21,0.045454547);
  ndn::SetBetweeness(14,21,0.1590909);
  ndn::SetBetweeness(15,21,0.022727273);
  ndn::SetBetweeness(16,21,0.022727273);
  ndn::SetBetweeness(17,21,0.022727273);
  ndn::SetBetweeness(18,21,0.022727273);
  ndn::SetBetweeness(19,21,0.022727273);
  ndn::SetBetweeness(20,21,0.022727273);
  ndn::SetBetweeness(22,21,0.022727273);
  ndn::SetBetweeness(23,21,0.022727273);
  ndn::SetBetweeness(24,21,0.022727273);
  ndn::SetBetweeness(25,21,0.022727273);
  ndn::SetBetweeness(26,21,0.022727273);
  ndn::SetBetweeness(27,21,0.022727273);
  ndn::SetBetweeness(28,21,0.022727273);
  ndn::SetBetweeness(29,21,0.022727273);
  ndn::SetBetweeness(30,21,0.022727273);
  ndn::SetBetweeness(31,21,0.022727273);
  ndn::SetBetweeness(32,21,0.022727273);
  ndn::SetBetweeness(33,21,0.022727273);
  ndn::SetBetweeness(34,21,0.022727273);
  ndn::SetBetweeness(35,21,0.022727273);
  ndn::SetBetweeness(36,21,0.022727273);
  ndn::SetBetweeness(37,21,0.022727273);
  ndn::SetBetweeness(38,21,0.022727273);
  ndn::SetBetweeness(39,21,0.022727273);
  ndn::SetBetweeness(40,21,0.022727273);
  ndn::SetBetweeness(41,21,0.022727273);
  ndn::SetBetweeness(42,21,0.022727273);
  ndn::SetBetweeness(43,21,0.022727273);
  ndn::SetBetweeness(44,21,0.022727273);
  ndn::SetBetweeness(0,26,0.06818182);
  ndn::SetBetweeness(1,26,0.045454547);
  ndn::SetBetweeness(2,26,0.09090909);
  ndn::SetBetweeness(3,26,0.06818182);
  ndn::SetBetweeness(4,26,0.13636364);
  ndn::SetBetweeness(5,26,0.06818182);
  ndn::SetBetweeness(6,26,0.045454547);
  ndn::SetBetweeness(7,26,0.9318182);
  ndn::SetBetweeness(8,26,1.0);
  ndn::SetBetweeness(9,26,0.022727273);
  ndn::SetBetweeness(10,26,0.22727273);
  ndn::SetBetweeness(11,26,0.045454547);
  ndn::SetBetweeness(12,26,0.1590909);
  ndn::SetBetweeness(13,26,0.045454547);
  ndn::SetBetweeness(14,26,0.38636363);
  ndn::SetBetweeness(15,26,0.022727273);
  ndn::SetBetweeness(16,26,0.022727273);
  ndn::SetBetweeness(17,26,0.022727273);
  ndn::SetBetweeness(18,26,0.022727273);
  ndn::SetBetweeness(19,26,0.022727273);
  ndn::SetBetweeness(20,26,0.022727273);
  ndn::SetBetweeness(21,26,0.022727273);
  ndn::SetBetweeness(22,26,0.022727273);
  ndn::SetBetweeness(23,26,0.022727273);
  ndn::SetBetweeness(24,26,0.022727273);
  ndn::SetBetweeness(25,26,0.022727273);
  ndn::SetBetweeness(27,26,0.022727273);
  ndn::SetBetweeness(28,26,0.022727273);
  ndn::SetBetweeness(29,26,0.022727273);
  ndn::SetBetweeness(30,26,0.022727273);
  ndn::SetBetweeness(31,26,0.022727273);
  ndn::SetBetweeness(32,26,0.022727273);
  ndn::SetBetweeness(33,26,0.022727273);
  ndn::SetBetweeness(34,26,0.022727273);
  ndn::SetBetweeness(35,26,0.022727273);
  ndn::SetBetweeness(36,26,0.022727273);
  ndn::SetBetweeness(37,26,0.022727273);
  ndn::SetBetweeness(38,26,0.022727273);
  ndn::SetBetweeness(39,26,0.022727273);
  ndn::SetBetweeness(40,26,0.022727273);
  ndn::SetBetweeness(41,26,0.022727273);
  ndn::SetBetweeness(42,26,0.022727273);
  ndn::SetBetweeness(43,26,0.022727273);
  ndn::SetBetweeness(44,26,0.022727273);
  ndn::SetBetweeness(0,43,0.06818182);
  ndn::SetBetweeness(1,43,0.11363637);
  ndn::SetBetweeness(2,43,0.1590909);
  ndn::SetBetweeness(3,43,0.06818182);
  ndn::SetBetweeness(4,43,0.06818182);
  ndn::SetBetweeness(5,43,0.11363637);
  ndn::SetBetweeness(6,43,0.045454547);
  ndn::SetBetweeness(7,43,0.4090909);
  ndn::SetBetweeness(8,43,0.045454547);
  ndn::SetBetweeness(9,43,0.022727273);
  ndn::SetBetweeness(10,43,0.29545453);
  ndn::SetBetweeness(11,43,0.045454547);
  ndn::SetBetweeness(12,43,0.1590909);
  ndn::SetBetweeness(13,43,0.045454547);
  ndn::SetBetweeness(14,43,1.0);
  ndn::SetBetweeness(15,43,0.022727273);
  ndn::SetBetweeness(16,43,0.022727273);
  ndn::SetBetweeness(17,43,0.022727273);
  ndn::SetBetweeness(18,43,0.022727273);
  ndn::SetBetweeness(19,43,0.022727273);
  ndn::SetBetweeness(20,43,0.022727273);
  ndn::SetBetweeness(21,43,0.022727273);
  ndn::SetBetweeness(22,43,0.022727273);
  ndn::SetBetweeness(23,43,0.022727273);
  ndn::SetBetweeness(24,43,0.022727273);
  ndn::SetBetweeness(25,43,0.022727273);
  ndn::SetBetweeness(26,43,0.022727273);
  ndn::SetBetweeness(27,43,0.022727273);
  ndn::SetBetweeness(28,43,0.022727273);
  ndn::SetBetweeness(29,43,0.022727273);
  ndn::SetBetweeness(30,43,0.022727273);
  ndn::SetBetweeness(31,43,0.022727273);
  ndn::SetBetweeness(32,43,0.022727273);
  ndn::SetBetweeness(33,43,0.022727273);
  ndn::SetBetweeness(34,43,0.022727273);
  ndn::SetBetweeness(35,43,0.022727273);
  ndn::SetBetweeness(36,43,0.022727273);
  ndn::SetBetweeness(37,43,0.022727273);
  ndn::SetBetweeness(38,43,0.022727273);
  ndn::SetBetweeness(39,43,0.022727273);
  ndn::SetBetweeness(40,43,0.022727273);
  ndn::SetBetweeness(41,43,0.022727273);
  ndn::SetBetweeness(42,43,0.022727273);
  ndn::SetBetweeness(44,43,0.022727273);


  Simulator::Stop (Seconds (30.0));

  AnimationInterface anim (file);
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}

