/*====================
 * ���·���㷨
 *
 * �����㷨: 7.15��7.16
 =====================*/

#include "ShortestPaths.h"

/*
 * �洢���Զ���֮��Ĺ�ϵ��
 *
 * ����ͼ��˵���洢0��ʾ�����㲻ֱ����ͨ���洢1��ʾ������ֱ����ͨ��
 * ��������˵���洢���Ƕ���֮���Ȩֵ��ȨֵΪINFINITE��ʾ�����㲻ֱ����ͨ��
 */
static int adjs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];


/*
 * Ӧ����ִ�еϽ�˹�����㷨֮ǰ�����ã��������������֮��Ĺ�ϵ��
 */
void GetAdjs(ALGraph G) {
    int i, j;
    ArcNode* p;
    
    for(i = 0; i < G.vexnum; i++) {
        // ��ʼ�������ϵ
        for(j = 0; j < G.vexnum; j++) {
            // ���������ֻ�ߴ˷�֧
            if(G.kind == DN || G.kind == UDN) {
                adjs[i][j] = INFINITE;
            }
            
            // �����ͼ��ֻ�ߴ˷�֧
            if(G.kind == DG || G.kind == UDG) {
                adjs[i][j] = 0;
            }
        }
        
        // ����ֱ�����ӵĶ���
        for(p = G.vertices[i].firstarc; p != NULL; p = p->nextarc) {
            // ���������ֻ�ߴ˷�֧
            if(G.kind == DN || G.kind == UDN) {
                adjs[i][p->adjvex] = p->info->weight;
            }
            
            // �����ͼ��ֻ�ߴ˷�֧
            if(G.kind == DG || G.kind == UDG) {
                adjs[i][p->adjvex] = 1;
            }
        }
    }
}

/*
 * ���������������� �㷨7.15 ����������������
 *
 * �Ͻ�˹����(Dijkstra)�㷨��Դ���·��
 *
 * @param G  ��������ͼ��
 * @param v0 ��Դ���·������㡣
 * @param P  �洢��v0���������������·����Ϣ��
 *           P[j][k]==TRUE�����v0->j�����·���ᾭ������k�����򣬴���������
 *           ע��
 *           1.������ֻ��ӳ�˶���Ĵ����ԣ���δ��ӳ������·���ϵĴ���
 *           2.���������֮���ж������·����ֻ��ѡȡһ��
 * @param D  �洢��v0���������������·�����ۣ���ͼ�У��ô����ǲ����ͣ������У��ô�����Ȩֵ�͡�
 */
