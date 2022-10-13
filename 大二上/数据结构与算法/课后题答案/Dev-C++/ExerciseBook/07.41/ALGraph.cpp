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
    
    // ����˴��̶�Ϊ������
    kind = 1;
    
    // ���û���ļ�·����Ϣ����ӿ���̨��ȡ����
    readFromConsole = (path == NULL) || strcmp(path[kind], "") == 0;
    
    // ��Ҫ���ļ���ȡ
    if(readFromConsole) {
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
        case DN:
            flag = CreateDN(G);
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
