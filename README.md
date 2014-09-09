Algorithm
=========
1. 一些数据结构和算法的实现,均由本人学习算法时所写，目的是为了加强对算法的理解。
2. 实现这些算法的时间跨度比较大，编码风格未必一致。
3. 代码内均有详细的注释，请参考代码内部的讲解或参考链接进行学习。

##字符串搜索
###1.暴力搜索和KMP的实现
`KMP.cpp`

###2.BM算法
`Boyer-Moore.cpp`: Boyer-Moore搜索算法

##内部排序
InternalSort.cpp

    BubbingSort         冒泡排序 O(n^2)
    SimpleSelectSort    简单选择排序 O(n^2)
    QuickSort           快速排序O(n*logn)
    InsertSort          插入排序O(n^2)
    BInsertSort         折半插入排序O(n^2)
    ShellSort           希尔排序 O(N*(logN))
    RadixSort           基数排序O(nlog(r)m)
    MergeSort           归并排序O(n*log(n))
    HeapSort            堆排序O(n*log(n)
    BucketSort          桶排序O(N)~O(n^2)

##普通容器

###1.动态数组
`TArray.h`

###2.链表
1. C++模板类实现
>`TList.h` 链表C++模版类实现   
 `TListTest.cpp` 测试文件
2. C 实现
>`CList.h` 线性表链式表示(c语言)    
`CListTest.c` 测试文件

###3.队列
`CQueue.h` 队列的基本操作（c实现）  
`CQueueTest.c` 测试文件

###4.栈
`TStack.h` 栈模版类实现   
`TStackTest.cpp` 测试文件

##树形容器

###1.二叉树
`TBiTree.h`,二叉树的模版类实现   
包括前中后递归非递归遍历,层次遍历,层次遍历求深度


###2.前缀树
`Trie.cpp`,实现并测试前缀串查找

###3.二叉排序树
`BSTree.cpp`,二叉排序树算法实现

###4.红黑树
`RBTree.cpp`,红黑树的C++模版类实现

##压缩算法
###1.Huffman
`Huffman.cpp`，实现Huffman编码,采用系统STL库,实现对文件的编码和解码,有两个txt的测试文件

##AI算法
###1.A*算法以及跳步算法的实现
`AStar.cpp`  跳步算法是对普通A星算法的改进  
ps：文件开始有一个是否启用跳步算法进行优化A星算法的开关
