/*=============================================================================
#     FileName: Boyer-Moore.cpp
#         Desc: 字符串搜索Boyer-Moore算法
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2014-09-01 16:10:58
#      History:
=============================================================================*/

/*
 * 不同于KMP搜索算法从左往右匹配，BM算法从子串的右边开始搜索，平均比KMP快3~5倍;
 * BM算法广泛用于grep,IDE的字符串搜索。
 *
 * 算法详细解释：
 * <http://www.ruanyifeng.com/blog/2013/05/boyer-moore_string_search_algorithm.html>
 */

#include <iostream>
using namespace std;

/*
 * 好后缀表，数组长度为查询串的长度
 * 数组下标表示字符在查询串的位置
 * `bmGs[i] = m` 表示为：i后的字符都匹配的情况下，移动的距离
 */

void getGoods(const char* T,int bmGs[])
{
    int tLen = strlen(T);

    //辅助数组suff，suff[i]=m表示在i的位置，并往前搜索，与末尾匹配的长度为m
    int suff[tLen];
    suff[tLen-1] = tLen;
    for(int i = tLen-2; i>=0; i--)
    {
        int j = i;
        while(j>=0 && T[j] == T[tLen-1 -i +j]) //tLen-1 -i +j = 匹配串最后一个字母往前搜索
            j--;
        suff[i] = i-j;
    }

    //case 3（默认）：如果完全不存在和好后缀匹配的子串，则右移整个模式串。
    for(int i=0;i<tLen;i++)
        bmGs[i] = tLen+ tLen-1 -i; //字符串长度 + 已经移动的距离

    int j =0;
    //只有前缀匹配（部分匹配）
    for(int i=tLen -1;i>=0;i--)
    {
        if(suff[i] == i+1) //0~i的前缀串与后缀串是匹配的,但匹配长度可能不一致
        {
            for(;j<tLen -1 -i;j++)
            {
                if(bmGs[j] == tLen + tLen-1 - j) //如果为默认值
                    bmGs[j] = tLen-1 - j + tLen -1 -i; //已经移动的距离 + 对齐前缀串
            }
        }
    }

    //完全匹配
    for(int i = 0; i <= tLen - 2; i++)
    {
        //i:被匹配的子串的结束位置
        //tLen -1 -suff[i] : 末尾 - 后缀的长度 = 匹配的开始位置
        // = 子串与末尾对齐 + 子串的长度
        bmGs[tLen - 1 - suff[i]] = tLen - 1 - i +  suff[i];
    }
}

/*
 * 获取256位的坏字符数组
 */
void getBads(const char* T,int bmBs[])
{
    int len = strlen(T);
    for( int i = 0; i < 256; i++ ) //默认所有未出现的字符移动距离为字符串长度
        bmBs[i] = len;
    while(len>0)
    {
        bmBs[(unsigned int)*T++] = --len; //字符串后面的字符会覆盖前面相同的字符，表示离其右边最近出现的位置
    }
}

int BMSearch(const char* S,const char *T)
{
    int tLen = strlen(T);
    int sLen = strlen(S);

    int goods[tLen];
    int bads[256]; //字符集256

    getGoods(T,goods);
    getBads(T,bads);

    int i = tLen;
    while(i<=sLen)
    {
        int j = tLen;
        while(S[--i] == T[--j])
        {
            if(j==0)
                return i;
        }

        //已搜索的当前位置i向后移动
        int skipBad = bads[(unsigned int)S[i]]; //坏字符移动位数
        int skipGood = goods[j];

        //针对与坏字符：
        //1.上面循环减了1，这里要加上来
        //2.如果查询字符串的一个字符出现两次，且坏字符出现在第二次,这时已经移动的次数可能比坏字符移动字典还多
        //但加上好后缀的判定后，这种情况适合用好后缀
        //i += (tLen - j> skipBad ? tLen:skipBad) +1;

        i+= (skipBad > skipGood ? skipBad:skipGood) +1;
    }


    return -1;
}

int main()
{
    cout<<BMSearch("here is a simple example.","example")<<endl;
    cout<<BMSearch("abcde-acde.","acdac")<<endl;
    cout<<BMSearch("abcdeac-acdace.","acdac")<<endl;
    cout<<BMSearch("abaxxcba","cba")<<endl;
    return 0;
}


