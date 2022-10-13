#include <stdio.h>
#include "SqList.h"
#include "ALGraph.h"

/*
 * ��ȡ�洢�������޻�ͼ�еı��ʽ���沨��ʽ
 *
 * ע�����ʽ�ṹ�ο��̲Ĳ�ͼ7.23
 */
void Algo_7_38(ALGraph G);

/*
 * �Ӷ���v������ȡ����ͼ�д洢�ı��ʽ���沨��ʽ��
 * ��ȡ���沨��ʽ��洢��RPN�С�
 */
static void AntiPolandFormula_7_38(ALGraph G, int v, SqList* RPN);


int main(int argc, char* argv[]) {
    ALGraph G;
    
    printf("���������������� ��������ӡ������... \n");
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
    
    printf("���������������� ��ȡ�������д洢�ı��ʽ���沨��ʽ... \n");
    {
        Algo_7_38(G);
        printf("\n");
    }
    
    return 0;
}


/*
 * ��ȡ�洢�������޻�ͼ�еı��ʽ���沨��ʽ
 *
 * ע�����ʽ�ṹ�ο��̲Ĳ�ͼ7.23
 */
void Algo_7_38(ALGraph G) {
    int i, root;
    int indegree[MAX_VERTEX_NUM];   // ���ж���������Ϣ
    ArcNode* p;
    SqList RPN;  // �洢�沨�����ʽ
    ElemType e;
    
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
    
    // ���ҵ������
    for(i = 0; i < G.vexnum; i++) {
        if(indegree[i] == 0) {
            root = i;
            break;
        }
    }
    
    // ��ʼ������Ϊ0�����Ա�
    InitList(&RPN);
    
    // �������޻�ͼ�ĸ���������ͨ��β�ݹ��ȡ�����д洢�ı��ʽ���沨��ʽ
    AntiPolandFormula_7_38(G, root, &RPN);
    
    for(i = 1; i <= ListLength(RPN); i++) {
        GetElem(RPN, i, &e);
        printf("%c", ops[e]);
    }
    printf("\n");
}

/*
 * �Ӷ���v������ȡ����ͼ�д洢�ı��ʽ���沨��ʽ��
 * ��ȡ���沨��ʽ��洢��RPN�С�
 */
void AntiPolandFormula_7_38(ALGraph G, int v, SqList* RPN) {
    ArcNode* r;
    
    // �ȱ����ڽӵ�
    for(r = G.vertices[v].firstarc; r != NULL; r = r->nextarc) {
        AntiPolandFormula_7_38(G, r->adjvex, RPN);
    }
    
    // ��û���ڽӵ�ɱ���ʱ���洢�ö���
    ListInsert(RPN, ListLength(*RPN) + 1, v);
}
