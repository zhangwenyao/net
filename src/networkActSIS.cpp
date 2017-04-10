#include "ActSIS.h"
#include "networkActSIS.h"
#ifdef ACT_SIS

#include "common.h"
using namespace std;
//**//****************************************************//*
int net_save_params_act_SIS(std::ostream& os, const Network& net)
{
    if(!os) return -1;
    os    << "--act_SIS-lambda_c\t" << net.act_SIS.lambda_c
          << "\n--act_SIS-ksi\t"    << net.act_SIS.ksi
          << "\n--act_SIS-lambda\t" << net.act_SIS.lambda
          << "\n--act_SIS-p0\t"     << net.act_SIS.p0
          << "\n--act_SIS-p\t"      << net.act_SIS.p
          << "\n";
    return 0;
}

int net_act_SIS(Network &net)
{
    act_SIS_init(net.act_SIS.statusSN, net.act_SIS.SN, net.act_SIS.N_i, net.act_SIS.NDeg_i, net.act_SIS.t, net.p2p, net.act_SIS.p0, net.act_SIS.M);
    net.act_SIS.nSum = 0;
    net.act_SIS.n2Sum = 0;
    net.act_SIS.nNum = 0;
    act_SIS(net.act_SIS.statusSN, net.act_SIS.SN, net.act_SIS.N_i, net.act_SIS.NDeg_i, net.act_SIS.t, net.act_SIS.nSum, net.act_SIS.n2Sum, net.act_SIS.nNum, net.act_SIS.p, net.act_SIS.lambda, net.act_SIS.t_r, net.act_SIS.t_av, net.p2p, net.kMax);
    act_SIS_cal_params(net.act_SIS.ksi, net.act_SIS.lambda_c, net.p2p, net.act_SIS.nSum, net.act_SIS.n2Sum, net.act_SIS.nNum);
    return 0;
}

//**//****************************************************//*
#endif  // ACT_SIS

