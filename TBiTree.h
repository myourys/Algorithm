/*=============================================================================
#     FileName: TBiTree.h
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 1.0.1
#   LastChange: 2013-03-23 00:36:24
#         Desc: 
#      History:
=============================================================================*/
#ifndef _BITREE_H 
#define _BITREE_H 
#include "TStack.h" 
#include "TQueue.h"

template <class DataType>
class BiTree;                                      //友元类引用申明

template <class DataType>
class TreeNode
{
TreeNode():lchild(NULL),rchild(NULL){}
friend class BiTree<DataType>;
private:
DataType data;
TreeNode *lchild,*rchild;
//bool tag;                                     //后序遍历时用的标志域
};

template <class DataType>
class BiTree{
public:
void CreateBiTree();                            //创建根节点------主过程
void CreateBiTree(TreeNode<DataType>* &p);      //创建节点函数----子过程
void PreROrderTraverse();                       //递归------先序遍历二叉树---主过程              
void PreROrderTraverse(TreeNode<DataType>* p);  //递归------先序遍历二叉树---子过程
void InROrderTraverse();                        //递归------中序遍历二叉树---主过程
void InROrderTraverse(TreeNode<DataType>* p);   //递归------中序遍历二叉树---子过程
void PosROrderTraverse();                       //递归------后序遍历二叉树---主过程
void PosROrderTraverse(TreeNode<DataType>* p);  //递归------后序遍历二叉树---子过程
void PreOrderTraverse();                        //非递归------中序遍历二叉树
void InOrderTraverse();                         //非递归------中序遍历二叉树
void PosOrderTraverse();                        //非递归------后序遍历二叉树
void LevelOrderTraverse();                      //非递归------层次遍历二叉树
protected:
TreeNode<DataType>* root;                       //树根
DataType temp;                                  //代表元素为空的符号
};

template <class DataType>
void BiTree<DataType>::CreateBiTree()
{
cout<<"请输入代表元素为空的符号:";
cin>>temp;   //若换输入方式，以上三句可以去掉
if(!(root=(TreeNode<DataType>*)malloc(sizeof(TreeNode<DataType>)))) exit(1);
cout<<"请输入数据:"<<endl;
CreateBiTree(root);
}

template <class DataType>
void BiTree<DataType>::CreateBiTree(TreeNode<DataType>* &p)
{
TreeNode<DataType>* px;
if(!(px=(TreeNode<DataType>*)malloc(sizeof(TreeNode<DataType>)))) exit(1);
cin>>px->data;
if(px->data==temp) {p=NULL;free(px);}
else{
p=px;
// p->tag=false;                                   //后序遍历时用的标志域初始化
CreateBiTree(px->lchild);
CreateBiTree(px->rchild);
}
}

template <class DataType>
void BiTree<DataType>::PreROrderTraverse()
{
PreROrderTraverse(root);
}

template <class DataType>
void BiTree<DataType>::PreROrderTraverse(TreeNode<DataType>* p)
{
if(p){
   cout<<p->data<<" ";
   PreROrderTraverse(p->lchild);
   PreROrderTraverse(p->rchild);
}
}

template <class DataType>
void BiTree<DataType>::InROrderTraverse()
{
InROrderTraverse(root);
}

template <class DataType>
void BiTree<DataType>::InROrderTraverse(TreeNode<DataType>* p)
{
if(p){
   InROrderTraverse(p->lchild);
   cout<<p->data<<" ";
   InROrderTraverse(p->rchild);
}
}

template <class DataType>
void BiTree<DataType>::PosROrderTraverse()
{
PosROrderTraverse(root);
}

template <class DataType>
void BiTree<DataType>::PosROrderTraverse(TreeNode<DataType>* p)
{
if(p){
   PosROrderTraverse(p->lchild);
   PosROrderTraverse(p->rchild);
   cout<<p->data<<" ";
}
}

template <class DataType>
void BiTree<DataType>::PreOrderTraverse()
{
Stack<TreeNode<DataType>*> S;
TreeNode<DataType>* p;
p=root;
while(p||!S.IsEmpty()){
  if(p){S.Push(p);cout<<p->data<<" "; p=p->lchild;}
  else{
    S.Pop(p);
    p=p->rchild;
   }
}
S.Destroy();
}

template <class DataType>
void BiTree<DataType>::InOrderTraverse()
{
Stack<TreeNode<DataType>*> S;
TreeNode<DataType>* p;
p=root;
while(p||!S.IsEmpty()){
  if(p){S.Push(p); p=p->lchild;}
  else{
    S.Pop(p);
    cout<<p->data<<" ";
    p=p->rchild;
   }
}
S.Destroy();
}


template <class DataType>
void BiTree<DataType>::PosOrderTraverse()
{
Stack<TreeNode<DataType>*> S;
TreeNode<DataType>* p;
TreeNode<DataType>* r;       //使用r节点表示访问了右子树替代标志域
p=root;
while(p||!S.IsEmpty())
{
  if(p){S.Push(p);p=p->lchild;}
  else{
    S.GetTop(p);
   if(p->rchild&&p->rchild!=r){p=p->rchild;S.Push(p);p=p->lchild;}
   else{S.Pop(p);cout<<p->data<<" ";r=p;p=NULL;}
   }
}
S.Destroy();
}


//template <class DataType>
//void BiTree<DataType>::PosOrderTraverse()
//{
// Stack<TreeNode<DataType>*> S;
// TreeNode<DataType>* p;
// p=root;
// while(p||!S.StackEmpty())
// {
//   if(p){S.Push(p); p->tag=true;p=p->lchild;}
//   else{
//    S.GetTop(p);
//    if(p->rchild&&!p->rchild->tag){  
//      p=p->rchild;S.Push(p);p->tag=true;p=p->lchild;
//    }
//    else{S.Pop(p);cout<<p->data<<" ";p=NULL;}
//   }
// }
//   S.DestroyStack();
//}

template <class DataType>
void BiTree<DataType>::LevelOrderTraverse()
{
Queue<TreeNode<DataType>*> qu;
TreeNode<DataType>* p;
qu.EnQueue(root);
while(!qu.IsEmpty()){
   qu.DeQueue(p);
   cout<<p->data<<" ";
  if (p->lchild!= NULL) qu.EnQueue(p->lchild);
        if (p->rchild!= NULL) qu.EnQueue(p->rchild);
}
} 
#endif

