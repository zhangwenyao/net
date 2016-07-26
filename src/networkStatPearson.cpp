#include "StatPearson.h"
#include "networkStatPearson.h"
#ifdef STAT_PEARSON

#include "common.h"
using namespace std;

//**//****************************************************//*
int net_clear_pearson(Network& net)
{
    net.nodeNeiAveDeg.clear();
    net.neiAveDeg.clear();
    if(net.dirFlag){
        net.nodeNeiAveDegIn.clear();
        net.neiAveDegInOut.clear();
        net.neiAveDegInIn.clear();
        net.nodeNeiAveDegOut.clear();
        net.neiAveDegOutIn.clear();
        net.neiAveDegOutOut.clear();
    }
    return 0;
}

//**//****************************************************//*
int net_cal_pearson(Network& net)
{
    if(!net.dirFlag){
        if(!net.lkk.empty() && !net.weightFlag) cal_pearson_lkk(net.pearson, net.lkk, net.degArrVal, net.linkSize);
        if(!net.p2p.empty()){
            cal_nodeNeiAveDeg_weight(net.nodeNeiAveDeg, net.p2p, net.nodeDeg, net.vvweight, net.nodeWeight, net.weightFlag);
            cal_neiAveDeg_weight(net.neiAveDeg, net.nodeNeiAveDeg, net.nodeDeg, net.degArrSize, net.degArrNo, net.degArrVal, net.degArrWeight, net.nodeWeight, net.weightFlag);
            if(!net.weightFlag){
                if(net.lkk.empty()) cal_pearson(net.pearson, net.p2p, net.linkSize);
            }else cal_pearson_dir_weight(net.pearson, net.ps_rho, net.p2p, net.vvweight, net.netWeight, net.nodeDeg, net.nodeDeg, net.weightFlag);
        }

    }else{
        // AllAll
        cal_nodeNeiAveDeg_AllAll_weight(net.nodeNeiAveDeg, net.p2p, net.nodeDeg, net.vvweight, net.nodeWeight, net.weightFlag);
        cal_neiAveDeg_weight(net.neiAveDeg, net.nodeNeiAveDeg, net.nodeDeg, net.degArrSize, net.degArrNo, net.degArrVal, net.degArrWeight, net.nodeWeight, net.weightFlag);
        cal_pearson_dir_weight(net.pearson, net.ps_rho, net.p2p, net.vvweight, (net.weightFlag ? net.netWeightOut : net.linkSize), net.nodeDeg, net.nodeDeg, net.weightFlag);

        //OutIn
        cal_nodeNeiAveDeg_weight(net.nodeNeiAveDegIn, net.p2p, net.nodeDegIn, net.vvweight, net.nodeWeightOut, net.weightFlag);
        cal_neiAveDeg_weight(net.neiAveDegOutIn, net.nodeNeiAveDegIn, net.nodeDegOut, net.degArrSizeOut, net.degArrNoOut, net.degArrValOut, net.degArrWeightOut, net.nodeWeightOut, net.weightFlag);
        cal_pearson_dir_weight(net.pearsonOutIn, net.ps_rhoOutIn, net.p2p, net.vvweight, (net.weightFlag ? net.netWeightOut : net.linkSize), net.nodeDegOut, net.nodeDegIn, net.weightFlag);

        if(STAT_TYPE_DIRAA){
            // OutOut
            cal_nodeNeiAveDeg_weight(net.nodeNeiAveDegOut, net.p2p, net.nodeDegOut, net.vvweight, net.nodeWeightOut, net.weightFlag);
            cal_neiAveDeg_weight(net.neiAveDegOutOut, net.nodeNeiAveDegOut, net.nodeDegOut, net.degArrSizeOut, net.degArrNoOut, net.degArrValOut, net.degArrWeightOut, net.nodeWeightOut, net.weightFlag);
            cal_pearson_dir_weight(net.pearsonOutOut, net.ps_rhoOutOut, net.p2p, net.vvweight, (net.weightFlag ? net.netWeightOut : net.linkSize), net.nodeDegOut, net.nodeDegOut, net.weightFlag);

            // InIn
            cal_neiAveDeg_weight(net.neiAveDegInIn, net.nodeNeiAveDegIn, net.nodeDegIn, net.degArrSizeIn, net.degArrNoIn, net.degArrValIn, net.degArrWeightOut, net.nodeWeightOut, net.weightFlag);
            cal_pearson_dir_weight(net.pearsonInIn, net.ps_rhoInIn, net.p2p, net.vvweight, (net.weightFlag ? net.netWeightOut : net.linkSize), net.nodeDegIn, net.nodeDegIn, net.weightFlag);

            // InOut
            cal_neiAveDeg_weight(net.neiAveDegInOut, net.nodeNeiAveDegOut, net.nodeDegIn, net.degArrSizeIn, net.degArrNoIn, net.degArrValIn, net.degArrWeightOut, net.nodeWeightOut, net.weightFlag);
            cal_pearson_dir_weight(net.pearsonInOut, net.ps_rhoInOut, net.p2p, net.vvweight, (net.weightFlag ? net.netWeightOut : net.linkSize), net.nodeDegIn, net.nodeDegOut, net.weightFlag);
        }
    }

    return 0;
}

