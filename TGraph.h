/*=============================================================================
#     FileName: TGraph.h
#         Desc: 数据结构-图
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2014-09-16 00:19:20
#      History:
=============================================================================*/

#ifndef _TGRAPH_H
#define _TGRAPH_H

#include <iostream>
#include "TStack.h"

template <class T>
struct TreeNode
{
    T data;
    TreeNode<T> *lchild,*nextSibling; //孩子兄弟链表
};

template <class T>
class Graph
{
public:
    /*邻接矩阵*/
    void createUDN(); //无向网
    void destroyUDN();

    void createDN(); //有向图
    void destroyDN();

    /*领接表*/
    void createAlGraph();
    void destroyAlGraph();

    void alDFS(); //深度优先搜索
    void alBFS(); //广度优先搜索

    void DFSForest(TreeNode<T> *&tree); //深度优先生成树
    void DFSForestSub(int vex,TreeNode<T> *&parent,bool *visited);
    void visitTree(TreeNode<T> *tree);

    /*十字链表*/
    void createOlGraph();
    void destroyOlGraph();
    /*
     * 强连通分量
     * 指有向图中,最大的两两相互可以到达的点。
     * 缩点: 在大量分析中,可以将一个强连通分量作为一个点
     */
    /*
     * Kosaraju算法 - 强连通分量
     * 基于有向图的强连通分量与其逆向图是一样这个事实
     * 这里用十字链表，少了生成逆向图这一步
     */
    void kosaraju();
    void olDFS(int v,bool *visited,int *finished); //顺向
    void olDFS(int v,bool *visited);//逆向

    /*
     * Tarjan算法 - > <http://blog.sina.com.cn/s/blog_9dd49f8101013ygb.html>
     * 一次遍历求强连通分量,这里用邻接表作为示例
     */
    void tarjan();
    void tarjanSub(int vex,int *dfn,int *low,Stack<int> &s);

    /*
     * Gabow算法 - 求强连通分量 <http://www.cppblog.com/sosi/archive/2010/09/27/127863.aspx>
     * 是Tarjan算法的变异体，利用第二个堆栈来辅助求出强连通分量的根，而不是Tarjan算法里面的DFN[]和Low[]数组。
     */
    void gabow();
    void gabowSub(int vex,int *dfn,int *belong,Stack<int> &s1,Stack<int> &s2);
protected:
    void alSubDFS(int vex,bool *visited);
private:
    int count; //辅助变量

    /* 存储方式1 - 邻接矩阵
     * 存储顶点列表，和已顶点为边的二维数组表述边信息
     */
    struct MatrixGraph{
        int vexNum;
        int arcNum;
        T *vertex;  //顶点
        int **adjMatrix; //边
    };
    MatrixGraph _mgraph;


    /*
     * 存储方式2 - 邻接表
     * 存储顶点列表，每个顶点存储
     */

    struct ArcNode //弧
    {
        int adjvex; //该条弧指向的顶点序号
        ArcNode *next; //下一条弧
        float weight;//边的权重
    };

    struct VNode //顶点
    {
        T data;
        ArcNode *firstArc; //顶点对应的边
    };

    struct AlGraph //邻接表
    {
        int vexNum;//顶点数
        int arcNum;//边数
        bool kind;//种类
        VNode *vertexs; //顶点
    };
    AlGraph _algraph;

    /*
     * 存储方式3 - 十字链表
     */
    struct ArcBox //弧
    {
        int tailVex; //弧头位置
        int headVex; //弧尾位置
        ArcBox *hlink;//与弧头相同的下一条弧
        ArcBox *tlink;//与弧尾相同的下一条弧形
        float weight;
    };

    struct VexNode
    {
        T data;
        ArcBox *firstIn;//第一个入弧
        ArcBox *firstOut;//第一个出弧
    };

    struct OlGraph
    {
        int vexNum;//顶点数
        int arcNum;//边数
        VexNode *vertexs;
    };
    OlGraph _olgraph;

};

#endif
