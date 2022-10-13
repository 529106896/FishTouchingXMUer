#include <stdio.h>
#include "Status.h"     //**��01 ����**//
#include "ALGraph.h"    //**��07 ͼ**//

// ���ʱ�־���飬��¼���ʹ��Ķ���
static Boolean visited[MAX_VERTEX_NUM];


/*
 * ������������ļ�·��
 */
void Algo_7_27(ALGraph G, VertexType start, VertexType end, int k);

/*
 * �������������ļ�·����
 *
 * path�����洢·���Ķ��㣬path[0]�洢path�еĶ���������
 *
 * ����ҵ���·��������洢��path�У�������OK�����򣬷���ERROR��
 */
Status SimplePath_7_27(ALGraph G, int start, int end, int k, int path[MAX_VERTEX_NUM]);


int main(int argc, char* argv[]) {
    ALGraph G;
    
    printf("���������������� ���������ͼ...\n");
    {
        char* path[4];
        
        path[0] = "";
        path[1] = "";
        path[2] = "TestData_UDG.txt";
        path[3] = "";
        
        CreateGraph(&G, path);
        PrintGraph(G);
        printf("\n");
    }
    
    printf("���������������� ���Ҽ�·��...\n");
    {
        VertexType start = 'A';
        VertexType end = 'B';
        int k = 4;
        
        Algo_7_27(G, start, end, k);
        printf("\n");
    }
    
    return 0;
}


/*
 * ������������ļ�·��
 */
void Algo_7_27(ALGraph G, VertexType start, VertexType end, int k) {
    int i, m, n;
    int path[MAX_VERTEX_NUM + 1]; // 0�ŵ�Ԫ������¼path�д洢�Ķ�������
    Status s;
    
    m = LocateVex(G, start);
    n = LocateVex(G, end);
    
    if(k <= 0 || m == -1 || n == -1 || m == n) {
        printf("��������\n");
        return;
    }
    
    // �����ж�����Ϊδ����
    for(i = 0; i < G.vexnum; i++) {
        visited[i] = FALSE;
    }
    
    path[0] = 0;
    
    s = SimplePath_7_27(G, m, n, k, path);
    
    if(s == ERROR) {
        printf("δ�ҵ����������ļ�·����\n");
        return;
    }
    
    printf("%c �� %c ֮����ڵ�һ������Ϊ %d �ļ�·��Ϊ��", start, end, k);
    for(i = 1; i <= path[0]; i++) {
        printf("%c ", GetVex(G, path[i]));
    }
    printf("\n");
}

/*
 * �������������ļ�·����
 *
 * path�����洢·���Ķ��㣬path[0]�洢path�еĶ���������
 *
 * ����ҵ���·��������洢��path�У�������OK�����򣬷���ERROR��
 */
Status SimplePath_7_27(ALGraph G, int start, int end, int k, int path[MAX_VERTEX_NUM]) {
    int w;
    
    path[0]++;
    path[path[0]] = start;
    visited[start] = TRUE;  // ��Ǹö����ѷ���
    
    // ��������յ㣬����Ҫ�����η���
    if(start == end) {
        // ������ = ·������+1
        if(path[0] == k + 1) {
            return OK;
        }
    } else {
        // ������ȱ���
        for(w = FirstAdjVex(G, G.vertices[start].data);
            w >= 0;
            w = NextAdjVex(G, G.vertices[start].data, G.vertices[w].data)) {
            // �����ѷ��ʹ��Ķ���
            if(visited[w] == TRUE) {
                continue;
            }
            
            if(SimplePath_7_27(G, w, end, k, path) == OK) {
                return OK;
            }
        }
    }
    
    // ��·�����Ƴ��ö��㣬������״̬����Ϊ"�ѷ���"
    path[0]--;
    visited[start] = FALSE;  // ������ʱ��
    
    return ERROR;
}
