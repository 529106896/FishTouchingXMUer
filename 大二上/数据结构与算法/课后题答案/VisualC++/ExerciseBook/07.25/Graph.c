/*=================================
 * ����7.25������������һ������ͼ�ṹ
 ==================================*/

#include "Graph.h"

// ¼�����ݵ�Դ�ļ���fpΪnullʱ��˵����Ҫ�ӿ���̨¼��
static FILE* fp = NULL;


/*
 * ��������ͼ
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
 * ��������ͼ�ĺ����㷨
 */
static void Create(Graph* G) {
    int i, j, k;
    VertexType v1, v2;
    Boolean adjs[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = {FALSE};   // ��¼�ڽӵ���Ϣ
    int cur;
    
    // �ӿ���̨��ȡ
    if(fp == NULL) {
        printf("����������ͼ�Ķ�������");
        scanf("%d", &((*G).vexnum));
        printf("����������ͼ�Ļ�����");
        scanf("%d", &((*G).arcnum));
        
        // ¼�붥�㼯
        printf("��¼�� %d �����㣬��ͬ����֮���ÿո������", (*G).vexnum);
        for(i = 0; i < (*G).vexnum; i++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(stdin);
            scanf("%c", &((*G).vexs[i]));
        }
        
        // ���ļ���ȡ
    } else {
        ReadData(fp, "%d", &((*G).vexnum)); // ¼�붥����
        ReadData(fp, "%d", &((*G).arcnum)); // ¼�뻡��
        
        // ¼�붥�㼯
        for(i = 0; i < (*G).vexnum; i++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(fp);
            ReadData(fp, "%c", &((*G).vexs[i]));
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
        
        adjs[i][j] = TRUE;
    }
    
    cur = 0;
    
    // ��¼�ڽӵ���Ϣ
    for(i = 0; i < G->vexnum; i++) {
        G->fst[i] = -1;
        G->lst[i] = -2;
        
        for(j = 0; j < G->vexnum; j++) {
            if(adjs[i][j] == TRUE) {
                if(G->fst[i] == -1) {
                    G->fst[i] = cur;
                }
                
                G->s[cur++] = j;    // �洢��̶�����Ϣ
            }
        }
        
        if(G->fst[i] != -1) {
            G->lst[i] = cur - 1;
        }
    }
}

/*
 * ����
 *
 * ���ض���u������ͼ�е�λ��
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
 * ��ӡ����ͼ�ṹ
 */
void PrintGraph(Graph G) {
    int i, j;
    
    if(G.vexnum == 0) {
        printf("��ͼ�������ӡ��\n");
        return;
    }
    
    printf("��ǰ����ͼ���� %2d �����㣬 %2d ����...\n", G.vexnum, G.arcnum);
    
    for(i = 0; i < G.vexnum; i++) {
        printf("%c -> ", G.vexs[i]);
        for(j = G.fst[i]; j <= G.lst[i]; j++) {
            printf("%c ", G.vexs[G.s[j]]);
        }
        printf("\n");
    }
}
