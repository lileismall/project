#include "Dictionary.h"



using namespace std;
using std::ifstream;
#define KK 1

//将文件里的内容读到容器里
//
#if KK 
void Dictionary::read(const string & filename)
{
    ifstream ifs(filename);
    if(!ifs.good())
    {
        cout << "open error " << endl;
    }
    string str;
    string word;
    size_t i;
    while(getline(ifs,str))
    {
        /* std::regex re("[0-9,;:.\[]\()]"); */
        /* string sstr =regex_replace(str,re," "); */
        for(i=0;i < str.size();i++)
        {
            if(str[i] > 'a' && str[i] < 'z')
            {
                continue;
            }else if(str[i] >'A' && str[i] <'Z')
            {
                str[i] = str[i] + 32;
                continue;
            }
            str[i] = ' ';
        }
        stringstream line(str);
        while(line >> word)
        {
            /* _vec.push_back(str); */
            /* _mapp[word]++; */
            _unmapp[word]++;
        }
    }

    //ofstream os("file");
    //for(auto &s : _vec)
    //{
    //    os << s <<endl;
    //}
}
#endif
#if 0
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
#endif

#if 0
void Dictionary::print()
{
    for(const auto &w : _mapp)
    {
        if(w.second > 1000)
        cout << w.first << ": " << w.second <<endl;
    }
}
#endif
void Dictionary::print()
{
    for(const auto &str : _vec)
        cout << str << endl;
}

void Dictionary::store(const string & filename)
{
    ofstream ofs(filename);
    string ss;
    for(const auto &w : _unmapp)
    {
        stringstream str;
        str << w.first <<" : " << w.second << endl;
        /* cout << str.str() << endl; */
        ofs << str.str();

    }
}

int main()
{
    Dictionary test;
    test.read("The_Holy_Bible.txt");
    test.store("file");

    /* test.print(); */
    
}
