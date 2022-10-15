#pragma once
#include <iostream>
#include <sstream>

using namespace std;

class INT
{
private:
	int* arr;
	int length;

public:
	//构造函数
	INT();

	INT(string s, int n);

	//调试用的函数两个
	int getLength()
	{
		return length;
	}

	void printArr()
	{
		for (int i = 0; i < length; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	//判断当前INT是否为0
	bool isZero(INT& n);

	//把当前长度为length的arr改为长度为0的arr
	void changeLengthToN(int n);

	//创建长度为n的临时INT
	void createTemp(int n);

	//比较s1和s2的绝对值大小
	bool compare(int* s1, int* s2, int n);

	//取相反数
	void qufan();

	//扩展后n位
	void addToLast(int n);

	INT operator +(INT &n);
	INT operator +(int p);
	INT operator -(INT& n);
	INT operator -(int p);
	INT operator *(INT& n);
	INT operator *(int p);
	INT operator /(INT& n);
	INT operator /(int p);
	INT& operator =(const INT& n);

	//要访问private成员，又不能在类内定义，所以定义成友元函数，这样就可以在类外定义时访问private成员
	friend ostream& operator<<(ostream& out, INT& p);

};