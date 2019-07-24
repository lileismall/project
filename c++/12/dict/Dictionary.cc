#include "Dictionary.h" 


using namespace std;


int main()
{
    Dictionary dict;
    dict.read("The_Holy_Bible.txt");

    dict.store("tt.txt");
    dict.print();
    return 0;
}

