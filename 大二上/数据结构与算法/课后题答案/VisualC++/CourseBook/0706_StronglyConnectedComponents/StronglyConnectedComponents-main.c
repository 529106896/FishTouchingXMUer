#include <stdio.h>
#include "OLGraph.h"
#include "StronglyConnectedComponents.h"

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
    }
    PressEnterToContinue(debug);
    
    printf("���������������� Tarjan�㷨��ȡǿ��ͨ����... \n");
    {
        Tarjan(G);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� Kosaraju�㷨��ȡǿ��ͨ����... \n");
    {
        Kosaraju(G);
    }
    PressEnterToContinue(debug);
    
    return 0;
}
