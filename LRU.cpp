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
/*
 * 这里采用Hash_Map + 双向链表的数据结构，map便于查找
 */
#include <iostream>

using namespace std;

/*
 * 双向链表存储节点,将最近使用Node的永远放在表头，则最久未使用的就在表尾
 */
template<class K,class V>
struct Node
{
    K key;
    V data;
    Node *prev,*next;
};

int main()
{
    cout<<"LRU"<<endl;
    return 0;
}
