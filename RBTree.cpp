/*=============================================================================
#     FileName: RBTree.cpp
#         Desc: 红黑树实现
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2013-04-01 23:52:42
#      History:
=============================================================================*/
#include<iostream>
using namespace std;
#include <stdlib.h>

/*
 * 参考维基百科 http://zh.wikipedia.org/wiki/%E7%BA%A2%E9%BB%91%E6%A0%91
 * 红黑树是二叉搜索树的变种，故先了解二叉排序树BSTree.cpp
 */

enum Nodecolor{Red,Black};

//节点
template <class T>
struct RBNode
{
    Nodecolor color;
	RBNode *lchild,*rchild,*parent;
	T key;
	RBNode()
	{
        color = Red; // 新增节点为红色，避免多一个额外的黑色节点
		lchild = rchild = parent =NULL;
	}
};

template <class T>
class RBTree
{
protected:
    RBNode<T>* root;
    void AdjustInsertNode(RBNode<T>* n); //调整插入节点颜色等
    void AdjustDelNode(RBNode<T>* n);    //调整待移走的节点
public:
	RBTree():root(NULL){};
    ~RBTree();
	void Destroy();
	void Destroy(RBNode<T>* n);
	void InROrder();
	void InROrder(RBNode<T>* n);//中序遍历
	void OutLevelROrder();
	void OutLevelROrder(RBNode<T>* n,int i);//遍历输出颜色和层数,可画出树结构
	RBNode<T>* GrandParent(RBNode<T>* n);		//祖父
	RBNode<T>* Uncle(RBNode<T>* n);		        //叔父
	RBNode<T>* Sibling(RBNode<T>* n);		    //兄弟
    void RotateLeft(RBNode<T>* n);                 //左旋
    void RotateRight(RBNode<T>* n);                //右旋
    bool Search(T key,RBNode<T>* &p);             //若没有搜索到，返回最后遍历的节点
    bool Search(RBNode<T>* n,T key,RBNode<T>* &p);
    bool Insert(T key); //插入
    bool Delete(T key); //删除
    bool Delete(RBNode<T>* n,T key); //删除

};

template <class T>
RBTree<T>::~RBTree()
{
    Destroy();
}

template <class T>
RBNode<T>* RBTree<T>::GrandParent(RBNode<T>* n)		//祖父
{
	if(n->parent)
		return n->parent->parent;
	return NULL;
}

template <class T>
RBNode<T>* RBTree<T>::Uncle(RBNode<T>* n)		//叔父
{
	RBNode<T>* p = GrandParent(n);
	if(p)
		if(n->parent == p->lchild)
			return p->rchild;
		else
			return p->lchild;
	return NULL;
}

template <class T>
RBNode<T>* RBTree<T>::Sibling(RBNode<T>* n)		//兄弟
{
	if(n->parent)
		if(n = n->parent->lchild)
			return n->parent->rchild;
		else
			return n->parent->lchild;
	return NULL;
}

template <class T>
void RBTree<T>::RotateLeft(RBNode<T>* n)                //左旋
{
    if(!n->rchild)
        return;
    RBNode<T>* p =n->rchild;
    //调整左右指向
    n->rchild = p->lchild;
    p->lchild = n;
    //调整父子指向
    p->parent = n->parent;
    if(n->parent)
    {
        if(n==n->parent->lchild)
            p->parent->lchild = p;
        else
            p->parent->rchild = p;
    }
    n->parent = p;
    if(n->rchild)
        n->rchild->parent = n;
    if(!p->parent) //p位置上升
        root = p;
}

template <class T>
void RBTree<T>::RotateRight(RBNode<T>* n)                 //右旋
{
   if(!n->lchild)
        return;
    RBNode<T>* p =n->lchild;
    //调整左右指向
    n->lchild = p->rchild;
    p->rchild = n;
    //调整父子指向
    p->parent = n->parent;
    if(n->parent)
    {
        if(n==n->parent->lchild)
            p->parent->lchild = p;
        else
            p->parent->rchild = p;
    }
    n->parent = p;
    if(n->lchild)
        n->lchild->parent = n;
    if(!p->parent) //p位置上升
        root = p;
}

