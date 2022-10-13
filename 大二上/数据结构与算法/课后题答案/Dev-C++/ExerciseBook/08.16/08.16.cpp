#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MemoryManager.h"

/*
 * �洢�����㷨
 *
 * ���㷨��ʵ�ֹ�����洢������ϢϢ��ء�
 * �˴��Ľ����㷨�ǽ������Լ�ʵ�ֵ�MemoryManager֮�ϵġ�
 * ����б�Ĵ洢����������ô�����㷨Ҳ��Ҫ��֮�ı䡣
 *
 * ���岽��������μ��̲ġ�
 */
void Algo_8_16(Space* space);

// �����ڴ��¼���׵�ַ���ڴ��¼��������ʱ�õ��ıȽ������÷��������ڲ�ʹ��
static int qsortCompar(const void* r1, const void* r2);

// ����һ���ڴ��¼�����������ڴ��¼ӵ�оɵ�ַoldAddr���÷��������ڲ�ʹ��
static int search(Space space, int oldAddr);

// ��ϰ��8.10���������ݽ��в���
void Test_8_10(Space* space, char* path);

// ʹ���Զ���Ĳ������ݣ����ﻹ���Բ����û������ı�����
void TestCustom(Space* space, int* p[]);


int main(int argc, char** argv) {

//    printf("=== ʹ��ϰ��8.10�еĲ������� ===\n\n");
//    {
//        Space space;
//
//        // ��ʼ��һƬ���õĴ洢
//        InitSpace(&space);
//        printf("��ʼ�ڴ沼�֣�\n");
//        PrintMemoryLayout(space);
//
//        // ����ϰ��8.10������
//        Test_8_10(&space, "TestData_8_10.md");
//        printf("ϰ��8.10�е��ڴ沼�֣�\n");
//        PrintMemoryLayout(space);
//
//        // �洢����
//        Algo_8_16(&space);
//        printf("���д洢��������ڴ沼�֣�\n");
//        PrintMemoryLayout(space);
//    }

    printf("=== ʹ���Զ���Ĳ������� ===\n\n");
    {
        Space space;
        int* p[10]; // �û�������(�����ַ)
        char* data = (char*)malloc(sizeof(char));

        // ��ʼ��һƬ���õĴ洢
        InitSpace(&space);
        printf("��ʼ�ڴ沼�֣�\n");
        PrintMemoryLayout(space);

        // �Զ�������
        TestCustom(&space, p);

        // �洢����
        Algo_8_16(&space);
        printf("���д洢��������ڴ沼�֣�\n");
        PrintMemoryLayout(space);

        printf("�����ڴ沼�֣���֤�û������Ƿ��Ѿ�ͬ�����£�\n");
        memmove(data, getPtr(space, p[9]), 1);
        printf("p10 = %d\n", *data);
        memmove(data, getPtr(space, p[6]), 1);
        printf("p7  = %d\n", *data);
        memmove(data, getPtr(space, p[7]), 1);
        printf("p8  = %d\n", *data);
        memmove(data, getPtr(space, p[5]), 1);
        printf("p6  = %d\n", *data);
        memmove(data, getPtr(space, p[8]), 1);
        printf("p9  = %d\n", *data);
    }

}


/*
 * �洢�����㷨
 *
 * ���㷨��ʵ�ֹ�����洢������ϢϢ��ء�
 * �˴��Ľ����㷨�ǽ������Լ�ʵ�ֵ�MemoryManager֮�ϵġ�
 * ����б�Ĵ洢����������ô�����㷨Ҳ��Ҫ��֮�ı䡣
 *
 * ���岽��������μ��̲ġ�
 */
