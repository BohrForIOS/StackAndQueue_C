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

#endif /* Queue_h */
