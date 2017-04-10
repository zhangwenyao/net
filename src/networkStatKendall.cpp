#include "StatKendall.h"
#include "networkStatKendall.h"
#ifdef STAT_KENDALL

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
    cal_kendallTau_lkkSum(net.stat_kendall.tau, net.lkk, net.lkkSum, net.dirFlag);
    //al_kendallTau_lkk(net.stat_kendall.tau, net.lkk, net.linkSize, net.dirFlag);
    if(net.dirFlag){
        if(net.lkkSumOutIn.empty() && 0 != lkk_2_lkkSum(net.lkkSumOutIn, net.lkkOutIn, net.dirFlag)){
            ERROR();
            return -1;
        }
        cal_kendallTau_lkkSum(net.stat_kendall.OutIn, net.lkkOutIn, net.lkkSumOutIn, net.dirFlag);
    }
    return 0;
}

//**//****************************************************//*
int net_read_params_kendallTau(istream& is, Network& net)
{
    for(string s; is >> s;){
        if (s == "--stat_kendall.tau") {
            is >> net.stat_kendall.tau;
            cout << s << '\t'   << net.stat_kendall.tau << endl;
            continue;
        }
        if (s == "--stat_kendall.OutIn") {
            is >> net.stat_kendall.OutIn;
            cout << s << '\t'   << net.stat_kendall.OutIn << endl;
            continue;
        }
    }
    return 0;
}

int net_save_params_kendallTau(ostream& os, const Network& net)
{
    if(!os) return -1;
    os << "--stat_kendall.tau\t" << net.stat_kendall.tau << '\n';
    if(net.dirFlag) os << "--stat_kendall.OutIn\t" << net.stat_kendall.OutIn << '\n';
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
#endif  // STAT_KENDALL
