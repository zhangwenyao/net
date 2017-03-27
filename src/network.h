#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include "net.h"

//**//*****************************************************************//*
/*
    net_run     argv        options
    参数        cal_params  dirFlag !dirFlag        是否有向
                            weightFlag !weightFlag  是否带权重
    随机数种子  init_seee0                  仅首次初始化
                init_seed                   重新初始化种子
    度分布      cal_deg     read_deg        读取度序列
                            read_degArr     读取度分布
                            read_lkk        读取连边分布
                            power           度序列幂律分布
                            poisson         度序列泊松分布
    连边        cal_p2p     p2p             利用已有数组转化
                            read_p2p        读取连边链接表
                            read_linkMatr   读取连边矩阵
                            read_link       读取连边
                            Max             最大度关联网络
                            Min             最小度关联网络
                            MinLkkP2p       min lkk -> p2p
                            MinLkkP2pFix    min lkk -> p2p fix
                            ER              ER随机网络
                            random          随机网络
                            BA              BA网络
                            Grid            网格网络
                            Spearman        sp系数给定的网络
    修正        fix_p2p                     修正自环、重边、缺边
                fix_p2p_nodeDeg0            按p2p度排序重新映射节点，度为0在最后（剔除）
    连边矩阵    lkk_max                     lkk最强pearson同配
                lkk_min                     lkk最强pearson异配
                lkk_maxN    countN          lkk最强pearson同配
                lkk_minN    countN          lkk最强pearson异配
                MinLkk                      最小度关联网络
                MinLkkFix                   最小度关联网络
    统计        stat
    推荐        recommend   mass            扩散
                            heat            热传导
    保存        save
    清理        clear
    结束        exit

    ranLink_ranNode     // 直接随机选点连边；用到linkMatr,p2p
    ranLink_proNode     // 所有点按概率连边；用到linkMatr,p2p
    ranLink_remDeg      // 随机选取剩余度连边；用到p2p,link
    ranLink_remDegGauss // 随机选剩余度按点的度之差的相应高斯概率连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranLink_remDegExp   // 随机选剩余度按点的度之差的相应指数概率连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranLink_remDegExp0  // 随机选剩余度按点的度之差的相应指数概率连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranNode_link        // 随机选点连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranNode_deg         // 随机按度选点连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranNode_node        // 随机选点连边、重连时随机选点；用到p2p,remNodeNum
    ranNode_nodeM       // 随机选点连边、重连时随机选点；用到linkMatr,p2p,remNodeNum
    ranNode_Gauss       // 随机选点按点的度之差的相应高斯概率连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranNode_node        // 随机选点连边、重连时随机选点再选边；用到p2p,remNodeNum
*//**/

//**//*****************************************************************//*
class Network
{
    public:
        // params
        std::string argv;       // 参数
        std::string saveName;   // 保存文件名前缀
        std::string readName;   // 读取文件名前缀
        int         status;     // 网络状态 0：空，1：正常，-1：有错，-2：未连完
        int         seed;       // 随机数种子值
        int         dirFlag;       // 网络是否有向，0无向，非0有向
        int         weightFlag;     // 网络是否有权，0无权，非0有权
        int         distFlag;   //  网络距离是否01，0:01，非0:实数
        NodeType    nodeSize;   // 节点数
        NodeType    kMin, kMax; // 度范围,最小度,最大度
        LinkType    linkSize;   // 连边数
        std::vector<int>    paramsInt;  // 整型参数
        std::vector<double> paramsDouble;   // 实数参数
        char        priChar, priChar2;    // 保存文件时的分隔符

#ifdef NET_DEGREE
#ifdef DEG_POISSON
        double      Poi_p;
#endif
#ifdef DEG_POWER
        double      Pow_gamma;
#endif
#endif  // NET_DEGREE

#ifdef NET_A
        int         A_a;
#endif

#ifdef NET_RANDOM
        double      ER_p;
#endif

#ifdef NET_BA
        int         BA_M, BA_M0;
#endif

#ifdef NET_GRID
        int         Grid_NX, Grid_NY;
#endif

