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

