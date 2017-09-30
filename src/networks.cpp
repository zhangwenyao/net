#include "networks.h"

#include "common.h"
using namespace std;

//**//****************************************************//*
Networks::Networks(void)
    : net2(NULL)
{
}

// Networks::~Networks(void) {}

Networks& Networks::clear(void)
{
  Network::clear();

#ifdef STAT_PEARSON
  pearson.clear();
#endif

#ifdef STAT_SPEARMAN
  spearman.clear();
#endif

#ifdef STAT_KELDALLTAU
  kendallTau.clear();
#endif

#ifdef STAT_BETWEENNESS
  betweenness.clear();
#endif

#ifdef STAT_MODULARITY
  modularity.clear();
#endif

#ifdef STAT_CLUSTER
  cluster.clear();
#endif

#ifdef ACT_SIS
  sis.clear();
#endif

  return *this;
}

//**//****************************************************//*
ostream& operator<<(ostream& os, Networks& net)
{
  if (!os) {
    net.runStatus = -1;
    ERROR();
    return os;
  }

  net.Network::save_params(os);

#ifdef NET_DEGREE
  os << net.degree;
#endif

#ifdef NET_RANDOM
  os << net.random;
#endif

#ifdef NET_BA
  os << net.ba;
#endif

#ifdef NET_GRID
  os << net.grid;
#endif

#ifdef STAT_BETWEENNESS
  os << net.betweenness;
#endif

#ifdef STAT_MODULARITY
  os << net.modularity;
#endif

#ifdef STAT_CLUSTER
  os << net.cluster;
#endif

#ifdef STAT_PEARSON
  os << net.pearson;
#endif

#ifdef STAT_SPEARMAN
  os << net.spearman;
#endif

#ifdef STAT_KENDALL
  os << net.kendall;
#endif

#ifdef ACT_SIS
  os << net.sis;
#endif

  return os;
}

Networks& Networks::save_params(std::ostream& os)
{
  if (!os) {
    runStatus = 1;
    ERROR();
  }
  os << *this;
  return *this;
}

Networks& Networks::save_params(const char* name)
{
  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else {
    stringstream ss;
    ss << seed;
    fn = saveName + '_' + ss.str();
  }
  ofstream os((fn + ".params.txt").c_str());
  if (!os) {
    ERROR();
    return *this;
  }
  os << *this;
  os.close();
  return *this;
}

Networks& Networks::save_data(const char* name)
{
  string fn;
  stringstream ss;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else {
    ss.clear();
    ss << seed;
    fn = saveName + '_' + ss.str();
  }

  Network::save_data(fn.c_str());
  if (0 != runStatus)
    ERROR();

#ifdef NET_DEGREE
  runStatus = degree.save_data((fn + ".degree").c_str());
  if (0 != runStatus)
    ERROR();
#endif

#ifdef NET_BA
  runStatus = ba.save_data((fn + ".ba").c_str());
  if (0 != runStatus)
    ERROR();
#endif

#ifdef STAT_PEARSON
  runStatus = pearson.save_data(
      (fn + ".pearson").c_str(), dirFlag, priChar, priChar2);
  if (0 != runStatus)
    ERROR();
#endif

#ifdef STAT_SPEARMAN
  runStatus = spearman.save_data(
      (fn + ".spearman").c_str(), dirFlag, priChar, priChar2);
  if (0 != runStatus)
    ERROR();
#endif

#ifdef STAT_KENDALL
  runStatus = kendall.save_data((fn + ".kendall").c_str(), priChar, priChar2);
  if (0 != runStatus)
    ERROR();
#endif

#ifdef STAT_BETWEENNESS
  runStatus = betweenness.save_data(
      (fn + ".betweenness").c_str(), priChar, priChar2);
  if (0 != runStatus)
    ERROR();
#endif

#ifdef STAT_MODULARITY
  runStatus
      = modularity.save_data((fn + ".modularity").c_str(), priChar, priChar2);
  if (0 != runStatus)
    ERROR();
#endif

#ifdef STAT_SIMILARITY
  runStatus
      = similarity.save_data((fn + ".similarity").c_str(), priChar, priChar2);
  if (0 != runStatus)
    ERROR();
#endif

#ifdef STAT_CLUSTER
  runStatus = cluster.save_data((fn + ".cluster").c_str(), priChar, priChar2);
  if (0 != runStatus)
    ERROR();
#endif

#ifdef ACT_SIS
  runStatus = sis.save_data((fn + ".sis").c_str());
  if (0 != runStatus)
    ERROR();
#endif

  return *this;
}

