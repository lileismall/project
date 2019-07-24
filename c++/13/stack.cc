
#include <iostream>
#include <stack>

using namespace std;
class Solution {
public:
    bool isValid(string s) 
    {
        stack<char> test;
        for(size_t i=0;i<s.size();i++)
        {
            if(s[i]=='('|s[i]=='['|s[i]=='{')
            {
                test.push(s[i]);
            }else if(s[i]==')'){
                if(test.top() == '(')
                {
                    test.pop();
                }else{
                    return false;
                }
            }else if(s[i]==']'){
                if(test.top()=='[')
                {
                    test.pop();
                }else{
                    return false;
                }
            }else if(s[i]=='}'){
                if(test.top()=='{')
                {
                    test.pop();
                }else{
                    return false;
                }
            }
        }
        return true;
    }
};
int main()
{
    Solution test;    
    cout << "是否有效: " << test.isValid(string("{()[}")) << endl;

}

