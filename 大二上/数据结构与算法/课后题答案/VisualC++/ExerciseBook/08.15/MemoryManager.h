/*=======================
 * �洢����������ϰ��8.15
 ========================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H


/* �궨�� */
#define MAXSIZE 100 // �ڴ�������
#define e 5         // ����ռ�ʱ�õ����ݲ�


/*
 * �ڴ�"��"�����Ͷ���
 *
 * ��ν"��"��ָ�ռ�������С��λ���������ֽڡ�
 * һ��"��"�ж��ȡ���ڶ�"��"�ṹ����ζ���ġ�
 */
typedef struct WORD {
    int tag;            // ���־��0���У�1ռ��
    int cellsize;       // ��ǰ��Ĵ�С
    struct WORD* next;  // ָ����һ�����п�
    
    
    /*
     * ʹ�ñ�ǣ�0������У�1����ռ�ã�-1������Ȼ���У����ǲ��ڿ��������С�
     * �����ǽ��������Դ�ӡ���ܣ���û������ʵ���Ե��ô���
     */
    int flag;
} WORD;

// "��"�ռ�
typedef struct {
    struct WORD* lowbound;  // �ռ��½�
    struct WORD* highbound; // �ռ��Ͻ�
    struct WORD* avail; // ָ����ÿռ�����
} Space;


// ��ʼ��һƬ���õĴ洢
void InitSpace(Space* space);

// �����СΪn���ڴ棬������ָ����ڴ�������ַ
WORD* AllocMemory(Space* space, int n);

// �ͷ�ָ��p�����ڴ�
void FreeMemory(Space* space, WORD* p);

// ��ӡ�ڴ沼��
void PrintMemoryLayout(Space space);

#endif
