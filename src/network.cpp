#include "network.h"

#include "common.h"
using namespace std;

//**//****************************************************//*
Network::Network(void)
    : argv("."),
      saveName("data/test"),
      readName("data/test"),
      status(0),
      seed(0),
      dirFlag(0),
      weightFlag(0),
      distFlag(0),
      nodeSize(0),
      kMin(0),
      kMax(0),
      linkSize(0),
      priChar('\n'),
      priChar2('\t'),
      runStatus(0),

      degMean(0),
      degMeanOut(0),
      degMeanIn(0),
      linkRemain(0),
      weight_m(2),
      weight_n(2),
      netWeight(0),
      netWeightOut(0),
      netWeightIn(0),
      degWeightMean(0),
      degWeightMeanOut(0),
      degWeightMeanIn(0){


#ifdef STAT_KENDALL
  params_kendall.tau = 0;
  params_kendall.OutIn = 0;
#endif
}

//**//************************************************************//*
istream& operator>>(istream& is, Network& net) {
  if (0 != net.runStatus || !is) {
    ERROR();
    return is;
  }
  for (string s; is; is >> s) {
    if (s.size() <= 0) continue;
    if (0 != net.read_params_1(s, is).runStatus || s.size() > 0) {
      net.runStatus = -1;
      ERROR(s);
      break;
    }
  }
  return is;
}

Network& Network::read_params_1(string& s, istream& is) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (s.size() <= 0) return *this;
  int flag = 1;
  do {
    if (s == "--version") {
      string v;
      getline(is, v);
      cout << s << '\t' << v << endl;
      break;
    }
    if (s == "--argv") {
      getline(is, argv);
      cout << s << '\t' << argv << endl;
      break;
    }
    if (s == "--saveName") {
      is >> saveName;
      cout << s << '\t' << saveName << endl;
      break;
    }
    if (s == "--readName") {
      is >> readName;
      cout << s << '\t' << readName << endl;
      break;
    }
    if (s == "--status") {
      is >> status;
      cout << s << '\t' << status << endl;
      break;
    }
    if (s == "--runStatus") {
      is >> runStatus;
      cout << s << '\t' << runStatus << endl;
      break;
    }
    if (s == "--seed") {
      is >> seed;
      cout << s << '\t' << seed << endl;
      break;
    }
    if (s == "--dirFlag") {
      is >> dirFlag;
      cout << s << '\t' << dirFlag << endl;
      break;
    }
    if (s == "--weightFlag") {
      is >> weightFlag;
      cout << s << '\t' << weightFlag << endl;
      break;
    }
    if (s == "--nodeSize") {
      is >> nodeSize;
      cout << s << '\t' << nodeSize << endl;
      break;
    }
    if (s == "--kMin") {
      is >> kMin;
      cout << s << '\t' << kMin << endl;
      break;
    }
    if (s == "--kMax") {
      is >> kMax;
      cout << s << '\t' << kMax << endl;
      break;
    }
    if (s == "--linkSize") {
      is >> linkSize;
      cout << s << '\t' << linkSize << endl;
      break;
    }
    if (s == "--paramsInt") {
      common_read1_0(is, paramsInt);
      cout << s << '\t' << paramsInt << endl;
      break;
    }
    if (s == "--paramsIntSize") {
      vector<int>::size_type st = 0;
      is >> st;
      paramsInt.resize(st);
      cout << s << '\t' << st << endl;
      break;
    }
    if (s == "--paramsInt2") {
      vector<int>::size_type st = 0;
      is >> st;
      if (paramsInt.size() < st) paramsInt.resize(st);
      is >> paramsInt[st];
      cout << s << '\t' << st << "\t" << paramsInt[st] << endl;
      break;
    }
    if (s == "--paramsDouble") {
      common_read1_0(is, paramsDouble);
      cout << s << '\t' << paramsDouble << endl;
      break;
    }
    if (s == "--paramsDoubleSize") {
      vector<double>::size_type st = 0;
      is >> st;
      paramsDouble.resize(st);
      cout << s << '\t' << st << endl;
      break;
    }
    if (s == "--paramsDouble2") {
      vector<double>::size_type st = 0;
      is >> st;
      if (paramsDouble.size() < st) paramsDouble.resize(st);
      is >> paramsDouble[st];
      cout << s << '\t' << st << "\t" << paramsDouble[st] << endl;
      break;
    }
    flag = 0;
  } while (0);
  if (flag) s.clear();

  return *this;
}

