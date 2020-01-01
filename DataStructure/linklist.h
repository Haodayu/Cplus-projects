#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//栈的链式表达
typedef int Elemtype;
typedef struct LNode{
    Elemtype data;
    struct LNode *next;
}LNode, *LinkList;

void CreateList(LinkList L,int n){
    LinkList p;
    L->next = NULL;
    for(int i=n;i>0;--i){
        p = (LinkList)malloc(sizeof(LNode));
        printf("Number %d: ",i);
        scanf("%d",&p->data);
        p->next = L->next;
        L->next = p;
    }
}

void PrintList(LinkList L){
    LinkList m;
    m = L;
    printf("LinkList: ");
    while(m->next != NULL){
        m = m->next;
        printf("%d  ",m->data);
    }
}