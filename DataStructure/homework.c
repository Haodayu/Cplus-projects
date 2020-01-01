#include "sqlist.h"

int main()
{
    Sqlist La;
    InitList(&La);
    Sqlist Lb;
    InitList(&Lb);
    Sqlist Lc;
    InitList(&Lc);

    int i;

    printf("[list_A]\n");
    for (i = 1; i <=5; i++)
    {
        ListInsert(&La, i, i*i);
        printf("%d  ",i*i);
    }

    printf("\n\n[list_B]\n");
    for (i = 1; i <=9; i++)
    {
        ListInsert(&Lb, i, i*4);
        printf("%d  ",i*4);
    }

    MergeList(La, Lb, &Lc);
    printf("\n\n[list_C]\n");
    for (i = 1; i <=Lc.length; i++)
    {
        printf("%d  ",Lc.elem[i-1]);
    }
    
    getchar();
}