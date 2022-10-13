#include <stdio.h>
#include "ALGraph.h"    //**��07 ͼ**//

/*
 * ���������޻�ͼ�ĸ��ڶ��������е���ţ���������ڣ�����-1��
 *
 * ע������������ڣ�����ζ�Ÿø��������һ��Ϊ0��
 * ������Ϊ���������Ȳ�Ϊ0����ô�ض����γɻ���
 * ������ˣ����Ȿ���Ͼ���Ѱ�������޻�ͼ�����Ϊ0���Ǹ����㡣
 */
int Algo_7_35(ALGraph G);


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
    
    printf("���������������� ���������޻�ͼ�ĸ�...\n");
    {
        int r = Algo_7_35(G);
        
        if(r == -1) {
            printf("����������ͼ�޻�ͼ�����ڸ�\n");
        } else {
            printf("�������޻�ͼ�ĸ�Ϊ��%c\n", G.vertices[r].data);
        }
        
        printf("\n");
    }
    
    return 0;
}


/*
 * ���������޻�ͼ�ĸ��ڶ��������е���ţ���������ڣ�����-1
 *
 * ע������������ڣ�����ζ�Ÿø��������һ��Ϊ0��
 * ������Ϊ���������Ȳ�Ϊ0����ô�ض����γɻ���
 * ������ˣ����Ȿ���Ͼ���Ѱ�������޻�ͼ�����Ϊ0���Ǹ����㡣
 */
int Algo_7_35(ALGraph G) {
    int i, count, root;
    int indegree[MAX_VERTEX_NUM];
    ArcNode* p;
    
    // ��ʼ�����ж�������Ϊ0
    for(i = 0; i < G.vexnum; i++) {
        indegree[i] = 0;
    }
    
    // �������ж���
    for(i = 0; i < G.vexnum; i++) {
        // ָ��ö�����׸��ڽӵ�
        p = G.vertices[i].firstarc;
        
        // �����ö���������ڽӵ㣬ͳ�Ƹ���������
        while(p != NULL) {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }
    
    // ͳ�����Ϊ0�Ķ�������
    count = 0;
    root = -1;
    
    for(i = 0; i < G.vexnum; i++) {
        if(indegree[i] == 0) {
            count++;
            root = i;
        }
    }
    
    // ���ֻ��һ����
    if(count==1) {
        return root;
    } else {
        return -1;
    }
}
