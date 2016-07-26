#include "networks.h"

#include "common.h"
using namespace std;

//**//****************************************************//*
int net_read_params_0(istream& is, Network& net)
{
    if (!is) {
        ERROR();
        return -1;
    }

    for(string s; is >> s;) {
        if (s.size() <= 0 || s == ".") {
            continue;
        }
        if (s == "--file") {
            cout << s << '\t';
            is >> s;
            cout << s << endl;
            if (!is || s.size() <= 0 || s == net.readName) {
                ERROR();
            } else {
                net.readName = s;
                net_read_params(net, s.c_str());
            }
            continue;
        }
        if (s == "--argv") {
            is >> net.argv;
            cout << s << '\t'   << net.argv << endl;
            continue;
        }
        if (s == "--saveName") {
            is >> net.saveName;
            cout << s << '\t'   << net.saveName << endl;
            continue;
        }
        if (s == "--readName") {
            is >> net.readName;
            cout << s << '\t'   << net.readName << endl;
            continue;
        }
        if (s == "--status") {
            is >> net.status;
            cout << s << '\t'   << net.status << endl;
            continue;
        }
        if (s == "--seed") {
            is >> net.seed;
            cout << s << '\t'   << net.seed << endl;
            continue;
        }
        if (s == "--dirFlag") {
            is >> net.dirFlag;
            cout << s << '\t'   << net.dirFlag << endl;
            continue;
        }
        if (s == "--weightFlag") {
            is >> net.weightFlag;
            cout << s << '\t'   << net.weightFlag << endl;
            continue;
        }
        if (s == "--nodeSize") {
            is >> net.nodeSize;
            cout << s << '\t'   << net.nodeSize << endl;
            continue;
        }
        if (s == "--kMin") {
            is >> net.kMin;
            cout << s << '\t'   << net.kMin << endl;
            continue;
        }
        if (s == "--kMax") {
            is >> net.kMax;
            cout << s << '\t'   << net.kMax << endl;
            continue;
        }
        if (s == "--linkSize") {
            is >> net.linkSize;
            cout << s << '\t'   << net.linkSize << endl;
            continue;
        }
        if (s == "--paramsInt") {
            common_read1_0(is, net.paramsInt);
            cout << s << '\t'   << net.paramsInt << endl;
            continue;
        }
        if (s == "--paramsIntSize") {
            vector<int>::size_type st = 0;
            is >> st;
            net.paramsInt.resize(st);
            cout << s << '\t'   << st << endl;
            continue;
        }
        if (s == "--paramsInt2") {
            vector<int>::size_type st = 0;
            is >> st;
            if (net.paramsInt.size() < st) net.paramsInt.resize(st);
            is >> net.paramsInt[st];
            cout << s << '\t'   << st << "\t" << net.paramsInt[st] << endl;
            continue;
        }
        if (s == "--paramsDouble") {
            common_read1_0(is, net.paramsDouble);
            cout << s << '\t'   << net.paramsDouble << endl;
            continue;
        }
        if (s == "--paramsDoubleSize") {
            vector<double>::size_type st = 0;
            is >> st;
            net.paramsDouble.resize(st);
            cout << s << '\t'   << st << endl;
            continue;
        }
        if (s == "--paramsDouble2") {
            vector<double>::size_type st = 0;
            is >> st;
            if (net.paramsDouble.size() < st) net.paramsDouble.resize(st);
            is >> net.paramsDouble[st];
            cout << s << '\t'   << st << "\t" << net.paramsDouble[st] << endl;
            continue;
        }
    }

    return 0;
}

