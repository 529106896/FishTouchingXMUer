/*==============
 * ���ϵͳ
 *
 * �����㷨: 8.2
 ===============*/

#include "BuddySystem.h"

// ��¼�ڴ����ʼ��ַ���ڼ������ʱ����Ҫ�õ�
WORD* start;


/*
 * ��ʼ��һ���СΪ2^M���ֵ��ڴ棬������ָ����ڴ������ָ��
 * ע�����صĳ�ʼ�ڴ��Ѿ�������head��
 */
void InitSpace(FreeList avail) {
    int k;
    WORD* r;

    // ����M+1��Ԫ��
    for(k = 0; k <= M; k++) {
        avail[k].nodesize = (int) pow(2, k);
        avail[k].first = NULL;
    }

    r = (WORD*) malloc((int) pow(2, M) * sizeof(WORD));
    if(r == NULL) {
        exit(OVERFLOW);
    }

    // ����ͷ����Ϣ
    r->llink = r->rlink = r;
    r->tag = 0;
    r->kval = M;

    avail[M].first = r;

    start = r;
}

/*
 * ���������������� �㷨8.2 ����������������
 *
 * ���ϵͳ���ڴ�����㷨
 *
 * �ӿռ�avail������һ���С����Ϊn(ԭʼֵ)�Ŀռ䣬������ָ�����뵽�Ŀռ��ָ�롣�������ʧ�ܣ��򷵻�NULL��
 *
 * ע��
 * 1.��������״���Ϸ�����һ���������������ڴ��ͽ��з��������
 * 2.�����������n���ֵĿռ䣬ָ�����û������ԭʼ�ռ䡣
 *   ʵ��������ʱ����Ҫ���ǵ�ÿ����ǰ����1���ֵ�head��Ϣ�������������ʵ����Ҫ����(n+1)���֡�
 *   �����n���㷨8.1�����n���������෴����Ҫע�⡣
 */
WORD* AllocBuddy(FreeList avail, int n) {
    int k, i;
    WORD* pa, * pre, * suc, * pi;

    /*
     * ����һ���жϣ���������Ŀռ�����С��1����ֱ�ӷ��ء�
     */
    if(n < 1) {
        printf("��־������ʧ�ܣ������\"��\"��Ӧ����С��1\n");
        return NULL;
    }

    // ���Ҳ�С��n�Ŀ��п�
    for(k = 0; k <= M && (avail[k].nodesize < n + 1 || !avail[k].first); k++) {
    }

    // �Ҳ������ʵĿ��п飬���ؿ�ָ��
    if(k > M) {
        printf("��־������ʧ�ܣ�û���㹻�Ŀ��п�\n");
        return NULL;
    }

    pa = avail[k].first; // ָ��ɷ����ӱ�ĵ�һ�����
    pre = pa->llink;     // �ֱ����ǰ���ͺ��
    suc = pa->rlink;

    // ����˴�����һ�����п飬��������ӱ��Ϊ��
    if(pa == suc) {
        avail[k].first = NULL;

        // ���򣬴�����ͷ��ժ��һ�����õĿ��п飬�����ӱ�ͷָ��ָ����һ�����п�
    } else {
        pre->rlink = suc;
        suc->llink = pre;
        avail[k].first = suc;
    }

    /*
     * ��k-1����ʼ�������FreeList���飬���������ʣ��Ŀ��п顣
     * ʣ��Ŀ��п��Ƕ�ʣ����ÿռ�Ĳ�֡�
     *
     * �����õ�һ����ʽ��2^m-2^n = 2^n+2^(n+1)+...+2^(m-1)
     * �����ʼ����Ϊ2^16����ʱ�ܹ�����1500���֣���ô��Ҫ����һ��2^11�Ŀ��п������
     * ������֮��ʣ�������Ϊ��2^16-2^11 = 2^11+2^12+2^13+2^14+2^15��
     * ��Щʣ���������Բ��Ϊ5�����п飬�ֱ�洢��15��14��13��12��11�������������
     */
    for(i = 1; k - i >= 0 && avail[k - i].nodesize >= n + 1; i++) {
        pi = pa + (int) pow(2, k - i);  // ÿ�ν�piָ��ʣ��ռ�ĺ�һ��
        pi->rlink = pi->llink = pi;     // ��ʼ��pi��ǰ���ͺ��
        pi->tag = 0;                    // ���Ϊ���п�
        pi->kval = k - i;               // ���øÿ��������־����ʵ����Ϊ2^(k-i)
        avail[k - i].first = pi;

        /*
         * ע��
         * ����ֽ������piֱ����ӵ���avail�У���û�п���ͬλ�ô��᲻���б��������ͬ�Ŀ��п顣
         * ���ﲻ��Ҫ���ǵ�ԭ�������ͬλ�ô��Ѿ����ڱ��������ͬ�Ŀ��п飬
         * ��ô�����������Ҫ�ֽ�ʣ��ռ䣬���仰˵�������ѭ������������
         * ֻҪ�������ѭ����˵��Ŀ��λ�ô��Ѿ�Ϊ���ˣ�û���ҵ����ʵĿ��п飬������Ž�һ������α괦Ѱ�ҿ��п顣
         */
    }

    // ���ʣ�µ��ǰ�Ŀռ������Ҫ����Ŀռ�(����û������pa��ǰ���ͺ�̣���Ϊû��Ҫ)
    pa->tag = 1;
    pa->kval = k - (--i);

    printf("��־������ɹ����û����� %d ���֣�ϵͳ���� %d ���֣�ʵ�ʷ��� %d ����\n", n, n + 1, (int) pow(2, pa->kval));

    return pa;
}

