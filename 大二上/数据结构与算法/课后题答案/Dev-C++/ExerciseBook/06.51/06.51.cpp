#include <stdio.h>
#include "Status.h"     //**��01 ����**//
#include "BiTree.h"     //**��06 ���Ͷ�����**//

/*
 * ����������ʽ���ɵĶ����������������
 */
void Algo_6_51(BiTree T);

// �ж��ַ�c�Ƿ�Ϊ������
Status IsOperator(char c);


int main(int argc, char* argv[]) {
    BiTree T;

    printf("�������������������У�T...\n");
    InitBiTree(&T);
    CreateBiTree(&T, "TestData.txt");
    PrintTree(T);
    printf("\n");

    printf("����������ʽ��");
    Algo_6_51(T);
    printf("\n");

    return 0;
}


/*
 * ����������ʽ���ɵĶ����������������
 */
void Algo_6_51(BiTree T) {
    if(T == NULL) {
        return;
    }

    if(T->lchild != NULL) {
        // �������Ǳ��ʽ�����������
        if(IsOperator(T->lchild->data)) {
            printf("(");
            Algo_6_51(T->lchild);
            printf(")");
        } else {
            Algo_6_51(T->lchild);
        }
    }

    printf("%c", T->data);

    if(T->rchild != NULL) {
        // �������Ǳ��ʽ�����������
        if(IsOperator(T->rchild->data)) {
            printf("(");
            Algo_6_51(T->rchild);
            printf(")");
        } else {
            Algo_6_51(T->rchild);
        }
    }
}

// �ж��ַ�c�Ƿ�Ϊ������
Status IsOperator(char c) {
    if(c == '+' || c == '-' || c == '*' || c == '/') {
        return TRUE;
    } else {
        return ERROR;
    }
}

