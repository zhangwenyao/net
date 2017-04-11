#include "ActSIS.h"
#include "networkActSIS.h"
#ifdef ACT_SIS

#include "common.h"
using namespace std;
//**//****************************************************//*
int net_save_params_act_SIS(std::ostream& os, const Network& net)
{
    if(!os) return -1;
    os    << "--params_SIS-lambda_c\t" << net.params_SIS.lambda_c
          << "\n--params_SIS-ksi\t"    << net.params_SIS.ksi
          << "\n--params_SIS-lambda\t" << net.params_SIS.lambda
          << "\n--params_SIS-p0\t"     << net.params_SIS.p0
          << "\n--params_SIS-p\t"      << net.params_SIS.p
          << "\n";
    return 0;
}

int net_act_SIS(Network &net)
{
    act_SIS_init(net.params_SIS.statusSN, net.params_SIS.SN, net.params_SIS.N_i, net.params_SIS.NDeg_i, net.params_SIS.t, net.p2p, net.params_SIS.p0, net.params_SIS.M);
    net.params_SIS.nSum = 0;
    net.params_SIS.n2Sum = 0;
    net.params_SIS.nNum = 0;
    act_SIS(net.params_SIS.statusSN, net.params_SIS.SN, net.params_SIS.N_i, net.params_SIS.NDeg_i, net.params_SIS.t, net.params_SIS.nSum, net.params_SIS.n2Sum, net.params_SIS.nNum, net.params_SIS.p, net.params_SIS.lambda, net.params_SIS.t_r, net.params_SIS.t_av, net.p2p, net.kMax);
    act_SIS_cal_params(net.params_SIS.ksi, net.params_SIS.lambda_c, net.p2p, net.params_SIS.nSum, net.params_SIS.n2Sum, net.params_SIS.nNum);
    return 0;
}

//**//****************************************************//*
#endif  // ACT_SIS

