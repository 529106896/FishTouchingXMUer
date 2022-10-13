//
// ʵ������Ļ�������
//
#include <stdio.h>
#include <malloc.h>

struct node // �����Ͻ������ݽṹ
{
	int data;
	node *next;
};

node *Create(void)  // ����һ����������
{
	node *p1,*p2,*head;  // p2ָ�����һ�����, p1ָ������㣬headָ��ͷ���
	int a;
	head = 0;
	printf("����һ�������������������ݣ���-1������\n");
	scanf("%d",&a);
	while(a!=-1)   // 1��3��2��4��-1
	{
		p1 = (node *)malloc(sizeof(node));
		p1->data=a;
		if(head == 0)  // ����������ײ�
		{
			head = p1; p2 = p1;
		}
		else  // ��������β
		{ 
			p2->next = p1; p2 = p1;
		}
		scanf("%d",&a);
	}
	if(head) 
		p2->next = 0;
	return (head);
}

void Print(node *head)  // ��������ϸ���������
{
	node *p;
	p = head;
	printf("�����ϸ���������Ϊ��\n");
	while(p!=0)
	{
		printf("%d  ",p->data);
		p=p->next;
	}
	printf("\n");
}

node *Delete_one_node(node *head,int num)  // ��������ֵɾ�������е�һ�����
{
	node *p1,*p2;
	if(head == 0)
	{	
		printf("����Ϊ�գ��޽���ɾ��!\n");
		return 0;
	}
	if(head->data == num)  //ɾ���׽��
	{	   
		p1 = head;    
		head = head->next;    
		free( (void *)p1 );
		printf("ɾ����һ�����!\n");
	}
	else
	{       	    
		p1 = head;    
		p2 = head->next;  // p1ָ��ȽϽڵ��ǰһ�����
		while(p2->data != num && p2->next != 0)  // �ҵ�Ҫɾ���Ľ��
		{ 	
			p1 = p2;    
			p2 = p2->next;
		}
		if(p2->data == num)  // ɾ���ҵ��Ľ��
		{	
			p1->next = p2->next;	
			free( (void *)p2 );
			printf("ɾ����һ�����!\n");
		}
		else
			printf("������û���ҵ�Ҫɾ���Ľ��!\n");
	}
	return head;
}

node *Insert(node *head,node *p)  // ��һ��������������
{
	node *p1,*p2;
	if(head == 0 )  // ���������������׽��
	{      
		head = p;  
		p->next = 0;
		return head;
	}
	if(head->data >= p->data)  // �ǿ��������뵽������׽��
	{
		p->next = head;   
		head = p;
		return head;
	}
	p2 = p1 = head;
	while(p2->next && p2->data <p->data)  // �ҵ�Ҫ�����λ��
	{
		p1 = p2;  
		p2 = p2->next;
	}
	if(p2->data < p->data)  // ��������β
	{
		p2->next = p; 
		p->next = 0;
	}
	else  // ������p1��p2��ָ��Ľ��֮��
	{
		p->next = p2; 
		p1->next = p;
	}
	return head;
}

node *Create_sort(void)  // ����һ����������
{
	node *p1,*head = NULL;
	int a;
	printf("����һ�������������������ݣ���-1������\n");
	scanf("%d",&a);
	while(a!=-1)
	{
		p1 = (node *)malloc(sizeof(node));  // ����һ���½��
		p1->data=a;
		head = Insert(head,p1);  // ���½�����������
		scanf("%d",&a);
	}
	return head;
}


void deletechain(node *head)  // �ͷ������ϸ����ռ�õ��ڴ�ռ�
{
	node *p1;
	while(head)
	{
		p1 = head;
		head = head->next;
		free( (void *)p1 );
	}
}

/////////////////////////////////////////////////////////////////////////////
int main()
{
	node * head;
	int num;
	head = Create();                       // ����һ����������   1��3��2��5��-1

	Print(head);                           // ��������ϵĸ����ֵ

	printf("����Ҫɾ������ϵ�������\n");
	scanf("%d",&num);          
	head = Delete_one_node(head,num);      // ɾ�������Ͼ���ָ��ֵ�Ľ��   2��1
	Print(head);    
	
	node *p1 = (node *)malloc(sizeof(node));
	p1->data=4;
	head = Insert(head,p1);                // ���½�����������
	Print(head);

	deletechain(head);                     // �ͷ���������Ľ��ռ�

	head = Create_sort();                  // ����һ����������   1��3��2��5��-1
	Print(head);
	deletechain(head);                     // �ͷ������ϸ����ռ�õ��ڴ�ռ�

	return 0;
}