int net_save_params_0(ostream& os, const Network& net)
{
    if (!os) {
        ERROR();
        return -1;
    }
    os  << "--version\t"      << NET_VERSION
        << "\n--saveName\t" << net.saveName
        << "\n--readName\t" << net.readName
        << "\n--argv\t"     << (net.argv.size() <= 0 ? "." : net.argv)
        << "\n--status\t"   << net.status
        << "\n--seed\t"     << net.seed
        << "\n--dirFlag\t"      << net.dirFlag
        << "\n--weightFlag\t"   << net.weightFlag
        << "\n--nodeSize\t" << net.nodeSize
        << "\n--kMin\t"     << net.kMin
        << "\n--kMax\t"     << net.kMax
        << "\n--degSize\t"  << net.degArrVal.size()
        << "\n--degMean\t"  << net.degMean
        << "\n--linkSize\t" << net.linkSize;
    if(net.weightFlag){
        os  << "\n--netWeight\t"        << net.netWeight
            << "\n--degWeightMean\t"    << net.degWeightMean;
    }

    os << "\n--paramsIntSize\t"    << net.paramsInt.size();
    if (!net.paramsInt.empty())
        os << "\n--paramsInts\t" << net.paramsInt;
    os  << "\n--paramsDoubleSize\t" << net.paramsDouble.size();
    if (!net.paramsDouble.empty())
        os << "\n--paramsDoubles\t" << net.paramsDouble;

    if(net.dirFlag && !net.degArrSumOut.empty()){
        os  << "\n--nodeSizeOut\t"  << (net.degArrSumOut.back() - (net.degArrValOut.front() <= 0 ? net.degArrSizeOut.front() : 0))
            << "\n--nodeSizeIn\t"   << (net.degArrSumIn.back() - (net.degArrValIn.front() <= 0 ? net.degArrSizeIn.front() : 0))
            << "\n--degMeanOut\t"   << net.degMeanOut
            << "\n--degMeanIn\t"    << net.degMeanIn;
        if(net.weightFlag){
            os  << "\n--netWeightOut\t"     << net.netWeightOut
                << "\n--netWeightIn\t"      << net.netWeightIn
                << "\n--degWeightMeanOut\t" << net.degWeightMeanOut
                << "\n--degWeightMeanIn\t"  << net.degWeightMeanIn;
        }
    }
    os  << '\n';

    return 0;
}

int net_save_params_0(const Network& net, const char* name)
{
    string fn;
    if (name != NULL && name[0] != '\0') {
        fn = name;
    } else {
        stringstream ss;
        ss << net.seed;
        fn = net.saveName + '_' + ss.str() + "_params.txt";
    }
    ofstream os(fn.c_str());
    if (!os) {
        return -1;
    }
    os << net;
    os.close();
    return 0;
}

//**//****************************************************//*
int net_clear_deg(Network& net)
{
    // deg
    net.degArrProb.clear(); // [degSize]    度分布概率 p(k)
    net.degArrVal.clear();  // [degSize]    度分布序列 k
    net.degArrSize.clear(); // [degSize]    各度节点数 n(k)
    net.degArrNo.clear();   // [kMax+1]     度k在degArrVal中的位置
    net.degArrSum.clear();  // [degSize+1]  度分布累计序列
    net.nodeDeg.clear();    // [nodeSize]   各节点度
    net.remNodeNum.clear(); // [remNodeSize] 未全连边的节点编号
    net.nodesName.clear(), net.nodesName2.clear();    // [nodeSize]   节点的映射关系
    net.degArrWeight.clear(), net.degArrWeightOut.clear(), net.degArrWeightIn.clear();
    return 0;
}

int net_clear_p2p(Network& net)
{
    // link
    net.link.clear();       // [nodeSize]   网络连边
    net.p2pSize.clear();
    for (VVNodeTypeItr i = net.p2p.begin(); i != net.p2p.end(); i++) i->clear();
    net.p2p.clear();        // [nodeSize]   各点连边
    for (VVNodeTypeItr i = net.p2pIn.begin(); i != net.p2pIn.end(); i++) i->clear();
    net.p2pIn.clear();      // [nodeSize]   各点连边
    for (VVWeightTypeItr i = net.vvweight.begin(); i != net.vvweight.end(); i++) i->clear();
    net.vvweight.clear();        // [nodeSize]   各点连边
    for (VVDistTypeItr i = net.linkMatr.begin(); i != net.linkMatr.end(); i++) i->clear();
    net.linkMatr.clear();   // [nodeSize]   网络连边矩阵
    for (VVCharItr i = net.linkMatrC.begin(); i != net.linkMatrC.end(); i++) i->clear();
    net.linkMatrC.clear();  // [nodeSize]   网络连边矩阵
    return 0;
}

