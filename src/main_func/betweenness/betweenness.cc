#include "betweenness.h"
#ifdef MAIN_BETWEENNESS

#include <boost/graph/betweenness_centrality.hpp>

#include "../../common/common.h"
#include "../../network/networks.h"
#include "../../statistics/betweenness/betweenness.h"
#include "../../statistics/stat.h"
using namespace std;
using namespace common;
using namespace network;

#ifdef MAIN_BETWEENNESS_STAT_BOOST
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/betweenness_centrality.hpp>
using namespace boost;

#ifdef MAIN_BETWEENNESS_STAT_BOOST_NODE
typedef adjacency_list<vecS, vecS, undirectedS> Graph;
template <typename Graph>
void cal_betweenness_boost(Graph& g, vector<double>& centrality) {
  brandes_betweenness_centrality(
      g, centrality_map(make_iterator_property_map(centrality.begin(),
                                                   get(vertex_index, g))));
}
#endif
#ifdef MAIN_BETWEENNESS_STAT_BOOST_EDGE
typedef adjacency_list<vecS, vecS, undirectedS, no_property,
                       property<edge_index_t, int> >
    Graph;

template <typename Graph>
void cal_betweenness_boost(Graph& g, vector<double>& edge_centrality) {
  brandes_betweenness_centrality(
      g, edge_centrality_map(make_iterator_property_map(
             edge_centrality.begin(), get(edge_index, g), double())));
}
#endif
#ifdef MAIN_BETWEENNESS_STAT_BOOST_NODE_EDGE
typedef adjacency_list<vecS, vecS, undirectedS, no_property,
                       property<edge_index_t, int> >
    Graph;

template <typename Graph>
void cal_betweenness_boost(Graph& g, vector<double>& vertex_centrality,
                           vector<double>& edge_centrality) {
  brandes_betweenness_centrality(
      g, centrality_map(make_iterator_property_map(vertex_centrality.begin(),
                                                   get(vertex_index, g)))
             .edge_centrality_map(make_iterator_property_map(
                 edge_centrality.begin(), get(edge_index, g))));
}
#endif
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
#endif  // MAIN_BETWEENNESS_STAT_BOOST

//**//**************************************************//**//*
#ifdef MAIN_BETWEENNESS_DATA
int main_func::betweenness::networks_data(int argc, char** argv) {
  return EXIT_SUCCESS;
}
#endif  // MAIN_BETWEENNESS_DATA

#ifdef MAIN_BETWEENNESS_STAT
#ifdef MAIN_BETWEENNESS_STAT_BOOST
template <typename Graph>
int net_2_graph(Graph& g, Networks& net) {
  for (LinkType i = 0, p = 0; i < net.linkSize; i++) {
    NodeType x = net.link[p++];
    NodeType y = net.link[p++];
    add_edge(x, y, g);
  }
  return EXIT_SUCCESS;
}

template <typename Graph>
void normalize_betweenness_boost_node(Graph& g, vector<double>& centrality) {
  int n1 = num_vertices(g) - 1;  // n-1
  if (n1 <= 0) return;
  double normalizer = 2.0 / (n1 * (n1 - 1));  // (n-1)(n-2) / 2
  typename graph_traits<Graph>::vertex_iterator vit, vitEnd;
  for (tie(vit, vitEnd) = vertices(g); vit != vitEnd; ++vit) {
    centrality[*vit] *= normalizer;
  }
}

template <typename Graph>
void normalize_betweenness_boost_edge(Graph& g,
                                      vector<double>& edge_centrality) {
  int n = num_vertices(g);  // nodeSize
  if (n <= 0) return;
  double normalizer = 2.0 / (n * (n - 1));  // n(n-1) / 2
  typename graph_traits<Graph>::edge_iterator eit, eitEnd;
  for (tie(eit, eitEnd) = edges(g); eit != eitEnd; ++eit) {
    Edge e = *eit;
    edge_centrality[get(edge_index, g, e)] *= normalizer;
  }
}
#endif  // MAIN_BETWEENNESS_STAT_BOOST

