#include "StatKendallTau.h"
#ifdef STAT_KENDALLTAU

#include "common.h"
using namespace std;

//**//****************************************************//*
int cal_kendallTau_lkk(double& kendallTau, const VVLinkType& lkk, const LinkType linkSize, const int dir)
{
    const NodeType degSize = lkk.size();
    if(degSize == 0 || lkk[0].empty() || linkSize <= 1){
        kendallTau = 0;
        return 0;
    }
    LinkType ls = 0, ld = 0;
    if(dir){
        const NodeType degSize2 = lkk[0].size();
        for(NodeType ti1 = 0; ti1 < degSize; ti1++){
            for(NodeType tj1 = 0; tj1 < degSize2; tj1++){
                const LinkType n1 = lkk[ti1][tj1];
                if(n1 <= 0) continue;
                for(NodeType ti2 = 0; ti2 < degSize; ti2++){
                    for(NodeType tj2 = 0; tj2 < degSize2; tj2++){
                        const LinkType n2 = lkk[ti2][tj2];
                        if(n2 <= 0) continue;
                        if((ti2 < ti1 && tj2 < tj1) || (ti2 > ti1 && tj2 > tj1)) ls += n1 * n2;
                        if((ti2 < ti1 && tj2 > tj1) || (ti2 > ti1 && tj2 < tj1)) ld += n1 * n2;
                    }
                }
            }
        }
        kendallTau = ((double)ls - ld) / linkSize / (linkSize - 1);
    }else{ // !dir
        for(NodeType ti1 = 0; ti1 < degSize; ti1++){
            for(NodeType tj1 = 0; tj1 <= ti1; tj1++){
                const LinkType n1 = lkk[ti1][tj1];
                if(n1 <= 0) continue;
                for(NodeType ti2 = 0; ti2 < degSize; ti2++){
                    for(NodeType tj2 = 0; tj2 <= ti2; tj2++){
                        LinkType n2 = lkk[ti2][tj2];
                        if(ti2 == ti1 && tj2 == tj1 && n2 > 0) n2--; // self compare
                        if(n2 <= 0) continue;
                        if((ti2 < ti1 && tj2 < tj1) || (ti2 > ti1 && tj2 > tj1)) ls += n1 * n2;
                        if((ti2 < ti1 && tj2 > tj1) || (ti2 > ti1 && tj2 < tj1)) ld += n1 * n2;
                        if((ti2 < tj1 && tj2 < ti1) || (ti2 > tj1 && tj2 > ti1)) ls += n1 * n2;
                        if((ti2 < tj1 && tj2 > ti1) || (ti2 > tj1 && tj2 < ti1)) ld += n1 * n2;
                    }
                }
            }
        }
        kendallTau = ((double)ls - ld) / linkSize / (linkSize - 1) / 2;
    }
    return 0;
}

