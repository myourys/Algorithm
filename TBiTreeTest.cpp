/*=============================================================================
#     FileName: TBiTreeTest.cpp
#         Desc: 二叉树模版类测试文件
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2013-03-24 20:38:29
#      History:
=============================================================================*/
/* 例如输入:(以0为空节点)
 * a b d 0 0 e 0 0 c 0 f 0 0
 */

#include<iostream>
using namespace std; 
#include <stdlib.h>
#include "TBiTree.h"

int main()
{
    BiTree<char> my;
    my.CreateBiTree();
    my.PreROrderTraverse();
    cout<<endl;
    my.PreOrderTraverse();
    cout<<endl;
    my.InOrderTraverse();
    cout<<endl;
    my.InROrderTraverse();
    cout<<endl;
    my.PosROrderTraverse();
    cout<<endl;
    my.PosOrderTraverse();
    
    cout<<endl;
    my.LevelOrderTraverse();
    return 0;
}

