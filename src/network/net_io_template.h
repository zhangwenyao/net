#ifndef NETWORK__NET_IO_TEMPLATE_H_
#define NETWORK__NET_IO_TEMPLATE_H_

#include <algorithm>
#include <functional>
#include <random>
#include <vector>

#include "net_io.h"

// **********************************************************
template <typename LinknameType>
int network::read_link_name(std::map<LinknameType, NodeType>& mp,
                            const char* name) {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  std::ifstream is(name);
  if (!is) {
    ERROR(name);
    return -1;
  }
  for (LinknameType i, j; is >> i >> j;) {
    if (!mp.count(i)) {
      mp[i] = 0;
    }
    if (!mp.count(j)) {
      mp[j] = 0;
    }
  }
  is.close();
  NodeType i = 0;
  for (auto& it : mp) it.second = i++;
  std::cout << name << "\tnodeSize:\t" << mp.size() << "\n";
  return 0;
}

template <typename LinknameType>
int network::read_link_name_weight(std::map<LinknameType, NodeType>& mp,
                                   const char* name) {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  std::ifstream is(name);
  if (!is) {
    ERROR(name);
    return -1;
  }
  std::string _weight;
  for (LinknameType i, j; is >> i >> j >> _weight;) {
    if (!mp.count(i)) {
      mp[i] = 0;
    }
    if (!mp.count(j)) {
      mp[j] = 0;
    }
  }
  is.close();
  NodeType i = 0;
  for (auto& it : mp) it.second = i++;
  std::cout << name << "\tnodeSize:\t" << mp.size() << "\n";
  return 0;
}

template <typename LinknameType>
int network::linkname_2_link0(const char* linkfile0, const char* linkfile,
                              const char* namefile) {
  // linkname to node index
  std::map<LinknameType, NodeType> mp;
  read_link_name(mp, linkfile0);
  std::vector<LinknameType> names(mp.size());
  for (auto& it : mp) {
    names[it.second] = it.first;
  }
  {  // save linkname
    std::ofstream out(namefile);
    for (auto& name : names) {
      out << name << "\n";
    }
    out.close();
  }
  {  // linkname to link0
    std::ifstream in(linkfile0);
    std::ofstream out(linkfile);
    for (LinknameType i, j; in >> i >> j;) {
      out << mp[i] << "\t" << mp[j] << "\n";
    }
    in.close();
    out.close();
  }
  return 0;
}

template <typename LinknameType>
int network::linkname_2_link(const char* link_name, const char* namefile0,
                             const char* linkfile0, const char* namefile,
                             const char* linkfile, const bool is_weight) {
  // link_name to node index
  std::map<LinknameType, NodeType> mp;
  if (!is_weight)
    read_link_name(mp, link_name);
  else
    read_link_name_weight(mp, link_name);
  std::vector<LinknameType> names0(mp.size());
  for (auto& it : mp) {
    names0[it.second] = it.first;
  }

  // save node name0
  {
    std::ofstream out(namefile0);
    for (auto& name0 : names0) {
      out << name0 << "\n";
    }
    out.close();
  }

  VNodeType link0;
  {  // linkname to link0
    std::ifstream in(link_name);
    if (!is_weight) {
      for (LinknameType i, j; in >> i >> j;) {
        NodeType x = mp[i], y = mp[j];
        link0.push_back(x);
        link0.push_back(y);
      }
    } else {
      std::string _weight;
      for (LinknameType i, j; in >> i >> j >> _weight;) {
        NodeType x = mp[i], y = mp[j];
        link0.push_back(x);
        link0.push_back(y);
      }
    }
    in.close();
    // common::save1(linkfile0, link0);
    save_link(linkfile0, link0);
  }

  VNodeType link;
  {  // link0 to link
    std::set<LinkKeyType> link_set;
    std::map<NodeType, NodeType> nodes_map;
    for (auto itr = link0.begin(); itr != link0.end();) {
      NodeType i = *itr++;
      NodeType j = *itr++;
      if (i == j) {
        INFORM("self-loop: ", i, "-", j);
        continue;
      }
      if (i > j) std::swap(i, j);
      link_set.insert(link_key(i, j));
      nodes_map[i] = i;
      nodes_map[j] = j;
    }
    {
      NodeType id = 0;
      for (auto& itr : nodes_map) itr.second = id++;
    }
    // save nodes name
    {
      std::ofstream out(namefile);
      for (auto& it : nodes_map) {
        out << names0[it.first] << "\n";
      }
      out.close();
    }
    // save links
    for (auto key : link_set) {
      NodeType i0 = key >> 32, j0 = key & 0xffffffff, i = nodes_map[i0],
               j = nodes_map[j0];
      link.push_back(i);
      link.push_back(j);
    }
    // common::save1(linkfile, link);
    save_link(linkfile, link);
  }
  return 0;
}

// **********************************************************
#endif
