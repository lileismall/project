#include "Dictionary.h"




using namespace std;
using std::ifstream;
#define KK 0

//将文件里的内容读到容器里
//
#ifdef KK 
void Dictionary::read(const string & filename)
{
    ifstream ifs(filename);
    if(!ifs.good())
    {
        cout << "open error " << endl;
    }
    string str;
    string word;
    while(getline(ifs,str))
    {
        stringstream line(str);
        while(line >> word)
        {
            _vec.push_back(word);
        }
    }
}
#endif

void Dictionary::rread(const string & filename)
{
    ifstream ifs(filename);
    if(!ifs.good())
    {
        cout << "open error " << endl;
    }
    string str;
    string word;
    while(getline(ifs,str))
    {
       istringstream line(str); 
       while(line >> word)
       {
           if(word[word.length()-1] < 'a' |word[word.length()-1] > 'z')
           {
               word[word.length()-1]='\0';
           }
            _mapp[word]++;
       }
    }
}

void Dictionary::print()
{
    for(const auto &w : _mapp)
    {
        if(w.second > 1000)
        cout << w.first << ": " << w.second <<endl;
    }
}

void Dictionary::store(const string & filename)
{
    ofstream ofs(filename);
    string ss;
    for(const auto &w : _mapp)
    {
        stringstream str;
        str << w.first <<" : " << w.second << endl;
        cout << str.str() << endl;
        ofs << str.str();

    }
}

//void adjustDown(map<string,size_t> a,int parent,int size)
//{
//    int child = parent * 2 + 1;
//    while(child < size)
//    {
//        if(child + 1 <size && a.s)
//    }
//}

