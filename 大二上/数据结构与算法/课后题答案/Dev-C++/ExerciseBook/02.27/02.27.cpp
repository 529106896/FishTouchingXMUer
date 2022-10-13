#include <stdio.h>
#include "SqList.h"    //**��02 ���Ա�**//

/*
 * ��2.27
 *
 * �󽻼���C=A��B��
 *
 * A��B��Ԫ�ؿ����ظ�����C��Ԫ�ز��ظ���
 * ���ң�Ҫ��C����Aԭ�еĿռ䡣
 */
Status Algo_2_27(SqList La, SqList Lb, SqList* Lc);

// ���Ժ�������ӡԪ��
void PrintElem(ElemType e);


int main(int argc, char* argv[]) {
    SqList La, Lb, Lc;
    int i;

    // 0�ŵ�Ԫ�洢�������鳤��
    int a[] = {10, 1, 3, 3, 7,  9, 10, 13, 15, 15, 19};
    int b[] = {8,  1, 3, 7, 7, 10, 18, 18, 20};

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

    // �󽻼����������Ԫ�ظ�����ͬ
    Algo_2_27(La, Lb, &Lc);

    printf("Lc = ");
    ListTraverse(Lc, PrintElem);

    return 0;
}


/*
 * ��2.27
 *
 * �󽻼���C=A��B��
 *
 * A��B��Ԫ�ؿ����ظ�����C��Ԫ�ز��ظ���
 * ���ң�Ҫ��C����Aԭ�еĿռ䡣
 */
Status Algo_2_27(SqList La, SqList Lb, SqList* Lc) {
    int i, j, k;

    // ȷ��La��Lb����
    if(La.elem == NULL || Lb.elem == NULL) {
        return ERROR;
    }

    // ��ʼ��Lc��ʹ��ֱ��ʹ��La�Ĵ洢�ռ�
    *Lc = La;

    i = j = 0;  // ����La��Lb
    k = 0;      // ����Lc

    // ֻ����La��Lb�Ĺ�ͬ���־���
    while(i < La.length && j < Lb.length) {
        if(La.elem[i] < Lb.elem[j]) {
            i++;
        } else if(La.elem[i] > Lb.elem[j]) {
            j++;

            // ���La��Lb�е�Ԫ�����
        } else {
            // ���Lc��Ϊ�գ�����Ҫ��֤���е�Ԫ�ز��ظ�
            if(k == 0 || (*Lc).elem[k - 1] != La.elem[i]) {
                (*Lc).elem[k] = La.elem[i];
                k++;
            }

            i++;
            j++;
        }
    }

    // ����˳���Lc�ĳ���
    (*Lc).length = k;

    return OK;
}

void PrintElem(ElemType e) {
    printf("%2d ", e);
}

