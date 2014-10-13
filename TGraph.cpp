/*=============================================================================
#     FileName: TGraph.cpp
#         Desc: 
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2014-09-16 00:20:16
#      History:
=============================================================================*/

#include <iostream>

#include "TGraph.h"
#include "TQueue.h"

#define MIN(x,y) (x) > (y) ? (y):(x);

using namespace std;

template<class T>
void Graph<T>::createUDN()
{
    cout<<"邻接矩阵-输入无向网顶点数和边数:"<<endl;
    cin>> _mgraph.vexNum >> _mgraph.arcNum;

    _mgraph.vertexs = new T[_mgraph.vexNum];
    cout<<"输入顶点信息:"<<endl;
    for(int i =0;i < _mgraph.vexNum;i++)
        cin>> _mgraph.vertexs[i];

    _mgraph.adjMatrix = new int*[_mgraph.vexNum];
    for(int i = 0;i<_mgraph.vexNum;i++) //默认所有点不连通
    {
        _mgraph.adjMatrix[i] =new int[_mgraph.vexNum];
        for (int j = 0; j < _mgraph.vexNum; j++) {
            _mgraph.adjMatrix[i][j] = INT_MAX;
        }
    }

    cout<<"输入弧尾弧头两点以及权值:"<<endl;
    T v1,v2;
    int t,m,n;
    for (int i = 0; i < _mgraph.arcNum; i++) {
        cin>> v1 >> v2 >> t;
        for (int j = 0; j < _mgraph.vexNum; j++) {
            if( v1 == _mgraph.vertexs[j])
                m = j;
            if( v2 == _mgraph.vertexs[j])
                n = j;
        }
        _mgraph.adjMatrix[m][n] = t;
        _mgraph.adjMatrix[n][m] = t;
    }
}

template<class T>
void Graph<T>::destroyUDN()
{
    delete []_mgraph.vertexs;
    for (int i = 0; i < _mgraph.vexNum; i++) {
        delete []_mgraph.adjMatrix[i];
    }
    delete [] _mgraph.adjMatrix;
}

template<class T>
void Graph<T>::createDN()
{
    cout<<"邻接矩阵-输入有向图顶点数和边数:"<<endl;
    cin>> _mgraph.vexNum >> _mgraph.arcNum;

    _mgraph.vertex = new T[_mgraph.vexNum];
    cout<<"输入顶点信息:"<<endl;
    for(int i =0;i < _mgraph.vexNum;i++)
        cin>> _mgraph.vertex[i];

    _mgraph.adjMatrix = new int*[_mgraph.vexNum];
    for(int i = 0;i<_mgraph.vexNum;i++) //默认所有点不连通
    {
        _mgraph.adjMatrix[i] =new int[_mgraph.vexNum];
        for (int j = 0; j < _mgraph.vexNum; j++) {
            _mgraph.adjMatrix[i][j] = INT_MAX;
        }
    }

    cout<<"输入弧尾弧头两点以及权值:"<<endl;
    T v1,v2;
    int t,m,n;
    for (int i = 0; i < _mgraph.arcNum; i++) {
        cin>> v1 >> v2 >> t;
        for (int j = 0; j < _mgraph.vexNum; j++) {
            if( v1 == _mgraph.vertex[j])
                m = j;
            if( v2 == _mgraph.vertex[j])
                n = j;
        }
        _mgraph.adjMatrix[m][n] = t;
    }
}

template<class T>
void Graph<T>::destroyDN()
{
    delete []_mgraph.vertex;
    for (int i = 0; i < _mgraph.vexNum; i++) {
        delete []_mgraph.adjMatrix[i];
    }
    delete [] _mgraph.adjMatrix;
}

