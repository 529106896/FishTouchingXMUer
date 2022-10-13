#include <stdio.h>
#include "Status.h"     //**��01 ����**//
#include "CSTree.h"     //**��06 ���Ͷ�����**//

// ���Ժ�������ӡԪ��
Status PrintElem(TElemType c) {
    printf("%c", c);
    return OK;
}


int main(int argc, char* argv[]) {
    CSTree T;
    
    printf("���������������� InitTree \n");
    {
        printf("�� ��ʼ������ T ...\n");
        InitTree(&T);
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� CreateTree \n");
    {
        printf("�� ���������д����� T ...\n");
        CreateTree(&T, "TestData_T.txt");
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� TreeDepth \n");
    {
        printf("�� �� T �����Ϊ��%d \n", TreeDepth(T));
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� PrintTree \n");
    {
        printf("�� �����Ľṹ��ӡ�� T ...\n");
        printf("�� T = \n");
        PrintTree(T);
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� PreOrderTraverse \n");
    {
        printf("�� ǰ������� T = ");
        PreOrderTraverse(T, PrintElem);
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� PostOrderTraverse \n");
    {
        printf("�� ��������� T = ");
        PostOrderTraverse(T, PrintElem);
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� LevelOrderTraverse \n");
    {
        printf("�� ��������� T = ");
        LevelOrderTraverse(T, PrintElem);
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� Value \n");
    {
        TElemType e = 'F';
        printf("�� ��� %c ��ֵΪ %c\n", e, Value(T, e));
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� Assign \n");
    {
        TElemType e = 'F';
        TElemType value = 'X';
        printf("�� ����� %c ��ֵΪ %c ...\n", e, value);
        Assign(T, e, value);
        printf("�� T = \n");
        PrintTree(T);
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� Root \n");
    {
        printf("�� T �ĸ����Ϊ %c\n", Root(T));
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� Parent \n");
    {
        TElemType e = 'E';
        printf("�� ��� %c ��˫��Ϊ��%c \n", e, Parent(T, e));
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� ChildCount \n");
    {
        TElemType e = 'X';
        printf("�� ��� %c �� %d ������\n", e, ChildCount(T, e));
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� Child \n");
    {
        TElemType e = 'X';
        int i = 2;
        printf("�� ��� %c �ĵ� %d �����ӽ��ֵΪ��%c \n", e, i, Child(T, e, i));
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� LeftSibling \n");
    {
        TElemType e = 'H';
        printf("�� ��� %c �����ֵ�Ϊ��%c\n", e, LeftSibling(T, e));
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� RightSibling \n");
    {
        TElemType e = 'H';
        printf("�� ��� %c �����ֵ�Ϊ��%c\n", e, RightSibling(T, e));
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� InsertChild \n");
    {
        CSTree c;
        TElemType p = 'C';
        int i = 2;
        
        printf("�� �������� c ...\n");
        InitTree(&c);
        CreateTree(&c, "TestData_c.txt");
        printf("�� c = \n");
        PrintTree(c);
        
        printf("�� ������ c ����Ϊ�� T �� %c ���ĵ� %d ������ ...\n", p, i);
        InsertChild(&T, p, i, c);
        printf("�� T = \n");
        PrintTree(T);
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� DeleteChild \n");
    {
        TElemType p = 'C';
        int i = 1;
        
        printf("�� ɾ���� T �� %c ���ĵ� %d ������ ...\n", p, i);
        DeleteChild(&T, p, i);
        printf("�� T = \n");
        PrintTree(T);
    }
    PressEnterToContinue(debug);
    
    
    printf("���������������� ClearTree��TreeEmpty \n");
    {
        printf("�� ���ǰ��");
        TreeEmpty(T) ? printf("T Ϊ�գ�\n") : printf("T ��Ϊ�գ�\n");
        
        ClearTree(&T);
        
        printf("�� ��պ�");
        TreeEmpty(T) ? printf("T Ϊ�գ�\n") : printf("T ��Ϊ�գ�\n");
    }
    PressEnterToContinue(debug);
    
    return 0;
}
