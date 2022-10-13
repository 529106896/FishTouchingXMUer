#include <stdio.h>
#include "Status.h"      //**��01 ����**//
#include "LinkList.h"    //**��02 ���Ա�**//

/*
 * ��2.23
 *
 * ����һ����La�е�Ԫ�ز��뵽Lb�У�Ȼ����Lcָ��Lb
 *
 * ����鲢����������������ʹ��ԭ����Ĵ洢�ռ䡣
 */
Status Algo_2_23_1(LinkList La, LinkList Lb, LinkList* Lc);

/*
 * ��2.23
 *
 * ����������La��Lb�е�Ԫ�ؽ���ժ�£���������뵽Lc��
 *
 * ����鲢����������������ʹ��ԭ����Ĵ洢�ռ䡣
 */
Status Algo_2_23_2(LinkList La, LinkList Lb, LinkList* Lc);

// ���Ժ�������ӡԪ��
void PrintElem(ElemType e);


int main(int argc, char* argv[]) {
    LinkList La, Lb, Lc;
    int i;
    
    // 0�ŵ�Ԫ�洢�������鳤��
    int a[] = {10, 1, 3, 5, 7,  9, 11, 13, 15, 17, 19};
    int b[] = { 8, 2, 4, 6, 8, 10, 12, 14, 16};
    
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
//    Algo_2_23_1(La, Lb, &Lc);
    Algo_2_23_2(La, Lb, &Lc);
    
    printf("Lc = ");
    ListTraverse(Lc, PrintElem);
    
    return 0;
}


/*
 * ��2.23
 *
 * ����һ����La�е�Ԫ�ز��뵽Lb�У�Ȼ����Lcָ��Lb
 *
 * ����鲢����������������ʹ��ԭ����Ĵ洢�ռ䡣
 */
Status Algo_2_23_1(LinkList La, LinkList Lb, LinkList* Lc) {
    LinkList p, pb;
    
    // ��ʼ��Lc
    InitList(Lc);
    
    // ȷ��La��Lb����
    if(La == NULL || Lb == NULL) {
        return ERROR;
    }
    
    pb = Lb;
    
    // �ȱ���La��Lb�Ĺ�ͬ����
    while(La->next != NULL && pb->next != NULL) {
        // ��La��ժ�½��
        p = La->next;
        La->next = p->next;
        
        // ��La��ժ�µĽ����뵽Lb��
        p->next = pb->next;
        pb->next = p;
        
        // ǰ����ԭLb����һ������λ��
        pb = pb->next->next;
    }
    
    // ���La��ʣ�࣬��Lb�ѱ�������ͷ������Ҫ��La��ʣ��Ԫ���������ӵ�Lb��β��
    if(pb->next == NULL && La->next != NULL) {
        pb->next = La->next;
        La->next = NULL;
    }
    
    // ��Lcָ��Lb������
    (*Lc)->next = Lb->next;
    Lb->next = NULL;
    
    return OK;
}

/*
 * ��2.23
 *
 * ����������La��Lb�е�Ԫ�ؽ���ժ�£���������뵽Lc��
 *
 * ����鲢����������������ʹ��ԭ����Ĵ洢�ռ䡣
 */
Status Algo_2_23_2(LinkList La, LinkList Lb, LinkList* Lc) {
    LinkList p, pc;
    int flag;   // ָ�ӵ�ǰӦ��ժ��La�е�Ԫ�ػ���ժ��Lb�е�Ԫ��
    
    // ��ʼ��Lc
    InitList(Lc);
    
    // ȷ��La��Lb����
    if(La == NULL || Lb == NULL) {
        return ERROR;
    }
    
    flag = 0;
    pc = *Lc;
    
    // �ȱ���La��Lb�Ĺ�ͬ����
    while(La->next!=NULL && Lb->next!=NULL){
        // ժ��La�е�Ԫ��
        if(flag==0) {
            // ժ��La�е�Ԫ��
            p = La->next;
            La->next = p->next;
            
            flag = 1;
    
            // ժ��La�е�Ԫ��
        } else {
            p = Lb->next;
            Lb->next = p->next;
    
            flag = 0;
        }
    
        // ��ժ�µ�Ԫ�ز��뵽Lc
        pc->next = p;
        pc = pc->next;
    }
    
    // ���La�Ѿ���������ͷ(Lb������ʣ��)
    if(La->next==NULL) {
        // ժ��Lb�п���ʣ�������Ԫ��
        p = Lb->next;
        Lb->next = NULL;
        pc->next = p;
    
        // ���La��ʣ��(Lbһ����������ͷ�ˣ����������whileѭ�������ִ��)
    } else {
        // ժ��La��ʣ���Ԫ��
        p = La->next;
        La->next = NULL;
        pc->next = p;
    }
    
    return OK;
}

// ���Ժ�������ӡԪ��
void PrintElem(ElemType e) {
    printf("%2d ", e);
}
