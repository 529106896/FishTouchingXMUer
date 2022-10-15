#define _CRT_SECURE_NO_WARNINGS 1
#include "INT.h"

INT::INT()
{
	arr = NULL;
	length = 0;
}

//�˴���n��s�ĳ���
//�����123����ô������3
//�����-123����ô����Ҳ��3
INT::INT(string s, int n)
{
	arr = new int[n + 1];
	//��arr�ĵ�һλ��Ϊ����λ
	//����Ǹ�������ô��һλΪ����
	//�������������ô��һλ��0
	if (s[0] == '-')
	{
		arr[0] = -1;
		for (int i = 1; i <= n; i++)
		{
			//��Ϊ�з���λ������s����Ч���ִ�s[1]��ʼ
			arr[i] = s[i] - '0';
		}
	}
	else
	{
		arr[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			//��Ϊû�з���λ������s����Ч���ִ�s[0]��ʼ
			arr[i] = s[i - 1] - '0';
		}
	}

	//��Ϊ�����˷���λ������length = n + 1
	length = n + 1;
}

bool INT::isZero(INT& n)
{
	//int flag = 0;
	for (int i = 1; i < n.length; i++)
	{
		if (n.arr[i] != 0)
			return false;
	}
	return true;
}

void INT::createTemp(int n)
{
	arr = new int[n];
	length = n;
}

//�Ƚ��������ľ���ֵ��s1 > s2�򷵻�true�����򷵻�false
bool INT::compare(int* s1, int* s2, int n)
{

	int sum1 = 0;
	int sum2 = 0;
	int pow = 1;
	for (int i = n - 1; i >= 1; i--)
	{
		sum1 += s1[i] * pow;
		sum2 += s2[i] * pow;
		pow *= 10;
	}
	if (sum1 > sum2)
		return true;
	else
		return false;
}

void INT::changeLengthToN(int n)
{
	//�˺�����Ŀ��������arr�ĳ���
	//���Դ˴���nһ����length��
	int* temp = arr;

	//����
	if (arr[0] == 0)
	{
		arr = new int[n];
		//��arr������
		for (int i = n - length + 1; i < n; i++)
		{
			arr[i] = temp[i - (n - length)];
		}

		//��λ��0
		for (int i = 0; i <= n - length; i++)
			arr[i] = 0;
		length = n;

	}
	//����
	else if (arr[0] == -1)
	{
		arr = new int[n];
		arr[0] = -1;
		for (int i = n - length + 1; i < n; i++)
		{
			arr[i] = temp[i - (n - length)];
		}
		for (int i = 1; i <= n - length; i++)
		{
			arr[i] = 0;
		}
		length = n;

	}

}

void INT::qufan()
{
	if (arr[0] == 0)
		arr[0] = -1;
	else
		arr[0] = 0;
}

void INT::addToLast(int n)
{
	int* temp = arr;
	arr = new int[length + n];

	for (int i = length; i < length + n; i++)
		arr[i] = 0;
	for (int i = 0; i < length; i++)
		arr[i] = temp[i];
	length = length + n;
}

