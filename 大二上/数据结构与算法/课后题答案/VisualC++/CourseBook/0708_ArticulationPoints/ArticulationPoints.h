/*====================
 * ����ͼ�Ĺؽڵ�
 *
 * �����㷨: 7.10��7.11
 =====================*/

#ifndef ARTICULATIONPOINTS_H
#define ARTICULATIONPOINTS_H

#include <stdio.h>
#include "Status.h"     //**��01 ����**//
#include "ALGraph.h"    //**��07 ͼ**//

/*
 * ���������������� �㷨7.10 ����������������
 *
 * ���Ҳ����G��ȫ���ؽڵ�
 */
void FindArticul(ALGraph G);

/*
 * ���������������� �㷨7.11 ����������������
 *
 * �ӵ�v0���������������ȱ���ͼG�����Ҳ�������йؽڵ�
 */
void DFSArticul(ALGraph G, int v0);

#endif