void Algo_8_16(Space* space) {
    Record* r;
    int len;
    int i, j, k, count;
    int busy, free;
    int* oldPtr;    // ��¼�ɵ������ַ

    // ��ǰ�������ڴ�ʹ�ü�¼����
    len = ListLength(space->recordList);

    /* 0. ���ڴ��¼����������������ں������ڴ�����Ǩ�� */
    qsort(space->recordList.elem, len, sizeof(ElemType), qsortCompar);

//    printf("��־0. ���ڴ��¼�����������ˣ�ֻ����˶��׵�ַ��˳�򣩣�\n");
//    PrintMemoryLayout(*space);


    /* 1. ȷ�������洢�����󣬸��ڴ����µ�ַ�����仰˵�������˲��裬��������һ���¾ɵ�ַ���ձ� */

    free = 0;   // ͳ�ƿ��п�Ĵ�С
    busy = 0;   // ͳ��ռ�ÿ�Ĵ�С����ȷ����ռ�ÿ���µ�ַ
    count = 0;  // ͳ�ƽ�������ڴ������
    j = 0;

    for(i = 1; i <= len; i++) {
        GetElem(space->recordList, i, (ElemType*) &r);

        // ���Կ��п飬����Ҫͳ�����Ĵ�С
        if(r->tag == 0) {
            free += r->size;
            continue;
        }

        // ��ͳ��ռ�ÿ�����
        count++;

        // �ռ�ռ�ÿ飬�������ַ��Ϣ
        r->oldAddr = r->addr;
        r->addr = busy;
        busy += r->size;

        // ���µ�ռ�ÿ���Ϣ���е�����ǰ��
        space->recordList.elem[j++] = r;
    }

    // ��¼���п����Ϣ
    if(free != 0) {
        // �������·����ڴ�
        r = (Record*) malloc(sizeof(Record));
        r->addr = busy;
        r->size = free;
        r->tag = 0;
        r->oldAddr = -1;

        space->recordList.elem[j] = r;

        count++;

        // ָ�����µĿ��п�ļ�¼
        space->cur = count;
    }

    // �ڴ�ʹ�ü�¼���³���
    space->recordList.length = count;

//    printf("��־1. �����¾ɵ�ַ���ձ����ˣ�ֻ�����\"ռ��\"�ڴ��ǰ�ƣ��Լ�\"����\"�ڴ�ĺϲ�����\n");
//    PrintMemoryLayout(*space);


    /* 2. ����û����������������ַ���Ա����֮��ı��������������� */

    // �û���������
    len = ListLength(space->ptrList);

    for(i = 0; i < len; i++) {
		// ע��C++�е�ǿ������ת����ʽ
        oldPtr = static_cast<int*>(space->ptrList.elem[i]);

        // ��ȡ�ɵ�ַ���ڴ��¼���е�����
        k = search(*space, *oldPtr);

        // ����Ϊ�µ�ַ
        *oldPtr = ((Record*) (space->recordList.elem[k]))->addr;
    }

//    printf("��־2. �û������������ɣ����ˣ��û�����(�����ַָ��)�Ѿ�ָ������ȷ���ڴ棬����������ʾ����������\n");
//    PrintMemoryLayout(*space);


    /* 3. ������ӣ�����ǰ���ͺ�� */

    len = ListLength(space->recordList);

    for(i = 1; i <= len; i++) {
        GetElem(space->recordList, i, (ElemType*) &r);

        // �������п�ʱ�����Խ���ѭ����
        if(r->tag==0) {
            break;
        }

        if(r->pre != -1) {
            k = search(*space, r->pre);
            r->pre = ((Record*) (space->recordList.elem[k]))->addr;
        }

        if(r->next != -1) {
            k = search(*space, r->next);
            r->next = ((Record*) (space->recordList.elem[k]))->addr;
        }
    }

//    printf("��־3. �ڴ��¼�е�ǰ���ͺ���Ѿ�����������ʾ��\n");
//    PrintMemoryLayout(*space);


    /* 4. Ǩ���û����� */

    for(i = 1; i <= len; i++) {
        GetElem(space->recordList, i, (ElemType*) &r);

        // ������Ŀ��м�¼һ�����������ģ������������м�¼ʱ���Ϳ��Խ���ѭ����
        if(r->tag == 0) {
            // ���õ�ַ��Ӧ���ڴ洦������Ĩ��(���Ǹ���ѡ����)
            memset(getPtr(*space, &(r->addr)), 0, r->size * BYTE);
            break;
        }

        // ����¾ɵ�ַһ����������Ǩ������
        if(r->addr == r->oldAddr) {
            continue;
        }

        memmove(space->base + r->addr * BYTE, space->base + r->oldAddr * BYTE, r->size);
    }

//    printf("��־4. ����Ǩ����ɣ����ˣ�����������ʾ���в������û����ݣ�\n");
//    PrintMemoryLayout(*space);

}