void ShortestPath_DIJ(ALGraph G, int v0, PathMatrix_DIJ P, ShortPathTable_DIJ D) {
    int v, w, i, j, min;
    Status final[MAX_VERTEX_NUM];   // ������ǵ�ǰ����Ƿ��Ѿ����ʹ������Ƿ��Ѽ������·��
    
    /*
     * Ԥ���ѷ��ʹ��Ķ��㼯ΪS��δ���ʹ��Ķ��㼯ΪV-S
     * ��ʼʱ�����㼯SΪ�գ������㼯V-SΪ���ж���ļ���V
     */
    for(v = 0; v < G.vexnum; v++) {
        // ��ʼʱ�����ж����δ���ʹ�
        final[v] = FALSE;
        
        // ��ʼ��v0->v��·������
        D[v] = adjs[v0][v];
        
        // Ԥ���v0->v����Ҫ��������w�������·��
        for(w = 0; w < G.vexnum; w++) {
            P[v][w] = FALSE;
        }
        
        // ���������ֻ�ߴ˷�֧(�̲�ֻ�����˴�������)
        if(G.kind == DN || G.kind == UDN) {
            // ���v0->vֱ����ͨ
            if(D[v] < INFINITE) {
                P[v][v0] = TRUE;    // ָʾv0->v�ؽ���������v0(�˵�һ)
                P[v][v] = TRUE;     // ָʾv0->v�ؽ���������v(�˵��)
            }
        }
        
        // �����ͼ��ֻ�ߴ˷�֧
        if(G.kind == DG || G.kind == UDG) {
            // ���v0��vֱ����ͨ
            if(D[v] != 0) {
                P[v][v0] = TRUE;    // ָʾv0->v�ؽ���������v0(�˵�һ)
                P[v][v] = TRUE;     // ָʾv0->v�ؽ���������v(�˵��)
            }
        }
    }
    
    // ��ʼ����v0���붥�㼯S
    D[v0] = 0;
    final[v0] = TRUE;
    
    /*
     * ��ʼ��ѭ������������G1.vexnum-1�����㡣
     * ÿ�����v0��ĳ����������·�����򽫸ö���Ӷ��㼯V-S��Ų�����㼯S��
     */
    for(i = 1; i < G.vexnum; i++) {
        /*
         * ÿ�ν���ѡȡ�������֮ǰ����Ӧ����v����Ϊһ�������������֮���ֵ
         * (�̲����޴˲��裬��Ҫ���ϣ��������кܶ����Ч��ѭ��)
         */
        v = -1;
        
        // ��¼�������붥��v0����̾���
        min = INFINITE;
        
        // �������㼯V-S(����δ����·���Ķ���)������ѡ������v0�����Ķ���
        for(w = 0; w < G.vexnum; w++) {
            // ���w������V-S��(δ�������·��)
            if(!final[w]) {
                // ����ͼ��˵������Ϊ0��ζ�������㲻��ͨ
                if((G.kind == DG || G.kind == UDG) && D[w] == 0) {
                    continue;
                }
                
                // ���v0��w�ľ���D[w]С�ڵ�ǰԤ�����С���룬����Ҫ���¶���;�����Ϣ
                if(D[w] < min) {
                    v = w;      // ����δ���ʵĶ����о���v0�����Ķ��㣬���߿������Ϊ���¶��㼯V-S�о��붥�㼯S�����Ķ���
                    min = D[w]; // ���¸����ľ���
                }
            }
        }
        
        // �ҵ��˸����Ķ���
        if(v != -1) {
            // �����㼯V-S�е�ǰ����v0���������v����S��
            final[v] = TRUE;
        } else {
            // ���û�ҵ������Ķ��㣬˵������v0��V-S�е�ʣ�ඥ��û�����ӣ���ʱ����ֱ�ӽ���������
            return;
        }
        
        // �������Ķ���v�����壬���¶���v0��V-S��������㶥������·��
        for(w = 0; w < G.vexnum; w++) {
            // ���������ֻ�ߴ˷�֧(�̲�ֻ�����˴�������)
            if(G.kind == DN || G.kind == UDN) {
                /*
                 * Ϊ�˱����������Ҫȷ��adjs[v][w]��ΪINFINITE��
                 * �˴���ʵû��Ҫ�ж�min!=INFINITE����Ϊ���û�ҵ������Ķ���ʱ���������ǰ�����ˡ�
                 * (�̲ĵ�α����δ�������������Ҫ�������)
                 */
                if(min != INFINITE && adjs[v][w] != INFINITE) {
                    // ���¶��㼯S�����㼯V-S���������
                    if(!final[w] && (min + adjs[v][w] < D[w])) {
                        // ���¾��룺���ڶ���v0->w����v����ø��̵ľ��룬�ʴ˴���Ҫ���¸þ���
                        D[w] = min + adjs[v][w];
                        
                        /* ����·����P[w] = P[v] + [w] */
                        
                        // �Ƚ�v0->w��·������Ϊv0->j��·��
                        for(j = 0; j < G.vexnum; j++) {
                            P[w][j] = P[v][j];
                        }
                        
                        // �ٽ�w��ӵ�v0->w��·����
                        P[w][w] = TRUE;
                    }
                }
            }
            
            // �����ͼ��ֻ�ߴ˷�֧
            if(G.kind == DG || G.kind == UDG) {
                // ���¶��㼯S�����㼯V-S���������
                if(!final[w] && adjs[v][w] != 0 && D[w] == 0) {
                    // ���¾��룺���ڶ���v0->w����v����ø��̵ľ��룬�ʴ˴���Ҫ���¸þ���
                    D[w] = D[v] + 1;    // ͼ�����ڶ��㲽��Ϊ1
                    
                    /* ����·����P[w] = P[v] + [w] */
                    
                    // �Ƚ�v0->w��·������Ϊv0->j��·��
                    for(j = 0; j < G.vexnum; j++) {
                        P[w][j] = P[v][j];
                    }
                    
                    // �ٽ�w��ӵ�v0->w��·����
                    P[w][w] = TRUE;
                }
            }
        }
    }
}

