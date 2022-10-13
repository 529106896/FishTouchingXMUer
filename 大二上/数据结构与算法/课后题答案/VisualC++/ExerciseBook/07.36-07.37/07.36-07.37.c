#include <stdio.h>
#include "Status.h"             //**��01 ����**//
#include "ALGraph.h"            //**��07 ͼ**//
#include "TopologicalSorting.h" //**��07 ͼ**//

/*
 * �������޻�ͼ��������·����
 *
 * ���Խ������������У��Ӻ���ǰ�����������������·����
 * ԭ���Ƕ�����һ����������·��p1�����ڽӵ���·��p2Ҳ�ض����·��p1�ϣ�
 * ����ĳ������·�� = max{�ڽӵ���·��}
 *
 * ����û�н�MPL��ֱ��д��ALGraph�ṹ�У����ǽ��䵥����Ϊһ������ȡ�������ں����㷨��û���κ�����
 */
void Algo_7_36(ALGraph G, int MPL[MAX_VERTEX_NUM][MAX_VERTEX_NUM + 1]);

/*
 * ��ӡ��������·��
 */
static void PrintPath_7_36(ALGraph G, int MPL[MAX_VERTEX_NUM][MAX_VERTEX_NUM + 1]);

/*
 * ��ȡ�����޻�ͼ���·��
 */
void Algo_7_37(ALGraph G, int mpl[MAX_VERTEX_NUM + 1]);


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
    
    printf("���������������� ��7.36����ȡ�����޻�ͼ��������·��...\n");
    {
        int MPL[MAX_VERTEX_NUM][MAX_VERTEX_NUM + 1];
        
        Algo_7_36(G, MPL);
        PrintPath_7_36(G, MPL);
        printf("\n");
    }
    
    printf("���������������� ��7.37����ȡ�����޻�ͼ�е��·��...\n");
    {
        int mpl[MAX_VERTEX_NUM + 1];
        int i;
        
        Algo_7_37(G, mpl);
        for(i = 1; i <= mpl[0] + 1; i++) {
            printf("%c ", G.vertices[mpl[i]].data);
        }
        printf("\n");
    }
    
    return 0;
}


/*
 * �������޻�ͼ��������·����
 *
 * ���Խ������������У��Ӻ���ǰ�����������������·����
 * ԭ���Ƕ�����һ����������·��p1�����ڽӵ���·��p2Ҳ�ض����·��p1�ϣ�
 * ����ĳ������·������ = max{�ڽӵ���·������} + 1
 *
 * ����û�н�MPL��ֱ��д��ALGraph�ṹ�У����ǽ��䵥����Ϊһ������ȡ�������ں����㷨��û���κ�����
 */
void Algo_7_36(ALGraph G, int MPL[MAX_VERTEX_NUM][MAX_VERTEX_NUM + 1]) {
    int i, j, v, w;
    int max, k;
    int topo[MAX_VERTEX_NUM];
    ArcNode* p;
    
    if(TopologicalSort(G, topo) == ERROR) {
        printf("����������ͼ���ڻ�·���޷���ȡ����������...\n");
        return;
    }
    
    // ���������������
    for(i = G.vexnum - 1; i >= 0; i--) {
        v = topo[i];
        
        MPL[v][0] = 0;  // 0�ŵ�Ԫ�洢·������
        MPL[v][1] = v;  // 1�ŵ�Ԫ�洢·������ʼ�������
        
        p = G.vertices[v].firstarc;
        
        // ����û���ڽӵ�Ķ��㣬���·������Ϊ0���������о���ȥ
        if(p == NULL) {
            continue;
        }
        
        max = -1;   // �ڽӵ������·������
        k = -1;     // ��¼ӵ�����·�����ȵ��ڽӵ�����
        
        // �����ڽӵ�
        while(p != NULL) {
            w = p->adjvex;  // �ڽӵ����
            
            // ����ж�����ͬ���ȵ�·������ֻȡ���ȷ��ֵ�һ��
            if(MPL[w][0] > max) {
                max = MPL[w][0];
                k = w;
            }
            
            p = p->nextarc;
        }
        
        // �����·������ =  max{�ڽӵ���·������} + 1
        MPL[v][0] = max + 1;
        
        // ���ڽӵ�������·�����Ƶ���ǰ������·����
        for(j = 1; j <= max + 1; j++) {
            MPL[v][j + 1] = MPL[k][j];
        }
    }
}

/*
 * ��ӡ��������·��
 */
static void PrintPath_7_36(ALGraph G, int MPL[MAX_VERTEX_NUM][MAX_VERTEX_NUM + 1]) {
    int i, j;
    
    for(i = 0; i < G.vexnum; i++) {
        printf("�Ӷ��� %c �������·��Ϊ��", G.vertices[i].data);
        for(j = 1; j <= MPL[i][0] + 1; j++) {
            printf("%c ", G.vertices[MPL[i][j]].data);
        }
        printf("\n");
    }
}

/*
 * ��ȡ�����޻�ͼ���·��
 */
void Algo_7_37(ALGraph G, int mpl[MAX_VERTEX_NUM + 1]) {
    int MPL[MAX_VERTEX_NUM][MAX_VERTEX_NUM + 1];
    int i, max, k;
    
    // ��ȡ���ж�����·��
    Algo_7_36(G, MPL);
    
    max = -1;
    
    for(i = 0; i < G.vexnum; i++) {
        if(MPL[i][0] > max) {
            max = MPL[i][0];
            k = i;
        }
    }
    
    for(i = 0; i <= MPL[k][0] + 1; i++) {
        mpl[i] = MPL[k][i];
    }
}
