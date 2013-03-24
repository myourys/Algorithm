/*=============================================================================
#     FileName: InternalSort.cpp
#         Desc: 内部排序算法
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2013-03-25 00:02:24
#      History:
=============================================================================*/

#include<iostream>
#include <stdlib.h>
using namespace std;

int s[10]={8,1,0,3,9,7,2,4,6,5};
int n = 10;

void swap(int &a,int &b)
{
    int t = a;
    a = b;
    b = t;
}

/*
 * 冒泡排序
 * O(n^2)
 * 每次循环将最大的数放在前面
 */
void BubbingSord()
{
    int i,j,t,pos;
    for(i=0;i<n-1;i++)
    {
        t=s[i];
        pos = i;
        for(j=i+1;j<n;j++)
        {
            if(s[j]>t)
            {
                pos = j;
                t = s[j];
            }
        }
        if(i!=pos)
            swap(s[i],s[pos]);
    }
}

/*
 * 快速排序
 * O(n*logn)
 * 以开头第一个元素为中间点,大的放在前面,小的放在后边,递归排序
 * 分别从后往前搜索,将大数放前面,然后从前往后搜索,将小的放在后边
 */
void FastSord(int begin,int end)
{
    if(begin>=end) return; //重合点
    // a,b 为前后搜索的定位点,e为中间点
    int a = begin,b = end;
    int e = a;

    //从后往前搜索
    for(b=end;b>a;b--)
    {
        if(s[b]>s[e])
        {
            swap(s[e],s[b]);
            e=b;
            //从前往后搜索
            for(a = a+1;a<b;a++)
            {
                if(s[a]<s[e])
                {
                    swap(s[e],s[a]);
                    e=a;
                    break;//反方向搜索
                }
            }
        }
    }
    FastSord(begin,e-1);
    FastSord(e+1,end);
}

int main()
{
//    BubbingSord();
    FastSord(0,9);
    for(int i =0;i<n;i++)
        cout<<s[i];
    return 0;
}
