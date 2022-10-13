/*====================
 * ͼ��ʮ������洢��ʾ
 *
 * �����㷨: 7.3
 ====================*/

#include "OLGraph.h"

// ¼�����ݵ�Դ�ļ���fpΪnullʱ��˵����Ҫ�ӿ���̨¼��
static FILE* fp = NULL;

/*
 * IncInfoָʾ��ͼ�ı����Ƿ���ڸ�����Ϣ��
 * �����ֵ��Ϊ0�����ʾ�޸�����Ϣ�����򣬱�ʾ���ڸ�����Ϣ��
 */
Boolean IncInfo = FALSE;

// ���ʱ�־���飬��¼���ʹ��Ķ���
static Boolean visited[MAX_VERTEX_NUM];

// ��������
static Status (* VisitFunc)(VertexType e);


/*
 * ����
 *
 *����ע��
 *
 * �̲���Ĭ�ϴӿ���̨��ȡ���ݡ�
 * ����Ϊ�˷�����ԣ�����ÿ�����ж��ֶ��������ݣ�
 * �������ѡ���Ԥ����ļ�path�ж�ȡ�������ݡ�
 *
 * �����Ҫ�ӿ���̨��ȡ���ݣ���pathΪNULL����path[kind]Ϊ""��
 * �����Ҫ���ļ��ж�ȡ���ݣ�����Ҫ��path����д�ļ�����Ϣ��
 */
Status CreateGraph(OLGraph* G, char* path[]) {
    int readFromConsole;    // �Ƿ�ӿ���̨��ȡ����
    int kind;
    Status flag;
    
    // ����˴��̶�Ϊ����ͼ
    kind = 0;
    
    // ���û���ļ�·����Ϣ����ӿ���̨��ȡ����
    readFromConsole = (path == NULL) || strcmp(path[kind], "") == 0;
    
    // ��Ҫ���ļ���ȡ
    if(readFromConsole) {
        // ע��C++�ļ��У�����תö����Ҫǿ��ת��
        (*G).kind = GraphKind(kind);   // ��¼ͼ/��������
    } else {
        // ���ļ���׼����ȡ��������
        fp = fopen(path[kind], "r");
        if(fp == NULL) {
            return ERROR;
        }
        
        // ¼��ͼ������
        ReadData(fp, "%d", &((*G).kind));
    }
    
    // �����������ͼ/��������ͼ/����һ��
    switch((*G).kind) {
        case DG:
            flag = CreateDG(G);
            break;
        default:
            flag = ERROR;
            break;
    }
    
    if(fp != NULL) {
        fclose(fp);
        fp = NULL;
    }
    
    return flag;
}

/*
 * ���������������� �㷨7.3 ����������������
 *
 * ��������ͼ
 *
 * ע��
 * �̲���ʹ����ͷ�巨�����뻡������������Ψһ�ŵ��ǲ��뷽�㣬
 * �������漰��ɾ�������ʱ��Ч�ʽϵͣ�
 * ���ң�"ͷ�巨"���������˳���������ı�/��������ģ�
 * �����չ������ͼ/���еı�/��Ҳ������ġ�
 *
 * Ϊ�˿˷�����ȱ�㣬�������"����"���뷨����֤����Ļ���"����"�ġ�
 * ��ͬʱ����������ʹ"����"�㷨��ý�Ϊ���ӡ�
 */