//**//****************************************************//*
ostream& operator<<(std::ostream& os, Network& net) {
  if (!os) {
    ERROR();
    net.runStatus = -1;
    return os;
  }
  os << "--version\t" << NET_VERSION << "\n--saveName\t" << net.saveName
     << "\n--readName\t" << net.readName << "\n--argv\t" << net.argv
     << "\n--runStatus\t" << net.runStatus << "\n--status\t" << net.status
     << "\n--seed\t" << net.seed << "\n--dirFlag\t" << net.dirFlag
     << "\n--weightFlag\t" << net.weightFlag << "\n--nodeSize\t" << net.nodeSize
     << "\n--kMin\t" << net.kMin << "\n--kMax\t" << net.kMax << "\n--degSize\t"
     << net.degArrVal.size() << "\n--degMean\t" << net.degMean
     << "\n--linkSize\t" << net.linkSize;
  if (net.weightFlag) {
    os << "\n--netWeight\t" << net.netWeight << "\n--degWeightMean\t"
       << net.degWeightMean;
  }

  if (!net.paramsInt.empty()) {
    os << "\n--paramsIntSize\t" << net.paramsInt.size() << "\n--paramsInts\t"
       << net.paramsInt;
  }
  if (!net.paramsDouble.empty()) {
    os << "\n--paramsDoubleSize\t" << net.paramsDouble.size()
       << "\n--paramsDoubles\t" << net.paramsDouble;
  }

  if (net.dirFlag && !net.degArrSumOut.empty()) {
    os << "\n--nodeSizeOut\t"
       << (net.degArrSumOut.back() -
           (net.degArrValOut.front() <= 0 ? net.degArrSizeOut.front() : 0))
       << "\n--nodeSizeIn\t"
       << (net.degArrSumIn.back() -
           (net.degArrValIn.front() <= 0 ? net.degArrSizeIn.front() : 0))
       << "\n--degMeanOut\t" << net.degMeanOut << "\n--degMeanIn\t"
       << net.degMeanIn;
    if (net.weightFlag) {
      os << "\n--netWeightOut\t" << net.netWeightOut << "\n--netWeightIn\t"
         << net.netWeightIn << "\n--degWeightMeanOut\t" << net.degWeightMeanOut
         << "\n--degWeightMeanIn\t" << net.degWeightMeanIn;
    }
  }
  os << '\n';

  return os;
}

Network& Network::save_params(ostream& os) {
  if (!os) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  os << *this;
  return *this;
}

Network& Network::save_params(const char* name) {
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
    runStatus = -1;
    ERROR();
    return *this;
  }
  os << *this;
  os.close();
  return *this;
}

Network& Network::save_data(const char* name) {
  string fn;
  stringstream ss;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else {
    ss.clear();
    ss << seed;
    fn = saveName + '_' + ss.str();
  }
  if (0 != save_deg(fn.c_str()).runStatus) ERROR();
  if (0 != save_p2p(fn.c_str()).runStatus) ERROR();
  return *this;
}

Network& Network::save(const char* name) {
  if (0 != save_params(name).runStatus) ERROR();
  if (0 != save_data(name).runStatus) ERROR();
  return *this;
}

//**//****************************************************//*
Network& Network::init_seed(void) {
  if (runStatus != 0) {
    ERROR();
    return *this;
  }
  if (seed <= 0)
    while (0 == (seed = RAND2_INIT(seed))) continue;
  return *this;
}

