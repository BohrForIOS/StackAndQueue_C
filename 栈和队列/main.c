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
    SqList sqList = {.data = {'[', '(', ')','(', '[',']', ')', ']'},
        .length = 8};
    if (MatchCheck(sqList)) {
        printf("匹配成功");
    }
    else {
         printf("匹配失败");
    }
    
    
    
    return 0;
}