/*
 * ��ӡʹ�õϽ�˹����(Dijkstra)�㷨��ȡ�ĵ�Դ���·��
 */
void PrintPath_DIJ(ALGraph G, int v0, PathMatrix_DIJ P, ShortPathTable_DIJ D) {
    int j;
    
    // ��������·��
    for(j = 0; j < G.vexnum; j++) {
        if(P[j][v0] == FALSE) {
            printf("%c �� %c ֮��û��ͨ·\n", GetVex(G, v0), GetVex(G, j));
            continue;
        }
        
        printf("%c �� %c ֮�����̾���Ϊ%2d�������·��Ϊ��", GetVex(G, v0), GetVex(G, j), D[j]);
        
        /*
         * ��v0->j֮������򶥵����г�һ������·�����ӡ
         * P[i]ָʾv0->j����·���Ͼ����Ķ���
         */
        PrintPath(G, v0, j, P[j]);
    }
}

/*
 * ��ӡ��a��b��·������·���Ķ�����Ϣλ��P��
 */
static void PrintPath(ALGraph G, int a, int b, Boolean P[MAX_VERTEX_NUM]) {
    int i;
    int vexs[MAX_VERTEX_NUM + 1];
    int path[MAX_VERTEX_NUM + 1];
    
    vexs[0] = 0;
    
    // ��ȡv0->i����;���ϵ����ж��㣬�����������
    for(i = 0; i < G.vexnum; i++) {
        if(P[i] == TRUE) {
            vexs[0]++;
            vexs[vexs[0]] = i;
        }
    }
    
    // ֻ����������������¿��ٴ���
    if(vexs[0] == 2) {
        path[0] = 2;
        path[1] = a;
        path[2] = b;
        goto print;
    }
    
    // ֻ����������������¿��ٴ���
    if(vexs[0] == 3) {
        path[0] = 3;
        path[1] = a;
        for(i = 1; i <= vexs[0]; i++) {
            if(vexs[i] != a && vexs[i] != b) {
                path[2] = vexs[i];
                break;
            }
        }
        path[3] = b;
        goto print;
    }
    
    path[0] = 1;
    path[1] = a;
    
    for(i = 1; i <= vexs[0]; i++) {
        if(vexs[i] == a) {
            vexs[i] = -1;
            break;
        }
    }
    
    Find(G, a, b, vexs, path);

print:
    // ��ӡ���кõ�·��
    for(i = 1; i <= path[0]; i++) {
        printf("%c ", GetVex(G, path[i]));
    }
    
    printf("\n");
}

/*
 * ���ù��Ԥ�������ҵ�һ����pre��b��·������·����·�������ж���λ��vexs�У��ҳ���·���洢��path��
 */
static Status Find(ALGraph G, int pre, int b, int vexs[MAX_VERTEX_NUM + 1], int path[MAX_VERTEX_NUM + 1]) {
    int i;
    int tmp;
    Status s;
    
    for(i = 1; i <= vexs[0]; i++) {
        // �Ѽ��뵽·��
        if(vexs[i] == -1) {
            continue;
        }
        
        // ����ͨ
        if(((G.kind == DN || G.kind == UDN) && adjs[pre][vexs[i]] == INFINITE)
        || ((G.kind == DG || G.kind == UDG) && adjs[pre][vexs[i]] == 0)) {
            continue;
        }
        
        path[0]++;
        path[path[0]] = vexs[i];
        
        // �����յ�
        if(vexs[i] == b) {
            // �ҵ������·��
            if(path[0] == vexs[0]) {
                return OK;
            } else {
                path[0]--;
                continue;
            }
        }
        
        tmp = vexs[i];
        vexs[i] = -1;
        
        s = Find(G, tmp, b, vexs, path);
        
        if(s == OK) {
            return OK;
        } else {
            // �ָ��ö��㣬�Ա������������
            vexs[i] = tmp;
            path[0]--;
        }
    }
    
    return ERROR;
}
