#include "common.h"
#include "networks.h"

using namespace std;

//**//****************************************************//*
Network::Network() :
    argv("."),
    saveName("data/test"),
    readName("data/test"),
    status(0),
    seed(0),
    dirFlag(0),
    weightFlag(0),
    distFlag(0),
    nodeSize(0),
    kMin(0),
    kMax(0),
    linkSize(0),
    priChar('\n'),
    priChar2('\t'),

#ifdef NET_DEGREE
#ifdef DEG_POISSON
    Poi_p(0.1),
#endif
#ifdef DEG_POWER
    Pow_gamma(2.5),
#endif
#endif  // NET_DEGREE


#ifdef NET_A
    A_a(0),
#endif

#ifdef NET_RANDOM
    ER_p(0.1),
#endif

#ifdef NET_BA
    BA_M(0),
    BA_M0(0),
#endif

#ifdef NET_GRID
    Grid_NX(0),
    Grid_NY(0),
#endif

    degMean(0),
    degMeanOut(0),
    degMeanIn(0),
    linkRemain(0),
    weight_m(2),
    weight_n(2),
    netWeight(0),
    netWeightOut(0),
    netWeightIn(0),
    degWeightMean(0),
    degWeightMeanOut(0),
    degWeightMeanIn(0),

#ifdef STAT_PEARSON
    pearson(0),
    pearsonNo(0),
    pearsonNoInIn(0),
    pearsonNoInOut(0),
    pearsonNoOutIn(0),
    pearsonNoOutOut(0),
    ps_rho(0),
    ps_rhoInIn(0),
    ps_rhoInOut(0),
    ps_rhoOutIn(0),
    ps_rhoOutOut(0),
#endif

    deg2WeightMean(0),
    deg2WeightMeanOut(0),
    deg2WeightMeanIn(0),

#ifdef STAT_SPEARMAN
    spearman(0),
    spearmanInIn(0),
    spearmanInOut(0),
    spearmanOutIn(0),
    spearmanOutOut(0),
    sp_rho(0),
    sp_rhoInIn(0),
    sp_rhoInOut(0),
    sp_rhoOutIn(0),
    sp_rhoOutOut(0),
#ifdef MODEL_GAUSS
    sp_r0(0),
#endif  // MODEL_GAUSS
#endif  // STAT_SPEARMAN

#ifdef STAT_BETWEENNESS
    bt(0), btEdge(0),
#endif

#ifdef STAT_KENDALLTAU
        kendallTau(0),
        kendallTauOutIn(0),
#endif  // STAT_KENDALLTAU

#ifdef STAT_MODULARITY
    moduCoef(0),
#endif

#ifdef STAT_CLUSTER
    cluster_c(0),
#endif

    net2(NULL),
    runStatus(0)
{}

Network::~Network()
{
    net_clear(*this);
}

//**//****************************************************//*
ostream& operator<<(ostream& os, const Network& net)
{
    if (!os)    return os;

    if(0 != net_save_params_0(os, net)) ERROR();

#ifdef NET_DEGREE
#ifdef DEG_POISSON
    if(0 != net_save_params_poisson(os, net)) ERROR();
#endif
#ifdef DEG_POWER
    if(0 != net_save_params_power(os, net)) ERROR();
#endif
#endif  // DEGREE

#ifdef NET_A
    if(0 != net_save_params_A(os, net)) ERROR();
#endif  // NET_BA

#ifdef NET_RANDOM
    if(0 != net_save_params_ER(os, net)) ERROR();
#endif

#ifdef NET_BA
    if(0 != net_save_params_BA(os, net)) ERROR();
#endif  // NET_BA

#ifdef NET_GRID
    if(0 != net_save_params_Grid(os, net)) ERROR();
#endif  // NET_GRID


#ifdef STAT_BETWEENNESS
    if(0 != net_save_params_betweenness(os, net)) ERROR();
#endif  //STAT_BETWEENNESS

#ifdef STAT_MODULARITY
    if(0 != net_save_params_modularity(os, net)) ERROR();
#endif

#ifdef STAT_CLUSTER
    if(0 != net_save_params_cluster(os, net)) ERROR();
#endif

#ifdef STAT_PEARSON
    if(0 != net_save_params_pearson(os, net)) ERROR();
#endif

#ifdef STAT_SPEARMAN
    if(0 != net_save_params_spearman(os, net)) ERROR();
#endif

#ifdef STAT_KENDALLTAU
    if(0 != net_save_params_kendallTau(os, net)) ERROR();
#endif

    return os;
}

