#include <stdio.h>
#include "../../../���α��㷨ʵ��/��01 ����/Status.h"	//**��01 ����**//
#include "../../../���α��㷨ʵ��/��06 ���Ͷ�����/04 ThreadBinaryTree/ThreadBinaryTree.c" //**��06 ���Ͷ�����**//

/* ����ԭ�� */
Status Algo_6_58(ThrBiTree p, ThrBiTree x);
void PrintElem(TElemType_Thr e);

int main(int argc, char *argv[])
{	
	ThrBiTree Thrt_1, T_1;
	ThrBiTree Thrt_2, T_2;
	ThrBiTree p, x;
	FILE *fp;
	char tmp;
	
	printf("Ԥ���������������Ϊ��ABDG^^^EH^^I^^CF^J^^^...\n");
	printf("Ԥ����Ҫ����Ķ�������������Ϊ��123^^4^^^...\n");

	fp = fopen("Data/Algo_6_58.txt", "r");
	CreateBiTree_Thr(fp, &T_1);
	Scanf(fp, "%c", &tmp);					//�������з� 
	CreateBiTree_Thr(fp, &T_2);

	InOrderThreading_Thr(&Thrt_1, T_1);	 
	InOrderThreading_Thr(&Thrt_2, T_2);	
	printf("\n");
	
	p = T_1->rchild;									//���ڲ��Ե�p��x 
	x = T_2;
	
	printf("�� %c �����������뵽 %c ��...\n", x->data, p->data); 
	Algo_6_58(p, x);
	printf("\n");
	
	printf("�������������ɺ������");
	InOrderTraverse_Thr(Thrt_1, PrintElem);
	printf("\n\n");
	
	return 0;
}

/*������������������������������
����6.58�����������������Ĳ��멧
������������������������������*/
Status Algo_6_58(ThrBiTree p, ThrBiTree x)
{
	ThrBiTree pre_p, x_first, lp_first;
	
	x_first = x;							// Ѱ����x���������һ�����
	while(x_first->lchild && x_first->LTag!=Thread)
		x_first = x_first->lchild;
	
	pre_p = p->lchild;	// ����p�����㣬��������������Ҳ������������ 
	
	if(p->LTag==Thread)	// ���p���������������x����Ϊ������ 
	{
		/* ��ʱ��pre_pΪp��ǰ������ */	
		
		p->LTag = Link;	// �޸ı�ǣ������������� 
		p->lchild = x;
			
		x_first->lchild = pre_p;	// �޸���x�������ǰ�� 
							 
		x->rchild = p;	// �޸�x�ĺ������ 
	}
	else				// p��������������򽫸�����ժ�£����������Ϊx�������� 
	{
		/* ��ʱ��pre_pΪp�������� */
		
		x->RTag = Link;
		x->rchild = pre_p;	// ժ��p������������Ϊx�������� 
		
		lp_first = p;		// Ѱ��p�������������������е�һ�����
		while(lp_first->LTag==Link)
			lp_first = lp_first->lchild;
		
		x_first->lchild = lp_first->lchild;	// �޸���x�������ǰ�� 
		lp_first->lchild = x;				// lp_first������������Ϊx 
		
		p->lchild = x;	// ����p�������� 
	}
	
	return OK;
}

void PrintElem(TElemType_Thr e)
{
	printf("%c ",e);
}
