#include <iostream>


#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>



using namespace log4cpp;
using namespace std;

int main()
{
    //设置格式
    PatternLayout * pthLaout1 = new PatternLayout();
    pthLaout1->setConversionPattern("%d [%p] %m%n");

    PatternLayout * pthLaout2 = new PatternLayout();
    pthLaout2->setConversionPattern("%d [%p] %m%n");
    
    PatternLayout * pthLaout3 = new PatternLayout();
    pthLaout3->setConversionPattern("%d [%p] %m%n");

    OstreamAppender * ostr = new OstreamAppender("OstreamAppender",&cout);
    ostr->setLayout(pthLaout1);
    
    FileAppender * fstr = new FileAppender("FileAppender","file.log");
    fstr->setLayout(pthLaout2);

    RollingFileAppender *rstr = new RollingFileAppender("RollingFileAppender","rolling.log",
                                                        5*1024,
                                                        2);
    rstr->setLayout(pthLaout3);
    
    Category & root = Category::getRoot();  //日志记录器

    //设置输出源
    root.setAppender(ostr); 
    root.setAppender(fstr);
    root.setAppender(rstr);

    root.setPriority(Priority::DEBUG);

    //设置记录器的级别
    int cnt=100;
    while(cnt--)
    {
        root.alert("alert message");
        root.crit("crit message");
        root.debug("debug message");
        root.error("error message");
        root.info("info message");
        root .fatal("fatal message");
        root.warn("warn message");
    }

    Category::shutdown(); // 回收资源


    return 0;

}

