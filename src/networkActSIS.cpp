#include "ActSIS.h"
#include "networkActSIS.h"
#ifdef ACT_SIS

#include "common.h"
using namespace std;
//**//****************************************************//*
int net_act_SIS(Network &net, ParamsSIS& params)
{
    act_SIS_init(params.statusSN, params.SN, params.N_i, params.NDeg_i, params.t, net.p2p, params.p0, params.M);
    params.nSum = 0;
    params.n2Sum = 0;
    params.nNum = 0;
    act_SIS(params.statusSN, params.SN, params.N_i, params.NDeg_i, params.t, params.nSum, params.n2Sum, params.nNum, params.p, params.lambda, params.t_r, params.t_av, net.p2p, net.kMax);
    params.ksi = ((double)params.n2Sum - ((double)params.nSum * params.nSum) / params.nNum) / params.nSum;
    return 0;
}

//**//****************************************************//*
#endif  // ACT_SIS

