/*==================
 * ͼ���ڽӱ�洢��ʾ
 ===================*/

#include "ALGraph.h"

// ¼�����ݵ�Դ�ļ���fpΪnullʱ��˵����Ҫ�ӿ���̨¼��
static FILE* fp = NULL;

/*
 * IncInfoָʾ��ͼ/���ı�/�����Ƿ���ڸ�����Ϣ��
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
Status CreateGraph(ALGraph* G, char* path[]) {
    int readFromConsole;    // �Ƿ�ӿ���̨��ȡ����
    int kind;
    Status flag;
    
    // ����˴��̶�Ϊ����ͼ
    kind = 2;
    
    // ���û���ļ�·����Ϣ����ӿ���̨��ȡ����
    readFromConsole = (path == NULL) || strcmp(path[kind], "") == 0;
    
    // ��Ҫ���ļ���ȡ
    if(readFromConsole) {
        (*G).kind = kind;   // ��¼ͼ/��������
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
        case UDG:
            flag = CreateUDG(G);
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
 * ��������ͼ
 */
static Status CreateUDG(ALGraph* G) {
    int i, k;
    int vexnum, arcnum;
    VertexType v1, v2;
    InfoType* info = NULL;
    
    (*G).vexnum = (*G).arcnum = 0;
    
    if(fp == NULL) {
        printf("����������ͼ�Ķ�������");
        scanf("%d", &vexnum);
        printf("����������ͼ�ı�����");
        scanf("%d", &arcnum);
        printf("������ͼ�ı����Ƿ��������������Ϣ(0-��������1-����)��");
        scanf("%d", &IncInfo);
        
        // ¼�붥�㼯
        printf("��¼�� %d �����㣬��ͬ����֮���ÿո������", vexnum);
        for(i = 0; i < vexnum; i++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(stdin);
            scanf("%c", &((*G).vertices[i].data));
            (*G).vertices[i].firstarc = NULL;
            (*G).vexnum++;
        }
    } else {
        ReadData(fp, "%d", &vexnum); // ¼�붥����
        ReadData(fp, "%d", &arcnum); // ¼�����
        ReadData(fp, "%d", &IncInfo);// �жϱ����Ƿ����������Ϣ
        
        // ¼�붥�㼯
        for(i = 0; i < vexnum; i++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(fp);
            ReadData(fp, "%c", &((*G).vertices[i].data));
            (*G).vertices[i].firstarc = NULL;
            (*G).vexnum++;
        }
    }
    
    // ���ڿ���̨¼����Ϣʱ�������ʾ
    if(fp == NULL && arcnum != 0) {
        printf("��Ϊ����ͼ����¼�� %d ���ߵ���Ϣ������֮���ÿո������\n", arcnum);
    }
    
    // ¼��ߵ���Ϣ
    for(k = 0; k < arcnum; k++) {
        if(fp == NULL) {
            printf("�� %2d ���ߣ�", k + 1);
            skipBlank(stdin);   // �����հף�Ѱ����һ���ɶ�����
            scanf("%c", &v1);
            skipBlank(stdin);   // �����հף�Ѱ����һ���ɶ�����
            scanf("%c", &v2);
        } else {
            // �����հף�Ѱ����һ���ɶ�����
            skipBlank(fp);
            ReadData(fp, "%c%c", &v1, &v2);
        }
        
        // �����Ҫ¼��ߵ�����������Ϣ
        if(IncInfo) {
            // ���¼�븽����Ϣ
            Input(*G, &info);
            
        }
        
        // �����<v1, v2>
        InsertArc(G, v1, v2, info);
    }
    
    // ���ļ��ж�ȡ����ʱ�������ʵӦ���ж�һ���Ƿ�������㹻����Ϣ
    return OK;
}

/*
 * ¼���/������ظ�����Ϣ
 */
