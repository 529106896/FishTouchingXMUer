#include <stdio.h>
#include "AMLGraph.h"     //**��07 ͼ**//

// ���Ժ�������ӡԪ��
Status PrintElem(VertexType c) {
    printf("%c ", c);
    return OK;
}


int main(int argc, char* argv[]) {
    AMLGraph G;
    
    printf("���������������� CreateGraph \n");
    {
        char* path[4];
    
        path[0] = "";
        path[1] = "";
        path[2] = "TestData_UDG.txt";
        path[3] = "TestData_UDN.txt";
        
        printf("��������ͼ/��...\n");
        CreateGraph(&G, path);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� PrintGraph \n");
    {
        printf("���ͼ/�����ڽӾ���... \n");
        PrintGraph(G);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� LocateVex \n");
    {
        VertexType u = 'X';
        printf("���� '%c' ��λ��Ϊ %d\n", u, LocateVex(G, u));
    }
    PressEnterToContinue(debug);
    
    printf("���������������� GetVex \n");
    {
        int v = 1;
        printf("���� '%d' ���Ķ���ֵΪ %c\n", v, GetVex(G, v));
    }
    PressEnterToContinue(debug);
    
    printf("���������������� FirstAdjVex \n");
    {
        VertexType v = 'X';
        int k = FirstAdjVex(G, v);
        printf("���� '%c' �ĵ�һ���ڽӶ���Ϊ '%c'\n", v, G.adjmulist[k].data);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� NextAdjVex \n");
    {
        VertexType v = 'X';
        VertexType w = 'A';
        int k = NextAdjVex(G, v, w);
        printf("���� '%c' ����ڶ��� '%c' ����һ���ڽӶ���Ϊ '%c'\n", v, w, G.adjmulist[k].data);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� DeleteVex \n");
    {
        VertexType v = 'X';
        
        printf("ɾ������ '%c' ...\n", v);
        DeleteVex(&G, v);
        
        PrintGraph(G);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� InsertVex \n");
    {
        VertexType v = 'Y';
        printf("���붥�� '%c' ...\n", v);
        InsertVex(&G, v);
        PrintGraph(G);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� InsertArc \n");
    {
        // ע��<E, B>���ظ��ı�
        VertexType v[10] = {'B', 'C', 'E', 'Y', 'Y', 'Y', 'D', 'D', 'E', 'E'};
        VertexType w[10] = {'Y', 'Y', 'Y', 'A', 'B', 'D', 'C', 'A', 'B', 'D'};
        InfoType info[10] = {{8}, {5}, {1}, {11}, {2}, {6}, {3}, {7}, {2}, {9}};
        int k;
        
        // ����ͼ
        if(G.kind == UDG) {
            for(k = 0; k < 10; k++) {
                printf("������Ȩֵ�ıߣ�<%c, %c>...\n", v[k], w[k]);
                InsertArc(&G, v[k], w[k]);
            }
            
            // ������
        } else if(G.kind == UDN) {
            for(k = 0; k < 10; k++) {
                printf("�����Ȩֵ�ıߣ�<%c, %c, %d>...\n", v[k], w[k], info[k].weight);
                InsertArc(&G, v[k], w[k], &info[k]);
            }
        } else {
            return ERROR;
        }
        
        PrintGraph(G);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� PutVex \n");
    {
        VertexType v     = 'Y';
        VertexType value = 'F';
        printf("�Զ��� '%c' ��ֵ '%c' ...\n", v, value);
        PutVex(&G, v, value);
        PrintGraph(G);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� DeleteArc \n");
    {
        VertexType v[3] = {'D', 'E', 'F'};
        VertexType w[3] = {'A', 'B', 'B'};
        int k;
        
        for(k=0; k<3; k++) {
            printf("ɾ���ߣ�<%c, %c>...\n", v[k], w[k]);
            DeleteArc(&G, v[k], w[k]);
        }
        PrintGraph(G);
    }
    PressEnterToContinue(debug);
    
    printf("���������������� DFSTraverse�� \n");
    {
        printf("������ȱ���ͼ/��...\n");
        DFSTraverse(G, PrintElem);
        printf("\n");
    }
    PressEnterToContinue(debug);
    
    printf("���������������� BFSTraverse \n");
    {
        printf("������ȱ���ͼ/��...\n");
        BFSTraverse(G, PrintElem);
        printf("\n");
    }
    PressEnterToContinue(debug);
    
    printf("���������������� DestroyGraph \n");
    {
        printf("����ͼ/��G...\n");
        DestroyGraph(&G);
        PrintGraph(G);
    }
    PressEnterToContinue(debug);
    
}
