/*=======================
 * �洢����������ϰ��8.16
 ========================*/

#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SqList.h"


#define MAXSIZE 100     // ����ڴ���
#define e 0             // �ݲ�

#define BYTE sizeof(char)   // 1���ֽ�


// �ڴ��¼���Ͷ���
typedef struct {
    int addr;   // �µ�ַ�򣬴洢�ڴ��ĵ�ǰ���µ�ַ����ʼֵ�ǿռ��׵�ַ
    int size;   // ���С
    int tag;    // ��־��ָʾ�ڴ�������ʹ��(1)���ǿ���״̬(0)

    /* �洢��֮������ӹ�ϵ�������û��������ַ�㿴�������ӹ�ϵ���ܲ���һ�� */
    int pre;    // ǰ��
    int next;   // ���

    int oldAddr; // ���д洢������ľɵ�ַ
} Record;

// ���ÿռ����Ͷ���
typedef struct {
    void* base;          // �ڴ���ʼ��ַ
    SqList recordList;   // �ڴ�ʹ�ü�¼
    int cur;             // ��¼���п���ڴ��¼��λ�ã���ֵΪ1

    /*
     * ��¼�����ַ��
     * ����ʵ����ģ�����ϵͳ����Ϊ��
     * �û�ʹ�õĵ�ַ��Ӳ����ʵ�ʵ�ַ���ܲ���һ�£�������Ҫ����ϵͳ����һ�������ַ����
     */
    SqList ptrList;
} Space;


// ��ʼ��һƬ���õĴ洢
void InitSpace(Space* space);

// �����СΪn���ڴ棬������ָ����ڴ�������ַ
int* AllocMemory(Space* space, int n);

// �ͷ������ַp�����ڴ�
void FreeMemory(Space* space, int* p);

// �������ַaddrת��Ϊ�ײ����ʵ��ַ
void* getPtr(Space space, const int* addr);

// ��ӡ�ڴ沼�֣���ʾ��ʽΪ���׵�ַ ���С ��־�� | ǰ�� ��� | ����
void PrintMemoryLayout(Space space);

#endif

