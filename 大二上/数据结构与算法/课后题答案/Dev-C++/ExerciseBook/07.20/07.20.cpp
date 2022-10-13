#include <stdio.h>
#include "Status.h"  //**��01 ����**//
#include "MGraph.h"  //**��07 ͼ**//

/*
 * �ж�ͼG�Ƿ�ɴ���
 */
Status Algo_7_20(MGraph G);


int main(int argc, char* argv[]) {
    MGraph G;
    
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
    
    Algo_7_20(G) ? printf("ͼG�ɴ��ݣ�\n") : printf("ͼG���ɴ��ݣ�\n");
    printf("\n");
    
    return 0;
}


/*
 * �ж�ͼG�Ƿ�ɴ���
 */
Status Algo_7_20(MGraph G) {
    Status trans;
    int x, y, z;
    int flag;   // ����ͨ�ı��
    
    // ����ͼ������ͨ�����0
    if(G.kind == DG || G.kind == UDG) {
        flag = 0;
        
        // ������������ͨ�����INFINITE
    } else if(G.kind == DN || G.kind == UDN) {
        flag = INFINITE;
    } else {
        return ERROR;
    }
    
    // Ԥ��Ϊ�ɴ���
    trans = TRUE;
    
    // ����V��ÿ��x
    for(x = 0; x < G.vexnum; x++) {
        // N(x)��ÿ��y
        for(y = 0; y < G.vexnum; y++) {
            if(G.arcs[x][y].adj != flag) {
                // N(y)�в�����x��ÿ��z
                for(z = 0; z < G.vexnum; z++) {
                    if(G.arcs[y][z].adj != flag && z != x) {
                        // z����N(x)��
                        if(G.arcs[x][z].adj == flag) {
                            // ���ɴ���
                            trans = FALSE;
                            return trans;
                        }
                    }
                }
            }
        }
    }
    
    return trans;
}
