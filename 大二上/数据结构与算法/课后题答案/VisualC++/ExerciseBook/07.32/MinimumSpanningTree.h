/*===================
 * ����������С����ɭ��
 ===================*/

#ifndef MINIMUMSPANNINGTREE_H
#define MINIMUMSPANNINGTREE_H

#include <stdio.h>
#include <limits.h>   /* �ṩINT_MAX�� */
#include "MFSet.h"    //**��06 ���Ͷ�����**//
#include "ALGraph.h"  //**��07 ͼ**//
#include "CSTree.h"   //**��06 ���Ͷ�����**//

/*
 * ʹ������ķ�㷨����������G����С����ɭ��
 */
CSTree MinSpanTree_PRIM(ALGraph G);

/*
 * �Ӷ����Ӽ�V-U��ѡ����һ����ѡ�����Ա�������뵽��С������
 *
 * ѡ�񶥵��Ӽ�U�������Ӽ�V-U��Ȩֵ��С�ıߣ�
 * �����ظñ��ڶ����Ӽ�V-U����ͷ�Ķ˵㣬
 * �ö˵��������뵽�����Ӽ�U�У���Ϊ��С���������½�㡣
 *
 * ע���β���̲��и�����ģ��������ͬ
 */
static int minimum(ALGraph G);

#endif
