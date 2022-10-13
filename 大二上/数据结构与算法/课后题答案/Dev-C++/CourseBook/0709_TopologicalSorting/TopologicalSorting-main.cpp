#include <stdio.h>
#include "ALGraph.h"
#include "TopologicalSorting.h"

int main(int argc, char* argv[]) {
    ALGraph G;
    
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
    
    printf("���������������� �������ͼ����������... \n");
    {
        int topo[MAX_VERTEX_NUM];
        int i;
        
        if(TopologicalSort(G, topo)) {
            printf("�������й����ɹ���");
            for(i=0; i<G.vexnum; i++) {
                printf("%c ", G.vertices[topo[i]].data);
            }
        } else {
            printf("�쳣�˳�������������ͼ�д��ڻ�·�����޷�������������������...\n");
        }
    }
    PressEnterToContinue(debug);
    
    return 0;
}
