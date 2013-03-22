/*=============================================================================
#     FileName: TQueue.cpp
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 1.0.1
#   LastChange: 2013-03-23 00:02:51
#         Desc: 队列模版类实现测试文件
#      History:
=============================================================================*/
#include<iostream> 
#include <stdlib.h>
#include "TQueue.h"
using namespace std;

int main()
{
    Queue<int> my;
    int temp;
    for(int i=2;i<10;i++)
    {
        my.EnQueue(i);
        my.GetHead(temp);
        cout<<temp<<endl;
    }
    for(int i=2;i<10;i++)
    {
        my.DeQueue(temp);
        cout<<temp<<endl; 
    }
    return 0;
}

