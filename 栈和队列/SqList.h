//
//  SqList.h
//  栈和队列
//
//  Created by 王二 on 17/6/26.
//  Copyright © 2017年 mbs008. All rights reserved.
//

#ifndef SqList_h
#define SqList_h

#include <stdio.h>

#define OK  1
#define ERROR   0
#define TRUE    1
#define FALSE   0
#define MAXSIZE  100

typedef int Status;

typedef int ElemType;
/**
 定义一个顺序表
 */
typedef struct{
    ElemType data[MAXSIZE];
    int length;
}SqList;

#endif /* SqList_h */