int net_save_params(ostream& os, const Network& net)
{
    if(!os) return -1;
    os << net;
    return 0;
}

int net_save_params(const Network& net, const char* name)
{
    string fn;
    if(name != NULL && name[0] != '\0') fn = name;
    else{
        stringstream ss;
        ss << net.seed;
        fn = net.saveName + '_' + ss.str() + "_params.txt";
    }
    ofstream os(fn.c_str());
    if(!os) return -1;
    os << net;
    os.close();
    return 0;
}

//**//****************************************************//*
std::istream& operator>>(std::istream& is, Network& net)
{
    if(!is){
        ERROR();
        return is;
    }

    if(0 != net_read_params_0(is, net)){
        ERROR();
        net.status = -1;
    }

#ifdef NET_DEGREE
#ifdef DEG_POISSON
    is.clear();
    is.seekg(ios::beg);
    if(0 != net_read_params_poisson(is, net)){
        ERROR();
        net.status = -1;
    }
#endif
#ifdef DEG_POWER
    is.clear();
    is.seekg(ios::beg);
    if(0 != net_read_params_power(is, net)){
        ERROR();
        net.status = -1;
    }
#endif
#endif  // DEGREE

#ifdef NET_A
    is.clear();
    is.seekg(ios::beg);
    if(0 != net_read_params_A(is, net)) ERROR();
#endif  // NET_BA

#ifdef NET_RANDOM
    is.clear();
    is.seekg(ios::beg);
    if(0 != net_read_params_ER(is, net)) ERROR();
#endif

#ifdef NET_BA
    is.clear();
    is.seekg(ios::beg);
    if(0 != net_read_params_BA(is, net)) ERROR();
#endif  // NET_BA

#ifdef NET_GRID
    is.clear();
    is.seekg(ios::beg);
    if(0 != net_read_params_Grid(is, net)) ERROR();
#endif  // NET_GRID


#ifdef STAT_BETWEENNESS
    is.clear();
    is.seekg(ios::beg);
    if(0 != net_read_params_betweenness(is, net)) ERROR();
#endif  //STAT_BETWEENNESS

#ifdef STAT_MODULARITY
    is.clear();
    is.seekg(ios::beg);
    if(0 != net_read_params_modularity(is, net)) ERROR();
#endif

#ifdef STAT_CLUSTER
    is.clear();
    is.seekg(ios::beg);
    if( 0 != net_read_params_cluster(is, net)) ERROR();
#endif

#ifdef STAT_PEARSON
    is.clear();
    is.seekg(ios::beg);
    if(0 != net_read_params_pearson(is, net)) ERROR();
#endif

#ifdef STAT_SPEARMAN
    is.clear();
    is.seekg(ios::beg);
    if(0 != net_read_params_spearman(is, net)) ERROR();
#endif

#ifdef STAT_KENDALLTAU
    is.clear();
    is.seekg(ios::beg);
    if(0 != net_read_params_kendallTau(is, net)) ERROR();
#endif

    return is;
}

int net_read_params(istream& is, Network& net)
{
    if(!is) return -1;
    is >> net;
    return 0;
}

int net_read_params(Network& net, const char* name)
{
    string fn;
    if(name != NULL && name[0] != '\0')    fn = name;
    else    fn = net.readName;
    if(fn.size() <= 0)  return -1;

    ifstream is((fn + "_params.txt").c_str());
    if(!is) return -1;
    is >> net;
    is.close();

    return net.status;
}