//**//****************************************************//*
int net_read_params_pearson(istream& is, Network& net)
{
    for(string s; is >> s;){
        if (s == "--pearson") {
            is >> net.pearson;
            cout << s << '\t'   << net.pearson << endl;
            continue;
        }
        if(net.dirFlag) {
            if (s == "--pearsonInIn") {
                is >> net.pearsonInIn;
                cout << s << '\t'   << net.pearsonInIn << endl;
                continue;
            }
            if (s == "--pearsonInOut") {
                is >> net.pearsonInOut;
                cout << s << '\t'   << net.pearsonInOut << endl;
                continue;
            }
            if (s == "--pearsonOutIn") {
                is >> net.pearsonOutIn;
                cout << s << '\t'   << net.pearsonOutIn << endl;
                continue;
            }
            if (s == "--pearsonOutOut") {
                is >> net.pearsonOutOut;
                cout << s << '\t'   << net.pearsonOutOut << endl;
                continue;
            }
        }
    }
    return 0;
}

int net_save_params_pearson(ostream& os, const Network& net)
{
    if(!os) return -1;
    if(!net.dirFlag){
        os << "--pearson\t" << net.pearson << '\n';
    }else{
        os  << "--pearson\t" << net.pearson
            << "\n--ps_rho\t" << net.ps_rho
            << "\n--pearsonOutIn\t" << net.pearsonOutIn
            << "\n--ps_rhoOutIn\t" << net.ps_rhoOutIn
            << '\n';
        if(STAT_TYPE_DIRAA){
            os  << "--pearsonOutOut\t"  << net.pearsonOutOut
                << "\n--ps_rhoOutOut\t"   << net.ps_rhoOutOut
                << "\n--pearsonInIn\t"  << net.pearsonInIn
                << "\n--ps_rhoInIn\t"   << net.ps_rhoInIn
                << "\n--pearsonInOut\t" << net.pearsonInOut
                << "\n--ps_rhoInOut\t"  << net.ps_rhoInOut
                << '\n';
        }
    }
    return 0;
}

int net_save_pearson(const Network& net, const char *name)
{
    string fn;
    if(name != NULL && name[0] != '\0') fn = name;
    else{
        stringstream ss;
        ss << net.seed;
        fn = net.saveName + '_' + ss.str();
    }
    int f = 0;
    //if(!net.nodeNeiAveDeg.empty()) f |= common_save1((fn + "_nodeNeiAveDeg.txt").c_str(), net.nodeNeiAveDeg, net.priChar);
    //if(!net.neiAveDeg.empty()) f |= common_save1((fn + "_neiAveDeg.txt").c_str(), net.neiAveDeg, net.priChar);

    //if(net.dirFlag){
    //if(!net.nodeNeiAveDegIn.empty()) f |= common_save1((fn + "_nodeNeiAveDegIn.txt").c_str(), net.nodeNeiAveDegIn, net.priChar);
    //if(!net.nodeNeiAveDegOut.empty()) f |= common_save1((fn + "_nodeNeiAveDegOut.txt").c_str(), net.nodeNeiAveDegOut, net.priChar);
    //if(!net.neiAveDegInIn.empty()) f |= common_save1((fn + "_neiAveDegInIn.txt").c_str(), net.neiAveDegInIn, net.priChar);
    //if(!net.neiAveDegInOut.empty()) f |= common_save1((fn + "_neiAveDegInOut.txt").c_str(), net.neiAveDegInOut, net.priChar);
    //if(!net.neiAveDegOutIn.empty()) f |= common_save1((fn + "_neiAveDegOutIn.txt").c_str(), net.neiAveDegOutIn, net.priChar);
    //if(!net.neiAveDegOutOut.empty()) f |= common_save1((fn + "_neiAveDegOutOut.txt").c_str(), net.neiAveDegOutOut, net.priChar);
    //}
    return f;
}
//**//****************************************************//*
#endif  // STAT_PEARSON