int net_clear_lkk(Network& net)
{
    // lkk
    for (VVLinkTypeItr i = net.lkk.begin(); i != net.lkk.end(); i++) i->clear();
    net.lkk.clear();
    for (VVDoubleItr i = net.lkkProb.begin(); i != net.lkkProb.end(); i++) i->clear();
    net.lkkProb.clear();
    return 0;
}

//**//****************************************************//*
int net_read_nodeDeg_0(Network& net, const char *name)
{
    if(!net.nodeDeg.empty() || !net.degArrVal.empty()){
        ERROR();
        return -1;
    }

    string fn;
    if (name != NULL && name[0] != '\0') fn = name;
    else fn = net.readName + "_nodeDeg.txt";

    if (0 != common_read1_0(fn.c_str(), net.nodeDeg)) {
        ERROR();
        return -1;
    }
    cout << fn << "\tsize:\t" << net.nodeDeg.size() << '\n';

    return 0;
}

int net_read_degArr_0(Network& net, const char *name)
{
    if(!net.nodeDeg.empty() || !net.degArrVal.empty()){
        ERROR();
        return -1;
    }

    string fn;
    if (name != NULL && name[0] != '\0') fn = name;
    else fn = net.readName;

    if (net.degArrVal.empty()){
        if(0 != common_read1_0((fn + "_degArrVal.txt").c_str(), net.degArrVal, 0)) {
            ERROR();
            return -1;
        }
        cout << '\t' << fn << "_degArrVal.txt\tsize:\t" << net.degArrVal.size() << '\n';
    }
    if(net.degArrSize.empty()){
        if (0 != common_read1_0((fn + "_degArrSize.txt").c_str(), net.degArrSize, 0) || net.degArrSize.size() != net.degArrVal.size()) {
            ERROR();
            return -1;
        }
        cout << '\t' << fn << "_degArrSize.txt\tsize:\t" << net.degArrVal.size() << '\n';
    }
    if(net.degArrSum.empty()) degArrSize_2_degArrSum(net.degArrSum, net.degArrSize);

    if(net.linkSize <= 0 && 0 != degArr_2_linkSize(net.linkSize, net.degArrVal, net.degArrSize)){
        ERROR();
        return -1;
    }
    if(net.nodeSize <= 0 && 0 != degArr_2_nodeSize(net.nodeSize, net.degArrSize)){
        ERROR();
        return -1;
    }
    if(net.nodeDeg.empty()){
        net.nodeDeg.reserve(net.nodeSize);
        if(0 != degArr_2_nodeDeg(net.nodeDeg, net.degArrVal, net.degArrSize)){
            ERROR();
            return -1;
        }
    }
    if(net.degArrNo.empty() && 0 != degArrVal_2_degArrNo(net.degArrNo, net.degArrVal)){
        ERROR();
        return -1;
    }

    return 0;
}

int net_read_lkk_0(Network& net, const char *name)
{
    if(!net.lkk.empty()){
        ERROR();
        return -1;
    }

    string fn;
    if (name != NULL && name[0] != '\0') fn = name;
    else fn = net.readName;

    if(0 != net_read_degArr_0(net, name)){
        ERROR();
        return -1;
    }
    if(0 != common_read2_0((fn + "_lkk.txt").c_str(), net.lkk)) {
        ERROR();
        return -1;
    }
    return 0;
}

