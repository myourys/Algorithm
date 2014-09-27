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
    void Push(T e);
    int Pop(T &e);
    int GetTop(T &e);
    int Empty();
    void Destroy();
private:
    T *base;
    T *top;
    int stacksize;
};

template <class T>
Stack<T>::Stack()
{
    if(!(base=(T*)malloc(STACK_INIT_SIZE*sizeof(T)))) exit(1);
    top=base;
    stacksize=STACK_INIT_SIZE;
}

template <class T>
void Stack<T>::Push(T e)
{
    if(top-base>=stacksize)
    {
        if(!(base=(T*)realloc(base,(stacksize+STACKINCREMENT)*sizeof(T)))) exit(1);
        top=base+stacksize;
        stacksize+=STACKINCREMENT;
    }
    *top++=e;
}

template <class T>
int Stack<T>::Pop(T &e)
{
    if(top==base) return 0;
    e=*--top;
    return 1;
}
template <class T>
int Stack<T>::GetTop(T &e)
{
    if(top==base) return 0;
    e=*(top-1);
    return 1;
}
template <class T>
int Stack<T>::Empty()
{
    return top==base? 1:0;
}
template <class T>
void Stack<T>::Destroy()
{
    free(base);
}

#endif

