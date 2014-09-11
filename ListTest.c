/*=============================================================================
#     FileName: CListTest.c
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 1.0.1
#   LastChange: 2014-09-11 15:10:27
#         Desc: 线性表C语言版 基本测试文件
#      History:
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
int main()
{
    List list=list_create(NULL);
    for(int i=0;i<10;i++)
    {
        list_insert(list,i,(i+1)*(i+1));
    }

    list_delete(list,1);
    list_delete(list,4);

    Item p = list->head;
    for(int i=0;i<list->len;i++)
    {
        printf("%d'th element is : %d\n", i , p->data);
        p = p->next;
    }

    printf("list length is:%d\n",list->len);

    list_destroy(list);

    return 0;
}