int net_read_params(Network& net, int argc, char **argv)
{
    string s;
    for(int i = 0; i < argc; i++)   (s += '\t') += argv[i];
    stringstream ss(s);
    ss >> net;
    ss.clear();
    return net.status;
}

//**//****************************************************//*
Network& Network::save0(void)
{
    if(runStatus != 0){
        ERROR();
        return *this;
    }
    runStatus = net_save0(*this);
    if(runStatus != 0) ERROR();
    return *this;
}

Network& Network::save(const char *name)
{
    if(runStatus != 0){
        ERROR();
        return *this;
    }
    runStatus = net_save(*this, name);
    if(runStatus != 0) ERROR();
    return *this;
}

int net_save0(const Network& net)
{
    return net_save(net, net.saveName.c_str());
}

int net_save(const Network& net, const char *name)
{
    string fn;
    stringstream ss;
    if(name != NULL && name[0] != '\0') fn = name;
    else{
        ss.clear();
        ss << net.seed;
        fn = net.saveName + '_' + ss.str();
    }

    int f = 0;
    f |= net_save_params(net, (fn + "_params.txt").c_str());
    f |= net_save_deg(net, fn.c_str());
    f |= net_save_p2p(net, fn.c_str());

#ifdef STAT_BETWEENNESS
    f |= net_save_betweenness(net, fn.c_str());
#endif

#ifdef STAT_MODULARITY
    f |= net_save_modularity(net, fn.c_str());
#endif

#ifdef STAT_PEARSON
    f |= net_save_pearson(net, fn.c_str());
#endif

#ifdef STAT_SPEARMAN
    f |= net_save_spearman(net, fn.c_str());
#endif

#ifdef STAT_KENDALLTAU
    f |= net_save_kendallTau(net, fn.c_str());
#endif

#ifdef STAT_CLUSTER
    f |= net_save_cluster(net, fn.c_str());
#endif

    return f;
}

//**//****************************************************//*
Network& Network::init_seed(void)
{
    if(runStatus != 0){
        ERROR();
        return *this;
    }
    runStatus = net_init_seed(*this);
    if(runStatus != 0) ERROR();
    return *this;
}

int net_init_seed(Network& net)
{
    if(net.seed <= 0){
        while(0 == (net.seed = RAND2_INIT(net.seed)));
        cout << "\tseed\t" << net.seed << '\n';
    }
    return 0;
}

Network& Network::init_seed(const int seed)
{
    if(runStatus != 0){
        ERROR();
        return *this;
    }
    runStatus = net_init_seed(*this, seed);
    if(runStatus != 0) ERROR();
    return *this;
}

int net_init_seed(Network& net, const int seed)
{
    while(0 == (net.seed = RAND2_INIT(seed)));
    cout << '\t' << net.seed << '\n';
    return 0;
}

//**//****************************************************//*
Network& Network::run(const string& argv)
{
    if(runStatus == 0) runStatus = net_run(*this, argv);
    if(runStatus != 0) ERROR();
    return *this;
}

