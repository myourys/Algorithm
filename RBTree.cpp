#include<iostream>
using namespace std; 
#include <stdlib.h>

/*
 * 红黑树开始
 * 参考维基百科 http://zh.wikipedia.org/wiki/%E7%BA%A2%E9%BB%91%E6%A0%91
 * 红黑树是二叉搜索树的变种，故先了解二叉排序树BSTree.cpp
 */
enum NodeColor{Red,Black};

//节点
template <class T>
struct RBNode
{
  NodeColor Color; 
	RBNode *lchild,*rchild,*parent;
	T Key;
	RBNode()
	{
        Color = Red; // 新增节点为红色，避免多一个额外的黑色节点
		lchild = rchild = parent =NULL;
	}
};

template <class T>
class RBTree
{
protected:
    RBNode<T>* root;
    void AdjustInsertNode(RBNode<T>* node); //调整插入节点颜色等
public:
	RBTree():root(NULL){};
    ~RBTree();
	void Destroy();
	void Destroy( RBNode<T>* node);
	void InROrder();
	void InROrder(RBNode<T>* node);//中序遍历
	RBNode<T>* GrandParent(RBNode<T>* node);		//祖父
	RBNode<T>* Uncle(RBNode<T>* node);		        //叔父
	RBNode<T>* Sibling(RBNode<T>* node);		    //兄弟
    bool Search(T key,RBNode<T>* &p);             //若没有搜索到，返回最后遍历的节点
    bool Search(RBNode<T>* node,T key,RBNode<T>* &p);             
    bool Insert(T key); //插入

};

template <class T>
RBTree<T>::~RBTree()
{
    Destroy();
}

template <class T>
RBNode<T>* RBTree<T>::GrandParent(RBNode<T>* node)		//祖父
{
	if(node->parent)
		return node->parent->parent;
	return NULL;
}

template <class T>
RBNode<T>* RBTree<T>::Uncle(RBNode<T>* node)		//叔父
{
	RBNode<T>* p = GrandParent(node);
	if(p)
		if(node->parent == p->lchild)
			return p->rchild;
		else 
			return p->lchild;
	return NULL;
}

template <class T>
RBNode<T>* RBTree<T>::Sibling(RBNode<T>* node)		//兄弟
{
	if(node->parent)
		if(node = node->parent->lchild)
			return node->parent->rchild;
		else
			return node->parent->lchild;
	return NULL;
}

template <class T>  
void RBTree<T>::Destroy()
{
	Destroy(root);
}

template <class T>  
void RBTree<T>::Destroy( RBNode<T>* node)
{  
    if ( node != NULL )  
    {  
        Destroy( node->lchild );  
        Destroy( node->rchild );  
        delete node;  
    }    
}  

template <class T>
void RBTree<T>::InROrder()
{
	InROrder(root);
}

template <class T>
void RBTree<T>::InROrder(RBNode<T>* node)
{
    if(node)
    {
        InROrder(node->lchild);
        cout<<node->key<<"  ";
        InROrder(node->rchild);
    }
}

template <class T>
bool RBTree<T>::Search(T key,RBNode<T>* &p)
{
    return Search(root,key,p);
}

template <class T>
bool RBTree<T>::Search(RBNode<T>* node,T key,RBNode<T>* &p)
{
    p=node;
	if (!node) //根节点为空
		return false;

	if (key == node->key) //查找成功
        return true;

    if (key < node->key && node->lchild) //在左子树中继续查找
        return Search(node->lchild, key, p);

    if (key > root->key && root->rchild)//右子树继续查找
        return Search(node->rchild, key, p);

	return false;
    
}

template <class T>
bool RBTree<T>::Insert(T key) //插入
{
    RBNode<T>* p;
    if(Search(key,p)) //找到了，不满足二叉排序树规则则退出
        return false;
    
    RBNode<T>* s = new RBNode<T>;
    s->key = key;
    s->parent = p;
    if(!p)
        root = s;
    else if (p->key > s->key)
        p->lchild = s;
    else
        p->rchild = s;

    AdjustInsertNode(s);// 开始进行颜色调整
    return true;
}

template <class T>
void RBTree<T>::AdjustInsertNode(RBNode<T>* node) //调整插入节点颜色等
{
    if(node->parent = NULL) //根节点颜色为红色
        node->Color = Black; 
    else if (node->parent->Color = Black) //父节点颜色为黑色，无需调整
        ;
    else if (   //父节点为红色，此时本身也会红色，不满足条件
}

int main()
{
    return 0;
}

