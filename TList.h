/*=============================================================================
#     FileName: List.h
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 1.0.1
#   LastChange: 2013-03-21 16:52:20
#         Desc: List 
#      History:
=============================================================================*/
#ifndef _LIST_H
#define _LIST_H
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
template <class T> 
class List
{ 
public:
    List(); 
    //~List(); 
    void Destroy(); //Destroy List
    void Clear(); 
    bool Empty(); 
    int Length(); 
    T GetElem(int i,T &e); //Get Item by index
    int LocateElem(T e); //Get First Item
    T PriorElem(T cur_e,T &pre_e); //Get Prior Item
    T NextElem(T cur_e,T &next_e); //Get Next Item
    void Insert(int i,T e); //Insert e at i
    T Delete(int i,T &e); //delete Item and return
    void Traverse(void visit()); //visit all Item

private:
    T *elem;
    int length;
    int listsize; 
};

template <class T> 
List<T>::List() 
{
    elem=(T *)malloc(LIST_INIT_SIZE*sizeof(T)); 
    if(!elem) 
    {
        throw "Allocation failed";
    }
    else
    {
        length=0;
        listsize=LIST_INIT_SIZE;
    }
}

template <class T>
void List<T>::Destroy() 
{
    this->Clear();
    free(elem);
}

template <class T>
void List<T>::Clear() 
{
    length=0;
}

template <class T> 
bool List<T>::Empty() 
{
    return length ? true:false;
}

template <class T>
int List<T>::Length() 
{
    return length;
}

template <class T>
T List<T>::GetElem(int i,T &e) 
{
    if(i<1||i>length)
        throw "Index out of bounds";
    else
        e=elem[i-1];
    return e;
}

template <class T>
int List<T>:: LocateElem(T e)
{
    for(int i=0;i<length;i++) 
    { 
        if(elem[i]==e) 
            return i+1; 
    }  
    cout<<"List Not Exist Item '"<<e<<"' !"<<endl; 
    return 0; 
}

template <class T> 
T List<T>::PriorElem(T cur_e,T &pre_e) 
{
    int i=LocateElem(cur_e);
    if(i>1)
    {
        pre_e=elem[i-2];
        return pre_e;
    }
    else
    {
        return NULL;
    }
}

template <class T>
T List<T>::NextElem(T cur_e,T &next_e) 
{
    int i=LocateElem(cur_e); 
    if(i>0 && i<length) 
    { 
        next_e=elem[i];  
        return next_e; 
    } 
    else 
    {
        return NULL; 
    }
    
}

template <class T>
void List<T>::Insert(int i,T e)
{
    if(i<0 || i>length+1) cout<<"Out of Index!";
    else if(i==length)
    {
        elem = (T *)realloc(elem,(length+LISTINCREMENT)*sizeof(T));
    }
    for(int j=length;j>=i;j--) elem[length]=elem[length-1];
    elem[i-1]=e;
    length++;
}

template <class T>
T List<T>::Delete(int i,T &e)
{
    if(length==0) return NULL;
    if(i<0||i>length) return NULL;
    e=elem[i-1];
    for(int j=i;j<length;j++) elem[j-1]=elem[j]; 
    length--; 
    return e;
}

template <class T>
void List<T>::Traverse(void visit())
{ 
    for(int i=0;i<length;i++) visit(elem[i]); 
} 

#endif