int net_run(Network& net, const string& argv)
{
    string s;
    istringstream ss;
    if(argv.size() > 0) ss.str(argv);
    else ss.str(net.argv);
    while(ss >> s){
        cout << s << '\n';
        if(s.size() <= 0 || s == ".") continue;

        if(s == "cal_params"){
            common_get_string(ss, s);
            if(0 != net_cal_params(net, s)) {
                ERROR();
                return net.status = -1;
            }
            continue;
        }

        if(s == "init_seed0"){
            if(net.seed <= 0) while(0 == (net.seed = RAND2_INIT(net.seed)));
            cout << "\tseed\t" << net.seed << '\n';
            continue;
        }

        if(s == "init_seed"){
            while(0 == (net.seed = RAND2_INIT(net.seed)));
            cout << "\tseed\t" << net.seed << '\n';
            continue;
        }

        if(s == "cal_deg"){
            if(!(ss >> s) || 0 != net_cal_nodeDeg(net, s)){
                ERROR();
                return net.status = -1;
            }
            continue;
        }

        if(s == "cal_p2p"){
            if(!(ss >> s) || 0 != net_cal_p2p(net, s)){
                ERROR();
                return net.status = -1;
            }
            continue;
        }

        if(s == "fix_p2p"){
            if(0 != fix_p2p(net.p2p, net.dirFlag)){
                ERROR();
                return net.status = -1;
            }
            continue;
        }

        if(s == "fix_p2p_nodeDeg0"){
            if(0 != net_fix_p2p_nodeDeg0(net)){
                ERROR();
                return net.status = -1;
            }
            continue;
        }

#ifdef NET_EXTREMUM
        if(s == "lkk_max"){
            if(0 != net_extreme_lkk(net, 1)){
                ERROR();
                return net.status = -1;
            }
            continue;
        }
        if(s == "lkk_min"){
            if(0 != net_extreme_lkk(net, 0)){
                ERROR();
                return net.status = -1;
            }
            continue;
        }
        if(s == "lkk_maxN"){
            unsigned t;
            if(!(ss >> t) || 0 != net_extreme_lkk(net, 1, t)){
                ERROR();
                return net.status = -1;
            }
            continue;
        }
        if(s == "lkk_minN"){
            unsigned t;
            if(!(ss >> t) || 0 != net_extreme_lkk(net, 0, t)){
                ERROR();
                return net.status = -1;
            }
            continue;
        }
        if(s == "MinLkk"){
            if(0 != net_Min_new_lkk(net, 0)){
                ERROR();
                return net.status = -1;
            }
            continue;
        }
        if(s == "MinLkkFix"){
            if(0 != net_Min_new_lkk(net, 1)){
                ERROR();
                return net.status = -1;
            }
            continue;
        }
#endif

        if(s == "stat"){
            if(0 != net_stat(net)){
                ERROR();
                return net.status = -1;
            }
            continue;
        }

        if(s == "print"){
            if(0 != net_save_params(cout, net)){
                ERROR();
                return net.status = -1;
            }
            continue;
        }

        if(s == "save"){
            if(0 != net_save(net)){
                ERROR();
                return net.status = -1;
            }
            continue;
        }
        if(s == "save0"){
            if(0 != net_save0(net)){
                ERROR();
                return net.status = -1;
            }
            continue;
        }

        if(s == "clear"){
            if(0 != net_clear(net)){
                ERROR();
                return net.status = -1;
            }
            continue;
        }

        if(s == "exit") return 0;

        ERROR(s);
        return net.status = -1;
    }

    return 0;
}

//**//****************************************************//*
Network& Network::clear_net(void)
{
    if(runStatus != 0){
        ERROR();
        return *this;
    }
    runStatus = net_clear(*this);
    if(runStatus != 0) ERROR();
    return *this;
}

int net_clear(Network& net)
{
    net_clear_deg(net);
    net_clear_p2p(net);
    net_clear_lkk(net);

#ifdef NET_A
    net_clear_A(net);
#endif

#ifdef STAT_PEARSON
    net_clear_pearson(net);
#endif

#ifdef STAT_SPEARMAN
    net_clear_spearman(net);
#ifdef MODEL_GAUSS
    net.sp_GaussS2.clear();         // [nodeSize]   模型的联合概率的方差
#endif
#endif

#ifdef STAT_KELDALLTAU
    net_clear_kendallTau(net);
#endif

#ifdef STAT_BETWEENNESS
    net_clear_betweenness(net);
#endif

#ifdef STAT_MODULARITY
    net_clear_modularity(net);
#endif

#ifdef STAT_CLUSTER
    net_clear_cluster(net);
#endif

    return 0;
}

