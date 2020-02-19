#include "net_io.h"

#include "../common/common.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
int network::read0_link(VNodeType& link, const char* name, const unsigned n)
{
  if (n < 2 || name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  ifstream is(name);
  if (!is) {
    ERROR(name);
    return -1;
  }
  LinkType c = 0;
  for (NodeType i, j; is >> i >> j; c++) {
    link.push_back(i);
    link.push_back(j);
    unsigned t = 2;
    for (string x; t < n && (is >> x); t++)
      continue;
    if (t < n) {
      is.close();
      ERROR(name, "\t", c, "\t", t);
      return -1;
    }
  }
  is.close();
  cout << name << "\tlink, size:\t" << c << '\n';
  return 0;
}

int network::read_link(VNodeType& link, const char* name)
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  ifstream is(name);
  if (!is) {
    ERROR(name);
    return -1;
  }
  LinkType c = 0;
  for (NodeType i, j; is >> i >> j; c++) {
    link.push_back(i);
    link.push_back(j);
  }
  is.close();
  cout << name << "\tlink, size:\t" << c << '\n';
  return 0;
}

int network::read_weight_link(VVWeightType& vvweight,
    VVWeightType& vvweightIn, const LinkType linkSize, const char* name,
    const unsigned weight_m, const unsigned weight_n, const int dirFlag)
{
  if (weight_m < 2 || weight_m >= weight_n || name == NULL
      || name[0] == '\0') {
    ERROR();
    return -1;
  }
  ifstream is(name);
  if (!is) {
    ERROR(name);
    return -1;
  }
  LinkType l = 0;
  for (NodeType i, j; l < linkSize && is >> i >> j; l++) {
    unsigned c = 2;
    for (string s; c < weight_m && is >> s; c++)
      continue;
    if (c < weight_m) {
      is.close();
      ERROR(name, '\t', l, ":\t", c);
      return -1;
    }
    WeightType w;
    if (!(is >> w)) {
      is.close();
      ERROR(name, '\t', l, ":\t", c);
      return -1;
    }
    if (!dirFlag) {
      NodeType m = i >= j ? i : j;
      if (vvweight.size() <= m)
        vvweight.resize(m + 1);
      vvweight[i].push_back(w);
      vvweight[j].push_back(w);
    } else {
      if (vvweight.size() <= i + 1)
        vvweight.resize(i + 1);
      vvweight[i].push_back(w);
      if (vvweightIn.size() <= j)
        vvweightIn.resize(j + 1);
      vvweightIn[j].push_back(w);
    }
    c++;
    for (string s; c < weight_n && is >> s; c++)
      continue;
    if (c < weight_n) {
      is.close();
      ERROR(name, '\t', l, ':', c);
      return -1;
    }
  }
  is.close();
  if (l < linkSize) {
    is.close();
    ERROR(name, '\t', l);
    return -1;
  }
  cout << name << "\tvvweight, size:\t" << l << '\n';
  return 0;
}

int network::read_link_weight_0(VNodeType& link, LinkType& linkSize,
    VVWeightType& vvweight, VVWeightType& vvweightIn, const char* name,
    const unsigned weight_m, const unsigned weight_n, const int dirFlag)
{
  if (weight_m < 2 || weight_m >= weight_n || name == NULL || name[0] == '\0'
      || !link.empty() || !vvweight.empty()) {
    ERROR();
    return -1;
  }
  ifstream is(name);
  if (!is) {
    ERROR(name);
    return -1;
  }
  for (NodeType i, j; is >> i >> j; linkSize++) {
    link.push_back(i);
    link.push_back(j);
    unsigned c = 2;
    for (string s; c < weight_m && is >> s; c++)
      continue;
    if (c < weight_m) {
      is.close();
      ERROR(name, '\t', linkSize, ":\t", c);
      return -1;
    }

    WeightType w;
    if (!(is >> w)) {
      is.close();
      ERROR(name, '\t', linkSize, ":\t", c);
      return -1;
    }
    c++;

    if (!dirFlag) {
      NodeType m = i >= j ? i : j;
      if (vvweight.size() <= m)
        vvweight.resize(m + 1);
      vvweight[i].push_back(w);
      vvweight[j].push_back(w);
    } else {
      if (vvweight.size() <= i)
        vvweight.resize(i + 1);
      vvweight[i].push_back(w);
      if (vvweightIn.size() <= j)
        vvweightIn.resize(j + 1);
      vvweightIn[j].push_back(w);
    }
    for (string s; c < weight_n && is >> s; c++)
      continue;
    if (c < weight_n) {
      is.close();
      ERROR(name, '\t', linkSize, ':', c);
      return -1;
    }
  }
  is.close();
  cout << name << "\tlink vvweight, size:\t" << linkSize << '\n';
  return 0;
}

