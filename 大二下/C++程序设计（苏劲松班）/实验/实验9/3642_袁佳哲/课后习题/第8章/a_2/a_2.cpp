#include <iostream>

using namespace std;

template <class T>
struct Node
{
	T data;
	Node<T>* next;
};

template <class T>
class Queue
{
private:
	Node<T>* head;
	int count;
public:
	Queue()
	{
		head = NULL;
		count = 0;
	}
	
	void enQueue(const T& e)
	{
		if (count == 0)
		{
			Node<T>* p = new Node<T>;
			p->data = e;
			p->next = NULL;
			head = p;
		}
		else
		{
			Node<T>* temp = head;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			Node<T>* p = new Node<T>;
			p->data = e;
			p->next = NULL;
			temp->next = p;
		}
		count++;
	}

	void deQueue()
	{
		if (head == NULL)
			return;
		else
		{
			cout << "队首出队！" << endl;
			Node<T>* temp = head;
			head = head->next;
			delete temp;
		}
	}

	void printQueue()
	{
		if (head == NULL)
		{
			return;
		}
		else
		{
			Node<T>* p = head;
			cout << "队列展示如下：" << endl;
			while (p != NULL)
			{
				cout << p->data << endl;
				p = p->next;
			}
		}
	}
};

int main()
{
	Queue<int> q1;
	q1.enQueue(1);
	q1.enQueue(2);
	q1.enQueue(3);
	q1.printQueue();
	q1.deQueue();
	q1.printQueue();
	q1.enQueue(1);
	q1.printQueue();
	return 0;
}