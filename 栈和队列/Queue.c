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
#include <string.h>


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
    
    // 特殊情况,尾指针指向p，即只有一个元素
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

#pragma mark - 离散事件模拟

//初始化一个空队列
Status InitQueue_DiscreteEvent(LinkQueue_DiscreteEvent *Q) {
    // 给头结点和尾结点开辟空间，并赋值
    Q->front = Q->rare = (QNodeOfCustomer *)malloc(sizeof(QNodeOfCustomer));
    // 如果开辟不成功，直接退出
    if (!Q->front) {
        exit(-1);
    }
    // 开辟成功，给头结点的指针域赋值NULL
    Q->front->next = NULL;
    
    return OK;
}

//判断是否为空队列
Status QueueEmpty_DiscreteEvent(LinkQueue_DiscreteEvent *Q) {
    if (Q->front == Q->rare) {
        return TRUE;
    }
    
    return FALSE;
}

//判断长度
Status QueueLength_DiscreteEvent(LinkQueue_DiscreteEvent *Q) {
    if (Q->front == Q->rare) {
        return 0;
    }
    
    int i = 0;
    
    QNodeOfCustomer *q = Q->front;
    
    if (q->next) {
        q = q->next;
        i++;
    }
    
    return i;
}
//向队列尾部插入元素e
Status EnQueue_DiscreteEvent(LinkQueue_DiscreteEvent *Q, ElemType e) {
    // 生成结点
    QNodeOfCustomer *q;
    q = (QNodeOfCustomer *)malloc(sizeof(QNodeOfCustomer));
    
    if (!q) {
        exit(-1);
    }
    
    q->data = e;
    q->next = NULL;
    
    // 将尾结点的指针域指向新结点
    Q->rare->next = q;
    // 修改尾指针指向
    Q->rare = q;
    return OK;
}

//删除队列头部元素并返回
Status Dequeue_Event(LinkQueue_DiscreteEvent *Q, ElemType *e) {
    if (Q->front == Q->rare) {
        return ERROR;
    }
    
    // 令q为第一个结点
    QNodeOfCustomer *q = Q->front->next;
    *e = q->data;
    // 修改头结点的指针域的指向第二个结点
    Q->front->next = Q->front->next->next;
    
    // 释放第一个结点
    if (!Q->front->next) {// 如果第二个结点不存在
        Q->rare = Q->front;
    }
    
    free(q);
    
    return OK;
}

//=================================  排队队列定义结束 ================================




//=================================  事件链表定义开始 ================================

void InitList_Event(LinkList L) {
    L = (LinkList)malloc(sizeof(LNode)); // 生成新结点
    
    if (!L) {
        exit(-1);
    }
    
    L->next = NULL;
}

//插入元素，在L中第i个位置之前插入数据 e
Status ListInsert_L(LinkList L, int i, EvElemType e) {
    // 找到事件单链表的第i-1处元素的指针
    LNode *q;
    q = L;
    
    int j = 0;
    
    while (q && j < (i - 1)) {// q为第i-1个元素
        q = q->next;
        j++;
    }
    
    if (!q || i < 1) {//1.q为NULL(第i-1个元素为空)  2.i不能小于1
        return ERROR;
    }
    
    // 创建一个新的结点
    LNode *s;
    s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = NULL;
    
    // 将新结点的指针指向第i个元素，第i-1个元素的指针指向s
    s->next = q->next;
    q->next = s;
    
    return OK;
}//时间复杂度为 O（n）

//按照事件发生的时间点顺序，将事件结点插入事件链表 时间点从小到大排序
Status OrderInsert(LinkList L, EvElemType e) {
    LNode *q;
    q = L;
    
    if (!q->next) {
        // 如果L是空表，插入第一个元素e
        ListInsert_L(L, 1, e);
    }
    else {
        // 寻找满足后面条件的第一个结点：条件：结点的客户到达时间要比e的到达时间大;
        while (q->next && e.OccurTime > q->next->data.OccurTime) {
            q = q->next;
        }
        
        // 生成新结点
        LNode *s;
        s = (LinkList)malloc(sizeof(LNode));
        s->data = e;
        
        // 将新结点插入
        s->next = q->next;
        q->next = s;
    }
    
    return OK;
}
//=================================  银行排队业务模拟程序定义开始 ================================

EventList ev; // 事件链表
Event en;     // 事件结点

CustomerNode cn; // 客户节点
LinkQueue_DiscreteEvent q[5]; // 客户队列
int CloseTime;                                //银行结束时间
int TotalTime,CustomerNum;                    //累计逗留时间 ，累计客户数量

void OpenDay() {
    // 初始化总时间，客户数量
    TotalTime = 0;
    CustomerNum = 0;
    
    //初始化事件链表
    InitList_Event(ev);
    // 第一个事件初始化
    en.OccurTime = 0;
    en.NType = 0;
    
    // 插入事件
    OrderInsert(ev, en);
    
    int i = 1;
    // 初始化任务队列
    for (i = 1; i < 5; i++) {
        InitQueue_DiscreteEvent(&q[i]);
    }
}

//寻找队伍人数最少的队列。
int MinQueue() {
    // 拿到第一个队列的长度
    int len = QueueLength_DiscreteEvent(&q[1]);
    int cur = 1;
    
    // 遍历队列数组，依次和第一个的长度比较
    for (int i = 2; i < 5; i++) {
        if (len > QueueLength_DiscreteEvent(&q[i])) {
            len = QueueLength_DiscreteEvent(&q[i]);
            cur = i;
        }
    }
    
    return cur;
}

