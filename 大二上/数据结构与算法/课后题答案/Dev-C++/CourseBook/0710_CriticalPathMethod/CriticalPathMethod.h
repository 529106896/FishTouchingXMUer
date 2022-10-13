/*=======================
 * AOE-��(������)�Ĺؼ�·��
 *
 * �����㷨: 7.13��7.14
 ========================*/

#ifndef CRITICALPATHMETHOD_H
#define CRITICALPATHMETHOD_H

#include <stdio.h>
#include "Status.h"     //**��01 ����**//
#include "SqStack.h"    //**��03 ջ�Ͷ���**//
#include "ALGraph.h"    //**��07 ͼ**//

/*
 * ���������������� �㷨7.14 ����������������
 *
 * ����������G�Ĺؼ�·��
 *
 * ע���������������������һ���������Ϊ�¼��յ�
 */
Status CriticalPath(ALGraph G);

/*
 * ���������������� �㷨7.13 ����������������
 *
 * ���������G�޻�·����Ѱ������һ���������д洢����������ջT�У�������OK�����򣬷���FALSE��
 * ��������ͨ����Ψһ�����Ǳ��뱣֤ĳЩ�ؼ��ڵ���Ⱥ����
 */
static Status TopologicalOrder(ALGraph G, SqStack* T);

/*
 * �������������
 */
static void FindInDegree(ALGraph G, int indegree[MAX_VERTEX_NUM]);

#endif
