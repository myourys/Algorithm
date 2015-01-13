/*=============================================================================
#     FileName: Trie.cpp
#         Desc: 单词前缀树的基本实现
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2013-03-25 23:32:48
#      History:
=============================================================================*/
/*
 * 经常用来前缀单词的查找
 * 插入、查找的复杂度均为O(len),len为字符串长度
 */

#include<iostream>
using namespace std;

#define kCharNum 26  /* 代表26个英文字母 */

struct TrieNode
{
    bool isStr; //是否句尾
    TrieNode *childs[kCharNum]; // 共26个子树
    TrieNode():isStr(false)//初始化结构体
    {
        std::memset(childs,0,sizeof(childs)); //所有孩子置为NULL
    }
};

class Trie
{
public:
    Trie();
    ~Trie();
    void insert(const char* word);
    bool search(const char* word);
    void destroy(TrieNode *p);
private:
    TrieNode *root;
};

Trie::Trie()
{
    root = new TrieNode; //根节点为空
}

void Trie::insert(const char* word)
{
    TrieNode *p=root;
    while(*word)
    {
        if(!p->childs[*word-'a'])
        {
            p->childs[*word-'a']=new TrieNode;
        }
        p=p->childs[*word-'a'];
        word++;
    }
    p->isStr= true;
}

bool Trie::search(const char * word)
{
    TrieNode *p=root;
    while(*word)
    {
        if(!p->childs[*word-'a'])
            return false;
        p=p->childs[*word-'a'];
        word++;
    }
    if(!p->isStr)
        return false;
    else
        return true;
}

void Trie::destroy(TrieNode *p)
{
    for(int i=0;i<kCharNum;i++)
    {
        if(p->childs[i])
            destroy(p->childs[i]);
    }
    delete p;
}
Trie::~Trie()
{
    if(root)
        destroy(root);
}


int main()
{
    Trie t;
    t.insert("a");
    t.insert("abcdefg");
    const char *c = "abcdlkk";
    t.insert(c);
    t.insert("abcdeee");
    if(t.search("abcdeee"))
        cout<<"true"<<endl;
    else
        cout<<"false"<<endl;
    return 0;
}
