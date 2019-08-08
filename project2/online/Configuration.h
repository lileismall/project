#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>

using namespace std;

namespace ll
{


class Configuration
{
public:
    Configuration(const string &filepath)
        : _filepath(filepath)
    {
        InitConfigMap();
    }
    ~Configuration() {}

    void InitConfigMap()
    {
        ifstream ifs(_filepath);
        string str;
        while(getline(ifs,str,'\n'))
        {
            int i=0;
            while(str[i] != '=') i++;
            /* str.find("=",i); */
            string confname(str,0,i);
            string confpath(str,i+1,str.size()-1);
            _configMap[confname] = confpath;
        }
        for(auto &s : _configMap)
        {
            cout << s.first << " : " << s.second << endl;
        }
    }
    map<string,string> &getConfigMap()
    {
        return _configMap;
    }

set<std::string> & getStopWordList()
    {
        if(stopWordList_.size() > 0)
            return stopWordList_;

        std::string stopWordFilePath = _configMap["stopwordpath"];
        std::ifstream ifs(stopWordFilePath.c_str());
        if(!ifs)
        {
            std::cout << "StopWord ifstream open error!" << std::endl;

        }

        std::string word;
        while(getline(ifs, word))
        {
            stopWordList_.insert(word);

        }

#if 0
        for(auto &str : stopWordList_)
        {
            std::cout << str << "\t" << str.size() << std::endl;
        }
        std::cout << std::endl;
#endif

        return stopWordList_;
    }

private:
    string _filepath;
    map<string,string> _configMap;
    set<std::string> stopWordList_;
};

/* int main() */
/* { */
/*     Configuration test("../conf/conf"); */
/*     test.getConfigMap(); */
/*     return 0; */
/* } */
}
