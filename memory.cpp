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