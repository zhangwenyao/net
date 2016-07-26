//**//********************************************************************
#ifdef NET_BA
do{
    Network net;
    net.saveName = net.readName = "data/BA_power2.5";
    net.nodeSize = 1024;    // 节点数
    net.Pow_gamma = 2.5;    // 度分布幂律分布的幂指数
    net.kMin = 4;   // 最小度
    net.kMax = net.kMin + sqrt(net.nodeSize) - 1;   // 最大度
    while(0 == (net.seed = RAND2_INIT(net.seed)));    // 初始化随机数种子
    if(0 != net_new(net, "cal_deg deg_power cal_p2p BA save")){
        ERROR();
        break;
    }
}while(0);
#endif
//**//********************************************************************