// ʹ���Զ���Ĳ������ݣ����ﻹ���Բ����û������ı�����
void TestCustom(Space* space, int* p[]) {

    printf("+ Ϊ p1 ����10���ڴ棬������ڴ���д������ 1 ...\n");
    p[0] = AllocMemory(space, 10);
    memset(getPtr(*space, p[0]), 1, 1);
    PrintMemoryLayout(*space);

    printf("+ Ϊ p2 ����50���ڴ棬������ڴ���д������ 2 ...\n");
    p[1] = AllocMemory(space, 50);
    memset(getPtr(*space, p[1]), 2, 1);
    PrintMemoryLayout(*space);

    printf("+ Ϊ p3 ����20���ڴ棬������ڴ���д������ 3 ...\n");
    p[2] = AllocMemory(space, 20);
    memset(getPtr(*space, p[2]), 3, 1);
    PrintMemoryLayout(*space);

    printf("- �ͷ� p2 ����50���ڴ�...\n");
    FreeMemory(space, p[1]);
    PrintMemoryLayout(*space);

    printf("+ Ϊ p4 ����5���ڴ棬������ڴ���д������ 4 ...\n");
    p[3] = AllocMemory(space, 5);
    memset(getPtr(*space, p[3]), 4, 1);
    PrintMemoryLayout(*space);

    printf("+ Ϊ p5 ����10���ڴ棬������ڴ���д������ 5 ...\n");
    p[4] = AllocMemory(space, 10);
    memset(getPtr(*space, p[4]), 5, 1);
    PrintMemoryLayout(*space);

    printf("- �ͷ� p4 ����5���ڴ�...\n");
    FreeMemory(space, p[3]);
    PrintMemoryLayout(*space);

    printf("- �ͷ� p3 ����20���ڴ�...\n");
    FreeMemory(space, p[2]);
    PrintMemoryLayout(*space);

    printf("+ Ϊ p6 ����15���ڴ棬������ڴ���д������ 6 ...\n");
    p[5] = AllocMemory(space, 15);
    memset(getPtr(*space, p[5]), 6, 1);
    ((Record*)(space->recordList.elem[2]))->pre = 25;
    ((Record*)(space->recordList.elem[2]))->next = 0;
    PrintMemoryLayout(*space);

    printf("+ Ϊ p7 ����10���ڴ棬������ڴ���д������ 7 ...\n");
    p[6] = AllocMemory(space, 10);
    memset(getPtr(*space, p[6]), 7, 1);
    ((Record*)(space->recordList.elem[4]))->pre = 60;
    ((Record*)(space->recordList.elem[4]))->next = -1;
    PrintMemoryLayout(*space);

    printf("+ Ϊ p8 ����15���ڴ棬������ڴ���д������ 8 ...\n");
    p[7] = AllocMemory(space, 15);
    memset(getPtr(*space, p[7]), 8, 1);
    ((Record*)(space->recordList.elem[7]))->pre = -1;
    ((Record*)(space->recordList.elem[7]))->next = 15;
    PrintMemoryLayout(*space);

    printf("- �ͷ� p5 ����10���ڴ�...\n");
    FreeMemory(space, p[4]);
    PrintMemoryLayout(*space);

    printf("+ Ϊ p9 ����5���ڴ棬������ڴ���д������ 9 ...\n");
    p[8] = AllocMemory(space, 5);
    memset(getPtr(*space, p[8]), 9, 1);
    ((Record*)(space->recordList.elem[3]))->pre = 15;
    ((Record*)(space->recordList.elem[3]))->next = 60;
    PrintMemoryLayout(*space);

    printf("- �ͷ� p1 ����10���ڴ�...\n");
    FreeMemory(space, p[0]);
    PrintMemoryLayout(*space);

    printf("+ Ϊ p10 ����5���ڴ棬������ڴ���д������ 10 ...\n");
    p[9] = AllocMemory(space, 5);
    memset(getPtr(*space, p[9]), 10, 1);
    ((Record*)(space->recordList.elem[0]))->pre = -1;
    ((Record*)(space->recordList.elem[0]))->next = -1;
    PrintMemoryLayout(*space);

}

