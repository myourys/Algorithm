/*=============================================================================
#     FileName: TListTest.cpp
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 1.0.1
#   LastChange: 2013-03-22 16:29:42
#         Desc: 链表模版类实现测试文件
#      History:
=============================================================================*/
#include<iostream> 
#include <stdlib.h>
using namespace std; 
#include "TList.h" 
int main() 
{ 

   List<int> list; 
   for(int i=0;i<10;i++) list.Insert(i+1,i*(1+i)); 
   int a[10],b[10]; 
   for(int i=0;i<list.Length();i++) cout<<list.GetElem(1+i,a[i])<<endl; 
  
   cout<<list.Length()<<endl; 
   cout<<list.LocateElem(90)<<endl; 
   list.NextElem(0,b[0]); 
   cout<<b[0]<<endl; 
   cout<<list.Delete(4,b[1])<<endl; 
   for(int i=0;i<list.Length();i++) cout<<list.GetElem(1+i,a[i])<<endl; 

  
    return 0; 
} 

