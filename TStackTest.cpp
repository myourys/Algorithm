/*=============================================================================
#     FileName: TStackTest.cpp
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 1.0.1
#   LastChange: 2013-03-22 16:28:57
#         Desc: 栈模版类实现测试文件
#      History:
=============================================================================*/
#include <iostream>
#include <stdlib.h>
using namespace std;
#include "TStack.h"
int main()
{
    Stack<int> my;
    int a[2];
    my.Push(5);
    my.Push(4);
    my.Pop(a[0]);
    my.GetTop(a[1]);
    cout<<a[0]<<a[1]<<endl;
    my.Destroy();
    return 0;
}

