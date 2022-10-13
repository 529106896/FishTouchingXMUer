#include <stdio.h>
#include "Status.h"             //**��01 ����**//
#include "ALGraph.h"            //**��07 ͼ**//
#include "TopologicalSorting.h" //**��07 ͼ**//

/*
 * �������޻�ͼ�еĶ����ʵ��ر�ţ�ʹ�����л�vi->vj����i<j
 *
 * ע�����յ�26�⣬���ﱾ����ֻ������������
 */
void Algo_7_34(ALGraph G);

/*
 * ��ͼ�λ���ʽ����������˳����ͼ�ṹ
 *
 * ע����ͼ/���У�ʹ��"-"����ʾ�����㲻ֱ����ͨ
 */
static void PrintGraph_7_34(ALGraph G, int topo[MAX_VERTEX_NUM]);


int main(int argc, char* argv[]) {
    ALGraph G;
    
    printf("���������������� ���������ͼ...\n");
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
    
    printf("���������������� �������ͼ�Ķ���˳��...\n");
    {
        Algo_7_34(G);
        printf("\n");
    }
    
    return 0;
}


/*
 * �������޻�ͼ�еĶ����ʵ��ر�ţ�ʹ�����л�vi->vj����i<j
 *
 * ע�����յ�26�⣬���ﱾ����ֻ������������
 */
void Algo_7_34(ALGraph G) {
    int i;
    int topo[MAX_VERTEX_NUM];
    
    if(TopologicalSort(G, topo) == ERROR) {
        printf("����������ͼ���ڻ�·���޷���ȡ����������...\n");
        return;
    }
    
    printf("����ǰ��");
    for(i = 0; i < G.vexnum; i++) {
        printf("%c ", G.vertices[i].data);
    }
    printf("\n");
    
    printf("������");
    for(i = 0; i < G.vexnum; i++) {
        printf("%c ",G.vertices[topo[i]].data);
    }
    printf("\n\n");
    
    printf("���������������� ���ݵ�����Ķ�����򣬴�ӡ��洢�ṹ(�˲����ѡ)...\n");
    PrintGraph_7_34(G, topo);
}

/*
 * ��ͼ�λ���ʽ����������˳����ͼ�ṹ
 *
 * ע����ͼ/���У�ʹ��"-"����ʾ�����㲻ֱ����ͨ
 */
static void PrintGraph_7_34(ALGraph G, int topo[MAX_VERTEX_NUM]) {
    int i, j;
    int pos[MAX_VERTEX_NUM];
    int adjs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    ArcNode* p;
    
    // ��¼�����������������е�����
    for(i = 0; i < G.vexnum; i++) {
        pos[topo[i]] = i;
    }
    
    // ��ʼ��
    for(i = 0; i < G.vexnum; i++) {
        for(j = 0; j < G.vexnum; j++) {
            adjs[i][j] = 0;
        }
    }
    
    // ��������ͼ����֮��Ĺ�ϵ
    for(i = 0; i < G.vexnum; i++) {
        p = G.vertices[i].firstarc;
        
        while(p != NULL) {
            adjs[pos[i]][pos[p->adjvex]] = 1;
            p = p->nextarc;
        }
    }
    
    
    printf("  ");
    for(i = 0; i < G.vexnum; i++) {
        printf("  %c", G.vertices[topo[i]].data);
    }
    printf("\n");
    
    for(i = 0; i < G.vexnum; i++) {
        printf("%c ", G.vertices[topo[i]].data);
        
        for(j = 0; j < G.vexnum; j++) {
            if(adjs[i][j] == 0) {
                printf("  -");
            } else {
                printf("%3d", adjs[i][j]);
            }
        }
        
        printf("\n");
    }
}
