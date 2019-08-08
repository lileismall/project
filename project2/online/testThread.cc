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
#include "WordQuery.h"

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
            WordQuery &wordQue,
           const TcpConnectionPtr & conn)
        : _msg(msg)
          , _threadpool(threadpool)
          , _wordQue(wordQue)
          , _conn(conn)
    {}

    //运行在线程池的某一个子线程中
    void process()
    {
        _msg.pop_back();
        RedisTool redis;
        string setstr = redis.getString(_msg);
        cout << "_msg" << _msg << endl;
        if(!setstr.empty())
        {
            cout << "经Redis缓存找到的" << endl;
            string response = setstr;
            string len = to_string(response.size());
            response = len + "\n" + response;
            /* _conn->sendInLoop(len); */
            _conn->sendInLoop(response);
        }else{
            cout << "经网页库查找到" << endl;
            string response = _wordQue.doQuery(_msg); 
            redis.setString(_msg,response);
            string len = to_string(response.size());
            response = len + "\n" + response;
            /* _conn->sendInLoop(len); */
            _conn->sendInLoop(response);
            cout << __FILE__ << __LINE__ << endl;
        }
    }
private:
    string _msg;
    Threadpool &_threadpool; //线程池
    WordQuery &_wordQue;// 用来查询
    TcpConnectionPtr _conn; //具体链接

};


class EchoServer
{
    friend void myTask::process();
public:
    EchoServer(int i,int j,string str,int n)
        : _threadpool(i,j)
          , _server(str,n)
    {
        Configuration conf("../conf/conf");
        _wordQue = new WordQuery(conf);
        _wordQue->loadLibrary();
    }
    void onConnection(const TcpConnectionPtr & conn);
    void onMessage(const TcpConnectionPtr & conn);
    void onClose(const TcpConnectionPtr & conn);

    void start();
    void stop();

    void process();//业务逻辑的处理

private:
    Threadpool _threadpool;
    TcpServer _server;
    WordQuery *_wordQue;
};

//回调函数体现了扩展性
void EchoServer::onConnection(const ll::TcpConnectionPtr & conn)
{
    cout << conn->toString() << " has connected!" << endl;
    /* conn->send("welcome to server."); */
}

void EchoServer::onMessage(const ll::TcpConnectionPtr & conn)
{
    cout << "onMessage...." << endl;
    string msg = conn->receive();
    cout << ">> receive msg from client: " << msg << endl;
    //::sleep(2);//碰到需要长时间的处理时，响应速度会降下来
    //conn->send(msg); /* Task task(msg, conn)
    myTask task(msg,_threadpool,*_wordQue,conn);
    _threadpool.addTask(std::bind(&myTask::process,task));
}

void EchoServer::onClose(const ll::TcpConnectionPtr & conn)
{
    cout << "onClose...." << endl;
    cout << conn->toString() << " has closed!" << endl;
}

void EchoServer::start()
{
    int * test = new int();
    _threadpool.start();
    _server.setConnectionCallback(std::bind(&EchoServer::onConnection,this,std::placeholders::_1));
    _server.setMessageCallback(bind(&EchoServer::onMessage,this,placeholders::_1));
    _server.setCloseCallback(bind(&EchoServer::onClose,this,placeholders::_1));
    cout << "-----------服务器已开启------------" << endl;
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
    ll::EchoServer test(4,4,"192.168.204.135",8888);
    test.start();

    /* server.start(); */
    return 0;
}
#endif
