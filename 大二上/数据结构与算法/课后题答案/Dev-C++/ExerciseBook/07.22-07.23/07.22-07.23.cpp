#include <stdio.h>
#include "Status.h"   //**��01 ����**//
#include "ALGraph.h"  //**��07 ͼ**//

// ���ʱ�־���飬��¼���ʹ��Ķ���
static Boolean visited[MAX_VERTEX_NUM];


/*
 * ͨ��������ȱ������������vi��vj֮���·��
 */
void Algo_7_22(ALGraph G, VertexType vi, VertexType vj);

/*
 * ������ȱ���ͼG�����Ҷ���i������j֮���·������path
 */
static Status DFS_7_22(ALGraph G, int i, int j, int path[MAX_VERTEX_NUM + 1]);

/*
 * ͨ��������ȱ������������vi��vj֮���·��
 */
void Algo_7_23(ALGraph G, VertexType vi, VertexType vj);

/*
 * ������ȱ���ͼG�����Ҷ���i������j֮���·������path
 */
static Status BFS_7_23(ALGraph G, int i, int j, int path[MAX_VERTEX_NUM + 1]);


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
    
    printf("���������������� ��7.22��ͨ��������ȱ����ж���������Ƿ����·��...\n");
    {
        VertexType vi = 'A';
        VertexType vj = 'F';
        
        Algo_7_22(G, vi, vj);
        printf("\n");
    }
    
    printf("���������������� ��7.23��ͨ��������ȱ����ж���������Ƿ����·��...\n");
    {
        VertexType vi = 'A';
        VertexType vj = 'F';
    
        Algo_7_23(G, vi, vj);
        printf("\n");
    }
    
    return 0;
}


/*
 * ͨ��������ȱ������ж϶���vi��vj֮���Ƿ����·��
 */
void Algo_7_22(ALGraph G, VertexType vi, VertexType vj) {
    int i, j, k;
    int path[MAX_VERTEX_NUM + 1];
    
    for(k = 0; k < G.vexnum; k++) {
        visited[k] = FALSE;
    }
    
    i = LocateVex(G, vi);
    j = LocateVex(G, vj);
    
    path[0] = 0;
    
    if(DFS_7_22(G, i, j, path) == ERROR) {
        printf("%c �� %c ֮�䲻����ͨ·��\n", vi, vj);
        return;
    }
    
    printf("%c �� %c ֮���ͨ·Ϊ��", vi, vj);
    for(k = 1; k <= path[0]; k++) {
        printf("%c ", GetVex(G, path[k]));
    }
    printf("\n");
}

/*
 * ������ȱ���ͼG�����Ҷ���i������j֮���·������path
 */
static Status DFS_7_22(ALGraph G, int i, int j, int path[MAX_VERTEX_NUM + 1]) {
    int w;
    
    // ������i����·��
    visited[i] = TRUE;
    path[0]++;
    path[path[0]] = i;
    
    if(i == j) {
        return OK;
    }
    
    // ����vi�����ڽӵ�
    for(w = FirstAdjVex(G, GetVex(G, i)); w >= 0; w = NextAdjVex(G, GetVex(G, i), GetVex(G, w))) {
        // �����ѷ��ʵĶ���
        if(visited[w]) {
            continue;
        }
        
        // �ݹ�(�������)
        if(DFS_7_22(G, w, j, path) == OK) {
            return OK;
        }
    }
    
    // �Ƴ�����i
    visited[i] = FALSE;
    path[0]--;
    
    return ERROR;
}

/*
 * ͨ��������ȱ������ж϶���vi��vj֮���Ƿ����·��
 */
void Algo_7_23(ALGraph G, VertexType vi, VertexType vj) {
    int i, j, k;
    int path[MAX_VERTEX_NUM + 1];
    
    for(k = 0; k < G.vexnum; k++) {
        visited[k] = FALSE;
    }
    
    i = LocateVex(G, vi);
    j = LocateVex(G, vj);
    
    path[0] = 0;
    
    if(BFS_7_23(G, i, j, path) == ERROR) {
        printf("%c �� %c ֮�䲻����ͨ·��\n", vi, vj);
        return;
    }
    
    printf("%c �� %c ֮���ͨ·Ϊ��", vi, vj);
    for(k = 1; k <= path[0]; k++) {
        printf("%c ", GetVex(G, path[k]));
    }
    printf("\n");
}

/*
 * ������ȱ���ͼG�����Ҷ���i������j֮���·������path
 */
static Status BFS_7_23(ALGraph G, int i, int j, int path[MAX_VERTEX_NUM + 1]) {
    int w;
    LinkQueue Q;
    QElemType e;
    
    // ������i����·��
    visited[i] = TRUE;
    path[0]++;
    path[path[0]] = i;
    
    if(i == j) {
        return OK;
    }
    
    // �ÿո�������
    InitQueue(&Q);
    
    // ����vi�����ڽӵ�
    for(w = FirstAdjVex(G, GetVex(G, i)); w >= 0; w = NextAdjVex(G, GetVex(G, i), GetVex(G, w))) {
        // �����ѷ��ʵĶ���
        if(visited[w]) {
            continue;
        }
        
        if(w == j) {
            // ������w����·��
            visited[w] = TRUE;
            path[0]++;
            path[path[0]] = w;
            return OK;
        }
        
        EnQueue(&Q, w);
    }
    
    // ���ڽӵ����������Ѱ��Ŀ��·��
    while(!QueueEmpty(Q)) {
        DeQueue(&Q, &e);
    
        // �ݹ�(�������)
        if(BFS_7_23(G, e, j, path) == OK) {
            return OK;
        }
    }
    
    // �Ƴ�����i
    visited[i] = FALSE;
    path[0]--;
    
    return ERROR;
}