int main_func::betweenness::networks_stat(int argc, char** argv) {
  for (auto& dataset : kDatasetNames) {
    string data_dir = kDataDir + "/" + dataset + "/", stat_dir = data_dir;
    INFORM(dataset, " in ", data_dir);
    mkdirs(stat_dir.c_str());

    Networks net;
    string fn_full = data_dir + dataset;
    net.readName = fn_full;
    net.saveName = fn_full;
    net.dirFlag = 0;
    net.argv =
        " --cal_p2p read_link"
        " --stat"
        " --save";

    // 带参数运行
    if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
      ERROR("net.read_params(argc, argv)");
      break;
    }

    // 功能模块
    // if (0 != net.run().runStatus) {
    //   ERROR("net.run");
    //   cerr << net << endl;
    //   net.saveName += "_error";
    //   net.save_params();
    // }

    {  // read links
      _ERR(read_link(net.link, (fn_full + ".link.txt").c_str()));
      net.linkSize = net.link.size() / 2;
      link_2_nodeSize(net.nodeSize, net.link);

      _ERR(link_2_p2p(net.p2p, net.link, net.nodeSize));
      _ERR(net.p2p_2_degArr().runStatus);
      net.kMin = net.degArrVal.front();
      net.kMax = net.degArrVal.back();
      net.status = 1;
      INFORM("nodeSize: ", net.nodeSize, "\tlinkSize: ", net.linkSize);
    }

    {  // stat betweenness
#ifndef MAIN_BETWEENNESS_STAT_BOOST
      INFORM("stat betweenness");
      // _ERR(net.stat_betweenness().runStatus);
      _ERR(net.stat_betweenness(true).runStatus);  // is_large
#else
      net.saveName += "_boost";
      Graph g(net.nodeSize);
      net_2_graph(g, net);
      INFORM("stat...");
#ifdef MAIN_BETWEENNESS_STAT_BOOST_NODE
      auto& centrality = net.betweenness.betwNode;
      centrality.assign(net.nodeSize, 0);
      cal_betweenness_boost(g, centrality);
      normalize_betweenness_boost_node(g, centrality);
      net.betweenness.meanNode =
          accumulate(centrality.begin(), centrality.end(), 0.0) / net.nodeSize;
#endif
#ifdef MAIN_BETWEENNESS_STAT_BOOST_EDGE
      auto& edge_centrality = net.betweenness.betwLink;
      edge_centrality.assign(net.linkSize, 0);
      // 边的索引映射
      property_map<Graph, edge_index_t>::type e_index = get(edge_index, g);
      int edge_count = 0;
      graph_traits<Graph>::edge_iterator ei, ei_end;
      for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
        put(e_index, *ei, edge_count++);
      }
      cal_betweenness_boost(g, edge_centrality);
      normalize_betweenness_boost_edge(g, edge_centrality);
      net.betweenness.meanEdge =
          accumulate(edge_centrality.begin(), edge_centrality.end(), 0.0) /
          net.linkSize;
#endif
#ifdef MAIN_BETWEENNESS_STAT_BOOST_NODE_EDGE
      auto& centrality = net.betweenness.betwNode;
      auto& edge_centrality = net.betweenness.betwLink;
      centrality.assign(net.nodeSize, 0);
      edge_centrality.assign(net.linkSize, 0);
      // 边的索引映射
      property_map<Graph, edge_index_t>::type e_index = get(edge_index, g);
      int edge_count = 0;
      graph_traits<Graph>::edge_iterator ei, ei_end;
      for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
        put(e_index, *ei, edge_count++);
      }
      cal_betweenness_boost(g, centrality, edge_centrality);
      normalize_betweenness_boost_node(g, centrality);
      normalize_betweenness_boost_edge(g, edge_centrality);
      net.betweenness.meanNode =
          accumulate(centrality.begin(), centrality.end(), 0.0) / net.nodeSize;
      net.betweenness.meanEdge =
          accumulate(edge_centrality.begin(), edge_centrality.end(), 0.0) /
          net.linkSize;
#endif  //
#endif  // MAIN_BETWEENNESS_STAT_BOOST
      net.betweenness.save_data((net.saveName + ".betweenness").c_str());
      // save1((net.saveName + ".betweenness.node.txt").c_str(),
      // net.betweenness.betwNode);
    }
    _ERR(net.save_params().runStatus);
  }
  return EXIT_SUCCESS;
}
#endif  // MAIN_BETWEENNESS_STAT

//**//****************************************************//*
#endif