static Status CreateDG(OLGraph* G) {
    int i, k;
    int vexnum, arcnum;
    VertexType v1, v2;
    InfoType* info = NULL;
    
    (*G).vexnum = (*G).arcnum = 0;
    
    if(fp == NULL) {
        printf("����������ͼ�Ķ�������");
        scanf("%d", &vexnum);
        printf("����������ͼ�Ļ�����");
        scanf("%d", &arcnum);
        printf("������ͼ�Ļ����Ƿ��������������Ϣ(0-��������1-����)��");
        scanf("%d", &IncInfo);
        
        // ¼�붥�㼯
        printf("��¼�� %d �����㣬��ͬ����֮���ÿո������", vexnum);
        for(i = 0; i < vexnum; i++) {
            scanf("%c", &((*G).xlist[i].data));
            (*G).xlist[i].firstin = NULL;
            (*G).xlist[i].firstout = NULL;
            (*G).vexnum++;
        }
    } else {
        ReadData(fp, "%d", &vexnum);    // ¼�붥����
        ReadData(fp, "%d", &arcnum);    // ¼�뻡��
        ReadData(fp, "%d", &IncInfo);   // �жϻ����Ƿ����������Ϣ
        
        // ¼�붥�㼯
        for(i = 0; i < vexnum; i++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(fp);
            ReadData(fp, "%c", &((*G).xlist[i].data));
            (*G).xlist[i].firstin = NULL;
            (*G).xlist[i].firstout = NULL;
            (*G).vexnum++;
        }
    }
    
    // ���ڿ���̨¼����Ϣʱ�������ʾ
    if(fp == NULL && arcnum != 0) {
        printf("��Ϊ����ͼ����¼�� %d ��������Ϣ������֮���ÿո������\n", arcnum);
    }
    
    // ¼�뻡����Ϣ
    for(k = 0; k < arcnum; k++) {
        if(fp == NULL) {
            printf("�� %2d ������", k + 1);
            skipBlank(stdin);   // �����հף�Ѱ����һ���ɶ�����
            scanf("%c", &v1);
            skipBlank(stdin);   // �����հף�Ѱ����һ���ɶ�����
            scanf("%c", &v2);
        } else {
            // �����հף�Ѱ����һ���ɶ�����
            skipBlank(fp);
            ReadData(fp, "%c%c", &v1, &v2);
        }
        
        // �����Ҫ¼�뻡������������Ϣ
        if(IncInfo) {
            // ���¼�븽����Ϣ
            Input(*G, &info);
        }
        
        // ���뻡<v1, v2>
        InsertArc(G, v1, v2, info);
    }
    
    // ���ļ��ж�ȡ����ʱ�������ʵӦ���ж�һ���Ƿ�������㹻����Ϣ
    return OK;
}

/*
 * ¼�뻡����ظ�����Ϣ
 */
static void Input(OLGraph G, InfoType** info) {
    int weight;
    
    // ��"��"����������Ҫ¼��Ȩֵ��Ϣ
    if(G.kind == DN || G.kind == UDN) {
        *info = (InfoType*) malloc(sizeof(InfoType));
        
        if(fp == NULL) {
            scanf("%d", &weight);
        } else {
            ReadData(fp, "%d", &weight);
        }
        
        (*info)->weight = weight;
    }
}

/*
 * ����
 *
 * ���ض���u��ͼ/���е�λ��
 */
int LocateVex(OLGraph G, VertexType u) {
    int i;
    
    for(i = 0; i < G.vexnum; i++) {
        if(G.xlist[i].data == u) {
            return i;
        }
    }
    
    return -1;
}

/*
 * ȡֵ
 *
 * ��������v���Ķ���ֵ
 */
VertexType GetVex(OLGraph G, int v) {
    if(v < 0 || v >= G.vexnum) {
        return '\0';    // ָ���Ķ��㲻����
    }
    
    return G.xlist[v].data;
}

/*
 * �׸��ڽӵ�
 *
 * ���ض���v���׸��ڽӵ�
 */
int FirstAdjVex(OLGraph G, VertexType v) {
    int k;
    ArcBox* r;
    
    // ������Ҫ�жϸö����Ƿ����
    k = LocateVex(G, v);
    if(k == -1) {
        return -1;    // ָ���Ķ��㲻����
    }
    
    r = G.xlist[k].firstout;
    if(r == NULL) {
        return -1;
    } else {
        return r->headvex;
    }
}

/*
 * ��һ���ڽӵ�
 *
 * ���ض���v��(�����w��)��һ���ڽӵ�
 */
