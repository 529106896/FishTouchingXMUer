/*=================================
 * ����7.33������������һ���������ṹ
 ==================================*/

#include "Graph.h"

// ¼�����ݵ�Դ�ļ���fpΪnullʱ��˵����Ҫ�ӿ���̨¼��
static FILE* fp = NULL;


/*
 * ����������
 *
 * pathΪNULL��Ϊ""ʱ���ӿ���̨��ȡͼ�ĳ�ʼ����Ϣ��
 * ���򣬴�Ԥ����ļ��ж�ȡͼ�ĳ�ʼ����Ϣ��
 */
Status CreateGraph(Graph* G, char* path) {
    int readFromConsole;    // �Ƿ�ӿ���̨��ȡ����
    
    // ���û���ļ�·����Ϣ����ӿ���̨��ȡ����
    readFromConsole = path == NULL || strcmp(path, "") == 0;
    
    // ��Ҫ���ļ���ȡ
    if(!readFromConsole) {
        // ���ļ���׼����ȡ��������
        fp = fopen(path, "r");
        if(fp == NULL) {
            return ERROR;
        }
    }
    
    Create(G);
    
    if(fp != NULL) {
        fclose(fp);
        fp = NULL;
    }
    
    return OK;
}

/*
 * �����������ĺ����㷨
 */
static void Create(Graph* G) {
    int u, v, k;
    VertexType v1, v2;
    int weight;
    
    // �ӿ���̨��ȡ
    if(fp == NULL) {
        printf("�������������Ķ�������");
        scanf("%d", &((*G).vexnum));
        printf("�������������ı�����");
        scanf("%d", &((*G).arcnum));
        
        // ¼�붥�㼯
        printf("��¼�� %d �����㣬��ͬ����֮���ÿո������", (*G).vexnum);
        for(k = 0; k < (*G).vexnum; k++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(stdin);
            scanf("%c", &((*G).vexs[k]));
        }
        
        // ���ļ���ȡ
    } else {
        ReadData(fp, "%d", &((*G).vexnum)); // ¼�붥����
        ReadData(fp, "%d", &((*G).arcnum)); // ¼�����
        
        // ¼�붥�㼯
        for(k = 0; k < (*G).vexnum; k++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(fp);
            ReadData(fp, "%c", &((*G).vexs[k]));
        }
    }
    
    // ���ڿ���̨¼����Ϣʱ�������ʾ
    if(fp == NULL && (*G).arcnum != 0) {
        printf("��Ϊ����������¼�� %d ���ߵ���Ϣ��������Ȩֵ֮���ÿո������\n", (*G).arcnum);
    }
    
    // ����߼��ṹ��0�ŵ�Ԫ�洢�ߵ�����
    (*G).EdgeSet = (EdgeSetType*) malloc(((*G).arcnum + 1) * sizeof(EdgeSetType));
    if((*G).EdgeSet == NULL) {
        exit(ERROR);
    }
    
    // EdgeSet��0�ŵ�Ԫ�洢���������бߵ�����
    (*G).EdgeSet[0].weight = (*G).arcnum;
    
    // ¼��ߵ���Ϣ
    for(k = 0; k < (*G).arcnum; k++) {
        if(fp == NULL) {
            printf("�� %2d ������Ȩֵ��", k + 1);
            skipBlank(stdin);   // �����հף�Ѱ����һ���ɶ�����
            scanf("%c", &v1);
            skipBlank(stdin);   // �����հף�Ѱ����һ���ɶ�����
            scanf("%c", &v2);
            skipBlank(stdin);   // �����հף�Ѱ����һ���ɶ�����
            scanf("%d", &weight);
        } else {
            // �����հף�Ѱ����һ���ɶ�����
            skipBlank(fp);
            ReadData(fp, "%c%c%d", &v1, &v2, &weight);
        }
        
        u = LocateVex(*G, v1);  // ��ȡ����v1�ڶ��㼯�е�λ��
        v = LocateVex(*G, v2);  // ��ȡ����v2�ڶ��㼯�е�λ��
        
        (*G).EdgeSet[k + 1].u = u;
        (*G).EdgeSet[k + 1].v = v;
        (*G).EdgeSet[k + 1].weight = weight;
    }
}

