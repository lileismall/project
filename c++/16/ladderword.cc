
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>

using namespace std;

class Sulution
{
    int ladderlenth(const string &begword,const string &endword,
                    const vector<string> &wordlist)
    {
        int cnt = count(wordlist.begin(),wordlist.end(),endword);
        if(!cnt)
            return 0;
        queue<string> currentque;
        queue<string> nextque;
        unordered_set<string> visited;
        int len = 1;
        currentque.push(begword);
        visited.insert(begword);
        while(!currentque.empty())
        {
            while(!currentque.empty())
            {
                string word = currentque.front();
                currentque.pop();
                
                //求下一层结点
                vector<string> nextsta;
                getnextsta(begword,wordlist,visited,nextsta);
                {

                }
            }
        }

        getnextsta(const string &begword,const vector<string> &wordlist,
                   const unordered_set<string> visited,vector<string> nextsta)
        {

        }
    }
};

int main()
{

}

