#include <stdio.h>
#include "ALGraph.h"
#include "CriticalPathMethod.h"

int main(int argc, char* argv[]) {
    ALGraph G;
    
    printf("���������������� ��������ӡ������... \n");
    {
        char* path[4];
        
        path[0] = "";
        path[1] = "TestData_DN.txt";
        path[2] = "";
        path[3] = "";
        
        CreateGraph(&G, path);
        PrintGraph(G);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� ��ȡ�������Ĺؼ�·��... \n");
    {
        CriticalPath(G);
    }
    PressEnterToContinue(debug);
    
    return 0;
}
