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
 * ȡֵ
 *
 * ��������v���Ķ���ֵ
 */
VertexType GetVex(MGraph G, int v) {
    if(v < 0 || v >= G.vexnum) {
        return '\0';    // ָ���Ķ��㲻����
    }
    
    return G.vexs[v];
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