Network& Network::init_seed(const int s) {
  if (runStatus != 0) {
    ERROR();
    return *this;
  }
  while (0 == (seed = RAND2_INIT(s))) continue;
  return *this;
}

//**//****************************************************//*
Network& Network::clear_deg(void) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  degArrProb.clear();  // [degSize]    度分布概率 p(k)
  degArrVal.clear();   // [degSize]    度分布序列 k
  degArrSize.clear();  // [degSize]    各度节点数 n(k)
  degArrNo.clear();    // [kMax+1]     度k在degArrVal中的位置
  degArrSum.clear();   // [degSize+1]  度分布累计序列
  nodeDeg.clear();     // [nodeSize]   各节点度
  remNodeNum.clear();  // [remNodeSize] 未全连边的节点编号
  nodesName.clear(), nodesName2.clear();  // [nodeSize]   节点的映射关系
  degArrWeight.clear();
  degArrWeightOut.clear();
  degArrWeightIn.clear();
  return *this;
}

Network& Network::save_deg(const char* name) {
  string fn;
  if (name != NULL && name[0] != '\0') {
    fn = name;
  } else {
    stringstream ss;
    ss.clear();
    ss << seed;
    fn = saveName + '_' + ss.str();
  }

  if (!nodeDeg.empty())
    if (0 != common_save1((fn + ".nodeDeg.txt").c_str(), nodeDeg, priChar)) {
      runStatus = -1;
      ERROR();
    }
  if (!degArrVal.empty())
    if (0 !=
        common_save1((fn + ".degArrVal.txt").c_str(), degArrVal, priChar)) {
      runStatus = -1;
      ERROR();
    }
  if (!degArrSize.empty())
    if (0 !=
        common_save1((fn + ".degArrSize.txt").c_str(), degArrSize, priChar)) {
      runStatus = -1;
      ERROR();
    }
  // if (!degArrSum.empty())
  // if (0 !=
  // common_save1((fn + ".degArrSum.txt").c_str(), degArrSum, priChar)) {
  // runStatus = -1;
  // ERROR();
  //}
  if (!nodesName.empty())
    if (0 !=
        common_save1((fn + ".nodesName.txt").c_str(), nodesName, priChar)) {
      runStatus = -1;
      ERROR();
    }
  if (!nodesName2.empty())
    if (0 !=
        common_save1((fn + ".nodesName2.txt").c_str(), nodesName2, priChar)) {
      runStatus = -1;
      ERROR();
    }
  if (weightFlag) {
    if (!nodeWeight.empty() &&
        0 != common_save1((fn + ".nodeWeight.txt").c_str(), nodeWeight,
                          priChar)) {
      runStatus = -1;
      ERROR();
    }
    if (!degArrWeight.empty() &&
        0 != common_save1((fn + ".degArrWeight.txt").c_str(), degArrWeight,
                          priChar)) {
      runStatus = -1;
      ERROR();
    }
  }  // weightFlag
  if (dirFlag) {
    if (!nodeDegOut.empty())
      if (0 !=
          common_save1((fn + ".nodeDegOut.txt").c_str(), nodeDegOut, priChar)) {
        runStatus = -1;
        ERROR();
      }
    if (!degArrValOut.empty())
      if (0 != common_save1((fn + ".degArrValOut.txt").c_str(), degArrValOut,
                            priChar)) {
        runStatus = -1;
        ERROR();
      }
    if (!degArrSizeOut.empty())
      if (0 != common_save1((fn + ".degArrSizeOut.txt").c_str(), degArrSizeOut,
                            priChar)) {
        runStatus = -1;
        ERROR();
      }
    // if (!degArrSumOut.empty())
    // if (0 != common_save1((fn + ".degArrSumOut.txt").c_str(), degArrSumOut,
    // priChar)) {
    // runStatus = -1;
    // ERROR();
    //}
    if (!nodeDegIn.empty())
      if (0 !=
          common_save1((fn + ".nodeDegIn.txt").c_str(), nodeDegIn, priChar)) {
        runStatus = -1;
        ERROR();
      }
    if (!degArrValIn.empty())
      if (0 != common_save1((fn + ".degArrValIn.txt").c_str(), degArrValIn,
                            priChar)) {
        runStatus = -1;
        ERROR();
      }
    if (!degArrSizeIn.empty())
      if (0 != common_save1((fn + ".degArrSizeIn.txt").c_str(), degArrSizeIn,
                            priChar)) {
        runStatus = -1;
        ERROR();
      }
    // if (!degArrSumIn.empty())
    // if (0 != common_save1((fn + ".degArrSumIn.txt").c_str(), degArrSumIn,
    // priChar)) {
    // runStatus = -1;
    // ERROR();
    //}
    if (weightFlag) {
      if (!nodeWeightOut.empty() &&
          0 != common_save1((fn + ".nodeWeightOut.txt").c_str(), nodeWeightOut,
                            priChar)) {
        runStatus = -1;
        ERROR();
      }
      if (!degArrWeightOut.empty() &&
          0 != common_save1((fn + ".degArrWeightOut.txt").c_str(),
                            degArrWeightOut, priChar)) {
        runStatus = -1;
        ERROR();
      }
      if (!nodeWeightIn.empty() &&
          0 != common_save1((fn + ".nodeWeightIn.txt").c_str(), nodeWeightIn,
                            priChar)) {
        runStatus = -1;
        ERROR();
      }
      if (!degArrWeightIn.empty() &&
          0 != common_save1((fn + ".degArrWeightIn.txt").c_str(),
                            degArrWeightIn, priChar)) {
        runStatus = -1;
        ERROR();
      }
    }
  }  // dirFlag
  return *this;
}

