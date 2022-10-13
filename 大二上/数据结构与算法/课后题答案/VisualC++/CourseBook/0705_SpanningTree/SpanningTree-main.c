#include <stdio.h>
#include "MGraph.h"
#include "SpanningTree.h"

int main(int argc, char* argv[]) {
    MGraph G;
    
    printf("���������������� ��������ӡ����ͼ... \n");
    {
        char* path[4];
    
        path[0] = "";
        path[1] = "";
        path[2] = "TestData_UDG.txt";
        path[3] = "";
    
        CreateGraph(&G, path);
        PrintGraph(G);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� DFSForest��DFSTree \n");
    {
        CSTree T;
        
        printf("��������ͼ����������ɭ�֣�... \n");
        DFSForest(G, &T);
        PrintTree(T);
        printf("\n");
    }
    PressEnterToContinue(debug);
    
    return 0;
}
