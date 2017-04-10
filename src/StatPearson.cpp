#include "StatPearson.h"
#ifdef STAT_PEARSON

#include "common.h"
using namespace std;

//**//****************************************************//*
int cal_nodeNeiAveDeg(VDouble& nodeNeiAveDeg, const VVNodeType& p2p)
{
    if(p2p.empty() || !nodeNeiAveDeg.empty()){
        ERROR();
        return -1;
    }
    const NodeType nodeSize = p2p.size();
    nodeNeiAveDeg.assign(nodeSize, 0);
    for(NodeType i = 0; i < nodeSize; i++) {
        if(p2p[i].size() <= 0) continue;
        LinkType l = 0;
        for(VNodeTypeCItr n = p2p[i].begin(); n != p2p[i].end(); n++) l += p2p[*n].size();
        nodeNeiAveDeg[i] = (double)l / p2p[i].size();
    }
    return 0;
}

int cal_nodeNeiAveDeg_nodeDeg(VDouble& nodeNeiAveDeg, const VVNodeType& p2p, const VNodeType& nodeDegIn)
{
    if(p2p.empty() || !nodeNeiAveDeg.empty()){
        ERROR();
        return -1;
    }
    const NodeType nodeSize = p2p.size();
    nodeNeiAveDeg.assign(nodeSize, 0);
    for(NodeType i = 0; i < nodeSize; i++) {
        if(p2p[i].size() <= 0) continue;
        LinkType l = 0;
        for(VNodeTypeCItr j = p2p[i].begin(); j != p2p[i].end(); j++) l += nodeDegIn[*j];
        nodeNeiAveDeg[i] = (double)l / p2p[i].size();
    }
    return 0;
}

int cal_nodeNeiAveDeg_weight(VDouble& nodeNeiAveDeg, const VVNodeType& p2p, const VNodeType& nodeDegIn, const VVWeightType& vvweight, const VWeightType& nodeWeightOut, const int weightFlag)
{
    if(!weightFlag) return cal_nodeNeiAveDeg_nodeDeg(nodeNeiAveDeg, p2p, nodeDegIn);
    if(p2p.empty() || !nodeNeiAveDeg.empty() || vvweight.size() != p2p.size()){
        ERROR();
        return -1;
    }
    const NodeType nodeSize = p2p.size();
    nodeNeiAveDeg.assign(nodeSize, 0);
    for(NodeType i = 0; i < nodeSize; i++) {
        if(p2p[i].size() <= 0) continue;
        double l = 0;
        for(NodeType j = 0; j < p2p[i].size(); j++) l += (double)vvweight[i][j] * nodeDegIn[p2p[i][j]];
        nodeNeiAveDeg[i] = l / nodeWeightOut[i];
    }
    return 0;
}

int cal_nodeNeiAveDeg_AllAll_weight(VDouble& nodeNeiAveDeg, const VVNodeType& p2p, const VNodeType& nodeDeg, const VVWeightType& vvweight, const VWeightType& nodeWeight, const int weightFlag)
{
    if(!weightFlag) return cal_nodeNeiAveDeg_nodeDeg(nodeNeiAveDeg, p2p, nodeDeg);
    if(p2p.empty() || !nodeNeiAveDeg.empty() || vvweight.size() != p2p.size()){
        ERROR();
        return -1;
    }
    const NodeType nodeSize = p2p.size();
    nodeNeiAveDeg.assign(nodeSize, 0);
    for(NodeType i = 0; i < nodeSize; i++) {
        if(p2p[i].size() <= 0) continue;
        for(NodeType j = 0; j < p2p[i].size(); j++){
            nodeNeiAveDeg[i] += (double)vvweight[i][j] * nodeDeg[p2p[i][j]];
            nodeNeiAveDeg[p2p[i][j]] += (double)vvweight[i][j] * nodeDeg[i];
        }
    }
    for(NodeType i = 0; i < nodeSize; i++)
        if(nodeDeg[i] > 0) nodeNeiAveDeg[i] /= nodeWeight[i];
    return 0;
}

