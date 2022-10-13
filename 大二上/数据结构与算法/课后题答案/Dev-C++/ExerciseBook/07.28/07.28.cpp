#include <stdio.h>
#include "Status.h"     //**��01 ����**//
#include "MGraph.h"    //**��07 ͼ**//

// ���ʱ�־���飬��¼���ʹ��Ķ���
static Boolean visited[MAX_VERTEX_NUM];


/*
 * ������������ļ�·��
 */
void Algo_7_28(MGraph G, VertexType start, VertexType end);

/*
 * ����start��end֮������еļ�·��
 */
void SimplePath_7_28(MGraph G, int start, int end, int path[MAX_VERTEX_NUM]);


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
    
    printf("���������������� ���Ҽ�·��...\n");
    {
        VertexType start = 'u';
        VertexType end = 'v';
        
        Algo_7_28(G, start, end);
        printf("\n");
    }
    
    return 0;
}


/*
 * ���start��end֮������еļ�·��
 */
void Algo_7_28(MGraph G, VertexType start, VertexType end) {
    int i, m, n;
    int path[MAX_VERTEX_NUM + 1]; // 0�ŵ�Ԫ������¼path�д洢�Ķ�������
    
    m = LocateVex(G, start);
    n = LocateVex(G, end);
    
    if(m == -1 || n == -1 || m == n) {
        printf("��������\n");
        return;
    }
    
    // �����ж�����Ϊδ����
    for(i = 0; i < G.vexnum; i++) {
        visited[i] = FALSE;
    }
    
    path[0] = 0;
    
    printf("���� %c �� %c ֮����ڵ����м�·��...\n", start, end);
    SimplePath_7_28(G, m, n, path);
}

/*
 * ����start��end֮������еļ�·��
 */
void SimplePath_7_28(MGraph G, int start, int end, int path[MAX_VERTEX_NUM]) {
    int i, w;
    
    path[0]++;
    path[path[0]] = start;
    visited[start] = TRUE;  // ��Ǹö����ѷ���
    
    // ����������������·�����������
    if(start == end) {
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
    
            SimplePath_7_28(G, w, end, path);
        }
    }
    
    // ��·�����Ƴ��ö��㣬������״̬����Ϊ"�ѷ���"
    path[0]--;
    visited[start] = FALSE;  // ������ʱ��
}
