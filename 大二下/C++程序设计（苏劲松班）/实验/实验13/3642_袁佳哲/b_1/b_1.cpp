#include <iostream>
#include <fstream>

using namespace std;

void check(double a, double b, double c)
{
	if (a + b <= c || a + c <= b || b + c <= a)
	{
		throw - 1;
	}
}


int main()
{
	double a, b, c;
	cout << "请输入三条边的长度：";

	while (1)
	{
		try
		{
			cin >> a >> b >> c;
			check(a, b, c);
			break;
		}
		catch (int)
		{
			cout << "两边之和应大于第三边！" << endl;
			cout << "请重新输入：";
		}
	}
	cout << "三条边的长度是：" << a << " " << b << " " << c << endl;
	double p = (a + b + c) / 2;
	double area = sqrt(p * (p - a) * (p - b) * (p - c));
	cout << "面积等于：" << area << endl;

	ofstream out;
	out.open("123.txt", ios::out);
	out << "三边长度：" << a << " " << b << " " << c << "  " << "面积：" << area << endl;

	cout << "信息已输出到\"123.txt\"" << endl;

	return 0;
}