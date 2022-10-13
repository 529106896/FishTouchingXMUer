/*==================
 * ����ͼ��ǿ��ͨ����
 ===================*/

#include "StronglyConnectedComponents.h"


/* ȫ�ֱ��� */
static int count;      // �Է��ʹ��Ľ�����

// Kosaraju�㷨
static Boolean visited[MAX_VERTEX_NUM];    // ���ʱ�־���飬��¼���ʹ��Ķ���
static int finished[MAX_VERTEX_NUM];       // �洢������ȱ����з��ʵ���Ԫ��

// Tarjan�㷨
static int dfs[MAX_VERTEX_NUM];    // ������ȱ���ʱ���η��ʵ���Ԫ��(�����)
static int low[MAX_VERTEX_NUM];    // low[v]  ==> Ԫ��v���Ի��ݵ�����������
static int stack[MAX_VERTEX_NUM];  // �洢���������������Ľ��


/*
 * (1) Tarjan�㷨��ȡǿ��ͨ����
 *
 * ����˼����������ȱ���+���ݣ��뱾�µ�8����ؽڵ���㷨������֮��
 */
void Tarjan(OLGraph G) {
    int i;
    
    count = -1;  // ��ʼ������
    
    // ��ʼ������Ϊ��δ����
    for(i = 0; i < G.vexnum; i++) {
        dfs[i] = -1;
        low[i] = -1;
    }
    
    printf("��ӡ��ǰ����ͼ�еĸ���ǿ��ͨ������\n");
    
    for(i = 0; i < G.vexnum; i++) {
        if(dfs[i] == -1) {
            DFS_Tarjan(G, i);
        }
    }
}

/*
 * ������ȱ�������v�ɴ������Ԫ�أ��������ҳ����е�ǿ��ͨ����
 */
static void DFS_Tarjan(OLGraph G, int v) {
    int min;
    int w;
    int i;
    
    ++count;
    
    // ��¼���ʴ���
    dfs[v] = min = count;
    
    // ��¼�����Ľ��
    stack[count] = v;
    
    // ��ȱ���v��ʼ��ͼ
    for(w = FirstAdjVex(G, G.xlist[v].data); w >= 0; w = NextAdjVex(G, G.xlist[v].data, G.xlist[w].data)) {
        // ���w���δ����
        if(dfs[w] == -1) {
            DFS_Tarjan(G, w);  // ����δ���ʵĶ������DFS
            
            if(low[w] < min) {
                min = low[w];
            }
            
            // �����ѷ��ʹ��Ľ��
        } else {
            // ���w�ѱ����ʹ�����w��v���������ϵ�����
            if(dfs[w] < min) {
                min = dfs[w];
            }
        }
    }
    
    // ���"����"��㻹û��ȷ���������ȣ���ֻ��¼"����"����ϵķ��ʴ���
    if(low[stack[min]]==-1) {
        low[v] = min;
    } else {
        // ��ȡ"����"����ϵĿɻ�������
        low[v] = low[stack[min]];
    }
    
    // ��ȡ��ǰ����������ǿ��ͨ�Ӽ�
    if(low[v] == dfs[v]) {
        for(i = count; i >= 0; i--) {
            if(low[stack[i]] == dfs[v]) {
                printf("%c ", GetVex(G, stack[i]));
                count--;
            } else {
                break;
            }
        }
        printf("\n");
    }
}


/*
 * (2) Kosaraju�㷨��ȡǿ��ͨ���������ǽ̲����ᵽ���㷨
 *
 * ����˼���ǣ�
 * 1.��ĳ�����������ȱ�������ͼ���õ�һ���������У�
 * 2.��������ͼ��
 * 3.��������ó��ķ������У������е�ÿ���������������ȱ�����
 */
