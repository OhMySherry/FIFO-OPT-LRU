[TOC]

# 虚存页面置换

## 问题描述

- 设计程序模拟先进先出FIFO，最佳置换OPT和最近最久未使用LRU页面置换算法的工作过程。假设内存中分配给每个进程的最小物理块数为m，在进程运行过程中要访问的页面个数为n，页面访问序列为P1, … ,Pn，分别利用不同的页面置换算法调度进程的页面访问序列，给出页面访问序列的置换过程，计算每种算法缺页次数和缺页率。

**程序要求如下：**

- 实现先进先出FIFO，最佳置换OPT和最近最久未使用LRU三种页面置换算法，模拟页面访问过程，并对三个算法进行评价。

## 实验环境

- Windows 11
- Visual Studio Code
- GCC version 8.1.0

## 输入

- 页面个数n
- 页面访问序列P~1~, … ,P~n~
- 算法选择1-FIFO，2-OPT，3-LRU，4-退出


## 输出

- 输出每次置换后的物理块，若命中则输出”hit”
- 输出每种算法的缺页次数和缺页率

## 测试数据

| 物理块数         | 3                                           |
| ---------------- | ------------------------------------------- |
| **页面个数**     | **20**                                      |
| **页面访问序列** | **4 3 2 1 4 3 5 4 3 2 1 5 6 2 3 7 1 2 6 1** |

## 实验设计

### 数据结构

```cpp
#define MAXSIZE 100 //页面最大数量
struct pagedata
{
    int id;    //页面号
    int visit; //被访问的标记
};
pagedata *block; //物理块
pagedata *page;  //页面
int blocknum;     //物理块数
int pagenum;      //合并的页面数
int sub[MAXSIZE]; //输入时用的数组
```

### 主要函数功能和参数

- `void ConverToPage()`

输入物理块数、页面个数以及页面访问序列

对页面进行初始化

- `void VisitClear()`

初始化页面结构体的visit变量

- `void BlockClear()`

初始化物理块结构体

- `int FindSpace()`

查找是否有空闲块

- `int FindExist(int curpage)`

curpage : 当前访问到的页面

查找内存中是否有该页面

- `int FindReplace()`

查找应予置换的页面

- `void ShowBlock(int index)`

index : 当前访问页面的索引

显示置换完一次后的内存信息

- `void FIFO()`

先进先出算法

输出每次置换后的物理块，若命中则输出”hit”

输出缺页次数和缺页率

- `void OPT()`

最佳置换算法

输出每次置换后的物理块，若命中则输出”hit”

输出缺页次数和缺页率

- `void LRU()`

最近最久未使用置换算法

输出每次置换后的物理块，若命中则输出”hit”

输出缺页次数和缺页率


### 详细设计

**页面置换的实现过程如下：**

1. 变量初始化；

2. 通过参数接收用户输入最小物理块数m，页面个数n，页面序列P~1~, … ,P~n~；

3. 根据用户选择的算法进行页面的分配和置换，输出页面置换算法的模拟过程；

4. 计算并输出选择算法的缺页次数和缺页率；

**主函数的实现过程如下：**

1. 变量初始化；

2. 用户输入最小物理块m，页面个数n，页面序列P~1~, … ,P~n~，选择算法1-FIFO，2-OPT，3-LRU，4-退出程序；

3. 根据选择的算法调用对应的页面置换算法。

### 流程图

