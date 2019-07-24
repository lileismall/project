

#include <iostream>
#include <string>
#include <memory>
#include <vector>


using namespace std;

class QueryReslt
{
    friend ostream& print(ostream&,const QueryReslt);

public:
    QueryReslt(string s,shared_ptr<set<line_no>> p,
               shared_ptr<vector<string>>):
        
private:
        string sought;
        shared_ptr<set<line_no>> lines;
        shared_ptr<vector<string>> file;
};

int main()
{
}

