#include <stdio.h>	
#include "../../../���α��㷨ʵ��/��02 ���Ա�/01 SequenceList/SequenceList.c"	//**��02 ���Ա�**//

/*
 * ��2.25
 *
 * �󽻼���C=A��B��Ҫ����˳�����ٿռ䡣
 */
Status Algo_2_25(SqList La, SqList Lb, SqList* Lc);

// ���Ժ�������ӡԪ��
void PrintElem(LElemType_Sq e);


int main(int argc, char* argv[]) {
    SqList La, Lb, Lc;
    int i;
    
    // 0�ŵ�Ԫ�洢�������鳤��
    int a[] = {10, 1, 3, 5, 7,  9, 11, 13, 15, 17, 19};
    int b[] = {8,  1, 5, 7, 8, 10, 15, 17, 20};
    
    // ׼���������ݣ�ͬһ���е�Ԫ��ֵ������ͬ
    InitList_Sq(&La);
    InitList_Sq(&Lb);
    for(i = 1; i <= a[0]; i++) {
        ListInsert_Sq(&La, i, a[i]);
    }
    for(i = 1; i <= b[0]; i++) {
        ListInsert_Sq(&Lb, i, b[i]);
    }
    printf("La = ");
    ListTraverse_Sq(La, PrintElem);
    printf("\n");
    printf("Lb = ");
    ListTraverse_Sq(Lb, PrintElem);
    printf("\n");
    
    // �󽻼�
    Algo_2_25(La, Lb, &Lc);
    
    printf("Lc = ");
    ListTraverse_Sq(Lc, PrintElem);
    printf("\n");
    
    return 0;
}

// �󽻼���C=A��B��Ҫ����˳�����ٿռ䡣
Status Algo_2_25(SqList La, SqList Lb, SqList* Lc) {
    int i, j, k;
    
    // ��ʼ��Lc
    InitList_Sq(Lc);
    
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
            ListInsert_Sq(Lc, k, La.elem[i]);
            k++;
            i++;
            j++;
        }
    }
    
    return OK;
}

// ���Ժ�������ӡԪ��
void PrintElem(LElemType_Sq e) {
    printf("%2d ", e);
}
