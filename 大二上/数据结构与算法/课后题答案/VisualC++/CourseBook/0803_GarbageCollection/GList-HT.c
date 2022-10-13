/*============================
 * ������ͷβ����洢��ʾ
 *
 * �����㷨: 5.5��5.6��5.7��5.8
 =============================*/

#include "GList-HT.h"                        //**��05 ����͹����**//

/*
 * ��ʼ��
 *
 * ��ʼ���յĹ��������Ϊ0�����Ϊ1��
 *
 *��ע��
 * ��Ҫ��ÿһ��ȥ�����ſ���
 */
Status InitGList(GList* L) {
    if(L == NULL) {
        return ERROR;
    }
    
    *L = NULL;
    
    return OK;
}

/*
 * ���������������� �㷨5.7 ����������������
 *
 * ����
 *
 * ���ַ���S���������L��
 */
Status CreateGList(GList* L, SString S) {
    SString emp;        // ����չ������ַ���
    SString hsub, sub;
    GList p, q;
    
    if(L == NULL) {
        return ERROR;
    }
    
    // �����ַ���S�еĿհף����������ɴ�ӡ�ַ�������ո�
    ClearBlank(S);
    
    if(StrEmpty(S)) {
        return ERROR;
    }
    
    StrAssign(emp, "()");
    
    /*
     * ������봮Ϊ()���������Ҫ�����յĹ����
     *
     *��ע��
     * �̲�����Ĵ�����������ġ�
     * StrCompare�ķ���ֵָʾ���������ַ����Ĵ�С��������ָʾ�����ַ����Ƿ���ȡ�
     * ���������S��()��ȣ�����ֵӦ����0��
     */
    if(!StrCompare(S, emp)) {
        *L = NULL;
    } else {
        *L = (GList) malloc(sizeof(GLNode));
        if(*L == NULL) {
            exit(OVERFLOW);
        }
        
        // ��ʼ�����Ϊ0����˼�Ǹý��δ����
        (*L)->mark = 0;
        
        // ����ԭ��
        if(StrLength(S) == 1) {
            (*L)->tag = Atom;
            (*L)->Node.atom = S[1];
        } else {
            (*L)->tag = List;
            
            p = *L;
            
            // ȥ�����������
            SubString(sub, S, 2, StrLength(S) - 2);
            
            // �ظ���n���ӱ�
            do {
                // ��sub�з������ͷ��hsub��������ɺ�subҲ�ᷢ���仯
                sever(hsub, sub);
                
                // �ݹ鴴�������
                CreateGList(&(p->Node.ptr.hp), hsub);
                
                q = p;
                
                // �����β��Ϊ�գ���Ҫ���������β
                if(!StrEmpty(sub)) {
                    p = (GList) malloc(sizeof(GLNode));
                    if(p == NULL) {
                        exit(OVERFLOW);
                    }
                    
                    // ��ʼ�����Ϊ0����˼�Ǹý��δ����
                    p->mark = 0;
    
                    p->tag = List;
                    
                    q->Node.ptr.tp = p;
                }
            } while(!StrEmpty(sub));
            
            q->Node.ptr.tp = NULL;
        }
    }
    
    return OK;
}

/*
 * ͼ�λ����
 *
 * ��������������L��
 */
void PrintGList(GList L) {
    Print(L, Head);
    printf("\n");
}

/*
 * ͼ�λ�������ڲ�ʵ�֣�mark��ͼ�λ������ǡ�
 */
static void Print(GList L, Mark mark) {
    // LΪ��
    if(L == NULL) {
        if(mark == Head) {
            printf("(");
        }
        
        printf(")");
        
        // L��Ϊ��ʱ
    } else {
        // ����ԭ�ӽ�㣬���ԭ��
        if(L->tag == Atom) {
            printf("%c", L->Node.atom);
            
            // �����ӱ��㣬Ҫ�Ա�ͷ����β�ֱ�����
        } else {
            if(mark == Head) {
                printf("(");
            } else {
                printf(",");
            }
            
            Print(L->Node.ptr.hp, Head);
            Print(L->Node.ptr.tp, Tail);
        }
    }
}

/*
 * ���������������� �㷨5.8 ����������������
 *
 * ���ǿմ�str�ָ�������֣�hsubΪ��һ��','֮ǰ���Ӵ���strΪ��һ��','֮����Ӵ���
 *
 *��ע��
 * 1.��������ַ���str������ȷ�������޿հ׷��ţ���str���Ѿ���ȥ��������š���
 * 2.������ɺ�strҲ�ᷢ���仯
 */
static void sever(SString hstr, SString str) {
    int i, k, n;
    SString ch;
    
    n = StrLength(str);
    
    i = 0;  // �����ַ���ʱ���α�
    k = 0;  // ���������δ�����������
    
    do {
        ++i;
        
        // ��ȡstr��һ���ַ�
        SubString(ch, str, i, 1);
        
        if(ch[1] == '(') {
            ++k;
        }
        
        if(ch[1] == ')') {
            --k;
        }
    } while(i < n && (ch[1] != ',' || k != 0));
    
    // ������ڶ���������
    if(i < n) {
        SubString(hstr, str, 1, i - 1);
        SubString(str, str, i + 1, n - i);
        
        // ֻ��һ���������
    } else {
        StrCopy(hstr, str);
        ClearString(str);
    }
}
