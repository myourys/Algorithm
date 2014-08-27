/*=============================================================================
#     FileName: AStar.cpp
#         Desc: A星寻路算法
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2014-08-21 18:48:40
#      History:
=============================================================================*/
/*
 * A*算法不同于深度和广度优先算法，是一种启发式搜索算法
 * 其主要逻辑是不断估算当前点到目的节点的大概距离，选取最优的路径不断前进，直至到达终点。过程如下：
 * 1. 将当前点放如一个未处理的节点列表，叫做openList，另外有个已处理的节点列表叫做closeList.
 * 2. 从openList中找到最优节点n（可用堆算法|优先队列），针对其每一个子节点x：
 *      a. 如果x在open中，如果x比open中节点的更好，则替换open中的节点，否则跳过x
 *      b. 如果x在close中，如果x比close中的节点更好，则要删掉close中的节点，并将x放到open中，代表重新处理。否则跳过x.
 *      c. 如果x不在open和close中，则放入open中，代表需要处理。
 * 3. 重复2，直至到目标节点。到了目标节点后，从目标节点一步步后退，即可找到来的路径。
 *
 * 估价函数 f'(n) = g'(n) + h'(n)
 * f'(n)是估价函数，g'(n)是起点到终点的最短路径值，h'(n)是n到目标的最短路经的启发值。
 */

#include <iostream>
#include <queue> /* priority_queue不支持遍历，利用vector容器和push_heap(堆算法)模拟一个优先容器 */
#include <vector>
#include <sstream>

#define STR(A) #A

using namespace std;

/* 地图
 * 第一行 行列数
 * 第二行 起点，终端坐标
 * 地图 0:可通过 1:不可通过
 * 这里我们设定一个节点到相邻节点消耗为10，如果是对接线则为14.
 */

const char* MapStr = STR(
9 10                \n
2 3    2 6          \n
0 0 0 0 1 0 0 0 0 0 \n
0 0 0 0 1 0 0 0 0 0 \n
0 0 0 0 1 0 0 0 0 0 \n
0 0 1 1 1 0 0 0 0 0 \n
0 0 1 1 0 0 0 0 0 0 \n
0 0 1 0 0 0 0 0 0 0 \n
0 0 1 0 1 0 0 0 0 0 \n
0 0 0 0 1 0 0 0 0 0 \n
0 0 0 0 1 0 0 0 0 0 \n
);

class Point
{
public:
    int x,y;
    Point& operator=(const Point & other){this->x = other.x;this->y=other.y;return *this;};
    bool operator==(const Point & other){return this->x == other.x && this->y== other.y;};
};

typedef struct _Node{
    Point pos;//当前点在迷宫中的位置坐标
    int g;//起始点到当前点实际代价
    int h;//当前节点到目标节点最佳路径的估计代价
    int f;//估计函数：f = g + h。
    _Node *father;//指向其父节点的指针 
}Node;

//比较函数，用于堆操作
struct NodeCompare
{
    bool operator ()(Node *&n1, Node *&n2) const
    {
        return n1->f > n2->f; //小值优先
    }
};


class AStar{

public:
    AStar():_map(nullptr){};
    ~AStar(){clear();};
    int readMap(const char* str);
    void printMap();
    bool findRoad();
    void printRoad();
    void clear();
private:
    int estimate(const Point& pos); //估计点到目的地的值
    void initNode(Node &node,const Point& pos,int g,Node* father);
private:
    Point _mapSize;
    Point _startPos;
    Point _endPos;
    int **_map;
    vector<Node*> _closeList;
    vector<Node*> _openList;
};

void AStar::clear()
{
    for(auto iter:_closeList)
        delete iter;
    for(auto iter:_openList)
        delete iter;
    if(_map)
    {
        for(int i =0;i<_mapSize.x;i++)
            delete []_map[i];
        delete []_map;
    }

}


int AStar::estimate(const Point& pos)
{
    return 10* (abs(_endPos.x - pos.x) + abs(_endPos.y-pos.y));
}

int AStar::readMap(const char* str)
{
    istringstream istr(str);

    istr>>_mapSize.x>>_mapSize.y;
    istr>>_startPos.x>>_startPos.y;
    istr>>_endPos.x>>_endPos.y;

    _map = new int *[_mapSize.x];
    for(int i = 0;i< _mapSize.x;i++)
    {
        _map[i] = new int[_mapSize.y];
        for(int j = 0;j< _mapSize.y;j++)
        {
            istr>>_map[i][j];
        }
    }
    return 0;
}

