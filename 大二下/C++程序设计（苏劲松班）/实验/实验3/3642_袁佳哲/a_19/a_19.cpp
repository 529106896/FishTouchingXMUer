#include <iostream>

using namespace std;

struct Node
{
	int data;
	struct Node* next;
};

bool insert(Node*& h, int a, int pos)//头插法插入结点
{
	Node* node = new Node;
	if (pos == 0)
	{
		node->data = a;
		node->next = h;
		h = node;
		return true;
	}
	else
	{
		Node* pre = h;
		int i = 1;
		while (pre != NULL && i < pos)
		{
			pre = pre->next;
			i++;
		}
		if (pre != NULL)
		{
			node->next = pre->next;
			node->data = a;
			pre->next = node;
			return true;
		}
		else
			return false;
	}
}

void showList(Node* h) // 输出链表以供查看结果
{
	while (h != NULL)
	{
		cout << h->data << endl;
		h = h->next;
	}
}

int main()
{
	Node* head = NULL;
	if (insert(head, 1, 0))
		cout << "ok" << endl;
	else
		cout << "no" << endl;

	if (insert(head, 2, 0))
		cout << "ok" << endl;
	else
		cout << "no" << endl;

	if (insert(head, 3, 0))
		cout << "ok" << endl;
	else
		cout << "no" << endl;

	if (insert(head, 4, 1))
		cout << "ok" << endl;
	else
		cout << "no" << endl;

	if (insert(head, 5, 1))
		cout << "ok" << endl;
	else
		cout << "no" << endl;

	if (insert(head, 6, 1))
		cout << "ok" << endl;
	else
		cout << "no" << endl;
	
	showList(head);

	return 0;
}