template<class T>
void Graph<T>::createAlGraph()
{
    int i,j,m,n;
    cout<<"邻接表-输入图类型(1 无向图, 0 有向图)"<<endl;
    cin>>_algraph.kind;
    cout<<"输入顶点数和边数:"<<endl;
    cin>>_algraph.vexNum >> _algraph.arcNum;

    _algraph.vertexs = new VNode[_algraph.vexNum];
    cout<<"输入顶点信息:"<<endl;
    for (i = 0; i < _algraph.vexNum; i++) {
        cin>> _algraph.vertexs[i].data;
        _algraph.vertexs[i].firstArc = nullptr;
    }

    T v1,v2;
    float w;
    if(_algraph.kind) //无向图
    {
        cout<<"分别输入边的两个点和对应的权值:"<<endl;
        for (i = 0; i < _algraph.arcNum; i++) {//输入每条边
            cin>>v1>>v2>>w;
            for (j = 0; j < _algraph.vexNum; j++) {
                if(v1 == _algraph.vertexs[j].data) m = j;
                if(v2 == _algraph.vertexs[j].data) n = j;
            }
            /* 无向图对两个顶点是一样的，要生成两个边 */
            ArcNode *p0 = new ArcNode;
            p0->adjvex = m;
            p0->weight = w;
            p0->next = _algraph.vertexs[n].firstArc; //插入链表首位
            _algraph.vertexs[n].firstArc = p0;

            ArcNode *p1 = new ArcNode;
            p1->adjvex = n;
            p1->weight = w;
            p1->next = _algraph.vertexs[m].firstArc; //插入链表首位
            _algraph.vertexs[m].firstArc = p1;

        }
    }
    else //有向图
    {
        cout<< "输入各边的弧头弧尾的节点以及有向边的权值:"<<endl;
        for (i = 0; i < _algraph.arcNum; i++) {
            cin>>v1>>v2>>w;
            for (j = 0; j < _algraph.vexNum; j++) {
                if(v1 == _algraph.vertexs[j].data) m = j;
                if(v2 == _algraph.vertexs[j].data) n = j;
            }
            ArcNode *p = new ArcNode;
            p->adjvex = n;
            p->weight = w;
            p->next = _algraph.vertexs[m].firstArc; //插入链表首位
            _algraph.vertexs[m].firstArc = p;
        }
    }
}

template<class T>
void Graph<T>::destroyAlGraph()
{
    ArcNode *p,*q;
    for (int i = 0; i < _algraph.vexNum; i++) {
        p = _algraph.vertexs[i].firstArc;
        while(p)
        {
            q = p;
            p = p->next;
            delete q;
        }
    }

    delete []_algraph.vertexs;
}

template<class T>
void Graph<T>::createOlGraph()
{
    int i,j,m,n;
    cout<<"十字链表-输入顶点数和边数:"<<endl;
    cin>>_olgraph.vexNum >> _olgraph.arcNum;

    cout<<"输入顶点信息:"<<endl;
    _olgraph.vertexs = new VexNode[_olgraph.vexNum];
    for (i = 0; i < _olgraph.vexNum; i++) {
        cin>>_olgraph.vertexs[i].data;
        _olgraph.vertexs[i].firstIn = nullptr;
        _olgraph.vertexs[i].firstOut = nullptr;
    }

    cout<<"输入弧头弧尾和权值信息:"<<endl;
    T v1,v2;
    float w;
    for (i = 0; i < _olgraph.arcNum; i++) {
        cin>> v1 >>v2 >>w;
        for (j = 0; j < _olgraph.vexNum; j++) {
            if(_olgraph.vertexs[j].data == v1) m = j;
            if(_olgraph.vertexs[j].data == v2) n = j;
        }
        ArcBox *p = new ArcBox;
        p->headVex = m;
        p->tailVex = n;

        p->hlink = _olgraph.vertexs[m].firstOut;
        _olgraph.vertexs[m].firstOut = p;

        p->tlink = _olgraph.vertexs[n].firstIn;
        _olgraph.vertexs[n].firstIn = p;
    }
}

template<class T>
void Graph<T>::destroyOlGraph()
{
    ArcBox *p,*q;
    for (int i = 0; i < _olgraph.vexNum; i++) {
        p = _olgraph.vertexs[i].firstOut;
        while(p)
        {
            q = p;
            p = p->hlink;
            delete q;
        }
    }

    delete []_olgraph.vertexs;
}

template<class T>
void Graph<T>::alSubDFS(int vex,bool *visited)
{
    cout<< _algraph.vertexs[vex].data<<endl;
    visited[vex] = true;
    ArcNode *p = _algraph.vertexs[vex].firstArc;
    while(p)
    {
        if(!visited[p->adjvex])
            alSubDFS(p->adjvex,visited);
        p = p->next;
    }
}

template<class T>
void Graph<T>::alDFS()
{
    bool *visited = new bool[_algraph.vexNum];
    for (int i = 0; i < _algraph.vexNum; i++)
        visited[i] = false;

    cout<<"邻接表-深度优先搜索:"<<endl;
    for (int i = 0; i < _algraph.vexNum; i++)
        if(!visited[i])
            alSubDFS(i,visited);
    delete []visited;
}

template<class T>
void Graph<T>::alBFS()
{
    bool *visited = new bool[_algraph.vexNum];
    for (int i = 0; i < _algraph.vexNum; i++)
        visited[i] = false;

    cout<<"邻接表-广度优先搜索:"<<endl;
    Queue<int> queue;
    int v;
    ArcNode *p;
    for(int i = 0;i < _algraph.vexNum; i++)
    {
        if(visited[i])
            continue;

        cout<<_algraph.vertexs[i].data<<endl;
        visited[i] = true;

        queue.enQueue(i);
        while(!queue.empty())//
        {
            queue.deQueue(v);
            p = _algraph.vertexs[v].firstArc; //针对v的每一条弧进行遍历，并把弧放进队列
            while(p)
            {
                v = p->adjvex;
                if(!visited[v])
                {
                    cout<<_algraph.vertexs[v].data<<endl;
                    visited[v] = true;
                    queue.enQueue(v);
                }
                p = p->next;
            }
        }
    }
    delete []visited;
}

