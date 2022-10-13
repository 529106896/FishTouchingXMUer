/*=======================
 * ����������
 *
 * �����㷨: 6.5��6.6��6.7
 ========================*/

#include "BiThrTree.h"

/*
 * ����
 *
 * ����Ԥ��Ķ�����������������
 * ����Լ��ʹ�á��������С���������������
 *
 *
 *����ע��
 *
 * �̲���Ĭ�ϴӿ���̨��ȡ���ݡ�
 * ����Ϊ�˷�����ԣ�����ÿ�����ж��ֶ��������ݣ�
 * �������ѡ���Ԥ����ļ�path�ж�ȡ�������ݡ�
 *
 * �����Ҫ�ӿ���̨��ȡ���ݣ���pathΪNULL����Ϊ�մ���
 * �����Ҫ���ļ��ж�ȡ���ݣ�����Ҫ��path����д�ļ�����Ϣ��
 */
Status CreateBiTree(BiThrTree* T, char* path) {
    FILE* fp;
    int readFromConsole;    // �Ƿ�ӿ���̨��ȡ����
    
    // ���û���ļ�·����Ϣ����ӿ���̨��ȡ����
    readFromConsole = path == NULL || strcmp(path, "") == 0;
    
    if(readFromConsole) {
        printf("��������������������У����û���ӽ�㣬ʹ��^���棺");
        CreateTree(T, NULL);
    } else {
        // ���ļ���׼����ȡ��������
        fp = fopen(path, "r");
        if(fp == NULL) {
            return ERROR;
        }
        CreateTree(T, fp);
        fclose(fp);
    }
    
    return OK;
}

/*
 * ���������������� �㷨6.6 ����������������
 *
 * �������������T��������ȫ������Ϊ����������Thrt��
 * ע���������������ǰ����������������
 */
Status InOrderThreading(BiThrTree* Thrt, BiThrTree T) {
    // ����ͷ���
    *Thrt = (BiThrTree) malloc(sizeof(BiThrNode));
    if(!*Thrt) {
        exit(OVERFLOW);
    }
    
    (*Thrt)->data = '\0';
    
    (*Thrt)->LTag = Link;       // ���ӣ���Ҫָ��������ĸ����
    (*Thrt)->RTag = Thread;     // ��ָ�룬��Ҫָ�������������һ��Ԫ�أ��Ա��������������������
    
    (*Thrt)->rchild = *Thrt;
    
    // ��������Ϊ�գ�����ָ���ָ
    if(!T) {
        (*Thrt)->lchild = *Thrt;
    } else {
        (*Thrt)->lchild = T;    // ָ�������ͷ���
        pre = *Thrt;            // ��¼ǰ����Ϣ����ʼ��Ϊ����������ͷ���
        
        InTheading(T);          // ����������Խ�������������
        
        pre->rchild = *Thrt;    // ���һ�����ָ������������ͷ���
        pre->RTag = Thread;     // ���һ�����������
        (*Thrt)->rchild = pre;  // ͷ���ָ�����һ����㣬����˫����ϵ
    }
    
    return OK;
    
}

/*
 * ���������������� �㷨6.5 ����������������
 *
 * �����������ȫ�������������ǵݹ��㷨����
 *
 * ע���÷���������֤��������Ƿ���ȷ
 */
Status InOrderTraverse_Thr(BiThrTree T, Status(Visit)(TElemType)) {
    BiThrTree p = T->lchild;    // pָ�����������㣨��ͬ��������������ͷ��㣩
    
    // �������������ʱ��p==T
    while(p != T) {
        // ����������ӣ�������������
        while(p->LTag == Link) {
            p = p->lchild;
        }
        
        // ����������Ϊ�յĽ�㣨����ߣ�
        if(!Visit(p->data)) {
            return ERROR;
        }
        
        // ������ں����������û����������
        while(p->RTag == Thread && p->rchild != T) {
            p = p->rchild;   // ��pָ������
            Visit(p->data);  // ���ʺ�̽��
        }
        
        // ����������
        p = p->rchild;
    }
    
    printf("\n");
    
    return OK;
}


/*�������������������������������������������� �����ڲ�ʹ�õĺ��� ��������������������������������������������*/

// �������������ڲ�����
static void CreateTree(BiThrTree* T, FILE* fp) {
    char ch;
    
    // ��ȡ��ǰ����ֵ
    if(fp == NULL) {
        scanf("%c", &ch);
    } else {
        ReadData(fp, "%c", &ch);
    }
    
    if(ch == '^') {
        *T = NULL;
    } else {
        // ���ɸ����
        *T = (BiThrTree) malloc(sizeof(BiThrNode));
        if(!(*T)) {
            exit(OVERFLOW);
        }
        (*T)->data = ch;
        CreateTree(&((*T)->lchild), fp); // ����������
        CreateTree(&((*T)->rchild), fp); // ����������
    }
}

/*
 * ���������������� �㷨6.7 ����������������
 *
 * ����ȫ���������ڲ�ʵ��
 */
static void InTheading(BiThrTree p) {
    if(p == NULL) {
        return;
    }
    
    InTheading(p->lchild);  // ������������
    
    // �����ǰ����������Ϊ�գ�����Ҫ����ǰ������
    if(!p->lchild) {
        p->LTag = Thread;
        p->lchild = pre; 

        /*
         * �����������Ϊ�գ�������ӱ�ǡ�
         * �̲���ȱ����һ���裬��ᵼ�³���һЩ����BUG��
         * �����Linkö��ֵ���㣬����������ڶ�̬�����ڴ��ǡ�ðѸñ�ǳ�ʼ��Ϊ0��
         * ��ôЧ�����ֶ�����Link��һ���ġ������������û�г�ʼ����ֵ����ô�ͻ��BUG��
         */
    } else {
        p->LTag = Link;
    }
    
    // ���ǰ������������Ϊ�գ���Ϊǰ����㽨���������
    if(!pre->rchild) {
        pre->RTag = Thread;
        pre->rchild = p;
        
		/*
         * �����������Ϊ�գ�����Һ��ӱ�ǡ�
         * �̲���ȱ����һ���裬��ᵼ�³���һЩ����BUG������ͬ�ϡ�
         */
    } else {
        pre->RTag = Link;
    }
    
    pre = p;                // pre��ǰŲһ��
    
    InTheading(p->rchild);  // ������������
}


/*�������������������������������������������� �������� ��������������������������������������������*/

/*
 * �������������ȫ�������������ǵݹ��㷨����
 *
 * ע���÷���������֤ǰ�������Ƿ���ȷ
 */
Status InOrderTraverse_Thr_Inverse(BiThrTree T, Status(Visit)(TElemType)) {
    BiThrTree p = T->rchild;    // pָ�������������������һ����㣬��Ҳ�൱����T����������������������һ�����
    
    // �������������ʱ��p==T
    while(p != T) {
        // ���ʽ��p���ý����ĳ����������������������һ�����
        if(!Visit(p->data)) {
            return ERROR;
        }
        
        // �������ǰ����������û����������
        while(p->LTag == Thread && p->lchild != T) {
            p = p->lchild;   // ��pָ����ǰ��
            Visit(p->data);  // ����ǰ�����
        }
        
        // ����ǰ��һ��������������������Ҳ���������յ�T
        p = p->lchild;
        
        // ���û�������յ㣬�����������������ҵ�����������������������һ�����
        if(p != T) {
            while(p->RTag == Link) {
                p = p->rchild;
            }
        }
    }
    
    printf("\n");
    
    return OK;
}