int NextAdjVex(OLGraph G, VertexType v, VertexType w) {
    int kv, kw;
    ArcBox* r;
    
    // ������Ҫ�жϸö����Ƿ����
    kv = LocateVex(G, v);
    if(kv == -1) {
        return -1;    // ָ���Ķ��㲻����
    }
    
    // ������Ҫ�жϸö����Ƿ����
    kw = LocateVex(G, w);
    if(kw == -1) {
        return -1;    // ָ���Ķ��㲻����
    }
    
    r = G.xlist[kv].firstout;
    if(r == NULL) {
        return -1;  // ����Ϊ��
    }
    
    // �������в���w
    while(r != NULL && r->headvex < kw) {
        r = r->tlink;
    }
    
    // ���û�ҵ�w
    if(r == NULL) {
        return -1;
    }
    
    // ����ҵ���w������w����û�б�Ķ��㣬��ôҲ�޷������ڽӵ�
    if(r->headvex == kw && r->tlink != NULL) {
        return r->tlink->headvex;
    }
    
    return -1;
}

/*
 * ����һ����/�����(�����ڲ�ʹ��)
 */
static ArcBox* newArcBoxPtr(int tailvex, int headvex, ArcBox* hlink, ArcBox* tlink, InfoType* info) {
    ArcBox* p = (ArcBox*) malloc(sizeof(ArcBox));
    if(!p) {
        exit(OVERFLOW);
    }
    
    p->tailvex = tailvex;
    p->headvex = headvex;
    
    p->hlink = hlink;
    p->tlink = tlink;
    
    p->info = info;
    
    return p;
}

/*
 * �����/��<v, w>
 *
 * �����ǰͼ/��������ģ������һ������Ҫ�������������ϵ������������ֻ��һ��
 * ����ͼ/����˵�������ڿɱ�������г���/���ĸ�����Ϣ��
 *
 * ע���˴����յĲ�����MGraph��Щ��һ�������ĸ�����Ϣ�а����˸�����/����Ȩֵ��
 */
Status InsertArc(OLGraph* G, VertexType v, VertexType w, ...) {
    int tail, head, k, count;
    ArcBox* p;
    ArcBox* pre;
    ArcBox* r;
    Boolean overlay = FALSE;   // �Ƿ�Ϊ�������
    InfoType* info = NULL;     // ��/���ĸ�����Ϣ
    va_list ap;
    
    tail = LocateVex(*G, v); // ��ȡ����v�ڶ��㼯�е�λ��
    if(tail == -1) {
        return ERROR;  // ָ���Ķ��㲻����
    }
    
    head = LocateVex(*G, w); // ��ȡ����w�ڶ��㼯�е�λ��
    if(head == -1) {
        return ERROR;  // ָ���Ķ��㲻����
    }
    
    // �ܾ���
    if(tail == head) {
        return ERROR;
    }
    
    // �����/���ϴ��ڸ�����Ϣ
    if(IncInfo) {
        va_start(ap, w);                // ��w���ѯ�׸��ɱ����
        info = va_arg(ap, InfoType*);   // ��ȡ������Ϣ
        va_end(ap);
    }
    
    /* ����������Ҫ���Һ��ʵĲ���λ�� */
    
    for(count = 0; count < 2; count++) {
        
        // �ں��������ϲ��Һ��ʵĲ���λ��
        pre = NULL;
        // ָ����tailΪβ��������/��
        r = G->xlist[tail].firstout;
        while(r != NULL && r->headvex < head) {
            pre = r;
            r = r->tlink;
        }
        
        // ��������ͬλ�õĽ��
        if(r != NULL && r->headvex == head) {
            r->info = info; // ���øý��
            overlay = TRUE; // �����˸���
        } else {
            p = newArcBoxPtr(tail, head, NULL, r, info);
            
            if(pre == NULL) {
                G->xlist[tail].firstout = p;
            } else {
                pre->tlink = p;
            }
        }
        
        // ���û�з������ǣ�˵���������½�㣬��ʱ��Ҫ�����������������ϵ�λ��
        if(overlay == FALSE) {
            // �����������ϲ��Һ��ʵĲ���λ��
            pre = NULL;
            // ָ����headΪͷ��������/��
            r = G->xlist[head].firstin;
            while(r != NULL && r->tailvex < tail) {
                pre = r;
                r = r->hlink;
            }
            
            // ��������ͬλ�õĽ��
            if(r != NULL && r->tailvex == tail) {
                // ����ִ�е������Ϊ��������˸��ǣ�ǰ�������
            } else {
                /* ���ˣ����p�Ѿ������� */
                
                if(pre == NULL) {
                    p->hlink = G->xlist[head].firstin;
                    G->xlist[head].firstin = p;
                } else {
                    p->hlink = pre->hlink;
                    pre->hlink = p;
                }
            }
        }
        
        // �����ǰͼ/��������ģ���Ҫ���ǶԳ���
        if((G->kind == UDG || G->kind == UDN) && tail != head) {
            // �ߵ�i��j
            k = tail;
            tail = head;
            head = k;
        } else {
            break;  // ���������ģ����Խ�����
        }
    }
    
    // �ڷǸ��ǵ������£��ſ��Ǹ��±�/��������
    if(!overlay) {
        (*G).arcnum++;  // �����������򣬱�/����ֻ��һ
    }
    
    return OK;
}

