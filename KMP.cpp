/*=============================================================================
#     FileName: KMP.cpp
#         Desc: 字符串搜索算法
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2013-03-27 01:49:43
#      History:
=============================================================================*/
/* 一般字符串搜索算法时间复杂度O(m*n) m,n分别为原串和子串的长度
 * KMP 时间复杂度 为 O(m+n)
 * 本文参考http://billhoo.blog.51cto.com/2337751/411486
 */
#include<iostream>
#include <stdlib.h>
using namespace std;

/*
 * 一般字符串查找函数,查找成功,返回在原串中的位置,否则返回-1
 * S[]原串,T[]待搜索的目标子串,pos 搜索起始点
 */

int StrSearch(const char S[],const char T[], int pos=0 )
{
    int i = pos, j = 0;
    //i 原串搜索位置,每次+1
    //j 子串被匹配长度,如果j等于子串长度,则匹配成功
    while ( S[i+j] != '\0'&& T[j] != '\0')
    if ( S[i+j] == T[j] )
        j ++; // 继续比较后一字符
    else
    {
        i ++; j = 0; // 重新开始新的一轮匹配
    }

    if ( T[j] == '\0')
        return i; // 匹配成功   返回下标
    else
        return -1; // 串S中(第pos个字符起)不存在和串T相同的子串
} 

/*
 * KM - 获取子串的模式值数组(前后缀串)
 * 即:即是前缀串又是后缀串的子串长度
 * 如:abcabca 为abca,即是4
 * KMP即是如果匹配了这7个字符,则跳3个字符(直接原串和T[4]比较),如下:
 * abcabcax
 *    abcabca
 */
void GetNext(const char *T,int next[])
{
     register int iLen = 0;    // Length of T
     while( '\0' != T[iLen] )
         iLen++;

     int LOLP = 0;     // Lenth of longest prefix,前后串
     next[1] = 0;
     next[0] = 0;
     for( int NOCM=2; NOCM<iLen+1; NOCM++ )     // NOCM represent the number of characters matched
     {
         //如:abaaba+b ,b!=T[3]
         //则判断 此前后串的长度3的前后串,
         //即aba的前后串(长度为1,为a),此时a后面为b,和新加的字符相同,跳出循环
         //得到新的字符串的前后串为ab
         while( LOLP>0 && (T[LOLP] != T[NOCM-1]) )
            LOLP = next[LOLP];

         if( T[LOLP] == T[NOCM-1] ) //如果新的字符也满足前后串,则前后串长度加1,如abcabc+a, a = T[3],前后串长度变为4
             LOLP++;
         next[NOCM] = LOLP;
     }
}

/*
 * KMP算法
 */

int KMPSearch(const char S[],const char T[])
{
    int SLen=0,TLen=0;
    while( '\0' != S[SLen] )
        SLen++;
    while( '\0' != T[TLen] )
        TLen++;

    int *next = new int[TLen];
    GetNext(T,next);
    int NOCM = 0;     // Number of characters matched

    for(int i=0;i<SLen;i++)//必须比较到最后一位
    {
        while(NOCM>0 && S[i]!=T[NOCM]) //如果前后串后字符不满足,则可以循环判断前后串的子前后串是否满足
            NOCM = next[NOCM];

        if(S[i]==T[NOCM])
            if((++NOCM) == TLen)
                return i-TLen+1;
    }
    if(NOCM!=TLen) return -1;
}


int main()
{
    cout<<StrSearch("abccabccabca","cabc")<<endl;
    cout<<KMPSearch("abccabccabca","cabc")<<endl;
    cout<<KMPSearch("abccabccabca","cabccabc")<<endl;

}

