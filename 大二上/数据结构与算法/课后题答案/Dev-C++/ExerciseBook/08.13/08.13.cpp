#include <stdio.h>
#include "BoundaryTagMethod.h"      //**��08 ��̬�洢����**//

/*
 * �߽��ʶ�����ڴ�����㷨
 *
 * ��ָ��p�����ڴ�����ͷ�
 */
void Algo_8_13(Space* pav, Space p);


int main(int argc, char* argv[]) {
    Space pav;
    Space p[12];    // ��¼���뵽���ڴ��ָ��
    int s[12] = {10, 20, 30, 50, 5, 15, 10, 5, 15, 15, 2, 20};  // ����Ŀռ��С
    int i = 0;

    printf("���������������� InitSpace \n");
    {
        int max = 200;  // ��ֵ����Ϊ20�ı�����Ŀ���Ǵ�ӡ�������Զ���

        printf("��ʼ������ %d ��\"��\"���ڴ��󣬵�ǰ�ڴ沼��Ϊ��\n", max);
        pav = InitSpace(max);
        PrintMemoryLayout();
        printf("\n");
    }
    PressEnterToContinue(debug);

    printf("���������������� AllocBoundTag \n");
    {
        for(i = 0; i < 12; i++) {
            printf("�������� %2d> ���� %d ��\"��\"���ڴ�󣬵�ǰ�ڴ沼��Ϊ��\n", i + 1, s[i]);
            p[i] = AllocBoundTag(&pav, s[i]);
            PrintMemoryLayout();
            printf("\n");
        }
    }
    PressEnterToContinue(debug);

    printf("���������������� FreeBoundTag \n");
    {
        // ����һ��ָ�����˳��
        int a[10] = {7, 3, 10, 6, 8, 5, 11, 1, 0, 4};

        for(i = 0; i < 10; i++) {
            printf("���� p%d ָ����ڴ�...\n", a[i] + 1);
            Algo_8_13(&pav, p[a[i]]);
            PrintMemoryLayout();
            printf("\n");
        }
    }
    PressEnterToContinue(debug);

    return 0;
}


/*
 * �߽��ʶ�����ڴ�����㷨
 *
 * ��ָ��p�����ڴ�����ͷ�
 */
void Algo_8_13(Space* pav, Space p) {
    FreeBoundTag(pav, p);
}