//**//****************************************************//*
int net_save_deg(const Network& net, const char *name)
{
    string fn;
    if (name != NULL && name[0] != '\0') {
        fn = name;
    } else {
        stringstream ss;
        ss.clear();
        ss << net.seed;
        fn = net.saveName + '_' + ss.str();
    }
    //if (!net.nodeDeg.empty())
        //if(0 != common_save1((fn + "_nodeDeg.txt").c_str(), net.nodeDeg, net.priChar)) ERROR();
    if (!net.degArrVal.empty())
        if(0 != common_save1((fn + "_degArrVal.txt").c_str(), net.degArrVal, net.priChar)) ERROR();
    if (!net.degArrSize.empty())
        if(0 != common_save1((fn + "_degArrSize.txt").c_str(), net.degArrSize, net.priChar)) ERROR();
    //if (!net.degArrSum.empty())
    //if(0 != common_save1((fn + "_degArrSum.txt").c_str(), net.degArrSum, net.priChar)) ERROR();
    //if (!net.nodesName.empty())
    //if(0 != common_save1((fn + "_nodesName.txt").c_str(), net.nodesName, net.priChar)) ERROR();
    //if (!net.nodesName2.empty())
    //if(0 != common_save1((fn + "_nodesName2.txt").c_str(), net.nodesName2, net.priChar)) ERROR();
    //if(net.weightFlag){
    //if(!net.nodeWeight.empty() && 0 != common_save1((fn + "_nodeWeight.txt").c_str(), net.nodeWeight, net.priChar)) ERROR();
    //if(!net.degArrWeight.empty() && 0 != common_save1((fn + "_degArrWeight.txt").c_str(), net.degArrWeight, net.priChar)) ERROR();
    //}
    if(net.dirFlag){
        if (!net.nodeDegOut.empty())
            if(0 != common_save1((fn + "_nodeDegOut.txt").c_str(), net.nodeDegOut, net.priChar)) ERROR();
        if (!net.degArrValOut.empty())
            if(0 != common_save1((fn + "_degArrValOut.txt").c_str(), net.degArrValOut, net.priChar)) ERROR();
        if (!net.degArrSizeOut.empty())
            if(0 != common_save1((fn + "_degArrSizeOut.txt").c_str(), net.degArrSizeOut, net.priChar)) ERROR();
        //if (!net.degArrSumOut.empty())
        //if(0 != common_save1((fn + "_degArrSumOut.txt").c_str(), net.degArrSumOut, net.priChar)) ERROR();
        if (!net.nodeDegIn.empty())
            if(0 != common_save1((fn + "_nodeDegIn.txt").c_str(), net.nodeDegIn, net.priChar)) ERROR();
        if (!net.degArrValIn.empty())
            if(0 != common_save1((fn + "_degArrValIn.txt").c_str(), net.degArrValIn, net.priChar)) ERROR();
        if (!net.degArrSizeIn.empty())
            if(0 != common_save1((fn + "_degArrSizeIn.txt").c_str(), net.degArrSizeIn, net.priChar)) ERROR();
        //if (!net.degArrSumIn.empty())
        //if(0 != common_save1((fn + "_degArrSumIn.txt").c_str(), net.degArrSumIn, net.priChar)) ERROR();
        if(net.weightFlag){
            if(!net.nodeWeightOut.empty() && 0 != common_save1((fn + "_nodeWeightOut.txt").c_str(), net.nodeWeightOut, net.priChar)) ERROR();
            if(!net.degArrWeightOut.empty() && 0 != common_save1((fn + "_degArrWeightOut.txt").c_str(), net.degArrWeightOut, net.priChar)) ERROR();
            if(!net.nodeWeightIn.empty() && 0 != common_save1((fn + "_nodeWeightIn.txt").c_str(), net.nodeWeightIn, net.priChar)) ERROR();
            if(!net.degArrWeightIn.empty() && 0 != common_save1((fn + "_degArrWeightIn.txt").c_str(), net.degArrWeightIn, net.priChar)) ERROR();
        }
    }
    return 0;
}

