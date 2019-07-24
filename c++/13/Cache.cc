
#include <iostream>
#include <deque>
#include <list>
#include <unordered_map>

using namespace std;
class LRUCcache {
public:
    LRUCcache(int capacity) : _capacity(capacity)
    {
               
    }
        
    int get(int key) 
    {
        for(auto &s : _listp)
        {
            if(s.first == key)
            {
                int v = s.second;
                _listp.insert(_listp.begin(),make_pair(key,v));
                /* _listp.erase(_unm[key]); */
                /* _listp.push_front(make_pair(key,v)); */
                _unm[key] = _listp.begin();
                return s.second;
            }
        }
        return -1;
    }
        
    void put(int key, int value) 
    {
        if(_cnt < _capacity)
        {
            _cnt++;
        }else{
            _listp.pop_back();
        }
        _listp.push_front(make_pair(key,value));
        _unm[key] = _listp.begin();
    }
        
    void print()
    {
        for(auto &s : _listp)
        {
            cout << s.first << "-->" << s.second <<endl;
        }
    }
private:
    list<pair<int,int>> _listp;
    unordered_map<int,list<pair<int,int>>::iterator> _unm; //存放每个key在单链表中的位置
    int _capacity;
    int _cnt=0;
            
};

/**
 *  * Your LRUCache object will be instantiated and called as such:
 *   * LRUCache* obj = new LRUCache(capacity);
 *    * int param_1 = obj->get(key);
 *     * obj->put(key,value);
 *      */
int main()
{
    LRUCcache test(2);
    test.put(1,1);
    test.put(2,2);
    test.put(3,3);
    cout<<test.get(2)<<endl;
    test.put(4,4);
    test.print();
    return 0;
}

