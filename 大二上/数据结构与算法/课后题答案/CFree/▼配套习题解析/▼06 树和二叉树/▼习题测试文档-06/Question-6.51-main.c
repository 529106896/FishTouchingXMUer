#include <stdio.h>
#include "../../../���α��㷨ʵ��/��01 ����/Status.h"	//**��01 ����**//
#include "../../../���α��㷨ʵ��/��06 ���Ͷ�����/02 BinaryTree/BinaryTree.c" //**��06 ���Ͷ�����**//

/* ����ԭ�� */
void Algo_6_51(BiTree T);
Status IsOperator_6_51(char c);

int main(int argc, char *argv[])
{
	BiTree T;
	FILE *fp;
	
	printf("�������������������У�T�� */*+a^^b^^-c^^d^^e^^-g^^h^^...\n");
	InitBiTree(&T);
	fp = fopen("Data/Algo_6_51.txt", "r");
	CreateBiTree(fp, &T);
	fclose(fp);
	printf("\n");
	
	printf("������TΪ��\n");
	PrintTree(T);
	printf("\n");
	
	printf("����������ʽ��");
	Algo_6_51(T);	
	printf("\n\n");
	
	return 0;
}

/*������������������������������������
����6.51������������ʽ���ɵĶ�������
������������������������������������*/
void Algo_6_51(BiTree T)
{
	if(T)
	{
		if(T->lchild)
		{	
			// �������Ǳ��ʽ�����������			
			if(IsOperator_6_51(T->lchild->data))
			{
				printf("(");
				Algo_6_51(T->lchild);
				printf(")");
			}			
			else
				Algo_6_51(T->lchild);
		}
		
		printf("%c", T->data);
		
		if(T->rchild)
		{
			// �������Ǳ��ʽ�����������
			if(IsOperator_6_51(T->rchild->data))
			{
				printf("(");
				Algo_6_51(T->rchild);
				printf(")");
			}			
			else
				Algo_6_51(T->rchild);		
		}
	} 
}

Status IsOperator_6_51(char c)				//�ж��ַ�c�Ƿ�Ϊ������
{
	if(c=='+' || c=='-' || c=='*' || c=='/')
		return TRUE;
	else
		return ERROR;
} 
