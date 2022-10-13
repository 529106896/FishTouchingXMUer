/*==================
 * ����������С������
 *
 * �����㷨: 7.9
 ==================*/

#include "MinimumSpanningTree.h"


/*
 * ����ķ�㷨���õ��ĸ������飬
 * ������¼�Ӷ����Ӽ�U�������Ӽ�V-U�Ĵ�����С�ı�
 */
static struct {
    VertexType adjvex;      // �����Ӽ�U�еĶ���
    VRType lowcost;         // �����Ӽ�V-U����ǰ����ıߵ�Ȩֵ
} closedge[MAX_VERTEX_NUM]; // ��������


/*
 * ���������������� �㷨7.9 ����������������
 *
 * ����ķ�㷨
 *
 * �ӵ�u�������������������G����С������T�����T�ĸ����ߡ�
 * ���㷨�ĺ�ʱ�����ǶԶ���ı����������еı����޹أ���Ϊ�����ڱ߱Ƚϳ��ܵ���
 *
 * ע��Ԥ��ͼ��Ȩֵ������0���������
 */
void MinSpanTree_PRIM(MGraph G, VertexType u) {
    int i, j, k;
    
    // ���ض���u���������е�λ��
    k = LocateVex(G, u);
    
    // ���������ʼ����������u�����˶����Ӽ�U
    for(j = 0; j < G.vexnum; j++) {
        if(j != k) {
            closedge[j].adjvex = u;
            closedge[j].lowcost = G.arcs[k][j].adj;
        }
    }
    
    // ��ֵΪ0��ζ�Ŷ���k�ѽ��붥���Ӽ�U
    closedge[k].lowcost = 0;
    
    // ѡ������G.vexnum-1������
    for(i = 1; i < G.vexnum; i++) {
        // �Ӷ����Ӽ�V-U��ѡ����һ����ѡ�����Ա�������뵽��С������
        k = minimum(G);
        
        // ��ӡ����ͱߵ���Ϣ
        printf("%c --%d-- %c\n", closedge[k].adjvex, closedge[k].lowcost, G.vexs[k]);
        
        // ������k���뵽�����Ӽ�U
        closedge[k].lowcost = 0;
        
        // �¶�����붥���Ӽ�U����Ҫ���¶����Ӽ�U�붥���Ӽ�V-U�ıߵ���Ϣ
        for(j = 0; j < G.vexnum; j++) {
            if(G.arcs[k][j].adj < closedge[j].lowcost) {
                closedge[j].adjvex = G.vexs[k];
                closedge[j].lowcost = G.arcs[k][j].adj;
            }
        }
    }
}

/*
 * �Ӷ����Ӽ�V-U��ѡ����һ����ѡ�����Ա�������뵽��С������
 *
 * ѡ�񶥵��Ӽ�U�������Ӽ�V-U��Ȩֵ��С�ıߣ�
 * �����ظñ��ڶ����Ӽ�V-U����ͷ�Ķ˵㣬
 * �ö˵��������뵽�����Ӽ�U�У���Ϊ��С���������½�㡣
 *
 * ע���β���̲��и�����ģ��������ͬ
 */
static int minimum(MGraph G) {
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

/*
 * ��³˹�����㷨
 *
 * �ӵ�u�������������������G����С������T�����T�ĸ�����
 * ���㷨�ĺ�ʱ�����ǶԱߵı����������еĶ����޹أ���Ϊ�����ڱ߱Ƚ�ϡ�����
 *
 * ���ԸĽ�֮���������б�����ʱ���Բ��õ�9�½��ܵĶ�����
 */
void MinSpanTree_KRUSKAL(MGraph G) {
    int i, j, k;
    int s1, s2;
    
    // �߼�
    struct Edge {
        int v1;         // ����1���±�
        int v2;         // ����2���±�
        VRType adj;     // Ȩֵ
    } * edges, tmp;
    
    // ��¼�Ѿ����뵽��С�������Ķ��㼯������ʹ�ü��ϵ�Ŀ���ǿ����жϺ�ѡ�����Ƿ����ɻ�·
    MFSet S;
    Relation relation;

    // �߼����������Ǳߵ�����
    edges = (struct Edge*)malloc(G.arcnum* sizeof(struct Edge));

    // �Ա߼���
    k = 0;
    
    // ��ȡ���еı�
    for(i = 0; i < G.vexnum; i++) {
        // ������������ģ�����ֻ����һ��ı߾Ϳ���
        for(j = 0; j <= i; j++) {
            // ֻ����Ч�ı߽���ͳ��
            if(G.arcs[i][j].adj != INFINITE) {
                edges[k].v1 = i;
                edges[k].v2 = j;
                edges[k].adj = G.arcs[i][j].adj;
                k++;
            }
        }
    }
    
    // ����Ȩֵ��С����Ա߽�����������ֻ�Ǽ�ʹ����Ч�ʽϵ͵�ð������
    for(i = 0; i < G.arcnum - 1; i++) {
        for(j = 0; j < G.arcnum - i - 1; j++) {
            // ÿ�ֱ�������Ȩֵ�������Ų
            if(edges[j].adj > edges[j + 1].adj) {
                tmp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = tmp;
            }
        }
    }
    
    // ��ʼ�����㼯��
    initial_mfset(&S, G.vexnum);
    
    // �ӱ߼�������ѡ��Ȩֵ��С���Ҳ����ɻ�·�ı߼��뵽��С������
    for(i = 0; i < G.arcnum; i++) {
        s1 = find_mfset(S, edges[i].v1);
        s2 = find_mfset(S, edges[i].v2);

        // ����������˵�λ��ͬһ�����ϣ�������������
        if(s1 == s2) {
            continue;
        }
        
        // �����Ԫ��ϵ
        relation.n = 1;
        relation.pairs[0].i = edges[i].v1;
        relation.pairs[0].j = edges[i].v2;
        
        build_mfset(&S, relation);
        
        // ��ӡ����ͱߵ���Ϣ
        printf("%c --%d-- %c\n", GetVex(G, edges[i].v1), edges[i].adj, GetVex(G, edges[i].v2));
    }
}
