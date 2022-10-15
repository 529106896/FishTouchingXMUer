#include <iostream>

using namespace std;

int factorial(int& n)
{
	int f = 1;
	while (n > 1)
	{
		f *= n;
		n--;
	}
	return f;
}

int factorial_1(int& n)
{
	int i = n;
	int f = 1;
	while (i > 1)
	{
		f *= i;
		i--;
	}
	return f;
}

int factorial_2(int n)
{
	int f = 1;
	while (n > 1)
	{
		f *= n;
		n--;
	}
	return f;
}

int main()
{
	int n;
	cin >> n;
	cout << factorial(n) << endl;
	cout << n << endl;
	cout << "以上的factorial函数问题在于：" << endl;
	cout << "把引用作为形参传进来，函数执行完后，实参也改变了" << endl;
	cout << "比如上面的n原来是5，执行完阶乘函数后，就变成了0" << endl;

	cout << "\n下面展示两种解决办法:" << endl;
	cout << "方法一：用临时变量" << endl;
	int a;
	cin >> a;
	cout << factorial_1(a) << endl;
	cout << a << endl;


	cout << "\n方法二：不用引用做参数" << endl;
	int b;
	cin >> b;
	cout << factorial_2(b) << endl;
	cout << b << endl;

	return 0;
}