int cal_kendallTau_lkkSum(double& kendallTau, const VVLinkType& lkk, const VVLinkType& lkkSum, const int dir)
{
    const NodeType degSize = lkkSum.size(), degEnd = degSize - 1;
    const LinkType linkSize = lkkSum.back().back();
    if(degSize == 0 || lkkSum[0].empty() || linkSize <= 1){
        kendallTau = 0;
        return 0;
    }
    LinkType ls = 0, ld = 0;
    if(dir){
        const NodeType degSize2 = lkkSum[0].size(), degEnd2 = degSize2 - 1;
        for(NodeType ti1 = 0; ti1 < degSize; ti1++){
            for(NodeType tj1 = 0; tj1 < degSize2; tj1++){
                const LinkType n1 = lkk[ti1][tj1];
                if(n1 <= 0) continue;
                // ti2 < ti1 && tj2 < tj1
                if(ti1 > 0 && tj1 > 0) ls += n1 * lkkSum[ti1 - 1][tj1 - 1];
                // ti2 > ti1 && tj2 > tj1
                if(ti1 < degEnd && tj1 < degEnd2) ls += n1 * (linkSize - lkkSum[ti1][degEnd] + lkkSum[ti1][tj1] - lkkSum[degEnd2][tj1]);
                // ti2 < ti1 && tj2 > tj1
                if(ti1 > 0 && tj1 < degEnd2) ld += n1 * (lkkSum[ti1 - 1][degEnd2] - lkkSum[ti1 - 1][tj1]);
                // ti2 > ti1 && tj2 < tj1
                if(ti1 < degEnd && tj1 > 0) ld += n1 * (lkkSum[degEnd][tj1 - 1] - lkkSum[ti1][tj1 - 1]);
            }
        }
        kendallTau = ((double)ls - ld) / linkSize / (linkSize - 1);
    }else{  // !dir
        for(NodeType ti1 = 0; ti1 < degSize; ti1++){
            for(NodeType tj1 = 0; tj1 <= ti1; tj1++){
                const LinkType n1 = lkk[ti1][tj1];
                if(n1 <= 0) continue;
                // ti1->tj1 : ti2->tj2
                if(tj1 > 0) ls += n1 * lkkSum[ti1 - 1][tj1 - 1]; // ti2 < ti1 && tj2 < tj1
                if(ti1 < degEnd) ls += n1 * (linkSize - lkkSum[ti1][ti1] + lkkSum[ti1][tj1] - lkkSum[degEnd][tj1]); // ti2 > ti1 && tj2 > tj1
                if(ti1 > tj1 + 1) ld += n1 * (lkkSum[ti1 - 1][ti1 - 1] - lkkSum[ti1 - 1][tj1]); // ti2 < ti1 && tj2 > tj1    <==>    tj1 < tj2 <= ti2 < ti1
                if(ti1 < degEnd && tj1 > 0) ld += n1 * (lkkSum[degEnd][tj1 - 1] - lkkSum[ti1][tj1 - 1]); // ti2 > ti1 && tj2 < tj1    <==>    tj2 < tj1 <= ti1 < ti2
                // ti1->tj1 : tj2->ti2
                if(tj1 > 0) ls += n1 * lkkSum[tj1 - 1][tj1 - 1]; // tj2 < ti1 && ti2 < tj1    <==>    tj2 <= ti2 < tj1 <= ti1
                if(ti1 < degEnd) ls += n1 * (linkSize - lkkSum[degEnd][ti1]); // tj2 > ti1 && ti2 > tj1    <==>    ti2 >= tj2 > ti1 >= tj1
                if(ti1 > 0 && tj1 < degEnd) ld += n1 * (lkkSum[degEnd][ti1 - 1] - lkkSum[tj1][tj1 < ti1 - 1 ? tj1 : ti1 - 1]); // tj2 < ti1 && ti2 > tj1
                //ld += 0; // tj2 > ti1 && ti2 < tj1    <==>    ti2 >= tj2 > ti1 >= tj1 > ti2    <==>    NULL
                if(tj1 != ti1) ld -= n1; // self compare
            }
        }
        kendallTau = ((double)ls - ld) / linkSize / (linkSize - 1) / 2;
    }
    return 0;
}

int cal_kendallTau_p2p(double kendallTau, const VVNodeType& p2p, const VNodeType& nodeDegOut, const VNodeType& nodeDegIn, const LinkType linkSize, const int dir)
{
    if(p2p.empty() || nodeDegOut.empty()){
        kendallTau = 0;
        return 0;
    }
    LinkType ls = 0, ld = 0;
    if(!dir){
        for(NodeType i = 0, ni; i < p2p.size(); i++){
            ni = nodeDegOut[i];
            for(NodeType pj = 0, j, nj; pj < p2p[i].size(); pj++){
                j = p2p[i][pj];
                if(i <= j) continue;
                nj = nodeDegIn[j];
                for(NodeType i2 = 0, ni2; i2 < p2p.size(); i2++){
                    ni2 = nodeDegOut[i2];
                    for(NodeType pj2 = 0, j2, nj2; pj2 < p2p[i2].size(); pj2++){
                        j2 = p2p[i2][pj2];
                        if(i2 <= j2 || (i2 == i && j2 == j)) continue;
                        nj2 = nodeDegIn[j2];
                        if((ni < ni2 && nj < nj2) || (ni > ni2 && nj > nj2)) ls++;
                        if((ni < ni2 && nj > nj2) || (ni > ni2 && nj < nj2)) ld++;
                        if((nj < ni2 && ni < nj2) || (nj > ni2 && ni > nj2)) ls++;
                        if((nj < ni2 && ni > nj2) || (nj > ni2 && ni < nj2)) ld++;
                    }
                }
            }
        }
        kendallTau = ((double)ls - ld) / linkSize / (linkSize - 1) / 2;
    }else{ // dir
        for(NodeType i = 0, ni; i < p2p.size(); i++){
            ni = nodeDegOut[i];
            for(NodeType pj = 0, j, nj; pj < p2p[i].size(); pj++){
                j = p2p[i][pj];
                nj = nodeDegIn[j];
                for(NodeType i2 = 0, ni2; i2 < p2p.size(); i2++){
                    ni2 = nodeDegOut[i2];
                    for(NodeType pj2 = 0, j2, nj2; pj2 < p2p[i2].size(); pj2++){
                        j2 = p2p[i2][pj2];
                        if(i2 == i && j2 == j) continue;
                        nj2 = nodeDegIn[j2];
                        if((ni < ni2 && nj < nj2) || (ni > ni2 && nj > nj2)) ls++;
                        if((ni < ni2 && nj > nj2) || (ni > ni2 && nj < nj2)) ld++;
                    }
                }
            }
        }
        kendallTau = ((double)ls - ld) / linkSize / (linkSize - 1);
    }
    return 0;
}

//**//****************************************************//*
#endif  // STAT_KENDALLTAU

