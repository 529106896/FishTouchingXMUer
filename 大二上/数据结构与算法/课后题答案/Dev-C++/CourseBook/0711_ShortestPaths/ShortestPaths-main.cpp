#include <stdio.h>
#include "MGraph.h"
#include "ShortestPaths.h"

int main(int argc, char* argv[]) {
    MGraph G;
    
    printf("���������������� ��������ӡ����ͼ/��... \n");
    {
        char* path[4];
        
        path[0] = "TestData_DG.txt";
        path[1] = "TestData_DN.txt";
        path[2] = "TestData_UDG.txt";
        path[3] = "TestData_UDN.txt";
        
        CreateGraph(&G, path);
        PrintGraph(G);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� �Ͻ�˹�����㷨��Դ���·��... \n");
    {
        VertexType v0 = 'A';
        PathMatrix_DIJ P;
        ShortPathTable_DIJ D;
        
        printf("����Ӷ��� %c �����ඥ������·����\n", v0);
        ShortestPath_DIJ(G, LocateVex(G, v0), P, D);
        PrintPath_DIJ(G, LocateVex(G, v0), P, D);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� ���������㷨���Դ���·��... \n");
    {
        PathMatrix_FLOYD P;
        ShortPathTable_FLOYD D;
        
        printf("������Զ���֮������·����\n");
        ShortestPath_FLOYD(G, P, D);
        PrintPath_FLOYD(G, P, D);
    }
    PressEnterToContinue(debug);
    
}
