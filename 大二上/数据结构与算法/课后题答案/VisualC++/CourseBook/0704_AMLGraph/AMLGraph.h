/*=====================
 * ͼ���ڽӶ��ر�洢��ʾ
 ======================*/

#ifndef AMLGRAPH_H
#define AMLGRAPH_H

#include <stdio.h>
#include <string.h>     // �ṩmemset��strcmp ԭ��
#include <stdarg.h>     // �ṩ��va_list��va_start��va_arg��va_end
#include <stdlib.h>     // �ṩmalloc��realloc��free��exitԭ��
#include "Status.h"     //**��01 ����**//
#include "LinkQueue.h"  //**��03 ջ�Ͷ���**//

/*
 * ע��
 *
 * ͨ����������Ȩͼ�����Ϊ��ͼ������Ȩͼ�����Ϊ��������
 * ����ͼ/���еĶ����ϵ����Ϊ���ߡ�������ͼ/���еĶ����ϵ����Ϊ�������������ֻ�ͷ�뻡β��
 * ʵ�ʱ����У�δ�ػ��ϸ���������������
 *
 * ��ǰ�ṹ�ʺϴ洢����ͼ/����
 *
 * �� �����/������Ϣʱ�������ʵ���ǰ�"����"����ģ���ʹ�ò���Ļ��ǰ�"����"���еġ�
 */


/* �궨�� */
#define MAX_VERTEX_NUM 26                       // ��󶥵����


// ͼ������
// ͼ������
typedef enum {
    DG,     // 0-����ͼ���˴���֧��
    DN,     // 1-������(��Ȩֵ)���˴���֧��
    UDG,    // 2-����ͼ
    UDN     // 3-������(��Ȩֵ)
} GraphKind;


/* ����ͼ���ڽӶ��ر����Ͷ��� */
typedef enum {
    unvisit, visit
} VisitIf;

// ��������
typedef char VertexType;

// �ߵ���ظ�����Ϣ
typedef struct {
    /*
     * ע��
     * �̲��и����Ľṹֻ��������Ȩͼ����û������Ȩͼ(��)��
     * ����Ϊ�˰ѡ�����������Ҳ���ǽ�ȥ�����ڸ�����Ϣ��������"Ȩ��"���ԡ�
     */
    int weight;
} InfoType;

/* �߽�� */
typedef struct EBox {
    VisitIf mark;       // ���ʱ��
    int ivex;           // �ñ����������������λ��
    int jvex;           // �ñ����������������λ��
    struct EBox* ilink; // �ֱ�ָ�������������������һ����
    struct EBox* jlink; // �ֱ�ָ�������������������һ����
    InfoType* info;
} EBox;

// ÿ�������ͷ���
typedef struct VexBox {
    VertexType data;    // ������Ϣ
    EBox* firstedge;    // ָ���һ�������ö���ıߵ�ָ��
} VexBox;

/* ͼ���ڽӶ��ر�洢��ʾ���Ͷ��� */
typedef struct {
    VexBox adjmulist[MAX_VERTEX_NUM];   // ��ͷ����
    int vexnum, edgenum;                // ͼ/���Ķ������ͱ���
    GraphKind kind;                     // ͼ�����ͱ�־
} AMLGraph;


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
Status CreateGraph(AMLGraph* G, char* path[]);

/*
 * ��������ͼ
 */
static Status CreateUDG(AMLGraph* G);

/*
 * ����������
 */
static Status CreateUDN(AMLGraph* G);

/*
 * ¼��ߵ���ظ�����Ϣ
 */
static void Input(AMLGraph G, InfoType** info);

/*
 * ����
 *
 * �ڽӱ�洢��ͼ��Ҫ�ͷ��ڴ档
 */
Status DestroyGraph(AMLGraph* G);

/*
 * ����
 *
 * ���ض���u��ͼ/���е�λ��
 */
int LocateVex(AMLGraph G, VertexType u);

/*
 * ȡֵ
 *
 * ��������v���Ķ���ֵ
 */
VertexType GetVex(AMLGraph G, int v);

/*
 * ��ֵ
 *
 * ������v��ֵΪvalue
 */
Status PutVex(AMLGraph* G, VertexType v, VertexType value);

/*
 * �׸��ڽӵ�
 *
 * ���ض���v���׸��ڽӵ�
 */
int FirstAdjVex(AMLGraph G, VertexType v);

/*
 * ��һ���ڽӵ�
 *
 * ���ض���v��(�����w��)��һ���ڽӵ�
 */
int NextAdjVex(AMLGraph G, VertexType v, VertexType w);

/*
 * ���붥��
 *
 * ��ָ���Ķ���v׷�ӵ����㼯�У�δ�����ö�������������Ĺ�ϵ
 */
Status InsertVex(AMLGraph* G, VertexType v);

/*
 * ɾ������
 *
 * �Ӷ��㼯��ɾ��ָ���Ķ���v��ע����Ҫ������صĶ����ϵ
 */
Status DeleteVex(AMLGraph* G, VertexType v);

/*
 * ����һ���߽��(�����ڲ�ʹ��)
 */
static EBox* newEBoxPtr(VisitIf mark, int ivex, int jvex, EBox* ilink, EBox* jlink, InfoType* info);

/*
 * �����<v, w>
 *
 * ��ǰͼ/��������ģ�����������Ľṹ��ʹ�ò���һ����ʱֻ��Ҫ����һ�Զ����ϵ���ߵ�������Ȼ��һ��
 * ����ͼ/����˵�������ڿɱ�������г��ߵĸ�����Ϣ��
 *
 * ע���˴����յĲ�����MGraph��Щ��һ�������ĸ�����Ϣ�а����˸����ߵ�Ȩֵ��
 */
Status InsertArc(AMLGraph* G, VertexType v, VertexType w, ...);

/*
 * ɾ����<v, w>
 */
Status DeleteArc(AMLGraph* G, VertexType v, VertexType w);

/*
 * ������ȱ���(�˴������ݹ�ʵ��)
 */
void DFSTraverse(AMLGraph G, Status(Visit)(VertexType));

/*
 * ������ȱ������ĺ���
 */
static void DFS(AMLGraph G, int v);

/*
 * ������ȱ���(�˴���������ʵ��)
 */
void BFSTraverse(AMLGraph G, Status(Visit)(VertexType));

/*
 * ��ͼ�λ���ʽ�����ǰ�ṹ
 */
void PrintGraph(AMLGraph G);

#endif
