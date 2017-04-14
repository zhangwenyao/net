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
    传播        SIS
    输出        print
    保存        save
                save0
    清理        clear
    结束        exit
 */ /**/

//**//*****************************************************************//*
class Network {
 public:
  // variables
  std::string argv, argv0;  // 参数
  std::string saveName;     // 保存文件名前缀
  std::string readName;     // 读取文件名前缀
  int status;  // 网络状态 0：空，1：正常，-1：有错，-2：未连完
  int seed;    // 随机数种子值
  int dirFlag;                 // 网络是否有向，0无向，非0有向
  int weightFlag;              // 网络是否有权，0无权，非0有权
  int distFlag;                //  网络距离是否01，0:01，非0:实数
  NodeType nodeSize;           // 节点数
  NodeType kMin, kMax;         // 度范围,最小度,最大度
  LinkType linkSize;           // 连边数
  std::vector<int> paramsInt;  // 整型参数
  std::vector<double> paramsDouble;  // 实数参数
  char priChar, priChar2;            // 保存文件时的分隔符
  int runStatus;

  // deg
  VDouble degArrProb;    // [degSize]    度分布概率 p(k)
  VNodeType degArrVal;   // [degSize]    度分布序列 k
  VNodeType degArrSize;  // [degSize]    各度节点数 n(k)
  MNodeType degArrNo;    // [kMax+1]     度k在degArrVal中的位置
  VNodeType degArrSum;   // [degSize+1]  度分布累计序列
  VNodeType nodeDeg;     // [nodeSize]   各节点度
  VNodeType remNodeNum;  // [remNodeSize]    未全连边的节点编号
  VNodeType nodesName, nodesName2;  // [nodeSize]   节点的映射关系
                                    // net2.nodesName[i] -> i   i ->
                                    // net2.nodesName2[i]

  VNodeType nodeDegIn, degArrValIn, degArrSizeIn, degArrSumIn;
  VNodeType nodeDegOut, degArrValOut, degArrSizeOut, degArrSumOut;
  MNodeType degArrNoIn, degArrNoOut;
  double degMean, degMeanOut, degMeanIn;

  // link
  VNodeType link, p2pSize;  // [nodeSize*2] 网络连边
  VVNodeType p2p, p2pIn;  // [nodeSize]   各点连边链表p2p:出度,p2pIn:入度
  VVDistType linkMatr;  // [nodeSize]   网络连边距离矩阵
  VVChar linkMatrC;     // [nodeSize]   网络连边01矩阵
  LinkType linkRemain;
  VLinkType linkSum;  // 各度累计线头数

  // weightFlag
  VVWeightType vvweight, vvweightIn, weightMatr;  // 连边权重
  unsigned weight_m, weight_n;  // 数据文件中连边权重位置 (m+1) / n
  VWeightType nodeWeight, nodeWeightOut, nodeWeightIn;  // 各节点总连边权重
  VWeightSumType degArrWeight, degArrWeightOut,
      degArrWeightIn;  // 同度节点连边总权重
  WeightSumType netWeight, netWeightOut, netWeightIn;
  double degWeightMean, degWeightMeanOut, degWeightMeanIn;

  // lkk
  VVLinkType lkk, lkkOutIn;        // 不同度之间连边数目矩阵
  VVLinkType lkkSum, lkkSumOutIn;  // 同度点连向不同度的累计边数
  VVDouble lkkProb;                // [degSize]    连边的联合分布概率

  VDouble nodeNeiAveDeg, nodeNeiAveDegIn,
      nodeNeiAveDegOut;  // [nodeSize]   各点的邻居平均度
  VDouble neiAveDeg, neiAveDegInIn, neiAveDegInOut, neiAveDegOutIn,
      neiAveDegOutOut;  // [degSize]    各度的邻居平均度
  VDouble nodeNeiAveNo, nodeNeiAveNoInIn, nodeNeiAveNoInOut, nodeNeiAveNoOutIn,
      nodeNeiAveNoOutOut;  // [nodeSize]   各点的邻居编号平均值
  VDouble neiAveNo, neiAveNoInIn, neiAveNoInOut, neiAveNoOutIn,
      neiAveNoOutOut;  // [degSize]    各度的邻居编号平均值

