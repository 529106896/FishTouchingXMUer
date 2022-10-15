#include <iostream>

using namespace std;

struct Node
{
	int value;
	Node* next;
};

class LinearList
{
private:
	int count;
	Node* head;

public:
	LinearList()
	{
		count = 0;
		head = NULL;
	}

	~LinearList()
	{
		while (head != NULL)
		{
			Node* p = head;
			head = head->next;
			delete p;
		}
		count = 0;
	}

	void print()
	{
		Node* p = head;
		while (p != NULL)
		{
			cout << p->value << " ";
			p = p->next;
		}
		cout << endl;
	}

	bool insert(int x, int pos)
	{
		if (pos < 0 || pos > count)
		{
			return false;
		}
		else
		{
			Node* p = new Node;
			p->value = x;
			p->next = NULL;
			if (pos == 0)
			{
				p->next = head;
				head = p;
			}
			else
			{
				Node* temp = head;
				for (int i = 1; i < pos; i++)
					temp = temp->next;
				p->next = temp->next;
				temp->next = p;
			}
			count++;
			return true;
		}
	}

	bool remove(int& x, int pos)
	{
		if (pos <= 0 || pos > count)
		{
			return false;
		}
		else
		{
			if (pos == 1)
			{
				Node* p = head;
				head = head->next;
				x = p->value;
				delete p;
			}
			else
			{
				Node* p = head;
				for (int i = 2; i < pos; i++)
				{
					p = p->next;
				}
				Node* temp = p->next;
				p->next = temp->next;
				x = temp->value;
				delete temp;
			}
			count--;
			return true;
		}
	}

	int element(int pos) const
	{
		if (pos <= 0 || pos > count)
		{
			return -1;
		}
		else
		{
			Node* p = head;
			for (int i = 1; i < pos; i++)
			{
				p = p->next;
			}
			return p->value;
		}
	}

	int search(int x) const
	{
		int pos = 1;
		Node* p = head;
		while (p != NULL)
		{
			if (p->value == x)
				return pos;
			pos++;
			p = p->next;
		}
		return 0;
	}

	int length() const
	{
		return count;
	}
};

int main()
{
	LinearList list1;
	list1.insert(1, 0);
	list1.insert(2, 0);
	list1.insert(4, 1);
	list1.insert(5, 0);
	list1.insert(9, 0);
	list1.insert(10, 0);
	list1.insert(8, 0);
	cout << "show list:";
	list1.print();
	cout << "length is " << list1.length() << endl;
	int temp;
	list1.remove(temp, 1);
	cout << "show list:";
	list1.print();
	cout << "length is " << list1.length() << endl;
	cout << "element at pos 1st is ";
	cout << list1.element(1) << endl;
	cout << "the pos of element \"5\" is ";
	cout << list1.search(5) << endl;
	return 0;
}