/*=============================================================================
#     FileName: TQueue.h
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 1.0.1
#   LastChange: 2014-09-22 23:20:50
#         Desc: 队列的C++模版类实现
#      History:
=============================================================================*/
#ifndef _QUEUE_H
#define _QUEUE_H
#define kQueueInitSize 100 //初始队列的最大长度
#define kQueueIncrement 10 //每次新增的长度

template <class T>
class Queue{
public:
    Queue(); //构造函数，创建一个新的队列
    ~Queue(); //销毁队列
    bool enQueue(T e); //插入一个值为e的队尾元素
    bool getHead(T &e); //取出队头元素
    bool deQueue(T &e); //删除队头元素
    bool empty(); //判断是否非空
    bool clear(); //清空队列
private:
    T *front;
    T *rear;
    int queuesize;
};

template<class T>
Queue<T>::Queue()
{
    if(!(front=(T*)malloc(kQueueInitSize*sizeof(T)))) exit(1);
    rear=front;
    queuesize=kQueueInitSize;
}

/*———— 插入一个值为e的队尾元素 ————–*/
template<class T>
bool Queue<T>::enQueue(T e)
{
    if(rear-front>=queuesize){
        if(!(front=(T*)realloc(front,(queuesize+kQueueIncrement)*sizeof(T)))) exit(1);
        rear=front+queuesize;
        queuesize+=kQueueIncrement;
    }
    *rear++=e;
    return true;
}


template<class T>
bool Queue<T>::getHead(T &e)
{
    if(rear==front) return false;
    e=*front;
    return true;
}

template<class T>
bool Queue<T>::deQueue(T &e)
{
    if(rear==front) return false;
    e=*front;
    T* temp;
    temp=front;
    while(temp!=rear) //为了删除后的空间继续利用，所有元素都向前移一位
    {
        *temp=*(temp+1);
        temp++;
    }
    rear--;
    return true;
}

template<class T>
bool Queue<T>::empty()
{
    return rear==front? 1:0;
}

template<class T>
bool Queue<T>::clear()
{
    rear=front;
    return true;
}

template<class T>
Queue<T>::~Queue()
{
    free(front);
}

#endif

