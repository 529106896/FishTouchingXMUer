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
    
    printf("������ͼ������(0-����ͼ �� 1-������ �� 2-����ͼ �� 3-������)��");
    scanf("%d", &kind);
    
    // ���Ͳ��Ϲ�
    if(kind < 0 || kind > 3) {
        return ERROR;
    }
    
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
        case DG:
            flag = CreateDG(G);
            break;
        case DN:
            flag = CreateDN(G);
            break;
        case UDG:
            flag = CreateUDG(G);
            break;
        case UDN:
            flag = CreateUDN(G);
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
static Status CreateDG(ALGraph* G) {
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
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(stdin);
            scanf("%c", &((*G).vertices[i].data));
            (*G).vertices[i].firstarc = NULL;
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
            ReadData(fp, "%c", &((*G).vertices[i].data));
            (*G).vertices[i].firstarc = NULL;
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
 * ����������
 */
static Status CreateDN(ALGraph* G) {
    int i, k;
    int vexnum, arcnum;
    VertexType v1, v2;
    InfoType* info = NULL;
    
    (*G).vexnum = (*G).arcnum = 0;
    
    if(fp == NULL) {
        printf("�������������Ķ�������");
        scanf("%d", &vexnum);
        printf("�������������Ļ�����");
        scanf("%d", &arcnum);
        printf("���������Ļ��ϱ����������������Ϣ����Ϊ�˴���Ȩֵ��Ҫ�洢��������Ϣ��...\n");
        IncInfo = 1;
    
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
        ReadData(fp, "%d", &arcnum); // ¼�뻡��
        ReadData(fp, "%d", &IncInfo);// �жϻ����Ƿ����������Ϣ(�˴�Ӧ������)
        IncInfo = 1;    // ǿ�ƽ�Ȩֵ¼�뵽������Ϣ��
        
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
        printf("��Ϊ����������¼�� %d ����(��Ȩֵ)����Ϣ�����㼰Ȩֵ֮���ÿո������\n", arcnum);
    }
    
    // ¼�뻡����Ϣ
    for(k = 0; k < arcnum; k++) {
        if(fp == NULL) {
            printf("�� %2d ��������Ȩֵ��", k + 1);
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
            // ���¼�븽����Ϣ(�˴���Ҫ¼������Ȩֵ)
            Input(*G, &info);
        }
        
        // ���뻡<v1, v2>
        InsertArc(G, v1, v2, info);
    }
    
    // ���ļ��ж�ȡ����ʱ�������ʵӦ���ж�һ���Ƿ�������㹻����Ϣ
    return OK;
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
 * ����������
 */
static Status CreateUDN(ALGraph* G) {
    int i, k;
    int vexnum, arcnum;
    VertexType v1, v2;
    InfoType* info = NULL;
    
    (*G).vexnum = (*G).arcnum = 0;
    
    if(fp == NULL) {
        printf("�������������Ķ�������");
        scanf("%d", &vexnum);
        printf("�������������ı�����");
        scanf("%d", &arcnum);
        printf("���������ı��ϱ����������������Ϣ����Ϊ�˴���Ȩֵ��Ҫ�洢��������Ϣ��...\n");
        IncInfo = 1;
    
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
        IncInfo = 1;    // ǿ�ƽ�Ȩֵ¼�뵽������Ϣ��
        
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
        printf("��Ϊ����������¼�� %d ����(��Ȩֵ)����Ϣ�����㼰Ȩֵ֮���ÿո������\n", arcnum);
    }
    
    // ¼��ߵ���Ϣ
    for(k = 0; k < arcnum; k++) {
        if(fp == NULL) {
            printf("�� %2d ���߼���Ȩֵ��", k + 1);
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
            // ���¼�븽����Ϣ(�˴���Ҫ¼������Ȩֵ)
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
 * �ڽӱ�洢��ͼ��Ҫ�ͷ��ڴ档
 */
Status DestroyGraph(ALGraph* G) {
    int k;
    ArcNode* pre, * r;
    
    for(k = 0; k < G->vexnum; k++) {
        r = G->vertices[k].firstarc;
        
        while(r != NULL) {
            pre = r;
            r = r->nextarc;
            free(pre);
        }
        
        G->vertices[k].firstarc = NULL;
    }
    
    (*G).vexnum = 0;
    (*G).arcnum = 0;
    IncInfo = 0;
    
    return OK;
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
 * ��ֵ
 *
 * ������v��ֵΪvalue
 */
Status PutVex(ALGraph* G, VertexType v, VertexType value) {
    int k;
    
    // ������Ҫ�жϸö����Ƿ����
    k = LocateVex((*G), v);
    if(k == -1) {
        return ERROR;    // ָ���Ķ��㲻����
    }
    
    // �滻ͷ���
    (*G).vertices[k].data = value;
    
    /* �����е�Ԫ�ش洢���Ƕ����λ�ã�������������������滻Ŀ��ֵ */
    
    return OK;
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
 * ���붥��
 *
 * ��ָ���Ķ���v׷�ӵ����㼯�У�δ�����ö�������������Ĺ�ϵ
 */
Status InsertVex(ALGraph* G, VertexType v) {
    int k;
    
    // ����������
    if((*G).vexnum == MAX_VERTEX_NUM) {
        return ERROR;
    }
    
    // ������Ҫ�жϸö����Ƿ����
    k = LocateVex(*G, v);
    if(k >= 0) {
        return ERROR;    // ָ���Ķ������ʱ�������ظ����
    }
    
    G->vertices[(*G).vexnum].data = v;
    G->vertices[(*G).vexnum].firstarc = NULL;
    
    (*G).vexnum++;
    
    return OK;
}

/*
 * ɾ������
 *
 * �Ӷ��㼯��ɾ��ָ���Ķ���v��ע����Ҫ������صĶ����ϵ
 */
Status DeleteVex(ALGraph* G, VertexType v) {
    int k, i;
    ArcNode* pre, * r;
    
    // ������Ҫ�жϸö����Ƿ����
    k = LocateVex(*G, v);
    if(k == -1) {
        return ERROR;    // ָ���Ķ��㲻����
    }
    
    // �ҵ��Խ��v�����������ͷŸ����������н��
    r = G->vertices[k].firstarc;
    while(r != NULL) {
        pre = r;
        r = r->nextarc;
        free(pre);
        
        (*G).arcnum--;
    }
    
    G->vertices[k].firstarc = NULL;
    
    // ����������������ɾ����Щָ�򶥵�v�Ļ������ң��±곬��k�Ķ��㣬���±�ֵ��Ҫ�ݼ�
    for(i = 0; i < G->vexnum; i++) {
        pre = NULL;
        r = G->vertices[i].firstarc;
        while(r != NULL && r->adjvex < k) {
            pre = r;
            r = r->nextarc;
        }
        
        // ���������ж�����±��С��k
        if(r == NULL) {
            continue;
        }
        
        if(r->adjvex == k) {
            // �ӿ�ͷɾ�����v
            if(pre == NULL) {
                G->vertices[i].firstarc = r->nextarc;
                
                // ���м�ĳ��λ��ɾ�����v
            } else {
                pre->nextarc = r->nextarc;
            }
            
            free(r);
            
            // ������������ͼ/������Ȼ��Ҫ�ݼ���/��������
            if((*G).kind == DG || (*G).kind == DN) {
                (*G).arcnum--;
            }
        }
        
        // �ٴ�ȷ��r��λ��
        if(pre == NULL) {
            r = G->vertices[i].firstarc;
        } else {
            r = pre->nextarc;
        }
        
        // �±곬��k�Ķ��㣬��Ҫ�ݼ����±�
        while(r != NULL && r->adjvex > k) {
            r->adjvex -= 1;
            r = r->nextarc;
        }
    }
    
    // ���㼯ǰ��
    for(i = k + 1; i < (*G).vexnum; i++) {
        G->vertices[i - 1] = G->vertices[i];
    }
    
    // �������ݼ�
    (*G).vexnum--;
    
    return OK;
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
 * ɾ����/��<v, w>
 */
Status DeleteArc(ALGraph* G, VertexType v, VertexType w) {
    int tail, head, k, count;
    ArcNode* r;
    ArcNode* pre;
    
    tail = LocateVex(*G, v);
    if(tail == -1) {
        return ERROR;    // ָ���Ķ��㲻����
    }
    
    head = LocateVex(*G, w);
    if(head == -1) {
        return ERROR;    // ָ���Ķ��㲻����
    }
    
    for(count = 0; count < 2; count++) {
        pre = NULL;
        // �ڵ�ǰ�������ҵ���ɾ���ı�/��
        r = G->vertices[tail].firstarc;
        while(r != NULL && r->adjvex < head) {
            pre = r;
            r = r->nextarc;
        }
        
        // �ҵ��˴�ɾ���ı�/��
        if(r != NULL && r->adjvex == head) {
            if(pre == NULL) {
                G->vertices[tail].firstarc = r->nextarc;
            } else {
                pre->nextarc = r->nextarc;
            }
            
            free(r);
        } else {
            return ERROR; // û�ҵ�
        }
        
        // �����ǰͼ/��������ģ���Ҫ���ǶԳ���
        if((G->kind == UDG || G->kind == UDN) && tail != head) {
            // �ߵ�tail��head
            k = tail;
            tail = head;
            head = k;
        } else {
            break;  // ���������ģ����Խ�����
        }
    }
    
    (*G).arcnum--;  // �����������򣬱�/����ֻ��һ
    
    return OK;
}

/*
 * ������ȱ���(�˴������ݹ�ʵ��)
 */
void DFSTraverse(ALGraph G, Status(Visit)(VertexType)) {
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
static void DFS(ALGraph G, int v) {
    int w;
    
    // �ӵ�v����������ݹ��������ȱ���ͼG
    visited[v] = TRUE;
    
    // ���ʵ�v������
    VisitFunc(G.vertices[v].data);
    
    for(w = FirstAdjVex(G, G.vertices[v].data);
        w >= 0;
        w = NextAdjVex(G, G.vertices[v].data, G.vertices[w].data)) {
        if(!visited[w]) {
            DFS(G, w);  // ����δ���ʵĶ������DFS
        }
    }
}

/*
 * ������ȱ���(�˴���������ʵ��)
 */
void BFSTraverse(ALGraph G, Status(Visit)(VertexType)) {
    int v, w;
    LinkQueue Q;
    QElemType u;
    
    // ��ʼ��Ϊδ����
    for(v = 0; v < G.vexnum; v++) {
        visited[v] = FALSE;
    }
    
    // �ÿո�������
    InitQueue(&Q);
    
    for(v = 0; v < G.vexnum; v++) {
        // ����ö����ѷ��ʹ�����ֱ�Ӻ���
        if(visited[v]) {
            continue;
        }
        
        // ��Ǹö����ѷ���
        visited[v] = TRUE;
        
        // ���ʶ���
        Visit(G.vertices[v].data);
        
        EnQueue(&Q, v);
        
        while(!QueueEmpty(Q)) {
            DeQueue(&Q, &u);
            
            // �ȼ��з��ʶ���v���ڽӶ��㣬����ٷ����ڽӶ�����ڽӶ���
            for(w = FirstAdjVex(G, G.vertices[u].data);
                w >= 0;
                w = NextAdjVex(G, G.vertices[u].data, G.vertices[w].data)) {
                if(!visited[w]) {
                    visited[w] = TRUE;
                    Visit(G.vertices[w].data);
                    EnQueue(&Q, w);
                }
            }
        }
    }
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
