#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

struct Node
{
	int data;
	struct Node* next;
};

void Push(Node* top, int data)	//入栈
{
	Node* newNode = new Node;
	newNode->data = data;
	newNode->next = top->next;
	top->next = newNode;
}

void Pop(Node* top, int& data)	//出栈
{
	Node* p = top->next;
	if (!p)
	{
		cout << "Empty Stack!" << endl;
		return;
	}
	else
	{
		top->next = p->next;
		data = p->data;
		delete p;
	}
}

bool isStackEmpty(Node* top)	//看栈是否为空
{
	if (top->next == NULL)
	{
		return true;
	}
	else
		return false;
}

void PrintStack(Node* top)
{
	if (isStackEmpty(top))
	{
		cout << "Empty Stack!" << endl;
		return;
	}
	cout << "The Elements in the Stack are:" << endl;
	Node* p = top->next;
	while (p != NULL)
	{
		cout << p->data << endl;
		p = p->next;
	}

}

int StackLength(Node* top)		//统计栈的有效长度（除去头节点）
{
	int length = 0;
	Node* temp = top->next;
	while (temp != NULL)
	{
		length++;
		temp = temp->next;
	}
	return length;
}

int GetTop(Node * top)
{
	Node* p = top->next;
	if (p == NULL)
	{
		cout << "Empty Stack!" << endl;
		return 0;
	}
	else
	{
		return p->data;
	}
}

int main()
{
	Node* top = new Node;
	top->next = NULL;
	Push(top, 1);
	Push(top, 2);
	Push(top, 3);
	PrintStack(top);
	cout << "The length of stack is " << StackLength(top) << endl;
	cout << "The top of the stack is " << GetTop(top) << endl;
	cout << "Now pop one node." << endl;
	int temp;
	Pop(top, temp);
	PrintStack(top);
	cout << "The length of stack is " << StackLength(top) << endl;
	cout << "The top of the stack is " << GetTop(top) << endl;
	return 0;
}