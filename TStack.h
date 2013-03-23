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
template <class DataType>
class Stack{
public:
    Stack();
    void Push(DataType e);     
    int Pop(DataType &e);      
    int GetTop(DataType &e);   
    int IsEmpty();          
    void Destroy();       
private:
    DataType *base;
    DataType *top;
    int stacksize;
};

template <class DataType>
Stack<DataType>::Stack()
{
    if(!(base=(DataType*)malloc(STACK_INIT_SIZE*sizeof(DataType)))) exit(1);
    top=base;
    stacksize=STACK_INIT_SIZE;
}

template <class DataType>
void Stack<DataType>::Push(DataType e)
{
    if(top-base>=stacksize)
    {
        if(!(base=(DataType*)realloc(base,(stacksize+STACKINCREMENT)*sizeof(DataType)))) exit(1);
        top=base+stacksize;
        stacksize+=STACKINCREMENT;
    }
    *top++=e;
}

template <class DataType>
int Stack<DataType>::Pop(DataType &e)
{
    if(top==base) return 0;
    e=*--top;
    return 1;
}
template <class DataType>
int Stack<DataType>::GetTop(DataType &e)
{
    if(top==base) return 0;
    e=*(top-1);
    return 1;
}
template <class DataType>
int Stack<DataType>::IsEmpty()
{
    return top==base? 1:0;
}
template <class DataType>
void Stack<DataType>::Destroy()
{
    free(base);
}

#endif

