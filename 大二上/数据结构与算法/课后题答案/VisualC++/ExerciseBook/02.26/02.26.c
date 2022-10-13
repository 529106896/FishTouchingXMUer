#include <stdio.h>
#include "Status.h"      //**��01 ����**//
#include "LinkList.h"    //**��02 ���Ա�**//

/*
 * ��2.26
 *
 * �󽻼���C=A��B��Ҫ����������ٿռ䡣
 */
Status Algo_2_26(LinkList La, LinkList Lb, LinkList* Lc);

// ���Ժ�������ӡԪ��
void PrintElem(ElemType e);


int main(int argc, char* argv[]) {
    LinkList La, Lb, Lc;
    int i;
    
    // 0�ŵ�Ԫ�洢�������鳤��
    int a[] = {10, 1, 3, 5, 7,  9, 11, 13, 15, 17, 19};
    int b[] = {8,  1, 5, 7, 8, 10, 15, 17, 20};
    
    // ׼���������ݣ�ͬһ���е�Ԫ��ֵ������ͬ
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
    
    // �󽻼�
    Algo_2_26(La, Lb, &Lc);
    
    printf("Lc = ");
    ListTraverse(Lc, PrintElem);
    
    return 0;
}


// �󽻼���C=A��B��Ҫ����������ٿռ䡣
Status Algo_2_26(LinkList La, LinkList Lb, LinkList* Lc) {
    LinkList pa, pb, pc, s;
    
    // ��ʼ��Lc
    InitList(Lc);
    
    // ȷ��La��Lb����
    if(La == NULL || Lb == NULL) {
        return ERROR;
    }
    
    pa = La->next;
    pb = Lb->next;
    pc = *Lc;
    
    // ֻ����La��Lb�Ĺ�ͬ���־���
    while(pa != NULL && pb != NULL) {
        if(pa->data < pb->data) {
            pa = pa->next;
        } else if(pa->data > pb->data) {
            pb = pb->next;
        } else {
            // �����½���Ž���Ԫ��
            s = (LinkList) malloc(sizeof(LNode));
            if(s == NULL) {
                exit(OVERFLOW);
            }
            s->data = pa->data;
            s->next = NULL;
    
            // ������Ԫ�ز��뵽Lc
            pc->next = s;
            pc = pc->next;
            
            pa = pa->next;
            pb = pb->next;
        }
    }
    
    return OK;
}

// ���Ժ�������ӡԪ��
void PrintElem(ElemType e) {
    printf("%2d ", e);
}
