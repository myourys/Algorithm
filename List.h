/*=============================================================================
#     FileName: CList.h
#         Desc: 
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2014-09-09 18:38:39
#      History:
=============================================================================*/
#include <stdlib.h>
/*Data type*/
typedef int T;

typedef struct _Item
{
    T data;
    struct _Item* next;
}*Item;

typedef struct _List
{
    Item head;
    int len;
    void (*delete_func)(T* e);
}*List;

List list_create(void (*_delete_func)(T* e))
{
    List list;
    list = (List)malloc(sizeof(struct _List));
    list->head = NULL;
    list->len = 0;
    list->delete_func = _delete_func;
    return list;
}

/*
 * insert element after i'th
 */
int list_insert(List list,int i,T e)
{
    if(i < 0 || i > list->len)
        return 0;
    else
    {
        Item tmp = (Item)malloc(sizeof(struct _Item));
        tmp->data = e;
        tmp->next = NULL;

        Item p= list->head;
        if( i== 0)
        {
            tmp->next = p;
            list->head = tmp;
        }
        else
        {
            while(--i > 0)
                p = p->next;
            tmp->next = p->next;
            p->next = tmp;
        }

        list->len++;
        return 1;
    }
}


/*
 * delete i'th element
 */
int list_delete(List list,int i)
{
    if(i < 1 || i > list->len)
    {
        printf("Delete out of range!\n");
        return 0;
    }
    else
    {
        Item p = list->head;
        T *e;
        if(i==1)
        {
            list->head = p->next;
            e = &p->data;
            free(p);
        }
        else
        {
            while(--i > 1)
                p = p->next;

            Item tmp = p->next;
            p->next = tmp->next;
            e = &tmp->data;
            free(tmp);
        }
        list->len--;
        if(list->delete_func)
            list->delete_func(e);
        return 1;
    }
    return 0;
}

int list_destroy(List list)
{
    while(list->len > 0)
        list_delete(list,1);
    free(list);
    return 1;
}
