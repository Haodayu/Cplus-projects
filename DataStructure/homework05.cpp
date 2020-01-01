#include "bitree.h"

int main() {
    BiTree tree;
    stack<char> S;

    printf("____________________________________\n\n");
    printf("1.输入任意值并回车代表节点值\n2.输入空格并回车代表该节点为空\n");
    printf("____________________________________\n\n先序输入二叉树：\n");
    CreateBiTree(tree);
    printf("____________________________________\n\n叶子结点数：%d",LeafNum(tree, 0));
    printf("\n____________________________________\n\n先序遍历：");
    PreOrderTraverse(tree);
    printf("\n____________________________________\n\n中序遍历：");
    InOrderTraverse(tree);
    printf("\n____________________________________\n\n后序遍历：");
    PostOrderTraverse(tree);
    printf("\n____________________________________\n\n树的深度：%d",TreeDeep(tree));

    printf("\n____________________________________\n\n根到各叶子的路径：\n\n");
    ShowLeafPath(tree,S);

    getchar();getchar();
}