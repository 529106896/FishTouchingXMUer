/*==================
 * ����������С������
 *
 * �����㷨: 7.9
 ==================*/

#include "MinimumSpanningTree.h"

/*
 * ʹ�ÿ�³˹�����㷨��ȡ��С������
 */
CSTree MinSpanTree_KRUSKAL(Graph G) {
    int k;
    int v1, v2;
    int s1, s2;
    
    CSTree T = NULL;
    CSTree parent[MAX_VERTEX_NUM] = {NULL}; // ׷�ٸ����������е�λ��(��ָ��ָ��ö���)
    SqQueue queue;
    int root;
    
    // ��¼�Ѿ����뵽��С�������Ķ��㼯������ʹ�ü��ϵ�Ŀ���ǿ����жϺ�ѡ�����Ƿ����ɻ�·
    MFSet S;
    Relation relation;
    
    // �洢�������߼���һ������
    EdgeSetType* EdgeSet;
    
    // �洢��С�������а����ı߼�
    EdgeSetType* tree;
    EdgeSetType edge;
    
    // �����������ı߼�
    EdgeSet = (EdgeSetType*) malloc((G.EdgeSet[0].weight * sizeof(EdgeSetType)));
    for(k = 0; k <= G.EdgeSet[0].weight; k++) {
        EdgeSet[k] = G.EdgeSet[k];  // �ṹ�����ֱ�Ӹ���
    }
    
    // ��С�������а����ıߵ�����Ϊ������-1��������������һ����Ԫ����Ϊ0�ŵ�ԪҪ�洢�ߵ�����
    tree = (EdgeSetType*) malloc(G.vexnum * sizeof(EdgeSetType));
    tree[0].weight = 0;
    
    // ��ʼ�����㼯��
    initial_mfset(&S, G.vexnum);
    
    // �ӱ߼�������ѡ��Ȩֵ��С���Ҳ����ɻ�·�ı߼��뵽��С������
    for(k = 0; k < G.arcnum; k++) {
        // ѡ��һ��Ȩֵ��С�ı�
        GetMinEdge(EdgeSet, &v1, &v2);
        // ѡ��֮��Ϳ��Դӱ߼��ĸ�����ɾ���������ˣ���Ϊ����������Ҫ��
        DelMinEdge(EdgeSet, v1, v2);
        
        s1 = find_mfset(S, v1);
        s2 = find_mfset(S, v2);
        
        // ����������˵�λ��ͬһ�����ϣ�������������
        if(s1 == s2) {
            continue;
        }
        
        // �����Ԫ��ϵ
        relation.n = 1;
        relation.pairs[0].i = v1;
        relation.pairs[0].j = v2;
        
        build_mfset(&S, relation);
        
        // ��ӡ����ͱߵ���Ϣ
        printf("%c %c\n", G.vexs[v1], G.vexs[v2]);
        
        // ���������v1
        if(parent[v1] == NULL) {
            parent[v1] = (CSTree) malloc(sizeof(CSNode));
            parent[v1]->data = G.vexs[v1];
            parent[v1]->firstchild = parent[v1]->nextsibling = NULL;
        }
        
        // ���������v2
        if(parent[v2] == NULL) {
            parent[v2] = (CSTree) malloc(sizeof(CSNode));
            parent[v2]->data = G.vexs[v2];
            parent[v2]->firstchild = parent[v2]->nextsibling = NULL;
        }
        
        // �򼯺��д洢������С�������ı�
        tree[0].weight++;
        tree[tree[0].weight].u = v1;
        tree[tree[0].weight].v = v2;
    }
    
    
    /* ������ʹ����֪�ı����������ĺ���-�ֵ�����洢�ṹ */
    
    if(tree[0].weight<=0) {
        return NULL;
    }
    
    InitQueue(&queue);
    
    // ȷ���������ĸ����
    T = parent[tree[1].u];
    
    // ׷��ÿ�������ĸ����
    root = tree[1].u;
    
    while(tree[0].weight > 0) {
        // ���Ұ����˵�root�ı�
        for(k = 1; k <= tree[0].weight; k++) {
            if(tree[k].u == root || tree[k].v == root) {
                break;
            }
        }
        
        // �ҵ��������ı�
        if(k <= tree[0].weight) {
            edge = tree[k];
            
            // �Ƴ������ߣ��˴�ֻ�������һ���ߵ���Ϣ�򵥵ظ��������ߵ���Ϣ
            tree[k] = tree[tree[0].weight];
            tree[0].weight--;
            
            if(edge.u == root) {
                // �ѽ��v���Ϊ���u��һ�����ӽ�㣬����򵥵�ʹ��ͷ�巨
                parent[edge.v]->nextsibling = parent[edge.u]->firstchild;
                parent[edge.u]->firstchild = parent[edge.v];
                
                EnQueue(&queue, edge.v);
            } else {
                // �ѽ��u���Ϊ���v��һ�����ӽ�㣬����򵥵�ʹ��ͷ�巨
                parent[edge.u]->nextsibling = parent[edge.v]->firstchild;
                parent[edge.v]->firstchild = parent[edge.u];
    
                EnQueue(&queue, edge.u);
            }
        } else {
            // ��ȡ�µ�������root
            DeQueue(&queue, &root);
        }
    }
    
    return T;
}
