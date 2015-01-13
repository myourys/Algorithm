/*=============================================================================
#     FileName: BsTree.c
#         Desc: 二叉查找树C语言实现
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2015-01-09 18:54:20
#      History:
=============================================================================*/
/*
 * 二叉查找树,左子树总是小于根节点,右子树总是大于根节点
 */
#include <stdlib.h>
#include <stdio.h>

typedef int T;

typedef struct _BsTree
{
    T key;
    struct _BsTree *lchild;
    struct _BsTree *rchild;
}*BsTree;


BsTree BsTree_create(T key)
{
    BsTree node = (BsTree)malloc(sizeof(struct _BsTree));
    node->key = key;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

int BsTree_find(BsTree root,T key)
{
    if(!root)
        return 0;
    else if(key == root->key)
        return 1;
    else if(key < root->key)
        return BsTree_find(root->lchild, key);
    else if(key > root->key)
        return BsTree_find(root->rchild, key);
    return 0;
}

/* root pointer maybe change */
int BsTree_insert(BsTree *root,T key)
{
    BsTree node = *root;
    if (!node) {
        *root = BsTree_create(key);
    }
    else if(key == node->key)
        return 0;
    else if (key < node->key)
    {
        if (!node->lchild)
            node->lchild = BsTree_create(key);
        else
            return BsTree_insert(& node->lchild, key);
    }
    else // (key > root->key)
    {
        if (!node->rchild)
            node->rchild = BsTree_create(key);
        else
            return BsTree_insert(& node->rchild, key);
    }
    return 1;
}

/*
 * root 如果删除的是根节点，root指针可能改变
 */
int BsTree_erase(BsTree *root,T key)
{
    BsTree node = *root;
    if(!node)
        return 0;

    if (key < node->key)
        return node->lchild? BsTree_erase(&node->lchild, key) : 0;
    else if (key > node->key)
        return node->rchild? BsTree_erase(&node->rchild, key) : 0;

    BsTree delNode = *root;

    if(!delNode->lchild) //左子树为空，只需右接右子树
        *root = delNode->rchild;
    else if (!delNode->rchild)
        *root = delNode->lchild;
    else
    {
        BsTree replaceNode = delNode->lchild;
        BsTree replaceFather = delNode;
        while(replaceNode->rchild) //找到左子树最大值 放到删除的节点中当做新的节点
        {
            replaceFather = replaceNode;
            replaceNode = replaceNode->rchild;
        }
        replaceFather->rchild = replaceNode->lchild;
        *root = replaceNode;
        replaceNode->lchild = delNode->lchild;
        replaceNode->rchild = delNode->rchild;
    }

    free(delNode);

    return 1;
}


void BsTree_destroy(BsTree *root)
{
    BsTree node = *root;
    if ( node != NULL )
    {
        if (node->lchild) BsTree_destroy( & node->lchild );
        if (node->rchild) BsTree_destroy( & node->rchild );
        free(node);
    }
    *root = NULL;
}

void BsTree_mid_visit(BsTree root)
{
    if(root)
    {
        BsTree_mid_visit(root->lchild);
        printf("%d ",root->key);
        BsTree_mid_visit(root->rchild);
    }
}



int main(int argc, const char * argv[])
{
    int t[]={5,9,1,0,4,8,7,3,2,6};
    BsTree root = NULL;

    for(int i = 0;i < 10;i++)
        BsTree_insert(&root,t[i]);

    BsTree_mid_visit(root);
    printf("\n");

    BsTree_erase(&root,0);
    BsTree_mid_visit(root);
    printf("\n");

    BsTree_erase(&root,5);
    BsTree_mid_visit(root);
    printf("\n");

    BsTree_erase(&root,7);
    BsTree_mid_visit(root);
    printf("\n");

    BsTree_erase(&root,1);
    BsTree_mid_visit(root);
    printf("\n");

    BsTree_destroy(&root);
    return 0;

}


