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

//// 迷宫
//int mazeMap[5][5] =
//{  //0,1,2,3,4,5,6,7,8,9
//    {0,0,0,0,0}, //0
//    {0,1,1,0,1}, //1
//    {0,1,1,0,1}, //2
//    {0,1,1,1,0}, //3
//    {0,1,0,0,0}, //4
//    
//};

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

/**
 初始化迷宫栈

 @param mazeStack 已经初始化的栈

 @return y/n
 */
Status InitSqStack_Maze(MazeStack *mazeStack) {
    mazeStack->base = (MazeType *)malloc(sizeof(MazeType));
    
    if (!mazeStack->base) {
        printf("申请空间失败");
        exit(-1);
    }
    
    mazeStack->top = mazeStack->base;
    mazeStack->stacksize = STACK_INIT_SIZE;
    
    return OK;
}

/**
 迷宫栈入栈

 @param mazeStack 迷宫栈
 @param e         入栈元素

 @return y/n
 */
Status Push_Maze(MazeStack *mazeStack, MazeType *e) {
    if (mazeStack->top - mazeStack->base >= mazeStack->stacksize) {// 栈满
        mazeStack->base = (MazeType *)realloc(mazeStack->base, (mazeStack->stacksize + STACKINCREMENT) * sizeof(MazeType));
        
        if (!mazeStack->base) {
            exit(-1);
        }
        
        mazeStack->top = mazeStack->base + mazeStack->stacksize;
        mazeStack->stacksize += STACKINCREMENT;
    }
    
    mazeStack->top++;
    *mazeStack->top = *e;
    
    return OK;
}

/**
 出栈

 @param mazeStack 迷宫栈
 @param e         元素

 @return y/n
 */
Status Pop_Maze(MazeStack *mazeStack, MazeType *e) {
    if (mazeStack->top == mazeStack->base) {// 空栈
        return ERROR;
    }
    
    *e = *mazeStack->top;
    mazeStack->top--;
    
    return OK;
}

/**
 迷宫栈是否是空栈

 @param mazeStack 迷宫栈

 @return y/n
 */
Status StackEmpty_Maze(MazeStack *mazeStack) {
    if (mazeStack->base == mazeStack->top) {
        return OK;
    }
    
    return ERROR;
}

/**
 走迷宫

 @param start 开始位置
 @param end   结束位置

 @return y/n
 */
Status MazePath(PosType start, PosType end) {
    PosType curpos;// 当前的点位置
    MazeStack *s;  // 路线栈
    MazeType *e;// 栈点
    int curstep;//当前的步数
    
    // 初始化路线栈
    s = (MazeStack *)malloc(sizeof(MazeStack));
    
    if (!s) {
        printf("申请空间失败");
        exit(-1);
    }
    
    InitSqStack_Maze(s);
    
    curpos = start;// 设定当前位置为入口位置
    curstep = 1; // 探索第一步
    
    do {
        if (Pass(curpos)) {// //当前位置可以通过，即是未曾走到的通道块
            // 加入路径
            FootPrint(curpos);// 留下足迹
            
            e->ord = curstep;
            e->seat = curpos;
            e->di = 1;
            Push_Maze(s, e);
            
            if (curpos.x == end.x && curpos.y == end.y) {
                // 打印路线
                printfMazePath(s);
                
                return TRUE;// 到达终点
            }
            
            curpos = NextPos(curpos, &e->di); //下一位置是当前位置的东邻
            ++curstep;// 探索下一步
        }
        //0,1,2,3,4,5,6,7,8,9
//        {0,0,0,0,0,0,0,0,0,0}, //0
//        {0,1,1,0,1,1,1,0,1,0}, //1
//        {0,1,1,0,1,1,1,0,1,0}, //2
//        {0,1,1,1,1,0,0,1,1,0}, //3
//        {0,1,0,0,0,1,1,1,1,0}, //4
//        {0,1,1,1,0,1,1,1,1,0}, //5
//        {0,1,0,1,1,1,0,1,1,0}, //6
//        {0,1,0,0,0,1,0,0,1,0}, //7
//        {0,0,1,1,1,1,1,1,1,0}, //8
//        {0,0,0,0,0,0,0,0,0,0}  //9
        else {// 当前位置不能通过
            if (!StackEmpty_Maze(s)) {
                Pop_Maze(s, e);// 往后退，出栈，将上一个压栈的先出栈
                
                // 要用while，因为可能联                                                                                                                                                      系e->di == 4;
                while (e->di == 4 && !StackEmpty_Maze(s)) {// 栈点的最后一个方向不能通过，则留下不能通过的标记,并往后退
                    MakePrint(curpos);
                    Pop_Maze(s, e);
                }
                if (e->di < 4) {
                    printf("第%d步时，当前点不能通过curpos = {x: %d, y: %d}\n", curstep, curpos.x, curpos.y);
                    e->di++;// 换下一个方向探索，换个方向压栈
                    
                    Push_Maze(s, e);
                    curpos = NextPos(e->seat, &e->di);//设定当前位置是该新方向上的相邻块，更新当前的位置
                }
            }
        }
    } while (!StackEmpty_Maze(s));
    
    return FALSE;
}

/**
 判断点是否可以通过

 @param pos 点位置

 @return 是否可以通过
 */
Status Pass(PosType pos) {
    if (mazeMap[pos.y][pos.x] == 1) {// 1说明可以通过,
        return TRUE;
    }
    
    return FALSE;
}

/**
 标记走过的点

 @param pos 点位置
 */
void FootPrint(PosType pos) {
    mazeMap[pos.y][pos.x] = 2; //将走过的点位置设为2
}


