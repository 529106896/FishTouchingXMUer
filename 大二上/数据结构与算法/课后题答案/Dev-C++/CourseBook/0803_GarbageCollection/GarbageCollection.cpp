/*==============
 * ���õ�Ԫ�ռ�
 *
 * �����㷨: 8.3
 ===============*/

#include "GarbageCollection.h"

/*
 * ���������������� �㷨8.3 ����������������
 *
 * ���������(��ʹ��ջ)��
 */
void MakeList(GList G) {
    GList t, p, q;
    Status finished;

    if(!G || G->mark != 0) {
        return;
    }

    t = NULL;   // tΪp��ĸ��
    p = G;
    finished = FALSE;

    while(!finished) {
        while(p->mark == 0) {
            p->mark = 1;        // MakeHead(p)��ϸ��
            q = p->Node.ptr.hp; // qָ��p�ı�ͷ

            if(q != NULL && q->mark == 0) {
                // ��ͷΪԭ�ӽ��
                if(q->tag == Atom) {
                    q->mark = 1;

                    // ���������ӱ�
                } else {
                    p->Node.ptr.hp = t;
                    p->tag = Atom;
                    t = p;
                    p = q;
                }
            }
        } // ��ɶԱ�ͷ�ı��

        q = p->Node.ptr.tp;

        // ����������β
        if(q != NULL && q->mark == 0) {
            p->Node.ptr.tp = t;
            t = p;
            p = q;

            // BackTrack(finished)��ϸ��
        } else {
            // ���㣬�ӱ�β����
            while(t && t->tag == List) {
                q = t;
                t = q->Node.ptr.tp;
                q->Node.ptr.tp = p;
                p = q;
            }

            // ����
            if(t == NULL) {
                finished = TRUE;

                // �ӱ�ͷ����
            } else {
                q = t;
                t = q->Node.ptr.hp;
                q->Node.ptr.hp = p;
                p = q;
                p->tag = List;
            }// ����������β
        }
    }
}