int net_save_p2p(const Network& net, const char *name)
{
    string fn;
    if (name != NULL && name[0] != '\0') {
        fn = name;
    } else {
        stringstream ss;
        ss.clear();
        ss << net.seed;
        fn = net.saveName + '_' + ss.str();
    }
    //if(!net.p2p.empty() && 0 != common_save2((fn + "_p2p.txt").c_str(), net.p2p, net.priChar2)) ERROR();

    // link
    //if(!net.link.empty() && 0 != common_save2((fn + "_link.txt").c_str(), &net.link[0], net.linkSize, 2, net.priChar2)) ERROR();

    //if(net.linkMatr.size() > 0){
    //if(0 != common_save2((fn + "_linkMatr.txt").c_str(), net.linkMatr, net.priChar2)) ERROR();
    //}
    //if(net.status == -2 && 0 !=common_save1((fn + "_p2pSize.txt").c_str(), net.p2pSize)) ERROR();

    if(!net.lkk.empty() && 0 != common_save2((fn + "_lkk.txt").c_str(), net.lkk, net.priChar2)) ERROR();

    //if(net.weightFlag && !net.vvweight.empty() && 0 != common_save2((fn + "_vvweight.txt").c_str(), net.vvweight, net.priChar2)) ERROR();

    return 0;
}

//**//****************************************************//*
int net_read_link_0(Network& net, const char *name)
{
    string fn;
    if (name != NULL && name[0] != '\0') fn = name;
    else fn = net.readName + "_link.txt";

    if (0 != read0_link(net.link, fn.c_str(), net.weight_n)) {
        ERROR();
        return -1;
    }
    net.linkSize = net.link.size() / 2;

    return 0;
}

int net_read_link(Network& net, const char *name)
{
    string fn;
    if (name != NULL && name[0] != '\0') fn = name;
    else fn = net.readName + "_link.txt";

    if (0 != read_link(net.link, fn.c_str())) {
        ERROR();
        return -1;
    }
    net.linkSize = net.link.size() / 2;

    return 0;
}

int net_read_weight_link(Network& net, const char *name)
{
    string fn;
    if (name != NULL && name[0] != '\0') fn = name;
    else fn = net.readName + "_link.txt";

    if(net.weight_m < 2 || net.weight_m >= net.weight_n){
        ERROR();
        return -1;
    }
    if(0 != read_weight_link(net.vvweight, net.vvweightIn, net.linkSize, fn.c_str(), net.weight_m, net.weight_n, net.dirFlag)){
        ERROR();
        return -1;
    }
    return 0;
}

int net_read_link_weight_0(Network& net, const char *name)
{
    string fn;
    if (name != NULL && name[0] != '\0') fn = name;
    else fn = net.readName + "_link.txt";

    if(net.weight_m < 2 || net.weight_m >= net.weight_n){
        ERROR();
        return -1;
    }
    if(0 != read_link_weight_0(net.link, net.linkSize, net.vvweight, net.vvweightIn, fn.c_str(), net.weight_m, net.weight_n, net.dirFlag)){
        ERROR();
        return -1;
    }
    return 0;
}

int net_read_p2p_0(Network& net, const char *name)
{
    string fn;
    if (name != NULL && name[0] != '\0') fn = name;
    else fn = net.readName + "_p2p.txt";

    net.p2p.clear();
    if (0 != common_read2_0(fn.c_str(), net.p2p)) {
        ERROR();
        return -1;
    }
    cout << fn << "\tsize:\t" << net.p2p.size() << '\n';

    return 0;
}

int net_read_linkMatr_0(Network& net, const char *name)
{
    string fn;
    if (name != NULL && name[0] != '\0') fn = name;
    else fn = net.readName + "_linkMatr.txt";

    net.linkMatr.clear();
    if (0 != common_read2_0(fn.c_str(), net.linkMatr)) {
        ERROR();
        return -1;
    }
    cout << fn << "\tsize:\t" << net.linkMatr.size() << '\n';

    //linkMatr_fix_max(net.linkMatr);

    return 0;
}

int net_read_weightMatr_0(Network& net, const char *name)
{
    string fn;
    if (name != NULL && name[0] != '\0') fn = name;
    else fn = net.readName + "_weightMatr.txt";

    net.weightMatr.clear();
    if (0 != common_read2_0(fn.c_str(), net.weightMatr)) {
        ERROR();
        return -1;
    }
    cout << fn << "\tsize:\t" << net.weightMatr.size() << '\n';

    if(net.linkMatr.empty()) weightMatr_2_linkMatr(net.linkMatr, net.weightMatr);

    return 0;
}

