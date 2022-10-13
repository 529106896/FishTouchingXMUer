#include <stdio.h>
#include "LinkList.h"    //**��02 ���Ա�**//

/*
 * ��2.28
 *
 * �󽻼���C=A��B��
 *
 * A��B��Ԫ�ؿ����ظ�����C��Ԫ�ز��ظ���
 * ���ң�Ҫ��C����Aԭ�еĿռ䣬����A�е���Ч���ᱻ�ͷš�
 */
Status Algo_2_28(LinkList La, LinkList Lb, LinkList* Lc);

// ���Ժ�������ӡԪ��
void PrintElem(ElemType e);


int main(int argc, char* argv[]) {
    LinkList La, Lb, Lc;
    int i;
    
    // 0�ŵ�Ԫ�洢�������鳤��
    int a[] = {10, 1, 1, 1, 7, 7,  9, 10, 18, 18, 19};
    int b[] = {8,  1, 1, 7, 7, 7, 15, 18, 18};
    
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
    Algo_2_28(La, Lb, &Lc);
    
    printf("Lc = ");
    ListTraverse(Lc, PrintElem);
    
    return 0;
}


/*
 * ��2.28
 *
 * �󽻼���C=A��B��
 *
 * A��B��Ԫ�ؿ����ظ�����C��Ԫ�ز��ظ���
 * ���ң�Ҫ��C����Aԭ�еĿռ䣬����A�е���Ч���ᱻ�ͷš�
 */
Status Algo_2_28(LinkList La, LinkList Lb, LinkList* Lc) {
    LinkList pa, pb, pc, s;
    
    // ȷ��La��Lb����
    if(La == NULL || Lb == NULL) {
        return ERROR;
    }
    
    // Lc����La�Ŀռ�
    *Lc = La;
    
    pa = La->next;
    pb = Lb->next;
    pc = *Lc;
    
    // ����La��Lb�Ĺ�ͬ����
    while(pa != NULL && pb != NULL) {
        if(pa->data < pb->data) {
            pc->next = pa->next;
            free(pa);   // �ͷ�La�е���Ч���
            pa = pc->next;
        } else if(pa->data > pb->data) {
            pb = pb->next;
            
            // ��������Ԫ��
        } else {
            // ���Lc��Ϊ�գ�����Ҫȷ��Lc�е�Ԫ�ز��ظ�
            if(pc == (*Lc) || pc->data != pa->data) {
                pc = pc->next;  // pc�α�ֱ��ǰ�����൱�ڱ�����paָ���Ԫ��
                
                pa = pa->next;
            } else {
                // ����ý���Ԫ���Ѿ������ˣ����ͷ�������
                pc->next = pa->next;
                free(pa);   // �ͷ�La�е���Ч���
                
                pa = pc->next;
            }
    
            // pb�����ճ�ǰ��
            pb = pb->next;
        }
    }
    
    // Lc�����ɣ�Lc��La����һ���ڴ�
    pc->next = NULL;

    // �ͷ�La�ж������Ч���
    while(pa!=NULL){
        s = pa;
        pa = pa->next;
        free(s);
    }
    
    return OK;
}

// ���Ժ�������ӡԪ��
void PrintElem(ElemType e) {
    printf("%2d ", e);
}
