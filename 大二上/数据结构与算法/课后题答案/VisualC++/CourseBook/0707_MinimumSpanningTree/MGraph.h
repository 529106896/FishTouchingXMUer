/*=================================
 * ͼ������(�ڽӾ���)�洢��ʾ
 *
 * �����㷨: 7.1��7.2��7.4��7.5��7.6
 ==================================*/

#ifndef MGRAPH_H
#define MGRAPH_H

#include <stdio.h>
#include <limits.h>     // �ṩ��INT_MAX
#include <string.h>     // �ṩmemset��strcmp ԭ��
#include <stdarg.h>     // �ṩ��va_list��va_start��va_arg��va_end
#include "Status.h"     //**��01 ����**//

/*
 * ע��
 *
 * ͨ����������Ȩͼ�����Ϊ��ͼ������Ȩͼ�����Ϊ��������
 * ����ͼ/���еĶ����ϵ����Ϊ���ߡ�������ͼ/���еĶ����ϵ����Ϊ�������������ֻ�ͷ�뻡β��
 * ʵ�ʱ����У�δ�ػ��ϸ���������������
 */

/* �궨�� */
#define INFINITE INT_MAX    // ���ֵ��������ʾ���е��������㲻ֱ������
#define MAX_VERTEX_NUM 26   // ��󶥵����


// ͼ������
typedef enum {
    DG,     // 0-����ͼ
    DN,     // 1-������(��Ȩֵ)
    UDG,    // 2-����ͼ
    UDN     // 3-������(��Ȩֵ)
} GraphKind;

// ��������
typedef char VertexType;

/*
 * �����ϵ����
 *
 * ����Ȩͼ�У���ֵͨ��Ϊ0��1����ʾ�������Ƿ�ֱ����ͨ��
 * ����Ȩͼ�У���ֵͨ��ΪȨֵ��
 */
typedef int VRType;

// �ߵ���ظ�����Ϣ
typedef struct {
    // ����еĻ��������������Ӧ������
    void* v; // ���һ��������ı�����ռλ������ṹ��Ϊ�յĻ�����VC++�лᱨ��
} InfoType;

// �ߵ����ͣ�ÿ�����Ͽ����и�����Ϣinfo
typedef struct ArcCell {
    VRType adj;  // �����ϵ������Ȩͼ����Ȩͼ�еĺ��岻ͬ
    InfoType* info; // �ߵĸ�����Ϣ��ͨ������
} ArcCell;

/* ͼ/��������(�ڽӾ���)�洢��ʾ���Ͷ��� */
typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];               // ��������
    ArcCell arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  // �ڽӾ���
    int vexnum, arcnum;                            // ͼ/���Ķ������ͻ���
    GraphKind kind;                                // ͼ�����ͱ�־
} MGraph;


// ��/�����Ƿ���ڸ�����Ϣ
extern Boolean IncInfo;


/*
 * ���������������� �㷨7.1 ����������������
 *
 * ����
 *
 *����ע��
 *
 * �̲���Ĭ�ϴӿ���̨��ȡ���ݡ�
 * ����Ϊ�˷�����ԣ�����ÿ�����ж��ֶ��������ݣ�
 * �������ѡ���Ԥ����ļ�path�ж�ȡ�������ݡ�
 *
 * �����Ҫ�ӿ���̨��ȡ���ݣ���pathΪNULL����path[kind]Ϊ""��
 * �����Ҫ���ļ��ж�ȡ���ݣ�����Ҫ��path����д�ļ�����Ϣ��
 */
Status CreateGraph(MGraph* G, char* path[]);

/*
 * ���������������� �㷨7.2 ����������������
 *
 * ����������
 */
static Status CreateUDN(MGraph* G);

/*
 * ¼��ߵ���ظ�����Ϣ
 */
static void Input(MGraph G, InfoType** info);

/*
 * ����
 *
 * ���ض���u��ͼ/���е�λ��
 */
int LocateVex(MGraph G, VertexType u);

/*
 * ȡֵ
 *
 * ��������v���Ķ���ֵ
 */
VertexType GetVex(MGraph G, int v);

/*
 * ��ͼ�λ���ʽ�����ǰ�ṹ
 *
 * ע����ͼ/���У�ʹ��"-"����ʾ�����㲻ֱ����ͨ
 */
void PrintGraph(MGraph G);

#endif
