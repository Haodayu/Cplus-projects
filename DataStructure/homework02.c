#include "linklist.h"

int main()
{
    LinkList L;
    L = (LinkList)malloc(sizeof(LNode));
    CreateList(L,5);
    PrintList(L);

    getchar();getchar();
}