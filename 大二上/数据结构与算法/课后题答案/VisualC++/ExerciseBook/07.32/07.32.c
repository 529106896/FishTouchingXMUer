#include <stdio.h>
#include "CSTree.h"
#include "ALGraph.h"
#include "MinimumSpanningTree.h"

/*
 * ������������С����ɭ��
 */
void Algo_7_32(ALGraph G);


int main(int argc, char* argv[]) {
    ALGraph G;
    
    printf("���������������� ��������ӡ������... \n");
    {
        char* path[4];
        
        path[0] = "";
        path[1] = "";
        path[2] = "";
        path[3] = "TestData_UDN.txt";
        
        CreateGraph(&G, path);
        PrintGraph(G);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� ʹ������ķ�㷨��ȡ��С����ɭ��... \n");
    {
        Algo_7_32(G);
    }
    PressEnterToContinue(debug);
    
}


/*
 * ������������С����ɭ��
 */
void Algo_7_32(ALGraph G) {
    CSTree T = MinSpanTree_PRIM(G);
    
    // �����ȡ����С����ɭ�֣��˲����ѡ
    PrintTree(T);
}
