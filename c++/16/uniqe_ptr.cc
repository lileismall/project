
#include <iostream>
#include <memory>
#include <string.h>

using namespace std;

class FileClose
{
    void operator()(FILE *fp)
    {
        if(fp)
        {
            fclose(fp);
            cout << "this is close(fp)" << endl;
        }
    }
        
};

int main()
{
    unique_ptr<FILE,FileClose> up(fopen("test.txt","aw+"));
    char str[10] = "hello";
    fwrite(str,strlen(str),1,up.get());
}

