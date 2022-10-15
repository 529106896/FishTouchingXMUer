#define _CRT_SECURE_NO_WARNINGS 1
#include "INT.h"

INT::INT()
{
	arr = NULL;
	length = 0;
}

//此处的n是s的长度
//如果是123，那么长度是3
//如果是-123，那么长度也是3
INT::INT(string s, int n)
{
	arr = new int[n + 1];
	//把arr的第一位作为符号位
	//如果是负数，那么第一位为负号
	//如果是整数，那么第一位置0
	if (s[0] == '-')
	{
		arr[0] = -1;
		for (int i = 1; i <= n; i++)
		{
			//因为有符号位，所以s的有效数字从s[1]开始
			arr[i] = s[i] - '0';
		}
	}
	else
	{
		arr[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			//因为没有符号位，所以s的有效数字从s[0]开始
			arr[i] = s[i - 1] - '0';
		}
	}

	//因为增加了符号位，所以length = n + 1
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

//比较两个数的绝对值，s1 > s2则返回true，否则返回false
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
	//此函数的目的是扩充arr的长度
	//所以此处的n一定比length大
	int* temp = arr;

	//正数
	if (arr[0] == 0)
	{
		arr = new int[n];
		//把arr往后移
		for (int i = n - length + 1; i < n; i++)
		{
			arr[i] = temp[i - (n - length)];
		}

		//空位置0
		for (int i = 0; i <= n - length; i++)
			arr[i] = 0;
		length = n;

	}
	//负数
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

	//保持长度一致
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

	//如果都是正数
	if (this->arr[0] == 0 && n.arr[0] == 0)
	{
		//类似于大整数加法，不逐行写注释了
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
		//防止进位进到符号位上，输出时得不到正确结果
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
	//正数+负数
	else if (this->arr[0] == 0 && n.arr[0] == -1)
	{
		for (int i = 0; i < temp.length; i++)
		{
			temp.arr[i] = 0;
		}
		if (compare(this->arr, n.arr, temp.length))
		//正数绝对值 > 负数，结果还是正数
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
			//负数绝对值 > 正数，颠倒过来即可
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
	//负数 + 正数
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
	//负数 + 负数
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
		//防止进位进到符号位上，把符号位的-1给进成0
		if (temp.arr[0] >= 0)
		{
			temp.length++;
			int* temp_temp = temp.arr;
			temp.arr = new int[temp.length];
			for (int i = temp.length; i > 0; i--)
			{
				temp.arr[i] = temp_temp[i - 1];
			}
			//符号位之后的一位进1
			temp.arr[1]++;
			//重写符号位
			temp.arr[0] = -1;
		}
	}
	return temp;
}

INT INT::operator+(int p)
{
	//把int转换成字符串，再转换成INT，然后再进行下一步处理
	stringstream ss;
	ss << p;
	int p_length = 0;
	if (p >= 0)
		p_length = ss.str().length();
	else
		p_length = ss.str().length() - 1;
	INT n(ss.str(), p_length);

	INT temp;

	//保持长度一致
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

	//如果都是正数
	if (this->arr[0] == 0 && n.arr[0] == 0)
	{
		//类似于大整数加法，不逐行写注释了
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
		//防止进位进到符号位上，输出时得不到正确结果
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
	//正数+负数
	else if (this->arr[0] == 0 && n.arr[0] == -1)
	{
		for (int i = 0; i < temp.length; i++)
		{
			temp.arr[i] = 0;
		}
		if (compare(this->arr, n.arr, temp.length))
			//正数绝对值 > 负数，结果还是正数
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
			//负数绝对值 > 正数，颠倒过来即可
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
	//负数 + 正数
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
	//负数 + 负数
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
		//防止进位进到符号位上，把符号位的-1给进成0
		if (temp.arr[0] >= 0)
		{
			temp.length++;
			int* temp_temp = temp.arr;
			temp.arr = new int[temp.length];
			for (int i = temp.length; i > 0; i--)
			{
				temp.arr[i] = temp_temp[i - 1];
			}
			//符号位之后的一位进1
			temp.arr[1]++;
			//重写符号位
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
	//直接套用加法的操作，省事简便
	n.qufan();
	temp = *this + n;
	return temp;
}

INT INT::operator-(int p)
{
	//把int转换成字符串，再转换成INT，然后再进行下一步处理
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
	//直接套用加法的操作，省事简便
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

	//同号相乘，结果为正数
	if ((arr[0] == 0 && n.arr[0] == 0) || (arr[0] == -1) && (n.arr[0] == -1))
	{
		//模拟大整数乘法
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
	//把int转换成字符串，再转换成INT，然后再进行下一步处理
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

	//同号相乘，结果为正数
	if ((arr[0] == 0 && n.arr[0] == 0) || (arr[0] == -1) && (n.arr[0] == -1))
	{
		//模拟大整数乘法
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
			//用temp3 = temp3 - n出现莫名其妙的bug，所以直接加上n的相反数
			temp3 = temp3 + n;
			//temp3.printArr();
			temp1 = temp1 + temp2;
			//temp1.printArr();
		}
		//之前如果能整除，temp3是 -1 0 0，提前退出，导致temp1少一位，所以这里加上
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
	//把int转换成字符串，再转换成INT，然后再进行下一步处理
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
			//用temp3 = temp3 - n出现莫名其妙的bug，所以直接加上n的相反数
			temp3 = temp3 + n;
			//temp3.printArr();
			temp1 = temp1 + temp2;
			//temp1.printArr();
		}
		//之前如果能整除，temp3是 -1 0 0，提前退出，导致temp1少一位，所以这里加上
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
	//如果是负数，先输出负号
	if (p.arr[0] == -1)
		out << "-";

	//输出除符号位的各位数字
	for (int i = 1; i < p.length; i++)
	{
		out << p.arr[i];
	}
	return out;
}