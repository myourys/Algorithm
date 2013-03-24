/*=============================================================================
#     FileName: TArray.h
#         Desc: 数组的模版类实现
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2013-03-24 21:41:06
#      History:
                使用的可变参数,可以参考 http://www.ourys.com/post/56.html
=============================================================================*/
#ifndef _ARRAY_H
#define _ARRAY_H
#include "stdarg.h"     //可变参数的头文件
#define MAX_ARRAY_DIM 8 //数组元素最大维数
template<class T>
class Array{
public:
    Array(int _dim,...); //构造_dim维数组
    ~Array(); //销毁数组
    bool Locate(va_list ap,int &off); //求出该元素在A中的相对地址off
    bool Value(T* e,...); //e被赋值为数组的相应元素（stdarg.h不能传引用，所以用传地址的形式）
    bool Assign(T e,...); //将e赋值为数组的相应的元素值
private:
    T* base; //数组元素基址
    int dim; //数组维数
    int* bounds; //数组每维度的长度 如[3,4,5] 
    int* constants; //数组映像函数常量基址 地址为[4x5,5x1,1]
};

/*———— 构造函数，构造_dim维数组 ————–*/
template <class T>
Array<T>::Array(int _dim,...)
{
    int elemtotal=1,i;
    va_list ap;
    if(_dim<1||_dim>MAX_ARRAY_DIM) exit(1);
    dim=_dim;
    if(!(bounds=(int*)malloc(dim*sizeof(int)))) exit(1);
    va_start(ap,_dim);
    for(i=0;i<_dim;i++)
    {
        bounds[i]=va_arg(ap,int); //把各维的长度赋值给bounds[dim]
        if(bounds[i]<0) exit(1); //如果维的长度为0错误
        elemtotal*=bounds[i]; //elemtotal 为元素总个数
    }
    va_end(ap); //保持健壮性
    if(!(base=(T*)malloc(elemtotal*sizeof(T)))) exit(1); //给元素分配空间
    if(!(constants=(int*)malloc(dim*sizeof(int)))) exit(1);
    constants[dim-1]=1;
    for(i=dim-2;i>=0;--i)
    {
        constants[i]=bounds[i+1]*constants[i+1];
    }
}

/*———— 销毁数组 ————–*/
template <class T>
Array<T>::~Array()
{
    if(base) free(base);
    if(bounds) free(bounds);
    if(constants) free(constants);
    bounds=constants=NULL;
    base=NULL;
    dim=0;
}

/*———— 求出该元素在A中的相对地址off ————–*/
template <class T>
bool Array<T>::Locate(va_list ap, int &off)
{
    int ind;
    for(int i=0;i<dim;++i)
    {
        ind=va_arg(ap,int);
        if(ind<0||ind>=bounds[i]) exit(1);
        off+=constants[i]*ind;
    }
    va_end(ap);
    return true;
}

/*———— e被赋值为数组的相应元素 ————–*/
template <class T>
bool Array<T>::Value(T* e,...)
{
    va_list ap;
    int off=0;
    va_start(ap,e);
    if(!Locate(ap,off)) return false;
    *e=*(base+off);
    return true;
}

/*———— 将e赋值为数组的相应的元素值 ————–*/
template <class T>
bool Array<T>::Assign(T e,...)
{
    va_list ap;
    int off=0;
    va_start(ap,e);
    if(!Locate(ap,off)) return false;
    *(base+off)=e;
    return true;
}

#endif
