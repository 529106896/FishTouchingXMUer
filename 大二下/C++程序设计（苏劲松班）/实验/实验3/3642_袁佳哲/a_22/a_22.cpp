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

void sortList(Node* h)
{
	int temp = 0;
	for (Node* p = h->next; p != NULL; p = p->next)
	{
		for (Node* q = p->next; q != NULL; q = q->next)
		{
			if (p->data > q->data)
			{
				temp = p->data;
				p->data = q->data;
				q->data = temp;
			}
		}
	}
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

	sortList(head1);
	showList(head1);

	return 0;
}