/*
 * ����
 *
 * ���ض���u���������е�λ��
 */
int LocateVex(Graph G, VertexType u) {
    int i;
    
    for(i = 0; i < G.vexnum; i++) {
        if(G.vexs[i] == u) {
            return i;
        }
    }
    
    return -1;
}

/*
 * �ӱ߼�EdgeSet�л�ȡ��С�ߵĶ���u��v��������TRUE��
 * ���߼�Ϊ�գ��򷵻�FASLE��
 */
Boolean GetMinEdge(EdgeSetType* EdgeSet, int* u, int* v) {
    int i, j, k;
    int min = INT_MAX;  // ��¼Ȩֵ�����ֵ
    
    // �߼�Ϊ��
    if(EdgeSet[0].weight == 0) {
        return FALSE;
    }
    
    // ����Ȩֵ��С�ı�
    for(k = 1; k <= EdgeSet[0].weight; k++) {
        if(EdgeSet[k].weight < min) {
            min = EdgeSet[k].weight;
            i = EdgeSet[k].u;
            j = EdgeSet[k].v;
        }
    }
    
    // ��¼������Ϣ
    *u = i;
    *v = j;
    
    return TRUE;
}

/*
 * �ӱ߼���ɾ�������ڶ���u��v����С�ߡ�
 * ɾ���ɹ�����TRUE�����򣬷���FALSE��
 */
Boolean DelMinEdge(EdgeSetType* EdgeSet, int u, int v) {
    int k;
    Boolean found = FALSE;  // �Ƿ��ҵ��˱�<u, v>
    
    // �߼�Ϊ��
    if(EdgeSet[0].weight == 0) {
        return FALSE;
    }
    
    // �Ȳ��Ҹ������ڱ߼��е�λ��
    for(k = 1; k <= EdgeSet[0].weight; k++) {
        if((EdgeSet[k].u == u && EdgeSet[k].v == v) || (EdgeSet[k].u == v && EdgeSet[k].v == u)) {
            found = TRUE;
            break;
        }
    }
    
    if(found == FALSE) {
        return FALSE;
    }
    
    // ������õ�ɾ����ʽ��ֱ�������һ���ߵ���Ϣ���Ǵ�ɾ���ߵ���Ϣ
    EdgeSet[k] = EdgeSet[EdgeSet[0].weight];
    EdgeSet[0].weight--;
    
    return TRUE;
}

/*
 * ��ӡ�������ṹ
 */
void PrintGraph(Graph G) {
    int i, j, k, w;
    int adjs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    
    if(G.vexnum == 0) {
        printf("��ͼ�������ӡ��\n");
        return;
    }
    
    // ��ʼ���ߵ���Ϣ
    for(i = 0; i < G.vexnum; i++) {
        for(j = 0; j < G.vexnum; j++) {
            adjs[i][j] = INFINITE;
        }
    }
    
    // ����߼�����
    for(k = 1; k <= G.EdgeSet[0].weight; k++) {
        i = G.EdgeSet[k].u;
        j = G.EdgeSet[k].v;
        w = G.EdgeSet[k].weight;
        
        adjs[i][j] = adjs[j][i] = w;
    }
    
    printf("��ǰ���������� %2d �����㣬 %2d ����...\n", G.vexnum, G.arcnum);
    
    printf("  ");
    for(i = 0; i < G.vexnum; i++) {
        printf("  %c", G.vexs[i]);
    }
    printf("\n");
    
    for(i = 0; i < G.vexnum; i++) {
        printf("%c ", G.vexs[i]);
        
        for(j = 0; j < G.vexnum; j++) {
            if(adjs[i][j] == INFINITE) {
                printf("  -");
            } else {
                printf("%3d", adjs[i][j]);
            }
        }
        
        printf("\n");
    }
}
