/*=============================================================================
#     FileName: TQueue.h
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 1.0.1
#   LastChange: 2013-03-22 23:53:18
#         Desc: 队列的C++模版类实现
#      History:
=============================================================================*/
#ifndef _QUEUE_H
#define _QUEUE_H
#define QUEUE_INIT_SIZE 100 //初始队列的最大长度
#define QUEUEINCREMENT 10 //每次新增的长度

template <class T>
class Queue{
public:
    Queue(); //构造函数，创建一个新的队列
    ~Queue(); //销毁队列
    bool EnQueue(T e); //插入一个值为e的队尾元素
    bool GetHead(T &e); //取出队头元素
    bool DeQueue(T &e); //删除队头元素
    bool Empty(); //判断是否非空
    bool Clear(); //清空队列
private:
    T *front;
    T *rear;
    int queuesize;
};

template<class T>
Queue<T>::Queue()
{
    if(!(front=(T*)malloc(QUEUE_INIT_SIZE*sizeof(T)))) exit(1);
    rear=front;
    queuesize=QUEUE_INIT_SIZE;
}

/*———— 插入一个值为e的队尾元素 ————–*/
template<class T>
bool Queue<T>::EnQueue(T e)
{
    if(rear-front>=queuesize){
        if(!(front=(T*)realloc(front,(queuesize+QUEUEINCREMENT)*sizeof(T)))) exit(1);
        rear=front+queuesize;
        queuesize+=QUEUEINCREMENT;
    }
    *rear++=e;
    return true;
}


template<class T>
bool Queue<T>::GetHead(T &e)
{
    if(rear==front) return false;
    e=*front;
    return true;
}

template<class T>
bool Queue<T>::DeQueue(T &e)
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
bool Queue<T>::Empty()
{
    return rear==front? 1:0;
}

template<class T>
bool Queue<T>::Clear()
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

