#include <stdio.h>
#include <stdarg.h>   // �ṩ��va_list��va_start��va_arg��va_end
#include "Status.h"   //**��01 ����**//
#include "OLGraph.h"  //**��07 ͼ**//

/*
 * ���붥��
 *
 * ��ָ���Ķ���v׷�ӵ����㼯�У�δ�����ö�������������Ĺ�ϵ
 */
Status InsertVex_7_17(OLGraph* G, VertexType v);

/*
 * ɾ������
 *
 * �Ӷ��㼯��ɾ��ָ���Ķ���v��ע����Ҫ������صĶ����ϵ
 */
Status DeleteVex_7_17(OLGraph* G, VertexType v);

/*
 * �����/��<v, w>
 *
 * �����ǰͼ/��������ģ������һ������Ҫ�������������ϵ������������ֻ��һ��
 *
 * ����ͼ��˵�������ڿɱ�������г���/���ĸ�����Ϣ��
 * ��������˵�������ڿɱ�����������г���/����Ȩֵ�Լ�������Ϣ��
 */
Status InsertArc_7_17(OLGraph* G, VertexType v, VertexType w, ...);

/*
 * ɾ����/��<v, w>
 *
 * ��ɾ��ֻ�Ǹ��±�/������ͨ��ϵ
 */
Status DeleteArc_7_17(OLGraph* G, VertexType v, VertexType w);


int main(int argc, char* argv[]) {
    OLGraph G;
    
    printf("���������������� ���������ͼ/��...\n");
    {
        char* path[4];
        
        path[0] = "TestData_DG.txt";
        path[1] = "TestData_DN.txt";
        path[2] = "TestData_UDG.txt";
        path[3] = "TestData_UDN.txt";
        
        CreateGraph(&G, path);
        PrintGraph(G);
        printf("\n");
    }
    
    printf("���������������� ɾ������...\n");
    {
        VertexType v = 'X';
        
        printf("ɾ������ '%c' ���ͼΪ��\n", v);
        DeleteVex_7_17(&G, v);
        PrintGraph(G);
        printf("\n");
    }
    
    printf("���������������� ���붥��...\n");
    {
        VertexType v = 'Y';
        
        printf("���붥�� '%c' ���ͼΪ��\n", v);
        InsertVex_7_17(&G, v);
        PrintGraph(G);
        printf("\n");
    }
    
    printf("���������������� �����/��...\n");
    {
        // ע��<E, B>���ظ��ı�
        VertexType v[10] = {'B', 'C', 'E', 'Y', 'Y', 'Y', 'D', 'D', 'E', 'E'};
        VertexType w[10] = {'Y', 'Y', 'Y', 'A', 'B', 'D', 'C', 'A', 'B', 'D'};
        InfoType info[10] = {{8}, {5}, {1}, {11}, {2}, {6}, {3}, {7}, {2}, {9}};
        int k;
    
        // ͼ
        if(G.kind == DG || G.kind == UDG) {
            for(k = 0; k < 10; k++) {
                printf("������Ȩֵ�ıߣ�<%c, %c>...\n", v[k], w[k]);
                InsertArc_7_17(&G, v[k], w[k]);
            }
        
            // ��
        } else if(G.kind == DN || G.kind == UDN) {
            for(k = 0; k < 10; k++) {
                printf("�����Ȩֵ�ıߣ�<%c, %c, %d>...\n", v[k], w[k], info[k].weight);
                InsertArc_7_17(&G, v[k], w[k], &info[k]);
            }
        } else {
            return ERROR;
        }
    
        PrintGraph(G);
        printf("\n");
    }
    
    printf("���������������� ɾ����/��...\n");
    {
        VertexType v[3] = {'D', 'E', 'F'};
        VertexType w[3] = {'A', 'B', 'B'};
        int k;
        
        for(k = 0; k < 3; k++) {
            printf("ɾ���ߣ�<%c, %c>...\n", v[k], w[k]);
            DeleteArc_7_17(&G, v[k], w[k]);
        }
        PrintGraph(G);
        printf("\n");
    }
    
    return 0;
}


/*
 * ���붥��
 *
 * ��ָ���Ķ���v׷�ӵ����㼯�У�δ�����ö�������������Ĺ�ϵ
 */
Status InsertVex_7_17(OLGraph* G, VertexType v) {
    return InsertVex(G, v);
}

/*
 * ɾ������
 *
 * �Ӷ��㼯��ɾ��ָ���Ķ���v��ע����Ҫ������صĶ����ϵ
 */
Status DeleteVex_7_17(OLGraph* G, VertexType v) {
    return DeleteVex(G, v);
}

/*
 * �����/��<v, w>
 *
 * �����ǰͼ/��������ģ������һ������Ҫ�������������ϵ������������ֻ��һ��
 *
 * ����ͼ��˵�������ڿɱ�������г���/���ĸ�����Ϣ��
 * ��������˵�������ڿɱ�����������г���/����Ȩֵ�Լ�������Ϣ��
 */
Status InsertArc_7_17(OLGraph* G, VertexType v, VertexType w, ...) {
    va_list ap;
    InfoType* info = NULL;      // ��/���ĸ�����Ϣ
    
    // �����/���ϴ��ڸ�����Ϣ
    if(IncInfo) {
        va_start(ap, w);                // ��w���ѯ�׸��ɱ����
        info = va_arg(ap, InfoType*);   // ��ȡ������Ϣ
        va_end(ap);
    }
    
    return InsertArc(G, v, w, info);
}

/*
 * ɾ����/��<v, w>
 *
 * ��ɾ��ֻ�Ǹ��±�/������ͨ��ϵ
 */
Status DeleteArc_7_17(OLGraph* G, VertexType v, VertexType w) {
    return DeleteArc(G, v, w);
}
