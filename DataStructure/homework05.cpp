#include "bitree.h"

int main() {
    BiTree tree;
    stack<char> S;

    printf("____________________________________\n\n");
    printf("1.��������ֵ���س�����ڵ�ֵ\n2.����ո񲢻س�����ýڵ�Ϊ��\n");
    printf("____________________________________\n\n���������������\n");
    CreateBiTree(tree);
    printf("____________________________________\n\nҶ�ӽ������%d",LeafNum(tree, 0));
    printf("\n____________________________________\n\n���������");
    PreOrderTraverse(tree);
    printf("\n____________________________________\n\n���������");
    InOrderTraverse(tree);
    printf("\n____________________________________\n\n���������");
    PostOrderTraverse(tree);
    printf("\n____________________________________\n\n������ȣ�%d",TreeDeep(tree));

    printf("\n____________________________________\n\n������Ҷ�ӵ�·����\n\n");
    ShowLeafPath(tree,S);

    getchar();getchar();
}