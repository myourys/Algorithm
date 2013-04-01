/*=============================================================================
#     FileName: BSTree.cpp
#         Desc: 二叉查找树
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2013-04-01 23:51:03
#      History:
=============================================================================*/
#include<iostream>
using namespace std;
#include <stdlib.h>

/*
 * 二叉查找树,左子树总是小时根节点,右子树总是大于根节点
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
bool DeleteBST(BiTree<T>* &root,T key)
{
	if(!root)
		return false;

	if(key < root->key)
		return DeleteBST(root->lchild,key);
	else if (key >root->key)
		return DeleteBST(root->rchild,key);
	else
	{
		BiTree<T>* my=root;
		if(!root->lchild) //左子树为空，只需右接右子树
			root=root->rchild;
		else if (!root->rchild)
			root=root->lchild;
		else
		{
			BiTree<T>* p=root->lchild;
			BiTree<T>* fa=root;
			while(p->rchild) //找到左子树最大值 放到删除的节点中当做新的节点
			{
				fa=p;
				p=p->rchild;
			}
			fa->rchild = p->lchild;
			root = p;
			root->lchild = my->lchild;
			root->rchild = my->rchild;
		}
		delete my;
	}
	return true;
}

template <class T>
void DestroyBST( BiTree<T>* &root )
{
    if ( root != NULL )
    {
        DestroyBST( root->lchild );
        DestroyBST( root->rchild );
        delete root;
    }
}

template <class T>
void InROrderBST(BiTree<T>* root)
{
    if(root)
    {
        InROrderBST(root->lchild);
        cout<<root->key<<"  ";
        InROrderBST(root->rchild);
    }
}



int main()
{
    BiTree<int>* root=NULL;
    int i;
	int t[]={5,9,1,0,4,8,7,3,2,6};
    for(i=0;i<10;i++)
        InsertBST(root,t[i]);

	cout<<"InROrderBST:"<<endl;
    InROrderBST(root);

	DeleteBST(root,0);
	cout<<"\nDelete [0] InROrderBST:"<<endl;
    InROrderBST(root);

	DeleteBST(root,5);
	cout<<"\nDelete [5] InROrderBST:"<<endl;
    InROrderBST(root);

	DeleteBST(root,7);
	cout<<"\nDelete [7] InROrderBST:"<<endl;
    InROrderBST(root);

	DestroyBST(root);
    return 0;
}
