/*=============================================================================
#     FileName: CListTest.c
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 1.0.1
#   LastChange: 2013-03-22 16:43:42
#         Desc: 线性表C语言版 基本测试文件
#      History:
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include "CList.h"
int main() 
{ 
    Link px;
    LinkList list=InitList();
    int i;
    for(i=0;i<10;i++)
    {
        ListInsert(list,i,(i+1)*(i+1));
    }
    ListDelete(list,1);
    ListDelete(list,4);
    px=list->head;
    for(i=0;i<list->len;i++)
    {
        printf("%d\n",px->data);
        px=px->next;
    }
    printf("%d\n",list->len);
    return 0; 
}

