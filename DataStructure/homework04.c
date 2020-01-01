#include "queue.h"

char *CleanIn(char str[]){
    char c[30];
    strcpy(c,str);
    printf("%s",c);
    char *p,*q;
	for(p=c,q=c;*p!='\0';p++){
        if((*p!='+')&&(*p!=' ')){
            *(q++)=*p;
            *q='\0';
        }
    }
	return c;
}

int main(){
    int numinline = 0;
    int numindiag = 0;
    LinkQueue patients;
    InitQueue(&patients);
    printf("\n-----<<<<<�����Ŷ�ģ����>>>>>-----\n\n\n");
    printf("�������:\n\n# + (�˴�������) #: �������ż������\n\n");
    printf("# - #: �Ŷ���ǰ�Ĳ��˾���\n\n");
    printf("# display #: ����������\n\n");
    printf("# exit #: �뿪ģ����\n\n___________________________________\n");

    while (1){
        char input[30];

        printf("\n> ");
        gets(input);
        if (input[0]=='+'){
            char *p,*q;
            for(p=input,q=input;*p!='\0';p++){
                if((*p!='+')&&(*p!=' ')){
                    *(q++)=*p;
                    *q='\0';
                }
            }
            Lineup(&patients,input);
        }
        else if (strcmp(input,"-")==0){
            numindiag += Diagnosis(&patients);
        }
        else if (strcmp(input,"display")==0){
            numinline = CheckQueue(&patients);
            printf("\n�Ѿ��ﲡ����: %d\n",numindiag);
            printf("δ���ﲡ����: %d\n",numinline);
        }
        else if (strcmp(input,"exit")==0){
            return 0;
        }
    }
}