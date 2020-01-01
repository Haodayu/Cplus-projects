#include <iostream>
#include <stack>
using namespace std;


typedef struct BiTNode{
    char data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

void CreateBiTree(BiTree &T){
    char ch;
    scanf("%c",&ch);
    if(ch == '\n') scanf("%c",&ch);
    if(ch == ' ') T=NULL;
    else {
        if (!(T=(BiTNode *)malloc(sizeof(BiTNode)))) {printf("Initial Fail");return;}
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

void PreOrderTraverse(BiTree T){
    if(T!=NULL){
        printf("%c",T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

void InOrderTraverse(BiTree T){
    if(T!=NULL){
        InOrderTraverse(T->lchild);
        printf("%c",T->data);
        InOrderTraverse(T->rchild);
    }
}

void PostOrderTraverse(BiTree T){
    if(T!=NULL){
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%c",T->data);
    }
}

int LeafNum(BiTree T,int counter){
    if(T==NULL) return counter;
    if(!T->lchild && !T->rchild){
        counter++;
    }
    else{
        counter = LeafNum(T->lchild,counter);
        counter = LeafNum(T->rchild,counter);
    }
    return counter;
}

int TreeDeep(BiTree T){
    int ld=0, rd=0;
    if(T!=NULL)
	{
        ld=TreeDeep(T->lchild)+1;
        rd=TreeDeep(T->rchild)+1;  
    }
    return max(ld,rd);
}

void PrintStack(stack<char> S){
    while(!S.empty()){
        printf("%c",S.top());
        S.pop();
        if(!S.empty()) printf("<--");
    }
    printf("\n\n");
}

void ShowLeafPath(BiTree T, stack<char> &S){
    if(T!=NULL){
        S.push(T->data);
        if(!T->lchild && !T->rchild){
            PrintStack(S);
        }
        else{
            ShowLeafPath(T->lchild,S);
            ShowLeafPath(T->rchild,S);
        }
        S.pop();
    }
}