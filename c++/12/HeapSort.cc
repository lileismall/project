
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <class Type,class Compare = less<Type>>
class HeapSort
{
public:
    HeapSort() {}
    HeapSort(vector<Type> data)  
    {
        /* for(int i=0;i < n ;i++) */
        /* { */
            /* _vec.push_back(data[i]); */
        /* } */
        _vec = data;
    }

    void print()
    {
        for(auto &s : _vec)
        {
            cout << s << " ";
        }
        cout << endl;
    }
    

    void heapAdjust(vector<Type> &_vec,int len);
    void sort(vector<Type> &_vec,int len);
    void mysort()
    {
        heapAdjust(_vec,_vec.size());
        sort(_vec,_vec.size());
    }

    vector<Type> Heapset(vector<Type> &vec,int k);
private:
    void max_heapify(vector<Type> &_vec,int start,int end);

    vector<Type> _vec;
};

template <class Type,class Compare>
void HeapSort<Type,Compare>::max_heapify(vector<Type> &_vec,int start,int end)
{
    int dad = start;
    int son = dad*2+1;
    while(son <= end)
    {
        if(son+1 <= end && _vec[son] < _vec[son+1])
        {
            son++;
        }
        if(_vec[dad] >= _vec[son])
        {
            break;
        }
        else
        {
            swap(_vec[son],_vec[dad]);
            /* cout << _vec[son] << "<--->" <<_vec[dad] <<endl; */ 
            dad = son;
            son = dad*2 + 1;
        }
    }
}
template <class Type,class Compare>
void HeapSort<Type,Compare>::heapAdjust(vector<Type> &_vec,int len)
{
    for(int i = len/2 -1;i >= 0;i--)
    {
        cout << __LINE__ <<endl;
        max_heapify(_vec,i,len-1);
    }
}
template <class Type,class Compare>
void HeapSort<Type,Compare>::sort(vector<Type> &_vec,int len)
{
    for(int i=len-1; i > 0;i--)
    {
        cout << __LINE__ <<endl;
            cout << _vec[0] << "<--->" <<_vec[i] <<endl; 
        swap(_vec[0],_vec[i]);
            cout << _vec[0] << "<--->" <<_vec[i] <<endl; 
        max_heapify(_vec,0,i-1);
    }
}

template <class Type,class Compare>
vector<Type> HeapSort<Type,Compare>::Heapset(vector<Type> &vec,int k)
{
    vector<Type> arr;  //用来建大跟堆
    //将vec前k个数据放进arr
    for(int i=0;i < k;i++)
    {
        arr[i] = vec[i];
    }

    /* for(int i=(k-2)/2;i >= 0;i--) */
    /* { */
        hepAdjust(arr,arr.size());
    /* } */
    for (int i = k; i < vec.size(); i++)
    {
        if (arr[0]<vec[i])
        {
            arr[0] = vec[i];
            AdjustDown(arr, 0, k);
        }
    }
    return arr;
}

int main()
{
    vector<int> a = {2,6,8,3};
    HeapSort<int> test(a);
    /* test.Heapset(a,4); */
    test.mysort();

    test.print();
}