//**//****************************************************//*
int net_cal_params(Network& net, const string& s)
{
    string t;
    istringstream ss(s);
    while(ss >> t){
        if(t.size() <= 0) continue;
        if(t == "dirFlag"){
            net.dirFlag = 1;
            continue;
        }
        if(t == "!dirFlag"){
            net.dirFlag = 0;
            continue;
        }
        if(t == "weightFlag"){
            net.weightFlag = 1;
            continue;
        }
        if(t == "!weightFlag"){
            net.weightFlag = 0;
            continue;
        }
        ERROR(s);
        return -1;
    }
    return 0;
}

//**//****************************************************//*
int net_cal_nodeDeg(Network& net, const string& s)
{
    cout << "\t" << s << '\n';
    if(!net.nodeDeg.empty() || s.size() <= 0){
        ERROR(s);
        return -1;
    }

    if(s == "p2p"){
        if(!net.p2p.empty()) return net_p2p_2_degArr(net);
        else return -1;
    }

    if(s == "read_deg") return net_read_nodeDeg_0(net);

    if(s == "read_degArr") return net_read_degArr_0(net);

    if(s == "read_lkk") return net_read_lkk_0(net);

#ifdef NET_DEGREE
#ifdef DEG_POWER
    if(s == "power") return net_deg_power(net);
#endif
#ifdef DEG_POISSON
    if(s == "poisson") return net_deg_poisson(net);
#endif
#endif  // NET_DEG

    ERROR(s);
    return -1;
}

//**//****************************************************//*
int net_cal_p2p(Network& net, const string& s)
{
    cout << "\t" << s << '\n';
    if(net.status < 0){
        ERROR();
        return net.status;
    }
    if(net.p2p.empty()){
        do{
            if(s.size() <= 0){
                ERROR();
                return net.status = -1;
            }
            if(s == "read_p2p" || s == "read_p2p_fix"){
                if(!net.p2p.empty() || 0 != net_read_p2p_0(net)){
                    ERROR();
                    return -1;
                }
                break;
            }

            if(s == "read_linkMatr" || s == "read_linkMatr_fix"){
                if(!net.p2p.empty() || 0 != net_read_linkMatr_0(net)){
                    ERROR();
                    return -1;
                }
            }
            if(s == "read_link" || s == "read_link_fix"){
                if(!net.link.empty() || 0 != net_read_link(net)){
                    ERROR();
                    return -1;
                }
            }
            if(s == "read_link_0" || s == "read_link_0_fix"){
                if(!net.link.empty() || 0 != net_read_link_0(net)){
                    ERROR();
                    return -1;
                }
            }

            if(s == "read_weightMatr"){
                if(!net.weightMatr.empty() || 0 != net_read_weightMatr_0(net)){
                    ERROR();
                    return -1;
                }
            }
            if(s == "read_weight_link"){
                if(!net.weightFlag || net.link.empty() || !net.vvweight.empty() || 0 != net_read_weight_link(net)){
                    ERROR();
                    return -1;
                }
            }
            if(s == "read_link_weight_0"){
                if(!net.weightFlag || !net.link.empty() || !net.vvweight.empty() || 0 != net_read_link_weight_0(net)){
                    ERROR();
                    return -1;
                }
            }

            if(s == "p2p" || s == "p2p_fix" || s.find("read_") != string::npos){
                if(net.weightFlag && !net.weightMatr.empty() && net.linkMatr.empty()){
                    if(0 != weightMatr_2_linkMatr(net.linkMatr, net.weightMatr)){
                        ERROR();
                        return -1;
                    }
                    //break;
                }
                if(!net.linkMatr.empty()){
                    if(0 != linkMatr_2_p2p(net.p2p, net.linkMatr)) ERROR();
                    break;
                }
                if(!net.linkMatrC.empty()){
                    if(0 != linkMatrC_2_p2p(net.p2p, net.linkMatrC)) ERROR();
                    break;
                }
                if(!net.link.empty()){
                    if(0 != link_2_p2p(net.p2p, net.link, net.p2pIn, net.nodeSize, net.dirFlag)){
                        ERROR();
                        return -1;
                    }
                    break;
                }
                ERROR(s);
                return net.status = -1;
            }

#ifdef NET_EXTREMUM
            if(s == "Max"){
                net.status = net_Max_new(net);
                break;
            }
            if(s == "Min"){
                net.status = net_Min_new(net);
                break;
            }
            if(s == "MinLkkP2p"){
                net.status = net_Min_new_lkk_p2p(net, 0);
                break;
            }
            if(s == "MinLkkP2pFix"){
                net.status = net_Min_new_lkk_p2p(net, 1);
                break;
            }
#endif

#ifdef NET_RANDOM
            if(s == "ER"){
                net.status = net_ER(net);
                break;
            }
            if(s == "random"){
                net.status = net_random_remDeg(net);
                break;
            }
#endif

#ifdef NET_BA
            if(s == "BA"){
                net.status = net_BA(net);
                break;
            }
#endif

#ifdef NET_GRID
            if(s == "Grid"){
                net.status = net_Grid_new(net);
                break;
            }
#endif

#ifdef STAT_SPEARMAN
            if(s == "Spearman"){
#ifdef MODEL_GAUSS
                net.status = net_gauss_new_ranLink(net);
#else
                net.status = -1;
#endif
                break;
            }
#endif

            ERROR(s);
            return net.status = -1;
        } while(0);
    }else if(net.status == 0) net.status = 1;

    if(net.status < 0 || net.p2p.empty()){
        ERROR();
        return net.status = -1;
    }

    if(s.find("_fix") != string::npos) {
        fix_p2p(net.p2p, net.dirFlag);
        net.linkSize = 0;
    }

    if(net.dirFlag && net.p2pIn.empty() && 0 != p2p_2_p2pIn(net.p2pIn, net.p2p)){
        ERROR();
        return -1;
    }

    if(0 != net_p2p_2_degArr(net)){
        ERROR();
        return -1;
    }
    if(net.kMax <= 0 || s.find("read_") != string::npos){
        net.kMin = net.degArrVal.front();
        net.kMax = net.degArrVal.back();
    }

    net.status = 1;
    return 0;
}

