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
#include <algorithm>


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

class Query_base
{
public:
    friend class Query;
protected:
    virtual ~Query_base() = default;

private:
    virtual QueryResult eval(const TextQuery &) const = 0;
    virtual string rep() const = 0;
};

class Query :public Query_base
{
    friend Query operator~(const Query &);
    friend Query operator&(const Query &,const Query &);
    friend Query operator|(const Query &,const Query &);
public:
    Query(const string&);//why
    QueryResult eval(const TextQuery &t) const //why  交给WordQuery去做
    {
        return q->eval(t);
    }
    string rep() const
    {
        return q->rep();
    }

private:
    Query(shared_ptr<Query_base> query) : q(query) {} //什么时候执行这个析构函数 解答：在运算符的return语句中
    shared_ptr<Query_base> q;
};
//Qurey的输出运算符
ostream &operator<<(ostream &os,Query &query) //因为没有使用到Query的私有成员，所以不用是Query的有元
{
    return os << query.rep();
}

class WordQuery:public Query_base
{
    friend class Query;
    WordQuery(const string &s):query_word(s) {}
    
    QueryResult eval(const TextQuery &t) const
    {
        return t.query(query_word);
    }
    string rep() const { return query_word; }
    string query_word;
};

inline Query::Query(const string &s) : q(new WordQuery(s)) {} 

class NotQuery: public Query_base
{
    friend Query operator~(const Query &);
    NotQuery(const Query &q): query(q) {}

    QueryResult eval(const TextQuery&) const;
    string rep() const { return "~(" + query.rep() + ")"; }
    Query query;
};

inline Query operator~(const Query &operand)
{
    return shared_ptr<Query_base>(new NotQuery(operand));
}

QueryResult NotQuery::eval(const TextQuery &text) const 
{
    auto result = query.eval(text);  //执行的是Query中的eval，
    auto ret_lines = make_shared<set<line_no>> ();
    auto beg = result.mybegin(),end = result.myend();
    auto sz = result.get_file()->size();

    for(size_t n = 0;n != sz; ++n)
    {
        if(beg == end || *beg != n)
        {
            ret_lines->insert(n);
        }else if(beg != end){
            ++beg;
        }
    }

    return QueryResult(rep(),ret_lines,result.get_file());
}

class BinaryQuery:public Query_base
{
protected:
    BinaryQuery(const Query &left,const Query &right,string s)
        : lhs(left)
        , rhs(right)
        , opSym(s)
    {}

    string rep() const
    {
        return "(" + lhs.rep() + " " + opSym
            +" " + rhs.rep() + ")";
    }

    Query lhs,rhs;
    string opSym;
};

class AndQuery:public BinaryQuery
{
    friend Query operator&(const Query&,const Query&);

    AndQuery(const Query &left,const Query &right)
        : BinaryQuery(left,right,"&")
    {}

    QueryResult eval(const TextQuery &) const;

    //rep()继承BinaryQuery的
};

inline Query operator&(const Query &lhs,const Query &rhs)
{
    return shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}

QueryResult AndQuery::eval(const TextQuery &text) const
{
    auto left = lhs.eval(text),right = rhs.eval(text);
    auto ret_lines = make_shared<set<line_no>>();

    set_intersection(left.mybegin(),left.myend(),
                     right.mybegin(),right.myend(),
                     inserter(*ret_lines,ret_lines->begin()));

    return QueryResult(rep(),ret_lines,right.get_file());
}