INT INT::operator+(INT& n)
{
	INT temp;

	//���ֳ���һ��
	if (this->length > n.length)
	{
		n.changeLengthToN(length);
		temp.createTemp(length);
	}
	else
	{
		this->changeLengthToN(n.length);
		temp.createTemp(n.length);
	}

	//�����������
	if (this->arr[0] == 0 && n.arr[0] == 0)
	{
		//�����ڴ������ӷ���������дע����
		for (int i = 0; i < temp.length; i++)
		{
			temp.arr[i] = 0;
		}
		for (int i = temp.length - 1; i >= 1; i--)
		{
			if (this->arr[i] + n.arr[i] <= 9)
				temp.arr[i] += this->arr[i] + n.arr[i];
			else
			{
				temp.arr[i] += this->arr[i] + n.arr[i] - 10;
				temp.arr[i - 1] += 1;
			}
		}
		//��ֹ��λ��������λ�ϣ����ʱ�ò�����ȷ���
		if (temp.arr[0] > 0)
		{
			temp.length++;
			int* temp_temp = temp.arr;
			temp.arr = new int[temp.length];
			for (int i = temp.length - 1; i > 0; i--)
			{
				temp.arr[i] = temp_temp[i - 1];
			}
			temp.arr[0] = 0;
		}
	}
	//����+����
	else if (this->arr[0] == 0 && n.arr[0] == -1)
	{
		for (int i = 0; i < temp.length; i++)
		{
			temp.arr[i] = 0;
		}
		if (compare(this->arr, n.arr, temp.length))
		//��������ֵ > �����������������
		{
			for (int i = temp.length - 1; i >= 1; i--)
			{
				if (this->arr[i] - n.arr[i] >= 0)
					temp.arr[i] += this->arr[i] - n.arr[i];
				else
				{
					temp.arr[i] += this->arr[i] - n.arr[i] + 10;
					temp.arr[i - 1] -= 1;
				}
			}
		}
		else
		{
			//��������ֵ > �������ߵ���������
			temp.arr[0] = -1;
			for (int i = temp.length - 1; i >= 1; i--)
			{
				if (n.arr[i] - this->arr[i] >= 0)
					temp.arr[i] += n.arr[i] - arr[i];
				else
				{
					temp.arr[i] += n.arr[i] - arr[i] + 10;
					temp.arr[i - 1] -= 1;
				}
			}
		}
	}
	//���� + ����
	else if (arr[0] == -1 && n.arr[0] == 0)
	{
		for (int i = 0; i < temp.length; i++)
		{
			temp.arr[i] = 0;
		}
		if (compare(arr, n.arr, temp.length))
		{
			temp.arr[0] = -1;
			for (int i = temp.length - 1; i >= 1; i--)
			{
				if (arr[i] - n.arr[i] >= 0)
				{
					temp.arr[i] += arr[i] - n.arr[i];
				}
				else
				{
					temp.arr[i] += arr[i] - n.arr[i] + 10;
					temp.arr[i - 1] -= 1;
				}
			}
		}
		else
		{
			for (int i = temp.length - 1; i >= 1; i--)
			{
				if (n.arr[i] - arr[i] >= 0)
				{
					temp.arr[i] += n.arr[i] - arr[i];
				}
				else
				{
					temp.arr[i] += n.arr[i] - arr[i] + 10;
					temp.arr[i - 1] -= 1;
				}
			}
		}
	}
	//���� + ����
	else
	{
		temp.arr[0] = -1;
		for (int i = 1; i < temp.length; i++)
		{
			temp.arr[i] = 0;
		}
		for (int i = length - 1; i >= 1; i--)
		{
			if (this->arr[i] + n.arr[i] <= 9)
				temp.arr[i] += this->arr[i] + n.arr[i];
			else
			{
				temp.arr[i] += this->arr[i] + n.arr[i] - 10;
				temp.arr[i - 1] += 1;
			}
		}
		//��ֹ��λ��������λ�ϣ��ѷ���λ��-1������0
		if (temp.arr[0] >= 0)
		{
			temp.length++;
			int* temp_temp = temp.arr;
			temp.arr = new int[temp.length];
			for (int i = temp.length; i > 0; i--)
			{
				temp.arr[i] = temp_temp[i - 1];
			}
			//����λ֮���һλ��1
			temp.arr[1]++;
			//��д����λ
			temp.arr[0] = -1;
		}
	}
	return temp;
}

