#include <stdio.h>
#include "OLGraph.h"
#include "StronglyConnectedComponents.h"

/*
 * ������ͼ��ǿ��ͨ����
 */
void Algo_7_31(OLGraph G);


int main(int argc, char* argv[]) {
    OLGraph G;
    
    printf("���������������� ��������ӡ����ͼ... \n");
    {
        char* path[4];
        
        path[0] = "TestData_DG.txt";
        path[1] = "";
        path[2] = "";
        path[3] = "";
        
        CreateGraph(&G, path);
        PrintGraph(G);
        printf("\n");
    }
    
    printf("���������������� ������ͼ��ǿ��ͨ����... \n");
    {
        Algo_7_31(G);
        printf("\n");
    }
    
    return 0;
}


/*
 * ������ͼ��ǿ��ͨ����
 */
void Algo_7_31(OLGraph G) {
    printf("Tarjan�㷨��\n");
    Tarjan(G);
    
//    printf("Kosaraju�㷨��\n");
//    Kosaraju(G);
}