// ��ϰ��8.10���������ݽ��в���
void Test_8_10(Space* space, char* path) {
    FILE* fp;

    char line[100]; // �����ȡ������
    char* p;        // ָ��ֽ����������

    Record* record;

    // ÿ�ж�ȡ��������
    int addr;
    int size;
    int tag;
    int pre;
    int next;

    // ��¼�����ַ
    int* free[100];
    int* ptr;

    int count;
    int i;
    
    char data;  // ������֤����Ǩ�ƵĲ�������

    fp = fopen(path, "r");

    // û����Ч���ݣ���ֱ�ӷ��ؿյ�˳���
    if(fp == NULL) {
        return;
    }

    // �������ڱ�ͷ��ǰ����
    fgets(line, 100, fp);
    fgets(line, 100, fp);

    count = 0;
    i = 0;
    data = 0;

    // ���û�е����ļ�β����һֱ��ȡ
    while(fgets(line, 100, fp)!=NULL) {
        // �׵�ַ
        p = strtok(line, " |\n\r");
        addr = atoi(p);

        // ���С
        p = strtok(NULL, " |\n\r");
        size = atoi(p);

        // ��־��
        p = strtok(NULL, " |\n\r");
        tag = atoi(p);

        // ǰ����ַ
        p = strtok(NULL, " |\n\r");
        pre = atoi(p);

        // ��̵�ַ
        p = strtok(NULL, " |\n\r");
        next = atoi(p);

        // ����size���ڴ�
        ptr = AllocMemory(space, size);

        // ��ȡ�ոմ������ڴ��¼��ָ�룬���ǰ���ͺ�̵ĳ�ʼ��
        // ע��C++�е�ǿ������ת����ʽ
        record = static_cast<Record*>(space->recordList.elem[i++]);
        record->pre = pre;
        record->next = next;

        /*
         * Ϊ�ո�������ڴ渳ֵ������Ϊ�˲��Ժ���������Ǩ���Ƿ�ɹ���
         * ע�����︳ֵʱҪ�������ַת��Ϊ��ʵ��ַ��
         */
        memset(getPtr(*space, ptr), ++data, 1);

        if(tag == 0) {
            // �õ�ַ�����ڴ������Ҫ�ͷ�
            free[count++] = ptr;
        }
    }

    fclose(fp);

    // �ͷ��ڴ�
    for(i = 0; i < count; i++) {
        FreeMemory(space, free[i]);
    }
}

// �����ڴ��¼���׵�ַ���ڴ��¼��������ʱ�õ��ıȽ������÷��������ڲ�ʹ��
static int qsortCompar(const void* r1, const void* r2) {
    Record* record1 = *((Record**) r1);
    Record* record2 = *((Record**) r2);

    return record1->addr - record2->addr;
}

/*
 * ����һ���ڴ��¼�����������ڴ��¼ӵ�оɵ�ַoldAddr
 *
 * ע�����������ʵ�ܵ�Ч����Ϊ��
 * �������ȣ�������ұ�����˳����ң�Ч�ʲ��ߣ�
 * ������Σ�������һᱻ�����ظ����ã���������Ч�ʵ�Ч��
 * �������õ��㷨��ʹ�ú���ѧ���Ĺ�ϣ�����¾ɵ�ַ�洢����ϣ���лἫ��ؼӿ�����ٶȡ�
 *
 * �÷��������ڲ�ʹ��
 */
static int search(Space space, int oldAddr) {
    int k;

    for(k = 0; k < space.recordList.length; k++) {
        // �ҵ���ƥ��ľɵ�ֵַ
        if(oldAddr == ((Record*) (space.recordList.elem[k]))->oldAddr) {
            return k;
        }
    }

    return -1;
}