![image-20220524224035424](https://s2.loli.net/2022/05/24/vWOEaP5FQnr6wtD.png)

## 实验结果与分析

### 结果展示与描述

- 输入基本信息

![image-20220524224144933](https://s2.loli.net/2022/05/24/dgs6zjNpaBtIcCr.png)

- FIFO

![image-20220524224209853](https://s2.loli.net/2022/05/24/N8nBJRypa4SWKhf.png)

- OPT

![image-20220524224323497](https://s2.loli.net/2022/05/24/mSCHxupc2nJ9zv3.png)

- LRU

![image-20220524224339079](https://s2.loli.net/2022/05/24/7FQDKMIWnVviptX.png)

- 退出程序

![image-20220524224439281](https://s2.loli.net/2022/05/24/9sSgWNoliaK1wAb.png)

### 结果分析

- 输入基本信息后，分别存储在内存和页面的结构体中
- 循环选择算法并执行，使用不同算法进行页面访问、置换的模拟，并输出对应的缺页次数和缺页率
- 输入4则退出程序

## 源代码

```cpp
#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

#define MAXSIZE 100 //页面最大数量
struct pagedata
{
    int id;    //页面号
    int visit; //被访问的标记
};
pagedata *block; //物理块
pagedata *page;  //页面
// 为便于测试 提前对以下两项赋值
int blocknum/* = 3*/;                                                                //物理块数
int pagenum/* = 20*/;                                                                //合并的页面数
int sub[MAXSIZE]/* = {4, 3, 2, 1, 4, 3, 5, 4, 3, 2, 1, 5, 6, 2, 3, 7, 1, 2, 6, 1}*/; //输入时用的数组

//分配页面
void ConverToPage()
{
    cout << "物理块数 : ";
    cin >> blocknum;
    cout << "页面数量 : ";
    cin >> pagenum;
    cout << "页面序列 : ";
    for (int i = 0; i < pagenum; i++)
    {
        cin >> sub[i];
    }
    page = new pagedata[pagenum];
    for (int i = 0; i < pagenum; i++)
    {
        page[i].id = sub[i];
        page[i].visit = 0;
    }
}

//页面的标记初始化
void VisitClear()
{
    for (int i = 0; i < pagenum; i++)
    {
        page[i].visit = 0;
    }
}

//物理块初始化
void BlockClear()
{
    for (int i = 0; i < blocknum; i++)
    {
        block[i].id = -1;
        block[i].visit = 0;
    }
}

//查找是否有空闲块
int FindSpace()
{
    for (int i = 0; i < blocknum; i++)
    {
        if (block[i].id == -1)
            return i;
    }
    return -1;
}

//寻找内存中是否有该页面
int FindExist(int curpage)
{
    for (int i = 0; i < blocknum; i++)
    {
        if (block[i].id == page[curpage].id)
        {
            return i;
        }
    }
    return -1;
}

//查找应予置换的页面
int FindReplace()
{
    int sign = 0;
    for (int i = 0; i < blocknum; i++)
    {
        if (block[i].visit >= block[sign].visit)
            sign = i;
    }
    return sign;
}

//显示置换完一次后的block
void ShowBlock(int index)
{
    cout << page[index].id << " : ";
    for (int i = 0; i < blocknum; i++)
    {
        if (block[i].id != -1)
        {
            cout << block[i].id << " ";
        }
    }
    cout << endl;
}

//先进先出算法
void FIFO()
{
    int exist, space, position;
    double fifo_missrate = 0.0; //缺页率
    int count = 0;              //页面中断次数
    int change = 0;             //页面置换次数
    for (int i = 0; i < pagenum; i++)
    {
        exist = FindExist(i);
        if (exist != -1)
        {
            cout << page[i].id << " : hit" << endl;
        }
        else
        {
            count++;
            space = FindSpace();
            if (space != -1) //物理块中有空位则直接插入
            {
                block[space] = page[i];
                ShowBlock(i);
            }
            else
            {
                change++;
                position = FindReplace();
                block[position] = page[i];
                ShowBlock(i);
            }
        }
        for (int i = 0; i < blocknum; i++)
        {
            block[i].visit++; //页面进入后，每再进入一个页面停留时间+1；
        }
    }
    fifo_missrate = (float)count / pagenum;
    cout << "缺页次数：" << count << endl;
    cout << "缺页率 : " << fifo_missrate * 100 << "%" << endl;
}

//最佳置换算法
void OPT()
{
    int exist, space, position;
    double opt_missrate = 0.0; //缺页率
    int count = 0;             //页面中断次数
    int change = 0;            //页面置换次数
    for (int i = 0; i < pagenum; i++)
    {
        exist = FindExist(i);
        if (exist != -1)
        {
            cout << page[i].id << " : hit" << endl;
        }
        else
        {
            count++;
            space = FindSpace();
            if (space != -1) //物理块中有空位则直接插入
            {
                block[space] = page[i];
                ShowBlock(i);
            }
            else //物理块中没有空位
            {
                change++;
                for (int j = 0; j < blocknum; j++)
                {
                    for (int k = i; k < pagenum; k++)
                    {
                        if (block[j].id != page[k].id)
                        {
                            block[j].visit = 100;
                        }
                        else
                        {
                            block[j].visit = k;
                            break;
                        }
                    }
                }
                position = FindReplace();
                block[position] = page[i];
                ShowBlock(i);
            }
        }
    }
    opt_missrate = (float)count / pagenum;
    cout << "缺页次数：" << count << endl;
    cout << "缺页率 : " << opt_missrate * 100 << "%" << endl;
}

//最近最久未使用置换算法
void LRU()
{
    int exist, space, position;
    double lur_missrate = 0.0; //缺页率
    int count = 0;             //页面中断次数
    int change = 0;            //页面置换次数
    for (int i = 0; i < pagenum; i++)
    {
        exist = FindExist(i);
        if (exist != -1)
        {
            cout << page[i].id << " : hit" << endl;
            block[exist].visit = 0; //每访问一次需要重置
        }
        else
        {
            count++;
            space = FindSpace();
            if (space != -1) //物理块中有空位则直接插入
            {
                block[space] = page[i];
                ShowBlock(i);
            }
            else
            {
                change++;
                position = FindReplace();
                block[position] = page[i];
                ShowBlock(i);
            }
        }
        for (int i = 0; i < blocknum; i++)
        {
            block[i].visit++; //页面进入后，每再进入一个页面停留时间+1
        }
    }
    lur_missrate = (float)count / pagenum;
    cout << "缺页次数 : " << count << endl;
    cout << "缺页率 : " << lur_missrate * 100 << "%" << endl;
}

int main()
{
    ConverToPage();
    block = new pagedata[blocknum];
    int input;
    while (true)
    {
        cout << endl;
        cout << "1、FIFO" << endl;
        cout << "2、OPT" << endl;
        cout << "3、LRU" << endl;
        cout << "4、EXIT" << endl;
        cout << "Choose 1-4 :";
        cin >> input;
        BlockClear();
        VisitClear();
        if (input = 4)
            break;
        else
            switch (input)
            {
            case 1:
                FIFO();
                break;
            case 2:
                OPT();
                break;
            case 3:
                LRU();
                break;
            default:
                cout << "ERROR! Please input again!" << endl;
                break;
            }
    }
    system("pause");
    return 0;
}
```



