/*=================================
 * ����7.33������������һ���������ṹ
 ==================================*/

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <limits.h>     // �ṩ��INT_MAX
#include <stdlib.h>     // �ṩ malloc��free ԭ��
#include <string.h>     // �ṩ memset��strcmp ԭ��
#include "Status.h"     //**��01 ����**//

#define INFINITE INT_MAX    // ���ֵ��������ʾ���е��������㲻ֱ������
#define MAX_VERTEX_NUM 26   // ����������ֵ

// ��������
typedef char VertexType;

// �߼�����
typedef struct {
    int u, v;    // ����
    int weight;  // Ȩֵ
} EdgeSetType;

// ����ͼ���Ͷ���
typedef struct Graph {
    VertexType vexs[MAX_VERTEX_NUM];  // ��������
    EdgeSetType* EdgeSet;             // �߼�
    int vexnum, arcnum;               // ����ͼ�Ķ������ͻ���
} Graph;


/*
 * ��������ͼ
 *
 * pathΪNULL��Ϊ""ʱ���ӿ���̨��ȡͼ�ĳ�ʼ����Ϣ��
 * ���򣬴�Ԥ����ļ��ж�ȡͼ�ĳ�ʼ����Ϣ��
 */
Status CreateGraph(Graph* G, char* path);

/*
 * ��������ͼ�ĺ����㷨
 */
static void Create(Graph* G);

/*
 * ����
 *
 * ���ض���u������ͼ�е�λ��
 */
int LocateVex(Graph G, VertexType u);

/*
 * �ӱ߼�EdgeSet�л�ȡ��С�ߵĶ���u��v��������TRUE��
 * ���߼�Ϊ�գ��򷵻�FASLE��
 */
Boolean GetMinEdge(EdgeSetType* EdgeSet, int* u, int* v);

/*
 * �ӱ߼���ɾ�������ڶ���u��v����С�ߡ�
 * ɾ���ɹ�����TRUE�����򣬷���FALSE��
 */
Boolean DelMinEdge(EdgeSetType* EdgeSet, int u, int v);

/*
 * ��ӡ����ͼ�ṹ
 */
void PrintGraph(Graph G);

#endif
