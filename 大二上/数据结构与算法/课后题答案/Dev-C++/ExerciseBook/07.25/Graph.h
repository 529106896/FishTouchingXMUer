/*=================================
 * ����7.25������������һ������ͼ�ṹ
 ==================================*/

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <string.h>     // �ṩmemset��strcmp ԭ��
#include "Status.h"     //**��01 ����**//

#define MAX_VERTEX_NUM 26   // ����������ֵ
#define MAX_ADJ_NUM    650  // ���ж�����ڽӵ����������ֵ

// ��������
typedef char VertexType;

// ����ͼ���Ͷ���
typedef struct Graph {
    VertexType vexs[MAX_VERTEX_NUM];  // ��������
    int s[MAX_ADJ_NUM];               // ��������ڽӵ�
    int fst[MAX_VERTEX_NUM];          // fst[v] -> ����v���ڽӵ���s�е���ʼ�±�
    int lst[MAX_VERTEX_NUM];          // lst[v] -> ����v���ڽӵ���s�е���ֹ�±�
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
 * ��ӡ����ͼ�ṹ
 */
void PrintGraph(Graph G);

#endif
