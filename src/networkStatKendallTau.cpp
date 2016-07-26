#include "StatKendallTau.h"
#include "networkStatKendallTau.h"
#ifdef STAT_KENDALLTAU

#include "common.h"
using namespace std;

//**//****************************************************//*
int net_clear_kendallTau(Network& net)
{
    return 0;
}

//**//****************************************************//*
int net_cal_kendallTau(Network& net)
{
    if(net.lkkSum.empty() && 0 != lkk_2_lkkSum(net.lkkSum, net.lkk, net.dirFlag)){
        ERROR();
        return -1;
    }
    cal_kendallTau_lkkSum(net.kendallTau, net.lkk, net.lkkSum, net.dirFlag);
    //al_kendallTau_lkk(net.kendallTau, net.lkk, net.linkSize, net.dirFlag);
    if(net.dirFlag){
        if(net.lkkSumOutIn.empty() && 0 != lkk_2_lkkSum(net.lkkSumOutIn, net.lkkOutIn, net.dirFlag)){
            ERROR();
            return -1;
        }
        cal_kendallTau_lkkSum(net.kendallTauOutIn, net.lkkOutIn, net.lkkSumOutIn, net.dirFlag);
    }
    return 0;
}

//**//****************************************************//*
int net_read_params_kendallTau(istream& is, Network& net)
{
    for(string s; is >> s;){
        if (s == "--kendallTau") {
            is >> net.kendallTau;
            cout << s << '\t'   << net.kendallTau << endl;
            continue;
        }
        if (s == "--kendallTauOutIn") {
            is >> net.kendallTauOutIn;
            cout << s << '\t'   << net.kendallTauOutIn << endl;
            continue;
        }
    }
    return 0;
}

int net_save_params_kendallTau(ostream& os, const Network& net)
{
    if(!os) return -1;
    os << "--kendallTau\t" << net.kendallTau << '\n';
    if(net.dirFlag) os << "--kendallTauOutIn\t" << net.kendallTauOutIn << '\n';
    return 0;
}

int net_save_kendallTau(const Network& net, const char *name)
{
    //string fn;
    //if(name != NULL && name[0] != '\0') fn = name;
    //else{
        //stringstream ss;
        //ss << net.seed;
        //fn = net.saveName + '_' + ss.str();
    //}
    int f = 0;
    return f;
}
//**//****************************************************//*
#endif  // STAT_KENDALLTAU
