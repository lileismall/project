#pragma once
#include "../include/cppjieba/include/cppjieba/Jieba.hpp"
#include "Configuration.h"

using namespace cppjieba;


namespace ll
{

class SplitTool
{
public:
    SplitTool() {}
    ~SplitTool() {}

    virtual vector<string> cut(const string &sentence) = 0;
private:

};

class CppJieba
:public SplitTool
{
public:
    CppJieba()
    {
        const char *DICT_PATH = "../include/cppjieba/dict/jieba.dict.utf8";
        const char* const HMM_PATH = "../include/cppjieba/dict/hmm_model.utf8";
        const char* const USER_DICT_PATH = "../include/cppjieba/dict/user.dict.utf8";
        const char* const IDF_PATH = "../include/cppjieba/dict/idf.utf8";
        const char* const STOP_WORD_PATH = "../include/cppjieba/dict/stop_words.utf8";
        _jieba = new Jieba(DICT_PATH, HMM_PATH,
                    USER_DICT_PATH,
                    IDF_PATH,
                    STOP_WORD_PATH
                   );
    }
    /* CppJieba(Configuration &conf) */
        /* : _conf(conf) */
    /* {} */

    ~CppJieba() {}

    vector<string> cut(const string &sentence) override
    {
        vector<string> cutvec;
        _jieba->Cut(sentence,cutvec,true);
        for(auto &s : cutvec)
        {
            cout << s << endl;
        }

        return cutvec;
    }

private:
        Jieba *_jieba;
    /* Configuration &_conf; */

};

//class EngJieba
//:public SplitTool
//{
//    EngJieba(){}
//    ~EngJieba(){}
//    vector<string> cut(const string &sentence) override
//    {
//        vector<string> cutvec;
//
//
//
//        return cutvec;
//    }
//
//};

}