void Kosaraju(OLGraph G) {
    int i, v;
    
    count = 0;  // ��ʼ������
    
    // 1.��ĳ�����������ȱ�������ͼ���õ�һ����������
    DFSTraverse(G, StoreElem);
    
    // 2.��������ͼ
    InverseGraph(&G);
    
    // ���ʱ�־�����ʼ��
    for(i = 0; i < G.vexnum; i++) {
        visited[i] = FALSE;
    }
    
    printf("��ӡ��ǰ����ͼ�еĸ���ǿ��ͨ������\n");
    
    // 3.��������ó��ķ������У������е�ÿ���������������ȱ���
    for(i = 0; i < count; i++) {
        v = LocateVex(G, finished[i]);
        
        if(visited[v] == TRUE) {
            continue;
        }
        
        DFS_Inverse(G, v);
        printf("\n");
    }
}

/*
 * ��������ͼ��ʮ������洢�ṹ�����������л��ķ�������
 *
 * ����˼���ǣ�
 * 1.����һ���������κλ��Ŀ�ͼ��
 * 2.���α���ÿ�������ÿ���뻡��
 * 3.ժ���������뻡��������뵽��ͼ�б�ɳ�����
 */
static void InverseGraph(OLGraph* G) {
    OLGraph newG = *G;
    int i;
    ArcBox* r;
    ArcBox* pre, * p;
    int tmp;
    
    for(i = 0; i < newG.vexnum; i++) {
        newG.xlist[i].firstin = NULL;
        newG.xlist[i].firstout = NULL;
    }
    
    for(i = 0; i < (*G).vexnum; i++) {
        while((*G).xlist[i].firstin != NULL) {
            // ժ��������ָ�򶥵�i���뻡
            r = (*G).xlist[i].firstin;
            (*G).xlist[i].firstin = r->hlink;
            
            // ���û��ķ���
            tmp = r->headvex;
            r->headvex = r->tailvex;
            r->tailvex = tmp;
            
            r->hlink = NULL;
            r->tlink = NULL;
            
            // ���뵽��ͼ��������
            pre = newG.xlist[r->headvex].firstin;
            if(pre == NULL) {
                newG.xlist[r->headvex].firstin = r;
            } else {
                if(r->tailvex < pre->tailvex) {
                    r->hlink = newG.xlist[r->headvex].firstin;
                    newG.xlist[r->headvex].firstin = r;
                } else if(r->tailvex > pre->tailvex) {
                    p = pre->hlink;
                    
                    while(p != NULL && r->tailvex > p->tailvex) {
                        pre = p;
                        p = p->hlink;
                    }
                    
                    if(p == NULL || r->tailvex < p->tailvex) {
                        r->hlink = p;
                        pre->hlink = r;
                    }
                } else {
                    // ����ʱ������
                }
            }
            
            // ���뵽��ͼ�ĺ�����
            pre = newG.xlist[r->tailvex].firstout;
            if(pre == NULL) {
                newG.xlist[r->tailvex].firstout = r;
            } else {
                if(r->headvex < pre->headvex) {
                    r->tlink = newG.xlist[r->tailvex].firstout;
                    newG.xlist[r->tailvex].firstout = r;
                } else if(r->headvex > pre->headvex) {
                    p = pre->tlink;
                    
                    while(p != NULL && r->headvex > p->headvex) {
                        pre = p;
                        p = p->tlink;
                    }
                    
                    if(p == NULL || r->headvex < p->headvex) {
                        r->tlink = p;
                        pre->tlink = r;
                    }
                } else {
                    // ����ʱ������
                }
            }
        }
    }
    
    *G = newG;
}

/*
 * �洢������ȱ����з��ʵ���Ԫ��
 */
static Status StoreElem(VertexType c) {
    finished[count++] = c;
    return OK;
}

/*
 * ��ȱ����Ѿ����ú��ͼ
 */
static void DFS_Inverse(OLGraph G, int v) {
    int w;
    
    // ����ѷ��ʹ���ֱ�ӷ���
    if(visited[v] == TRUE) {
        return;
    }
    
    // �ӵ�v����������ݹ��������ȱ���ͼG
    visited[v] = TRUE;
    
    // ��ӡ���ʵ��Ķ���
    printf("%c ", GetVex(G, v));
    
    for(w = FirstAdjVex(G, G.xlist[v].data);
        w >= 0;
        w = NextAdjVex(G, G.xlist[v].data, G.xlist[w].data)) {
        DFS_Inverse(G, w);  // ����δ���ʵĶ������DFS
    }
}
