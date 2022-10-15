#include <iostream>

using namespace std;

struct Node
{
	int data;
	Node* next;
};

void insertNodeByHead(Node* head, int value)
{
	Node* p = new Node;
	p->data = value;
	p->next = head->next;
	head->next = p;
}

void printList(Node* head)
{
	Node* p = head->next;
	while (p != NULL)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

void reverse(Node* head)
{
	if (head->next == NULL)	//空链表
		return;
	Node* p1 = head->next;	//p1用来保留第一个结点
	Node* p2 = p1->next;	//p2用来保留第一个结点的next
	Node* p3 = p1;			//p3用来保留整体第一个结点
	Node* p4;				//p4用来保留第二个结点的next
	while (p2 != NULL)
	{
		p4 = p2->next;
		p2->next = p1;
		p1 = p2;
		p2 = p4;
	}
	head->next = p1;
	p3->next = NULL;
}

int main()
{
	Node* head = new Node;
	head->next = NULL;
	insertNodeByHead(head, 1);
	insertNodeByHead(head, 2);
	insertNodeByHead(head, 3);
	insertNodeByHead(head, 4);
	insertNodeByHead(head, 5);
	insertNodeByHead(head, 6);
	printList(head);
	reverse(head);
	printList(head);
	return 0;
}