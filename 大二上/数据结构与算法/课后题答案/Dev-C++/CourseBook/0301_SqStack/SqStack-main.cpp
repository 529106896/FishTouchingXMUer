#include <stdio.h>
#include "SqStack.h"    //**��03 ջ�Ͷ���**//

// ���Ժ�������ӡԪ��
void PrintElem(SElemType e) {
    printf("%d ", e);
}


int main(int argc, char** argv) {
    SqStack S;
    int i;
    SElemType e;
    
    printf("���������������� ���� InitStack \n");
    {
        printf("�� ��ʼ��˳��ջ S ...\n");
        InitStack(&S);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� ���� StackEmpty \n");
    {
        StackEmpty(S) ? printf("�� S Ϊ�գ���\n") : printf("�� S ��Ϊ�գ�\n");
    }
    PressEnterToContinue(debug);
    
    printf("���������������� ���� Push \n");
    {
        for(i = 1; i <= 6; i++) {
            Push(&S, 2 * i);
            printf("�� �� \"%2d\" ѹ��ջ S ...\n", 2 * i);
        }
    }
    PressEnterToContinue(debug);
    
    printf("���������������� ���� StackTraverse \n");
    {
        printf("�� S �е�Ԫ��Ϊ��S = ");
        StackTraverse(S, PrintElem);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� ���� StackLength \n");
    {
        i = StackLength(S);
        printf("�� S �ĳ���Ϊ %d \n", i);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� ���� Pop \n");
    {
        Pop(&S, &e);
        printf("�� ջ��Ԫ�� \"%d\" ��ջ...\n", e);
        printf("�� S �е�Ԫ��Ϊ��S = ");
        StackTraverse(S, PrintElem);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� ���� GetTop \n");
    {
        GetTop(S, &e);
        printf("�� ջ��Ԫ�ص�ֵΪ \"%d\" \n", e);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� ���� ClearStack \n");
    {
        printf("�� ��� S ǰ��");
        StackEmpty(S) ? printf(" S Ϊ�գ���\n") : printf(" S ��Ϊ�գ�\n");
        
        ClearStack(&S);
        
        printf("�� ��� S ��");
        StackEmpty(S) ? printf(" S Ϊ�գ���\n") : printf(" S ��Ϊ�գ�\n");
    }
    PressEnterToContinue(debug);
    
    printf("���������������� ���� DestroyStack \n");
    {
        printf("�� ���� S ǰ��");
        S.base != NULL && S.top != NULL ? printf(" S ���ڣ�\n") : printf(" S �����ڣ���\n");
        
        DestroyStack(&S);
        
        printf("�� ���� S ��");
        S.base != NULL && S.top != NULL ? printf(" S ���ڣ�\n") : printf(" S �����ڣ���\n");
    }
    PressEnterToContinue(debug);
    
    return 0;
}
