#include <stdio.h>
#include "GarbageCollection.h"  //**��08 ��̬�洢����**//

// ���������
void Traverse(GList L, void(Visit)(GList));

// ��ӡ���������Ϣ
void PrintInfo(GList L);


int main(int argc, char* argv[]) {
    GList G;
    
    printf("��������������");
    {
        SString S;
        char* s = "((),(e),(a,(b,c,d)))";
        
        InitGList(&G);
        
        StrAssign(S, s);
        CreateGList(&G, S);
        
        PrintGList(G);
        printf("\n");
    }
    PressEnterToContinue(debug);
    
    printf("���������������� MakeList \n");
    {
        printf("����ǰ�ı�־״̬...\n");
        Traverse(G, PrintInfo);
        printf("\n");
        MakeList(G);
        
        printf("���ʺ�ı�־״̬...\n");
        Traverse(G, PrintInfo);
        printf("\n");
    }
    PressEnterToContinue(debug);
    
    return 0;
}


// ���������
void Traverse(GList L, void(Visit)(GList)) {
    if(L == NULL) {
        return;
    }
    
    Visit(L);
    
    if(L->tag == List) {
        Traverse(L->Node.ptr.hp, Visit);
        Traverse(L->Node.ptr.tp, Visit);
    }
}

// ��ӡ���������Ϣ
void PrintInfo(GList L) {
    if(L->tag == Atom) {
        printf("mark = %d ԭ�ӽ�㣺%c\n", L->mark, L->Node.atom);
    } else {
        printf("mark = %d ����\n", L->mark);
    }
}
