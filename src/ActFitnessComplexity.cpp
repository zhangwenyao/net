#include "ActFitnessComplexity.h"
#ifdef ACT_FITNESS_COMPLEXITY

#include "common.h"

//**//*****************************************************//*
int Mcp_2_FC(VDouble& Fc, VDouble& Cp, const VVBool& Mcp)
{
    int flag = 0;
    const double delta = 0.000001;
    const size_t cs = Mcp.size(), ps = Mcp[0].size();
    Fc.assign(cs, 1);
    Cp.assign(ps, 1);
    VDouble iFc = Fc, iCp = Cp;
    double fMean = 1, cMean = 1, ifMean, icMean;
    for(int count = 1; 1; count++){
        iFc.assign(cs, 0);
        ifMean = 0;
        for(size_t c = 0; c < cs; c++){
            for(size_t p = 0; p < ps; p++)
                if(Mcp[c][p]) iFc[c] += Cp[p];
            ifMean += iFc[c];
        }
        ifMean /= cs;
        if(ifMean <= 0){
            flag = -1;
            ERROR("ifMean = ", ifMean);
            break;
        }

        iCp.assign(ps, 0);
        icMean = 0;
        for(size_t p = 0; p < ps; p++){
            for(size_t c = 0; c < cs; c++){
                if(Fc[c] <= 0){
                    iCp[p] = -1;
                    break;
                }
                if(Mcp[c][p]) iCp[p] += 1 / Fc[c];
            }
            if(iCp[p] <= 0) iCp[p] = 0;
            else iCp[p] = 1 / iCp[p];
            icMean += iCp[p];
        }
        icMean /= ps;
        if(icMean <= 0){
            flag = -1;
            ERROR("icMean = ", icMean);
            break;
        }

        for(size_t c = 0; c < cs; c++) Fc[c] = iFc[c] / ifMean;
        for(size_t p = 0; p < ps; p++) Cp[p] = iCp[p] / icMean;

        if((1.0 - delta) * cMean <= icMean && icMean <= (1.0 + delta) * cMean &&
                (1.0 - delta) * fMean <= ifMean && ifMean <= (1.0 + delta) * fMean){
            //std::cout << count << std::endl;
            break;
        }
        fMean = ifMean;
        cMean = icMean;
        if(count % 1000 == 0) INFORM(count, "\tfm ", fMean, "\tcm ", cMean);
    }

    return flag;
}

//**//*****************************************************//*
#endif  // ACT_FITNESS_COMPLEXITY
