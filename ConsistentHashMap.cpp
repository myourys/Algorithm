/*=============================================================================
#     FileName: ConsistentHashMap.cpp
#         Desc: 一致性hash算法的实现
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2015-01-18 23:49:07
#      History:
=============================================================================*/
/*
 * 一致性Hash算法
 * 一般用作在分布式集群中，要把请求分散到不同的物理机器上，同时要保证服务器在删除（宕机）、添加时，尽量的减少原有的请求的迁移数
 * 一致性Hash的实现起来也很简单：
 * 1. 用Hash算法，将Hash的值域当做一个封闭的环，这样可以所有的物理机器分散的映射到这个环上
 * 2. 请求也运用这个Hash函数得到环上的一个点，顺时针就找到最近的物理机器
 * 3. 当有机器删除或添加时，只有这个机器在环上的前一些请求需要迁移
 *
 * 但是这样有个问题，就是当有机器宕机时,其所有的请求就到了环上的下一个节点上去了,解决办法也很简单:
 * 1. 将一台物理机器加一个编号之类的变成很多个虚拟机器，这些虚拟机器映射到环上
 * 2. 这样需要迁移的请求几乎会均匀分布在其他机器上
 */

#include <iostream>
#include <map>
#include <vector>
#include <array>
#include <sstream>
#include <ctime>

using namespace std;


/*
 * 一致性Hash
 * 1. 存储采用stl::map,其内部采用红黑树，是有序存储的，在保证效率和动态扩展的同时，保证查找效率在log(n)
 * 2. 此类相当简单,仅仅提供基本的一致性Hash算法的接口，基本就是调用map的方法
 */

template<typename Node, //虚拟服务器节点
    typename Hash, //Hash的彷函数，其返回值用来当做map的key
    typename Alloc = allocator<pair<const typename Hash::result_type,Node> > >
class ConsistentHashMap
{
public:
    typedef typename Hash::result_type MapKey;
    typedef map<MapKey,Node,less<MapKey>,Alloc> Map;
    typedef typename Map::iterator iterator;
    typedef typename Map::value_type value_type;

    pair<iterator,bool> insert(const Node &node)
    {
        return nodes.insert(value_type(hasher(node),node));
    }

    iterator erase(const Node &node)
    {
        return nodes.erase(value_type(hasher(node),node));
    }

    iterator erase(MapKey key)
    {
        auto iter = nodes.find(key);
        if(iter == nodes.end())
            return nodes.end();
        return nodes.erase(iter);
    }

    iterator find(const MapKey &key)
    {
        //lower_bound()返回一个 不小于 key 的 iterator
        auto iter = nodes.lower_bound(key);
        if(iter == nodes.end()) //如果是环尾,则返回环头
            iter = nodes.begin();
        return iter;
    }

    size_t size(){return nodes.size();}

    bool empty() { return nodes.empty(); }

    iterator begin() { return nodes.begin(); }

    iterator end() { return nodes.end(); }

private:
    Map nodes;
    Hash hasher;
};

/*
 * 服务器Hash类
 * 一个简单的例子,用来测试我们的一致性Hash类，同时稍稍改动也可作为在实际项目中使用
 *
 * 1. 设计成一个简单的单例类,方便项目全局使用
 * 2. Hash算法就直接调用了stl:hash<string>的算法
 */

/* 服务器节点 */
struct ServerNode
{
    const string name;
};

class ServerHash
{
public:
    //虚拟节点
    struct VNode
    {
        const size_t serialNo; //序号
        const ServerNode* realNode; //真实的服务器节点
    };

    struct Hash
    {
        typedef typename hash<string>::result_type result_type;
        result_type operator()(const VNode &vnode)
        {
            ostringstream vname;
            vname<< vnode.realNode->name << "#" << vnode.serialNo;
            return hash<string>()(vname.str());
        }
    };

    void insert(const ServerNode &node)
    {
        auto iter = nodesMap.insert(make_pair(node.name,node));
        for(size_t i=0;i<vnodeSize;++i)
        {
            chMap.insert(VNode{i,&iter.first->second});
        }
    }

    void erase(const string &serverName)
    {
        auto iter = nodesMap.find(serverName);
        if(iter == nodesMap.end())
            return;

        for(size_t i=0;i<vnodeSize;++i)
        {
            VNode vnode{i,&iter->second};
            chMap.erase(Hash()(vnode));
        }
    }


    const ServerNode* operator[](const string &request)
    {
        auto iter = chMap.find(hash<string>()(request));
        if(iter == chMap.end())
            return nullptr;
        return iter->second.realNode;
    }

    ServerHash(size_t _vnodeSize):vnodeSize(_vnodeSize)
    {
    };
private:
    map<string,ServerNode> nodesMap;
    ConsistentHashMap<VNode,Hash> chMap;
    const size_t vnodeSize;
};

int main()
{
    string sers[6] = {
        "192.168.1.100",
        "192.168.1.101",
        "192.168.1.102",
        "192.168.1.103",
        "192.168.1.104",
        "192.168.1.105"
    };
    ServerHash servers(100);
    for(auto iter:sers)
        servers.insert({iter});

    cout<<"resquest location:"<<endl;
    cout<<servers["www.google.com"]->name<<endl;
    cout<<servers["www.facebook.com"]->name<<endl;
    cout<<servers["www.twitter.com"]->name<<endl;
    cout<<servers["www.godaddy.com"]->name<<endl;
    cout<<servers["www.name.com"]->name<<endl;
    cout<<servers["www.sex.com"]->name<<endl;

    servers.erase(sers[3]);
    cout<<"after erase resquest location:"<<endl;

    cout<<servers["www.google.com"]->name<<endl;
    cout<<servers["www.facebook.com"]->name<<endl;
    cout<<servers["www.twitter.com"]->name<<endl;
    cout<<servers["www.godaddy.com"]->name<<endl;
    cout<<servers["www.name.com"]->name<<endl;
    cout<<servers["www.sex.com"]->name<<endl;

    servers.insert({sers[3]});
    cout<<"add back resquest location:"<<endl;

    cout<<servers["www.google.com"]->name<<endl;
    cout<<servers["www.facebook.com"]->name<<endl;
    cout<<servers["www.twitter.com"]->name<<endl;
    cout<<servers["www.godaddy.com"]->name<<endl;
    cout<<servers["www.name.com"]->name<<endl;
    cout<<servers["www.sex.com"]->name<<endl;


    /* rand test */
    const int reqSize = 100*1000;
    array<string,reqSize> reqs;
    for(int i=0;i<reqs.size(); ++i)
    {
        ostringstream ss;
        ss<<i* (rand()%10 + 1);
        reqs[i] = ss.str();
    }

    int nums[6] = {0};

	clock_t ibegin, iend;
	ibegin = clock();
    for(auto req:reqs)
    {
        servers[req];
    }
    iend = clock();

    cout<<"find "<<reqSize <<" resqust cost "<<iend - ibegin<< " milliseconds"<<endl;

    for(auto req:reqs)
    {
        const string &s = servers[req]->name;
        for(int i = 0;i<6;++i)
            if(s.compare(sers[i])==0)
            {
                nums[i] += 1;
                break;
            }
    }

    for(int i = 0;i<6;++i)
        cout<<nums[i]<<"  ";
    cout<<endl;

    return 0;
}
