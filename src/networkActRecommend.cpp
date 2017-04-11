#include "ActRecommend.h"
#include "networkActRecommend.h"
#ifdef ACT_RECOMMEND

#include "common.h"
using namespace std;
//**//****************************************************//*
int net_act_recommend_save_i(VDouble& o, char *name)
{
    common_save1(name, o);
    return 0;
}

int net_act_recommend_mass(VDouble& o, VDouble& u2, VDouble& o2, VVNodeType& pu, VVNodeType& po)
{
    const NodeType n = pu.size();
    for(NodeType i = 0 ; i < n; i++){
        o.assign(n, 0);
        o2 = u2 = o;
        recommend_start(pu[i], o);
        for(VNodeTypeItr oj = pu[i].begin(); oj != pu[i].end(); oj++){
            NodeType j = *oj;
            recommend_mass(po[j], u2, o[j] / po[j].size());
            for(VNodeTypeItr oi2 = po[j].begin(); oi2 != po[j].end(); pi2++){
                NodeType i2 = *oi2;
                recommend_mass(pu[i2], o2, u2[i2] / pu[i2].size());
            }
        }
        stringstream ss;
        ss.clear();
        ss << "mass_" << i << ".txt";
        net_act_recommend_save_i(o2, ss.str().c_str());
    }
    return 0;
}

int net_act_recommend(Network &net, const string& s)
{
    // TODO
    if(s == "mass"){
        return 0;
    }
    if(s == "heat"){
        return 0;
    }
    return net.status = -1;
}
//**//****************************************************//*
#endif  // ACT_RECOMMEND

