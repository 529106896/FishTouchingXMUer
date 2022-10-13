#include <stdio.h>
#include "Status.h"    //**��01 ����**//
#include "SqList.h"    //**��02 ���Ա�**//

/*
 * ��2.25
 *
 * �󽻼���C=A��B��Ҫ����˳�����ٿռ䡣
 */
Status Algo_2_25(SqList La, SqList Lb, SqList* Lc);

// ���Ժ�������ӡԪ��
void PrintElem(ElemType e);


int main(int argc, char* argv[]) {
    SqList La, Lb, Lc;
    int i;
    
    // 0�ŵ�Ԫ�洢�������鳤��
    int a[] = {10, 1, 3, 5, 7,  9, 11, 13, 15, 17, 19};
    int b[] = {8,  1, 5, 7, 8, 10, 15, 17, 20};
    
    // ׼���������ݣ�ͬһ���е�Ԫ��ֵ������ͬ
    InitList(&La);
    InitList(&Lb);
    for(i = 1; i <= a[0]; i++) {
        ListInsert(&La, i, a[i]);
    }
    for(i = 1; i <= b[0]; i++) {
        ListInsert(&Lb, i, b[i]);
    }
    printf("La = ");
    ListTraverse(La, PrintElem);
    printf("Lb = ");
    ListTraverse(Lb, PrintElem);
    
    // �󽻼�
    Algo_2_25(La, Lb, &Lc);
    
    printf("Lc = ");
    ListTraverse(Lc, PrintElem);
    
    return 0;
}

// �󽻼���C=A��B��Ҫ����˳�����ٿռ䡣
Status Algo_2_25(SqList La, SqList Lb, SqList* Lc) {
    int i, j, k;
    
    // ��ʼ��Lc
    InitList(Lc);
    
    // ȷ��La��Lb����
    if(La.elem == NULL || Lb.elem == NULL) {
        return ERROR;
    }
    
    i = j = 0;  // ����La��Lb
    k = 1;      // ����Lc
    
    // ֻ����La��Lb�Ĺ�ͬ���־���
    while(i < La.length && j < Lb.length) {
        if(La.elem[i] < Lb.elem[j]) {
            i++;
        } else if(La.elem[i] > Lb.elem[j]) {
            j++;

            // ���La��Lb�е�Ԫ�����
        } else {
            // ������Ԫ�ز��뵽Lc
            ListInsert(Lc, k, La.elem[i]);
            k++;
            i++;
            j++;
        }
    }
    
    return OK;
}

// ���Ժ�������ӡԪ��
void PrintElem(ElemType e) {
    printf("%2d ", e);
}