/**
 下一个位置

 @param curPos 当前的点位置
 @param i      下一步的方向  1东2南3西4北

 @return 下一个点位置
 */
PosType NextPos(PosType curPos, int *i) {
    switch (*i) {
        case 1:  // 东
            ++curPos.x;
//            if (mazeMap[curPos.y][curPos.x] != 2)
                break;
//            --curPos.x;
            
        case 2:  // 南
            ++curPos.y;
//            if (mazeMap[curPos.y][curPos.x] != 2)
                break;
//            --curPos.y;
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

/**
 标记走不通的块为墙壁

 @param pos 点位置
 */
void MakePrint(PosType pos) {
    mazeMap[pos.y][pos.x] = 0;// 将走不通的块替换为墙壁；
}

void printfMazePath(MazeStack *s) {
    if (s->top == s->base) {
        printf("栈为空");
        
        return;
    }
    
    while (s->top > s->base) {
        s->base++;
        printf("第%d步,位置为{x : %d, y : %d},方向%d\n", s->base->ord, s->base->seat.x, s->base->seat.y, s->base->di);
    }
    
}

#pragma mark - 表达式求值


//定义符号的优先级；

//获取计算符的优先级
int GetPriorityOfOperator(char c) {
    int priority;
    
    switch(c){
        case '-':
        case '+':
            priority = 1;
            break;
        case '*':
        case '/':
            priority = 2;
            break;
        default:
            printf("操作符不在范围内error\n");
            break;
    }
    
    return priority;
}


//运算a，b
int calculate(int a, int b, char operator) {
    int result;
    
    switch(operator) {
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        default:
            break;
    }
    
    return result;
}

int calculationBtweenStack(SeqStack *a, SeqStackchar *b) {
    int fir,sec,resultval;
    char topchar;
    
    // a出栈两个值
    fir = a->data[a->top];
    a->top--;
    
    if (a->top == -1) {// 已经到栈底了
        a->top++;
        a->data[a->top] = fir;
        
        return fir;
    }
    
    sec = a->data[a->top];
    a->top--;
    
    // b出栈一个运算符
    topchar = b->data[b->top];    //b的栈顶出栈
    b->top--;
    
    // 运算，运算结果进栈a
    resultval = calculate(sec,fir,topchar);
    a->top++;
    a->data[a->top] = resultval;
    
    return resultval;
}

// ④：确定运算思路——自左扫描表达式的每一个字符时，若当前字符是运算数值，入整型栈。是运算符时，若这个运算符比栈顶运算符高则入栈，继续向后处理，若这个运算符比栈顶运算符低，则从对象栈出栈两个运算量，从运算符栈出栈一个运算符进行运算，将其运算结果入对象栈。然后继续判断当前字符串是否高于栈顶运算符，如果比栈顶运算符高，则入栈，否则则继续运算。
//a出栈两个值 b出栈栈顶运算符，进行运算

//表达式求值
int result(SeqStack *numStack, SeqStackchar *operatorStack) {
    char expression[9] = {'1','*','4','+','2','-','9','*','3'};        //创建表达式
    int i,resultval = 0;
    int priorOfChar,priorOfTopStackChar;
    char c;
    int n = sizeof(expression);
    
    for(i = 0; i < n; i++) {
        c = expression[i];        //获取表达式第i个值
        printf("i = %d", i);
        
        if(i % 2 == 0) {//把数字和符号区分开来，
            numStack->top++;
            numStack->data[numStack->top] = c - '0';    //存放数值的
        }
        else {//存放符号的
            if(operatorStack->top == -1) {//如果b为空则直接存入符号
                operatorStack->top++;
                operatorStack->data[operatorStack->top] = c;
            }
            else {
                priorOfChar = GetPriorityOfOperator(c);                //求出当前符号的优先级
                priorOfTopStackChar = GetPriorityOfOperator(operatorStack->data[operatorStack->top]);    //求b栈顶的符号优先级
                printf("priorOfChar = %d, priorOfTopStackChar = %d\n", priorOfChar, priorOfTopStackChar);
                if(priorOfChar >priorOfTopStackChar)        //如果当前优先级大于栈顶优先级，则进栈
                {
                    operatorStack->top++;
                    operatorStack->data[operatorStack->top] = c;
                }
                else {
                    resultval = calculationBtweenStack(numStack,operatorStack);        //否则a的前两个出栈，b的栈顶出栈，然后进行运算，运算结果再进栈a；
                    if (operatorStack->top == -1) {// 如果操作符栈已经是栈底，则直接进栈
                        operatorStack->top++;
                        operatorStack->data[operatorStack->top] = c;
                    }
                    else {
                        priorOfTopStackChar = GetPriorityOfOperator(operatorStack->data[operatorStack->top]);        //继续判断表达式第i个值的优先级是否大于栈顶符号的优先级
                        if(priorOfChar >priorOfTopStackChar) {//如果当前优先级大于栈顶优先级，则进栈
                            operatorStack->top++;
                            operatorStack->data[operatorStack->top] = c;
                        }
                        else {//否则重复上面的操作对a的前两个出栈值和b的栈顶出栈并且运算
                            resultval = calculationBtweenStack(numStack,operatorStack);
                            //由于每次循环都会对b的栈顶符号的优先级做对比，所以优先级的对比只做一次即可
                            operatorStack->top++;            //把当前的符号进b栈
                            operatorStack->data[operatorStack->top] = c;
                        }
                    }
                }
            }
        }
        while(i == n - 1 && numStack->top != -1 && operatorStack->top != -1)        //当运算符输入完时
        {
            resultval = calculationBtweenStack(numStack,operatorStack);
        }
    }
    
    return resultval;
}