template<class T>
void Graph<T>::DFSForest(TreeNode<T> *&tree)
{
    TreeNode<T> *p,*r;
    p = r = nullptr;

    bool *visited = new bool[_algraph.vexNum];
    for(int i =0;i<_algraph.vexNum;i++)
        visited[i] = false;

    for(int i =0;i<_algraph.vexNum;i++)
    {
        if(visited[i])
            continue;
        visited[i] = true;
        r = new TreeNode<T>();
        r->data = _algraph.vertexs[i].data;
        r->lchild = r->nextSibling = nullptr;

        if(!p) //首节点
            tree = r;
        else
            p->nextSibling = r;

        p = r;

        DFSForestSub(i,p,visited);
    }

    delete []visited;

}
template<class T>
void Graph<T>::DFSForestSub(int vex,TreeNode<T> *&parent,bool *visited)
{
    TreeNode<T> *m,*n;
    m = n = nullptr;

    ArcNode *p = _algraph.vertexs[vex].firstArc;
    while(p)
    {
        if(!visited[p->adjvex])
        {
            visited[p->adjvex] = true;
            n = new TreeNode<T>();
            n->data = _algraph.vertexs[p->adjvex].data;
            n->lchild = n->nextSibling = nullptr;

            if(!m) //第一个作为孩子
                parent->lchild = n;
            else //边上的作为兄弟
                m->nextSibling = n;

            m = n;

            DFSForestSub(p->adjvex,m,visited);
        }
        p = p->next;
    }

}

template <class T>
void Graph<T>::visitTree(TreeNode<T> *tree)
{
    if(!tree)
        return;
    cout<<tree->data<<endl;
    visitTree(tree->lchild);
    visitTree(tree->nextSibling);
}

template <class T>
void Graph<T>::olDFS(int v,bool *visited,int *finished)
{
    visited[v] = true;
    finished[count++] = v; //第count个访问的是v
    ArcBox *p = _olgraph.vertexs[v].firstOut;
    while(p)
    {
        if(!visited[p->tailVex])
            olDFS(p->tailVex,visited,finished);
        p = p->tlink;
    }
}

template <class T>
void Graph<T>::olDFS(int v,bool *visited)
{
    cout<< _olgraph.vertexs[v].data<<endl;
    visited[v] = true;
    ArcBox *p = _olgraph.vertexs[v].firstIn;
    while(p)
    {
        if(!visited[p->headVex])
            olDFS(p->headVex,visited);
        p = p->hlink; //弧头继续搜索
    }
}

template<class T>
void Graph<T>::kosaraju()
{
    bool *visited = new bool[_olgraph.vexNum];
    int *finished = new int[_olgraph.vexNum];
    for(int i = 0;i<_olgraph.vexNum;i++)
    {
        visited[i] = false;
        finished[i]= -1;
    }

    count = 0;
    for(int i = 0;i<_olgraph.vexNum;i++)
    {
        if(!visited[i])
            olDFS(i,visited,finished);
    }

    for(int i = 0;i<_olgraph.vexNum;i++)
        visited[i] = false;

    cout<<"kosaraju-强连通分量为:"<<endl;
    for(int i = _olgraph.vexNum; i>=0;i--)
    {
        int v = finished[i];
        if(visited[v])
            continue;
        cout<<"强连通分量："<<endl;
        olDFS(v,visited);
    }

    delete []visited;
    delete []finished;
}

template<class T>
void Graph<T>::tarjan()
{
    count = 0;
    int *dfn = new int[_algraph.vexNum];
    int *low = new int[_algraph.vexNum];
    for(int i = 0; i< _algraph.vexNum;i++)
    {
        dfn[i] = -1;
        low[i] = -1;
    }

    Stack<int> s;

    for(int i = 0; i< _algraph.vexNum;i++)
    {
        if(dfn[i] != -1)
            continue;
        tarjanSub(i,dfn,low,s);
    }
    delete []dfn;
    delete []low;
}

