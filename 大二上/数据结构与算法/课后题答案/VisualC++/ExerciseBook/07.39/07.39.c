#include <stdio.h>
#include "SqList.h"
#include "BiTree.h"

/*
 * ��ȡ�洢�ڶ������еı��ʽ���沨��ʽ
 *
 * ע�����ʽ�ṹ�ο��̲Ĳ�ͼ7.22
 */
void Algo_7_39(BiTree T);

/*
 * �Ӷ������ĸ���������ȡ���д洢�ı��ʽ���沨��ʽ��
 * ��ȡ���沨��ʽ��洢��RPN�С�
 *
 * ע��ʹ���˺�������
 */
static void AntiPolandFormula_7_39(BiTree T, SqList* RPN);


int main(int argc, char* argv[]) {
    BiTree T;
    
    printf("���������������� ��������ӡ������... \n");
    {
        InitBiTree(&T);
        CreateBiTree(&T, "TestData_Pre.txt");
        PrintTree(T);
        printf("\n");
    }
    
    printf("���������������� ��ȡ�������д洢�ı��ʽ���沨��ʽ... \n");
    {
        Algo_7_39(T);
        printf("\n");
    }
    
    return 0;
}


/*
 * ��ȡ�洢�ڶ������еı��ʽ���沨��ʽ
 *
 * ע�����ʽ�ṹ�ο��̲Ĳ�ͼ7.23
 */
void Algo_7_39(BiTree T) {
    int i;
    SqList RPN;  // �洢�沨�����ʽ
    ElemType e;
    
    // ��ʼ������Ϊ0�����Ա�
    InitList(&RPN);
    
    // �������޻�ͼ�ĸ���������ͨ��β�ݹ��ȡ�����д洢�ı��ʽ���沨��ʽ
    AntiPolandFormula_7_39(T, &RPN);
    
    for(i = 1; i <= ListLength(RPN); i++) {
        GetElem(RPN, i, &e);
        printf("%c", e);
    }
    printf("\n");
}

/*
 * �Ӷ������ĸ���������ȡ���д洢�ı��ʽ���沨��ʽ��
 * ��ȡ���沨��ʽ��洢��RPN�С�
 *
 * ע��ʹ���˺�������
 */
void AntiPolandFormula_7_39(BiTree T, SqList* RPN) {
    if(T == NULL) {
        return;
    }
    
    AntiPolandFormula_7_39(T->lchild, RPN);
    AntiPolandFormula_7_39(T->rchild, RPN);
    // ��û�к��ӽ��ɱ���ʱ���洢��ǰ���
    ListInsert(RPN, ListLength(*RPN) + 1, T->data);
}