int cal_neiAveDeg(VDouble& neiAveDeg, const VDouble& nodeNeiAveDeg, const VNodeType& nodeDeg, const VNodeType& degArrSize, MNodeType& degArrNo, const VNodeType& degArrVal)
{
    if(nodeDeg.empty() || !neiAveDeg.empty() || degArrSize.empty()){
        ERROR();
        return -1;
    }
    const NodeType nodeSize = nodeDeg.size(), degSize = degArrSize.size();
    neiAveDeg.assign(degSize, 0);
    for(NodeType i = 0; i < nodeSize; i++)
        if(nodeDeg[i] > 0) neiAveDeg[degArrNo[nodeDeg[i]]] += nodeNeiAveDeg[i];
    for(NodeType i = 0; i < degSize; i++)
        if(degArrSize[i] > 0 && degArrVal[i] > 0) neiAveDeg[i] /= degArrSize[i];
    return 0;
}

int cal_neiAveDeg_weight(VDouble& neiAveDeg, const VDouble& nodeNeiAveDeg, const VNodeType& nodeDeg, const VNodeType& degArrSize, MNodeType& degArrNo, const VNodeType& degArrVal, const VWeightSumType& degArrWeight, const VWeightType& nodeWeight, const int weightFlag)
{
    if(!weightFlag) return cal_neiAveDeg(neiAveDeg, nodeNeiAveDeg, nodeDeg, degArrSize, degArrNo, degArrVal);
    if(nodeDeg.empty() || !neiAveDeg.empty() || degArrSize.empty()){
        ERROR();
        return -1;
    }
    const NodeType nodeSize = nodeDeg.size(), degSize = degArrSize.size();
    neiAveDeg.assign(degSize, 0);
    for(NodeType i = 0; i < nodeSize; i++)
        if(nodeDeg[i] > 0) neiAveDeg[degArrNo[nodeDeg[i]]] += nodeNeiAveDeg[i] * nodeWeight[i];
    for(NodeType i = 0; i < degSize; i++)
        if(degArrSize[i] > 0 && degArrVal[i] > 0) neiAveDeg[i] /= degArrWeight[i];
    return 0;
}

int cal_nodeNeiAveNo(VDouble& nodeNeiAveNo, const VVNodeType& p2p)
{
    if(p2p.empty() || !nodeNeiAveNo.empty()){
        ERROR();
        return -1;
    }
    const NodeType nodeSize = p2p.size();
    nodeNeiAveNo.assign(nodeSize, 0);
    for(NodeType i = 0; i < nodeSize; i++) {
        if(p2p[i].size() <= 0) continue;
        LinkType l = 0;
        for(VNodeTypeCItr n = p2p[i].begin(); n != p2p[i].end(); n++) l += *n;
        nodeNeiAveNo[i] = (double)l / p2p[i].size();
    }
    return 0;
}

int cal_pearson_lkk(double& pearson, const VVLinkType& lkk, const VNodeType& degArrVal, const LinkType& linkSize)
{
    double sx = 0., sxx = 0., sxy = 0.;
    const NodeType degSize = degArrVal.size();
    for(NodeType i = 0, ki; i < degSize; i++){
        ki = degArrVal[i];
        const double ki2 = (double)ki * ki;
        for(NodeType j = 0; j <= i; j++){
            const double l = lkk[i][j], kj = degArrVal[j];
            if(l <= 0) continue;
            sx += l * (ki + kj);
            sxx += l * (ki2 + kj * kj);
            sxy += 2 * l * ki * kj;
        }
    }
    const LinkType n = linkSize * 2;
    if(n * sxx - sx * sx == 0) pearson = 0;
    else pearson = (n * sxy - sx * sx) / (n * sxx - sx * sx);
    return 0;
}

int cal_pearson(double& pearson, const VVNodeType& p2p, const LinkType linkSize)
{
    const LinkType n = linkSize * 2;
    double sx = 0., sxx = 0., sxy = 0.;
    for(NodeType i = 0, k; i < p2p.size(); i++) {
        if((k = p2p[i].size()) <= 0) continue;
        const double k2 = (double)k * k;
        for(NodeType j = 0; j < k; j++) {
            sx += k;
            sxx += k2;
            sxy += (double)k * p2p[p2p[i][j]].size();
        }
    }
    if(n * sxx - sx * sx == 0) pearson = 0;
    else pearson = (n * sxy - sx * sx) / (n * sxx - sx * sx);
    return 0;
}