/*
 * ���ϵͳ���ڴ�����㷨
 *
 * ��ָ��p�����ڴ�����ͷ�(��������free()��ֻ�Ƕ��ڴ�����ͷŲ����������ÿ�ָ��p�Ĳ�����Ӧ�������÷����)
 *
 * ע������û����֤p��ȡֵ�����÷�Ӧ��ȷ��p�ںϹ�ķ�Χ
 */
void FreeBuddy(FreeList avail, WORD* p) {
    int k;
    WORD* r;
    WORD* buddy = Buddy(p);

    if(p == NULL) {
        return;
    }

    /*
     * ���ｫp���򵥵ز��뵽avail�У������������Σ�
     * 1.����ǿ���
     * 2.�����У����ǻ��Ĵ�С��p�Ĵ�С��һ�£�˵����黹ûƴ�Ϻ�
     * 3.pƴ�ӳ������һ�����Ŀ��п�
     */
    if(buddy->tag == 1 || buddy->kval != p->kval || p->kval == M) {
        for(k = 0; k <= M && k < p->kval; k++) {
            // ����p���Ӧ������Ĳ��
        }

        // �ҵ���ۣ�����ͷ�巨�����п���뵽Ŀ����
        if(k <= M && k == p->kval) {
            p->tag = 0;

            if(avail[k].first == NULL) {
                p->llink = p->rlink = p;
            } else {
                p->llink = avail[k].first->llink;
                p->rlink = avail[k].first;
                p->llink->rlink = p;
                p->rlink->llink = p;
            }

            avail[k].first = p;

            printf("��־�����ճɹ���[%d, (2^%d)]������ %d �Ŀ��п�������\n", (int) (p - start), k, k);
        }

        // ��������ǿ��еģ���ʱӦ�����кϲ�����
    } else {
        for(k = 0; k <= M && k < p->kval; k++) {
            // ���һ������ڵĲ��
        }

        // �ҵ���ۣ�������ӿ��п�������ժ����
        if(k <= M && k == p->kval) {
            // ����������һ��λ��
            if(avail[k].first == buddy) {
                buddy->rlink->llink = buddy->llink;
                buddy->llink->rlink = buddy->rlink;

                avail[k].first = buddy->rlink;

                // ������м�λ��
            } else {
                for(r = avail[k].first; r->rlink != buddy; r = r->rlink) {
                    // ���һ�飬rָ�����ǰ��
                }

                r->rlink = buddy->rlink;
                buddy->rlink->llink = r;
            }

            printf("��־���ϲ��ɹ���[%d, (2^%d)]��[%d, (2^%d)]�ϲ�����", (int) (p - start), k, (int) (buddy - start), k);

            // �ϲ�֮ǰ����Ҫȷ���ĸ���鿿ǰ
            if(p < buddy) {
                p->tag = 0;
            } else {
                p = buddy;
            }

            p->kval = k + 1;  // ָ����һ�󣬼���ɺϲ�

            printf("[%d, (2^%d)]\n", (int) (p - start), k + 1);

            // �����µĿ��п�֮��Ҫ����ݹ飬�鿴�ÿ��п��Ƿ�Ҳ���ڿ��л��
            FreeBuddy(avail, p);
        }
    }
}

/*
 * ��ӡ�ڴ沼�֣��鿴��ǰ�ڴ��ʹ�����
 * ע�������ڲ�����ʹ��
 */
void PrintMemoryLayout() {
    int i, count, total;
    WORD* p;

    printf("|");

    p = start;
    count = (int) pow(2, p->kval);

    for(i = 1; i <= count; i++) {
        if(p->tag == 0) {
            printf("_");
        } else {
            printf("*");
        }

        // ���뵽��һ����
        if(i == count && count < (int) pow(2, M)) {
            p = start + count;
            count += (int) pow(2, p->kval);
            printf("|");
        }
    }

    printf("|\n");
}

/*
 * ���ҿ�p�Ļ��
 *
 * ��һ�����п�԰���Ѻ󣬻����ɵ�����С���п飬������С���п黥Ϊ��顣
 *
 * ��������㷨Ϊ��
 * ������ʼ��ַΪp����СΪ2^k���ڴ�飺
 * 1.�� p MOD 2^(k+1) == 0   ,��p�Ļ������ʼ��ַΪp+2^k��
 * 2.�� p MOD 2^(k+1) == 2^k ,��p�Ļ������ʼ��ַΪp-2^k��
 *
 * ע�������ڲ�ʹ�ã����ڻ����㷨��
 */
static WORD* Buddy(WORD* p) {
    long s, m, n;

    if(p == NULL) {
        return NULL;
    }

    // start���������п�ľ�����ʼ��ַ��s��p�ڻ��ϵͳ�еľ��Ե�ַ����0��ʼ
    s = p - start;
    if(s < 0) {
        return NULL;
    }

    m = (long) pow(2, p->kval);
    n = (long) pow(2, p->kval + 1);

    if(s % n == 0) {
        return p + m;
    }

    if(s % n == m) {
        return p - m;
    }

    return NULL;
}

