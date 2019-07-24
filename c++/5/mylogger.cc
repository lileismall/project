#include "mylogger.h"



using namespace log4cpp;
using namespace std;

Mylogger *Mylogger::_pInstance=NULL;

int main()
{
   Mylogger *test = Mylogger::getInstance();
   test->mysetPriority("INFO");//目前可以设置为ERROR，INFO，DEBUG,  默认为INFO
   test->warn("this is warn messages");
   test->error("this is error messages");
   test->info("this is info messages");
   test->debug("this is debug message");
   return 0;
}

