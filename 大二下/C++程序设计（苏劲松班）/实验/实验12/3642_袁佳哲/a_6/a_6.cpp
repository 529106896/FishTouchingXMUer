#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

class Shape
{
protected:
	double width;
	double height;

public:
	virtual double getArea() = 0;
};

class Rectangle : public Shape
{
private:
	bool initialized;

public:
	Rectangle() { initialized = false; }
	double getArea()
	{
		return width * height;
	}
	bool data_is_ok()
	{
		return initialized;
	}
	friend istream& operator >>(istream& in, Rectangle& x);
	friend ostream& operator <<(ostream& out, Rectangle& x);
};

istream& operator >>(istream& in, Rectangle& x)
{
	if (&in == &cin)
		cout << "请输入矩形长、宽：" << endl;
	if (in.eof())
	{
		x.initialized = false;
		return in;
	}
	in >> x.width;
	in >> x.height;
	if (x .width < 0 || x.height < 0)
	{
		cout << "长/宽不能为负数！" << endl;
		x.initialized = false;
		return in;
	}
	x.initialized = true;
	return in;
}

ostream& operator <<(ostream& out, Rectangle& x)
{
	if (x.initialized == false)
	{
		out << "该矩形输入数据有错！";
		return out;
	}
	out << "矩形数据：" << " "
		<< "长：" << x.width << " "
		<< "宽：" << x.height << " "
		<< "面积：" << x.getArea();
	return out;
}

class Triangle : public Shape
{
private:
	bool initialized;

public:
	Triangle() { initialized = false; }
	double getArea()
	{
		return (width * height)/2;
	}
	bool data_is_ok()
	{
		return initialized;
	}
	friend istream& operator >>(istream& in, Triangle& x);
	friend ostream& operator <<(ostream& out, Triangle& x);
};

istream& operator >>(istream& in, Triangle& x)
{
	if (&in == &cin)
		cout << "请输入三角形的底、高：" << endl;
	if (in.eof())
	{
		x.initialized = false;
		return in;
	}
	in >> x.width;
	in >> x.height;
	if (x.width < 0 || x.height < 0)
	{
		cout << "底/高不能为负数！" << endl;
		x.initialized = false;
		return in;
	}
	x.initialized = true;
	return in;
}

ostream& operator <<(ostream& out, Triangle& x)
{
	if (x.initialized == false)
	{
		out << "该三角形输入数据有错！";
		return out;
	}
	out << "三角形数据：" << " "
		<< "底：" << x.width << " "
		<< "高：" << x.height << " "
		<< "面积：" << x.getArea();
	return out;
}

int main()
{
	ofstream out("123.txt", ios::out);
	ifstream in("123.txt", ios::in);
	int choice;
	cout << "下面进行图形信息输入，请做出选择(0:矩形 1:三角形 -1:退出输入)：" << endl;
	Rectangle rect;
	Triangle tri;
	int flag = 1;
	cin >> choice;
	while (flag)
	{
		switch (choice)
		{
		case 0:
			cin >> rect;
			out << rect << endl;
			break;
		case 1:
			cin >> tri;
			out << tri << endl;
			break;
		case -1:
			flag = 0;
			break;
		default:
			cout << "选项不正确！" << endl;
			break;
		}
		if (flag == 1)
		{
			cout << "下面进行图形信息输入，请做出选择(0:矩形 1:三角形 -1:退出输入)：" << endl;
			cin >> choice;
		}
	}
	cout << "是否查看图形信息？(查看：0  不查看：1)" << endl;
	int choice1;
	char info[100];
	cin >> choice1;
	switch (choice1)
	{
	case 0:
		cout << "全部图形信息如下" << endl;
		while (!in.eof())
		{
			in.getline(info, 100);
			cout << info << endl;
		}
		break;
	case 1:
		cout << "不查看，拜拜！" << endl;
		break;
	default:
		cout << "选项不对，拜拜！" << endl;
		break;
	}
	in.close();
	out.close();
	return 0;
}
