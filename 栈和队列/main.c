//
//  main.c
//  栈和队列
//
//  Created by 王二 on 17/6/26.
//  Copyright © 2017年 mbs008. All rights reserved.
//

#include <stdio.h>
#include "StackAndQueue.h"
#include <stdlib.h>
#include "SqList.h"


int main(int argc, const char * argv[]) {

//    // 1.初始化
//    SqStack *stack = (SqStack *)malloc(sizeof(SqStack));
//
//    InitStack(stack);
//    
//    // 2.插入元素
//    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
//    for (int i = 0; i < 8; i++) {
//        Push(stack, a[i]);
//    }
//   
//    // 3.打印元素
//    PrintfStack(stack);
    
//    conversion();
    
    //匹配括号
//    SqList sqList = {.data = {'[', '(', ')','(', '[',']', ')', ']'},
//        .length = 8};
//    if (MatchCheck(sqList)) {
//        printf("匹配成功");
//    }
//    else {
//         printf("匹配失败");
//    }
//    
//    // 走迷宫
//    PosType start = {.x = 1, .y = 1};
//    PosType end = {.x = 8, .y = 8};
//    Status success =  MazePath(start, end);
//    
//    if (success) {
//        printf("走出迷宫成功");
//    }
//    else {
//        printf("迷宫不能走出");
//    }
    
    // 多项式计算
//    SeqStack *seqStack = (SeqStack *)malloc(sizeof(seqStack));
//    
//    if (!seqStack) {
//        printf("分配空间失败");
//    }
//    
//    seqStack->top = -1;
//    
//    SeqStackchar *seqStackChar = (SeqStackchar *)malloc(sizeof(SeqStackchar));
//    
//    if (!seqStackChar) {
//        printf("分配空间失败");
//    }
//    
//    seqStackChar->top = -1;
//    
//    int resultValue =  result(seqStack, seqStackChar);
//    printf("计算结果为%d\n", resultValue);
    
//    hanoiFunction();
    
    // 练习strcmp的实现
//    char *ch1 = "abc";
//    char *ch2 = "abe";
//    int a = strcmpCompletion(ch1, ch2);
//    printf("%d", a);
    
//    exerciseOne();
    CPUHandleTask();
    
    return 0;
}
