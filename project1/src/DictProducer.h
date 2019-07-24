#pragma once

#include "nBtyte.h"
#include "SplitTool.h"
#include <vector>
#include <string>
#include <fstream>
#include <map>

using namespace std;

namespace ll
{

class DictProducer
{
public:
    DictProducer(Configuration &conf);
    DictProducer(const string &dir,SplitTool *splittool); //专门处理中文
    ~DictProducer() {}

    void bulid_dict(); //创建英文词库
    void bulid_cn_dict(); //创建中文词库
    void store_dict(); //写入磁盘
    void bulid_index();
    void store_index();
    map<string,set<string>> &getindex()
    {
        return _index;
    }


private:
    /* string _dir;  //语料库存放路径 */
    /* vector<string> _files;   //语料库文件的绝对路径集合 */
    map<string,int> _dict;   //词典
    map<string,set<string>> _index;
    SplitTool * _splitTool;  //initrd.img分词工具
    Configuration &_conf;
};

}
