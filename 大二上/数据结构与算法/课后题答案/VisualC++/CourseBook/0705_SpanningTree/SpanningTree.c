/*==================
 * ����ͼ��������
 *
 * �����㷨: 7.7��7.8
 ===================*/

#include "SpanningTree.h"


// ���ʱ�־���飬��¼���ʹ��Ķ���
static Boolean visited[MAX_VERTEX_NUM];


/*
 * ���������������� �㷨7.7 ����������������
 *
 * ��������ͼ��������(ɭ��)
 */
void DFSForest(MGraph G, CSTree* T) {
    int v;
    CSTree p, q;
    
    InitTree(T);
    
    for(v = 0; v < G.vexnum; v++) {
        visited[v] = FALSE;
    }
    
    for(v = 0; v < G.vexnum; v++) {
        // �����ѷ��ʹ��Ķ���
        if(visited[v]) {
            continue;
        }
        
        p = (CSTree) malloc(sizeof(CSNode));    // ��������
        if(!p) {
            exit(OVERFLOW);
        }
        p->data = GetVex(G, v);
        p->firstchild = p->nextsibling = NULL;
    
        if(!(*T)) {                            // �ǵ�һ���������ĸ�
            *T = p;
        } else {                               // �������������ĸ���ǰһ���������ֵܣ�
            q->nextsibling = p;
        }
    
        q = p;                                 // qָʾ��ǰ�������ĸ�
        
        DFSTree(G, v, &p);                     // ������pΪ����������
    }
}

/*
 * ���������������� �㷨7.8 ����������������
 *
 * ͨ��������ȱ�������㣬������v��ʼ����
 */
void DFSTree(MGraph G, int v, CSTree* T) {
    Status first;
    int w;
    CSTree p, q;
    
    visited[v] = TRUE;
    first = TRUE;
    
    // forѭ�������������ҳ�v�������к���
    for(w = FirstAdjVex(G, G.vexs[v]); w>=0; w = NextAdjVex(G, G.vexs[v], G.vexs[w])) {
        // �����ѷ��ʹ��Ķ���
        if(visited[w]) {
            continue;
        }
    
        // ���캢�ӽ��
        p = (CSTree) malloc(sizeof(CSNode));
        if(!p) {
            exit(OVERFLOW);
        }
        p->data = GetVex(G, w);
        p->firstchild = p->nextsibling = NULL;
        
        // ����ǵ�һ������
        if(first) {
            (*T)->firstchild = p;
            first = FALSE;
            
            // ������ǵ�һ�����ӣ������Ϊ�ֵܽ��
        } else {
            q->nextsibling = p;
        }
        
        q = p;
        
        DFSTree(G, w, &q);
    }
}
