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

#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

void swap(int &a,int &b)
{
    int t = a;
    a = b;
    b = t;
}

/*
 * 冒泡排序
 * 从第一个数开始,循环和旁边的数比较,如果后边小,则交换,因此轮交换过后最小数到最前面
 * O(n^2) =  (n-1)*n/2
 *
 */
void BubbingSort(int s[],int n)
{
    int i,j;
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if(s[j]<s[i])
                swap(s[i],s[j]);
}

/*
 * 简单选择排序
 * O(n^2) =  (n-1)*n/2
 * 对冒泡的一种改进，减少交换次数，如果内循环元素比外循环元素大，则记下位置和大小，内循环完成后得到最大的数
 * 每次外循环将最大(小)的数放在前面
 */
void SimpleSelectSort(int s[],int n)
{
    int i,j,t,pos;
    for(i=0;i<n-1;i++)
    {
        t=s[i];
        pos = i;
        for(j=i+1;j<n;j++)
        {
            if(s[j]<t)
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
 * 以开头第一个元素为中间点,小的放在前面,大的放在后边,递归排序
 * 分别从后往前搜索,将大数放前面,然后从前往后搜索,将小的放在后边
 */
void QuickSort(int s[],int begin,int end)
{
    if(begin>=end) return; //重合点
    // a,b 为前后搜索的定位点,e为中间点
    int a = begin,b = end;
    int e = a;

    //从后往前搜索
    for(b=end;b>a;b--)
    {
        if(s[b]<s[e])
        {
            swap(s[e],s[b]);
            e=b;
            //从前往后搜索
            for(a = a+1;a<b;a++)
            {
                if(s[a]>s[e])
                {
                    swap(s[e],s[a]);
                    e=a;
                    break;//反方向搜索
                }
            }
        }
    }
    QuickSort(s,begin,e-1);
    QuickSort(s,e+1,end);
}

/*
 * 插入排序
 * O(n^2)
 * 算法适用于少量数据的排序
 *⒈ 从第一个元素开始，该元素可以认为已经被排序
 *⒉ 取出下一个元素，在已经排序的元素序列中从后向前扫描
 *⒊ 如果该元素（已排序）大于新元素，将该元素移到下一位置
 *⒋ 重复步骤3，直到找到已排序的元素小于或者等于新元素的位置
 *⒌ 将新元素插入到下一位置中
 *⒍ 重复步骤2
 */

void InsertSort(int s[],int n)
{
    int i,j;
    for(i=0;i<n-1;i++) //i前面都是排好序的数列
       for(j=i+1;j>0 && s[j] < s[j-1];j--) // 大数往前面冒泡
           swap(s[j],s[j-1]);

}
/*
 * 折半插入排序
 * O(n^2)
 * 只能减少插入排序的比较次数，移动次数不变
 */
void BInsertSort(int s[],int n)
{
    int i,j,begin,end,mid,t;
    for(i=0;i<n-1;i++) //i前面都是排好序的数列
        if(s[i+1]<s[i])
        {
            begin = 0;
            end = i;
            // 找到最接近的右侧点
            while(begin<=end)
            {
                mid = (begin+end)/2;
                if(s[i+1]<s[mid])
                    end = mid-1;
                else
                    begin = mid+1;
            }
            t = s[i+1];
            //记录后移
            for(j=i;j>=begin;j--)
                s[j+1]=s[j];
            s[begin]= t;
        }
}

/*
 * 希尔排序
 * O(N*(logN)2)
 * 希尔排序是插入排序的一种。
 * 如此例第一次分为5组,上下为一组,然后每组排序
 * 8,1,3,0,9           得到: 8,2,4,6,9
 * 7,2,4,6,5                 7,1,3,0,5
 * 然后分为5/2=2组,每组排列...
 * 直至分为1组就是有序了
 */
void ShellSort(int s[],int n)
{
    int i,j;
    for(int gap =n/2;gap>0;gap /=2) //每次折半
        for(i=gap;i<n;i++) //从第二行数据开始,直接插入排序
        {
            for(j=i-gap;j>=0 && s[j+gap]<s[j];j-=gap) //与之前一列数据比较,此处参考插入排序
                swap(s[j],s[j+gap]);
        }
}

/*
 * 基数排序
 * O (nlog(r)m)，其中r为所采取的基数，而m为堆数
 * 在某些时候，基数排序法的效率高于其它的比较性排序法
 * 即:先按个位排序,然后按十位排序...
 */

void RadixSort(int m[],int n)
{
    int w = 6,j,k,r=1; //最大6位数
    for(int i = 1;i<=w;i++)
    {
        for(j=1;j<n;j++) //插入排序
            for(k=j-1;k>=0 && m[k+1]/r % 10 < m[k]/r %10;k--)
                swap(m[k],m[k+1]);

        r*=10;
    }
}



/*
 * 堆排序
 */

/*
 * 归并排序
 * O(N*logN)
 * 将两个有效数列合并成一个,因此可以考虑分成两个1组,2组合并成1组,直至整个数列完成
 */
void Merge(int a[], int b[], int low, int mid, int high)  //将A序列的两组(low-mid,mid+1-high),合并到同大小的b中
{
    int k = low;
    int begin1 = low;
    int end1 = mid;
    int begin2 = mid + 1;
    int end2 = high;
    while(k <= high )
    {
        if(begin1 > end1) //第1组完成,将第二组附加上去
            b[k++] = a[begin2++];
        else if(begin2 > end2)
            b[k++] = a[begin1++];
        else
        {
            if(a[begin1] <= a[begin2])
                b[k++] = a[begin1++];
            else
                b[k++] = a[begin2++];
        }
    }
}


//合并序列
void SubMerge(int a[], int b[], int ibegin, int mid,int iend)
{
   int pos = ibegin,i,j;
   for(i=ibegin,j=mid;i<=mid-1&&j<=iend;)
   {
       if(a[i]>a[j])
           b[pos++] = a[j++];
       else
           b[pos++] = a[i++];
   }
   while(i<=mid-1)
       b[pos++] = a[i++];
   while(j<=iend)
       b[pos++] = a[j++];

   //同时保持a也有序
   for(i=ibegin;i<=iend;i++)
	   a[i]=b[i];
}

/*
 * 将a中的从seg开始，长度为size的数排好序
 */

void SubMergeSort(int a[], int b[], int seg, int size)
{
    if(size>=2)
    {
        SubMergeSort(a,b,seg,size/2);//前一半合并到b中
        SubMergeSort(a,b,seg+size/2,size-size/2);//后一半合并到b中
		SubMerge(b,a,seg,seg+size/2,seg +size-1); //保持a,b都有序
    }
}

void MergeSort(int a[],int size)
{
	int *t=a;
    int *temp=new int[size];
	for(int i=0;i<size;i++)
		temp[i]=a[i];
	SubMergeSort(a,temp,0,size);
    delete []temp;
}

/*
 * 堆排序 [采用数组排序]
 * O(N * logN)
 * 1．父结点的键值总是大于或等于（小于或等于）任何一个子节点的键值。
 * 2．每个结点的左子树和右子树都是一个二叉堆（都是最大堆或最小堆）
 * i结点的父结点下标就为(i – 1) / 2，孩子2 * i + 1和2 * i + 2
 * 由于每次重新恢复堆的时间复杂度为O(logN)，共N - 1次重新恢复堆操作，再加上前面建立堆时N / 2次向下调整，
 * 每次调整时间复杂度也为O(logN)。二次操作时间相加还是O(N * logN)。故堆排序的时间复杂度为O(N * logN)
 */
void MiniHeap(int a[],int n); //堆话数组 ->建立最小堆
void MinHeapFixdown(int a[],int i,int n); //调整堆元素
void HeapSort(int a[],int n)
{
	int* t = new int[n];
	for(int i=0;i<n;i++)
		t[i]=a[i];
	MiniHeap(t,n);//建立堆
	for(int i=0;i<n;i++)
	{
		a[i] = t[0];
		t[0] = t[n-i-1];//删除堆顶，并调整堆,使堆顶是最小元素
		MinHeapFixdown(t,0,n-i);
	}
	delete []t;
}

void MiniHeap(int a[],int n) //堆话数组 ->建立最小堆
{
	//i 从最后一个不是叶子节点的位置开始调整堆
	for(int i= n/2 - 1;i>=0;i--)
		MinHeapFixdown(a,i,n);
}

void MinHeapFixdown(int a[],int i,int n) //大数下沉，自下而上
{
	int child = 2*i+1; //左孩子
	if(child>=n)//无左右孩子
		return;
	if(child+1<n && a[child+1]<a[child]) //找到左右孩子最小的
		child++;
	if(a[child]>=a[i]) //如果本身就是有序的
		return;
	swap(a[i],a[child]);
	MinHeapFixdown(a,child,n);//孩子继续下沉
}

/*
 * 桶排序
 * 类似Hash,采用分治的思想
 * O(N)-O(N^2)
 */

struct Bucket //桶结构
{
    int* s;
    int size;
    Bucket()
    {
        s =NULL;
        size = 0;
    }
};

void BucketSort(int a[],int n)
{
	Bucket b[1000]; //1千个桶
    for(int i=0;i<1000;i++)
        b[i].s = new int[n];
    //假如数在[0~1,000,000) 之间,分桶
    int t;
    for(int i = 0;i<n;i++)
    {
        t = a[i]/1000;
        b[t].s[b[t].size++] = a[i];
    }
    int pos =0;
    for(int i=0;i<1000;i++)
    {
        if(b[i].size >0)
        {
            QuickSort(b[i].s,0,b[i].size-1); //桶中数字排序
            for(int j=0;j<b[i].size;j++)
                a[pos++] = b[i].s[j];
        }
        delete []b[i].s;
    }
}

int main()
{
	int Flag = 0;

    srand(time(NULL));
	while(Flag < 10)
	{
		Flag++;
		int n = 1000000;
		int* s =new int[n];
		for(int i=0;i<n;i++)
			s[i] = rand() %1000000; //注rand()产生的数在0到RAND_MAX之间
		clock_t ibegin, iend;
		ibegin = clock();

        bool isSort = true;
		switch(Flag)
		{
		case 19:
			cout<<"冒泡排序【BubbingSort】："<<endl;
			BubbingSort(s,n);break;
		case 29:
			cout<<"简单选择排序【SimpleSelectSort】："<<endl;
			SimpleSelectSort(s,n);break;
		case 3:
			cout<<"快速排序【QuickSort】："<<endl;
			QuickSort(s,0,n-1);break;
		case 49:
			cout<<"插入排序【InsertSort】："<<endl;
			InsertSort(s,n);break;
		case 59:
			cout<<"折半插入排序【BInsertSort】："<<endl;
			BInsertSort(s,n);break;
		case 6:
			cout<<"希尔排序【ShellSort】："<<endl;
			ShellSort(s,n);break;
		case 7:
			cout<<"归并排序【MergeSort】："<<endl;
			MergeSort(s,n);break;
		case 8:
			cout<<"堆排序【MiniHeap】："<<endl;
			HeapSort(s,n);break;
		case 99:
			cout<<"基数排序【RadixSort】："<<endl;
			RadixSort(s,n);break;
		case 10:
			cout<<"桶排序【BucketSort】："<<endl;
	            BucketSort(s,n);break;
        default:
            isSort = false;
		}
		iend = clock();
		if(iend - ibegin>0.1 && isSort)
			cout<<"时间（毫秒）："<<iend - ibegin<<endl<<endl;

		//for(int i =0;i<n;i++)
		//	cout<<s[i]<<"  ";

        delete []s;
	}

    return 0;
}


