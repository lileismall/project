///
/// @file    TestAcceptor.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2019-05-07 15:42:14
///

#include "Threadpool.h"
#include "TcpServer.h"
#include "Configuration.h"
#include "DictProducer.h"
#include "nBtyte.h"
#include "LRUCache.h"
#include "RedisTool.h"
#include "RedisConfig.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <jsoncpp/json/json.h>
#include <stdlib.h>
#include <stdio.h>
using std::cout;
using std::endl;
using std::string;

using namespace Json;
using namespace std;

/* ll::Threadpool * gThreadpool = nullptr; */

namespace ll
{

/* struct cmp */
/* { */
/*     bool operator()(string l,string r) */ 
/*     { */
/*         return */ 
/*     } */
/* } */

typedef struct MyResult
{
    string _word;
    int *_ifreq;
    int *_idist;
}myResult;

class myTask
{
public:
    myTask(const string & msg,
           Threadpool &threadpool,
           const TcpConnectionPtr & conn)
        : _msg(msg)
          , _threadpool(threadpool)
          , _conn(conn)
    {}

    //运行在线程池的某一个子线程中
    void process()
    {
        cout << "sub thread:"<< pthread_self() <<" threadNum:" << current_thread::threadNum << endl;
        /* LRUCache cache = _threadpool.getCache(current_thread::threadNum); */      
        cout << "获得Cache前: " << _msg <<endl;
        _msg.pop_back();
        cout << _msg.size() << endl;
        RedisTool redis;
        string setstr = redis.getString(_msg);
        /* set<string> setstr = cache.tryGet(_msg); */
        /* cache.showCache(); */
        if(!setstr.empty())
        {
            //for(auto &s : setstr)
            //{
            //    cout << s << endl;
            //}
            //cout << "查找Cache获得" <<endl;
            //ostringstream oss;
            //for(auto &s: setstr)
            //{
            //    oss << s << "-->" << _msg
            //        << " : "<< EditDis(s,_msg) << endl ;
            //}
            string response = setstr;// = oss.str();//要返回给客户端的消息
            //cout << response << __LINE__ << endl;
            cout << "经Redis缓存找到的" << endl;
            if(!response.size())
            {
                response = "没有与之相似的！";
            }
            /* sleep(1); */
            _conn->sendInLoop(response);
        }
        else
        {
            Configuration conf("../conf/conf");   
            DictProducer test(conf);
            test.bulid_index();
            vector<string> singstr;
            string s;
            int i=0;
            //将词语中的字符提取出来
            while(_msg[i])
            {
                int nBytes = nByteCode(_msg[i]);
                s = _msg.substr(i,nBytes);
                singstr.push_back(s);
                i += nBytes;
            }
            map<string,set<string>> mapp = test.getindex();
            map<string,int> dis;  //候选词的编辑距离
            ostringstream oss;
            cout << "要发送前" <<endl;
            for(size_t i=0;i<singstr.size();i++)
            {
                auto s = mapp[singstr[i]];
                for(auto &ss : s)
                {
                    oss << ss << "-->" << _msg
                        << " : "<< EditDis(ss,_msg) << endl ;
                    dis[ss] = EditDis(ss,_msg);
                }
            }
            for(auto &s : dis)
            {
                if(s.first.size())
                    cout << s.first << ":" << s.second;
            }
            cout << endl;
            /* myResult result; */
            /* result._word = _msg; */
            map<string,int> idct = test.getIdct();
            auto cmp = [](pair<string,int> l,pair<string,int> r) { 
                return l.second > r.second; };
            priority_queue<pair<string,int>,
                vector<pair<string,int>>,decltype(cmp)> disque(cmp);
            auto iter = dis.begin();
            while(iter != dis.end())
            {
                disque.push(*iter);
                /* cout << (*iter).first << endl; */
                iter++;
            }
            oss.str(""); 
            Value val;
            StyledWriter style;
            if(!disque.empty())
            {
                for(size_t i =0;i< disque.size() && i < 3;i++)
                {
                    oss << disque.top().first<< " ";
                    val[to_string(i+1)] = disque.top().first;
                    disque.pop();
                }
            }


            cout << "经查词典找到的-----------" << endl;
            /* string response = oss.str();//要返回给客户端的消息 */
            string response = oss.str();
            if(response.empty())
            {
                response = "没有与之相似的！";
            }else
            {
                response = style.write(val);
                cout << response << endl;
                RedisTool redis;
                redis.setString(_msg,response);
                cout << response.size() << endl;
            }
            _conn->sendInLoop(response);
        }
        cout << __FILE__ << __LINE__ <<endl;
        //else{

        //    cout << "查找Cache获得" <<endl;
        //    ostringstream oss;
        //    for(auto &s: *setstr)
        //    {
        //        oss << s << "-->" << _msg
        //            << " : "<< EditDis(s,_msg) << endl ;
        //    }
        //}
        //decode
        //compute
        //encode
        //_conn->send(response);//由线程池的线程(计算线程)完成数据的发送,在设计上来说，是不合理的
        //数据发送的工作要交还给IO线程(Reactor所在的线程)完成
        //将send的函数的执行延迟到IO线程取操作
    }
private:
    string _msg;
    Threadpool &_threadpool;
    TcpConnectionPtr _conn;

};


class EchoServer
{
    friend void myTask::process();
public:
    EchoServer(int i,int j,string str,int n)
        : _threadpool(i,j)
          , _server(str,n)
    {}
    void onConnection(const TcpConnectionPtr & conn);
    void onMessage(const TcpConnectionPtr & conn);
    void onClose(const TcpConnectionPtr & conn);

    void start();
    void stop();

    void process();//业务逻辑的处理

private:
    Threadpool _threadpool;
    TcpServer _server;
};

//回调函数体现了扩展性
void EchoServer::onConnection(const ll::TcpConnectionPtr & conn)
{
    cout << conn->toString() << " has connected!" << endl;
    conn->send("welcome to server.");
}

void EchoServer::onMessage(const ll::TcpConnectionPtr & conn)
{
    cout << "onMessage...." << endl;
    string msg = conn->receive();
    cout << ">> receive msg from client: " << msg << endl;
    //业务逻辑的处理要交给线程池处理
    //decode
    //compute
    //encode
    //::sleep(2);//碰到需要长时间的处理时，响应速度会降下来
    //conn->send(msg); /* Task task(msg, conn)
    myTask task(msg,_threadpool,conn);
    _threadpool.addTask(std::bind(&myTask::process,task));
}

void EchoServer::onClose(const ll::TcpConnectionPtr & conn)
{
    cout << "onClose...." << endl;
    cout << conn->toString() << " has closed!" << endl;
}

void EchoServer::start()
{
    _threadpool.start();
    _server.setConnectionCallback(std::bind(&EchoServer::onConnection,this,std::placeholders::_1));
    _server.setMessageCallback(bind(&EchoServer::onMessage,this,placeholders::_1));
    _server.setCloseCallback(bind(&EchoServer::onClose,this,placeholders::_1));
    _server.start();
}

void EchoServer::stop()
{
    _threadpool.stop();
}

void EchoServer::process()
{
    cout << "this is process" <<endl;
}

}

/* int main() */
/* { */
/*     EchoServer test; */
/* } */

#if 1
int main(void)
{
    //ll::Threadpool threadpool(4, 10); 
    //threadpool.start();
    //
    //gThreadpool = &threadpool;

    //ll::TcpServer server("192.168.30.128", 8888);
    ll::EchoServer test(4,10,"192.168.204.135",8888);
    test.start();

    /* server.start(); */
    return 0;
}
#endif
