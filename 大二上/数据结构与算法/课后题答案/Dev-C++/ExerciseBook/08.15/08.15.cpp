#include <stdio.h>
#include "MemoryManager.h"

/*
 * �ڴ�����
 *
 * �����п��ռ����������ӳ�һ�����п�����
 */
void Algo_8_15(Space* space);


int main(int argc, char** argv) {
    Space space;
    int i;
    int a[11] = {10, 20, 30, 15, 20, 5, -1, -3, 0, 15, 10};
    WORD* p[11];

    InitSpace(&space);
    printf("��ʼ�ڴ沼�֣�\n");
    PrintMemoryLayout(space);

    /*
     * ע��
     * ����a[4]ʱ����ʣ25��"��"����ǰ�ݲ���5����˱��λ�ֱ�ӷ���20+5=25��"��"
     * ����a[5]ʱ���Ѿ�û�п��õ��֣���������ʧ��
     * ����a[10]ʱ�������ݲΧ�ڣ����������
     */
    for(i = 0; i < 11; i++) {
        if(a[i] > 0) {
            printf("+ ���� %d ���ֵĴ洢\n", a[i]);
            p[i] = AllocMemory(&space, a[i]);
        } else {
            printf("- �ͷ� %d ���ֵĴ洢\n", a[-a[i]]);
            FreeMemory(&space, p[-a[i]]);
        }

        PrintMemoryLayout(space);

        if(i == 8) {
            printf("�ڴ�����...\n");
            Algo_8_15(&space);
            PrintMemoryLayout(space);
        }
    }
}


/*
 * �ڴ�����
 *
 * �����п��ռ����������ӳ�һ�����п�����
 */
void Algo_8_15(Space* space) {
    WORD* p, * q;

    space->avail = NULL;

    q = NULL;

    // ����������
    for(p = space->lowbound; p < space->highbound; p += p->cellsize) {
        if(p->tag == 1) {
            continue;
        }

        // �ȰѺ���ÿ�
        p->next = NULL;

        // �����˵�һ�����п�
        if(space->avail == NULL) {
            space->avail = p;
            q = p;
            continue;
        }

        // ����������п��ַ�����ڣ����������
        if(q + q->cellsize != p) {
            q->next = p;

            // ���ڵ�ַ���ڵĿ��п飬Ҫ�ϲ�
        } else {
            q->cellsize += p->cellsize;
        }
    }
}

