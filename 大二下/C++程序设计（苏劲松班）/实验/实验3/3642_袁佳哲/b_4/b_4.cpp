#include <iostream>

using namespace std;

struct Node
{
	int data;
	struct Node* next;
};

void insert_Node(Node* h, int a)
{
	Node* newNode = new Node;
	newNode->data = a;
	newNode->next = h->next;
	h->next = newNode;
}

void showList(Node* h)
{
	Node* temp = h->next;
	cout << "Show List: ";
	while (temp != NULL)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}

void delete_last_node(Node* h)
{
	Node* p = h->next;
	if (p == NULL)//除头结点外什么都没有，就不存在最后一个结点
	{
		return;
	}
	if (p->next == NULL)//如果只有一个结点，直接删掉，直接return
	{
		delete p;
		h->next = NULL;
		return;
	}
	while (p->next->next != NULL)
		p = p->next;
	delete p->next;
	p->next = NULL;
}


int main()
{
	Node* head1 = new Node;
	head1->next = NULL;

	insert_Node(head1, 7);
	insert_Node(head1, 2);
	insert_Node(head1, 3);
	insert_Node(head1, 4);
	insert_Node(head1, 5);

	showList(head1);

	delete_last_node(head1);
	showList(head1);

	return 0;
}