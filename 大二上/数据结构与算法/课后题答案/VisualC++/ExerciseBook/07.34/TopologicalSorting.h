/*=======================
 * AOV-��(����ͼ)����������
 *
 * �����㷨: 7.12
 ========================*/

#ifndef TOPOLOGICALSORTING_H
#define TOPOLOGICALSORTING_H

#include <stdio.h>
#include "Status.h"     //**��01 ����**//
#include "SqStack.h"    //**��03 ջ�Ͷ���**//
#include "ALGraph.h"    //**��07 ͼ**//

/*
 * ���������������� �㷨7.12 ����������������
 *
 * �������ͼG�޻�·�����������һ���������в�����OK�����򣬷���FALSE��
 * ��������ͨ����Ψһ�����Ǳ��뱣֤ĳЩ�ؼ��ڵ���Ⱥ����
 */
Status TopologicalSort(ALGraph G, int topo[MAX_VERTEX_NUM]);

/*
 * �������������
 */
static void FindInDegree(ALGraph G, int indegree[MAX_VERTEX_NUM]);

#endif
