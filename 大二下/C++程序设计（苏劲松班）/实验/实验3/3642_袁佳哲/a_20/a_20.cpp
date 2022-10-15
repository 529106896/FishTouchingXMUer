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

bool remove(Node*& h, int& a, int pos)
{
	Node* p = h;
	Node* q = NULL;
	int i = 1;
	while (p != NULL && i < pos)
	{
		q = p;
		p = p->next;
		i++;
	}
	if (p != NULL)
	{
		a = p->data;
		if (q != NULL)
			q->next = p->next;
		else
			h->next = p->next;
		delete p;
		return true;
	}
	else
		return false;
}

void showList(Node* h) // 输出链表以供查看结果
{
	cout << "当前链表为：" << endl;
	while (h != NULL)
	{
		cout << h->data << endl;
		h = h->next;
	}
}

int main()
{
	Node* head = NULL;
	
	insert(head, 1, 0);
	insert(head, 2, 1);
	insert(head, 3, 1);
	insert(head, 4, 1);
	insert(head, 5, 1);
	insert(head, 6, 1);
	insert(head, 7, 1);
	
	showList(head);

	int temp = 0;

	remove(head, temp, 2);
	showList(head);

	return 0;
}