#include <stdio.h>
#include "CSTree.h"
#include "MinimumSpanningTree.h"
#include "Graph.h"

/*
 * ������������С������
 */
void Algo_7_33(Graph G);


int main(int argc, char* argv[]) {
    Graph G;
    
    printf("���������������� ��������ӡ������... \n");
    {
        CreateGraph(&G, "TestData_UDN.txt");
        PrintGraph(G);
        printf("\n");
    }
    
    printf("���������������� ʹ�ÿ�³˹�����㷨��ȡ��С������... \n");
    {
        Algo_7_33(G);
        printf("\n");
    }
}


/*
 * ������������С������
 */
void Algo_7_33(Graph G) {
    CSTree T = MinSpanTree_KRUSKAL(G);
    
    // �����ȡ����С���������˲����ѡ
    PrintTree(T);
}
