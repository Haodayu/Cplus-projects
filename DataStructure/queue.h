#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct QNode{
    char id[20];
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

void InitQueue(LinkQueue *Q){
    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q->front){
        printf("Initial Fail\n");
        return;
    }
    Q->front->next = NULL;
}

void DestroyQueue(LinkQueue *Q){
    while(Q->front){
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
}

void Lineup(LinkQueue *Q, char e[]){
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(QNode));
    if (!p){
        printf("Initial Fail\n");
        return;
    }
    strcpy(p->id,e);
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    printf("[+] %s 正在排队.\n",e);
}

int Diagnosis(LinkQueue *Q){
    QueuePtr p;
    if(Q->front == Q->rear) return 0;
    p = Q->front->next;
    printf("[-] %s 已就诊.\n",p->id);
    Q->front->next = p->next;
    if(Q->rear == p) Q->rear = Q->front;
    free(p);
    return 1;
}

int CheckQueue(LinkQueue *Q){
    int n = 0;
    QueuePtr p;
    p = Q->front->next;
    printf("\n-------队列情况-------\n");
    while(p){
        n++;
        printf("%s\n",p->id);
        p = p->next;
    }
    return n;
}