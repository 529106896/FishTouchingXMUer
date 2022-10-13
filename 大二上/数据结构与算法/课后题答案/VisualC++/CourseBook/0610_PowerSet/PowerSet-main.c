#include <stdio.h>
#include "PowerSet.h"   //**��06 ���Ͷ�����**//

int main(int argc, char* argv[]) {
    List A;
    
    printf("���������������� CreatePowerSet \n");
    {
        printf("�� �������� A ...\n");
        CreatePowerSet(&A, "TestData_A.txt");
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� PrintPowerSet \n");
    {
        printf("�� ������� A = ");
        PrintPowerSet(A);
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� GetPowerSet \n");
    {
        LinkList B;
        
        printf("�� ���㼯�ϵ��ݼ�...\n");
        
        printf("�� �������� B ��ʱ�洢�ݼ�Ԫ��...\n");
        InitList(&B);
        
        printf("�� ���������ȡ���ݼ��еĸ��Ӽ�...\n");
        GetPowerSet(1, A, B);
    }
    PressEnterToContinue(debug);
    
    return OK;
}
