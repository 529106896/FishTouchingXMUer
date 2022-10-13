#include <stdio.h>
#include "Status.h"     //**��01 ����**//
#include "MGraph.h"    //**��07 ͼ**//

// ���ʱ�־���飬��¼���ʹ��Ķ���
static Boolean visited[MAX_VERTEX_NUM];


/*
 * �������ͼG�г���Ϊk�ļ�·��
 */
void Algo_7_29(MGraph G, int k);

/*
 * ��������ͼG�г���Ϊk�ļ�·��
 */
void SimplePath_7_29(MGraph G, int start, int k, int path[MAX_VERTEX_NUM]);


int main(int argc, char* argv[]) {
    MGraph G;
    
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
    
    printf("���������������� ���Ҷ����ļ�·��...\n");
    {
        int k = 4;
        
        Algo_7_29(G, k);
        printf("\n");
    }
    
    return 0;
}


/*
 * �������ͼG�г���Ϊk�ļ�·��
 */
void Algo_7_29(MGraph G, int k) {
    int i;
    int path[MAX_VERTEX_NUM + 1]; // 0�ŵ�Ԫ������¼path�д洢�Ķ�������
    
    if(k <= 0) {
        printf("��������\n");
        return;
    }
    
    // �����ж�����Ϊδ����
    for(i = 0; i < G.vexnum; i++) {
        visited[i] = FALSE;
    }
    
    path[0] = 0;
    
    printf("�������г���Ϊ %d �ļ�·��...\n", k);
    
    for(i = 0; i < G.vexnum; i++) {
        SimplePath_7_29(G, i, k, path);
    }
    
}

/*
 * ��������ͼG�г���Ϊk�ļ�·��
 */
void SimplePath_7_29(MGraph G, int start, int k, int path[MAX_VERTEX_NUM]) {
    int i, w;
    
    path[0]++;
    path[path[0]] = start;
    visited[start] = TRUE;  // ��Ǹö����ѷ���
    
    // �����������Ϊk��·��(������ = ·������+1)���������
    if(path[0] == k + 1) {
        // ����ҵ��ļ�·��
        for(i = 1; i <= path[0]; i++) {
            printf("%c ", GetVex(G, path[i]));
        }
        printf("\n");
    } else {
        // ������ȱ���
        for(w = FirstAdjVex(G, G.vexs[start]);
            w >= 0;
            w = NextAdjVex(G, G.vexs[start], G.vexs[w])) {
            // �����ѷ��ʹ��Ķ���
            if(visited[w] == TRUE) {
                continue;
            }
            
            SimplePath_7_29(G, w, k, path);
        }
    }
    
    // ��·�����Ƴ��ö��㣬������״̬����Ϊ"�ѷ���"
    path[0]--;
    visited[start] = FALSE;  // ������ʱ��
}
