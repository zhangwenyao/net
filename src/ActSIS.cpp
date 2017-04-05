#include "ActSIS.h"
#ifdef ACT_SIS

#include "common.h"
using namespace std;

//**//*****************************************************//*
int sis_update(VNodeType &status, const VNodeType& deg, NodeType &iN, LinkType &iDeg, double &dt, const double lambda, const double p)
{
    if(iN <= 0 || iDeg <= 0){
        dt = 0;
        return 0;
    }
    double iAll = iN + lambda * iDeg;
    dt = 1. / iAll;
    if(FRAND2() * iAll <= iN){
        //recover
        NodeType i = RAND2() % iN--, tmp;
        tmp = status[i];
        status[i] = status[iN];
        status[iN] = tmp;
    }else{
        // infect
        for(NodeType i; 1;){
            i = RAND2() % iN;
        }
    }
    return 0;
}

int sis(const double p, double &dt)
{
    if(FRAND2() < p * dt){
        // renew
    }else{
        // continue
    }
    return 0;
}
//**//*****************************************************//*
#endif // ACT_SIS

