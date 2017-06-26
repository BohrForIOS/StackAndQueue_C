//
//  SqList.c
//  栈和队列
//
//  Created by 王二 on 17/6/26.
//  Copyright © 2017年 mbs008. All rights reserved.
//

#include "SqList.h"
#include <stdlib.h>

Status initList_Sq(SqList *s) {
    //
    s = (SqList *)malloc(sizeof(SqList));
    
    if (!s) {
        printf("申请空间失败");
        exit(-1);
    }
    
    return OK;
}
