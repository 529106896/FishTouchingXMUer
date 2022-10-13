#include <stdio.h>
#include "Status.h"     //**��01 ����**//
#include "SqStack.h"    //**��03 ջ�Ͷ���**//
#include "MGraph.h"     //**��07 ͼ**//

// ���ʱ�־���飬��¼���ʹ��Ķ���
static Boolean visited[MAX_VERTEX_NUM];


/*
 * ����ջ������ǿ��ͨͼ����������ȱ�����
 * ϰ����ָ���������ھ����ͼ�ṹ�������������ɲ������ڽӾ���洢��ͼ��Ϊʾ����
 */
Status Algo_7_24(MGraph G);


int main(int argc, char* argv[]) {
    MGraph G;
    
    printf("���������������� ���������ͼ...\n");
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
    
    printf("���������������� ������ȱ���ͼ...\n");
    {
        Algo_7_24(G);
        printf("\n");
    }
    
    return 0;
}


/*
 * ����ջ������ǿ��ͨͼ����������ȱ�����
 * ϰ����ָ���������ھ����ͼ�ṹ�������������ɲ������ڽӾ���洢��ͼ��Ϊʾ����
 */
Status Algo_7_24(MGraph G) {
    SqStack S;
    SElemType e;
    int i;
    
    if(G.vexnum < 1) {
        return ERROR;
    }
    
    for(i = 0; i < G.vexnum; i++) {
        visited[i] = FALSE;
    }
    
    InitStack(&S);
    
    // ��һ��������ջ
    Push(&S, 0);
    visited[0] = TRUE;
    printf("%c ", G.vexs[0]);
    
    while(!StackEmpty(S)) {
        GetTop(S, &e);
        
        for(i = 0; i < G.vexnum; i++) {
            if(G.arcs[e][i].adj!=0 && visited[i]==FALSE) {
                Push(&S, i);
                visited[i] = TRUE;
                printf("%c ", G.vexs[i]);
                
                // ����������ǰѭ����������һ�������Ѱ
                break;
            }
        }
        
        // �������eû��δ���ʵ��ڽӵ��ˣ��򽫸ö����ջ
        if(i == G.vexnum) {
            Pop(&S, &e);
        }
    }
    
    printf("\n");
    
    return OK;
}
