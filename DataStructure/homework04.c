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
    printf("\n-----<<<<<看病排队模拟器>>>>>-----\n\n\n");
    printf("命令帮助:\n\n# + (此处病历号) #: 将病历号加入队列\n\n");
    printf("# - #: 排队最前的病人就诊\n\n");
    printf("# display #: 输出队列情况\n\n");
    printf("# exit #: 离开模拟器\n\n___________________________________\n");

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
            printf("\n已就诊病人数: %d\n",numindiag);
            printf("未就诊病人数: %d\n",numinline);
        }
        else if (strcmp(input,"exit")==0){
            return 0;
        }
    }
}