// *************************************************************
int network::read_lkk_3(
    istream& is, VVLinkType& lkk, const NodeType degSize, const int rv)
{
  if (!rv) {
    LinkType n;
    for (NodeType i, j; is >> i >> j >> n;) {
      if (i >= lkk.size())
        lkk.resize(i + 1);
      if (j >= lkk[i].size())
        lkk[i].resize(j + 1, 0);
      lkk[i][j] = n;
    }
  } else {
    lkk.resize(degSize);
    if (degSize <= 0)
      return 0;
    LinkType n;
    for (NodeType i, j; is >> i >> j >> n;) {
      if (i > degSize || j > degSize) {
        ERROR();
        return -1;
      }
      i = degSize - i;
      j = degSize - i;
      if (i >= lkk.size())
        lkk.resize(i + 1);
      if (j >= lkk[i].size())
        lkk[i].resize(j + 1, 0);
      lkk[i][j] = n;
    }
  }
  return 0;
}

int network::read_lkk_3(
    const char* name, VVLinkType& lkk, const NodeType degSize, const int rv)
{
  if (!name || name[0] == '\0') {
    ERROR();
    return -1;
  }
  ifstream is(name);
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = read_lkk_3(is, lkk, degSize, rv);
  is.close();
  return flag;
}

int network::save_lkk_3(ostream& os, const VVLinkType& lkk, const int rv,
    const char pri2, const char pri)
{
  if (!os) {
    ERROR();
    return 0;
  }
  if (!rv) {
    for (size_t i = 0; i < lkk.size(); ++i)
      for (size_t j = 0; j < lkk[i].size(); ++j)
        if (lkk[i][j] > 0)
          os << i << pri2 << j << pri2 << lkk[i][j] << pri;
  } else {
    const NodeType degSize = lkk.size();
    for (size_t i = 0; i < lkk.size(); ++i)
      for (size_t j = 0; j < lkk[i].size(); ++j)
        if (lkk[i][j] > 0)
          os << (degSize - i) << pri2 << (degSize - j) << pri2 << lkk[i][j]
             << pri;
  }
  return 0;
}

int network::save_lkk_3(const char* name, const VVLinkType& lkk, const int rv,
    const char pri2, const char pri)
{
  if (!name || name[0] == '\0') {
    ERROR();
    return -1;
  }
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  int flag = save_lkk_3(os, lkk, rv, pri2, pri);
  os.close();
  return flag;
}

int network::read_lkk2(istream& is, VVLkk2LinkType& lkk2)
{
  if(is)
    common::read2_0(is, lkk2);
  return 0;
}

int network::read_lkk2(const char* name, VVLkk2LinkType& lkk2)
{
  if (!name || name[0] == '\0') {
    ERROR();
    return -1;
  }
  ifstream is(name);
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = read_lkk2(is, lkk2);
  is.close();
  return flag;
}

int network::save_lkk2(
    ostream& os, const VVLkk2LinkType& lkk2, const char pri2, const char pri)
{
  if (!os) {
    ERROR();
    return 0;
  }
  common::save2(os, lkk2, pri2);
  return 0;
}

int network::save_lkk2(const char* name, const VVLkk2LinkType& lkk2,
    const char pri2, const char pri)
{
  _ERR(!name || name[0] == '\0');
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  int flag = save_lkk2(os, lkk2, pri2, pri);
  os.close();
  return flag;
}

int network::read_lkk3(istream& is, VLkk3LinkType& lkk3)
{
  LinkType n;
  for (NodeType i, j; is >> i >> j >> n;) {
    lkk3.push_back({ i, j, n });
  }
  return 0;
}

int network::read_lkk3(const char* name, VLkk3LinkType& lkk3)
{
  if (!name || name[0] == '\0') {
    ERROR();
    return -1;
  }
  ifstream is(name);
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = read_lkk3(is, lkk3);
  is.close();
  return flag;
}

int network::save_lkk3(
    ostream& os, const VLkk3LinkType& lkk3, const char pri2, const char pri)
{
  if (!os) {
    ERROR();
    return 0;
  }
  for (auto& i : lkk3)
    os << i.x << pri2 << i.y << pri2 << i.val << pri;
  return 0;
}

int network::save_lkk3(const char* name, const VLkk3LinkType& lkk3,
    const char pri2, const char pri)
{
  _ERR(!name || name[0] == '\0');
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  int flag = save_lkk3(os, lkk3, pri2, pri);
  os.close();
  return flag;
}

int network::save_lkk3reverse(const char* filename, const VLkk3LinkType& lkk3,
    const NodeType max_index, const char priChar2, const char priChar)
{
  _ERR(!filename || filename[0] == '\0');
  ofstream os(filename);
  _ERR(!os);
  for (auto i : lkk3)
    os << max_index - i.x << priChar2 << max_index - i.y << priChar2 << i.val
       << priChar;
  os.close();
  return 0;
}

int network::read_lkk3reverse(
    const char* filename, const NodeType max_index, VLkk3LinkType& lkk3)
{
  _ERR(!filename || filename[0] == '\0');
  ifstream is(filename);
  _ERR(!is);
  LinkType val;
  for (NodeType x, y; is >> x >> y >> val;)
    lkk3.push_back({ max_index - x, max_index - y, val });
  is.close();
  return 0;
}

// *************************************************************
