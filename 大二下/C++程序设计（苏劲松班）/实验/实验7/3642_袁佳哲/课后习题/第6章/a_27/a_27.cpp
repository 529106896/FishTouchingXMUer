#include <iostream>

using namespace std;

class IntArray
{
private:
	int* arr;
	int length;

public:
	//默认构造函数
	IntArray()
	{
		arr = NULL;
		length = 0;
	}

	//有参构造函数
	IntArray(int* a, int n)
	{
		arr = new int[n];
		memcpy(arr, a, n * sizeof(int));
		length = n;
	}

	//拷贝构造函数
	IntArray(const IntArray& a)
	{
		arr = new int[a.length];
		memcpy(arr, a.arr, a.length * sizeof(int));
		length = a.length;
	}

	//析构函数
	~IntArray()
	{
		delete[] arr;
		length = 0;
	}

	bool operator>(IntArray& a)
	{
		int sum1 = 0;
		int sum2 = 0;
		for (int i = 0; i < length; i++)
		{
			sum1 += arr[i];
		}
		for (int i = 0; i < a.length; i++)
		{
			sum2 += a.arr[i];
		}
		if (sum1 > sum2)
			return true;
		else
			return false;
	}

	bool operator==(IntArray& a)
	{
		int sum1 = 0;
		int sum2 = 0;
		for (int i = 0; i < length; i++)
		{
			sum1 += arr[i];
		}
		for (int i = 0; i < a.length; i++)
		{
			sum2 += a.arr[i];
		}
		if (sum1 == sum2)
			return true;
		else
			return false;
	}

	bool operator<(IntArray& a)
	{
		int sum1 = 0;
		int sum2 = 0;
		for (int i = 0; i < length; i++)
		{
			sum1 += arr[i];
		}
		for (int i = 0; i < a.length; i++)
		{
			sum2 += a.arr[i];
		}
		if (sum1 < sum2)
			return true;
		else
			return false;
	}

	IntArray& operator=(const IntArray& a)
	{
		if (&a == this)
			return *this;
		delete [] arr;
		arr = new int[a.length];
		memcpy(arr, a.arr, a.length * sizeof(a.length));
		return *this;
	}

	int& operator[](int i)
	{
		if (i >= length || i < 0)
		{
			cerr << "下标越界" << endl;
			exit(-1);
		}
		return arr[i];
	}
	
	void print_array()
	{
		for (int i = 0; i < length; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
		cout << "length is " << length << endl;
	}
};

int main()
{
	int a[5] = { 1,2,3,4,5 };
	IntArray test_array(a, 5);
	test_array.print_array();

	//IntArray test2(test_array);
	//test2.print_array();

	int b[5] = { 1,1,1,1,1 };
	IntArray test1_array(b, 5);
	test1_array.print_array();
	if (test_array > test1_array)
		cout << "test_array > test1_array" << endl;

	IntArray test = test_array;
	test.print_array();

	cout << test_array[4] << endl;
	cout << test_array[5] << endl;

	return 0;
}