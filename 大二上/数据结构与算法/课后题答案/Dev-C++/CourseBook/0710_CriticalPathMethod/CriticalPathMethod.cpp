/*=======================
 * AOE-��(������)�Ĺؼ�·��
 *
 * �����㷨: 7.13��7.14
 ========================*/

#include "CriticalPathMethod.h"

/* ȫ�ֱ��� */
static int ve[MAX_VERTEX_NUM];  // ���¼������㣩�����緢��ʱ��(Խ��Խ��)
static int vl[MAX_VERTEX_NUM];  // ���¼������㣩��������ʱ��(Խ��Խ��)

/*
 * ���������������� �㷨7.14 ����������������
 *
 * ����������G�Ĺؼ�·��
 *
 * ע���������������������һ���������Ϊ�¼��յ�
 */
Status CriticalPath(ALGraph G) {
    int i, j, k;
    ArcNode* p;
    SqStack T;  // �������ж���ջ
    int dut;    // �����ʱ��
    int ee, el;
    char tag;
    int count;
    
    int path[MAX_VERTEX_NUM];           // �洢�������У���T�д洢����Ϣһ��
    Boolean P[MAX_VERTEX_NUM]= {FALSE}; // �洢�ؼ�·����Ϣ��ֻ��Ϊ������չʾ
    
    // ������������ڻ�·�����޷��������������У�����Ҳ�޷��ó����������Ĺؼ�·��
    if(!TopologicalOrder(G, &T)) {
        printf("�쳣�˳����������������д��ڻ�·�����޷�������������������...\n");
        return ERROR;
    } else {
        printf("���������������й����ɹ�...\n");
        // �����������е�path���Ա�������
        for(i=0; i<StackLength(T); i++) {
            path[i] = T.base[i];
        }
    }
    
    // ��ʼ�����¼���������ʱ��Ϊ�����¼���������ֵ��Ǹ����緢��ʱ��(�������������һ���¼������緢��ʱ��)
    for(i = 0; i < G.vexnum; i++) {
        vl[i] = ve[G.vexnum-1]; // ve[G.vexnum-1]�����յ�����緢��ʱ��
    }
    
    // ��������������ж���ջ(��ջ�ж����ջ���ɴﵽ�����Ŀ��)
    while(!StackEmpty(T)) {
        // ��ȡһ������
        Pop(&T, &j);
        
        // ����j������ڽӵ�
        for(p = G.vertices[j].firstarc; p != NULL; p = p->nextarc) {
            k = p->adjvex;              // ����j���ڽӵ����
            dut = (*(p->info)).weight;  // j->k��Ȩֵ�����¼�j->k�ĳ���ʱ��
            
            // ���¼�j��������ʱ����ǰ
            if(vl[k] - dut < vl[j]) {
                vl[j] = vl[k] - dut;
            }
        }
    }
    
    count = 0;
    
    printf("�����������Ĺؼ�·����Ϣ...\n");
    
    // �������ж���
    for(j = 0; j < G.vexnum; j++) {
        // ����j������ڽӵ�
        for(p = G.vertices[j].firstarc; p != NULL; p = p->nextarc) {
            k = p->adjvex;
            dut = (*(p->info)).weight;
            
            ee = ve[j];         // �¼�j�����緢��ʱ��
            el = vl[k] - dut;   // �¼�j��������ʱ��
            
            // ��*��ǹؼ�·��
            tag = (ee == el) ? '*' : ' ';
            
            printf("%c-%c  a%-2d=%2d  (%2d, %2d)  %c\n", G.vertices[j].data, G.vertices[k].data, count++, dut, ee, el, tag);
    
            // ��¼��Щ������뵽�˹ؼ�·����
            if(tag=='*') {
                P[j] = TRUE;
                P[k] = TRUE;
            }
        }
    }
    
    
    /*
     * ע���̲���û�к�������
     * �˴�������Щ������Ϊ�˸�ֱ�۵���ʾ�ؼ�·����Ϣ
     */
    printf("\n");
    printf("��ǰ�������Ĺؼ�·��Ϊ��");
    for(i = 0; i < G.vexnum; i++) {
        if(P[path[i]] == TRUE) {
            printf("%c ", G.vertices[path[i]].data);
        }
    }
    printf("\n");
    
    return OK;
}

/*
 * ���������������� �㷨7.13 ����������������
 *
 * ���������G�޻�·����Ѱ������һ���������д洢����������ջT�У�������OK�����򣬷���FALSE��
 * ��������ͨ����Ψһ�����Ǳ��뱣֤ĳЩ�ؼ��ڵ���Ⱥ����
 */
static Status TopologicalOrder(ALGraph G, SqStack* T) {
    int i, j, k, count;
    int indegree[MAX_VERTEX_NUM + 1];
    SqStack S;
    ArcNode* p;
    
    // �Ը����������
    FindInDegree(G, indegree);
    
    // ��ʼ������ȶ���ջ
    InitStack(&S);
    
    // ��ʼ���������ж���ջ
    InitStack(T);
    
    // �������Ϊ0�Ķ���ջ
    for(i = 0; i < G.vexnum; i++) {
        // �����Ϊ0�Ķ�����ӵ�ջ��
        if(indegree[i] == 0) {
            Push(&S, i);
        }
        
        // ��ʼ������ȶ���(�¼�)�����緢��ʱ��Ϊ0
        ve[i] = 0;
    }
    
    // �����������еĶ������
    count = 0;
    
    // ��������ջ
    while(!StackEmpty(S)) {
        // ��ȡһ������ȶ���
        Pop(&S, &j);
        
        // ���ö�����뵽�������ж���ջ��
        Push(T, j);
        
        count++;
        
        // ����i�Ŷ�����ڽӵ�
        for(p = G.vertices[j].firstarc; p != NULL; p = p->nextarc) {
            // ��j�Ŷ���ÿ���ڽӵ����ȼ�һ�����൱���ж�j�Ŷ��㵽�����ڽӵ����ϵ
            k = p->adjvex;
            
            // ����������µ����Ϊ0�Ķ��㣬����������ջ
            if((--indegree[k]) == 0) {
                Push(&S, k);
            }
            
            // �����ڽӵ��¼������緢��ʱ��
            if(ve[j] + (*(p->info)).weight > ve[k]) {
                ve[k] = ve[j] + (*(p->info)).weight;
            }
        }
    }
    
    // ��������˻�·���򷵻�ERROR
    if(count < G.vexnum) {
        return ERROR;
    } else {
        return OK;
    }
}

/*
 * �������������
 */
static void FindInDegree(ALGraph G, int indegree[MAX_VERTEX_NUM]) {
    int i;
    ArcNode* p;
    
    // ��ʼ�����ж�������Ϊ0
    for(i = 0; i < G.vexnum; i++) {
        indegree[i] = 0;
    }
    
    // �������ж���
    for(i = 0; i < G.vexnum; i++) {
        // ָ��ö�����׸��ڽӵ�
        p = G.vertices[i].firstarc;
        
        // �����ö���������ڽӵ㣬ͳ�Ƹ���������
        while(p != NULL) {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }
}
