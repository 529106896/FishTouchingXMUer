#include <stdio.h>
#include "Status.h"
#include "SqStack.h"

/* �궨�� */
#define MAXSIZE 200 // �ڴ��ܴ�С


/* ���пռ����Ͷ��� */
typedef struct {
    void* base;     // ���ÿռ��ڴ����ʼ��ַ
    int size;       // ���пռ��С(���ֽڼ���)
    SqStack block;  // �Ѿ�ʹ�õ��ڴ���С����������ڴ���Ϣ����ջ
} Space;


// ��ʼ���ڴ�ռ估�ڴ���Ϣջ
void InitSpace(Space* space);

// ��ӡ�ڴ沼�֣��鿴��ǰ�ڴ��ʹ�����
void PrintMemoryLayout(Space space);

// �����СΪn���ڴ�飬�������뵽���ڴ���ʼ��ַ
void* Algo_8_11(Space* space, int n);

// �����ڴ棬��ѭ"�������������ͷ�"��ԭ��
Status Algo_8_12(Space* space);


int main(int argc, char* argv[]) {
    Space space;
    int s[5] = {50, 50, 150, 100, 50}; // �����ڴ���������
    int i;

    // ��ʼ���ڴ�
    InitSpace(&space);
    PrintMemoryLayout(space);
    printf("\n");

    // ����/�ͷ��ڴ�
    for(i = 0; i < 5; i++) {
        printf("���� %d ���ڴ��...\n", s[i]);
        Algo_8_11(&space, s[i]);
        PrintMemoryLayout(space);
        printf("\n");
    }

    return 0;
}


// ��ʼ��һ����пռ�
void InitSpace(Space* space) {
    // ����MAX�ֽڵĿռ�(�������ܳ�ʼ���ɹ�)
    space->base = malloc(MAXSIZE);
    space->size = MAXSIZE;

    // ��ʼ���ڴ���Ϣջ
    InitStack(&(space->block));
}

// ��ӡ�ڴ沼�֣��鿴��ǰ�ڴ��ʹ�����
void PrintMemoryLayout(Space space) {
    int i;

    for(i = 1; i <= MAXSIZE; i++) {
        if(i <= space.size) {
            printf("��");
        } else {
            printf("��");
        }

        // Ԥ��ÿ��20����һ����
        if(i % 20 == 0) {
            printf("\n");
        }
    }

    if(MAXSIZE % 20 != 0) {
        printf("\n");
    }
}

// �����СΪn���ڴ�飬�������뵽���ڴ���ʼ��ַ
void* Algo_8_11(Space* space, int n) {

    /*
     * ������õ��ڴ���������������ڴ�������
     * ����Ҫ�ͷ��������ʹ�õ��ڴ����ڳ��ռ䡣
     */
    while(space->size < n && Algo_8_12(space) == OK) {
        // ֱ�������ڴ���������Ҫ�󣬻���ȫ��ռ���ڴ��Ѿ��ͷţ��Ż��˳�ѭ��
    }

    // ���û���㹻���ڴ���ã��򷵻ؿ�ָ��
    if(space->size < n) {
        return NULL;
    }

    // ���ÿռ��С
    space->size -= n;

    // ���³ɹ����뵽���ڴ�
    Push(&(space->block), n);

    // �������뵽���ڴ���ʼ��ַ
    return space->base + space->size;
}

// �����ڴ棬��ѭ"�������������ͷ�"��ԭ��
Status Algo_8_12(Space* space) {
    int e;

    // �Ѿ�û�п��ͷ��ڴ�ʱ������ERROR
    if(StackEmpty(space->block)) {
        return ERROR;
    }

    // �����������ڴ��ͷŵ�
    Pop(&(space->block), &e);

    // ���ÿռ�����
    space->size += e;

    return OK;
}

