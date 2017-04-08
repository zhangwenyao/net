#include "ActSIS.h"
#include "networkActSIS.h"
#ifdef ACT_SIS

#include "common.h"
using namespace std;
//**//****************************************************//*
int net_save_params_act_SIS(std::ostream& os, const ParamsSIS& params)
{
    if(!os) return -1;
    os   << "--lambda_c\t" << params.lambda_c
         << "\n--ksi\t"    << params.ksi
         << "\n--lambda\t" << params.lambda
         << "\n--p\t"      << params.p
         << "\n--p0\t"     << params.p0
         << "\n";
    return 0;
}

int net_save_params_act_SIS(std::ostream& os, const Network& net)
{
    return net_save_params_act_SIS(os, *((const ParamsSIS*)net.params));
}

int net_act_SIS(Network &net, ParamsSIS& params)
{
    act_SIS_init(params.statusSN, params.SN, params.N_i, params.NDeg_i, params.t, net.p2p, params.p0, params.M);
    params.nSum = 0;
    params.n2Sum = 0;
    params.nNum = 0;
    act_SIS(params.statusSN, params.SN, params.N_i, params.NDeg_i, params.t, params.nSum, params.n2Sum, params.nNum, params.p, params.lambda, params.t_r, params.t_av, net.p2p, net.kMax);
    act_SIS_cal_params(params.ksi, params.lambda_c, net.p2p, params.nSum, params.n2Sum, params.nNum);
    return 0;
}

//**//****************************************************//*
#endif  // ACT_SIS