//**//****************************************************//*
Network& Network::stat(void)
{
    if(runStatus != 0){
        ERROR();
        return *this;
    }
    runStatus = net_stat(*this);
    if(runStatus != 0) ERROR();
    return *this;
}

int net_stat(Network& net)
{
    if(net.lkk.empty() && net.p2p.empty()){
        ERROR();
        return -1;
    }
    if(!net.p2p.empty()){
        if(0 != net_p2p_2_degArr(net)){
            ERROR();
            return -1;
        }
    }else if(0 != net_lkk_2_degArr(net)){
        ERROR();
        return -1;
    }

#ifdef STAT_PEARSON
    cout << "\tpearson\n";
    if(0 != net_cal_pearson(net)){
        ERROR();
        return -1;
    }
#endif

#ifdef STAT_SPEARMAN
    cout << "\tspearman\n";
    if(0 != net_degArr_2_deg2ArrVal_weight(net) || 0 != net_cal_spearman(net)){
        ERROR();
        return -1;
    }
#endif

#ifdef STAT_BETWEENNESS
    cout << "\tbetweenness\n";
    if(0 != net_betweenness(net)){
        ERROR();
        return -1;
    }
#endif

#ifdef STAT_MODULARITY
    cout << "\tmodularity\n";
    if(0 != net_modularity(net)){
        ERROR();
        return -1;
    }
#endif

#ifdef STAT_CLUSTER
    cout << "\tcluster\n";
    if(0 != net_cal_cluster(net)){
        ERROR();
        return -1;
    }
#endif

#ifdef STAT_KENDALLTAU
    cout << "\tkendallTau\n";
    if(0 != net_cal_kendallTau(net)){
        ERROR();
        return -1;
    }
#endif

    return 0;
}

//**//****************************************************//*