void CustomerArrived() {
    // 增加客户数量
    ++CustomerNum;
    
    // 产生0~30的随机整数，为到达客户等待的时间
    int durTime = rand() % 31;
    //产生0-5 间的随机整数，为与下一客户到达时间的时间间隔。
    int interTime = rand() % 6;
    
    // 离开时间和到达时间
    int depT = en.OccurTime + durTime;
    int arrT = en.OccurTime + interTime;
    
    // 开始排队，找到最短队伍，并加入队伍
    int i = MinQueue();
    cn.OccurTime = en.OccurTime;// 设置到达时间
    cn.Duration = durTime;// 设置办理事务所需时间
    EnQueue_DiscreteEvent(&q[i], cn);
    
    // 把当前客户离开事件，加入事件列表
    en.OccurTime = depT;
    en.NType = i;
    en.dur = durTime;
    OrderInsert(ev, en);
    
    // 下一客户到达事件，加入事件列表
    en.OccurTime = arrT;
    en.NType = 0;
    en.dur = 0;
    
    if (en.OccurTime < CloseTime) {
        OrderInsert(ev, en);
    }
}

//客户离开
void CustomerDepature() {
    int i = en.NType;
    CustomerNode c;
    Dequeue_Event(&q[i], &c);
    TotalTime+=c.Duration;
}
//计算平均逗留时间
void CloseDay() {
    printf("\n总时间：%d\n",TotalTime);
    printf("客户总数量：%d\n",CustomerNum);
    printf("平均逗留时间：%d\n",TotalTime/CustomerNum);
}

#pragma mark - 队列练习  循环顺序队列的简单练习
/*
 描述
 请你定义一个队列，可以对队列进行“入队”、“出队”、“队列输出”等操作。键盘输入一些命令，可以执行上述操作。本题中，队列中元素均为整数。队列的最大元素个数为1000。
 输入
 输入各个命令，它们对应的格式如下：
 入队：enq x，x代表入队的元素，这里enq和元素之间用空格分隔。
 队列输出：printq
 出队：deq
 当输入的命令为exit时，程序结束。
 输出
 当输入的命令为deq时，请输出出队列的元素值。
 当输入的命令是printq时，请输出队列中所有元素的值。
 注意，如果没有满足的元素，请输出None。
 */

// 使用循环列表实现  p[1001],说明数组有1001个元素，在循环队列中，有一个位置不用的，用来判断队列是否已满（当当队列头指针在队列尾指针的下一位时，队列已满
int p[1001], tail, head;
// 入队
void enqueue(int x) {
    p[tail] = x;
    tail = (tail + 1)%1000;
}
// 出队
int dequeue() {
    int x;
    x = p[head];
    head = (head + 1)%1000;
    return x;
}

void exerciseOne() {
    char ch[10];
    int a;
    
    while (scanf("%s", ch)) {
        if (strcmp(ch, "enq") == 0) {
            scanf("%d", &a);
            enqueue(a);
        }
        else if (strcmp(ch, "deq") == 0) {
            if (head == tail) {
                 printf("None\n");
            }
            else {
                a = dequeue();
                printf("出队元素a=%d\n", a);
            }
        }
        else if (strcmp(ch, "printq") == 0) {
            // 输出队列
            if (head == tail) {
                printf("None\n");
            }
            else {
                for (int j = head; j < tail; j++) {
                     printf("%5d\n", p[j]);
                }
            }
        }
        else if (strcmp(ch, "exit") == 0) {
            exit(0);
        }

    }
}

// 比较两个字符串大小的内部实现
int strcmpCompletion(const char *dest, const char *source) {
    // 当每一个字符存在且相等时，指针往后移动一位
    while (*dest && *source && (*dest == *source))
    {
        dest ++;
        source ++;
    }
    return *dest - *source;
    /*如果dest > source,则返回值大于0，如果dest = source,则返回值等于0，如果dest  < source ,则返回值小于0。*/
}
// 拷贝一个字符串的内部实现
char *strcpyCompletion(char *strDest, const char *strScr) {
    char *address = strDest;
    
    while (*strScr) {
        *strDest++ = *strScr++;
    }
    
    *strDest = '\0';
    return address;
}

#pragma mark - 循环队列的练习题二
#define LEN 100005
typedef struct Task {
    // 名字
    char name[100];
    // 时间
    int time;
}Task;

Task Q[LEN];

int head, tail, n;

//向队列添加新元素
void enqueue_task(Task x) {
    Q[tail] = x;
    tail = (tail + 1) % LEN;
}
//从队列开头取出元素
Task dequeue_task() {
    Task x = Q[head];
    head = (head + 1) % LEN;
    return x;
}

int min(int a, int b) {
    return a<b?a:b;
}

void CPUHandleTask() {
    int q;
    int endTime;
    int c;
    
    Task u;
    
    scanf("%d %d", &n, &q);
    
    for (int i = 0; i < n; i++) {
        // 依次入队列
        scanf("%s %d", Q[i].name, &Q[i].time);
    }
    
    head = 0; tail = n;
    while (head != tail) {
        // 从队列里拿出
        u = dequeue_task();
        c = min(u.time, q);
        
        u.time-=c;// 所剩时间
        endTime+=c;// 累计已用时间
        if (u.time > 0) {//如果处理尚未结束则重新添加至队列
            enqueue_task(u);
        }
        else {
            printf("%s %d\n", u.name, endTime);
        }
    }
}