void AStar::printMap()
{
    for(int i = 0;i< _mapSize.x;i++)
    {
        for(int j = 0;j< _mapSize.y;j++)
        {
            cout<<_map[i][j]<<" ";
        }
        cout<<endl;
    }
}

void AStar::initNode(Node &node,const Point& pos,int g,Node* father)
{
    node.pos= pos;
    node.g = g;
    node.h = estimate(pos);
    node.f = node.g +node.h;
    node.father = father;
}

bool AStar::findRoad()
{
    Node *start = new Node();
    initNode(*start,_startPos,0,nullptr);

    _openList.push_back(start);
    push_heap(_openList.begin(),_openList.end(),NodeCompare());
    while(1)
    {
        if(_openList.empty())
        {
            cout<<"can't find the road."<<endl;
        }
        Node *n = _openList.front();

        if(n->pos == _endPos) //到达终点
        {
            cout<<"Find the Road:"<<endl;
            return true;
        }

        //将第一个元素移到最后，并将剩余区间重新排序，组成新的heap
        pop_heap(_openList.begin(),_openList.end(),NodeCompare());
        _openList.pop_back();//删除最后一个元素n

        for(int x = n->pos.x-1;x<= n->pos.x+1; x++) //针对每一个子节点
        {
            if(x < 0 || x > _mapSize.x -1)
                continue;
            for(int y = n->pos.y-1; y<= n->pos.y+1; y++)
            {

                if(y < 0 || y > _mapSize.y -1)
                    continue;
                Point pos;
                pos.x = x; pos.y = y;

                if(pos == n->pos)
                    continue;

                if(_map[x][y] == 1) //不可通过的点
                    continue;

                int gVal;
                if(x == n->pos.x || y == n->pos.y)
                    gVal= n->g +10;
                else
                    gVal=n->g +14; //对角线

                vector<Node*>::iterator openResult;
                for( openResult=_openList.begin();openResult!= _openList.end();++openResult)
                {
                    if((*openResult)->pos == pos) //在open列表
                        break;
                }

                //在open列表，并且open列表中已经是最优的，跳过
                if(openResult!= _openList.end() && (*openResult)->g <= gVal)
                    continue;

                //closed列表
                vector<Node*>::iterator closeResult;
                for( closeResult=_closeList.begin();closeResult!= _closeList.end();closeResult++)
                {
                    if((*closeResult)->pos == pos) //在close列表
                        break;
                }

                //在close列表，并且close列表中已经是最新的了，跳过
                if(closeResult!= _closeList.end() && (*closeResult)->g <= gVal)
                    continue;

                //新节点为最优节点
                //如果在close列表
                if(closeResult != _closeList.end())
                {
                    _closeList.erase(closeResult);
                    delete *closeResult;
                }

                //如果在open列表
                if(openResult!= _openList.end())
                {
                    _openList.erase(openResult);
                    make_heap(_openList.begin(),_openList.end(),NodeCompare());
                    delete *openResult;
                }

                Node *child = new Node();
                initNode(*child,pos,gVal,n);
                _openList.push_back(child);
                push_heap(_openList.begin(),_openList.end(),NodeCompare());
            }
        }

        _closeList.push_back(n);
    }
    return false;
}

void AStar::printRoad()
{
    int **tmpMap = new int*[_mapSize.x];
    for(int i=0;i<_mapSize.x;i++)
        tmpMap[i] = new int[_mapSize.y];
    for(int i=0;i<_mapSize.x;i++)
        for(int j=0;j<_mapSize.y;j++)
            tmpMap[i][j]=_map[i][j];
    Node* n= _openList.front();
    while(n)
    {
        tmpMap[n->pos.x][n->pos.y] = -1;
        n = n->father;
    }

    for(int i=0;i<_mapSize.x;i++)
    {
        for(int j=0;j<_mapSize.y;j++)
        {
            if(tmpMap[i][j] == -1)
                cout<<"# ";
            else
                cout<<tmpMap[i][j]<<' ';
        }

        cout<<endl;
    }

    for(int i=0;i<_mapSize.x;i++)
        delete []tmpMap[i];
    delete []tmpMap;
}

int main()
{
    AStar astar;
    astar.readMap(MapStr);
    if(astar.findRoad())
        astar.printRoad();
    return 0;
}
