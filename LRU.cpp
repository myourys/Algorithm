/*=============================================================================
#     FileName: LRU.cpp
#         Desc: LRU是Least Recently Used 近期最少使用算法.
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2015-01-07 18:48:30
#      History:
=============================================================================*/

#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

/*
 * Cache算法，数据只要使用一次就放在链表的头部,这样链表尾部就是近期最少使用的数据
 *
 * 最近看了STL源码，STL在实现常见数据结构是进行了大量的优化，并更加安全，所以这里就全部用STL的容器实现
 * 1. unordered_map,内部采用的是hash算法，方便查找数据
 * 2. list,双向链表,并负责存放数据
 */

template<class K,class T>
class LRUCache
{
public:
    /* 当找不到Cache时的处理函数，一般从他处读取*/
    typedef function<T (const K)> fetch_func;

    typedef pair<const K,T> ListValue;

    typedef list<ListValue> CacheList;
    typedef unordered_map<K,typename CacheList::iterator> CacheMap;

    LRUCache(fetch_func func,size_t capacity_):
    fetchFunc(func),capacity(capacity_){};

    T& operator[](const K &key)
    {
        return get(key);
    }

    T& get(const K key)
    {
        auto v = _map.find(key);
        if(v != _map.end())
        {
            //把map中的list迭代器放在_list的最前面
            _list.splice(_list.begin(),_list,v->second);
            return v->second->second;
        }

        T data = fetchFunc(key);
        put(key,data);
        return _list.front().second;
    }

    void put(K key,T data)
    {
        if(capacity == _list.size()) //cache is full
            eraseLru();

        auto v = _map.find(key);
        if(v == _map.end())
        {
            _list.push_front(ListValue(key,data));
            _map.insert(make_pair(key,_list.begin()));
        }
        else //value exist,update data
        {
            v->second->second = data;
        }
    };

    //for test
    void display()
    {
        for(auto iter = _list.begin();iter!=_list.end();++iter)
            cout<<iter->first<<"  ";
        cout<<endl;
    }
private:
    /*删除最早未使用的*/
    void eraseLru()
    {
        if(!_list.empty())
        {
            auto v = _list.back();
            _map.erase(v.first);
            _list.pop_back();
        }
    }

private:
    const fetch_func fetchFunc;
    const size_t capacity;

    CacheMap _map;
    CacheList _list;
};

int main()
{
    LRUCache<int,string> lru(nullptr,4);
    lru.put(1,"1111111");
    lru.put(2,"2222222");
    lru.put(3,"3333333");

    lru.display();

    cout<<lru[2]<<endl;
    lru.display(); //2 3 1

    lru.put(4,"4444444");
    lru.display(); //4 2 3 1

    cout<<lru[1]<<endl; //1 4 2 3
    lru.put(5,"555555"); //5 1 4 2
    lru.display();
    return 0;
}
