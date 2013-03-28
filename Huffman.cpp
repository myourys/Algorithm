/*
 * 霍夫曼编码（Huffman Coding）是一种编码方式，是一种用于无损数据压缩的熵编码（权编码）算法。
 */
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
//#include <stdlib.h>
using namespace std; 

typedef map<char,unsigned int> SymbolCount;
typedef map<char,string> HuffmanCode;

struct Node
{
    unsigned key;
    char symbol;
    Node* lchild;
    Node* rchild;

    Node(char s,unsigned f){
        symbol = s;
        key= f;
        lchild =NULL;
        rchild =NULL;
    }

    Node(Node* l,Node* r)
    {
        symbol = 0;
        key = l->key + r->key;
        lchild = l;
        rchild = r;
    }

    bool leaf() const //是否叶子
    {
        return lchild == NULL && rchild ==NULL;
    }

    bool operator <(Node &other)
    {
        return (*this).key > other.key;
    }

};

struct DereferenceLess
{
    template <typename T>
    bool operator ()(T& p1, T& p2) const
    {
        return *p1 < *p2;
    }
};

/*
 * 统计每个字符出现次数，用Map存放
 */
void CountSymbols(SymbolCount& freq_table,istream& s)
{
    while(1)
    {
        char c(s.get());
        if (s.eof())
            break;
        freq_table[c]++;
    }
}

/*
 * 打印Huffman树
 */
void PrintHuffmanTree(Node *node,unsigned int depth = 0)
{
    if (node == NULL)
        return;
    string indent(4 * depth,' ');
    if (node->leaf())
        cout << indent<<node->symbol<<" ("<<node->key<<")"<<endl;
    else
        cout << indent << '*' << " (" << node->key<< ")"<<endl;

    PrintHuffmanTree(node->lchild,depth+1);
    PrintHuffmanTree(node->rchild,depth+1);
}

Node *CreateHuffmanTree(vector<Node>& leaves)
{
    /* 
     * 优先队列存放节点，用于辅助建树
     * 参考 http://www.cplusplus.com/reference/queue/priority_queue/
     */
    typedef priority_queue<Node*,vector<Node*>,DereferenceLess> NodePtrQueue;
    NodePtrQueue nodes;

    vector<Node>::iterator p;
    for (p = leaves.begin();p!= leaves.end();++p;)
        nodes.push(&(*p));

    while(nodes.size()>1)
    {
        Node *first = nodes.top();
        node.pop();
        Node *second = nodes.top();
        nodes.pop();
        Node *combined_node = new Node(first,second);
}


int main()
{
    cout<<"Hello world!";
    return 0;
}
