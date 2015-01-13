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
#include "TStack.h"

using namespace std;
int main()
{
    Stack<int> my;
    int a[2];
    my.push(5);
    my.push(4);
    my.pop(a[0]);
    my.getTop(a[1]);
    cout<<a[0]<<a[1]<<endl;
    return 0;
}

