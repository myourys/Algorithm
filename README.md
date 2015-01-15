Algorithm
=========
1. 一些数据结构和算法的实现,均由本人学习算法时所写，目的是为了加强对算法的理解。
2. 实现这些算法的时间跨度比较大，编码风格未必一致,前期代码主要用gcc编译，后期用clang编译。
3. 代码内均有详细的注释，请参考代码内部的讲解或参考链接进行学习。
4. 实现从c,c++混杂，到逐渐区分，后面的算法多用C++0x和STL容器（安全+效率）。

##字符串搜索
###1.暴力搜索和KMP的实现
`KMP.cpp`
>1. 一般字符串搜索算法时间复杂度O(m*n) m,n分别为原串和子串的长度
>2. KMP 时间复杂度 为 O(m+n),其利用待查询串的回文特性，构造一个Next数组，跳过那些有回文特性的不必要查询的字符。


###2.BM算法
`Boyer-Moore.cpp`: Boyer-Moore搜索算法
>1. bm算法时间复杂度为`n/m`,极坏情况下位`n*m`，广泛用于grep，IDE文件内容查找。
>2. 其构造一个坏字符表和一个好后缀表，用查询串从后往前搜索，并择优跳过不必搜索的字符。

##内部排序
`InternalSort.cpp` 包含下列所有内部排序方法以及时间测试对比

###1.复杂度 `O(N*(logN))`
1. QuickSort           快速排序
2. HeapSort            堆排序
3. MergeSort           归并排序
4. ShellSort           希尔排序 O(N*(logN))

###2.复杂度 `O(n^2)`
1. BubbingSort         冒泡排序 O(n^2)
2. SimpleSelectSort    简单选择排序 O(n^2)
3. InsertSort          插入排序O(n^2)
4. BInsertSort         折半插入排序O(n^2)

###3.复杂度-其他
1. RadixSort           基数排序O(nlog(r)m)   
2. BucketSort          桶排序O(N)~O(n^2)

##普通容器

###1.动态数组
`TArray.h`,利用c++模板类实现了一个动态数组，添加stdarg.h以便支持可变的函数参数。

可以了解系统和编译器是怎么处理多维数组问题，并加强对多维数组的理解。

###2.链表
1. C++模板类实现
>`TList.h` 链表C++模版类实现   
>`TListTest.cpp` 测试文件

2. C 实现
>`List.h` 线性表链式表示(c语言)    
>`ListTest.c` 测试文件

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
`BsTree.c`纯C语言实现        
`BSTree.cpp`C++模版类实现

###4.红黑树
`RBTree.cpp`,红黑树的C++模版类实现

##图论
`TGraph.h`、`TGragh.cpp`图论数据结构和相关算法

##压缩算法
###1.Huffman
`Huffman.cpp`，实现Huffman编码,采用系统STL库,实现对文件的编码和解码,有两个txt的测试文件

##AI算法
###1.A*算法以及跳步算法的实现
`AStar.cpp`  跳步算法是对普通A星算法的改进  
ps：文件开始有一个是否启用跳步算法进行优化A星算法的开关

##其他
`LRU.cpp` LRU近期最少使用数据缓存算法，完全用标准STL实现
