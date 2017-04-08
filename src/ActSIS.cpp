#include "ActSIS.h"
#ifdef ACT_SIS

#include "common.h"
using namespace std;

//**//*****************************************************//*
int SIS_update(VNodeType &statusSN, VNodeType &SN, NodeType &N_i, LinkType &NDeg_i, const NodeType degMax, const VVNodeType& p2p, double &dt, const double lambda);
int SIS_update2(VVNodeType &statusSN, VVNodeType &SN, VNodeType &N_i, VLinkType &NDeg_i, VDouble &t, const double p, const double lambda, const VVNodeType& p2p, const NodeType degMax);

//**//*****************************************************//*
int act_SIS_init(VVNodeType &statusSN, VVNodeType &SN, VNodeType &N_i, VLinkType & NDeg_i, VDouble &t, const VVNodeType& p2p, const double p0, const unsigned M)
{
    t.assign(M + 1, 0);
    statusSN.resize(M + 1);
    SN.resize(M + 1);
    NodeType iN = 0, sN = 0;
    LinkType iD = 0;
    VNodeType &ssn = statusSN[M], &sn = SN[M];
    const NodeType nodeSize = p2p.size();
    ssn.resize(nodeSize);
    sn.resize(nodeSize);
    for(NodeType i = 0; i < nodeSize; ++i){
        if(FRAND2() < p0){
            sn[i] = iN++;
            ssn[sn[i]] = i;
            iD += p2p[i].size();
        }else{
            sn[i] = nodeSize - ++sN;
            ssn[sn[i]] = i;
        }
    }
    for(unsigned i = 0; i < M; ++i){
        statusSN[i] = statusSN[M];
        SN[i] = SN[M];
    }
    N_i.assign(M + 1, iN);
    NDeg_i.assign(M + 1, iD);
    return 0;
}

int SIS_update(VNodeType &statusSN, VNodeType &SN, NodeType &N_i, LinkType &NDeg_i, const NodeType degMax, const VVNodeType& p2p, double &dt, const double lambda)
{
    if(N_i <= 0 || NDeg_i <= 0){
        dt = 0;
        return 0;
    }
    double all_i = N_i + lambda * NDeg_i;
    dt = 1. / all_i;
    if(FRAND2() * all_i <= N_i){
        //recover
        NodeType ssn_i = RAND2() % N_i--, i = statusSN[ssn_i];
        if(ssn_i != N_i){
            NodeType j = statusSN[N_i];
            statusSN[ssn_i] = j;
            SN[j] = ssn_i;
            statusSN[N_i] = i;
            SN[i] = N_i;
        }
        NDeg_i -= p2p[i].size();
    }else{
        // spread
        for(NodeType i, j, k; 1;){
            i = statusSN[RAND2() % N_i];
            if((k = RAND2() % degMax) < p2p[i].size()){
                j = p2p[i][k];
                if(SN[j] >= N_i){
                    // infect
                    NodeType ssn_j = SN[j], l = statusSN[N_i];
                    if(ssn_j != N_i){
                        statusSN[N_i] = j;
                        SN[j] = N_i;
                        statusSN[ssn_j] = l;
                        SN[l] = ssn_j;
                    }
                    N_i++;
                    NDeg_i += p2p[j].size();
                }
                break;
            }
        }
    }
    return 0;
}

int SIS_update2(VVNodeType &statusSN, VVNodeType &SN, VNodeType &N_i, VLinkType &NDeg_i, VDouble &t, const double p, const double lambda, const VVNodeType& p2p, const NodeType degMax)
{
    int flag = 0;
    const unsigned M = N_i.size() - 1;
    double dt = 0;
    SIS_update(statusSN[M], SN[M], N_i[M], NDeg_i[M], degMax, p2p, dt, lambda);
    if(N_i[M] <= 0){    // all recovered
        NodeType i = RAND2() % M;
        statusSN[M] = statusSN[i];
        SN[M] = SN[i];
        N_i[M] = N_i[i];
        NDeg_i[M] = NDeg_i[i];
        t[M] = t[i];
        flag = 1;
    }else{
        t[M] += dt;
        if(FRAND2() < p * dt){ // renew status
            NodeType i = RAND2() % M;
            statusSN[i] = statusSN[M];
            SN[i] = SN[M];
            N_i[i] = N_i[M];
            NDeg_i[i] = NDeg_i[M];
            t[i] = t[M];
        }
    }
    return flag;
}

int act_SIS(VVNodeType &statusSN, VVNodeType &SN, VNodeType &N_i, VLinkType &NDeg_i, VDouble &t, LinkType &nSum, LinkType &n2Sum, NodeType &nNum, const double p, const double lambda, const double t_r, double t_av, const VVNodeType& p2p, const NodeType degMax)
{
    const unsigned M = N_i.size() - 1;
    while(t_av > 0){
        while(t[M] < t_r) SIS_update2(statusSN, SN, N_i, NDeg_i, t, p, lambda, p2p, degMax);
        double t0 = t[M];
        if(0 == SIS_update2(statusSN, SN, N_i, NDeg_i, t, p, lambda, p2p, degMax)){
            t_av -= t[M] - t0;
            nNum++;
            nSum += N_i[M];
            n2Sum += (LinkType)N_i[M] * N_i[M];
        }
    }
    return 0;
}

int act_SIS_cal_params(double &ksi, double &lambda_c, const VVNodeType& p2p, const NodeType& nSum, const LinkType& n2Sum, const NodeType& nNum)
{
    ksi = ((double)n2Sum - ((double)nSum * nSum) / nNum) / nSum;
    LinkType kSum = 0, k2Sum = 0;
    for(NodeType i = 0; i < p2p.size(); ++i){
        NodeType k = p2p[i].size();
        kSum += k;
        k2Sum += k * k;
    }
    lambda_c = (double)kSum / k2Sum;
    return 0;
}
//**//*****************************************************//*
#endif // ACT_SIS

