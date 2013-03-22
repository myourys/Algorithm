/*=============================================================================
#     FileName: CQueue.h
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 1.0.1
#   LastChange: 2013-03-22 17:04:31
#         Desc: 队列的基本操作（c实现）
#      History:
=============================================================================*/
typedef int Datatype;
typedef struct tagQNode{
    Datatype data;
    struct tagQNode* next;
}*QNode;

typedef struct {
    QNode front; //队首
    QNode rear;  //队尾
}*LinkQueue;

/*———— 构造一个空的队列 ————–*/
LinkQueue InitQueue()
{
    LinkQueue q;
    q->front=(QNode)malloc(sizeof(struct tagQNode));
    if(!q->front) exit(1);
    q->rear=q->front;
    q->front->next=NULL;
    return q;
}

/*———— 销毁队列 ————–*/
int DestroyQueue(LinkQueue q)
{
    while(q->front){
        q->rear=q->front->next;
        free(q->front);
        q->front=q->rear;
    }
    return 1;
}

/*———- 插入一个为e的队尾元素 ———–*/
void EnQueue(LinkQueue q,Datatype e)
{
    QNode p=(QNode)malloc(sizeof(struct tagQNode));
    p->data=e;
    p->next=NULL;
    q->rear->next=p;
    q->rear=p;
}

/*———- 删除一个队头元素，并返回 ———-*/
Datatype DeQueue(LinkQueue q)
{
    if(q->front==q->rear) return 0;
    Datatype e=q->front->next->data;
    QNode p=q->front->next;
    q->front->next=p->next;
    if(q->rear==p) q->rear=q->front;
    free(p);
    return e;
}

