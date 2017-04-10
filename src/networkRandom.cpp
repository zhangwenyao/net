#include "NetRandom.h"
#include "networkRandom.h"
#ifdef NET_RANDOM

#include "common.h"
using namespace std;

//**//****************************************************//*
int net_random_clear(Network& net)
{
    net.linkSize = 0;
    net.linkRemain = 0;
    net.status = 0;
    return 0;
}

int net_random_init(Network& net)
{
    net_random_clear(net);
    if(net.kMin > net.kMax || net.kMax >= net.nodeSize || (net.kMin == net.kMax && net.nodeSize % 2 == 1 && net.kMin % 2 == 1) || net.net_random.p < 0. || net.net_random.p > 1.) return net.status = -1;
    return 0;
}

//**//****************************************************//*
int net_ER(Network& net)
{
    // 初始化连边信息
    const NodeType nodeSize = net.nodeSize;
    int p = net.net_random.p * RAND2_MAX;
    net.p2p.clear();
    net.p2p.resize(nodeSize);
    for(NodeType i = 0; i < nodeSize; i++)
        for(NodeType j = i + 1; j < nodeSize; j++){
            if(RAND2() <= p){
                net.p2p[i].push_back(j);
                net.p2p[j].push_back(i);
            }
        }
    net.status = 1;
    return 0;
}

//**//****************************************************//*
int net_read_params_ER(istream& is, Network& net)
{
    for(string s; is >> s;){
        if (s == "--net_random.p") {
            is >> net.net_random.p;
            cout << s << '\t'   << net.net_random.p << endl;
            continue;
        }
    }
    return 0;
}

int net_save_params_ER(ostream& os, const Network& net)
{
    if(!os) return -1;
    os << "--net_random.p\t" << net.net_random.p
        << '\n';
    return 0;
}

//**//****************************************************//*
int net_random_ranNode_link(Network& net)  // 随机选点连边，重连时所有边中随机选
{
    // 初始化连边信息
    const NodeType nodeSize = net.nodeSize;
    net.p2p.clear();
    net.p2p.resize(nodeSize);
    net.link.clear();
    net.link.resize(net.linkSize * 2);
    net.remNodeNum.clear();
    net.remNodeNum.resize(nodeSize);
    for(NodeType i = 0, *p = &net.link[0]; i < net.nodeSize; i++) {
        net.p2p[i].reserve(net.nodeDeg[i]);
        net.remNodeNum[i] = i;
        for(NodeType j = net.nodeDeg[i]; j > 0; j--) *p++ = i; // 记录各点剩余度和网络所有连边情况
    }
    net.linkRemain = net.linkSize;
    LinkType linkRemain0 = net.linkRemain;
    // 随机连边
    for(size_t count = 0, iDel = 1; net.linkRemain > 0 && net.remNodeNum.size() > 0;) {
        if(0 == addLink_p2p_ranNode0(net.p2p, net.link, net.nodeDeg, net.remNodeNum, net.linkRemain, 1000)) break;  // 随机选点连边
        if(net.linkRemain < linkRemain0) {
            count = 0;
            iDel = 1;
            linkRemain0 = net.linkRemain;
        } else if(++count >= 1000) {
            count = 0;
            if(++iDel > 5)  break;
        }
        delLink_p2p_ranLink(net.p2p, net.nodeDeg, net.remNodeNum, net.linkRemain, net.link, iDel); // 随机删iDel条边
    }

    if(net.linkRemain > 0) {
        return net.status = -2;
    } else net.status = 1;
    return 0;
}

int net_random_node_prob(Network& net) // 所有点按概率p连边
{
    // 初始化连接矩阵
    const NodeType nodeSize = net.nodeSize;
    net.linkMatr.clear();
    net.linkMatr.assign(nodeSize, VNodeType(nodeSize, 0));

    // 连边
    net.linkSize = 0;
    addLink_linkMatr_proNode(net.linkMatr, net.linkSize, net.net_random.p, net.dirFlag); // 连边
    net.linkRemain = 0;
    linkMatr_2_p2p(net.p2p, net.linkMatr);

    net.status = 1;
    return 0;
}

int net_random_remDeg(Network& net)    // 随机抽取剩余度连边
{
    // 初始化连边信息
    net.p2p.clear();
    net.p2p.resize(net.nodeSize);
    net.link.resize(net.linkSize * 2);
    net.remNodeNum.resize(net.nodeSize);
    for(NodeType i = 0, *p = &net.link[0]; i < net.nodeSize; i++) {
        net.remNodeNum[i] = i;
        for(NodeType j = 0; j < net.nodeDeg[i]; j++) *p++ = i; // 记录各点剩余度和网络所有连边情况
    }
    net.linkRemain = net.linkSize;
    LinkType linkRemain0 = net.linkRemain;
    // 随机连边
    for(LinkType iDel = 1; iDel <= 5 && net.linkRemain > 0 && net.remNodeNum.size() > 0;) {
        for(size_t count = 1000; count > 0; count--){
            delLink_p2p_ranLink(net.p2p, net.nodeDeg, net.remNodeNum, net.linkRemain, net.link, iDel);   // 随机删iDel条边
            if(0 == addLink_p2p_remDeg(net.p2p, net.nodeDeg, net.remNodeNum, net.linkRemain, net.link, 1000)) break; // 随机抽取剩余度连边
        }
        if(net.linkRemain <= 0) break;
        cout << "linkRemain:\t" << net.linkRemain << '\n';
        if(net.linkRemain < linkRemain0){
            linkRemain0 = net.linkRemain;
            iDel = 1;
        } else iDel++;
    }
    cout << "\taddLink end\n";

    if(net.linkRemain > 0) {
        net.linkSize -= net.linkRemain;
        net.status = -2;
    } else net.status = 1;

    return net.status >= 0 ? 0 : -1;
}

//**//****************************************************//*
int net_random_ranNode(Network& net)   // 每次直接随机抽取两个点连边
{
    // 初始化连接矩阵
    init_linkMatrC(net.linkMatrC, net.nodeSize);

    // 连边
    net.linkRemain = net.linkSize = net.net_random.p * (net.nodeSize - 1) * net.nodeSize / 2;
    addLink_linkMatrC_ranNode(net.linkMatrC, net.linkRemain);   // 每次直接随机抽取两个点连边
    linkMatrC_2_p2p(net.p2p, net.linkMatrC);
    for(NodeType i = 0; i < net.nodeSize; i++) net.nodeDeg[i] = net.p2p[i].size();

    // 统计实际度分布
    nodeDeg_2_degArr(net.nodeDeg, net.degArrVal, net.degArrSize, net.degArrSum);
    p2p_2_link(net.link, net.p2p, net.dirFlag);

    net.status = 1;
    return 0;
}

//**//****************************************************//*
#endif  // NET_RANDOM