INT INT::operator+(int p)
{
	//��intת�����ַ�������ת����INT��Ȼ���ٽ�����һ������
	stringstream ss;
	ss << p;
	int p_length = 0;
	if (p >= 0)
		p_length = ss.str().length();
	else
		p_length = ss.str().length() - 1;
	INT n(ss.str(), p_length);

	INT temp;

	//���ֳ���һ��
	if (this->length > n.length)
	{
		n.changeLengthToN(length);
		temp.createTemp(length);
	}
	else
	{
		this->changeLengthToN(n.length);
		temp.createTemp(n.length);
	}

	//�����������
	if (this->arr[0] == 0 && n.arr[0] == 0)
	{
		//�����ڴ������ӷ���������дע����
		for (int i = 0; i < temp.length; i++)
		{
			temp.arr[i] = 0;
		}
		for (int i = temp.length - 1; i >= 1; i--)
		{
			if (this->arr[i] + n.arr[i] <= 9)
				temp.arr[i] += this->arr[i] + n.arr[i];
			else
			{
				temp.arr[i] += this->arr[i] + n.arr[i] - 10;
				temp.arr[i - 1] += 1;
			}
		}
		//��ֹ��λ��������λ�ϣ����ʱ�ò�����ȷ���
		if (temp.arr[0] > 0)
		{
			temp.length++;
			int* temp_temp = temp.arr;
			temp.arr = new int[temp.length];
			for (int i = temp.length - 1; i > 0; i--)
			{
				temp.arr[i] = temp_temp[i - 1];
			}
			temp.arr[0] = 0;
		}
	}
	//����+����
	else if (this->arr[0] == 0 && n.arr[0] == -1)
	{
		for (int i = 0; i < temp.length; i++)
		{
			temp.arr[i] = 0;
		}
		if (compare(this->arr, n.arr, temp.length))
			//��������ֵ > �����������������
		{
			for (int i = temp.length - 1; i >= 1; i--)
			{
				if (this->arr[i] - n.arr[i] >= 0)
					temp.arr[i] += this->arr[i] - n.arr[i];
				else
				{
					temp.arr[i] += this->arr[i] - n.arr[i] + 10;
					temp.arr[i - 1] -= 1;
				}
			}
		}
		else
		{
			//��������ֵ > �������ߵ���������
			temp.arr[0] = -1;
			for (int i = temp.length - 1; i >= 1; i--)
			{
				if (n.arr[i] - this->arr[i] >= 0)
					temp.arr[i] += n.arr[i] - arr[i];
				else
				{
					temp.arr[i] += n.arr[i] - arr[i] + 10;
					temp.arr[i - 1] -= 1;
				}
			}
		}
	}
	//���� + ����
	else if (arr[0] == -1 && n.arr[0] == 0)
	{
		for (int i = 0; i < temp.length; i++)
		{
			temp.arr[i] = 0;
		}
		if (compare(arr, n.arr, temp.length))
		{
			temp.arr[0] = -1;
			for (int i = temp.length - 1; i >= 1; i--)
			{
				if (arr[i] - n.arr[i] >= 0)
				{
					temp.arr[i] += arr[i] - n.arr[i];
				}
				else
				{
					temp.arr[i] += arr[i] - n.arr[i] + 10;
					temp.arr[i - 1] -= 1;
				}
			}
		}
		else
		{
			for (int i = temp.length - 1; i >= 1; i--)
			{
				if (n.arr[i] - arr[i] >= 0)
				{
					temp.arr[i] += n.arr[i] - arr[i];
				}
				else
				{
					temp.arr[i] += n.arr[i] - arr[i] + 10;
					temp.arr[i - 1] -= 1;
				}
			}
		}
	}
	//���� + ����
	else
	{
		temp.arr[0] = -1;
		for (int i = 1; i < temp.length; i++)
		{
			temp.arr[i] = 0;
		}
		for (int i = length - 1; i >= 1; i--)
		{
			if (this->arr[i] + n.arr[i] <= 9)
				temp.arr[i] += this->arr[i] + n.arr[i];
			else
			{
				temp.arr[i] += this->arr[i] + n.arr[i] - 10;
				temp.arr[i - 1] += 1;
			}
		}
		//��ֹ��λ��������λ�ϣ��ѷ���λ��-1������0
		if (temp.arr[0] >= 0)
		{
			temp.length++;
			int* temp_temp = temp.arr;
			temp.arr = new int[temp.length];
			for (int i = temp.length; i > 0; i--)
			{
				temp.arr[i] = temp_temp[i - 1];
			}
			//����λ֮���һλ��1
			temp.arr[1]++;
			//��д����λ
			temp.arr[0] = -1;
		}
	}
	return temp;
}

INT INT::operator-(INT& n)
{
	INT temp;
	if (this->length > n.length)
	{
		n.changeLengthToN(length);
		temp.createTemp(length);
	}
	else
	{
		this->changeLengthToN(n.length);
		temp.createTemp(n.length);
	}
	//ֱ�����üӷ��Ĳ�����ʡ�¼��
	n.qufan();
	temp = *this + n;
	return temp;
}

INT INT::operator-(int p)
{
	//��intת�����ַ�������ת����INT��Ȼ���ٽ�����һ������
	stringstream ss;
	ss << p;
	int p_length = 0;
	if (p >= 0)
		p_length = ss.str().length();
	else
		p_length = ss.str().length() - 1;
	INT n(ss.str(), p_length);

	INT temp;
	if (this->length > n.length)
	{
		n.changeLengthToN(length);
		temp.createTemp(length);
	}
	else
	{
		this->changeLengthToN(n.length);
		temp.createTemp(n.length);
	}
	//ֱ�����üӷ��Ĳ�����ʡ�¼��
	n.qufan();
	temp = *this + n;
	return temp;
}

