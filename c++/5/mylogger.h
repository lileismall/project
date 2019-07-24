#include <iostream>

#include <string.h>

#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>



using namespace log4cpp;


class Mylogger
{
public:

    static Mylogger *getInstance()
    {
        if(_pInstance==NULL)
        {
            _pInstance=new Mylogger();
        }
        return _pInstance;
    }

    static void destroy()
    {
        if(_pInstance)
        {
            delete _pInstance;
        }
    }
    //c++中不能用字符串作为switch的参数
    void mysetPriority(const char *priority);  //设置日志级别

    void warn(const char * msg);
    void error(const char * msg);
    void debug(const char * msg);
    void info(const char * msg);

private:
    Mylogger();//析构函数私有化
    ~Mylogger()
    {
        Category::shutdown();
    }
    
private:
    static Mylogger *_pInstance;

    PatternLayout *_pthLaout1;
    PatternLayout *_pthLaout2;

    OstreamAppender *_ostr;
    RollingFileAppender *_rstr;

    Category & _root = Category::getRoot();

    int _priority = Priority::DEBUG;  //默认级别为DEBUG,可以通过setPriority设置
};
