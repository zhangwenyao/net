#include "NetDegree.h"
#include "networkDegree.h"
#ifdef NET_DEGREE

#include "common.h"
using namespace std;

//**//****************************************************//*
#ifdef DEG_POISSON
int net_deg_poisson(Network& net) // 生成度序列 各点均按概率取任意度
{
    // 生成度分布概率
    poisson_cal_degArr(net.params_degree.poisson_p, net.degArrVal, net.degArrProb, net.kMin, net.kMax, net.nodeSize);
    net.nodeDeg.resize(net.nodeSize);
    random_new_randKArr(&net.nodeDeg[0], (size_t)net.nodeSize, &net.degArrProb[0], &net.degArrVal[0], net.degArrVal.size()); // 调用通用随机函数
    // 修正度序列使总数为偶数
    if(nodeDeg_2_linkSize(net.linkSize, net.nodeDeg) != 0){
        fix_nodeDeg(net.nodeDeg, net.degArrProb, net.degArrVal, net.linkSize);
        net.linkSize /= 2;
    }
    sort(net.nodeDeg.begin(), net.nodeDeg.end()); // 调用系统函数sort，对节点按度从小到大排序
    nodeDeg_2_degArr_Sort(net.nodeDeg, net.degArrVal, net.degArrSize, net.degArrSum);
    return 0;
}

//**//****************************************************//*
int net_read_params_poisson(istream& is, Network& net)
{
    for(string s; is >> s;){
        if (s == "--params_degree.poisson_p") {
            is >> net.params_degree.poisson_p;
            cout << s << '\t'   << net.params_degree.poisson_p << endl;
            continue;
        }
    }
    return 0;
}

int net_save_params_poisson(ostream& os, const Network& net)
{
    if(!os) return -1;
    os << "--params_degree.poisson_p\t" << net.params_degree.poisson_p
        << '\n';
    return 0;
}

#endif  // DEG_POISSON

//**//****************************************************//*
#ifdef DEG_POWER
int net_power_check_params(Network& net)
{
    if(net.kMin > net.kMax || net.kMax >= net.nodeSize || (net.kMin == net.kMax && net.nodeSize % 2 == 1 && net.kMin % 2 == 1) || net.params_degree.power_gamma < 0) return -1;
    return 0;
}

// 生成度分布
int net_deg_power(Network& net)
{
    // 生成度分布概率
    power_cal_degArr(net.params_degree.power_gamma, net.degArrVal, net.degArrProb, net.kMin, net.kMax);
    net.nodeDeg.resize(net.nodeSize);
    random_new_randKArr(&net.nodeDeg[0], (size_t)net.nodeSize, &net.degArrProb[0], &net.degArrVal[0], net.degArrVal.size()); // 调用通用随机函数
    // 修正度序列使总数为偶数
    if(nodeDeg_2_linkSize(net.linkSize, net.nodeDeg) != 0){
        fix_nodeDeg(net.nodeDeg, net.degArrProb, net.degArrVal, net.linkSize);
        net.linkSize /= 2;
    }
    sort(net.nodeDeg.begin(), net.nodeDeg.end()); // 调用系统函数sort，对节点按度从小到大排序
    nodeDeg_2_degArr_Sort(net.nodeDeg, net.degArrVal, net.degArrSize, net.degArrSum);
    return 0;
}

//**//****************************************************//*
int net_read_params_power(istream& is, Network& net)
{
    for(string s; is >> s;){
        if (s == "--params_degree.power_gamma") {
            is >> net.params_degree.power_gamma;
            cout << s << '\t'   << net.params_degree.power_gamma << endl;
            continue;
        }
    }
    return 0;
}

int net_save_params_power(ostream& os, const Network& net)
{
    if(!os) return -1;
    os << "--params_degree.power_gamma\t" << net.params_degree.power_gamma
        << '\n';
    return 0;
}

#endif  // DEG_POWER

//**//****************************************************//*
#endif  // NET_DEGREE

