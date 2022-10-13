/*=====
 * ����
 ======*/

#include "MFSet.h"

/*
 * ��ʼ��һ���ɶ���Ӽ���ÿ���Ӽ�ֻ����������Ա�����ɵļ���S��
 *
 *
 *����ע��
 *
 * ����Ե�6�µ�MFSet���˸Ķ���
 * 1.ֱ���ڲ����д����Ӽ�����
 * 2.�Ӽ���Ŵ�0��ʼ���������Ӱ�쵽����ĺ����й����±���ж�
 */
Status initial_mfset(MFSet* S, int n) {
    int i;
    
    if(n <= 0) {
        return ERROR;
    }
    
    S->n = n;
    S->r = 0;   // ��һ���Ӽ���λ����0�ŵ�Ԫ
    
    // �Ӽ���Ŵ�0��ʼ����
    for(i = 0; i < n; i++) {
        S->nodes[i].parent = -1;
    }
    
    return OK;
}

/*
 * �����������ཻ���Ӽ�Si���Ӽ�Sj�Ĳ�����
 */
Status merge_mfset(MFSet* S, int i, int j) {
    
    // ����Խ��
    if(i < 0 || i > S->n - 1 || j < 0 || j > S->n - 1) {
        return ERROR;
    }
    
    // ��ͬ���Ӽ�����ϲ���ֱ�ӷ���
    if(i == j) {
        return OK;
    }
    
    S->nodes[i].parent = j;
    
    return OK;
}

/*
 * �ڼ���S�в���Ԫ��i��ǰ�������Ӽ���
 */
int find_mfset(MFSet S, int i) {
    int j;
    
    // ����Խ��
    if(i < 0 || i > S.n - 1) {
        return -1;
    }
    
    // ����i�������Ӽ��ĸ����
    for(j = i; S.nodes[j].parent >= 0; j = S.nodes[j].parent) {
        // �������ϲ���
    }
    
    return j;
}

/*
 * ���ݵȼ۹�ϵR������/��������S�е�Ԫ��(�Ӽ�)��
 */
Status build_mfset(MFSet* S, Relation R) {
    int k;
    int i, j;
    
    for(k = 0; k < R.n; k++) {
        // �Ȼ�ȡ�Ӽ������
        i = find_mfset(*S, R.pairs[k].i);
        j = find_mfset(*S, R.pairs[k].j);
        
        // �����������ཻ���Ӽ����й鲢
        if(!merge_mfset(S, i, j)) {
            return ERROR;
        }
    }
    
    return OK;
}
