#include <stdio.h>
#include "ALGraph.h"
#include "ShortestPaths.h"

/*
 * ʹ��Dijkstra�㷨����ӵ�Դ������������·��
 */
void Algo_7_42(ALGraph G, int v0, PathMatrix_DIJ P, ShortPathTable_DIJ D);


int main(int argc, char* argv[]) {
    ALGraph G;
    
    printf("���������������� ��������ӡ����ͼ/��... \n");
    {
        char* path[4];
        
        path[0] = "TestData_DG.txt";
        path[1] = "TestData_DN.txt";
        path[2] = "TestData_UDG.txt";
        path[3] = "TestData_UDN.txt";
        
        CreateGraph(&G, path);
        PrintGraph(G);
        printf("\n");
    }
    
    printf("���������������� �Ͻ�˹�����㷨��Դ���·��... \n");
    {
        VertexType v0 = 'A';
        PathMatrix_DIJ P;
        ShortPathTable_DIJ D;
    
        printf("����Ӷ��� %c �����ඥ������·����\n", v0);
        Algo_7_42(G, LocateVex(G, v0), P, D);
        printf("\n");
    }
}


/*
 * ʹ��Dijkstra�㷨����ӵ�Դ������������·��
 */
void Algo_7_42(ALGraph G, int v0, PathMatrix_DIJ P, ShortPathTable_DIJ D) {
    
    // ���������ȵ��ô˺������������֮��Ĺ�ϵ
    GetAdjs(G);
    
    // ���·���㷨
    ShortestPath_DIJ(G, v0, P, D);
    
    // ��ӡ������Ľ�����˲����ѡ��
    PrintPath_DIJ(G, v0, P, D);
}
