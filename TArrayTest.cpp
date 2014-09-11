/*=============================================================================
#     FileName: TArrayTest.cpp
#         Desc: 数组模版类测试文件
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2013-03-24 22:51:20
#      History:
=============================================================================*/
#include<iostream>
#include <stdlib.h>
#include "TArray.h"
using namespace std;
int main()
{
    int i,j,k,dim=3,bound1=3,bound2=4,bound3=5;
    char temp;
    Array<char> my(dim,bound1,bound2,bound3);
    for(i=0;i<bound1;i++)
        for(j=0;j<bound2;j++)
            for(k=0;k<bound3;k++)
                my.Assign('a'+i+j+k,i,j,k);

    for(i=0;i<bound1;i++)
    {
        for(j=0;j<bound2;j++)
        {
            for(k=0;k<bound3;k++)
            {
                my.Value(&temp,i,j,k);
                cout<<temp;
            }
            cout<<endl;
        }
        cout<<endl;
    }

    return 0;
}