//**//****************************************************//*
Network& Network::clear_p2p(void) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  // link
  link.clear();  // [nodeSize]   网络连边
  p2pSize.clear();
  for (VVNodeTypeItr i = p2p.begin(); i != p2p.end(); i++) i->clear();
  p2p.clear();  // [nodeSize]   各点连边
  for (VVNodeTypeItr i = p2pIn.begin(); i != p2pIn.end(); i++) i->clear();
  p2pIn.clear();  // [nodeSize]   各点连边
  for (VVWeightTypeItr i = vvweight.begin(); i != vvweight.end(); i++)
    i->clear();
  vvweight.clear();  // [nodeSize]   各点连边
  for (VVDistTypeItr i = linkMatr.begin(); i != linkMatr.end(); i++) i->clear();
  linkMatr.clear();  // [nodeSize]   网络连边矩阵
  for (VVCharItr i = linkMatrC.begin(); i != linkMatrC.end(); i++) i->clear();
  linkMatrC.clear();  // [nodeSize]   网络连边矩阵
  return *this;
}

Network& Network::save_p2p(const char* name) {
  string fn;
  if (name != NULL && name[0] != '\0') {
    fn = name;
  } else {
    stringstream ss;
    ss.clear();
    ss << seed;
    fn = saveName + '_' + ss.str();
  }

  if (!p2p.empty() &&
      0 != common_save2((fn + ".p2p.txt").c_str(), p2p, priChar2)) {
    runStatus = -1;
    ERROR();
  }
  if (dirFlag && !p2pIn.empty() &&
      0 != common_save2((fn + ".p2pIn.txt").c_str(), p2pIn, priChar2)) {
    runStatus = -1;
    ERROR();
  }

  // link
  if (!link.empty() &&
      0 != common_save2((fn + ".link.txt").c_str(), &link[0], linkSize, 2,
                        priChar2)) {
    runStatus = -1;
    ERROR();
  }

  if (linkMatr.size() > 0) {
    if (0 != common_save2((fn + ".linkMatr.txt").c_str(), linkMatr, priChar2)) {
      runStatus = -1;
      ERROR();
    }
  }
  if (status == -2 &&
      0 != common_save1((fn + ".p2pSize.txt").c_str(), p2pSize)) {
    runStatus = -1;
    ERROR();
  }

  if (!lkk.empty() &&
      0 != common_save2((fn + ".lkk.txt").c_str(), lkk, priChar2)) {
    runStatus = -1;
    ERROR();
  }

  if (weightFlag) {
    if (!weightMatr.empty() &&
        0 != common_save2((fn + ".weightMatr.txt").c_str(), weightMatr,
                          priChar2)) {
      runStatus = -1;
      ERROR();
    }
    if (dirFlag) {
      if (!vvweight.empty() &&
          0 != common_save2((fn + ".vvweight.txt").c_str(), vvweight,
                            priChar2)) {
        runStatus = -1;
        ERROR();
      }
      if (!vvweightIn.empty() &&
          0 != common_save2((fn + ".vvweightIn.txt").c_str(), vvweightIn,
                            priChar2)) {
        runStatus = -1;
        ERROR();
      }
    }
  }

  return *this;
}