//**//****************************************************//*
int net_lkk_2_degArr(Network& net)
{
    if(net.lkk.empty()){
        ERROR();
        return -1;
    }
    if(net.linkSize <= 0 && 0 != degArr_2_linkSize(net.linkSize, net.degArrVal, net.degArrSize)){
        ERROR();
        return -1;
    }
    if(net.nodeSize <= 0 && 0 != degArr_2_nodeSize(net.nodeSize, net.degArrSize)){
        ERROR();
        return -1;
    }
    if(net.degArrNo.empty() && 0 != degArrVal_2_degArrNo(net.degArrNo, net.degArrVal)){
        ERROR();
        return -1;
    }
    if(net.degArrSum.empty()) degArrSize_2_degArrSum(net.degArrSum, net.degArrSize);

    if(net.kMax <= 0){
        net.kMin = net.degArrVal.front();
        net.kMax = net.degArrVal.back();
    }
    if(net.linkSize > 0){   // degMean
        net.degMean = 2. * net.linkSize / (net.degArrSum.back() - (net.degArrVal.front() <= 0 ? net.degArrSize.front() : 0));
    }

    return 0;
}

int net_p2p_2_degArr(Network& net)
{
    if(net.p2p.empty()){
        ERROR();
        return -1;
    }
    if(net.nodeSize <= 0) p2p_2_nodeSize(net.nodeSize, net.p2p);
    if(net.nodeSize <= 0) {
        ERROR();
        return -1;
    }
    while(net.p2p.size() < net.nodeSize) net.p2p.resize(net.nodeSize);

    if(!net.dirFlag){   // !dirFlag
        // All
        if(net.nodeDeg.empty() && p2p_2_nodeDeg(net.nodeDeg, net.p2p) != 0){    // nodeDeg
            ERROR();
            return -1;
        }
        if(net.degArrVal.empty() && nodeDeg_2_degArr(net.nodeDeg, net.degArrVal, net.degArrSize, net.degArrSum) != 0){  // degArr
            ERROR();
            return -1;
        }
        if(net.degArrNo.empty() && 0 != degArrVal_2_degArrNo(net.degArrNo, net.degArrVal)){     // degArrNo
            ERROR();
            return -1;
        }
        if(net.linkSize <= 0 && nodeDeg_2_linkSize(net.linkSize, net.nodeDeg) != 0) {   // linkSize
            ERROR();
            return -1;
        }
        if(net.lkk.empty() && 0 != p2p_2_lkk(net.lkk, net.p2p, net.degArrNo, net.degArrVal.size())){  // lkkMatr
            ERROR();
            return -1;
        }
        // weightFlag
        if(net.weightFlag){     // nodeWeight degArrWeight
            if(net.nodeWeight.empty() && !net.vvweight.empty()) vvweight_2_nodeWeight(net.nodeWeight, net.p2p, net.vvweight, net.netWeight);
            if(net.degArrWeight.empty() && !net.nodeWeight.empty()) nodeWeight_2_degArrWeight(net.degArrWeight, net.nodeWeight, net.nodeDeg, net.degArrNo, net.degArrVal.size());
        }

    }else{  //dirFlag
        // Out
        if(net.nodeDegOut.empty() && p2p_2_nodeDeg(net.nodeDegOut, net.p2p) != 0){
            ERROR();
            return -1;
        }
        if(net.nodeDegOut.size() <= net.nodeSize){
            net.nodeDegOut.resize(net.nodeSize, 0);
        }else{
            ERROR();
            return -1;
        }
        if(net.degArrValOut.empty() && nodeDeg_2_degArr(net.nodeDegOut, net.degArrValOut, net.degArrSizeOut, net.degArrSumOut) != 0){
            ERROR();
            return -1;
        }
        if(net.degArrNoOut.empty() && 0 != degArrVal_2_degArrNo(net.degArrNoOut, net.degArrValOut)){
            ERROR();
            return -1;
        }
        // Out Weight
        if(net.weightFlag){
            if(net.nodeWeightOut.empty() && !net.vvweight.empty()) vvweight_2_nodeWeight(net.nodeWeightOut, net.p2p, net.vvweight, net.netWeightOut);
            if(net.degArrWeightOut.empty() && !net.nodeWeightOut.empty()) nodeWeight_2_degArrWeight(net.degArrWeightOut, net.nodeWeightOut, net.nodeDegOut, net.degArrNoOut, net.degArrValOut.size());
        }

        // In
        if(net.p2pIn.empty() && p2p_2_p2pIn(net.p2pIn, net.p2p) != 0){
            ERROR();
            return -1;
        }
        if(net.nodeDegIn.empty() && p2p_2_nodeDeg(net.nodeDegIn, net.p2pIn) != 0){
            ERROR();
            return -1;
        }
        if(net.nodeDegIn.size() <= net.nodeSize){
            net.nodeDegIn.resize(net.nodeSize, 0);
        }else{
            ERROR();
            return -1;
        }
        if(net.degArrValIn.empty() && nodeDeg_2_degArr(net.nodeDegIn, net.degArrValIn, net.degArrSizeIn, net.degArrSumIn) != 0){
            ERROR();
            return -1;
        }
        if(net.degArrNoIn.empty() && 0 != degArrVal_2_degArrNo(net.degArrNoIn, net.degArrValIn)){
            ERROR();
            return -1;
        }
        // In Weight
        if(net.weightFlag){
            if(net.nodeWeightIn.empty() && !net.vvweightIn.empty()) vvweight_2_nodeWeight(net.nodeWeightIn, net.p2pIn, net.vvweightIn, net.netWeightIn);
            if(net.degArrWeightIn.empty() && !net.nodeWeightIn.empty()) nodeWeight_2_degArrWeight(net.degArrWeightIn, net.nodeWeightIn, net.nodeDegIn, net.degArrNoIn, net.degArrValIn.size());
        }

        // All
        if(net.nodeDeg.empty() && nodeDegIO_2_nodeDeg(net.nodeDeg, net.nodeDegOut, net.nodeDegIn) != 0){
            ERROR();
            return -1;
        }
        if(net.degArrVal.empty() && nodeDeg_2_degArr(net.nodeDeg, net.degArrVal, net.degArrSize, net.degArrSum) != 0){
            ERROR();
            return -1;
        }
        if(net.degArrNo.empty() && 0 != degArrVal_2_degArrNo(net.degArrNo, net.degArrVal)){
            ERROR();
            return -1;
        }
        if(net.linkSize <= 0 && nodeDeg_2_linkSize(net.linkSize, net.nodeDeg) != 0) {   // linkSize
            ERROR();
            return -1;
        }
        if(net.lkk.empty() && 0 != p2p_2_lkk_dir(net.lkk, net.p2p, net.nodeDeg, net.nodeDeg, net.degArrNo, net.degArrNo, net.degArrVal.size(), net.degArrVal.size())){  // lkk
            ERROR();
            return -1;
        }
        if(net.lkkOutIn.empty() && 0 != p2p_2_lkk_dir(net.lkkOutIn, net.p2p, net.nodeDegOut, net.nodeDegIn, net.degArrNoOut, net.degArrNoIn, net.degArrValOut.size(), net.degArrValIn.size())){  // lkkOutIn
            ERROR();
            return -1;
        }
        // All Weight
        if(net.weightFlag){
            if(net.nodeWeight.empty() && !net.nodeWeight.empty()) nodeWeightIO_2_nodeWeight(net.nodeWeight, net.nodeWeightOut, net.nodeWeightIn);
            net.netWeight = net.netWeightOut + net.netWeightIn;
            if(net.degArrWeight.empty() && !net.nodeWeight.empty()) nodeWeight_2_degArrWeight(net.degArrWeight, net.nodeWeight, net.nodeDeg, net.degArrNo, net.degArrVal.size());
        }
    }

    if(net.kMax <= 0){
        net.kMin = net.degArrVal.front();
        net.kMax = net.degArrVal.back();
    }
    if(net.linkSize > 0){   // degMean degWeightMean
        net.degMean = 2. * net.linkSize / (net.degArrSum.back() - (net.degArrVal.front() <= 0 ? net.degArrSize.front() : 0));
        if(net.weightFlag) net.degWeightMean = (double)net.netWeight / (net.degArrSum.back() - (net.degArrVal.front() <= 0 ? net.degArrSize.front() : 0));
        if(net.dirFlag){
            net.degMeanOut = (double)net.linkSize / (net.degArrSumOut.back() - (net.degArrValOut.front() <= 0 ? net.degArrSizeOut.front() : 0));
            net.degMeanIn = (double)net.linkSize / (net.degArrSumIn.back() - (net.degArrValIn.front() <= 0 ? net.degArrSizeIn.front() : 0));
            if(net.weightFlag){
                net.degWeightMeanOut = (double)net.netWeightOut / (net.degArrSum.back() - (net.degArrVal.front() <= 0 ? net.degArrSize.front() : 0));
                net.degWeightMeanIn = (double)net.netWeightIn / (net.degArrSum.back() - (net.degArrVal.front() <= 0 ? net.degArrSize.front() : 0));
            }
        }
    }
    return 0;
}

