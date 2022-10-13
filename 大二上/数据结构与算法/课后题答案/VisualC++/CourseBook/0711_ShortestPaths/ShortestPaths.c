/*====================
 * ���·���㷨
 *
 * �����㷨: 7.15��7.16
 =====================*/

#include "ShortestPaths.h"

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
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix_DIJ P, ShortPathTable_DIJ D) {
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
        D[v] = G.arcs[v0][v].adj;
        
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
                 * Ϊ�˱����������Ҫȷ��G.arcs[v][w].adj��ΪINFINITE��
                 * �˴���ʵû��Ҫ�ж�min!=INFINITE����Ϊ���û�ҵ������Ķ���ʱ���������ǰ�����ˡ�
                 * (�̲ĵ�α����δ�������������Ҫ�������)
                 */
                if(min != INFINITE && G.arcs[v][w].adj != INFINITE) {
                    // ���¶��㼯S�����㼯V-S���������
                    if(!final[w] && (min + G.arcs[v][w].adj < D[w])) {
                        // ���¾��룺���ڶ���v0->w����v����ø��̵ľ��룬�ʴ˴���Ҫ���¸þ���
                        D[w] = min + G.arcs[v][w].adj;
                        
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
                if(!final[w] && G.arcs[v][w].adj != 0 && D[w] == 0) {
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
void PrintPath_DIJ(MGraph G, int v0, PathMatrix_DIJ P, ShortPathTable_DIJ D) {
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
 * ���������������� �㷨7.16 ����������������
 *
 * ��������(Floyd)�㷨���Դ���·��
 *
 * @param G  ��������ͼ��
 * @param P  �洢���Զ���֮������·����Ϣ��
 *           P[i][j][k]==TRUE�����i->j�����·���ᾭ������k�����򣬴���������
 *           ע��������ֻ��ӳ�˶���Ĵ����ԣ���δ��ӳ������·���ϵĴ���
 * @param D  �洢���Զ���֮������·�����ۣ���ͼ�У��ô����ǲ����ͣ������У��ô�����Ȩֵ�͡�
 */
void ShortestPath_FLOYD(MGraph G, PathMatrix_FLOYD P, ShortPathTable_FLOYD D) {
    int i, v, w, u;
    
    // �Ը�����֮���ʼ��֪·��������
    for(v = 0; v < G.vexnum; v++) {
        for(w = 0; w < G.vexnum; w++) {
            // ��ȡ<v,w>�ı�/����Ϣ
            D[v][w] = G.arcs[v][w].adj;
            
            // ��ʼ��·��v->wΪ��·��
            for(u = 0; u < G.vexnum; u++) {
                P[v][w][u] = FALSE;
            }
            
            // ���������ֻ�ߴ˷�֧(�̲�ֻ�����˴�������)
            if(G.kind == DN || G.kind == UDN) {
                // ���v0->vֱ����ͨ
                if(D[v][w] < INFINITE) {
                    P[v][w][v] = TRUE;  // ָʾv->w�ؽ���������v(�˵�һ)
                    P[v][w][w] = TRUE;  // ָʾv->w�ؽ���������w(�˵��)
                }
            }
            
            // �����ͼ��ֻ�ߴ˷�֧
            if(G.kind == DG || G.kind == UDG) {
                // ���v0->vֱ����ͨ
                if(D[v][w] != 0) {
                    P[v][w][v] = TRUE;  // ָʾv->w�ؽ���������v(�˵�һ)
                    P[v][w][w] = TRUE;  // ָʾv->w�ؽ���������w(�˵��)
                }
            }
        }
    }
    
    for(u = 0; u < G.vexnum; u++) {
        for(v = 0; v < G.vexnum; v++) {
            for(w = 0; w < G.vexnum; w++) {
                // ����ͬһ���㣬������Ϊ����ͨ
                if(v == w) {
                    continue;
                }
                
                // ���������ֻ�ߴ˷�֧(�̲�ֻ�����˴�������)
                if(G.kind == DN || G.kind == UDN) {
                    // ��Ҫ���ж�Ȩֵ��Ϣ����ֹ���
                    if(D[v][u] != INFINITE && D[u][w] != INFINITE) {
                        // ��v��u��w(v->u->w)��һ��·������
                        if(D[v][u] + D[u][w] < D[v][w]) {
                            // ����Ȩֵ
                            D[v][w] = D[v][u] + D[u][w];
                            
                            // ����·��
                            for(i = 0; i < G.vexnum; i++) {
                                P[v][w][i] = P[v][u][i] || P[u][w][i];
                            }
                        }
                    }
                }
                
                // �����ͼ��ֻ�ߴ˷�֧
                if(G.kind == DG || G.kind == UDG) {
                    // ��Ҫ���ж�������Ϣ
                    if(D[v][u] != 0 && D[u][w] != 0) {
                        // ��v��u��w(v->u->w)��һ��·������
                        if(D[v][w] == 0 || D[v][u] + D[u][w] < D[v][w]) {
                            // ����Ȩֵ
                            D[v][w] = D[v][u] + D[u][w];
                            
                            // ����·��
                            for(i = 0; i < G.vexnum; i++) {
                                P[v][w][i] = P[v][u][i] || P[u][w][i];
                            }
                        }
                    }
                }
            }
        }
    }
}

/*
 * ��ӡʹ�ø�������(Floyd)�㷨��ȡ�ĵ�Դ���·��
 */
void PrintPath_FLOYD(MGraph G, PathMatrix_FLOYD P, ShortPathTable_FLOYD D) {
    int i, j;
    
    // ��������·��
    for(i = 0; i < G.vexnum; i++) {
        for(j = 0; j < G.vexnum; j++) {
            if(P[i][j][i] == FALSE) {
                printf("%c �� %c ֮��û��ͨ·\n", GetVex(G, i), GetVex(G, j));
                continue;
            }
            
            printf("%c �� %c ֮�����̾���Ϊ%2d�������·��Ϊ��", GetVex(G, i), GetVex(G, j), D[i][j]);
            
            /*
             * ��i->j֮������򶥵����г�һ������·�����ӡ
             * P[i][j]ָʾi->j����·���Ͼ����Ķ���
             */
            PrintPath(G, i, j, P[i][j]);
        }
    }
}

/*
 * ��ӡ��a��b��·������·���Ķ�����Ϣλ��P��
 */
static void PrintPath(MGraph G, int a, int b, Boolean P[MAX_VERTEX_NUM]) {
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
static Status Find(MGraph G, int pre, int b, int vexs[MAX_VERTEX_NUM + 1], int path[MAX_VERTEX_NUM + 1]) {
    int i;
    int tmp;
    Status s;
    
    for(i = 1; i <= vexs[0]; i++) {
        // �Ѽ��뵽·��
        if(vexs[i] == -1) {
            continue;
        }
        
        // ����ͨ
        if(((G.kind == DN || G.kind == UDN) && G.arcs[pre][vexs[i]].adj == INFINITE)
        || ((G.kind == DG || G.kind == UDG) && G.arcs[pre][vexs[i]].adj == 0)) {
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
