#include <stdio.h>
#include <limits.h>
#include "SqList.h"
#include "ALGraph.h"

/*
 * ��ȡ�洢�������޻�ͼ�еı��ʽ���沨��ʽ
 *
 * ע�����ʽ�ṹ�ο��̲Ĳ�ͼ7.23
 */
void Algo_7_40(ALGraph G, SqList* RPN);

/*
 * �Ӷ���v������ȡ����ͼ�д洢�ı��ʽ���沨��ʽ��
 * ��ȡ���沨��ʽ��洢��RPN�С�
 */
static void AntiPolandFormula_7_40(ALGraph G, int v, SqList* RPN);

/*
 * �����沨��ʽ��ֵ
 */
int Evaluation_7_40(SqList RPN);


int main(int argc, char* argv[]) {
    ALGraph G;
    SqList RPN;     // �洢�沨�����ʽ
    
    printf("���������������� ��������ӡ������... \n");
    {
        char* path[4];
        
        path[0] = "TestData_DG.txt";
        path[1] = "";
        path[2] = "";
        path[3] = "";
        
        CreateGraph(&G, path);
        PrintGraph(G);
        printf("\n");
    }
    
    printf("���������������� ��ȡ�������д洢�ı��ʽ���沨��ʽ... \n");
    {
        Algo_7_40(G, &RPN);
        printf("\n");
    }
    
    printf("���������������� �����沨��ʽ��ֵ... \n");
    {
        printf("���������沨��ʽ��ֵΪ��%d\n", Evaluation_7_40(RPN));
        printf("\n");
    }
    
    return 0;
}


/*
 * ��ȡ�洢�������޻�ͼ�еı��ʽ���沨��ʽ
 *
 * ע�����ʽ�ṹ�ο��̲Ĳ�ͼ7.23
 */
void Algo_7_40(ALGraph G, SqList* RPN) {
    int i, root;
    int indegree[MAX_VERTEX_NUM];   // ���ж���������Ϣ
    ArcNode* p;
    ElemType e;
    
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
    
    // ���ҵ������
    for(i = 0; i < G.vexnum; i++) {
        if(indegree[i] == 0) {
            root = i;
            break;
        }
    }
    
    // ��ʼ������Ϊ0�����Ա�
    InitList(RPN);
    
    // �������޻�ͼ�ĸ���������ͨ��β�ݹ��ȡ�����д洢�ı��ʽ���沨��ʽ
    AntiPolandFormula_7_40(G, root, RPN);
    
    // ����沨��ʽ
    for(i = 1; i <= ListLength(*RPN); i++) {
        GetElem(*RPN, i, &e);
        
        if(e.type == Operand) {
            printf("%d ", e.op);    // ������
        } else {
            printf("%c ", e.op);    // ������
        }
    }
    printf("\n");
}

/*
 * �Ӷ���v������ȡ����ͼ�д洢�ı��ʽ���沨��ʽ��
 * ��ȡ���沨��ʽ��洢��RPN�С�
 */
void AntiPolandFormula_7_40(ALGraph G, int v, SqList* RPN) {
    ArcNode* r;
    Vertex vex;
    
    // �ȱ����ڽӵ�
    for(r = G.vertices[v].firstarc; r != NULL; r = r->nextarc) {
        AntiPolandFormula_7_40(G, r->adjvex, RPN);
    }
    
    // ��ȡ������/������
    vex = G.vertices[v].context;
    
    // ��û���ڽӵ�ɱ���ʱ���洢�ö���
    ListInsert(RPN, ListLength(*RPN) + 1, vex);
}

/*
 * �����沨��ʽ��ֵ������������󣬷���INT_MIN��
 */
int Evaluation_7_40(SqList RPN) {
    int stack[MAX_VERTEX_NUM];  // ģ��һ��ջ�������洢���ʽ�ļ�����
    int top = 0; // ջ���α�
    int a, b;
    ElemType e;
    int i;
    Boolean hasError = FALSE;   // ��������г����˴���
    
    for(i = 1; i <= ListLength(RPN) && !hasError; i++) {
        GetElem(RPN, i, &e);
        
        // ������
        if(e.type == Operand) {
            stack[top++] = e.op;
            
            // ������
        } else {
            if(top > 0) {
                b = stack[--top];
            } else {
                return INT_MIN;
            }
            
            if(top > 0) {
                a = stack[--top];
            } else {
                return INT_MIN;
            }
            
            switch(e.op) {
                case '+':
                    stack[top++] = a + b;
                    break;
                case '-':
                    stack[top++] = a - b;
                    break;
                case '*':
                    stack[top++] = a * b;
                    break;
                case '/':
                    stack[top++] = a / b;
                    break;
                default:
                    printf("�޷�ʶ��Ĳ�������%c\n", e.op);
                    hasError = TRUE;
                    break;
            }
        }
    }
    
    // ջ�����ֻӦ��ʣһ��ֵ
    if(hasError || top != 1) {
        return INT_MIN;
    }
    
    return stack[0];
}
