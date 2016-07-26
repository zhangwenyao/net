#ifdef ACT_FITNESS_COMPLEXITY

#include "common.h"
#include "net.h"
using namespace std;

//**//*****************************************************//*
do{
    const int NY = 16, NC = 263, NP = 986;
    VNodeType   cNum[NY], pNum[NY];
    VVDouble    Qpc[NY];    // product_country
    VDouble     Qc[NY], Qp[NY];
    double      Qsum[NY];
    VVBool      Mcp[NY];     // Mcp
    stringstream ss;
    ifstream is;
    ofstream os;
    int status = 0;

    // read Qpc
    for(size_t y = 0; y < NY; y++){
        ss.str("");
        ss << "FC/exp" << y + 1995 << ".txt";
        is.open(ss.str().c_str());
        if(!is){
            ERROR(ss.str());
            return -1;
        }
        int t;
        is >> t;
        if(t != 0){
            status = -1;
            ERROR(ss.str().c_str());
            is.close();
            break;
        }
        common_read1_0(is, cNum[y], 1);
        for(NodeType p; is >> p;){
            pNum[y].push_back(p);
            Qpc[y].push_back(VDouble(cNum[y].size()));
            common_read1(is, Qpc[y].back());
        }
        is.close();
    }
    if(status < 0) return status;

    // cal Qp Qc Qsum
    for(size_t y = 0; y < NY; y++){
        Qsum[y] = 0;
        const size_t ps = pNum[y].size(), cs = cNum[y].size();
        Qc[y].assign(cs, 0);
        Qp[y].assign(ps, 0);
        for(size_t p = 0; p < ps; p++){
            for(size_t c = 0; c < cs; c++){
                Qp[y][p] += Qpc[y][p][c];
                Qc[y][c] += Qpc[y][p][c];
            }
            Qsum[y] += Qp[y][p];
        }
    }

    // cal Mcp
    for(size_t y = 0; y < NY; y++){
        const size_t cs = cNum[y].size(), ps = pNum[y].size();
        Mcp[y].assign(cs, VBool(ps, false));
        for(size_t p = 0; p < ps; p++){
            for(size_t c = 0; c < cs; c++){
                Mcp[y][c][p] = Qpc[y][p][c] * Qsum[y] >= Qc[y][c] * Qp[y][p];
            }
        }
    }

    // save Mcp
    for(size_t y = 0; y < NY; y++){
        ss.str("");
        ss << "data/Mcp" << y + 1995 << ".txt";
        os.open(ss.str().c_str());
        if(!os){
            ERROR();
            return -1;
        }
        for(size_t i = 1, i2 = 0; i <= NC; i++){
            if(i2 >= cNum[y].size() || i < cNum[y][i2]){
                for(size_t j = 1; j <= NP; j++) os << '\t' << 0;
                os << '\n';
                continue;
            }
            if(i > cNum[y][i2]){
                ERROR(y, '\t', i, '\t', i2);
                status = -1;
                break;
            }

            for(size_t j = 1, j2 = 0; j <= NP; j++){
                if(j2 >= pNum[y].size() || j < pNum[y][j2]){
                    os << '\t' << 0;
                    continue;
                }
                if(j > pNum[y][j2]){
                    ERROR(y, '\t', i, '\t', j, '\t', j2);
                    status = -1;
                    i = NC;
                    break;
                }
                os << '\t' << Mcp[y][i2][j2++];
            }
            os << '\n';
            i2++;
        }
        os.close();
        if(status < 0) return status;
    }

    // cal Fc Cp
    VDouble     Fc[NY], Cp[NY];
    for(size_t y = 0; y < NY; y++){
        INFORM(y + 1995);
        if(0 != Mcp_2_FC(Fc[y], Cp[y], Mcp[y])){
            ERROR(y+1995);
            return -1;
        }
    }

    // save Fc
    os.open("data/Fc1995-2010.txt");
    if(!os){
        ERROR();
        return -1;
    }
    //for(size_t i = 1; i <= NC; i++) os << '\t' << i;
    //os << '\n';
    for(size_t y = 0; y < NY; y++){
        for(size_t i = 1, j = 0; i <= NC; i++){
            if(j >= cNum[y].size() || i < cNum[y][j]){
                os << '\t' << 0;
                continue;
            }
            if(i > cNum[y][j]){
                ERROR(y, '\t', i, '\t', j);
                status = -1;
                break;
            }
            os << '\t' << Fc[y][j++];
        }
        os << '\n';
    }
    os.close();

    // save Cp
    os.open("data/Cp1995-2010.txt");
    if(!os){
        ERROR();
        return -1;
    }
    //for(size_t i = 1; i <= NP; i++) os << '\t' << i;
    //os << '\n';
    for(size_t y = 0; y < NY; y++){
        for(size_t i = 1, j = 0; i <= NP; i++){
            if(j >= pNum[y].size() || i < pNum[y][j]){
                os << '\t' << 0;
                continue;
            }
            if(i > pNum[y][j]){
                ERROR(y, '\t', i, '\t', j);
                status = -1;
                break;
            }
            os << '\t' << Cp[y][j++];
        }
        os << '\n';
        if(status < 0) return status;
    }
    os.close();

    return status;
}while(0);

//**//*****************************************************//*
#endif  // ACT

