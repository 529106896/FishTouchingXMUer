#include <iostream>

using namespace std;

template<class T>
struct Node
{
	T data;
	Node* next;
};

template<class T>
class LinkList
{
private:
	Node<T>* head;
	int len;
public:
	LinkList()
	{
		head = new Node<T>;
		head->next = NULL;
		len = 0;
	}

	void insert(T value)
	{
		Node<T>* p = new Node<T>;
		p->data = value;
		p->next = head->next;
		head->next = p;
		len++;

		Node<T>* p1;
		Node<T>* p2;
		int temp;
		for (p1 = head->next; p1 != NULL; p1 = p1->next)
		{
			for (p2 = p1->next; p2 != NULL; p2 = p2->next)
			{
				if (p1->data > p2->data)
				{
					temp = p1->data;
					p1->data = p2->data;
					p2->data = temp;
				}
			}
		}
	}

	void printList()
	{
		if (len == 0)
		{
			cout << "empty list" << endl;
		}
		cout << "show list:" << endl;
		Node<T>* p = head->next;
		for (int i = 0; i < len; i++, p = p->next)
		{
			cout << p->data << endl;
		}
	}

	void deleteNode(T value)
	{
		if (len == 0)
		{
			return;
		}
		cout << "try to delete node whose data is " << value << endl;
		Node<T>* pfront = head;
		Node<T>* p = head->next;
		while (p->data != value)
		{
			pfront = pfront->next;
			p = p->next;
			if (p == NULL)
			{
				cout << "no such node" << endl;
				return;
			}
		}
		pfront->next = p->next;
		delete p;
		len--;
	}
};

int main()
{
	LinkList<int>list;
	list.insert(4);
	list.insert(3);
	list.insert(1);
	list.insert(2);
	list.insert(8);
	list.insert(7);
	list.insert(9);
	list.insert(3);
	list.printList();
	list.deleteNode(7);
	list.printList();
	return 0;
}