template <class T>
void RBTree<T>::Destroy()
{
	Destroy(root);
}

template <class T>
void RBTree<T>::Destroy(RBNode<T>* n)
{
    if ( n != NULL )
    {
        Destroy( n->lchild );
        Destroy( n->rchild );
        delete n;
    }
}

template <class T>
void RBTree<T>::InROrder()
{
	InROrder(root);
}

template <class T>
void RBTree<T>::InROrder(RBNode<T>* n)
{
    if(n)
    {
        InROrder(n->lchild);
        cout<<n->key<<"  ";
        InROrder(n->rchild);
    }
}

template <class T>
void RBTree<T>::OutLevelROrder()
{
	OutLevelROrder(root,1);
}

template <class T>
void RBTree<T>::OutLevelROrder(RBNode<T>* n,int i)
{
    if(n)
    {
        if(n->color == Red)
            cout<<n->key<<"["<<i<<"][R]  ";
        else
            cout<<n->key<<"["<<i<<"][B]  ";
        OutLevelROrder(n->lchild,i+1);
        OutLevelROrder(n->rchild,i+1);
    }
}


template <class T>
bool RBTree<T>::Search(T key,RBNode<T>* &p)
{
    return Search(root,key,p);
}

template <class T>
bool RBTree<T>::Search(RBNode<T>* n,T key,RBNode<T>* &p)
{
    p=n;
	if (!n) //根节点为空
		return false;

	if (key == n->key) //查找成功
        return true;

    if (key < n->key && n->lchild) //在左子树中继续查找
        return Search(n->lchild, key, p);

    if (key > n->key && n->rchild)//右子树继续查找
        return Search(n->rchild, key, p);

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
bool RBTree<T>::Delete(T key) //删除
{
    return Delete(root,key);
}

template <class T>
bool RBTree<T>::Delete(RBNode<T>* n,T key) //删除
{
    if(!n)
		return false;

	if(key < n->key)
		return Delete(n->lchild,key);
	else if (key >n->key)
		return Delete(n->rchild,key);

	RBNode<T>* my=n; //my-待删除的节点,n 待移走[或删除的节点]
    RBNode<T>* p; //替换的节点
	if(!n->lchild) //左子树为空，只需右接右子树
        p=n->rchild;
	else if (!n->rchild)
		p=n->lchild;
	else
	{
		n=n->lchild;
		while(n->rchild) //找到左子树最大值 放到删除的节点中当做新的节点
			n=n->rchild;
        p = n->lchild; //被移走的节点由其左孩子代替
		//p->parent->rchild = p->lchild;
		//n = p;
		//n->lchild = my->lchild;
		//n->rchild = my->rchild;
	}

    //待移走的节点如果是红色,则不影响
    if(n->color == Black)
    {
        if(p && p->color == Red) //如果孩子是红色,则改为黑色,顶替上来
            p->color = Black;
        else if(n==root) //待移走的是根节点,孩子自动替换上来当做新的根节点就可以了
            ;
        else
        {
            RBNode<T>* s= Sibling(n);
            if(s && s->color==Red) //对应维基百科case2,如果兄弟为黑色,旋转一下
            {
                n->parent = Red;
                s->color = Black;
                if(n==n->parent->lchild)
                    RotateLeft(n->parent);
                else
                    RotateRight(n->parent);
            }
        }
    }

	delete my;
	return true;
}

template <class T>
void RBTree<T>::AdjustDelNode(RBNode<T>* n)    //调整待移走的节点
{
    //待移走的节点如果是红色,则不影响
    if(n->color == Red)
        return;

    RBNode<T>* p = n->lchild ? n->lchild:n->rchild; //替换的节点
    if(p && p->color == Red) //如果孩子是红色,则改为黑色,顶替上来    case 1
        p->color = Black;
    else if(n==root) //待移走的是根节点,孩子自动替换上来当做新的根节点就可以了
        ;
    else
    {
        RBNode<T>* s= Sibling(n);
        if(s && s->color==Red) //对应维基百科case2,如果兄弟为红色,旋转一下后再调整 case 2
        {
            n->parent = Red;
            s->color = Black;
            if(n==n->parent->lchild)
                RotateLeft(n->parent);
            else
                RotateRight(n->parent);

            AdjustDelNode(n);
        }
        //如果兄弟为黑色,父为黑色,则将改兄弟改为红色,本身[黑色]移走要-1,相当于调整父节点一样 case 3
        else if(n->parent->color==Black&&s&&s->color == Black&&(!s->lchild || s->color==Black)&&(!s->rchild || s->rchild->color==Black))
        {
            s->color =Red;
            AdjustDelNode(n->parent);
        }
        //如果父为红,兄弟为黑色,将父改为黑,兄改为红,则自己+1,抵消自己的-1 case 4
        else if(n->parent==Red&&s&&s->Black&&(!s->lchild || s->color==Black)&&(!s->rchild || s->rchild->color==Black))
        {
            s->color=Red;
            n->parent->color = Black;
        }
        //如果兄弟节点有一个为红色 转化为 case 2- 4 case 5
        else if(s&&s->color==Black)
        {
            if(n==n->parent->lchild && (!s->rchild||s->rchild->color==Black)&&s->lchild && s->lchild==Red)
            {
                s->color = Red;
                s->lchild->color =Black;
                RotateRight(s); //右旋
            }
            else if(n==n->parent->rchild && (!s->lchild||s->lchild->color==Black)&&s->rchild && s->rchild==Red)
            {
                s->color = Red;
                s->rchild->color =Black;
                RotateLeft(s); //左旋
            }
            AdjustDelNode(n);
        }
        else
        {
            s->color = n->parent->color;
            n->parent->color = Black;
            if(n==n->parent->lchild)
            {
                s->rchild->color = Black;
                RotateLeft(n->parent);
            }
            else
            {
                s->lchild->color = Black;
                RotateRight(n->parent);
            }
        }
    }

    if(n==root) //如果跟节点被移走,新上来的节点当做跟节点
        root = p;

}

template <class T>
void RBTree<T>::AdjustInsertNode(RBNode<T>* n) //调整插入节点颜色等
{
    if(!n->parent) //根节点颜色为红色
        n->color = Black;
    else if (n->parent->color == Black) //父节点颜色为黑色，无需调整
        ;
    else if (Uncle(n) &&Uncle(n)->color == Red)   //父节点为红色，此时本身也会红色，不满足条件
    {
        n->parent->color = Black;
        Uncle(n)->color = Black;
        GrandParent(n)->color = Red;
        AdjustInsertNode(GrandParent(n)); //递归检查祖父节点
    }
    else if (n==n->parent->rchild && n->parent == GrandParent(n)->lchild)
    {
        RotateLeft(n->parent);
        AdjustInsertNode(n);
    }
    else if (n==n->parent->lchild && n->parent == GrandParent(n)->rchild)
    {
        RotateRight(n->parent);
        AdjustInsertNode(n);
    }
    else  //无叔节点或为黑色,通过变换,将红色节点移到叔节点位置,对应维基百科中的情况5
    {
        n->parent->color = Black;
        GrandParent(n)->color = Red;
        if(n==n->parent->lchild && n->parent == GrandParent(n)->lchild)
            RotateRight(GrandParent(n));
        else
            RotateLeft(GrandParent(n));
    }
}

int main()
{
    RBTree<int> tree;
    int i;
	int t[]={0,1,2,3,4,5,6,7,8,-1,-2,-3,-4,-5,-6,-7,-8};
    for(i=0;i<17;i++)
        tree.Insert(t[i]);

	cout<<"InROrder:"<<endl;
    tree.InROrder();

    cout<<"\nOutLevelROrder:"<<endl;
    tree.OutLevelROrder();


    return 0;
}

