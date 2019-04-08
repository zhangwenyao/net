#ifndef NETWORK_H
#define NETWORK_H

#include "net.h"

#include <iostream>
// *******************************************************************
/*
 *                net_run       argv          options
 * 参数           cal_params    dirFlag !dirFlag        是否有向
 *                              weightFlag !weightFlag  是否带权重
 * 随机数种子     init_seed                   仅首次初始化
 *                init_seed0                  重新初始化种子
 * 度分布         cal_deg       read_deg      读取度序列
 *                              read_degArr   读取度分布
 *                              read_lkk      读取连边分布
 *                              lkk_power     度序列幂律的联合分布矩阵lkk
 *                              power         度序列幂律分布
 *                              power_arr     度序列幂律分布
 *                              poisson       度序列泊松分布
 * 连边           cal_p2p       p2p           利用已有数组转化
 *                              read_p2p      读取连边链接表
 *                              read_linkMatr 读取连边矩阵
 *                              read_link     读取连边
 *                              Max           最大度关联网络
 *                              Max_lkk       最大度关联网络
 *                              Max_lkk3      最大度关联网络
 *                              Min           最小度关联网络
 *                              Min_lkk       最小度关联网络
 *                              Min_lkk3       最小度关联网络
 *                              MinLkkP2p     min lkk -> p2p
 *                              MinLkkP2pFix  min lkk -> p2p fix
 *                              ER            ER随机网络
 *                              Random        随机网络
 *                              BA            BA网络
 *                              Grid          网格网络
 *                              Spearman      sp系数给定的网络
 * 修正           fix_p2p                     修正自环、重边、缺边
 *                fix_p2p_nodeDeg0
 * 按p2p度排序重新映射节点，度为0在最后（剔除） 连边矩阵       cal_extrLKK
 * lkk_max           lkk最强pearson同配 lkk_min           lkk最强pearson异配
 *                              lkk_maxN  countN  lkk最强pearson同配
 *                              lkk_minN  countN  lkk最强pearson异配
 *                              MinLkk            最小度关联网络
 *                              MinLkkFix         最小度关联网络
 * 统计           stat
 * 推荐           recommend     mass              物质扩散
 *                              heat              热传导
 *                              hybird            物质扩散&热传导
 *                              pagerank          网页排名
 *                              commonNeighbour   共同邻居
 *                              proximity_wcp     相似性-比例
 *                              proximity_phi     相似性-平均值
 *                              proximity_phi     相似性-平均值
 * 传播           sis
 * 输出           print
 * 保存           save                        以种子值命名保存
 *                save0                       无种子值保存
 * 清理           clear
 * 结束           exit
 */ /**/

// *******************************************************************
class Network {
  public:
  // variables
  std::string argv;     // 参数
  std::string saveName; // 保存文件名前缀
  std::string readName; // 读取文件名前缀
  int status; // 网络状态 0：空，1：正常p2p，2：lkk，-1：有错，-2：未连完
  long seed;  // 随机数种子值
  int dirFlag;                // 网络是否有向，0无向，非0有向
  int weightFlag;             // 网络是否有权，0无权，非0有权
  int distFlag;               //  网络距离是否01，0:01，非0:实数
  NodeType nodeSize, degSize; // 节点数，不同度数
  NodeType kMin, kMax;        // 度范围,最小度,最大度
  LinkType linkSize;          // 连边数
  std::vector<int> paramsInt; // 整型参数
  std::vector<double> paramsDouble; // 实数参数
  char priChar, priChar2;           // 保存文件时的分隔符
  int runStatus;

  // deg
  VDouble degArrProb, degArrProbSum; // [degSize]    度分布概率 p(k)
  double degProbSum;
  VDouble degProbSumArr;
  VNodeType degProbSumVal;
  VNodeType degArrVal;  // [degSize]    度分布序列 k
  VNodeType degArrSize; // [degSize]    各度节点数 n(k)
  MNodeType degArrNo;   // [kMax+1]     度k在degArrVal中的位置
  VNodeType degArrSum;  // [degSize+1]  度分布累计序列
  VNodeType nodeDeg;    // [nodeSize]   各节点度
  VNodeType remNodeNum; // [remNodeSize]    未全连边的节点编号
  VNodeType nodesName, nodesName2; // [nodeSize]   节点的映射关系

  VNodeType nodeDegIn, degArrValIn, degArrSizeIn, degArrSumIn;
  VNodeType nodeDegOut, degArrValOut, degArrSizeOut, degArrSumOut;
  MNodeType degArrNoIn, degArrNoOut;
  double degMean, degMeanOut, degMeanIn;

  // link
  VNodeType link, p2pSize; // [nodeSize*2] 网络连边
  VVNodeType p2p, p2pIn; // [nodeSize]   各点连边链表p2p:出度,p2pIn:入度
  VVDistType linkMatr; // [nodeSize]   网络连边距离矩阵
  VVChar linkMatrC;    // [nodeSize]   网络连边01矩阵
  LinkType linkRemain;
  VLinkType linkSum; // 各度累计线头数

  // weight
  VVWeightType vvweight, vvweightIn, weightMatr; // 连边权重
  unsigned weight_m, weight_n; // 数据文件中连边权重位置 (m+1) / n
  VWeightType nodeWeight, nodeWeightOut, nodeWeightIn; // 各节点总连边权重
  VWeightSumType degArrWeight, degArrWeightOut,
      degArrWeightIn; // 同度节点连边总权重
  WeightSumType netWeight, netWeightOut, netWeightIn;
  double degWeightMean, degWeightMeanOut, degWeightMeanIn;

  // lkk
  VVLinkType lkk, lkkOutIn;       // 不同度之间连边数目矩阵
  VVLinkType lkkSum, lkkSumOutIn; // 同度点连向所有度的累计边数
  VVDouble lkkProb;               // [degSize]    连边的联合分布概率
  int lkk_saveType;
  // lkk3
  VLkk3LinkType lkk3, lkk3reverse, lkk3OutIn; // 不同度之间连边数目矩阵
  VLkk3Double lkk3Prob; // [degSize]    连边的联合分布概率

  Network(void);
  friend std::istream& operator>>(std::istream& is, Network& net);
  Network& read_params_1(std::string& s, std::istream& is);
  friend std::ostream& operator<<(std::ostream& os, Network& net);
  Network& save_params(std::ostream& os);
  Network& save_params(const char* name = NULL);
  Network& save_data(const char* name = NULL);
  Network& save(const char* name = NULL);

  Network& init_seed0(const long s);
  Network& init_seed(const long s);
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
std::ostream& operator<<(std::ostream& os, Network& net);

// ******************************************************
#endif // NETWORK_H