//**//****************************************************//*
Network& Network::clear_lkk(void) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  // lkk
  for (VVLinkTypeItr i = lkk.begin(); i != lkk.end(); i++) i->clear();
  lkk.clear();
  for (VVDoubleItr i = lkkProb.begin(); i != lkkProb.end(); i++) i->clear();
  lkkProb.clear();
  return *this;
}

//**//****************************************************//*
Network& Network::clear(void) {
  status = 0;
  runStatus = 0;
  clear_deg();
  clear_p2p();
  clear_lkk();
  return *this;
}

//**//****************************************************//*
Network& Network::read_nodeDeg(const char* name) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (!nodeDeg.empty() || !degArrVal.empty()) {
    runStatus = -1;
    ERROR();
    return *this;
  }

  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else
    fn = readName + ".nodeDeg.txt";

  if (0 != common_read1_0(fn.c_str(), nodeDeg)) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  cout << fn << "\tsize:\t" << nodeDeg.size() << '\n';

  return *this;
}

Network& Network::read_degArr(const char* name) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (!nodeDeg.empty() || !degArrVal.empty()) {
    runStatus = -1;
    ERROR();
    return *this;
  }

  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else
    fn = readName;

  if (degArrVal.empty()) {
    if (0 != common_read1_0((fn + ".degArrVal.txt").c_str(), degArrVal, 0)) {
      runStatus = -1;
      ERROR();
      return *this;
    }
    cout << '\t' << fn << ".degArrVal.txt\tsize:\t" << degArrVal.size() << '\n';
  }
  if (degArrSize.empty()) {
    if (0 != common_read1_0((fn + ".degArrSize.txt").c_str(), degArrSize, 0) ||
        degArrSize.size() != degArrVal.size()) {
      runStatus = -1;
      ERROR();
      return *this;
    }
    cout << '\t' << fn << ".degArrSize.txt\tsize:\t" << degArrVal.size()
         << '\n';
  }
  if (degArrSum.empty()) degArrSize_2_degArrSum(degArrSum, degArrSize);

  if (linkSize <= 0 &&
      0 != degArr_2_linkSize(linkSize, degArrVal, degArrSize)) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  if (nodeSize <= 0 && 0 != degArr_2_nodeSize(nodeSize, degArrSize)) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  if (nodeDeg.empty()) {
    nodeDeg.reserve(nodeSize);
    if (0 != degArr_2_nodeDeg(nodeDeg, degArrVal, degArrSize)) {
      runStatus = -1;
      ERROR();
      return *this;
    }
  }
  if (degArrNo.empty() && 0 != degArrVal_2_degArrNo(degArrNo, degArrVal)) {
    runStatus = -1;
    ERROR();
    return *this;
  }

  return *this;
}

