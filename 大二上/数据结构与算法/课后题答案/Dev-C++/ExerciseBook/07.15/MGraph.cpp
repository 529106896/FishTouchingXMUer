/*=================================
 * ͼ������(�ڽӾ���)�洢��ʾ
 *
 * �����㷨: 7.1��7.2��7.4��7.5��7.6
 ==================================*/

#include "MGraph.h"     //**��07 ͼ**//

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
 * ���������������� �㷨7.1 ����������������
 *
 * ����ͼ/��
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
Status CreateGraph(MGraph* G, char* path[]) {
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
static Status CreateDG(MGraph* G) {
    int i, j, k;
    ArcCell arcs = {0, NULL};   // ����ͼÿ���ߵĳ�ʼֵ
    VertexType v1, v2;
    
    if(fp == NULL) {
        printf("����������ͼ�Ķ�������");
        scanf("%d", &((*G).vexnum));
        printf("����������ͼ�Ļ�����");
        scanf("%d", &((*G).arcnum));
        printf("������ͼ�Ļ����Ƿ��������������Ϣ(0-��������1-����)��");
        scanf("%d", &IncInfo);
        
        // ¼�붥�㼯
        printf("��¼�� %d �����㣬��ͬ����֮���ÿո������", (*G).vexnum);
        for(i = 0; i < (*G).vexnum; i++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(stdin);
            scanf("%c", &((*G).vexs[i]));
        }
    } else {
        ReadData(fp, "%d", &((*G).vexnum)); // ¼�붥����
        ReadData(fp, "%d", &((*G).arcnum)); // ¼�뻡��
        ReadData(fp, "%d", &IncInfo);       // �жϻ����Ƿ����������Ϣ
        
        // ¼�붥�㼯
        for(i = 0; i < (*G).vexnum; i++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(fp);
            ReadData(fp, "%c", &((*G).vexs[i]));
        }
    }
    
    // ��ʼ������ͼ���ڽӾ���
    for(i = 0; i < (*G).vexnum; i++) {
        for(j = 0; j < (*G).vexnum; j++) {
            (*G).arcs[i][j] = arcs;
        }
    }
    
    // ���ڿ���̨¼����Ϣʱ�������ʾ
    if(fp == NULL && (*G).arcnum != 0) {
        printf("��Ϊ����ͼ����¼�� %d ��������Ϣ������֮���ÿո������\n", (*G).arcnum);
    }
    
    // ¼�뻡����Ϣ
    for(k = 0; k < (*G).arcnum; k++) {
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
        
        i = LocateVex(*G, v1);  // ��ȡ����v1�ڶ��㼯�е�λ��
        j = LocateVex(*G, v2);  // ��ȡ����v2�ڶ��㼯�е�λ��
        
        // ��ָ���Ķ����ϵ����Ϊ1��ָʾ������������ֱ�����ӵ�(ע������û����֤�±��Ƿ�Խ��)
        (*G).arcs[i][j].adj = 1;
        
        // �����Ҫ¼�뻡������������Ϣ
        if(IncInfo) {
            // ���¼�븽����Ϣ
            Input(*G, &((*G).arcs[i][j].info));
        }
    }
    
    // ���ļ��ж�ȡ����ʱ�������ʵӦ���ж�һ���Ƿ�������㹻����Ϣ
    return OK;
}

/*
 * ����������
 */
static Status CreateDN(MGraph* G) {
    int i, j, k;
    ArcCell arcs = {INFINITE, NULL};    // ������ÿ�����ĳ�ʼֵ
    VertexType v1, v2;
    VRType w;
    
    if(fp == NULL) {
        printf("�������������Ķ�������");
        scanf("%d", &((*G).vexnum));
        printf("�������������Ļ�����");
        scanf("%d", &((*G).arcnum));
        printf("���������Ļ����Ƿ��������������Ϣ(0-��������1-����)��");
        scanf("%d", &IncInfo);
        
        // ¼�붥�㼯
        printf("��¼�� %d �����㣬��ͬ����֮���ÿո������", (*G).vexnum);
        for(i = 0; i < (*G).vexnum; i++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(stdin);
            scanf("%c", &((*G).vexs[i]));
        }
    } else {
        ReadData(fp, "%d", &((*G).vexnum)); // ¼�붥����
        ReadData(fp, "%d", &((*G).arcnum)); // ¼�뻡��
        ReadData(fp, "%d", &IncInfo);       // �жϻ����Ƿ����������Ϣ
        
        // ¼�붥�㼯
        for(i = 0; i < (*G).vexnum; i++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(fp);
            ReadData(fp, "%c", &((*G).vexs[i]));
        }
    }
    
    // ��ʼ�����������ڽӾ���
    for(i = 0; i < (*G).vexnum; i++) {
        for(j = 0; j < (*G).vexnum; j++) {
            (*G).arcs[i][j] = arcs;
        }
    }
    
    // ���ڿ���̨¼����Ϣʱ�������ʾ
    if(fp == NULL && (*G).arcnum != 0) {
        printf("��Ϊ����������¼�� %d ����(��Ȩֵ)����Ϣ�����㼰Ȩֵ֮���ÿո������\n", (*G).arcnum);
    }
    
    // ¼�뻡����Ϣ
    for(k = 0; k < (*G).arcnum; k++) {
        if(fp == NULL) {
            printf("�� %2d ��������Ȩֵ��", k + 1);
            skipBlank(stdin);   // �����հף�Ѱ����һ���ɶ�����
            scanf("%c", &v1);
            skipBlank(stdin);   // �����հף�Ѱ����һ���ɶ�����
            scanf("%c", &v2);
            scanf("%d", &w);
        } else {
            // �����հף�Ѱ����һ���ɶ�����
            skipBlank(fp);
            ReadData(fp, "%c%c%d", &v1, &v2, &w);
        }
        
        i = LocateVex(*G, v1);  // ��ȡ����v1�ڶ��㼯�е�λ��
        j = LocateVex(*G, v2);  // ��ȡ����v2�ڶ��㼯�е�λ��
        
        // ��ָ���Ķ����ϵ�ϼ�¼Ȩֵ(ע������û����֤�±��Ƿ�Խ��)
        (*G).arcs[i][j].adj = w;
        
        // �����Ҫ¼�뻡������������Ϣ
        if(IncInfo) {
            // ���¼�븽����Ϣ
            Input(*G, &((*G).arcs[i][j].info));
        }
    }
    
    // ���ļ��ж�ȡ����ʱ�������ʵӦ���ж�һ���Ƿ�������㹻����Ϣ
    return OK;
}

/*
 * ��������ͼ
 */
static Status CreateUDG(MGraph* G) {
    int i, j, k;
    ArcCell arcs = {0, NULL};   // ����ͼÿ���ߵĳ�ʼֵ
    VertexType v1, v2;
    
    if(fp == NULL) {
        printf("����������ͼ�Ķ�������");
        scanf("%d", &((*G).vexnum));
        printf("����������ͼ�ı�����");
        scanf("%d", &((*G).arcnum));
        printf("������ͼ�ı����Ƿ��������������Ϣ(0-��������1-����)��");
        scanf("%d", &IncInfo);
        
        // ¼�붥�㼯
        printf("��¼�� %d �����㣬��ͬ����֮���ÿո������", (*G).vexnum);
        for(i = 0; i < (*G).vexnum; i++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(stdin);
            scanf("%c", &((*G).vexs[i]));
        }
    } else {
        ReadData(fp, "%d", &((*G).vexnum)); // ¼�붥����
        ReadData(fp, "%d", &((*G).arcnum)); // ¼�����
        ReadData(fp, "%d", &IncInfo);       // �жϱ����Ƿ����������Ϣ
        
        // ¼�붥�㼯
        for(i = 0; i < (*G).vexnum; i++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(fp);
            ReadData(fp, "%c", &((*G).vexs[i]));
        }
    }
    
    // ��ʼ������ͼ���ڽӾ���
    for(i = 0; i < (*G).vexnum; i++) {
        for(j = 0; j < (*G).vexnum; j++) {
            (*G).arcs[i][j] = arcs;
        }
    }
    
    // ���ڿ���̨¼����Ϣʱ�������ʾ
    if(fp == NULL && (*G).arcnum != 0) {
        printf("��Ϊ����ͼ����¼�� %d ���ߵ���Ϣ������֮���ÿո������\n", (*G).arcnum);
    }
    
    // ¼��ߵ���Ϣ
    for(k = 0; k < (*G).arcnum; k++) {
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
        
        i = LocateVex(*G, v1);  // ��ȡ����v1�ڶ��㼯�е�λ��
        j = LocateVex(*G, v2);  // ��ȡ����v2�ڶ��㼯�е�λ��
        
        // ��ָ���Ķ����ϵ����Ϊ1��ָʾ������������ֱ�����ӵ�(ע������û����֤�±��Ƿ�Խ��)
        (*G).arcs[i][j].adj = 1;
        
        // �����Ҫ¼��ߵ�����������Ϣ
        if(IncInfo) {
            // ���¼�븽����Ϣ
            Input(*G, &((*G).arcs[i][j].info));
        }
        
        // ���ԳƵ�
        (*G).arcs[j][i] = (*G).arcs[i][j];
    }
    
    // ���ļ��ж�ȡ����ʱ�������ʵӦ���ж�һ���Ƿ�������㹻����Ϣ
    return OK;
}

/*
 * ���������������� �㷨7.2 ����������������
 *
 * ����������
 */
static Status CreateUDN(MGraph* G) {
    int i, j, k;
    ArcCell arcs = {INFINITE, NULL};    // ������ÿ���ߵĳ�ʼֵ
    VertexType v1, v2;
    VRType w;
    
    if(fp == NULL) {
        printf("�������������Ķ�������");
        scanf("%d", &((*G).vexnum));
        printf("�������������ı�����");
        scanf("%d", &((*G).arcnum));
        printf("���������ı����Ƿ��������������Ϣ(0-��������1-����)��");
        scanf("%d", &IncInfo);
        
        // ¼�붥�㼯
        printf("��¼�� %d �����㣬��ͬ����֮���ÿո������", (*G).vexnum);
        for(i = 0; i < (*G).vexnum; i++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(stdin);
            scanf("%c", &((*G).vexs[i]));
        }
    } else {
        ReadData(fp, "%d", &((*G).vexnum)); // ¼�붥����
        ReadData(fp, "%d", &((*G).arcnum)); // ¼�����
        ReadData(fp, "%d", &IncInfo);       // �жϱ����Ƿ����������Ϣ
        
        // ¼�붥�㼯
        for(i = 0; i < (*G).vexnum; i++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(fp);
            ReadData(fp, "%c", &((*G).vexs[i]));
        }
    }
    
    // ��ʼ�����������ڽӾ���
    for(i = 0; i < (*G).vexnum; i++) {
        for(j = 0; j < (*G).vexnum; j++) {
            (*G).arcs[i][j] = arcs;
        }
    }
    
    // ���ڿ���̨¼����Ϣʱ�������ʾ
    if(fp == NULL && (*G).arcnum != 0) {
        printf("��Ϊ����������¼�� %d ����(��Ȩֵ)����Ϣ�����㼰Ȩֵ֮���ÿո������\n", (*G).arcnum);
    }
    
    // ¼��ߵ���Ϣ
    for(k = 0; k < (*G).arcnum; k++) {
        if(fp == NULL) {
            printf("�� %2d ���߼���Ȩֵ��", k + 1);
            skipBlank(stdin);   // �����հף�Ѱ����һ���ɶ�����
            scanf("%c", &v1);
            skipBlank(stdin);   // �����հף�Ѱ����һ���ɶ�����
            scanf("%c", &v2);
            scanf("%d", &w);
        } else {
            // �����հף�Ѱ����һ���ɶ�����
            skipBlank(fp);
            ReadData(fp, "%c%c%d", &v1, &v2, &w);
        }
        
        i = LocateVex(*G, v1);  // ��ȡ����v1�ڶ��㼯�е�λ��
        j = LocateVex(*G, v2);  // ��ȡ����v2�ڶ��㼯�е�λ��
        
        // ��ָ���Ķ����ϵ�ϼ�¼Ȩֵ(ע������û����֤�±��Ƿ�Խ��)
        (*G).arcs[i][j].adj = w;
        
        // �����Ҫ¼��ߵ�����������Ϣ
        if(IncInfo) {
            // ���¼�븽����Ϣ
            Input(*G, &((*G).arcs[i][j].info));
        }
        
        // ���ԳƵ�
        (*G).arcs[j][i] = (*G).arcs[i][j];
    }
    
    // ���ļ��ж�ȡ����ʱ�������ʵӦ���ж�һ���Ƿ�������㹻����Ϣ
    return OK;
}

/*
 * ¼���/������ظ�����Ϣ
 */
static void Input(MGraph G, InfoType** info) {
    //¼���/������Ϣ���������漰���ı�/��Ĭ��������������Ϣ
}

/*
 * ����
 *
 * ���ض���u��ͼ/���е�λ��
 */
int LocateVex(MGraph G, VertexType u) {
    int i;
    
    for(i = 0; i < G.vexnum; i++) {
        if(G.vexs[i] == u) {
            return i;
        }
    }
    
    return -1;
}

/*
 * ���붥��
 *
 * ��ָ���Ķ���v׷�ӵ����㼯�У�δ�����ö�������������Ĺ�ϵ
 */
Status InsertVex(MGraph* G, VertexType v) {
    int i, k;
    VRType adj;
    
    // ����������
    if((*G).vexnum == MAX_VERTEX_NUM) {
        return ERROR;
    }
    
    // ������Ҫ�жϸö����Ƿ����
    k = LocateVex(*G, v);
    if(k >= 0) {
        return ERROR;    // ָ���Ķ������ʱ�������ظ����
    }
    
    // ȷ��һ������ͨ���
    if((*G).kind == DG || (*G).kind == UDG) {
        adj = 0;        // ͼ
    } else if((*G).kind == DN || (*G).kind == UDN) {
        adj = INFINITE; // ��
    } else {
        return ERROR;
    }
    
    (*G).vexs[(*G).vexnum] = v;
    (*G).vexnum++;
    
    for(i = 0; i < (*G).vexnum; i++) {
        (*G).arcs[i][(*G).vexnum - 1].adj = adj;
        (*G).arcs[(*G).vexnum - 1][i].adj = adj;
    }
    
    return OK;
}

/*
 * ɾ������
 *
 * �Ӷ��㼯��ɾ��ָ���Ķ���v��ע����Ҫ������صĶ����ϵ
 */
Status DeleteVex(MGraph* G, VertexType v) {
    int i, j, k;
    VRType adj;
    
    k = LocateVex(*G, v);
    if(k == -1) {
        return ERROR;    // ָ���Ķ��㲻����
    }
    
    // ȷ��һ������ͨ���
    if((*G).kind == DG || (*G).kind == UDG) {
        adj = 0;        // ͼ
    } else if((*G).kind == DN || (*G).kind == UDN) {
        adj = INFINITE; // ��
    } else {
        return ERROR;
    }
    
    // ���±�/��������
    for(i = 0; i < (*G).vexnum; i++) {
        // ������ڴӶ���v�����ıߣ���ߵ�������һ
        if((*G).arcs[k][i].adj != adj) {
            (*G).arcnum--;
        }
        
        // ������������ͼ/������Ȼ��Ҫ���±�/��������
        if((*G).kind == DG || (*G).kind == DN) {
            // ������ڵ��ﶥ��v�ıߣ���ߵ�������һ
            if((*G).arcs[i][k].adj != adj) {
                (*G).arcnum--;
            }
        }
    }
    
    // ���ڽӾ����еĶ����ϵ����
    for(j = k + 1; j < (*G).vexnum; j++) {
        for(i = 0; i < (*G).vexnum; i++) {
            (*G).arcs[i][j - 1] = (*G).arcs[i][j];    // �ұߵ���Ų����ߵ���
        }
    }
    
    // ���ڽӾ����еĶ����ϵ����
    for(i = k + 1; i < (*G).vexnum; i++) {
        // ע����������������ƵĹ�ϵ�����������j��С��(*G).vexnum - 1
        for(j = 0; j < (*G).vexnum - 1; j++) {
            (*G).arcs[i - 1][j] = (*G).arcs[i][j];    // ��һ��Ų����һ��
        }
    }
    
    // ���ö���Ӷ��㼯���Ƴ�
    for(i = k + 1; i < (*G).vexnum; i++) {
        (*G).vexs[i - 1] = (*G).vexs[i];
    }
    
    // ��������һ
    (*G).vexnum--;
    
    return OK;
}

/*
 * �����/��<v, w>
 *
 * �����ǰͼ/��������ģ������һ������Ҫ�������������ϵ������������ֻ��һ��
 *
 * ����ͼ��˵�������ڿɱ�������г���/���ĸ�����Ϣ��
 * ��������˵�������ڿɱ�����������г���/����Ȩֵ�Լ�������Ϣ��
 */
Status InsertArc(MGraph* G, VertexType v, VertexType w, ...) {
    int kv, kw;
    VRType adj;                 // �����ϵ
    Boolean overlay = FALSE;    // �Ƿ�Ϊ�������
    InfoType* info = NULL;      // ��/���ĸ�����Ϣ
    va_list ap;
    
    kv = LocateVex(*G, v);
    if(kv == -1) {
        return ERROR;    // ָ���Ķ��㲻����
    }
    
    kw = LocateVex(*G, w);
    if(kw == -1) {
        return ERROR;    // ָ���Ķ��㲻����
    }
    
    // �ܾ���
    if(kv == kw) {
        return ERROR;
    }
    
    /* ȷ��һ�������ϵ */
    
    // ����ͼ��˵����ͨ��ϵ��1��ʾ
    if((*G).kind == DG || (*G).kind == UDG) {
        adj = 1;
        
        // �����/���ϴ��ڸ�����Ϣ
        if(IncInfo) {
            va_start(ap, w);                // ��w���ѯ�׸��ɱ����
            info = va_arg(ap, InfoType*);   // ��ȡ������Ϣ
            va_end(ap);
        }
        
        overlay = (*G).arcs[kv][kw].adj != 0;
        
        // ��������˵���˴���Ҫ�ӿɱ�����л�ȡȨֵ��Ϣ
    } else if((*G).kind == DN || (*G).kind == UDN) {
        va_start(ap, w);    // ��w���ѯ�׸��ɱ����
        
        adj = va_arg(ap, VRType);   // ��ȡȨֵ��Ϣ
        
        // �����/���ϴ��ڸ�����Ϣ
        if(IncInfo) {
            info = va_arg(ap, InfoType*);   // ��ȡ������Ϣ
        }
        
        va_end(ap);
        
        overlay = (*G).arcs[kv][kw].adj != INFINITE;
    } else {
        return ERROR;
    }
    
    (*G).arcs[kv][kw].adj = adj;    // ��¼�����ϵ
    
    // �����/���ϴ��ڸ�����Ϣ�����¼���ӹ�ϵ
    if(IncInfo) {
        (*G).arcs[kv][kw].info = info;
    }
    
    // ���������ͼ/������Ҫ���ǶԳ���
    if((*G).kind == UDG || (*G).kind == UDN) {
        (*G).arcs[kw][kv] = (*G).arcs[kv][kw];
    }
    
    // �ڷǸ��ǵ������£��ſ��Ǹ��±�/��������
    if(!overlay) {
        (*G).arcnum++;  // �����������򣬱�/����ֻ��һ
    }
    
    return OK;
}

/*
 * ɾ����/��
 *
 * ��ɾ��ֻ�Ǹ��±�/������ͨ��ϵ
 */
Status DeleteArc(MGraph* G, VertexType v, VertexType w) {
    int kv, kw;
    VRType adj;
    Boolean found = FALSE;  // �Ƿ���ڴ�ɾ���ı�/��
    
    kv = LocateVex(*G, v);
    if(kv == -1) {
        return ERROR;    // ָ���Ķ��㲻����
    }
    
    kw = LocateVex(*G, w);
    if(kw == -1) {
        return ERROR;    // ָ���Ķ��㲻����
    }
    
    // ȷ��һ������ͨ���
    if((*G).kind == DG || (*G).kind == UDG) {
        adj = 0;        // ͼ
        
        found = (*G).arcs[kv][kw].adj != 0;
    } else if((*G).kind == DN || (*G).kind == UDN) {
        adj = INFINITE; // ��
        
        found = (*G).arcs[kv][kw].adj != INFINITE;
    } else {
        return ERROR;
    }
    
    // ��������������ѶϿ�����
    (*G).arcs[kv][kw].adj = adj;
    
    // ���������ͼ/������Ҫ���ǶԳ���
    if((*G).kind == UDG || (*G).kind == UDN) {
        (*G).arcs[kw][kv] = (*G).arcs[kv][kw];
    }
    
    // ���ҵ���ָ���Ļ�ʱ���ſ��Ǹ��±�/��������
    if(found) {
        (*G).arcnum--;  // �����������򣬱�/����ֻ��һ
    }
    
    return OK;
}

/*
 * ��ͼ�λ���ʽ�����ǰ�ṹ
 *
 * ע����ͼ/���У�ʹ��"-"����ʾ�����㲻ֱ����ͨ
 */
void PrintGraph(MGraph G) {
    int i, j;
    
    if(G.vexnum == 0) {
        printf("��ͼ�������ӡ��\n");
        return;
    }
    
    printf("��ǰͼ/������ %2d �����㣬 %2d ����/��...\n", G.vexnum, G.arcnum);
    
    printf("  ");
    for(i = 0; i < G.vexnum; i++) {
        printf("  %c", G.vexs[i]);
    }
    printf("\n");
    
    for(i = 0; i < G.vexnum; i++) {
        printf("%c ", G.vexs[i]);
        
        for(j = 0; j < G.vexnum; j++) {
            if(((G.kind == DG || G.kind == UDG) && G.arcs[i][j].adj == 0) || ((G.kind == DN || G.kind == UDN) && G.arcs[i][j].adj == INFINITE)) {
                printf("  -");
            } else {
                printf("%3d", G.arcs[i][j].adj);
            }
        }
        
        printf("\n");
    }
}
