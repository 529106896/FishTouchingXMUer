/*=======================
 * �洢����������ϰ��8.15
 ========================*/

#include "MemoryManager.h"

// ��ʼ��һƬ���õĴ洢
void InitSpace(Space* space) {
    space->avail = (WORD*) malloc(MAXSIZE * sizeof(WORD));
    space->avail->tag = 0;
    space->avail->cellsize = MAXSIZE;
    space->avail->next = NULL;

    space->lowbound = space->avail;
    space->highbound = space->avail + MAXSIZE;
}

// �����СΪn���ڴ棬������ָ����ڴ�������ַ
WORD* AllocMemory(Space* space, int n) {
    WORD* p, * q;

    if(space->avail == NULL) {
        return NULL;
    }

    p = space->avail;
    q = NULL;

    // �����һ�����п鲻��������
    if(p->cellsize < n) {
        // �������������Ŀ����ڴ�
        while(p != NULL && p->cellsize < n) {
            q = p;
            p = p->next;
        }
    }

    // û�з��������Ŀ����ڴ�
    if(p == NULL) {
        return NULL;
    }

    // ���ݲΧ�ڣ����������
    if(p->cellsize - e <= n) {
        if(q == NULL) {
            space->avail = p->next;
        } else {
            q->next = p->next;
        }

        // �ָ���п�
    } else {

        if(q == NULL) {
            space->avail += n;
            space->avail->tag = 0;
            space->avail->cellsize = p->cellsize - n;
            space->avail->next = p->next;
        } else {
            q->next = p + n;
            q->next->tag = 0;
            q->next->cellsize = p->cellsize - n;
        }

        p->cellsize = n;
    }

    // ���Ϊռ��
    p->tag = 1;

    return p;
}

// �ͷ�ָ��p�����ڴ�
void FreeMemory(Space* space, WORD* p) {
    p->tag = 0; // �򵥵ر��Ϊ���У��Դ���������
}

// ��ӡ�ڴ沼��
void PrintMemoryLayout(Space space) {
    int i, count;
    WORD* p;

    // �������п�
    for(p = space.lowbound; p < space.highbound; p += p->cellsize) {
        if(p->tag == 0) {
            p->flag = -1;  // ��ʱ���Ϊ"������"�Ŀ��п�
        } else {
            p->flag = 1;   // ���Ϊռ��
        }
    }

    // �������п�����
    for(p = space.avail; p != NULL; p = p->next) {
        p->flag = 0;       // ����Ϊ"����"�Ŀ��п�
    }

    count = 0;

    for(p = space.lowbound; p < space.highbound; p += p->cellsize) {
        for(i = 0; i < p->cellsize; i++) {
            switch(p->flag) {
                case -1:
                    printf("��");
                    break;
                case 0:
                    printf("��");
                    break;
                case 1:
                    printf("��");
                    break;
                default:
                    printf("����ı�ǣ�\n");
                    return;
            }

            count++;
            // ÿ��20���ֻ�һ����
            if(count % 20 == 0) {
                printf("\n");
            }
        }

    }

    if(count % 20 != 0) {
        printf("\n");
    }

    printf("\n");
}

