#include <stdio.h>
#include "Status.h"
#include "MGraph.h"

// ���ʱ�־���飬��¼���ʹ��Ķ���
static Boolean visited[MAX_VERTEX_NUM];


/*
 * �ҳ�����ͼ�����л�·
 */
void Algo_7_30(MGraph G);

/*
 * ��ӡ����ͼ�����л�·
 */
void Circuit_7_30(MGraph G, int start, int end, int path[MAX_VERTEX_NUM + 1]);


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
    
    printf("���������������� ����ͼ�еĻ�·...\n");
    {
        Algo_7_30(G);
        printf("\n");
    }
    
    return 0;
}


/*
 * �ҳ�����ͼ�����л�·
 */
void Algo_7_30(MGraph G) {
    int i;
    int path[MAX_VERTEX_NUM + 1]; // 0�ŵ�Ԫ������¼path�д洢�Ķ�������
    
    // �����ж�����Ϊδ����
    for(i = 0; i < G.vexnum; i++) {
        visited[i] = FALSE;
    }
    
    path[0] = 0;
    
    for(i = 0; i < G.vexnum; i++) {
        Circuit_7_30(G, i, i, path);
    }
}

/*
 * ��ӡ����ͼ�����л�·
 */
void Circuit_7_30(MGraph G, int start, int end, int path[MAX_VERTEX_NUM]) {
    int i, w;
    
    path[0]++;
    path[path[0]] = start;
    visited[start] = TRUE;  // ��Ǹö����ѽ���·��
    
    // ��������start���ڽӵ�
    for(w = FirstAdjVex(G, G.vexs[start]); w >= 0; w = NextAdjVex(G, G.vexs[start], G.vexs[w])) {
        // �������������·���е��ڽӵ㣬˵�������˻�·
        if(visited[w] == TRUE) {
            if(w == end) {
                // �����·
                for(i = 1; i <= path[0]; i++) {
                    printf("%c -> ", GetVex(G, path[i]));
                }
                printf("%c\n", GetVex(G, w));
            }
            
        } else {
            // ɸ���ظ�·��
            if(w > end) {
                Circuit_7_30(G, w, end, path);
            }
        }
    }
    
    // ��·�����Ƴ��ö��㣬������״̬����Ϊ"�ѷ���"
    path[0]--;
    visited[start] = FALSE;
}
