#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

enum Sex { male = 0, female };
enum Major { mathematics = 0, physics, chemistry};

struct Date
{
	int year;
	int month;
	int day;
};

class Student
{
private:
	string id;
	string name;
	Sex sex;
	Date birth_date;
	string birth_place;
	Major major;
	bool initialized;

public:
	Student()
	{
		initialized = false;
		birth_place = "";
		major = chemistry;
		sex = male;
		birth_date.year = 0;
	}
	bool data_is_ok()
	{
		return initialized;
	}
	friend istream& operator >>(istream& in, Student& x);
	friend ostream& operator <<(ostream& out, Student& x);
};

istream& operator >>(istream& in, Student& x)
{
	if (&in == &cin)
		cout << "请输入学号、姓名、性别(0:male 1:female)、出生日期(年 月 日)、出生地点、专业(0数 1物 2化)：" << endl;
	cout << "以学号为'E'结束" << endl;
	in >> x.id;
	if (in.eof() || x.id == "E")
	{
		x.initialized = false;
		return in;
	}
	in >> x.name;
	int sex;
	cin >> sex;
	if (sex == 0)
	{
		x.sex = male;
	}
	else if (sex == 1)
		x.sex == female;
	else
	{
		x.initialized = false;
		cout << "性别输入错误！" << endl;
		return in;
	}
	in >> x.birth_date.year >> x.birth_date.month >> x.birth_date.day;
	in >> x.birth_place;
	int major;
	cin >> major;
	switch (major)
	{
	case 0:
		x.major = mathematics;
		break;
	case 1:
		x.major = physics;
		break;
	case 2:
		x.major = chemistry;
		break;
	default:
		x.initialized = false;
		cout << "专业输入错误！" << endl;
		return in;
	}
	x.initialized = true;
	return in;
}

ostream& operator <<(ostream& out, Student& x)
{
	out << x.id << " "
		<< x.name << " "
		<< (x.sex == male ? "男" : "女") << " "
		<< x.birth_date.year << "-" << x.birth_date.month << "-" << x.birth_date.day << " "
		<< x.birth_place << " "
		<< (x.major == mathematics ? "数学" : (x.major == physics ? "物理" : "化学"));
	return out;
}

int main()
{
	ofstream out("123.txt", ios::out);
	Student st;
	cin >> st;
	while (st.data_is_ok())
	{
		cout << "输入成功！" << endl;
		out << st << endl;
		cin >> st;
	}
	return 0;
}
