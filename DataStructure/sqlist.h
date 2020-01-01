#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int Elemtype ;
typedef struct{
    Elemtype* elem;
    int length;
    int listsize;
}Sqlist;


int InitList(Sqlist *L)
{
    L->elem = (Elemtype *)malloc(sizeof(Elemtype)*LIST_INIT_SIZE);
    if (!L->elem)
    {
        printf("Initial Fail\n");
        return 0;
    }
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return 1;
}

int ListInsert(Sqlist *L, int i, Elemtype e)
{
    if (i<1 || i>L->listsize)
    {
        printf("Position Error\n");
        return 0;
    }
    if (L->length >= L->listsize)
    {
        L->elem = (Elemtype *)realloc(L->elem, (LISTINCREMENT + LIST_INIT_SIZE)*sizeof(Elemtype));
        if (!L->elem)
        {
            printf("Realloc Error\n");
            return 0;
        }
        L->listsize += LISTINCREMENT;
    }
        
    Elemtype *q = NULL;
    Elemtype *p = NULL;
    q = &L->elem[i - 1];
    for (p = &L->elem[L->length - 1]; p >= q; p--)
    {
        if(L->length != 0) *(p + 1) = *p;
    }
    *q = e;
    L->length++;
    return 1;
}

int Listdelete(Sqlist *L, int i, Elemtype *e)
{

    if (i<1 || i>L->listsize)
    {
        printf("Postion Error\n");
        return 0;
    }
    Elemtype *p = NULL;
    Elemtype *q = NULL;
    p = &L->elem[i - 1];
    *e = *p;
    q = &L->elem[L->length - 1];
    while (p <= q)
    {
        *p = *(p + 1);
        p++;
    }
    L->length--;
    return 0;
}

int LocateElem(Sqlist L, Elemtype e)
{
    int i;
    for (i = 0; i < L.length; i++)
    {
        if (L.elem[i] == e)
            return i+1;
    }
    return 0;
}

int MergeList(Sqlist La, Sqlist Lb, Sqlist *Lc)
{
    Elemtype *pa = NULL;
    Elemtype *pb = NULL;
    Elemtype *pa_list = NULL;
    Elemtype *pb_list = NULL;
    Elemtype *pc = NULL;
    pa = La.elem;
    pb = Lb.elem;
    Lc->listsize = Lc->length = La.length + Lb.length;
    pc = Lc->elem = (Elemtype *)malloc(Lc->listsize*sizeof(Elemtype));
    if (!Lc->elem)
    {
        printf("Malloc Error\n");
        return 0;
    }
    pa_list = La.elem + La.length-1;
    pb_list = Lb.elem + Lb.length-1;
    while (pa <= pa_list && pb <= pb_list)
    {
        if (*pa <= *pb) *pc++ = *pa++;
        else *pc++ = *pb++;
    }
    while (pa <= pa_list) *pc++ = *pa++;
    while (pb <= pb_list) *pc++ = *pb++;
    return 1;
}