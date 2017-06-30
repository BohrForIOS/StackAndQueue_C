//
//  Queue.c
//  栈和队列
//
//  Created by 王二 on 17/6/30.
//  Copyright © 2017年 mbs008. All rights reserved.
//

// 队列
#include "Queue.h"
#include <stdlib.h>

#pragma mark - 单链队列的基本操作
// 初始化队列
Status InitQueue(LinkQueue *Q) {
    //构造一个空队列Q
    Q->front = Q->rear = (QNodePtr)malloc(sizeof(QNode));
    
    if (Q->front) {
        exit(-1);
    }
    
    Q->front->next = NULL;
    
    return OK;
}

/*
 链表是一个很基本的数据结构，其他的数据结构（如：栈、队列、二叉树等）都可以用链表来实现。
 
 销毁：是先销毁了链表的头，然后接着一个一个的把后面的销毁了，这样这个链表就不能再使用了，即把包括头的所有节点全部释放。
 
 清空：是先保留了链表的头，然后把头后面的所有的都销毁，最后把头里指向下一个的指针设为空，这样就相当与清空了，但这个链表还在，还可以继续使用；即保留了头，后面的全部释放。
 清空是链表的头还在，可以继续插入节点；销毁就是链表没了，整个链表(包括头)的空间都被释放了，不能进行任何操作了。

 */
// 销毁队列
Status DestroyQueue (LinkQueue *Q) {
    while (Q->front) {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
    
    return OK;
}

// 插入元素e
Status EnQueue (LinkQueue *Q, QElemType e) {
    // 插入元素e为Q的新的对尾元素
    QNode *p = (QNodePtr)malloc(sizeof(QNode));
    
    if (!p) {
        exit(-1);
    }
    
    p->data = e;
    p->next = NULL;
    
    Q->rear->next = p;
    Q->rear = p;
    
    return OK;
}

Status DeQueue (LinkQueue *Q, QElemType *e) {
    // 若队列不为空，则删除队列的对头元素，用e返回其值,并返回OK;
    // 否则返回ERROR
    if (Q->front == Q->rear) {
        return ERROR;
    }
    
    QNodePtr p = Q->front->next;
    *e = p->data;
    
    Q->front->next = p->next;
    
    // 特殊情况,尾指针指向p
    if (Q->rear == p) {
        Q->rear = Q->front;
    }
    
    free(p);
    
    return OK;
}

#pragma mark - 循环队列  -- 顺序队列 的基本操作

Status InitQueue_Sq(SqQueue *Q) {
    // 构造一个空队列
    Q->base = (QElemType *)malloc(sizeof(QElemType));//动态申请一维数组
    
    if (!Q->base) {
        exit(-1);
    }
    
    Q->front = Q->rear = 0;
    
    return OK;
}

Status QueueEmpty_Sq(SqQueue *Q) {
    return Q->front == Q->rear;
}

Status QueueFull_Sq(SqQueue *Q) {
    return (Q->rear + 1) % Q->maxSize == Q->front;
}
// 插入元素
Status EnQueue_Sq(SqQueue *Q, QElemType e) {
    if (QueueFull_Sq(Q)) {
        printf("队列已经满了");
    }
    
    // 插入元素e为Q的新的对尾元素
    Q->base[Q->rear] = e;// 尾部插入元素
    
    Q->rear = (Q->rear + 1) % Q->maxSize;// 尾指针后移一位
    
    return OK;
}
// 删除元素
Status DeQueue_Sq(SqQueue *Q, QElemType *e) {
    // 若队列不为空，则删除Q的队头元素，用e返回其值，并返回OK;
    // 否则返回ERROR
    if (Q->front == Q->rear) {
        return ERROR;
    }
    
    *e = Q->base[Q->front];// 将对头元素赋值给e
    Q->front = (Q->front + 1) % Q->maxSize;
    
    return OK;
}

void printfQueue_Sq(SqQueue *Q) {
    if (QueueEmpty_Sq(Q)) {
        printf("队列为空");
        exit(-1);
    }
    
    while (Q->front != Q->rear) {
        printf("%d", Q->base[Q->front]);
        Q->front++;
    }
}