Networks& Networks::save(const char* name)
{
  if (0 != save_params(name).runStatus)
    ERROR();
  if (0 != save_data(name).runStatus)
    ERROR();
  return *this;
}

//**//****************************************************//*
std::istream& operator>>(std::istream& is, Networks& net)
{
  if (0 != net.runStatus || !is) {
    ERROR();
    return is;
  }
  for (string s; is >> s;) {
    if (s.size() <= 0)
      continue;
    if (0 != net.read_params_1(s, is).runStatus || s.size() > 0) {
      net.runStatus = -1;
      ERROR(s);
      break;
    }
  }
  return is;
}

Networks& Networks::read_params_1(string& s, istream& is)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (s.size() <= 0)
    return *this;
  do {
    if (s == "--file") {
      cout << s << '\t';
      is >> s;
      cout << s << endl;
      if (!is || s.size() <= 0 || s == readName) {
        runStatus = -1;
        ERROR();
        return *this;
      }
      readName = s;
      s.clear();
      if (0 != read_params(readName.c_str()).runStatus) {
        runStatus = -1;
        ERROR();
        return *this;
      }
      break;
    }

    if (0 != Network::read_params_1(s, is).runStatus) {
      ERROR();
      runStatus = -1;
      return *this;
    }
    if (s.size() <= 0)
      break;

#ifdef NET_DEGREE
    if (0 != degree.read_params_1(s, is)) {
      ERROR();
      runStatus = -1;
      return *this;
    }
    if (s.size() <= 0)
      break;
#endif

#ifdef NET_RANDOM
    if (0 != random.read_params_1(s, is)) {
      ERROR();
      runStatus = -1;
      return *this;
    }
    if (s.size() <= 0)
      break;
#endif

#ifdef NET_BA
    if (0 != ba.read_params_1(s, is)) {
      ERROR();
      runStatus = -1;
      return *this;
    }
    if (s.size() <= 0)
      break;
#endif

#ifdef NET_GRID
    if (0 != grid.read_params_1(s, is)) {
      ERROR();
      runStatus = -1;
      return *this;
    }
    if (s.size() <= 0)
      break;
#endif // NET_GRID

#ifdef STAT_PEARSON
    if (0 != pearson.read_params_1(s, is)) {
      ERROR();
      runStatus = -1;
      return *this;
    }
    if (s.size() <= 0)
      break;
#endif

#ifdef STAT_SPEARMAN
    if (0 != spearman.read_params_1(s, is)) {
      ERROR();
      runStatus = -1;
      return *this;
    }
    if (s.size() <= 0)
      break;
#endif

#ifdef STAT_KENDALL
    if (0 != kendall.read_params_1(s, is)) {
      ERROR();
      runStatus = -1;
      return *this;
    }
    if (s.size() <= 0)
      break;
#endif

#ifdef STAT_BETWEENNESS
    if (0 != betweenness.read_params_1(s, is)) {
      ERROR();
      runStatus = -1;
      return *this;
    }
    if (s.size() <= 0)
      break;
#endif // STAT_BETWEENNESS

#ifdef STAT_MODULARITY
    if (0 != modularity.read_params_1(s, is)) {
      ERROR();
      runStatus = -1;
      return *this;
    }
    if (s.size() <= 0)
      break;
#endif

#ifdef STAT_CLUSTER
    if (0 != cluster.read_params_1(s, is)) {
      ERROR();
      runStatus = -1;
      return *this;
    }
    if (s.size() <= 0)
      break;
#endif

#ifdef ACT_SIS
    if (0 != sis.read_params_1(s, is)) {
      runStatus = -1;
      ERROR();
      return *this;
    }
    if (s.size() <= 0)
      break;
#endif

    ERROR(s);
    runStatus = -1;
  } while (0);

  return *this;
}

