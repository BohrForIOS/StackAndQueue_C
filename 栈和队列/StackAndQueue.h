//
//  StackAndQueue.h
//  栈和队列
//
//  Created by 王二 on 17/6/26.
//  Copyright © 2017年 mbs008. All rights reserved.
//

#ifndef StackAndQueue_h
#define StackAndQueue_h


#include <stdio.h>
#include "SqList.h"

#define OK  1
#define ERROR 0
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 5

typedef int Status;
typedef int SElemType;

/**
 栈
 */
typedef struct {
    SElemType *top;
    SElemType *base;
    int stactsize;
}SqStack;// 顺序栈

// 初始化
Status InitStack(SqStack *s);

// 获取栈顶元素
Status GetTop(SqStack s, SElemType *e);

// 进栈（插入新元素）
Status Push(SqStack *s, SElemType e);
Status Pop(SqStack *s, SElemType *e);

void PrintfStack(SqStack *s);
#pragma mark - 顺序栈的应用

// 数值转换
// 将十进制数转换成8进制数输出
void conversion();
// 括号匹配的检验
Status MatchCheck(SqList s);

// 迷宫

/**
 位置
 */
typedef struct {
    int x;
    int y;
}PosType;

/**
 迷宫路径栈中的存储结构
 */
typedef struct {
    int ord;      //通道块在路径上的“序号”
    PosType seat; //通道块在迷宫中的“坐标位置”
    int di;       //从此通道块走向下一通道块的“方向”, //1:东 2:北 3:西 （顺时针)
}MazeType;

/**
 迷宫路径栈
 */
typedef struct {
    MazeType *base;
    MazeType *top;
    int stacksize;
}MazeStack;

// 迷宫
int mazeMap[10][10] =
{  //0,1,2,3,4,5,6,7,8,9
    {0,0,0,0,0,0,0,0,0,0}, //0
    {0,1,1,0,1,1,1,0,1,0}, //1
    {0,1,1,0,1,1,1,0,1,0}, //2
    {0,1,1,1,1,0,0,1,1,0}, //3
    {0,1,0,0,0,1,1,1,1,0}, //4
    {0,1,1,1,0,1,1,1,1,0}, //5
    {0,1,0,1,1,1,0,1,1,0}, //6
    {0,1,0,0,0,1,0,0,1,0}, //7
    {0,0,1,1,1,1,1,1,1,0}, //8
    {0,0,0,0,0,0,0,0,0,0}  //9
};

#endif /* StackAndQueue_h */
