#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

using namespace std;

class Configuration
{
public:
    Configuration(const string &filepath)
    : _filepath(filepath)
    {}
    ~Configuration() {}

    map<string,string> &getConfigMap()
    {
        ifstream ifs(_filepath);
        string str;
        while(getline(ifs,str,'\n'))
        {
            int i=0;
            while(str[i] != '=') i++;
            string confname(str,0,i);
            string confpath(str,i+1,str.size()-1);
            _configMap[confname] = confpath;
        }
        for(auto &s : _configMap)
        {
            cout << s.first << " : " << s.second << endl;
        }
        return _configMap;
    }

private:
    string _filepath;
    map<string,string> _configMap;

};

/* int main() */
/* { */
/*     Configuration test("../conf/conf"); */
/*     test.getConfigMap(); */
/*     return 0; */
/* } */