Network& Network::read_lkk(const char* name) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (!lkk.empty()) {
    runStatus = -1;
    ERROR();
    return *this;
  }

  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else
    fn = readName;

  if (0 != read_degArr(name).runStatus) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  if (0 != common_read2_0((fn + ".lkk.txt").c_str(), lkk)) {
    runStatus = -1;
    ERROR();
    return *this;
  }

  return *this;
}

//**//****************************************************//*
Network& Network::read_link_0(const char* name) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else
    fn = readName + ".link.txt";

  if (0 != read0_link(link, fn.c_str(), weight_n)) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  linkSize = link.size() / 2;

  return *this;
}

Network& Network::read_link(const char* name) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else
    fn = readName + ".link.txt";

  if (0 != ::read_link(link, fn.c_str())) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  linkSize = link.size() / 2;

  return *this;
}

Network& Network::read_weight_link(const char* name) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else
    fn = readName + ".link.txt";

  if (weight_m < 2 || weight_m >= weight_n) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  if (0 != ::read_weight_link(vvweight, vvweightIn, linkSize, fn.c_str(),
                              weight_m, weight_n, dirFlag)) {
    runStatus = -1;
    ERROR();
    return *this;
  }

  return *this;
}

Network& Network::read_link_weight(const char* name) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else
    fn = readName + ".link.txt";

  if (weight_m < 2 || weight_m >= weight_n) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  if (0 != read_link_weight_0(link, linkSize, vvweight, vvweightIn, fn.c_str(),
                              weight_m, weight_n, dirFlag)) {
    runStatus = -1;
    ERROR();
    return *this;
  }

  return *this;
}

Network& Network::read_p2p(const char* name) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else
    fn = readName + ".p2p.txt";

  p2p.clear();
  if (0 != common_read2_0(fn.c_str(), p2p)) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  cout << fn << "\tsize:\t" << p2p.size() << '\n';

  return *this;
}

Network& Network::read_linkMatr(const char* name) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else
    fn = readName + ".linkMatr.txt";

  linkMatr.clear();
  if (0 != common_read2_0(fn.c_str(), linkMatr)) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  cout << fn << "\tsize:\t" << linkMatr.size() << '\n';

  // linkMatr_fix_max(linkMatr);

  return *this;
}

Network& Network::read_weightMatr(const char* name) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  string fn;
  if (name != NULL && name[0] != '\0')
    fn = name;
  else
    fn = readName + ".weightMatr.txt";

  weightMatr.clear();
  if (0 != common_read2_0(fn.c_str(), weightMatr)) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  cout << fn << "\tsize:\t" << weightMatr.size() << '\n';

  if (linkMatr.empty()) weightMatr_2_linkMatr(linkMatr, weightMatr);

  return *this;
}

//**//****************************************************//*
Network& Network::lkk_2_degArr(void) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (lkk.empty()) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  if (linkSize <= 0 &&
      0 != degArr_2_linkSize(linkSize, degArrVal, degArrSize)) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  if (nodeSize <= 0 && 0 != degArr_2_nodeSize(nodeSize, degArrSize)) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  if (degArrNo.empty() && 0 != degArrVal_2_degArrNo(degArrNo, degArrVal)) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  if (degArrSum.empty()) degArrSize_2_degArrSum(degArrSum, degArrSize);

  if (kMax <= 0) {
    kMin = degArrVal.front();
    kMax = degArrVal.back();
  }
  if (linkSize > 0) {  // degMean
    degMean =
        2. * linkSize /
        (degArrSum.back() - (degArrVal.front() <= 0 ? degArrSize.front() : 0));
  }

  return *this;
}

