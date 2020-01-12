#include <stdio.h>  
#include <stdlib.h>  
#include "double_list_f.h"

//创建双向链表  
pNODE CreateDbLinkList(void)  
{  
    int i, length = 0, data = 0;  
    pNODE pTail = NULL, p_new = NULL;  
    pNODE pHead = (pNODE)malloc(sizeof(NODE));  
  
    if (NULL == pHead)  
    {  
        printf("内存分配失败！\n");  
        exit(EXIT_FAILURE);  
    }  
      
    pHead->data = 0;  
    pHead->pPre = NULL;  
    pHead->pNext = NULL;  
    pTail = pHead;  
  
    printf("请输入想要创建链表的长度：");  
    scanf("%d", &length);  
  
    for (i=1; i<length+1; i++)  
    {  
        p_new = (pNODE)malloc(sizeof(NODE));  
  
        if (NULL == p_new)  
        {  
            printf("内存分配失败！\n");  
            exit(EXIT_FAILURE);  
        }  
  
        printf("请输入第%d个元素的值：", i);  
        scanf("%d", &data);  
  
        p_new->data = data;  
        p_new->pNext = NULL;  /*  */
        p_new->pPre = pTail;  /* 当前节点的前驱指针指向，上一个节点的起始地址 */
        pTail->pNext = p_new; /* 上一个节点后继指针指向，当前节点的首地址 */
        pTail = p_new;        /* 将当前节点的首地址，作为下一个指针要指向的上一个节点要指向的起始地址 */
    }  
    return pHead;  
}  

//打印链表  
void TraverseDbLinkList(pNODE pHead)  
{  
    pNODE pt = pHead->pNext;  
  
    printf("打印链表如：");  
    while (pt != NULL)  
    {  
        printf("%d ", pt->data);  
        pt = pt->pNext;  
    }  
    putchar('\n');  
}  
  
//判断链表是否为空  
int IsEmptyDbLinkList(pNODE pHead)  
{  
    pNODE pt = pHead->pNext;  
  
    if (pt == NULL)  
        return 1;  
    else  
        return 0;  
}  
  
//计算链表的长度 : length+1(head node) 
int GetLengthDbLinkList(pNODE pHead)  
{  
    int length = 0;  
    pNODE pt = pHead->pNext;  
  
    while (pt != NULL)  
    {  
        length++;  
        pt = pt->pNext;  
    }
    
    return length;  
}  

//向双向链表中插入节点
/* 主要是新插入的节点中的前驱和后继指针和原有节点的指针的关系 */
int InsertEleDbLinkList(pNODE pHead, int pos, int data)  
{  
    pNODE pt = NULL, p_new = NULL;  /* 指针初始化*/
  
    if (pos > 0 && pos < GetLengthDbLinkList(pHead)+2)  
    {  
        p_new = (pNODE)malloc(sizeof(NODE));  
  
        if (NULL == p_new)  
        {  
            printf("内存分配失败！\n");  
            exit(EXIT_FAILURE);  
        }  
  
        while (1)  
        {  
            pos--;  
            if (0 == pos)  
                break;  
            pHead = pHead->pNext;  
        }  
          
        pt = pHead->pNext;  /* 将所要插入处节点的首地址保存好 */
        p_new->data = data;  
        p_new->pNext = pt;  /* 让新插入的节点指向被插入的节点的首地址，相当于被插入的节点后移 */
        
        if (NULL != pt)  /* 判断是不是到了最后一个节点，最后一个节点的后继指针指向NULL */
            pt->pPre = p_new;  /* 不是最后一个，该节点的前驱指针要指向前一个节点的起始地址,即插入的节点 */
        p_new->pPre = pHead;   /* p_new是新加的，  */
        pHead->pNext = p_new;
        
        return 1;  
    }  
    else  
        return 0;  
}  

//从链表中删除节点  
int DeleteEleDbLinkList(pNODE pHead, int pos)  
{  
    pNODE pt = NULL;  
  
    if (pos > 0 && pos < GetLengthDbLinkList(pHead) + 1)  
    {  
        while (1)  
        {  
            pos--;  
            if (0 == pos)  
                break;  
            pHead = pHead->pNext;  
        }
        
        pt = pHead->pNext->pNext;  /* 保留删除节点的后继指针 */
        free(pHead->pNext);        /* 释放删除节点的内存 */
        pHead->pNext = pt;         /* 让上一个节点的后继指针，指向所删除节点，后面节点的首地址，组成新的链表 */
        if (NULL != pt)  
            pt->pPre = pHead;  
  
        return 1;  
    }  
    else  
        return 0;  
}  

//删除整个链表，释放内存
/* ppHead--头结点的首地址 */
void FreeMemory(pNODE *ppHead)  
{  
    pNODE pt = NULL;  
  
    while (*ppHead != NULL)  
    {  
        pt = (*ppHead)->pNext;  
        free(*ppHead);  /* 通过后继指针释放每个节点占用的内存*/
        if (NULL != pt) /* 判断所删除的节点是不是最后一个节点 */
            pt->pPre = NULL;  /* 将当前节点改为头结点 */
        *ppHead = pt;  /* 到达最后一个节点，退出循环 */
    }  
}  

void dblist_test()
{
    pNODE pHead = NULL;

    pHead = CreateDbLinkList();  /* 创建 */
    TraverseDbLinkList(pHead);  /* 打印链表 */
    InsertEleDbLinkList(pHead,  2,  12);  /* 在第二个节点插入一个值为12的节点 */
    TraverseDbLinkList(pHead);  /* 打印链表 */
    DeleteEleDbLinkList( pHead,  2);
    TraverseDbLinkList(pHead);  /* 打印链表 */
    /* FreeMemory(&pHead); */
    /* TraverseDbLinkList(pHead);  /\* 打印链表 *\/ */

}






