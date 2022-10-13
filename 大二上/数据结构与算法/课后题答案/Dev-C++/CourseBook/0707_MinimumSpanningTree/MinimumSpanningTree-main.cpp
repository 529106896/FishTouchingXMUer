#include <stdio.h>
#include "MGraph.h"
#include "MinimumSpanningTree.h"

int main(int argc, char* argv[]) {
    MGraph G;
    
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
    
    printf("���������������� ʹ������ķ�㷨��ȡ��С������... \n");
    {
        MinSpanTree_PRIM(G, 'A'); // Ĭ�ϴӶ���'A'����
    }
    PressEnterToContinue(debug);
    
    printf("���������������� ʹ�ÿ�³˹�����㷨��ȡ��С������... \n");
    {
        MinSpanTree_KRUSKAL(G);
    }
    PressEnterToContinue(debug);
    
}
