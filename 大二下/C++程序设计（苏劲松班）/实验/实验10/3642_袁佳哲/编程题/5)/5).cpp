#include <iostream>
#include <typeinfo>

using namespace std;

template <class T>
class myArray
{
private:
	T* arr;
	int size;
public:
	myArray();
	myArray(int n);
	~myArray();
	T getSum();
	void printArr();
	void search(T a);
};

template <class T>
myArray<T>::myArray()
{
	arr = NULL;
	size = 0;
}

template <class T>
myArray<T>::myArray(int n)
{
	T input;
	size = n;
	arr = new T[n];
	printf("请输入%d个%s的类型的变量：", n, typeid(T).name());
	for (int i = 0; i < n; i++)
	{
		cin >> input;
		arr[i] = input;
	}
}

template<class T>
myArray<T>::~myArray()
{
	delete[] arr;
	size = 0;
}

template<class T>
void myArray<T>::printArr()
{
	if (size == 0)
		return;
	else
	{
		for (int i = 0; i < size - 1; i++)
		{
			cout << arr[i] << "  ";
		}
		cout << arr[size - 1] << endl;
	}
}

template<class T>
T myArray<T>::getSum()
{
	if (size == 0)
		return 0;
	T sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += arr[i];
	}
	return sum;
}

template<class T>
void myArray<T>::search(T a)
{
	if (size == 0)
	{
		cout << "empty array" << endl;
		return;
	}
	T temp = a;
	int pos = 0;
	int flag = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == temp)
		{
			pos = i;
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		cout << "没找到" << endl;
		return;
	}
	else if (flag == 1)
	{
		cout << "找到了，该元素的下标是" << pos << endl;
		return;
	}
}


int main()
{
	myArray<double> doubleArr(5);
	doubleArr.printArr();
	cout << doubleArr.getSum() << endl;
	doubleArr.search(3.14);
	return 0;
}