Networks& Networks::read_params(const char* name)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else
    fn = readName + ".params.txt";
  if (fn.size() <= 0) {
    runStatus = -1;
    ERROR();
    return *this;
  }

  ifstream is(fn.c_str());
  if (!is) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  is >> *this;
  is.close();

  return *this;
}

Networks& Networks::read_params(int argc, char** argv)
{
  string s;
  for (int i = 0; i < argc; i++)
    (s += '\t') += argv[i];
  stringstream ss(s);
  ss >> *this;
  return *this;
}

//**//****************************************************//*
Networks& Networks::run(const string argv2)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }

  string s;
  istringstream ss;
  if (argv2.size() > 0)
    ss.str(argv2);
  else
    ss.str(argv);

  while (ss >> s) {
    cout << s << '\n';
    if (s.size() <= 0 || s == ".")
      continue;

    if (s == "--cal_params") {
      common_get_string(ss, s);
      if (0 != cal_params(s).runStatus) {
        ERROR();
        runStatus = -1;
        return *this;
      }
      continue;
    }

    if (s == "--init_seed0") {
      init_seed0(seed);
      cout << "\tseed\t" << seed << '\n';
      continue;
    }

    if (s == "--init_seed") {
      init_seed(seed);
      cout << "\tseed\t" << seed << '\n';
      continue;
    }

    if (s == "--cal_deg") {
      if (!(ss >> s) || 0 != cal_nodeDeg(s).runStatus) {
        ERROR();
        runStatus = -1;
        return *this;
      }
      continue;
    }

    if (s == "--cal_p2p") {
      if (!(ss >> s) || 0 != cal_p2p(s).runStatus) {
        ERROR();
        runStatus = -1;
        return *this;
      }
      continue;
    }

    if (s == "--fix_p2p") {
      if (0 != ::fix_p2p(p2p, dirFlag)) {
        ERROR();
        runStatus = -1;
        return *this;
      }
      continue;
    }

    if (s == "--fix_p2p_nodeDeg0") {
      if (0 != fix_p2p_nodeDeg0().runStatus) {
        ERROR();
        runStatus = -1;
        return *this;
      }
      continue;
    }

#ifdef NET_EXTREMUM
    if (s == "--cal_extrLKK") {
      if (!(ss >> s) || 0 != extremum_cal_lkk(s, ss).runStatus) {
        ERROR();
        runStatus = -1;
        return *this;
      }
      continue;
    }
#endif

    if (s == "--stat") {
      if (0 != stat().runStatus) {
        ERROR();
        runStatus = -1;
        return *this;
      }
      continue;
    }

#ifdef ACT_RECOMMEND
    if (s == "--recommend") {
      act_recommend();
      if (0 != runStatus) {
        ERROR();
        return *this;
      }
      continue;
    }
#endif

#ifdef ACT_SIS
    if (s == "--sis") {
      act_sis();
      if (0 != runStatus) {
        ERROR();
        return *this;
      }
      continue;
    }
#endif

    if (s == "--print") {
      cout << *this;
      if (0 != runStatus) {
        ERROR();
        runStatus = -1;
        return *this;
      }
      continue;
    }

    if (s == "--save") {
      if (0 != save().runStatus) {
        ERROR();
        runStatus = -1;
        return *this;
      }
      continue;
    }
    if (s == "--save0") {
      if (0 != save(saveName.c_str()).runStatus) {
        ERROR();
        runStatus = -1;
        return *this;
      }
      continue;
    }

    if (s == "--clear") {
      clear();
      continue;
    }

    if (s == "exit")
      return *this;

    ERROR(s);
    runStatus = -1;
    return *this;
  }

  return *this;
}

