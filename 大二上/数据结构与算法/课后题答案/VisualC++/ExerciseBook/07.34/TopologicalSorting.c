/*=======================
 * AOV-��(����ͼ)����������
 *
 * �����㷨: 7.12
 ========================*/

#include "TopologicalSorting.h"

/*
 * ���������������� �㷨7.12 ����������������
 *
 * �������ͼG�޻�·�����������һ���������в�����OK�����򣬷���FALSE��
 * ��������ͨ����Ψһ�����Ǳ��뱣֤ĳЩ�ؼ��ڵ���Ⱥ����
 *
 * ע����̲Ĳ�֮ͬ�����ڣ��˴�������һ��topo������������
 * ��������������������У�����ֱ����������ǻỺ�浽topo�С�
 * ��������������Ŀ���Ǻ�����ϰ���л��жദ�õ����������С�
 */
Status TopologicalSort(ALGraph G, int topo[MAX_VERTEX_NUM]) {
    int i, k, count;
    int indegree[MAX_VERTEX_NUM];
    SqStack S;
    ArcNode* p;
    
    // �Ը����������
    FindInDegree(G, indegree);
    
    // ��ʼ������ȶ���ջ
    InitStack(&S);
    
    // �������Ϊ0�Ķ���ջ
    for(i = 0; i < G.vexnum; i++) {
        // �����Ϊ0�Ķ�����ӵ�ջ��
        if(indegree[i] == 0) {
            Push(&S, i);
        }
    }
    
    // �����������еĶ������
    count = 0;
    
    // ��������ջ
    while(!StackEmpty(S)) {
        // ��ȡһ������ȶ���
        Pop(&S, &i);
        
        // �������������ݴ�����
        topo[count++] = i;
        
        // ����i�Ŷ�����ڽӵ�
        for(p = G.vertices[i].firstarc; p != NULL; p = p->nextarc) {
            // ��ȡ�������
            k = p->adjvex;
    
            /*
             * ��i�Ŷ���ÿ���ڽӵ����ȼ�һ�����൱���ж�i�Ŷ��㵽�����ڽӵ����ϵ��
             * ����������µ����Ϊ0�Ķ��㣬����������ջ��
             */
            if((--indegree[k]) == 0) {
                Push(&S, k);
            }
        }
    }
    
    // ��������˻�·���򷵻�ERROR
    if(count < G.vexnum) {
        return ERROR;
    } else {
        return OK;
    }
}

/*
 * �������������
 */
static void FindInDegree(ALGraph G, int indegree[MAX_VERTEX_NUM]) {
    int i;
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
}
