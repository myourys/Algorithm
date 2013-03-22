/*=============================================================================
#     FileName: CQueueTest.c
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 1.0.1
#   LastChange: 2013-03-22 17:08:27
#         Desc: 队列的基本操作 测试文件
#      History:
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include "CQueue.h"
int main()
{
    LinkQueue queue=InitQueue();
    EnQueue(queue,1);
    EnQueue(queue,2);
    EnQueue(queue,3);
    EnQueue(queue,4);
    printf("%i\n",DeQueue(queue));
    printf("%i\n",DeQueue(queue));
    printf("%i\n",DeQueue(queue));
    printf("%i\n",DeQueue(queue));
    DestroyQueue(queue);
    return 0;
}