//**//************************************************************//*
Networks& Networks::stat(void)
{
  if (runStatus != 0) {
    ERROR();
    return *this;
  }

  if (lkk.empty() && p2p.empty()) {
    ERROR();
    runStatus = -1;
    return *this;
  }
  if (!p2p.empty()) {
    if (0 != p2p_2_degArr().runStatus) {
      ERROR();
      runStatus = -1;
      return *this;
    }
  } else if (0 != lkk_2_degArr().runStatus) {
    ERROR();
    runStatus = -1;
    return *this;
  }

#ifdef STAT_PEARSON
  cout << "\tpearson\n";
  stat_pearson();
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
#endif

#ifdef STAT_SPEARMAN
  cout << "\tspearman\n";
  if (0 != spearman_degArr_2_deg2ArrVal_weight().runStatus
      || 0 != stat_spearman().runStatus) {
    ERROR();
    return *this;
  }
#endif

#ifdef STAT_KENDALL
  cout << "\tkendall\n";
  stat_kendall();
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
#endif

#ifdef STAT_BETWEENNESS
  cout << "\tbetweenness\n";
  stat_betweenness();
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
#endif

#ifdef STAT_MODULARITY
  cout << "\tmodularity\n";
  stat_modularity();
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
#endif

#ifdef STAT_CLUSTER
  cout << "\tcluster\n";
  stat_cluster();
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
#endif

  return *this;
}

//**//****************************************************//*
Networks& Networks::cal_params(const string& s)
{
  if (runStatus != 0) {
    ERROR();
    return *this;
  }
  string t;
  istringstream ss(s);
  while (ss >> t) {
    if (t.size() <= 0)
      continue;
    if (t == "dirFlag") {
      dirFlag = 1;
      continue;
    }
    if (t == "!dirFlag") {
      dirFlag = 0;
      continue;
    }
    if (t == "weightFlag") {
      weightFlag = 1;
      continue;
    }
    if (t == "!weightFlag") {
      weightFlag = 0;
      continue;
    }
    ERROR(s);
    runStatus = -1;
    return *this;
  }
  return *this;
}

//**//****************************************************//*
Networks& Networks::cal_nodeDeg(const string& s)
{
  if (runStatus != 0) {
    ERROR();
    return *this;
  }
  cout << "\t" << s << '\n';
  if (!nodeDeg.empty() || s.size() <= 0) {
    ERROR(s);
    runStatus = -1;
    return *this;
  }

  if (s == "p2p") {
    if (!p2p.empty())
      p2p_2_degArr();
    else {
      ERROR();
      runStatus = -1;
    }
    return *this;
  }

  if (s == "read_deg") {
    if (0 != read_nodeDeg().runStatus)
      ERROR();
    return *this;
  }

  if (s == "read_degArr") {
    if (0 != read_degArr().runStatus)
      ERROR();
    return *this;
  }

  if (s == "read_lkk") {
    if (0 != read_lkk().runStatus)
      ERROR();
    return *this;
  }

#ifdef NET_DEGREE
#ifdef DEG_POWER
  if (s == "power_arr") {
    if (0 != degree_power_arr().runStatus)
      ERROR();
    return *this;
  }
  if (s == "power") {
    if (0 != degree_power().runStatus)
      ERROR();
    return *this;
  }
#endif
#ifdef DEG_POISSON
  if (s == "poisson") {
    if (0 != degree_poisson().runStatus)
      ERROR();
    return *this;
  }
#endif
#endif // NET_DEG

  ERROR(s);
  runStatus = -1;
  return *this;
}

