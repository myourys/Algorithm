/*=============================================================================
#     FileName: Tuple.cpp
#         Desc: stl::Tuple的简单实现
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2015-01-21 19:31:39
#      History:
=============================================================================*/

/*
 * Tuple是横向存储数据接口,比如可用如函数多个返回值
 * c++0x已经自带了完善的Tuple数据结构，这里只是一个供学习的简单实现
 * 实现方式是通过模版的可变参数和元编程的概念，会根据情况将代码展开
 */

#include <iostream>
using std::cout;
/*
 * 利用模板的可变参数特性,类似递归
 * 在c++0x之前不支持可变参数的模板可以采用最多支持n参数的形式，然后特例化1~n个参数
 */

/*--------  Tuple begin ------------*/
template<typename... TList>
struct Tuple;

/* 空的template */
template<>
struct Tuple<>
{};
typedef Tuple<> NullTuple;

/* 递归定义 */
template<typename T,typename... TList>
struct Tuple<T,TList...>:public Tuple<TList...>
{
    typedef T value_type; //本次递归的value_type
    typedef Tuple<TList...> base_type;//father
    typedef Tuple<T,TList...> this_type;

    constexpr Tuple(T value,TList... tails):_value(value),base_type(tails...){};

    T& front(){return _value;}
    const T& front() const{return _value;}

protected:
    T _value;

};

/* 一个参数的Tuple */
template<typename T>
struct Tuple<T>:public NullTuple
{
    typedef T value_type; //本次递归的value_type
    typedef NullTuple base_type;//father
    typedef Tuple<T> this_type;

    constexpr Tuple(T value):_value(value){};

    T& front(){return _value;}
    const T& front() const{return _value;}

    T& back(){return _value;}
    const T& back() const{return _value;}
protected:
    T _value;
};

/*--------  Tuple end ------------*/

/*--------  Tuple_at begin ------------*/
/*
 * Tuple_at 定义Tuple中第N个元素的类型,和Tuple的类型
 * 利用模版的可变参数和模板元编程的概念
 * 实现方式类似tuple,递归定义和特例化
 */

/* 类似Tuple先申明 */
template<unsigned int N,typename... TList>
struct Tuple_at;

/* 递推定义 */
template<unsigned int N,typename T,typename... TList>
struct Tuple_at<N,Tuple<T,TList...> >
{
    typedef typename Tuple_at<N-1,Tuple<TList...> >::value_type  value_type;
    typedef typename Tuple_at<N-1,Tuple<TList...> >::tuple_type  tuple_type;

};

/* NullTuple 的特殊定义为NULL */
template<>
struct Tuple_at<0,NullTuple>
{
    typedef NullTuple value_type;
    typedef NullTuple tuple_type;
};


template<typename T,typename... TList>
struct Tuple_at<0,Tuple<T,TList...> >
{
    typedef T value_type;
    typedef Tuple<T,TList...> tuple_type;
};



/*--------  Tuple_at end ------------*/

/*--------  Tuple_get function ------------*/
/* 调用Tuple_at 返回其元素值即可 */
template<unsigned int N,typename... TList>
typename Tuple_at<N,Tuple<TList...> >::value_type
    Tuple_get(const Tuple<TList...>& _tp)
{
    typedef Tuple<TList...> tuple_type;
    typedef typename Tuple_at<N, tuple_type>::tuple_type base_tuple_type;

    return static_cast<const base_tuple_type&>(_tp).front();
};



#include <string>
using namespace std;

int main()
{
    Tuple<int, float, char,string> t1 = {10, 0.1234, 'a',"test"};
    Tuple<int> t2(1);
    Tuple<int> t3(12);


    cout<<t1.front()<<endl;
    cout<<t1.back()<<endl;

    auto t4 = t1;
    cout<<t4.front()<<endl;
    cout<<t4.back()<<endl;

    cout<<Tuple_get<0>(t1)<<endl;
    cout<<Tuple_get<1>(t1)<<endl;
    cout<<Tuple_get<2>(t1)<<endl;
    cout<<Tuple_get<3>(t1)<<endl;
}