//**//****************************************************//*
// 节点按度排序 net->net2 剔除度为0的点
int net_fix_p2p_nodeDeg0(Network& net)
{
    if (net.status < 0 || net.p2p.empty() || (net.degArrVal.empty() && 0 != net_p2p_2_degArr(net))) {
        ERROR();
        return -1;
    }
    int flag = check_nodeDeg0(net.nodeDeg);
    cout << "check_nodeDeg0\t" << flag << endl;
    if(flag == 0) return 0;
    if(flag < 0 || (flag > 0 && net.net2 == NULL)){
        ERROR();
        return flag;
    }
    Network &net2 = *net.net2;
    if(net.degArrVal.back() <= 0){  // net2.nodeSize = 0
        ERROR();
        return -1;
    }
    net2.dirFlag = net.dirFlag;

    // net2.nodesName[i] <- i
    net.nodeSize = net.p2p.size();
    net2.nodeSize = net.nodeSize - net.degArrSize.front();
    net2.nodesName.resize(net.nodeSize);
    for (NodeType i = 0; i < net.nodeSize; i++) net2.nodesName[i] = i;
    net2.nodesName2 = net2.nodesName;
    common_sort_p_val(net2.nodesName.rbegin(), net2.nodesName.rend(), &net.nodeDeg.front());  // 按度从大到小排

    // i -> net2.nodesName2[i]
    common_sort_p_val(net2.nodesName2.begin(), net2.nodesName2.end(), &net2.nodesName.front());

    // 更新net2的连边信息net2.p2p
    net2.p2p.resize(net2.nodeSize);
    for (NodeType i = 0; i < net2.nodeSize; i++) net2.p2p[i].reserve(net.nodeDeg[net2.nodesName[i]]);
    for (NodeType i2 = 0; i2 < net2.p2p.size(); i2++) {
        NodeType i = net2.nodesName[i2];
        for (VNodeTypeCItr j = net.p2p[i].begin(); j != net.p2p[i].end(); j++) {
            net2.p2p[i2].push_back(net2.nodesName2[*j]);
        }
    }
    for (VVNodeTypeItr i = net2.p2p.begin(); i != net2.p2p.end(); i++) sort(i->begin(), i->end());   // net2.p2p从小到大排序

    // 更新net2的度信息
    if (0 != net_p2p_2_degArr(net2)) {
        ERROR();
        return -1;
    }
    net2.kMin = net2.degArrVal.front();
    net2.kMax = net2.degArrVal.back();
    net2.status = 1;

    return 0;
}

//**//****************************************************//*

