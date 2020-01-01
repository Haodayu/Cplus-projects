#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int SElemType;

typedef struct Snode {
    SElemType data;
    struct Snode *next;
} Snode, *StackPtr;

StackPtr InitStack(StackPtr s) {
    s = NULL;
    return s;
}


StackPtr push(StackPtr s,SElemType e) {
    StackPtr p;
    p = (StackPtr)malloc(sizeof(Snode));
    if(!p){
        printf("malloc error!");
        return 0;
    };
    p->data = e;
    p->next = s;
    s = p;
    return s;
}

StackPtr pop(StackPtr s,SElemType *e) {
    StackPtr p;
    if (!s){
        printf("error!");
    };
    *e = s->data;
    p = s;
    s = s->next;
    free(p);
    return s;
}


void conversion (StackPtr s) {
    int n;
    s = InitStack(s);
    printf("Enter a decimal value to covert to octal:\n");
    scanf("%d",&n);
    while(n){
        s = push(s, n%8);
        n = n/8;
    }
    printf("Convert Result:\n");
    while(s){
        SElemType* e;
        s = pop(s,e);
        printf("%d",*e);
    }
}

