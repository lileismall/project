#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <memory>


using namespace std;
using line_no = vector<string>::size_type;

class QueryResult
{
    friend ostream &print(ostream &os,const QueryResult &);
public:
    QueryResult(string s,
                shared_ptr<set<line_no>> p,
                shared_ptr<vector<string>> f)
    : sought(s)
    , lines(p)
    , file(f)
    {}
    
    set<line_no>::iterator mybegin()
    {
        return lines->begin();
    }

    set<line_no>::iterator myend()
    {
        return lines->end();
    }

    shared_ptr<vector<string>> get_file()
    {
        return file;
    }

private:
    string sought;
    shared_ptr<set<line_no>> lines;
    shared_ptr<vector<string>> file;


};

class TextQuery
{
public:
    TextQuery(ifstream &is);
    QueryResult query(const string &)const;
private:
    shared_ptr<vector<string>> file;
    map<string,shared_ptr<set<line_no>>> wm;
};
