#include <iostream>

using namespace std;

class A
{
private:
	//这个flag用来判断是否是第一个对象
	static A* flag;

public:
	static A* test();
};

A* A::flag = NULL;

A* A::test()
{
	if (flag == NULL)
	{
		flag = new A;
	}
	return flag;
}

int main() 
{
	A* a = A::test();
	A* b = A::test();
	cout << "a's address:" << a << endl;
	cout << "b's address:" << b << endl;
	//如果输出的a和b地址相同，就说明创建第二个对象时只返回了第一个对象的指针
	return 0;
}