        // deg
        VDouble     degArrProb; // [degSize]    度分布概率 p(k)
        VNodeType   degArrVal;  // [degSize]    度分布序列 k
        VNodeType   degArrSize; // [degSize]    各度节点数 n(k)
        MNodeType   degArrNo;   // [kMax+1]     度k在degArrVal中的位置
        VNodeType   degArrSum;  // [degSize+1]  度分布累计序列
        VNodeType   nodeDeg;    // [nodeSize]   各节点度
        VNodeType   remNodeNum; // [remNodeSize]    未全连边的节点编号
        VNodeType   nodesName, nodesName2;    // [nodeSize]   节点的映射关系 net2.nodesName[i] -> i   i -> net2.nodesName2[i]

        VNodeType   nodeDegIn, degArrValIn, degArrSizeIn, degArrSumIn;
        VNodeType   nodeDegOut, degArrValOut, degArrSizeOut, degArrSumOut;
        MNodeType   degArrNoIn, degArrNoOut;
        double      degMean, degMeanOut, degMeanIn;

        // link
        VNodeType   link, p2pSize;      // [nodeSize*2] 网络连边
        VVNodeType  p2p, p2pIn; // [nodeSize]   各点连边链表p2p:出度,p2pIn:入度
        VVDistType  linkMatr;   // [nodeSize]   网络连边距离矩阵
        VVChar      linkMatrC;  // [nodeSize]   网络连边01矩阵
        LinkType    linkRemain;
        VLinkType   linkSum;    // 各度累计线头数

        // weightFlag
        VVWeightType    vvweight, vvweightIn, weightMatr;   // 连边权重
        unsigned    weight_m, weight_n; // 数据文件中连边权重位置 (m+1) / n
        VWeightType nodeWeight, nodeWeightOut, nodeWeightIn;    // 各节点总连边权重
        VWeightSumType  degArrWeight, degArrWeightOut, degArrWeightIn;   // 同度节点连边总权重
        WeightSumType  netWeight, netWeightOut, netWeightIn;
        double degWeightMean, degWeightMeanOut, degWeightMeanIn;

        // lkk
        VVLinkType  lkk, lkkOutIn;  // 不同度之间连边数目矩阵
        VVLinkType  lkkSum, lkkSumOutIn;    // 同度点连向不同度的累计边数
        VVDouble    lkkProb;    // [degSize]    连边的联合分布概率

        VDouble     nodeNeiAveDeg, nodeNeiAveDegIn, nodeNeiAveDegOut;  // [nodeSize]   各点的邻居平均度
        VDouble     neiAveDeg, neiAveDegInIn, neiAveDegInOut, neiAveDegOutIn, neiAveDegOutOut;  // [degSize]    各度的邻居平均度
        VDouble     nodeNeiAveNo, nodeNeiAveNoInIn, nodeNeiAveNoInOut, nodeNeiAveNoOutIn, nodeNeiAveNoOutOut;   // [nodeSize]   各点的邻居编号平均值
        VDouble     neiAveNo, neiAveNoInIn, neiAveNoInOut, neiAveNoOutIn, neiAveNoOutOut;   // [degSize]    各度的邻居编号平均值

#ifdef STAT_PEARSON
        // pearson
        double      pearson, pearsonInIn, pearsonInOut, pearsonOutIn, pearsonOutOut;
        double      pearsonNo, pearsonNoInIn, pearsonNoInOut, pearsonNoOutIn, pearsonNoOutOut;
        double      ps_rho, ps_rhoInIn, ps_rhoInOut, ps_rhoOutIn, ps_rhoOutOut;
#endif

