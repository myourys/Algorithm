/*=============================================================================
#     FileName: BsTree.cpp
#         Desc: 二叉查找树C++实现
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2015-01-09 18:55:06
#      History:
=============================================================================*/
#include<iostream>
using namespace std;

/*
 * 二叉查找树,左子树总是小于根节点,右子树总是大于根节点
 * 查找: 沿着树查找节点，比节点小往左，比节点大往右，最后查找的位置即为插入点
 * 删除: 1.如果无左子树，接右子树（无右子树反之） 2.如果有左右子树，找到左子树最大，或者右子树最小节点当做替代节点
 */

template<class T>
struct BsTreeNode
{
    T key;
    BsTreeNode *lchild = nullptr;
    BsTreeNode *rchild = nullptr;
};

template<class T>
class BsTree
{
    public:
    typedef BsTreeNode<T> Node;

    BsTree():root(nullptr){};
    ~BsTree(){destroy(root);};

    Node* insert(T key);
    bool erase(T key){return erase(key,root);};
    Node* find(T key){return find(key,root);};
    void visitInOrder(void (*func)(Node*)){visitInOrder(root,func);}; //中序遍历
private:
    void destroy(Node *&node);
    Node* find(T key,Node *node);
    bool erase(T key,Node* &node);
    Node* findInsertFather(T key,Node *node);
    void visitInOrder(Node* node,void (*func)(Node*)); //中序遍历
public:
    Node *root;
};

template<class T>
void BsTree<T>::destroy(Node* &node)
{
    if(node)
    {
        destroy(node->lchild);
        destroy(node->rchild);
        delete node;
        node = nullptr;
    }
}

template<class T>
BsTreeNode<T>* BsTree<T>::find(T key,Node *node)
{
    if(node == nullptr || node->key == key)
        return node;

    if(key < node->key)
        return find(key,node->lchild);
    else
        return find(key,node->rchild);
}

template<class T>
BsTreeNode<T>* BsTree<T>::findInsertFather(T key,Node *node)
{
    if(node->key == key) //error
    {
        return nullptr;
    }
    else if(key < node->key)
    {
        if(node->lchild == nullptr)
            return node;
        else
            return findInsertFather(key,node->lchild);
    }
    else
    {
        if(node->rchild == nullptr)
            return node;
        else
            return findInsertFather(key,node->rchild);
    }
}

template<class T>
BsTreeNode<T>* BsTree<T>::insert(T key)
{
    Node* father = nullptr;
    if(root)
    {
        father = findInsertFather(key,root);
    }

    if(root && !father) // key exist
        return nullptr;

    Node* node = new Node();
    node->key = key;

    if(!root)
    {
        root = node;
    }
    else
    {
        if(key < father->key)
            father->lchild = node;
        else
            father->rchild = node;
    }

    return node;
}

template<class T>
bool BsTree<T>::erase(T key,Node* &node)
{
    if(!node)
        return false;

    if(key < node->key)
        return erase(key,node->lchild);
    else if(key > node->key)
        return erase(key,node->rchild);

    // key == node->key
    Node* preDel = node;

    if(!node->lchild)
        node = node->rchild;
    else if(!node->rchild)
        node = node->lchild;
    else
    {
        // 找到右子树的最小节点
        Node* minNode = node->rchild;
        Node* father = node;
        while(minNode->lchild)
        {
            father = minNode;
            minNode = minNode->lchild;
        }
        father->lchild = minNode->rchild; // 自己用其右子树替代

        minNode->lchild = preDel->lchild;
        minNode->rchild = preDel->rchild;

        node = minNode;
    }

    delete preDel;
    return true;
}

template<class T>
void  BsTree<T>::visitInOrder(Node* node,void (*func)(Node*)) //中序遍历
{
    if(node)
    {
        visitInOrder(node->lchild,func);
        func(node);
        visitInOrder(node->rchild,func);
    }
}


template<class T>
void display(BsTreeNode<T>* node)
{
    cout<<node->key<<" ";
}

int main()
{
    BsTree<int> tree;

	int t[]={5,9,1,0,4,8,7,3,2,6};
    for(int i = 0;i<10;i++)
        tree.insert(t[i]);
    tree.visitInOrder(display);

    cout<<endl;
    tree.erase(0);
    tree.visitInOrder(display);

    cout<<endl;
    tree.erase(5);
    tree.visitInOrder(display);

    cout<<endl;
    tree.erase(4);
    tree.visitInOrder(display);

    return 0;
}
