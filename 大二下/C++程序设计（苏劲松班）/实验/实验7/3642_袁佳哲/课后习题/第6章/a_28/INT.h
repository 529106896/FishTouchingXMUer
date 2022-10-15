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
	//���캯��
	INT();

	INT(string s, int n);

	//�����õĺ�������
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

	//�жϵ�ǰINT�Ƿ�Ϊ0
	bool isZero(INT& n);

	//�ѵ�ǰ����Ϊlength��arr��Ϊ����Ϊ0��arr
	void changeLengthToN(int n);

	//��������Ϊn����ʱINT
	void createTemp(int n);

	//�Ƚ�s1��s2�ľ���ֵ��С
	bool compare(int* s1, int* s2, int n);

	//ȡ�෴��
	void qufan();

	//��չ��nλ
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

	//Ҫ����private��Ա���ֲ��������ڶ��壬���Զ������Ԫ�����������Ϳ��������ⶨ��ʱ����private��Ա
	friend ostream& operator<<(ostream& out, INT& p);

};