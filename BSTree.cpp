#include<iostream>
using namespace std; 
#include <stdlib.h>

/*
 * 二叉查找树
 */

/*
 * 树节点
 */
template <class T>
struct BiTree
{
    BiTree()
    {
        lchild=NULL;
        rchild=NULL;
    }
    T key;
    BiTree *lchild,*rchild;
};

/* 搜索
 * node 返回搜索的节点，没找到则返回最后的查找节点
 */
template <class T>
bool SearchBST(BiTree<T>* &root, T key, BiTree<T>* &node)
{
  node=root;
	if (!root) //根节点为空
		return false;

	if (key == root->key) //查找成功
        return true;

    if (key < root->key && root->lchild) //在左子树中继续查找
        return SearchBST(root->lchild, key, node);

    if (key > root->key && root->rchild)//右子树继续查找
        return SearchBST(root->rchild, key, node);

	return false;
}

template <class T>
bool InsertBST(BiTree<T>* &root,T key)
{
    BiTree<T>* p;
    if(SearchBST(root,key,p)) //找到了，不满足二叉排序树规则则退出
        return false;

    BiTree<T>* s = new BiTree<T>;
    s->key = key;
    if(!p)
        root = s;
    else if (p->key > s->key)
        p->lchild = s;
    else
        p->rchild = s;
    return true;
}

template <class T>
void InROrderBST(BiTree<T>* root)
{
    if(root)
    {
        InROrderBST(root->lchild);
        cout<<root->key<<endl;
        InROrderBST(root->rchild);
    }
}


int main()
{
    BiTree<int>* root=NULL;
    int i,t;
    for(i=0;i<10;i++)
	{
		t = 1+rand()%1000;
		cout<<t<<endl;
        InsertBST(root,t);
	}

	cout<<"\nInROrderBST:"<<endl;
    InROrderBST(root);

    return 0;
}