  VDouble deg2ArrVal, deg2ArrValIn,
      deg2ArrValOut;  // [degSize]    归一化后的度分布序列 k
  VDouble nodeNeiAveDeg2, nodeNeiAveDeg2In, nodeNeiAveDeg2Out;  // [nodeSize]
  VDouble neiAveDeg2, neiAveDeg2InIn, neiAveDeg2InOut, neiAveDeg2OutIn,
      neiAveDeg2OutOut;  // [degSize]
  VDouble deg2ArrWeight, deg2ArrWeightOut,
      deg2ArrWeightIn;  // 同度节点连边总权重
  double deg2WeightMean, deg2WeightMeanOut, deg2WeightMeanIn;

#ifdef NET_BA
  struct ParamsBA {
    int M, M0;
  } params_BA;
#endif

#ifdef NET_GRID
  struct ParamsGrid {
    int NX, NY;
  } params_grid;
#endif

#ifdef STAT_PEARSON
  struct ParamsPearson {
    // pearson
    double pearson, InIn, InOut, OutIn, OutOut;
    double No, NoInIn, NoInOut, NoOutIn, NoOutOut;
    double rho, rhoInIn, rhoInOut, rhoOutIn, rhoOutOut;
  } params_pearson;
#endif

#ifdef STAT_SPEARMAN
  struct ParamsSpearman {
    // spearman
    double spearman, InIn, InOut, OutIn, OutOut, rho, rhoInIn, rhoInOut,
        rhoOutIn, rhoOutOut;
#ifdef MODEL_GAUSS
    // gauss模型
    double r0;
    VDouble GaussS2;  // [nodeSize]   模型的联合概率的方差
#endif                // MODEL_GAUSS
  } params_spearman;
#endif

#ifdef STAT_KENDALL
  struct ParamsKendall {
    double tau, OutIn;
  } params_kendall;
#endif

#ifdef STAT_BETWEENNESS
  struct ParamsBetweenness {
    double meanNode, meanEdge;  // 平均介数
    VDouble betwNode;           // 各点介数
    VVDouble betwEdge;          // 各边介数
    VVDistType minDistMatr;     // 最短距离
    VDouble minDistMean;        // 平均最短距离
  } params_betweenness;
#endif

#ifdef STAT_MODULARITY
  struct ParamsModularity {
    double Coef;       // 网络分组系数Q
    VDouble NodeCoef;  // 节点分组系数P
    VNodeType Val;     // 各节点分组的序号
    VNodeType Stk;     // 按分组序号排列的节点编号
    VNodeType Num;     // 节点在moduStk中的位置
    VRNodeType Range;  // 各分组的范围
    VVLinkType LKK;    // 不同组之间连边数目
  } params_modularity;
#endif

#ifdef STAT_SIMILARITY
  struct ParamsSimilarity {
    VVDouble NodeCoef;  // 网络节点相似系数
    VVDouble EdgeCoef;  // 网络连边相似系数
  } params_similarity;
#endif

#ifdef STAT_CLUSTER
  struct ParamsCluster {
    double coef;
    VDouble Node;  // clustering coefficient
  } params_cluster;
#endif

#ifdef STAT_SPREAD
  struct ParamsSpread {
    NodeType SOURCE_HEAD, SOURCE_NULL;
    std::vector<NodeType> source, nei, num, stk, time;
    NodeType spreadSize;
    NodeType head, nei1, nei0;
    LinkType neiCountSize;

    double prob;
    std::vector<int> prob_rand;

    NodeType dataSize;
    std::vector<NodeType> data_node, data_time;
  } params_spread;
#endif

  Network(void);
  friend std::istream& operator>>(std::istream& is, Network& net);
  Network& read_params_1(std::istream& is);
  Network& read_params(const char* name = NULL);
  Network& read_params(int argc, char** argv);
  friend std::ostream& operator<<(std::ostream& os, const Network& net);
  const Network& save_params(std::ostream& os) const;
  const Network& save_params(const char* name = NULL) const;
  Network& save_data(const char* name = NULL);
  Network& save(const char* name = NULL);

  Network& init_seed(void);
  Network& init_seed(const int s);
  Network& clear_deg(void);
  Network& save_deg(const char* name = NULL);
  Network& clear_p2p(void);
  Network& save_p2p(const char* name = NULL);
  Network& clear_lkk(void);
  Network& clear(void);

  Network& read_nodeDeg(const char* name = NULL);
  Network& read_degArr(const char* name = NULL);
  Network& read_lkk(const char* name = NULL);
  Network& read_link_0(const char* name = NULL);
  Network& read_link(const char* name = NULL);
  Network& read_weight_link(const char* name = NULL);
  Network& read_link_weight(const char* name = NULL);
  Network& read_p2p(const char* name = NULL);
  Network& read_linkMatr(const char* name = NULL);
  Network& read_weightMatr(const char* name = NULL);
  Network& lkk_2_degArr(void);
  Network& p2p_2_degArr(void);
};
std::ostream& operator<<(std::ostream& os, const Network& net);

//**//************************************************************//*
#ifdef NET_DEGREE
class Net_degree {
 public:
#ifdef DEG_POISSON
  double poisson_p;
#endif

#ifdef DEG_POWER
  double power_gamma;
#endif
  Net_degree(void);
  friend std::ostream& operator<<(std::ostream& os, const Net_degree& degree);
  int save_params(std::ostream& os) const;
  int save_params(const char* name = NULL) const;
  int save_data(const char* name = NULL);
  int save(const char* name = NULL);
  int read_params_1(std::string& s, std::istream& is);
};

std::ostream& operator<<(std::ostream& os, const Net_degree& degree);
#endif

//**//************************************************************//*
#ifdef NET_RANDOM
class Net_random {
 public:
  double p;
  Net_random(void);
  friend std::ostream& operator<<(std::ostream& os, const Net_random& random);
  int save_params(std::ostream& os) const;
  int save_params(const char* name = NULL) const;
  int save_data(const char* name = NULL);
  int save(const char* name = NULL);
  int read_params_1(std::string& s, std::istream& is);
};

std::ostream& operator<<(std::ostream& os, const Net_random& random);
#endif

//**//************************************************************//*
#ifdef ACT_SIS
class Act_SIS {
 public:
  unsigned M;
  double rho, p, lambda;
  double tau, t_av, ksi, lambda_c;
  LinkType nSum, n2Sum;
  NodeType nNum;
  VVNodeType statusSN, SN;
  VNodeType N_i;
  VLinkType NDeg_i;
  VDouble t;

  Act_SIS(void);
  friend std::ostream& operator<<(std::ostream& os, const Act_SIS& sis);
  int save_params(std::ostream& os) const;
  int save_params(const char* name = NULL) const;
  int save_data(const char* name = NULL);
  int save(const char* name = NULL);
  int read_params_1(std::string& s, std::istream& is);
  Act_SIS& clear(void);
};

std::ostream& operator<<(std::ostream& os, const Act_SIS& sis);
#endif

//**//************************************************************//*
#endif  // NETWORK_H
