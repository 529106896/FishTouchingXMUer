#include <stdio.h>
#include "Status.h"      //**��01 ����**//
#include "LinkList.h"    //**��02 ���Ա�**//

/*
 * ��2.24
 *
 * �鲢��������������Ϊһ���ݼ�������
 * �鲢�����ǣ����ժ��La��Lb�е�Ԫ�أ���ʹ��ͷ�巨���뵽Lc��
 * �鲢��ɺ󣬽�ԭ���ÿգ��������١�
 */
Status Algo_2_24(LinkList La, LinkList Lb, LinkList* Lc);

// ���Ժ�������ӡԪ��
void PrintElem(ElemType e);


int main(int argc, char* argv[]) {
    LinkList La, Lb, Lc;
    int i;

    // 0�ŵ�Ԫ�洢�������鳤��
    int a[] = {10, 1, 3, 5, 7,  9, 11, 13, 15, 17, 19};
    int b[] = {8,  2, 3, 6, 7, 10, 15, 17, 20};

    // ׼����������
    InitList(&La);
    InitList(&Lb);
    for(i = 1; i <= a[0]; i++) {
        ListInsert(La, i, a[i]);
    }
    for(i = 1; i <= b[0]; i++) {
        ListInsert(Lb, i, b[i]);
    }
    printf("La = ");
    ListTraverse(La, PrintElem);
    printf("Lb = ");
    ListTraverse(Lb, PrintElem);

    // �鲢��������
    Algo_2_24(La, Lb, &Lc);

    printf("Lc = ");
    ListTraverse(Lc, PrintElem);

    return 0;
}


// �鲢��������������Ϊһ���ݼ�������
Status Algo_2_24(LinkList La, LinkList Lb, LinkList* Lc) {
    LinkList pa, pb;

    // ��ʼ��Lc
    InitList(Lc);
    
    // ȷ��La��Lb����
    if(La == NULL || Lb == NULL) {
        return ERROR;
    }
    
    // ����La��Lb
    while(La->next!=NULL && Lb->next!=NULL){
        pa = La->next;
        pb = Lb->next;

        // ժ��La�н�С��Ԫ��
        if(pa->data<=pb->data) {
            La->next = pa->next;

            // ��ժ�µ�Ԫ��ͨ��ͷ�巨���뵽Lc
            pa->next = (*Lc)->next;
            (*Lc)->next = pa;

            // ժ��Lb�н�С��Ԫ��
        } else {
            Lb->next = pb->next;

            // ��ժ�µ�Ԫ��ͨ��ͷ�巨���뵽Lc
            pb->next = (*Lc)->next;
            (*Lc)->next = pb;
        }
    }

    // ���La����ʣ�࣬��La��ʣ��Ԫ�ز��뵽Lc��
    while(La->next!=NULL){
        pa = La->next;
        La->next = pa->next;

        pa->next = (*Lc)->next;
        (*Lc)->next = pa;
    }

    // ���Lb����ʣ�࣬��Lb��ʣ��Ԫ�ز��뵽Lc��
    while(Lb->next!=NULL){
        pb = Lb->next;
        Lb->next = pb->next;

        pb->next = (*Lc)->next;
        (*Lc)->next = pb;
    }

    return OK;
}

// ���Ժ�������ӡԪ��
void PrintElem(ElemType e) {
    printf("%2d ", e);
}