int cal_pearson_dir(double& pearson, double& rho, const VVNodeType& p2p, const LinkType linkSize, const VNodeType& nodeDegOut, const VNodeType& nodeDegIn)
{
    double sx = 0., sxx = 0., sy = 0., syy = 0., sxy = 0.;
    for(NodeType i = 0; i < p2p.size(); i++) {
        if(p2p[i].empty()) continue;
        const NodeType ki = nodeDegOut[i];
        const double ki2 = (double)ki * ki;
        for(VNodeTypeCItr j = p2p[i].begin(); j != p2p[i].end(); j++) {
            const double kj = nodeDegIn[*j], kj2 = kj * kj;
            sx += ki;
            sxx += ki2;
            sy += kj;
            syy += kj2;
            sxy += (double)ki * kj;
        }
    }
    if(linkSize * sxx - sx * sx == 0){
        pearson = rho = 0;
    }else{
        if(linkSize * syy - sy * sy == 0) pearson = 0;
        else pearson = (linkSize * sxy - sx * sy) / sqrt((linkSize * sxx - sx * sx) * (linkSize * syy - sy * sy));
        rho = (linkSize * sxy - sx * sy) / (linkSize * sxx - sx * sx);
    }
    return 0;
}

int cal_pearson_dir_weight(double& pearson, double& rho, const VVNodeType& p2p, const VVWeightType& vvweight, const WeightSumType netWeight, const VNodeType& nodeDegOut, const VNodeType& nodeDegIn, const int weightFlag)
{
    if(!weightFlag) return cal_pearson_dir(pearson, rho, p2p, netWeight, nodeDegOut, nodeDegIn);
    double sx = 0., sxx = 0., sy = 0., syy = 0., sxy = 0.;
    for(NodeType i = 0; i < p2p.size(); i++) {
        if(p2p[i].empty()) continue;
        const double ki = nodeDegOut[i], ki2 = ki * ki;
        for(NodeType j = 0; j < p2p[i].size(); j++) {
            const double kj = nodeDegIn[p2p[i][j]], kj2 = kj * kj, w = vvweight[i][j];
            sx += w * ki;
            sxx += w * ki2;
            sy += w * kj;
            syy += w * kj2;
            sxy += w * ki * kj;
        }
    }
    if(netWeight * sxx - sx * sx == 0){
        pearson = rho = 0;
    }else{
        if(netWeight * syy - sy * sy == 0) pearson = 0;
        else pearson = (netWeight * sxy - sx * sy) / sqrt((netWeight * sxx - sx * sx) * (netWeight * syy - sy * sy));
        rho = (netWeight * sxy - sx * sy) / (netWeight * sxx - sx * sx);
    }
    return 0;
}

int cal_pearson_link(double& pearson, const VNodeType& link, const VNodeType& nodeDeg)
{
    const LinkType n = link.size();
    double sx = 0., sxx = 0., sxy = 0.;
    for(LinkType i = 0; i < n; i += 2) {
        double x = nodeDeg[link[i]], y = nodeDeg[link[i+1]];
        sx += x + y;
        sxx += x * x + y * y;
        sxy += x * y;
    }
    if(n * sxx - sx * sx == 0) pearson = 0;
    else pearson = (n * 2. * sxy - sx * sx) / (n * sxx - sx * sx);
    return 0;
}

int cal_No(double& No, const VVNodeType& p2p, const LinkType linkSize)
{
    const LinkType n = linkSize * 2;
    const NodeType nodeSize = p2p.size();
    double sx = 0., sxx = 0., sxy = 0.;
    for(NodeType i = 0, k; i < nodeSize; i++) {
        if((k = p2p[i].size()) <= 0) continue;
        double i2 = (double)i * i;
        for(NodeType j = 0; j < k; j++) {
            sx += i;
            sxx += i2;
            sxy += (double)i * p2p[i][j];
        }
    }
    if(n * sxx - sx * sx == 0) No = 0;
    else No = (n * sxy - sx * sx) / (n * sxx - sx * sx);
    return 0;
}

int cal_No_link(double& No, const VNodeType& link)
{
    const LinkType n = link.size();
    double sx = 0., sxx = 0., sxy = 0.;
    for(LinkType i = 0; i < n; i += 2) {
        double x = link[i], y = link[i+1];
        sx += x + y;
        sxx += x * x + y * y;
        sxy += x * y;
    }
    if(n * sxx - sx * sx == 0) No = 0;
    else No = (n * sxy - sx * sx) / (n * sxx - sx * sx);
    return 0;
}

//**//****************************************************//*
#endif  // STAT_PEARSON
