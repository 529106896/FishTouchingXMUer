#include <stdio.h>
#include "ALGraph.h"
#include "SpanningTree.h"
#include "ArticulationPoints.h"

int main(int argc, char* argv[]) {
    ALGraph G;
    
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
    
    printf("���������������� ��ӡ������ͼ�����������ò���Ǳ�Ҫ��ֻ������չʾ������ṹ���� \n");
    {
        CSTree T;
        
        printf("��������ͼ����������ɭ�֣�... \n");
        DFSForest(G, &T);
        PrintTree(T);
        printf("\n");
    }
    PressEnterToContinue(debug);
    
    printf("���������������� Ѱ�Ҳ�����ؽڵ�... \n");
    {
        printf("��ӡ�����ҵ��Ĺؽڵ㣺\n");
        FindArticul(G);
    }
    PressEnterToContinue(debug);
    
    return 0;
}
