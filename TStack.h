/*=============================================================================
#     FileName: TStack.h
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 1.0.1
#   LastChange: 2013-03-22 16:27:56
#         Desc: 栈的模版类实现
#      History:
=============================================================================*/
#ifndef _STACK_H
#define _STACK_H
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
template <class T>
class Stack{
public:
    Stack();
    ~Stack();
    void push(T e);
    int pop(T &e);
    int getTop(T &e);
    int empty();
private:
    T *base;
    T *top;
    int stackSize;
};

template <class T>
Stack<T>::Stack()
{
    if(!(base=(T*)malloc(STACK_INIT_SIZE*sizeof(T)))) exit(1);
    top=base;
    stackSize=STACK_INIT_SIZE;
}

template <class T>
void Stack<T>::push(T e)
{
    if(top-base>=stackSize)
    {
        if(!(base=(T*)realloc(base,(stackSize+STACKINCREMENT)*sizeof(T)))) exit(1);
        top=base+stackSize;
        stackSize+=STACKINCREMENT;
    }
    *top++=e;
}

template <class T>
int Stack<T>::pop(T &e)
{
    if(top==base) return 0;
    e=*--top;
    return 1;
}
template <class T>
int Stack<T>::getTop(T &e)
{
    if(top==base) return 0;
    e=*(top-1);
    return 1;
}
template <class T>
int Stack<T>::empty()
{
    return top==base? 1:0;
}

template <class T>
Stack<T>::~Stack()
{
    free(base);
}

#endif