INT INT::operator*(INT& n)
{
	INT temp;
	temp.createTemp(length);

	for (int i = 0; i < temp.length; i++)
	{
		temp.arr[i] = 0;
	}

	//ͬ����ˣ����Ϊ����
	if ((arr[0] == 0 && n.arr[0] == 0) || (arr[0] == -1) && (n.arr[0] == -1))
	{
		//ģ��������˷�
		for (int i = 1; i < n.length; i++)
		{
			int j = n.arr[i];

			INT temp1;
			temp1.createTemp(length);

			for (int k = 0; k < length; k++)
				temp1.arr[k] = arr[k];

			INT temp2;
			temp2.createTemp(length);
			for (int k = 0; k < length; k++)
			{
				temp2.arr[k] = 0;
			}

			while (j != 0)
			{
				temp2 = temp2 + temp1;
				//temp2.printArr();
				j--;
			}
			temp2.addToLast(n.length - i - 1);
			temp = temp + temp2;
		}
		temp.arr[0] = 0;
	}
	else if((arr[0] == 0 && n.arr[0] == -1)||(arr[0] == -1 && n.arr[0] == 0))
	{
		for (int i = 1; i < n.length; i++)
		{
			int j = n.arr[i];

			INT temp1;
			temp1.createTemp(length);

			for (int k = 0; k < length; k++)
				temp1.arr[k] = arr[k];

			INT temp2;
			temp2.createTemp(length);
			for (int k = 0; k < length; k++)
			{
				temp2.arr[k] = 0;
			}

			while (j != 0)
			{
				temp2 = temp2 + temp1;
				j--;
			}
			temp2.addToLast(n.length - i - 1);
			temp = temp + temp2;
		}
		temp.arr[0] = -1;
	}

	return temp;
}

INT INT::operator*(int p)
{
	//��intת�����ַ�������ת����INT��Ȼ���ٽ�����һ������
	stringstream ss;
	ss << p;
	int p_length = 0;
	if (p >= 0)
		p_length = ss.str().length();
	else
		p_length = ss.str().length() - 1;
	INT n(ss.str(), p_length);

	INT temp;
	temp.createTemp(length);

	for (int i = 0; i < temp.length; i++)
	{
		temp.arr[i] = 0;
	}

	//ͬ����ˣ����Ϊ����
	if ((arr[0] == 0 && n.arr[0] == 0) || (arr[0] == -1) && (n.arr[0] == -1))
	{
		//ģ��������˷�
		for (int i = 1; i < n.length; i++)
		{
			int j = n.arr[i];

			INT temp1;
			temp1.createTemp(length);

			for (int k = 0; k < length; k++)
				temp1.arr[k] = arr[k];

			INT temp2;
			temp2.createTemp(length);
			for (int k = 0; k < length; k++)
			{
				temp2.arr[k] = 0;
			}

			while (j != 0)
			{
				temp2 = temp2 + temp1;
				j--;
			}
			temp2.addToLast(n.length - i - 1);
			temp = temp + temp2;
		}
		temp.arr[0] = 0;
	}
	else if ((arr[0] == 0 && n.arr[0] == -1) || (arr[0] == -1 && n.arr[0] == 0))
	{
		for (int i = 1; i < n.length; i++)
		{
			int j = n.arr[i];

			INT temp1;
			temp1.createTemp(length);

			for (int k = 0; k < length; k++)
				temp1.arr[k] = arr[k];

			INT temp2;
			temp2.createTemp(length);
			for (int k = 0; k < length; k++)
			{
				temp2.arr[k] = 0;
			}

			while (j != 0)
			{
				temp2 = temp2 + temp1;
				j--;
			}
			temp2.addToLast(n.length - i - 1);
			temp = temp + temp2;
		}
		temp.arr[0] = -1;
	}

	return temp;
}

