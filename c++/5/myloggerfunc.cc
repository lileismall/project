#include "mylogger.h"




using namespace log4cpp;
using namespace std;


Mylogger::Mylogger()
    : _pthLaout1(new PatternLayout())
    , _pthLaout2(new PatternLayout())
    , _ostr(new OstreamAppender("OstreamAppender",&cout))
    , _rstr(new RollingFileAppender("RollingFileAppender",
                                    "rolling.log",
                                    5*1024,
                                    2))
{
    _pthLaout1->setConversionPattern("%d [%p] %m%n");
    _pthLaout2->setConversionPattern("%d [%p] %m%n");

    _ostr->setLayout(_pthLaout1);
    _rstr->setLayout(_pthLaout2);

    //Category &root = Category::getRoot();

    _root.setAppender(_ostr);
    _root.setAppender(_rstr);
    
    //_root.setPriority(_priority);  //想法变成可设置的
    //如果想自己设置日志级别，就不能放在构造函数里
}

void Mylogger::mysetPriority(const char *priority)
{
    //c++中字符串不能作为switch的参数
    if(!strcmp(priority,"DEBUG"))
    {
        _priority = Priority::DEBUG;
    }
    
    else if(!strcmp(priority,"INFO"))
    {
        _priority = Priority::INFO;
    }
    else if(!strcmp(priority,"ERROR"))
    {
        _priority = Priority::ERROR;
    }
    _root.setPriority(_priority);
    return ;
}

void Mylogger::warn(const char *msg)
{
   _root.warn(msg);
   return ;
}

void Mylogger::error(const char *msg)
{
   _root.error(msg);
   return ;
}

void Mylogger::debug(const char *msg)
{
   _root.debug(msg);
   return ;
}

void Mylogger::info(const char *msg)
{
   _root.info(msg);
   return ;
}