        VDouble     deg2ArrVal, deg2ArrValIn, deg2ArrValOut; // [degSize]    归一化后的度分布序列 k
        VDouble     nodeNeiAveDeg2, nodeNeiAveDeg2In, nodeNeiAveDeg2Out;// [nodeSize]
        VDouble     neiAveDeg2, neiAveDeg2InIn, neiAveDeg2InOut, neiAveDeg2OutIn, neiAveDeg2OutOut; // [degSize]
        VDouble     deg2ArrWeight, deg2ArrWeightOut, deg2ArrWeightIn;   // 同度节点连边总权重
        double      deg2WeightMean, deg2WeightMeanOut, deg2WeightMeanIn;

#ifdef STAT_SPEARMAN
        // spearman
        double      spearman, spearmanInIn, spearmanInOut, spearmanOutIn, spearmanOutOut, sp_rho, sp_rhoInIn, sp_rhoInOut, sp_rhoOutIn, sp_rhoOutOut;
#ifdef MODEL_GAUSS
        // gauss模型
        double      sp_r0;
        VDouble     sp_GaussS2;     // [nodeSize]   模型的联合概率的方差
#endif  // MODEL_GAUSS
#endif  // STAT_SPEARMAN

#ifdef STAT_KENDALLTAU
        double      kendallTau, kendallTauOutIn;
#endif  // STAT_KENDALLTAU

#ifdef STAT_BETWEENNESS
        double      btNode, btEdge;   // 平均介数
        VDouble     betwNode;         // 各点介数
        VVDouble    betwEdge;     // 各边介数
        VVDistType  minDistMatr;  // 最短距离
        VDouble     minDistMean;  // 平均最短距离
#endif

#ifdef STAT_MODULARITY
        double      moduCoef;   // 分组系数
        VNodeType   moduVal;    // 各节点分组的序号
        VNodeType   moduStk;    // 按分组序号排列的节点编号
        VNodeType   moduNum;    // 节点在moduStk中的位置
        VRNodeType  moduRange;  // 各分组的范围
        VVLinkType  moduLKK;    // 不同组之间连边数目
#endif

#ifdef STAT_CLUSTER
        double      cluster_c;
        VDouble     cluster;    // clustering coefficient
#endif

#ifdef STAT_SPREAD
        NodeType SOURCE_HEAD, SOURCE_NULL;
        std::vector<NodeType> source, nei, num, stk, time;
        NodeType spreadSize;
        NodeType head, nei1, nei0;
        LinkType neiCountSize;

        double prob;
        std::vector<int> prob_rand;

        NodeType dataSize;
        std::vector<NodeType> data_node, data_time;
#endif

        Network     *net2;

        int     runStatus;
        Network();
        ~Network();
        Network& run(const std::string& argv);
        Network& init_seed(void);
        Network& init_seed(const int seed);
        Network& cal_deg(const std::string& argv);
        Network& cal_p2p(const std::string& argv);
        Network& stat(void);
        Network& save0(void);
        Network& save(const char *name = NULL);
        Network& clear_net(void);
};

int net_read_params_0(std::istream& is, Network& net);
int net_save_params_0(std::ostream& os, const Network& net);
int net_save_params_0(const Network& net, const char *namei = NULL);
//**//************************************************************//*
int net_clear_deg(Network& net);
int net_clear_p2p(Network& net);
int net_clear_lkk(Network& net);

//**//************************************************************//*
int net_save_deg(const Network& net, const char *name = NULL);
int net_save_p2p(const Network& net, const char *name = NULL);

int net_read_nodeDeg_0(Network& net, const char *name = NULL);
int net_read_degArr_0(Network& net, const char *name = NULL);
int net_read_lkk_0(Network& net, const char *name = NULL);
int net_read_link_0(Network& net, const char *name = NULL);
int net_read_link(Network& net, const char *name = NULL);
int net_read_weight_link(Network& net, const char *name = NULL);
int net_read_link_weight_0(Network& net, const char *name = NULL);
int net_read_p2p_0(Network& net, const char *name = NULL);
int net_read_linkMatr_0(Network& net, const char *name = NULL);
int net_read_weightMatr_0(Network& net, const char *name = NULL);

//**//************************************************************//*
int net_lkk_2_degArr(Network& net);
int net_p2p_2_degArr(Network& net);
int net_fix_p2p_nodeDeg0(Network& net);

//**//************************************************************//*
#endif // NETWORK_H

