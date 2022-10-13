#include <stdio.h>
#include "Status.h"   //**��01 ����**//
#include "ALGraph.h"  //**��07 ͼ**//

/*
 * �ж�ͼG�Ƿ�ɴ���
 */
Status Algo_7_21(ALGraph G);


int main(int argc, char* argv[]) {
    ALGraph G;
    
    printf("���������������� ���������ͼ...\n");
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
    
    Algo_7_21(G) ? printf("ͼG�ɴ��ݣ�\n") : printf("ͼG���ɴ��ݣ�\n");
    printf("\n");
    
    return 0;
}


/*
 * �ж�ͼG�Ƿ�ɴ���
 */
Status Algo_7_21(ALGraph G) {
    Status trans;
    int x, y, z;
    ArcNode* py, * pz, * px;
    
    // Ԥ��Ϊ�ɴ���
    trans = TRUE;
    
    // ����V��ÿ��x
    for(x = 0; x < G.vexnum; x++) {
        // N(x)��ÿ��y
        for(py = G.vertices[x].firstarc; py != NULL; py = py->nextarc) {
            y = py->adjvex;
            
            for(pz = G.vertices[y].firstarc; pz != NULL; pz = pz->nextarc) {
                z = pz->adjvex;
                
                // �ų���x��ȵ�z
                if(z != x) {
                    for(px = G.vertices[x].firstarc; px != NULL; px = px->nextarc) {
                        if(px->adjvex == z) {
                            break;  // �ҵ�z��ʱ����
                        }
                    }
                    
                    // ���z����N(x)��
                    if(px == NULL) {
                        trans = FALSE;
                        return trans;
                    }
                }
                
            }
        }
    }
    
    return trans;
}
