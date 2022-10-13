//
// 实现链表的基本操作
//
#include <stdio.h>
#include <malloc.h>

struct node // 链表上结点的数据结构
{
	int data;
	node *next;
};

node *Create(void)  // 产生一条无序链表
{
	node *p1,*p2,*head;  // p2指向最后一个结点, p1指向插入结点，head指向头结点
	int a;
	head = 0;
	printf("产生一条无序链表，请输入数据，以-1结束：\n");
	scanf("%d",&a);
	while(a!=-1)   // 1，3，2，4，-1
	{
		p1 = (node *)malloc(sizeof(node));
		p1->data=a;
		if(head == 0)  // 插入链表的首部
		{
			head = p1; p2 = p1;
		}
		else  // 插入链表尾
		{ 
			p2->next = p1; p2 = p1;
		}
		scanf("%d",&a);
	}
	if(head) 
		p2->next = 0;
	return (head);
}

void Print(node *head)  // 输出链表上各结点的数据
{
	node *p;
	p = head;
	printf("链表上各结点的数据为：\n");
	while(p!=0)
	{
		printf("%d  ",p->data);
		p=p->next;
	}
	printf("\n");
}

node *Delete_one_node(node *head,int num)  // 根据数据值删除链表中的一个结点
{
	node *p1,*p2;
	if(head == 0)
	{	
		printf("链表为空，无结点可删除!\n");
		return 0;
	}
	if(head->data == num)  //删除首结点
	{	   
		p1 = head;    
		head = head->next;    
		free( (void *)p1 );
		printf("删除了一个结点!\n");
	}
	else
	{       	    
		p1 = head;    
		p2 = head->next;  // p1指向比较节点的前一个结点
		while(p2->data != num && p2->next != 0)  // 找到要删除的结点
		{ 	
			p1 = p2;    
			p2 = p2->next;
		}
		if(p2->data == num)  // 删除找到的结点
		{	
			p1->next = p2->next;	
			free( (void *)p2 );
			printf("删除了一个结点!\n");
		}
		else
			printf("链表上没有找到要删除的结点!\n");
	}
	return head;
}

node *Insert(node *head,node *p)  // 将一个结点插入链表中
{
	node *p1,*p2;
	if(head == 0 )  // 空链表，插入链表首结点
	{      
		head = p;  
		p->next = 0;
		return head;
	}
	if(head->data >= p->data)  // 非空链表，插入到链表的首结点
	{
		p->next = head;   
		head = p;
		return head;
	}
	p2 = p1 = head;
	while(p2->next && p2->data <p->data)  // 找到要插入的位置
	{
		p1 = p2;  
		p2 = p2->next;
	}
	if(p2->data < p->data)  // 插入链表尾
	{
		p2->next = p; 
		p->next = 0;
	}
	else  // 插入在p1和p2所指向的结点之间
	{
		p->next = p2; 
		p1->next = p;
	}
	return head;
}

node *Create_sort(void)  // 产生一条有序链表
{
	node *p1,*head = NULL;
	int a;
	printf("产生一条有序链表，请输入数据，以-1结束：\n");
	scanf("%d",&a);
	while(a!=-1)
	{
		p1 = (node *)malloc(sizeof(node));  // 产生一个新结点
		p1->data=a;
		head = Insert(head,p1);  // 将新结点插入链表中
		scanf("%d",&a);
	}
	return head;
}


void deletechain(node *head)  // 释放链表上各结点占用的内存空间
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
	head = Create();                       // 产生一条无序链表   1，3，2，5，-1

	Print(head);                           // 输出链表上的各结点值

	printf("输入要删除结点上的整数：\n");
	scanf("%d",&num);          
	head = Delete_one_node(head,num);      // 删除链表上具有指定值的结点   2，1
	Print(head);    
	
	node *p1 = (node *)malloc(sizeof(node));
	p1->data=4;
	head = Insert(head,p1);                // 将新结点插入链表中
	Print(head);

	deletechain(head);                     // 释放整个链表的结点空间

	head = Create_sort();                  // 产生一条有序链表   1，3，2，5，-1
	Print(head);
	deletechain(head);                     // 释放链表上各结点占用的内存空间

	return 0;
}