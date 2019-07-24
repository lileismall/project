
#include <iostream>
#include <queue>
#include <map>
#include <deque>

using namespace std;
class LRUCache {
private:
    int _capacity;
    map<int,int> _mmap;
    deque<int,int> _deq;
public:
    LRUCache(int capacity)  : _capacity(capacity)
    {}
    int get(int key)
    {
        for(auto &s : _deq) 
        {
            if(s.first == key)
            {
                return s.second;
            }
        }
        return -1;
    }

    void put(int key, int value) 
    {
        if(_deq.size() < _capacity)
        {
            _deq.push(key,value);
        }else{
            _deq.pop_front();
            _deq.push(key,value);
        }
    }
};
int main()
{
    LRUCache test;
    test.put(1,2);
}