//**//****************************************************//*
Networks& Networks::cal_p2p(const string& s)
{
  cout << "\t" << s << '\n';
  if (runStatus != 0) {
    ERROR();
    return *this;
  }
  if (status < 0) {
    ERROR();
    runStatus = -1;
    return *this;
  }
  if (p2p.empty()) {
    do {
      if (s.size() <= 0) {
        ERROR();
        runStatus = -1;
        return *this;
      }
      if (s == "read_p2p" || s == "read_p2p_fix") {
        if (!p2p.empty() || 0 != read_p2p().runStatus) {
          ERROR();
          runStatus = -1;
          return *this;
        }
        break;
      }

      if (s == "read_linkMatr" || s == "read_linkMatr_fix") {
        if (!p2p.empty() || 0 != read_linkMatr().runStatus) {
          ERROR();
          runStatus = -1;
          return *this;
        }
      }
      if (s == "read_link" || s == "read_link_fix") {
        if (!link.empty() || 0 != read_link().runStatus) {
          ERROR();
          runStatus = -1;
          return *this;
        }
      }
      if (s == "read_link_0" || s == "read_link_0_fix") {
        if (!link.empty() || 0 != read_link().runStatus) {
          ERROR();
          runStatus = -1;
          return *this;
        }
      }

      if (s == "read_weightMatr") {
        if (!weightMatr.empty() || 0 != read_weightMatr().runStatus) {
          ERROR();
          runStatus = -1;
          return *this;
        }
      }
      if (s == "read_weight_link") {
        if (!weightFlag || link.empty() || !vvweight.empty()
            || 0 != read_weight_link().runStatus) {
          ERROR();
          runStatus = -1;
          return *this;
        }
      }
      if (s == "read_link_weight_0") {
        if (!weightFlag || !link.empty() || !vvweight.empty()
            || 0 != read_link_weight().runStatus) {
          ERROR();
          runStatus = -1;
          return *this;
        }
      }

      if (s == "p2p" || s == "p2p_fix" || s.find("read_") != string::npos) {
        if (weightFlag && !weightMatr.empty() && linkMatr.empty()) {
          if (0 != weightMatr_2_linkMatr(linkMatr, weightMatr)) {
            ERROR();
            runStatus = -1;
            return *this;
          }
          // break;
        }
        if (!linkMatr.empty()) {
          if (0 != ::linkMatr_2_p2p(p2p, linkMatr))
            ERROR();
          break;
        }
        if (!linkMatrC.empty()) {
          if (0 != ::linkMatrC_2_p2p(p2p, linkMatrC))
            ERROR();
          break;
        }
        if (!link.empty()) {
          if (0 != ::link_2_p2p(p2p, link, p2pIn, nodeSize, dirFlag)) {
            ERROR();
            runStatus = -1;
            return *this;
          }
          break;
        }
        ERROR(s);
        runStatus = -1;
        return *this;
      }

#ifdef NET_EXTREMUM
      if (s == "Max") {
        net_Max();
        if (0 != runStatus || 0 > status) {
          ERROR();
          return *this;
        }
        break;
      }
      if (s == "Max_lkk") {
        net_Max_new_lkk();
        if (0 != runStatus || 0 > status) {
          ERROR();
          return *this;
        }
        status = 2;
        return *this;
      }

      if (s == "Min") {
        net_Min();
        if (0 != runStatus || 0 > status) {
          ERROR();
          return *this;
        }
        break;
      }
      if (s == "Min_lkk") {
        net_Min_new_lkk();
        if (0 != runStatus || 0 > status) {
          ERROR();
          return *this;
        }
        status = 2;
        return *this;
      }
      if (s == "MinLkkP2p") {
        net_Min_new_lkk_p2p(0);
        if (0 != runStatus || 0 > status) {
          ERROR();
          return *this;
        }
        break;
      }
      if (s == "MinLkkP2pFix") {
        net_Min_new_lkk_p2p(1);
        if (0 != runStatus || 0 > status) {
          ERROR();
          return *this;
        }
        break;
      }
#endif

// TODO: lkk_2_p2p // lkk生成p2p

#ifdef NET_RANDOM
      if (s == "ER") {
        net_ER();
        if (0 != runStatus || 0 > status) {
          ERROR();
          return *this;
        }
        break;
      }
      if (s == "Random") {
        net_random_remDeg();
        if (0 != runStatus || 0 > status) {
          ERROR();
          return *this;
        }
        break;
      }
#endif

#ifdef NET_BA
      if (s == "BA") {
        net_BA();
        if (0 != runStatus || 0 > status) {
          ERROR();
          return *this;
        }
        break;
      }
#endif

#ifdef NET_GRID
      if (s == "Grid") {
        net_grid();
        if (0 != runStatus || 0 > status) {
          ERROR();
          return *this;
        }
        break;
      }
#endif

#ifdef STAT_SPEARMAN
      if (s == "Spearman") {
#ifdef MODEL_GAUSS
        spearman_gauss_new_ranLink();
#else
        runStatus = -1;
#endif
        if (0 != runStatus) {
          ERROR();
          return *this;
        }
        break;
      }
#endif

      ERROR(s);
      runStatus = -1;
      return *this;
    } while (0);
  } else {
    // !p2p.empty()
    if (status == 0)
      status = -1;
  }

  if (status < 0 || p2p.empty()) {
    ERROR();
    runStatus = -1;
    return *this;
  }

  if (s.find("_fix") != string::npos) {
    fix_p2p(p2p, dirFlag);
    linkSize = 0;
  }

  if (dirFlag && p2pIn.empty() && 0 != p2p_2_p2pIn(p2pIn, p2p)) {
    ERROR();
    runStatus = -1;
    return *this;
  }

  if (0 != p2p_2_degArr().runStatus) {
    ERROR();
    runStatus = -1;
    return *this;
  }
  if (kMax <= 0 || s.find("read_") != string::npos) {
    kMin = degArrVal.front();
    kMax = degArrVal.back();
  }

  status = 1;
  return *this;
}

