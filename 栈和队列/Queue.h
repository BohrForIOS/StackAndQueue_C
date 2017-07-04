//
//  Queue.h
//  栈和队列
//
//  Created by 王二 on 17/6/30.
//  Copyright © 2017年 mbs008. All rights reserved.
//

#ifndef Queue_h
#define Queue_h

#include <stdio.h>

#define OK  1
#define ERROR 0
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 5

typedef int Status;
typedef int QElemType;

/**
 定义单链队列的存储结点
 */
typedef struct QNode {
    QElemType data;
    struct QNode *next;
}QNode, *QNodePtr;

/**
 定义单链队列
 */
typedef struct {
    QNodePtr front;// 对头指针
    QNodePtr rear; // 对尾指针
}LinkQueue;

#pragma mark - 循环队列 - 队列的顺序存储结构

#define MAXQSIZE  100  // 最大队列长度
typedef struct {
    QElemType *base;  // 一维数组
    int front;
    int rear;
    int maxSize;
}SqQueue;

#pragma mark - 离散事件模拟

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//Status是函数的类型，其值是函数结果状态码
typedef int Status;

//=================================  排队队列定义开始================================
typedef struct{
    int OccurTime;            //到达时间
    int Duration;            //办理事务所需时间
}CustomerNode;

typedef CustomerNode ElemType;

//结点定义
typedef struct QNodeOfCustomer{
    ElemType data;                //数据节点；
    struct QNodeOfCustomer *next;            //结点的指针域
}QNodeOfCustomer;

//队列链定义
typedef struct{
    QNodeOfCustomer *front;                //队头指针
    QNodeOfCustomer *rare;                //队尾指针
}LinkQueue_DiscreteEvent;

#endif /* Queue_h */
