#include "common.h"

using namespace std;
//**//***********************************************************//*
int common_get_string(istream& is, string& s)
{
    if(is >> s && !s.empty() && s[0] == '\"'){
        for(string t; is >> t;){
            if(!t.empty()){
                s += '\t';
                s += t;
                if(t[t.size()-1] == '\"') break;
            }
        }
    }
    return 0;
}


//**//***********************************************************//*

