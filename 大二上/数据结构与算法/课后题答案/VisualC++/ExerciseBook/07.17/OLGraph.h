/*====================
 * ͼ��ʮ������洢��ʾ
 *
 * �����㷨: 7.3
 ====================*/

#ifndef OLGRAPH_H
#define OLGRAPH_H

#include <stdio.h>
#include <string.h>     // �ṩmemset��strcmp ԭ��
#include <stdarg.h>     // �ṩ��va_list��va_start��va_arg��va_end
#include <stdlib.h>     // �ṩmalloc��realloc��free��exitԭ��
#include "Status.h"     //**��01 ����**//

/*
 * ע��
 *
 * ͨ����������Ȩͼ�����Ϊ��ͼ������Ȩͼ�����Ϊ��������
 * ����ͼ/���еĶ����ϵ����Ϊ���ߡ�������ͼ/���еĶ����ϵ����Ϊ�������������ֻ�ͷ�뻡β��
 * ʵ�ʱ����У�δ�ػ��ϸ���������������
 *
 * ��ǰ�ṹ�ʺϴ洢����ͼ��
 *
 * �� �����/������Ϣʱ�������ʵ���ǰ�"����"����ģ���ʹ�ò���Ļ��ǰ�"����"���еġ�
 */


/* �궨�� */
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

// ��/������ظ�����Ϣ
typedef struct {
    /*
     * ע��
     * �̲��и����Ľṹֻ��������Ȩͼ����û������Ȩͼ(��)��
     * ����Ϊ�˰ѡ�����������Ҳ���ǽ�ȥ�����ڸ�����Ϣ��������"Ȩ��"���ԡ�
     */
    int weight;
} InfoType;

/* ��/����� */
typedef struct ArcBox {
    int tailvex;    // ��ͷ����λ��
    int headvex;    // ��β����λ��
    struct ArcBox* hlink;  // ָ����һ��ӵ����ͬ��ͷ�Ļ�
    struct ArcBox* tlink;  // ָ����һ��ӵ����ͬ��β�Ļ�
    InfoType* info;  // �û�����ظ�����Ϣ
} ArcBox;

// ÿ�����������ͷ���
typedef struct VexNode {
    VertexType data;    // ����
    ArcBox* firstin;    // ָ��ö���ĵ�һ���뻡
    ArcBox* firstout;   // ָ��ö���ĵ�һ������
} VexNode;

/* ͼ��ʮ������洢��ʾ���Ͷ��� */
typedef struct {
    VexNode xlist[MAX_VERTEX_NUM];  // ��ͷ����
    int vexnum, arcnum;             // �������ͻ���
    GraphKind kind;                 // ͼ�����ͱ�־
} OLGraph;


// ��/�����Ƿ���ڸ�����Ϣ
extern Boolean IncInfo;


/*
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
Status CreateGraph(OLGraph* G, char* path[]);

/*
 * ���������������� �㷨7.3 ����������������
 *
 * ��������ͼ
 *
 * ע��
 * �̲���ʹ����ͷ�巨�����뻡������������Ψһ�ŵ��ǲ��뷽�㣬
 * �������漰��ɾ�������ʱ��Ч�ʽϵͣ�
 * ���ң�"ͷ�巨"���������˳���������ı�/��������ģ�
 * �����չ������ͼ/���еı�/��Ҳ������ġ�
 *
 * Ϊ�˿˷�����ȱ�㣬�������"����"���뷨����֤����Ļ���"����"�ġ�
 * ��ͬʱ����������ʹ"����"�㷨��ý�Ϊ���ӡ�
 */
static Status CreateDG(OLGraph* G);

/*
 * ����������
 */
static Status CreateDN(OLGraph* G);

/*
 * ��������ͼ
 */
static Status CreateUDG(OLGraph* G);

/*
 * ����������
 */
static Status CreateUDN(OLGraph* G);

/*
 * ¼�뻡����ظ�����Ϣ
 */
static void Input(OLGraph G, InfoType** info);

/*
 * ����
 *
 * ���ض���u��ͼ/���е�λ��
 */
int LocateVex(OLGraph G, VertexType u);

/*
 * ���붥��
 *
 * ��ָ���Ķ���v׷�ӵ����㼯�У�δ�����ö�������������Ĺ�ϵ
 */
Status InsertVex(OLGraph* G, VertexType v);

/*
 * ɾ������
 *
 * �Ӷ��㼯��ɾ��ָ���Ķ���v��ע����Ҫ������صĶ����ϵ
 */
Status DeleteVex(OLGraph* G, VertexType v);

/*
 * ����һ����/�����(�����ڲ�ʹ��)
 */
static ArcBox* newArcBoxPtr(int tailvex, int headvex, ArcBox* hlink, ArcBox* tlink, InfoType* info);

/*
 * �����/��<v, w>
 *
 * �����ǰͼ/��������ģ������һ������Ҫ�������������ϵ������������ֻ��һ��
 * ����ͼ/����˵�������ڿɱ�������г���/���ĸ�����Ϣ��
 *
 * ע���˴����յĲ�����MGraph��Щ��һ�������ĸ�����Ϣ�а����˸�����/����Ȩֵ��
 */
Status InsertArc(OLGraph* G, VertexType v, VertexType w, ...);

/*
 * ɾ����/��<v, w>
 */
Status DeleteArc(OLGraph* G, VertexType v, VertexType w);

/*
 * ��ͼ�λ���ʽ�����ǰ�ṹ
 */
void PrintGraph(OLGraph G);

#endif