INT INT::operator/(INT& n)
{
	INT temp1;
	temp1.createTemp(2);
	temp1.arr[0] = 0;
	temp1.arr[1] = 0;

	INT temp2;
	temp2.createTemp(2);
	temp2.arr[0] = 0;
	temp2.arr[1] = 1;

	INT temp3;
	temp3.createTemp(length);

	for (int i = 0; i < length; i++)
		temp3.arr[i] = arr[i];

	if (arr[0] == 0 && n.arr[0] == 0)
	{
		n.qufan();
		while (temp3.arr[0] == 0)
		{
			//��temp3 = temp3 - n����Ī�������bug������ֱ�Ӽ���n���෴��
			temp3 = temp3 + n;
			//temp3.printArr();
			temp1 = temp1 + temp2;
			//temp1.printArr();
		}
		//֮ǰ�����������temp3�� -1 0 0����ǰ�˳�������temp1��һλ�������������
		if (isZero(temp3))
			temp1 = temp1 + 1;
		temp1 = temp1 - temp2;
	}
	else if (arr[0] == 0 && n.arr[0] == -1)
	{
		while (temp3.arr[0] == 0)
		{
			temp3 = temp3 + n;
			temp1 = temp1 + temp2;
		}
		if (isZero(temp3))
			temp1 = temp1 + 1;
		temp1 = temp1 - temp2;
		temp1.arr[0] = -1;
	}
	else if (arr[0] == -1 && n.arr[0] == 0)
	{
		while (temp3.arr[0] == -1)
		{
			temp3 = temp3 + n;
			temp1 = temp1 + temp2;
		}
		if (isZero(temp3))
			temp1 = temp1 + 1;
		temp1 = temp1 - temp2;
		temp1.arr[0] = -1;
	}
	else
	{
		temp3.qufan();
		while (temp3.arr[0] == 0)
		{
			temp3 = temp3 + n;
			temp1 = temp1 + temp2;
		}
		if (isZero(temp3))
			temp1 = temp1 + 1;
		temp1 = temp1 - temp2;
		temp1.arr[0] = 0;
	}
	return temp1;
}

INT INT::operator/(int p)
{
	//��intת�����ַ�������ת����INT��Ȼ���ٽ�����һ������
	stringstream ss;
	ss << p;
	int p_length = 0;
	if (p >= 0)
		p_length = ss.str().length();
	else
		p_length = ss.str().length() - 1;
	INT n(ss.str(), p_length);

	INT temp1;
	temp1.createTemp(2);
	temp1.arr[0] = 0;
	temp1.arr[1] = 0;

	INT temp2;
	temp2.createTemp(2);
	temp2.arr[0] = 0;
	temp2.arr[1] = 1;

	INT temp3;
	temp3.createTemp(length);

	for (int i = 0; i < length; i++)
		temp3.arr[i] = arr[i];

	if (arr[0] == 0 && n.arr[0] == 0)
	{
		n.qufan();
		while (temp3.arr[0] == 0)
		{
			//��temp3 = temp3 - n����Ī�������bug������ֱ�Ӽ���n���෴��
			temp3 = temp3 + n;
			//temp3.printArr();
			temp1 = temp1 + temp2;
			//temp1.printArr();
		}
		//֮ǰ�����������temp3�� -1 0 0����ǰ�˳�������temp1��һλ�������������
		if (isZero(temp3))
			temp1 = temp1 + 1;
		temp1 = temp1 - temp2;
	}
	else if (arr[0] == 0 && n.arr[0] == -1)
	{
		while (temp3.arr[0] == 0)
		{
			temp3 = temp3 + n;
			temp1 = temp1 + temp2;
		}
		if (isZero(temp3))
			temp1 = temp1 + 1;
		temp1 = temp1 - temp2;
		temp1.arr[0] = -1;
	}
	else if (arr[0] == -1 && n.arr[0] == 0)
	{
		while (temp3.arr[0] == -1)
		{
			temp3 = temp3 + n;
			temp1 = temp1 + temp2;
		}
		if (isZero(temp3))
			temp1 = temp1 + 1;
		temp1 = temp1 - temp2;
		temp1.arr[0] = -1;
	}
	else
	{
		temp3.qufan();
		while (temp3.arr[0] == 0)
		{
			temp3 = temp3 + n;
			temp1 = temp1 + temp2;
		}
		if (isZero(temp3))
			temp1 = temp1 + 1;
		temp1 = temp1 - temp2;
		temp1.arr[0] = 0;
	}
	return temp1;
}

INT& INT::operator=(const INT& n)
{
	length = n.length;
	int* temp = new int[n.length];
	for (int i = 0; i < n.length; i++)
	{
		temp[i] = n.arr[i];
	}
	delete[] arr;
	arr = temp;
	return *this;
}

ostream& operator<<(ostream& out, INT& p)
{
	//����Ǹ��������������
	if (p.arr[0] == -1)
		out << "-";

	//���������λ�ĸ�λ����
	for (int i = 1; i < p.length; i++)
	{
		out << p.arr[i];
	}
	return out;
}