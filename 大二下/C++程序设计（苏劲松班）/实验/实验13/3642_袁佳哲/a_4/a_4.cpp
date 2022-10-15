#include <iostream>
#include <vector>

using namespace std;

template <class T>
class myArray
{
private:
	vector<T> vec;

public:
	myArray()
	{
	}

	void add(T value)
	{
		vec.push_back(value);
	}

	void print()
	{
		for (typename vector<T>::iterator it = vec.begin(); it != vec.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}

	T& operator[](int i)
	{
		if (i >= vec.size() || i < 0)
		{
			throw -1;
		}
		return vec.at(i);
	}
};

int main()
{
	myArray<int> intArray;
	cout << "已创建一个int类型的数组" << endl;
	cout << "请输入数组的大小：";
	int size = 0;
	cin >> size;
	int temp = size;
	if (size == 0)
	{
		cout << "空数组，无法进行下一步操作！" << endl;
		exit(-1);
	}
	while (size)
	{
		cout << "请输入第" << temp + 1 - size-- << "个元素：";
		int value = 0;
		cin >> value;
		intArray.add(value);
	}

	cout << endl;
	
	while (1)
	{
		try
		{
			cout << "请输入要访问的数组元素的下标：";
			int pos = 0;
			cin >> pos;
			cout << "下标为" << pos << "的数组元素为：" << intArray[pos] << endl;
			cout << endl;
		}
		catch (int)
		{
			cout << "数组下标越界！" << endl;
			break;
		}
	}

	return 0;
}