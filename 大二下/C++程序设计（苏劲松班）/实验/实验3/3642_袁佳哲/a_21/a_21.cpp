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

bool find_data(Node* h, int val)
{
	Node* p = h->next;
	while (p!=NULL)
	{
		if (p->data == val)
			return true;
		else
			p = p->next;
	}
	return false;
}

Node* jiaoji(Node* h1, Node* h2)
{
	Node* temp = new Node;
	temp->next = NULL;
	Node* temp_1 = h1->next;
	Node* temp_2 = h2->next;
	while (temp_1 != NULL)
	{
		if (find_data(h2, temp_1->data))
			insert_Node(temp, temp_1->data);
		temp_1 = temp_1->next;
	}
	return temp;
}

Node* bingji(Node* h1, Node* h2)
{
	Node* temp = new Node;
	temp->next = NULL;
	Node* temp_1 = h1->next;
	Node* temp_2 = h2->next;
	while (temp_1 != NULL)
	{
		insert_Node(temp, temp_1->data);
		temp_1 = temp_1->next;
	}
	while (temp_2 != NULL)
	{
		if (!find_data(temp, temp_2->data))
			insert_Node(temp, temp_2->data);
		temp_2 = temp_2->next;
	}
	return temp;
}

Node* chaji(Node* h1, Node* h2)
{
	Node* temp = new Node;
	temp->next = NULL;
	Node* temp_1 = h1->next;
	Node* temp_2 = h2->next;

	while (temp_1 != NULL)
	{
		if (!find_data(h2, temp_1->data))
			insert_Node(temp, temp_1->data);
		temp_1 = temp_1->next;
	}
	return temp;
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

	Node* head2 = new Node;
	head2->next = NULL;

	insert_Node(head2, 1);
	insert_Node(head2, 2);
	insert_Node(head2, 6);
	insert_Node(head2, 3);
	insert_Node(head2, 4);

	showList(head2);

	cout << "交集为：";
	showList(jiaoji(head1, head2));
	cout << endl;

	cout << "并集为：";
	showList(bingji(head1, head2));
	cout << endl;

	cout << "差集为：";
	showList(chaji(head1, head2));
	cout << endl;

	return 0;
}