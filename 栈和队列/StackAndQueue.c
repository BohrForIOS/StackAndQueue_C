//
//  StackAndQueue.c
//  栈和队列
//
//  Created by 王二 on 17/6/26.
//  Copyright © 2017年 mbs008. All rights reserved.
//

#include "StackAndQueue.h"
#include <stdlib.h>
#include "SqList.h"

#pragma mark - 顺序栈的基本操作

// 初始化
Status InitStack(SqStack *s) {
    s->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    
    if (!s->base) {
        exit(-1);
    }
    
    s->top = s->base;
    s->stactsize = STACK_INIT_SIZE;
    
    return OK;
}

// 获取栈顶元素
Status GetTop(SqStack s, SElemType *e) {
    if (s.top == s.base) {
        return ERROR;
    }
    
    *e = *(s.top);
    
    return OK;
}

// 进栈（插入新元素）
Status Push(SqStack *s, SElemType e) {
    if (s->top - s->base >= s->stactsize) {// 栈满，追加存储空间
        s->base = (SElemType *)realloc(s->base, (s->stactsize + STACKINCREMENT) * sizeof(SElemType));
        
        if (!s->base) {
            exit(-1);// 存储分配失败
        }
        
        s->top = s->base + s->stactsize;
        s->stactsize += STACK_INIT_SIZE;
    }
    
    s->top++;
    *s->top = e;
    
    return OK;
}

Status Pop(SqStack *s, SElemType *e) {
    // 如果栈不为空，则删除s的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
    if (s->top == s->base) {
        return ERROR;
    }
    
    *e = *(s->top);
    s->top--;
    
    return OK;
}

void PrintfStack(SqStack *s) {
    if (s->top == s->base) {// 栈满，没有元素
         printf("栈为空\n");
        return;
    }
    
    while(s->top > s->base) {
        printf("%d\n",*s->base);
        s->base++;
    }
}

Status SqStackEmpty(SqStack *s) {
    if (s->top == s->base) {
        return 1;
    }
    
    return 0;
}

#pragma mark - 顺序栈的应用

// 数值转换
 // 将十进制数转换成8进制数输出
void conversion() {
    // 1.初始化栈
     SqStack *stack = (SqStack *)malloc(sizeof(SqStack));
    InitStack(stack);
    
    // 2.输入一个十进制数
    int n;
    scanf("%d", &n);
    
    // 3. N = (N/d) * d + N % d; 递归(N/d)至其为0;
    while (n) {
        Push(stack, n % 8);// 顺序入栈
        n = n / 8;
    }
    
//    PrintfStack(stack);
    // 4.反序出栈，打印
    while (!SqStackEmpty(stack)) {
        SElemType *e = (SElemType *)malloc(sizeof(SElemType));
        Pop(stack, e);
        printf("%d\n", *e);
    }
}

// 括号匹配的检验
Status MatchCheck(SqList s) {
    int e;
    int j = s.data[0];
    
    // 1.初始化栈
    SqStack *stack = (SqStack *)malloc(sizeof(SqStack));
    InitStack(stack);
    // '[', '(', '(', ')', ')', ']'
    //'[', '(', ')','(', '[',']', ')', ']'
    // 2.逐个读入括号
    for (int i = 0; i < s.length; i++) {
        j = s.data[i];
        
        //若遇左括号，则直接入栈
        if (j == '(' || j == '[') {// '['ASCII码为91，'('ASCII码为40，')'ASCII码为41，']'ASCII码为93，
            Push(stack, s.data[i]);
        }
        else if (j == ')') {//若遇右圆括号，则尝试匹配栈顶括号
            if (GetTop(*stack, &e)) {
                if (e == '(') {//匹配成功，左圆括号出栈
                    Pop(stack, &e);
                }
                else {
                    Push(stack, j);
                }
            }
            else {//栈为空，则将右括号入栈
                Push(stack, j);
            }
        }
        else if (j == ']') {
            if (GetTop(*stack, &e)) {
                if (e == '[') {//匹配成功，左圆括号出栈
                    Pop(stack, &e);
                }
                else {
                    Push(stack, j);
                }
            }
            else {//栈为空，则将右括号入栈
                Push(stack, j);
            }
        }
    }
    
    if (SqStackEmpty(stack)) {
        return OK;
    }
    else {
        return ERROR;
    }
}

#pragma mark - 迷宫

void FootPrint(PosType pos) {
    mazeMap[pos.y][pos.x] = 2; //将走过的路径设为2
}
// 下一个位置
PosType NextPos(PosType curPos, int *i) {
    switch (*i) {
        case 1:  // 东
            ++curPos.x;
            if (mazeMap[curPos.y][curPos.x] != 2)
                break;
            --curPos.x;
            
        case 2:  // 南
            ++curPos.y;
            if (mazeMap[curPos.y][curPos.x] != 2)
                break;
            --curPos.y;
        case 3:  // 西
            --curPos.x;
            
            break;
        case 4:  // 北
            --curPos.y;
            
            break;
            
        default:
            break;
    }
    
    return curPos;
}