static void Input(ALGraph G, InfoType** info) {
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
int LocateVex(ALGraph G, VertexType u) {
    int i;
    
    for(i = 0; i < G.vexnum; i++) {
        if(G.vertices[i].data == u) {
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
VertexType GetVex(ALGraph G, int v) {
    if(v < 0 || v >= G.vexnum) {
        return '\0';    // ָ���Ķ��㲻����
    }
    
    return G.vertices[v].data;
}

/*
 * �׸��ڽӵ�
 *
 * ���ض���v���׸��ڽӵ�
 */
int FirstAdjVex(ALGraph G, VertexType v) {
    int k;
    ArcNode* r;
    
    // ������Ҫ�жϸö����Ƿ����
    k = LocateVex(G, v);
    if(k == -1) {
        return -1;    // ָ���Ķ��㲻����
    }
    
    r = G.vertices[k].firstarc;
    if(r == NULL) {
        return -1;
    } else {
        return r->adjvex;
    }
}

/*
 * ��һ���ڽӵ�
 *
 * ���ض���v��(�����w��)��һ���ڽӵ�
 */
int NextAdjVex(ALGraph G, VertexType v, VertexType w) {
    int kv, kw;
    ArcNode* r;
    
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
    
    r = G.vertices[kv].firstarc;
    if(r == NULL) {
        return -1;  // ����Ϊ��
    }
    
    // �������в���w
    while(r != NULL && r->adjvex < kw) {
        r = r->nextarc;
    }
    
    // ���û�ҵ�w
    if(r == NULL) {
        return -1;
    }
    
    // ����ҵ���w������w����û�б�Ķ��㣬��ôҲ�޷������ڽӵ�
    if(r->adjvex == kw && r->nextarc != NULL) {
        return r->nextarc->adjvex;
    }
    
    return -1;
}

/*
 * ����һ����/�����(�����ڲ�ʹ��)
 */
static ArcNode* newArcNodePtr(int adjvex, ArcNode* nextarc, InfoType* info) {
    ArcNode* p = (ArcNode*) malloc(sizeof(ArcNode));
    if(!p) {
        exit(OVERFLOW);
    }
    
    p->adjvex = adjvex;
    
    p->nextarc = nextarc;
    
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
Status InsertArc(ALGraph* G, VertexType v, VertexType w, ...) {
    int tail, head, k, count;
    ArcNode* r;
    ArcNode* pre;
    Boolean overlay = FALSE;    // �Ƿ�Ϊ�������
    InfoType* info = NULL;      // ��/���ĸ�����Ϣ
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
        pre = NULL;
        // ָ����tailΪβ��������/��
        r = G->vertices[tail].firstarc;
        while(r != NULL && r->adjvex < head) {
            pre = r;
            r = r->nextarc;
        }
        
        // ��������ͬλ�õĽ��
        if(r != NULL && r->adjvex == head) {
            r->info = info; // ���øý��
            overlay = TRUE; // �����˸���
        } else {
            if(pre == NULL) {
                G->vertices[tail].firstarc = newArcNodePtr(head, r, info);
            } else {
                pre->nextarc = newArcNodePtr(head, r, info);
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
 * ��ͼ�λ���ʽ�����ǰ�ṹ
 */
void PrintGraph(ALGraph G) {
    int i;
    ArcNode* p;
    
    if(G.vexnum == 0) {
        printf("��ͼ�������ӡ��\n");
        return;
    }
    
    printf("��ǰͼ/������ %2d �����㣬 %2d ����/��...\n", G.vexnum, G.arcnum);
    
    for(i = 0; i < G.vexnum; i++) {
        printf("%c ===> ", G.vertices[i].data);
        
        p = G.vertices[i].firstarc;
        while(p != NULL) {
            if(IncInfo == 0) {
                printf("%c ", G.vertices[p->adjvex].data);
                
                // ������������丽����Ϣ�л�ȡ��Ȩֵ
            } else {
                printf("%c[%2d] ", G.vertices[p->adjvex].data, p->info->weight);
            }
            
            p = p->nextarc;
            
            if(p != NULL) {
                printf("- ");
            }
        }
        
        printf("\n");
    }
}
