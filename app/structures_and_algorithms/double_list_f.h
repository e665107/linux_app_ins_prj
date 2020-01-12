#ifndef DOUBLE_LIST_F_H
#define DOUBLE_LIST_F_H

typedef struct Node  
{  
    int data;  
    struct Node *pNext;  
    struct Node *pPre;  
}NODE, *pNODE;  
  
//创建双向链表  
pNODE CreateDbLinkList(void);  
  
//打印链表  
void TraverseDbLinkList(pNODE pHead);  
  
//判断链表是否为空  
int IsEmptyDbLinkList(pNODE pHead);  
  
//计算链表长度  
int GetLengthDbLinkList(pNODE pHead);  
  
//向链表插入节点  
int InsertEleDbLinkList(pNODE pHead, int pos, int data);  
  
//从链表删除节点  
int DeleteEleDbLinkList(pNODE pHead, int pos);  
  
//删除整个链表，释放内存  
void FreeMemory(pNODE *ppHead);  


void dblist_test(void);

#endif /* DOUBLE_LIST_F_H */
