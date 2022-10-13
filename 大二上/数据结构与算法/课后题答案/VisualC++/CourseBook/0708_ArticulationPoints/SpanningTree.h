/*==================
 * ����ͼ��������
 *
 * �����㷨: 7.7��7.8
 ===================*/

#ifndef SPANNINGTREE_H
#define SPANNINGTREE_H

#include <stdlib.h>     // �ṩmalloc��realloc��free��exitԭ��
#include "CSTree.h"     //**��06 ���Ͷ�����**//
#include "ALGraph.h"     //**��07 ͼ**//

/*
 * ���������������� �㷨7.7 ����������������
 *
 * ��������ͼ��������(ɭ��)
 */
void DFSForest(ALGraph G, CSTree* T);

/*
 * ���������������� �㷨7.8 ����������������
 *
 * ͨ��������ȱ�������㣬������v��ʼ����
 */
void DFSTree(ALGraph G, int v, CSTree* T);

#endif
