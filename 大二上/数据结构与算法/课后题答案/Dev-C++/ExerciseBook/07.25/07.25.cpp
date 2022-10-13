#include <stdio.h>
#include "Graph.h"

// ���ʱ�־
typedef enum {
    UnVisited, // δ����
    Visited,   // �ѷ���
    InPath,    // ��·����
} FLAG;

// ���ʱ�־���飬��¼���ʹ��Ķ���
static FLAG flags[MAX_VERTEX_NUM];


/*
 * �ҳ�����ͼ�еĻ�·
 */
void Algo_7_25(Graph G);

/*
 * ��start���㿪ʼ���һ�·��
 *
 * path�����洢·���Ķ��㣬path[0]�洢path�еĶ���������
 *
 * ����ҵ���·�����ػ�·��ʼ�������ţ�
 * ���û�ҵ���·���򷵻�-1��
 */
int Circuit_7_25(Graph G, int start, int path[MAX_VERTEX_NUM + 1]);


int main(int argc, char* argv[]) {
    Graph G;
    
    printf("���������������� ���������ͼ...\n");
    {
        char* path = "TestData_DG.txt";
        
        CreateGraph(&G, path);
        PrintGraph(G);
        printf("\n");
    }
    
    printf("���������������� ����ͼ�еĻ�·...\n");
    {
        Algo_7_25(G);
        printf("\n");
    }
    
    return 0;
}


/*
 * �ҳ�����ͼ�еĻ�·
 */
void Algo_7_25(Graph G) {
    int i, w = -1;
    int path[MAX_VERTEX_NUM + 1]; // 0�ŵ�Ԫ������¼path�д洢�Ķ�������
    
    // �����ж�����Ϊδ����
    for(i = 0; i < G.vexnum; i++) {
        flags[i] = UnVisited;
    }
    
    path[0] = 0;
    
    for(i = 0; i < G.vexnum; i++) {
        w = Circuit_7_25(G, i, path);
        
        if(w != -1) {
            break;  // ����ҵ�������һ����·������ѭ��
        }
    }
    
    if(w == -1) {
        printf("����������ͼ�в����ڻ�·��\n");
        return;
    }
    
    printf("����ͼ���ҵ���������·Ϊ��");
    for(i = 1; path[i] != w; i++) {
        // Ѱ�һ�·���
    }
    // �ҵ��˻�·���
    if(path[i] == w) {
        while(i <= path[0]) {
            printf("%c -> ", G.vexs[path[i]]);
            i++;
        }
        printf("%c\n", G.vexs[w]);
    }
}

/*
 * ��start���㿪ʼ���һ�·��
 *
 * path�����洢·���Ķ��㣬path[0]�洢path�еĶ���������
 *
 * ����ҵ���·�����ػ�·��ʼ�������ţ�
 * ���û�ҵ���·���򷵻�-1��
 */
int Circuit_7_25(Graph G, int start, int path[MAX_VERTEX_NUM]) {
    int i;
    int v, w;
    
    path[0]++;
    path[path[0]] = start;
    flags[start] = InPath;  // ��Ǹö����ѽ���·��
    
    // ��������start���ڽӵ�
    for(i = G.fst[start]; i <= G.lst[start]; i++) {
        v = G.s[i]; // ��ȡ�ڽӵ����
        
        // �������������·���е��ڽӵ㣬˵�������˻�·
        if(flags[v] == InPath) {
            return v;
            
            // �����ѷ��ʵ��ڽӵ�
        } else if(flags[v] == Visited) {
            continue;
        } else {
            w = Circuit_7_25(G, v, path);
            if(w != -1) {
                return w;
            }
        }
    }
    
    // ��·�����Ƴ��ö��㣬������״̬����Ϊ"�ѷ���"
    path[0]--;
    flags[start] = Visited;
    
    return -1;
}