Network& Network::p2p_2_degArr(void) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  if (p2p.empty()) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  if (nodeSize <= 0) p2p_2_nodeSize(nodeSize, p2p);
  if (nodeSize <= 0) {
    runStatus = -1;
    ERROR();
    return *this;
  }
  while (p2p.size() < nodeSize) p2p.resize(nodeSize);

  if (!dirFlag) {  // !dirFlag
    // All
    if (nodeDeg.empty() && p2p_2_nodeDeg(nodeDeg, p2p) != 0) {  // nodeDeg
      runStatus = -1;
      ERROR();
      return *this;
    }
    if (degArrVal.empty() &&
        nodeDeg_2_degArr(nodeDeg, degArrVal, degArrSize,
                         degArrSum) != 0) {  // degArr
      runStatus = -1;
      ERROR();
      return *this;
    }
    if (degArrNo.empty() &&
        0 != degArrVal_2_degArrNo(degArrNo, degArrVal)) {  // degArrNo
      runStatus = -1;
      ERROR();
      return *this;
    }
    if (linkSize <= 0 &&
        nodeDeg_2_linkSize(linkSize, nodeDeg) != 0) {  // linkSize
      runStatus = -1;
      ERROR();
      return *this;
    }
    if (lkk.empty() &&
        0 != p2p_2_lkk(lkk, p2p, degArrNo,
                       degArrVal.size())) {  // lkkMatr
      runStatus = -1;
      ERROR();
      return *this;
    }
    // weightFlag
    if (weightFlag) {  // nodeWeight degArrWeight
      if (nodeWeight.empty() && !vvweight.empty())
        vvweight_2_nodeWeight(nodeWeight, p2p, vvweight, netWeight);
      if (degArrWeight.empty() && !nodeWeight.empty())
        nodeWeight_2_degArrWeight(degArrWeight, nodeWeight, nodeDeg, degArrNo,
                                  degArrVal.size());
    }

  } else {  // dirFlag
    // Out
    if (nodeDegOut.empty() && p2p_2_nodeDeg(nodeDegOut, p2p) != 0) {
      runStatus = -1;
      ERROR();
      return *this;
    }
    if (nodeDegOut.size() <= nodeSize) {
      nodeDegOut.resize(nodeSize, 0);
    } else {
      runStatus = -1;
      ERROR();
      return *this;
    }
    if (degArrValOut.empty() &&
        nodeDeg_2_degArr(nodeDegOut, degArrValOut, degArrSizeOut,
                         degArrSumOut) != 0) {
      runStatus = -1;
      ERROR();
      return *this;
    }
    if (degArrNoOut.empty() &&
        0 != degArrVal_2_degArrNo(degArrNoOut, degArrValOut)) {
      runStatus = -1;
      ERROR();
      return *this;
    }
    // Out Weight
    if (weightFlag) {
      if (nodeWeightOut.empty() && !vvweight.empty())
        vvweight_2_nodeWeight(nodeWeightOut, p2p, vvweight, netWeightOut);
      if (degArrWeightOut.empty() && !nodeWeightOut.empty())
        nodeWeight_2_degArrWeight(degArrWeightOut, nodeWeightOut, nodeDegOut,
                                  degArrNoOut, degArrValOut.size());
    }

    // In
    if (p2pIn.empty() && p2p_2_p2pIn(p2pIn, p2p) != 0) {
      runStatus = -1;
      ERROR();
      return *this;
    }
    if (nodeDegIn.empty() && p2p_2_nodeDeg(nodeDegIn, p2pIn) != 0) {
      runStatus = -1;
      ERROR();
      return *this;
    }
    if (nodeDegIn.size() <= nodeSize) {
      nodeDegIn.resize(nodeSize, 0);
    } else {
      runStatus = -1;
      ERROR();
      return *this;
    }
    if (degArrValIn.empty() &&
        nodeDeg_2_degArr(nodeDegIn, degArrValIn, degArrSizeIn, degArrSumIn) !=
            0) {
      runStatus = -1;
      ERROR();
      return *this;
    }
    if (degArrNoIn.empty() &&
        0 != degArrVal_2_degArrNo(degArrNoIn, degArrValIn)) {
      runStatus = -1;
      ERROR();
      return *this;
    }
    // In Weight
    if (weightFlag) {
      if (nodeWeightIn.empty() && !vvweightIn.empty())
        vvweight_2_nodeWeight(nodeWeightIn, p2pIn, vvweightIn, netWeightIn);
      if (degArrWeightIn.empty() && !nodeWeightIn.empty())
        nodeWeight_2_degArrWeight(degArrWeightIn, nodeWeightIn, nodeDegIn,
                                  degArrNoIn, degArrValIn.size());
    }

    // All
    if (nodeDeg.empty() &&
        nodeDegIO_2_nodeDeg(nodeDeg, nodeDegOut, nodeDegIn) != 0) {
      runStatus = -1;
      ERROR();
      return *this;
    }
    if (degArrVal.empty() &&
        nodeDeg_2_degArr(nodeDeg, degArrVal, degArrSize, degArrSum) != 0) {
      runStatus = -1;
      ERROR();
      return *this;
    }
    if (degArrNo.empty() && 0 != degArrVal_2_degArrNo(degArrNo, degArrVal)) {
      runStatus = -1;
      ERROR();
      return *this;
    }
    if (linkSize <= 0 &&
        nodeDeg_2_linkSize(linkSize, nodeDeg) != 0) {  // linkSize
      runStatus = -1;
      ERROR();
      return *this;
    }
    if (lkk.empty() &&
        0 != p2p_2_lkk_dir(lkk, p2p, nodeDeg, nodeDeg, degArrNo, degArrNo,
                           degArrVal.size(),
                           degArrVal.size())) {  // lkk
      runStatus = -1;
      ERROR();
      return *this;
    }
    if (lkkOutIn.empty() &&
        0 != p2p_2_lkk_dir(lkkOutIn, p2p, nodeDegOut, nodeDegIn, degArrNoOut,
                           degArrNoIn, degArrValOut.size(),
                           degArrValIn.size())) {  // lkkOutIn
      runStatus = -1;
      ERROR();
      return *this;
    }
    // All Weight
    if (weightFlag) {
      if (nodeWeight.empty() && !nodeWeight.empty())
        nodeWeightIO_2_nodeWeight(nodeWeight, nodeWeightOut, nodeWeightIn);
      netWeight = netWeightOut + netWeightIn;
      if (degArrWeight.empty() && !nodeWeight.empty())
        nodeWeight_2_degArrWeight(degArrWeight, nodeWeight, nodeDeg, degArrNo,
                                  degArrVal.size());
    }
  }

  if (kMax <= 0) {
    kMin = degArrVal.front();
    kMax = degArrVal.back();
  }
  if (linkSize > 0) {  // degMean degWeightMean
    degMean =
        2. * linkSize /
        (degArrSum.back() - (degArrVal.front() <= 0 ? degArrSize.front() : 0));
    if (weightFlag)
      degWeightMean = (double)netWeight /
                      (degArrSum.back() -
                       (degArrVal.front() <= 0 ? degArrSize.front() : 0));
    if (dirFlag) {
      degMeanOut = (double)linkSize /
                   (degArrSumOut.back() -
                    (degArrValOut.front() <= 0 ? degArrSizeOut.front() : 0));
      degMeanIn = (double)linkSize /
                  (degArrSumIn.back() -
                   (degArrValIn.front() <= 0 ? degArrSizeIn.front() : 0));
      if (weightFlag) {
        degWeightMeanOut = (double)netWeightOut /
                           (degArrSum.back() -
                            (degArrVal.front() <= 0 ? degArrSize.front() : 0));
        degWeightMeanIn = (double)netWeightIn /
                          (degArrSum.back() -
                           (degArrVal.front() <= 0 ? degArrSize.front() : 0));
      }
    }
  }

  return *this;
}

//**//****************************************************//*
