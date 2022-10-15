#include <iostream>

using namespace std;

struct Node
{
	int data;
	Node* next;
};

struct Queue
{
	Node* front;
	Node* rear;
};

class ListQueue
{
private:
	int count;
	Node* head;
	Queue* LQ;

public:
	ListQueue()
	{
		count = 0;
		head = new Node;
		LQ = new Queue;
		LQ->front = LQ->rear = head;
		LQ->front->next = NULL;
	}

	void EnterQueue(int data)
	{
		Node* p = new Node;
		p->data = data;
		p->next = NULL;
		LQ->rear->next = p;
		LQ->rear = p;
	}

	void OffQueue(int& data)
	{
		if (LQ->front == LQ->rear)
			return;
		Node* p = LQ->front->next;
		data = p->data;
		LQ->front->next = p->next;
		if (LQ->rear == p)
			LQ->rear = LQ->front;
		delete p;
	}

	void printQueue()
	{
		if (LQ->front == LQ->rear)
			return;
		else
		{
			Node* p = LQ->front->next;
			while (p != NULL)
			{
				cout << p->data << " ";
				p = p->next;
			}
			cout << endl;
		}
	}
};

int main()
{
	ListQueue lq1;
	lq1.EnterQueue(1);
	lq1.EnterQueue(2);
	lq1.EnterQueue(3);
	lq1.printQueue();
	int temp;
	lq1.OffQueue(temp);
	lq1.printQueue();
	lq1.EnterQueue(4);
	lq1.printQueue();
	return 0;
}