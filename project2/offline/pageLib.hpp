
#pragma once
#include "tinyxml2.h"  // "" 从当前目录开始搜索
#include "readfile.h"
#include "Configuration.hpp"
#include <iostream>    // 从系统路径开始搜索
#include <regex>
#include <string>
#include <fstream>
#include <map>
using std::cout;
using std::endl;
using namespace tinyxml2;
using namespace std;
using namespace ll;

// learning by doing 

class PageLib
{
public:
    PageLib(Configuration &conf)
    : _conf(conf)
    {}

    void create();
    void store();

private:
    Configuration &_conf;
    vector<string> _vecFiles; //存放格式化后的网页容器
    vector<pair<string,string>> _offsetLib; //存放位置信息
};

void PageLib::create() //将网页保存在ector中
{
    XMLDocument doc;
    vector<string> path = getAllFilesName(dirr);
    /* vector<string> path; */
    path.push_back("coolshell.xml");
    path.push_back("coolshell.xml");
    XMLElement * itemElement; 
    int num = 0;  //id
    cout << "------------rss源语料文件名----------" << endl;
    for(auto &s : path)
    {
        cout << s << endl;
    }

    for(size_t i=0;i<path.size();i++)
    {
        cout << __FILE__ << __LINE__ << path[i] << endl;
        doc.LoadFile(path[i].c_str());
        if(doc.ErrorID()) {
        /* cout << __FILE__ << __LINE__ << endl; */
            cout << path[i].c_str() << endl;
            cout << "doc load error!" << endl;
            /* return; */
            continue;
        }
#if 1
        /* cout << __FILE__ << __LINE__ << endl; */
        itemElement = doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");
        if(itemElement == NULL)
        { break; }
        /* cout << __FILE__ << __LINE__ << endl; */
        do {
        /* cout << __FILE__ << __LINE__ << endl; */
            XMLElement * titleElement = itemElement->FirstChildElement("title");
            XMLElement * linkElement = itemElement->FirstChildElement("link");
            XMLElement * contentElement = itemElement->FirstChildElement("content:encoded");
            
        /* cout << __FILE__ << __LINE__ << endl; */
            const char * title = titleElement->GetText();
            const char * link = linkElement->GetText();
            const char *content = "NULL";
            if(contentElement == NULL)
            {
                //如果内容为空，直接放弃这一段标题，链接,等等
                continue;
            }
            /* if(contentElement != NULL) */
            /* { */
           content = contentElement->GetText();
            /* } */

        /* cout << __FILE__ << __LINE__ << endl; */
            /* cout << "title:" << title << endl << endl; */
            /* cout << "link:" << link << endl; */
            /* cout << "content:" << content << endl; */

            std::regex re("<[^>]*>");
            /* string contentProcess = "NULL"; */
        /* cout << __FILE__ << __LINE__ << endl; */
            /* if(content != NULL) */
            /* { */
            std::string contentProcess = std::regex_replace(content, re, "");
            /* } */
            /* cout << "content: " << endl */
                /* << contentProcess << endl; */
        /* cout << __FILE__ << __LINE__ << endl; */
            std::string doc = 
                "<doc>\n"
                "    <docid>" + std::to_string(num)+ "</docid>\n"
                "    <url>" + link + "</url>\n"
                "    <title>" + title +"</title>\n"
                "    <content>" + contentProcess + "</content>\n"
                "</doc>";
        /* cout << __FILE__ << __LINE__ << endl; */
            _vecFiles.push_back(doc);
        /* cout << __FILE__ << __LINE__ << endl; */
            num++;
        } while((itemElement = itemElement->NextSiblingElement("item")) != NULL);
        cout << __FILE__ << __LINE__ << endl;
#endif
    }//end of for
}

void PageLib::store()
{
    map<string,string> paths = _conf.getConfigMap();
    /* cout << "----------配置文件内容：----------" << endl; */
    /* for(auto &s:paths) */
    /* { */
    /*     cout << s.first << endl; */
    /* } */
    /* std::ofstream ofs("data.lib"); */
    std::ofstream ofs(paths["datapath"]); //格式化后的网页存储位置
    /* std::ofstream pofs("pdata.lib"); */
    std::ofstream pofs(paths["pdatapath"]); //位置信息
    int docId = 0;
    for(auto &s : _vecFiles)
    {
        size_t offset = ofs.tellp(); //偏移量
        size_t lenth =  s.size(); //网页长度
        /* std::string seek = std::to_string(docId++) +"\t"+ std::to_string(offset) */
        /*     +"\t" + std::to_string(lenth) + "\n"; */
        pair<string,string> set(to_string(offset),to_string(lenth));
        /* _offsetLib[to_string(docId)] = set; */
        _offsetLib.push_back(set);
        ofs << s; //保存网页
        /* pofs << seek; */
        pofs << docId++ << "\t" << offset << "\t" << lenth << endl;
    }


    ofs.close();
    pofs.close();
}


