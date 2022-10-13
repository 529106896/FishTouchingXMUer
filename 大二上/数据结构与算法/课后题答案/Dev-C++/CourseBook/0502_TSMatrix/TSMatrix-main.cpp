#include <stdio.h>
#include "TSMatrix.h"            //**��05 ����͹����**//

int main(int argc, char** argv) {
    TSMatrix M, N;
    
    printf("���������������� ���� CreateSMatrix \n");
    {
        printf("�� ��������ϡ����� M��N ...\n");
        CreateSMatrix(&M, "TestData_M.txt");
        CreateSMatrix(&N, "TestData_N.txt");
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� ���� PrintSMatrix \n");
    {
        printf("�� M = \n");
        PrintSMatrix(M);
        
        printf("�� N = \n");
        PrintSMatrix(N);
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� ���� CopySMatrix \n");
    {
        TSMatrix Tmp;
        
        printf("�� ���� M �� Tmp...\n");
        CopySMatrix(M, &Tmp);
        
        printf("�� Tmp = \n");
        PrintSMatrix(Tmp);
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� ���� AddSMatrix \n");
    {
        TSMatrix Q1;
        
        AddSMatrix(M, N, &Q1);
        
        printf("�� Q1 = M + N = \n");
        PrintSMatrix(Q1);
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� ���� SubSMatrix \n");
    {
        TSMatrix Q2;
        
        SubSMatrix(M, N, &Q2);
        
        printf("�� Q2 = M - N = \n");
        PrintSMatrix(Q2);
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� ���� MultSMatrix \n");
    {
        TSMatrix Q3;
        
        MultSMatrix(M, N, &Q3);
        
        printf("�� Q3 = M * N = \n");
        PrintSMatrix(Q3);
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� ���� TransposeSMatrix \n");
    {
        TSMatrix T1;
        
        TransposeSMatrix(M, &T1);
        
        printf("�� T1 = M(T) = \n");
        PrintSMatrix(T1);
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� ���� FastTransposeSMatrix \n");
    {
        TSMatrix T2;
        
        FastTransposeSMatrix(M, &T2);
        
        printf("�� T2 = M(T) = \n");
        PrintSMatrix(T2);
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� ���� DestroySMatrix \n");
    {
        printf("�� ���� M ǰ��");
        !M.mu && !M.nu && !M.tu ? printf(" M �����ڣ���\n") : printf(" M ���ڣ�\n");
        
        DestroySMatrix(&M);
        
        printf("�� ���� M ��");
        !M.mu && !M.nu && !M.tu ? printf(" M �����ڣ���\n") : printf(" M ���ڣ�\n");
    }
    PressEnterToContinue(debug);
    
    return 0;
}
