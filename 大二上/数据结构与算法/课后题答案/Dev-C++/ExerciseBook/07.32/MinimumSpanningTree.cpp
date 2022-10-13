/*===================
 * ����������С����ɭ��
 ===================*/

#include "MinimumSpanningTree.h"

/*
 * ����ķ�㷨���õ��ĸ������飬
 * ������¼�Ӷ����Ӽ�U�������Ӽ�V-U�Ĵ�����С�ı�
 */
static struct {
    VertexType adjvex;      // �����Ӽ�U�еĶ���
    int lowcost;            // �����Ӽ�V-U����ǰ����adjvex�ıߵ�Ȩֵ
} closedge[MAX_VERTEX_NUM]; // ��������


/*
 * ʹ������ķ�㷨����������G����С����ɭ��
 */
CSTree MinSpanTree_PRIM(ALGraph G) {
    int i, j, k;
    ArcNode* p;
    CSTree r;
    CSTree T = NULL;
    CSTree curRoot = NULL;                  // ׷��ɭ���������ĸ����
    CSTree parent[MAX_VERTEX_NUM] = {NULL}; // ׷�ٸ�������ɭ���е�λ��(��ָ��ָ��ö���)
    
    // ���������ʼ������ʼ������ȨֵΪ0
    for(j=0; j<G.vexnum; j++) {
        closedge[j].lowcost = INT_MAX;
    }
    
    // �����0��ʼ��������Ϊһ��ʼ��δָ���ĸ�������Ϊ�׿����ĸ�
    for(i = 0; i < G.vexnum; i++) {
        // �Ӷ����Ӽ�V-U��ѡ����һ����ѡ�����Ա�������뵽��С������
        k = minimum(G);
    
        r = (CSTree) malloc(sizeof(CSNode));
        r->firstchild = r->nextsibling = NULL;
        
        // �������µ�����
        if(k==-1) {
            printf("----------\n");
            
            // ȷ��ɭ���������ĸ�
            for(k=0; k<G.vexnum; k++) {
                if(closedge[k].lowcost==INT_MAX) {
                    r->data = G.vertices[k].data;
                    parent[k] = r;
                    
                    if(curRoot==NULL) {
                        T = curRoot = r;
                    } else {
                        // ���ӵ�ɭ������һ����
                        curRoot->nextsibling = r;
                        curRoot = r;
                    }
                    
                    break;
                }
            }
        } else {
            r->data = G.vertices[k].data;
            
            // ��ȡ�������ͼ�е����
            j = LocateVex(G, closedge[k].adjvex);
            if(parent[j]->firstchild==NULL) {
                parent[j]->firstchild = r;
            } else {
                // ֱ�Ӳ���ͷ�巨����
                r->nextsibling = parent[j]->firstchild->nextsibling;
                parent[j]->firstchild->nextsibling = r;
            }
    
            parent[k] = r;
            
            // ��ӡ����ͱߵ���Ϣ
            printf("%c --%2d-- %c\n", closedge[k].adjvex, closedge[k].lowcost, G.vertices[k].data);
        }
        
        // ������k���뵽�����Ӽ�U
        closedge[k].lowcost = 0;
    
        // �¶�����붥���Ӽ�U����Ҫ���¶����Ӽ�U�붥���Ӽ�V-U�ıߵ���Ϣ
        for(p=G.vertices[k].firstarc; p!=NULL; p = p->nextarc) {
            j = p->adjvex;
    
            if(p->info->weight<closedge[j].lowcost) {
                closedge[j].adjvex = G.vertices[k].data;
                closedge[j].lowcost = p->info->weight;
            }
        }
    }
    
    return T;
}

/*
 * �Ӷ����Ӽ�V-U��ѡ����һ����ѡ�����Ա�������뵽��С������
 *
 * ѡ�񶥵��Ӽ�U�������Ӽ�V-U��Ȩֵ��С�ıߣ�
 * �����ظñ��ڶ����Ӽ�V-U����ͷ�Ķ˵㣬
 * �ö˵��������뵽�����Ӽ�U�У���Ϊ��С���������½�㡣
 */
static int minimum(ALGraph G) {
    int i, k = -1;
    int min = INT_MAX;
    
    // ��Ȩֵ��Ϊ0�ı���ѡ��ӵ����СȨֵ�ı�
    for(i = 0; i < G.vexnum; i++) {
        if(closedge[i].lowcost != 0 && closedge[i].lowcost < min) {
            min = closedge[i].lowcost;
            k = i;
        }
    }
    
    return k;
}
