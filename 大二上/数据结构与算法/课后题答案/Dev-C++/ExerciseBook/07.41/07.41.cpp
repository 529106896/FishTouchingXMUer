#include <stdio.h>
#include "SqStack.h"
#include "ALGraph.h"

// �������ҵ���Ȩֵ������·����Ȩֵ��
static int MAX = -1;


/*
 * ��ȡ�������еĹؼ�·��(CPM)
 *
 * �˴�����������ȱ�����˼������ȡ�ؼ�·���������ԭ���ǣ��ؼ�·�� = Ȩֵ������·��
 *
 * ע���̲���Ӧ���Ǳ��󣬲���������ͼ�Ĺؼ�·�������������������·��
 */
void Algo_7_41(ALGraph G);

/*
 * ���ҹؼ�·���ϵ�Դ��
 *
 * �˴�ʹ������һ�ַ�ʽ��Դ�㣬��������֮ǰһ��ͨ�������Ϣ��Դ�㣬
 * ���������ַ�������;ͬ��ġ�
 */
static int FindBegin_7_41(ALGraph G);

/*
 * ͨ��������ȱ�������ͼ�дӶ���v������Ȩֵ���·��(�ؼ�·��)��
 *
 * sum��S��������·��Ȩֵ�����Ѿ��ҵ���·����
 * path������¼��ǰ�ҵ���Ȩֵ������·����path[0]�ϴ洢����������
 */
static void FindPath_7_41(ALGraph G, int v, int sum, SqStack* S, int path[MAX_VERTEX_NUM + 1]);


int main(int argc, char* argv[]) {
    ALGraph G;
    
    printf("���������������� ��������ӡ������... \n");
    {
        char* path[4];
        
        path[0] = "";
        path[1] = "TestData_DN.txt";
        path[2] = "";
        path[3] = "";
        
        CreateGraph(&G, path);
        PrintGraph(G);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� ��ȡ�������Ĺؼ�·��... \n");
    {
        Algo_7_41(G);
    }
    PressEnterToContinue(debug);
    
    return 0;
}


/*
 * ��ȡ�������еĹؼ�·��(CPM)
 *
 * �˴�����������ȱ�����˼������ȡ�ؼ�·���������ԭ���ǣ��ؼ�·�� = Ȩֵ������·��
 *
 * ע���̲���Ӧ���Ǳ��󣬲���������ͼ�Ĺؼ�·�������������������·��
 */
void Algo_7_41(ALGraph G) {
    int i;
    int begin;  // �ؼ�·���ϵ�Դ��
    int path[MAX_VERTEX_NUM + 1] = {-1}; // �洢Ȩֵ������·����0�õ�Ԫ�洢Ȩֵ��
    SqStack S;
    
    // ���ҹؼ�·���ϵ�Դ��
    begin = FindBegin_7_41(G);
    
    InitStack(&S);
    
    FindPath_7_41(G, begin, 0, &S, path);
    
    printf("���ҵ���Ȩֵ������·��(�ؼ�·��)Ϊ��");
    for(i = 1; i <= path[0]; i++) {
        printf("%c ", G.vertices[path[i]].data);
    }
    printf("\n");
}

/*
 * ���ҹؼ�·���ϵ�Դ��
 *
 * �˴�ʹ������һ�ַ�ʽ��Դ�㣬��������֮ǰһ��ͨ�������Ϣ��Դ�㣬
 * ���������ַ�������;ͬ��ġ�
 */
static int FindBegin_7_41(ALGraph G) {
    int k;
    ArcNode* p;
    Boolean isAdj[MAX_VERTEX_NUM] = {FALSE};   // ��¼��Щ���������ڽӵ�
    
    // �ҵ������ڽӵ�
    for(k = 0; k < G.vexnum; k++) {
        for(p = G.vertices[k].firstarc; p != NULL; p = p->nextarc) {
            isAdj[p->adjvex] = TRUE;
        }
    }
    
    // �ؼ�·���ϵ�Դ��û���뻡������Ҳ�����Ϊ��Ķ�����ڽӵ�
    for(k = 0; k < G.vexnum; k++) {
        if(isAdj[k] == FALSE) {
            return k;
        }
    }
    
    return -1;
}

/*
 * ͨ��������ȱ�������ͼ�дӶ���v������Ȩֵ���·��(�ؼ�·��)��
 *
 * sum��S��������·��Ȩֵ�����Ѿ��ҵ���·����
 * path������¼��ǰ�ҵ���Ȩֵ������·����path[0]�ϴ洢����������
 */
static void FindPath_7_41(ALGraph G, int v, int sum, SqStack* S, int path[MAX_VERTEX_NUM + 1]) {
    int i;
    ArcNode* p;
    SElemType e;
    
    // �������Ķ����ݴ浽·��ջ
    Push(S, v);
    
    // ������ȱ���
    for(p = G.vertices[v].firstarc; p != NULL; p = p->nextarc) {
        sum += p->info->weight;
        FindPath_7_41(G, p->adjvex, sum, S, path);
        sum -= p->info->weight;
    }
    
    /*
     * ���ˣ���·���ѱ������˾�ͷ��
     * �����·����Ȩֵ�ͱ�֮ǰ�ҵ���·��Ȩֵ�͸�������Ҫ�Ѹ�·�������ر��浽path�У�
     * ������ɺ󣬽���ǰ����v��ջ
     */
    
    // ����ö������յ�(����Ϊû���ڽӵ�)
    if(G.vertices[v].firstarc == NULL) {
        // ������Ȩֵ�͸����·��
        if(sum > MAX) {
            MAX = sum;
            
            path[0] = StackLength(*S);
            
            // ��ջ�б����·�����Ƶ�path��
            for(i = 0; i < StackLength(*S); i++) {
                path[i + 1] = S->base[i];
            }
        }
    }
    
    Pop(S, &e);
}