/*
 * ������ȱ���(�˴������ݹ�ʵ��)
 */
void DFSTraverse(OLGraph G, Status(Visit)(VertexType)) {
    int v;
    
    // ʹ��ȫ�ֱ���VisitFunc��ʹ��DFS�������ú���ָ�����
    VisitFunc = Visit;
    
    // ���ʱ�־�����ʼ��
    for(v = 0; v < G.vexnum; v++) {
        visited[v] = FALSE;
    }
    
    // �˴���Ҫ������ԭ���ǲ����ܱ�֤���ж��㶼��������һ��
    for(v = 0; v < G.vexnum; v++) {
        if(!visited[v]) {
            DFS(G, v);  // ����δ���ʵĶ������DFS
        }
    }
}

/*
 * ������ȱ������ĺ���
 */
static void DFS(OLGraph G, int v) {
    int w;
    
    // �ӵ�v����������ݹ��������ȱ���ͼG
    visited[v] = TRUE;
    
    // ���ʵ�v������
    VisitFunc(G.xlist[v].data);
    
    for(w = FirstAdjVex(G, G.xlist[v].data);
        w >= 0;
        w = NextAdjVex(G, G.xlist[v].data, G.xlist[w].data)) {
        if(!visited[w]) {
            DFS(G, w);  // ����δ���ʵĶ������DFS
        }
    }
}

/*
 * ��ͼ�λ���ʽ�����ǰ�ṹ
 */
void PrintGraph(OLGraph G) {
    int i, head;
    ArcBox* p;
    
    if(G.vexnum == 0) {
        printf("��ͼ�������ӡ��\n");
        return;
    }
    
    printf("��ǰͼ/������ %2d �����㣬 %2d ����/��...\n", G.vexnum, G.arcnum);
    
    for(i = 0; i < G.vexnum; i++) {
        printf("%c ===> ", G.xlist[i].data);
        
        head = 0;
        p = G.xlist[i].firstout;
        
        while(p != NULL) {
            if(head < p->headvex) {
                if(IncInfo == 0) {
                    printf("      ");
                    
                    // ������������丽����Ϣ�л�ȡ��Ȩֵ
                } else {
                    printf("          ");
                }
            } else {
                if(IncInfo == 0) {
                    printf("<%c, %c>", G.xlist[p->tailvex].data, G.xlist[p->headvex].data);
                    
                    // ������������丽����Ϣ�л�ȡ��Ȩֵ
                } else {
                    printf("<%c, %c, %2d>", G.xlist[p->tailvex].data, G.xlist[p->headvex].data, p->info->weight);
                }
                
                p = p->tlink;
            }
            
            head++;
            
            if(p != NULL) {
                printf("  ");
            }
        }
        
        printf("\n");
    }
}