template<class T>
void Graph<T>::tarjanSub(int vex,int *dfn,int *low,Stack<int> &s)
{
    dfn[vex] = low[vex] = count++;
    s.push(vex);
    ArcNode *p = _algraph.vertexs[vex].firstArc;
    while(p)
    {
        int j = p->adjvex;
        if(dfn[j] == -1) //not visited
        {
            tarjanSub(j,dfn,low,s);
            low[vex] = MIN(low[vex],low[j]);
        }
        else
        {
            low[vex] = MIN(low[vex],dfn[j]);
        }
        p = p->next;
    }
    if(dfn[vex] == low[vex])
    {
        cout<<"强连通分量:"<<endl;
        int t;
        do
        {
            s.pop(t);
            cout<<_algraph.vertexs[t].data<<endl;
        }while(!s.empty() && t != vex);
    }
}

template<class T>
void Graph<T>::gabow()
{
    count = 0;
    int *dfn = new int[_algraph.vexNum];
    int *belong = new int[_algraph.vexNum];
    for(int i = 0; i< _algraph.vexNum;i++)
    {
        dfn[i] = -1;
        belong[i] = -1;
    }

    Stack<int> s1;
    Stack<int> s2;

    for(int i = 0; i< _algraph.vexNum;i++)
    {
        if(dfn[i] != -1)
            continue;
        gabowSub(i,dfn,belong,s1,s2);
    }
    delete []dfn;
    delete []belong;
}

template<class T>
void Graph<T>::gabowSub(int vex,int *dfn,int *belong,Stack<int> &s1,Stack<int> &s2)
{
    int t;
    dfn[vex] = count++;
    s1.push(vex);
    s2.push(vex);
    ArcNode *p = _algraph.vertexs[vex].firstArc;
    while(p)
    {
        int j = p->adjvex;
        if(dfn[j] == -1) //not visited
        {
            gabowSub(j,dfn,belong,s1,s2);
        }
        else if(belong[j] == -1) //hava visited
        {
            s2.getTop(t);
            while(dfn[t] > dfn[j])
            {
                s2.pop(t);
                s2.getTop(t);
            }
        }
        p = p->next;
    }

    s2.getTop(t);
    if(t == vex)
    {
        s2.pop(t);
        cout<<"强连通分量:"<<endl;
        do
        {
            s1.pop(t);
            belong[t] = 1;
            cout<<_algraph.vertexs[t].data<<endl;
        }while(!s1.empty() && t!= vex);
    }
}

template<class T>
void Graph<T>::prim()
{
    struct closedge
    {
        int adjvex;
        int lowcost;
    };
    closedge *edge = new closedge[_mgraph.vexNum];

    int k = 0; // k 当前最小节点 头
    for(int i = 0;i<_mgraph.vexNum;i++)//初始化
    {
        edge[i].adjvex = k;
        edge[i].lowcost = INT_MAX;
    }

    cout<<"找到的最小生成树如下："<<endl;
    for(int i = 0;i<_mgraph.vexNum-1;i++) //n-1条边
    {
        edge[k].lowcost = -1; // k 点 到其他点的距离
        for(int j = 0;j<_mgraph.vexNum;j++) //更新最小值
        {
            if(_mgraph.adjMatrix[k][j] < edge[j].lowcost)
            {
                edge[j].adjvex = k; //最小值对应的
                edge[j].lowcost = _mgraph.adjMatrix[k][j];
            }
        }

        int min = INT_MAX;
        for(int j = 0;j<_mgraph.vexNum;j++)
        if(edge[j].lowcost != -1 && edge[j].lowcost < min)
        {
            min = edge[j].lowcost;
            k =j;
        }

        cout<<"("<<_mgraph.vertexs[edge[k].adjvex]<<","<<_mgraph.vertexs[k]<<")"<<endl;
    }

    delete []edge;
}

int main()
{
    Graph<char> gph;

    //邻接矩阵-无向网-最小生成树
    //gph.createUDN();
    //gph.prim();
    //gph.destroyUDN();

    //邻接表- 深度/广度 优先搜索
    //gph.createAlGraph();
    //gph.alBFS();
    //gph.alDFS();
    //gph.destroyAlGraph();

    /* 邻接表-深度优先生成树 */
    //cout<<"邻接表-深度优先生成树[孩子兄弟链表]:"<<endl;
    //gph.createAlGraph();
    //TreeNode<char> *tree;
    //gph.DFSForest(tree;)
    //gph.visitTree(tree);
    //gph.destroyAlGraph();

    //十字链表-kosaraju求强连通分量
    //gph.createOlGraph();
    //gph.kosaraju();
    //gph.destroyOlGraph();

    //邻接表-tarjan/gabow 求强连通分量
    //gph.createAlGraph();
    //cout<<"邻接表-tarjan 求强连通分量"<<endl;
    //gph.tarjan();
    //cout<<"邻接表-gabow 求强连通分量"<<endl;
    //gph.gabow();
    //gph.destroyAlGraph();

    return 0;
}
