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
    int di;       //从此通道块走向下一通道块的“方向”, //1:东 2:南 3:西 4:北（顺时针)
}MazeType;

/**
 迷宫路径栈
 */
typedef struct {
    MazeType *base;
    MazeType *top;
    int stacksize;
}MazeStack;



Status Pass(PosType pos);
void FootPrint(PosType pos);
PosType NextPos(PosType curPos, int *i);
void MakePrint(PosType pos);
Status MazePath(PosType start, PosType end);
void printfMazePath(MazeStack *s);

#pragma 多项式求值
//定义两个栈，一个存放数字，一个存放符号；

//定义存储整型的栈
typedef struct node
{
    int data[MAXSIZE];
    int top;
}SeqStack;
//定义存储字符型的栈
typedef struct nodeb
{
    char data[MAXSIZE];
    int top;
}SeqStackchar;

int GetPriorityOfOperator(char c);
//运算a，b
int calculate(int a, int b, char operator);
int calculationBtweenStack(SeqStack *a, SeqStackchar *b);
int result(SeqStack *numStack, SeqStackchar *operatorStack);

#endif /* StackAndQueue_h */
