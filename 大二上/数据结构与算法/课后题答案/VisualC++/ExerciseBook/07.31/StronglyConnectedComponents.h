/*==================
 * ����ͼ��ǿ��ͨ����
 ===================*/

#ifndef STRONGLYCONNECTEDCOMPONENTS_H
#define STRONGLYCONNECTEDCOMPONENTS_H

#include <stdio.h>
#include "OLGraph.h"    //**��07 ͼ**//

/*
 * (1) Tarjan�㷨
 *
 * ��ȡ����ͼ��ǿ��ͨ����
 */
void Tarjan(OLGraph G);

/*
 * ������ȱ�������v�ɴ������Ԫ�أ��������ҳ����е�ǿ��ͨ����
 */
static void DFS_Tarjan(OLGraph G, int v);


/*
 * (2) Kosaraju�㷨
 *
 * ��ȡ����ͼ��ǿ��ͨ���������ǽ̲����ᵽ���㷨
 *
 * ����˼���ǣ�
 * 1.��ĳ�����������ȱ�������ͼ���õ�һ���������У�
 * 2.��������ͼ��
 * 3.��������ó��ķ������У������е�ÿ���������������ȱ�����
 */
void Kosaraju(OLGraph G);

/*
 * ��������ͼ��ʮ������洢�ṹ�����������л��ķ�������
 *
 * ����˼���ǣ�
 * 1.����һ���������κλ��Ŀ�ͼ��
 * 2.���α���ÿ�������ÿ���뻡��
 * 3.ժ���������뻡��������뵽��ͼ�б�ɳ�����
 */
static void InverseGraph(OLGraph *G);

/*
 * �洢������ȱ����з��ʵ���Ԫ��
 */
static Status StoreElem(VertexType c);

/*
 * ��ȱ����Ѿ����ú��ͼ�������ڲ�ʹ��
 */
static void DFS_Inverse(OLGraph G, int v);

#endif
