#include <stdio.h>
#include "BuddySystem.h"    //**��08 ��̬�洢����**//

/*
 * ���ϵͳ���ڴ�����㷨
 *
 * ��ָ��p�����ڴ�����ͷ�(��������free()��ֻ�Ƕ��ڴ�����ͷŲ����������ÿ�ָ��p�Ĳ�����Ӧ�������÷����)
 *
 * ע������û����֤p��ȡֵ�����÷�Ӧ��ȷ��p�ںϹ�ķ�Χ
 */
void Algo_8_14(FreeList avail, WORD* p);


int main(int argc, char* argv[]) {
    FreeList avail;
    WORD* p[8];     // ��¼���뵽���ڴ��ָ��
    int s[8] = {4, 5, 6, 7, 1, 5, 3, 9};    // ����Ŀռ��С
    int i;

    printf("���������������� InitSpace \n");
    {
        printf("��ʼ��һ���ڴ��...\n");
        InitSpace(avail);
        PrintMemoryLayout();
        printf("\n");
    }
    PressEnterToContinue(debug);

    printf("���������������� AllocBuddy \n");
    {
        for(i = 0; i < 8; i++) {
            printf("�����СΪ %d ���ֵ��ڴ��...\n", s[i]);
            p[i] = AllocBuddy(avail, s[i]);
            PrintMemoryLayout();
            printf("\n");
        }
    }
    PressEnterToContinue(debug);

    printf("���������������� FreeBuddy \n");
    {
        // ����һ��ָ�����˳��
        int a[8] = {2, 0, 5, 7, 1, 4, 3, 6};

        for(i = 0; i < 8; i++) {
            Algo_8_14(avail, p[a[i]]);
            PrintMemoryLayout();
            printf("\n");
        }
    }
    PressEnterToContinue(debug);

    return 0;
}


/*
 * ���ϵͳ���ڴ�����㷨
 *
 * ��ָ��p�����ڴ�����ͷ�(��������free()��ֻ�Ƕ��ڴ�����ͷŲ����������ÿ�ָ��p�Ĳ�����Ӧ�������÷����)
 *
 * ע������û����֤p��ȡֵ�����÷�Ӧ��ȷ��p�ںϹ�ķ�Χ
 */
void Algo_8_14(FreeList avail, WORD* p) {
    FreeBuddy(avail, p);
}

