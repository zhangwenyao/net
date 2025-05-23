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
int network::linkname_2_link(const char* link_name, const char* namefile,
                             const char* linkfile0, const char* linkfile) {
  // link_name to node index
  std::map<LinknameType, NodeType> mp;
  read_link_name(mp, link_name);
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
  VNodeType link0, link;
  {  // linkname to link0
    std::ifstream in(link_name);
    for (LinknameType i, j; in >> i >> j;) {
      NodeType x = mp[i], y = mp[j];
      link0.push_back(x);
      link0.push_back(y);
    }
    in.close();
    common::save1(linkfile0, link0);
  }
  {  // link0_2_link(link, link0);
    std::set<LinkKeyType> st;
    for (auto itr = link0.begin(); itr != link0.end();) {
      NodeType i = *itr++;
      NodeType j = *itr++;
      st.insert(link_key(i, j));
    }
    for (auto key : st) {
      link.push_back(key >> 32);
      link.push_back(key & 0xffffffff);
    }
    common::save1(linkfile, link);
  }
  return 0;
}

// **********************************************************
#endif