//**//****************************************************//*
// 节点按度排序 net->net2 剔除度为0的点
Networks& Networks::fix_p2p_nodeDeg0(void)
{
  if (status < 0 || p2p.empty()
      || (degArrVal.empty() && 0 != p2p_2_degArr().runStatus)) {
    ERROR();
    runStatus = -1;
    return *this;
  }
  int flag = check_nodeDeg0(nodeDeg);
  cout << "check_nodeDeg0\t" << flag << endl;
  if (flag == 0)
    return *this;
  if (flag < 0 || (flag > 0 && net2 == NULL)) {
    ERROR();
    runStatus = flag;
    return *this;
  }
  Networks& net2 = *this->net2;
  if (degArrVal.back() <= 0) { // net2.nodeSize = 0
    ERROR();
    runStatus = -1;
    return *this;
  }
  net2.dirFlag = dirFlag;

  // net2.nodesName[i] <- i
  nodeSize = p2p.size();
  net2.nodeSize = nodeSize - degArrSize.front();
  net2.nodesName.resize(nodeSize);
  for (NodeType i = 0; i < nodeSize; i++)
    net2.nodesName[i] = i;
  net2.nodesName2 = net2.nodesName;
  common_sort_p_val(net2.nodesName.rbegin(), net2.nodesName.rend(),
      &nodeDeg.front()); // 按度从大到小排

  // i -> net2.nodesName2[i]
  common_sort_p_val(
      net2.nodesName2.begin(), net2.nodesName2.end(), &net2.nodesName.front());

  // 更新net2的连边信息net2.p2p
  net2.p2p.resize(net2.nodeSize);
  for (NodeType i = 0; i < net2.nodeSize; i++)
    net2.p2p[i].reserve(nodeDeg[net2.nodesName[i]]);
  for (NodeType i2 = 0; i2 < net2.p2p.size(); i2++) {
    NodeType i = net2.nodesName[i2];
    for (VNodeTypeCItr j = p2p[i].begin(); j != p2p[i].end(); j++) {
      net2.p2p[i2].push_back(net2.nodesName2[*j]);
    }
  }
  for (VVNodeTypeItr i = net2.p2p.begin(); i != net2.p2p.end(); i++)
    sort(i->begin(), i->end()); // net2.p2p从小到大排序

  // 更新net2的度信息
  if (0 != net2.p2p_2_degArr().runStatus) {
    ERROR();
    runStatus = -1;
    return *this;
  }
  net2.kMin = net2.degArrVal.front();
  net2.kMax = net2.degArrVal.back();
  net2.status = 1;

  return *this;
}

//**//****************************************************//*
