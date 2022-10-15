#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

class Date
{
private:
	int year;
	int month;
	int day;

public:
	Date()
	{
		year = 0;
		month = 0;
		day = 0;
	}
	Date(int y, int m, int d)
	{
		year = y;
		month = m;
		day = d;
	}

	void set_date(int y, int m, int d)
	{
		year = y;
		month = m;
		day = d;
	}
	
	int getYear()
	{
		return year;
	}

	int getMonth()
	{
		return month;
	}

	int getDay()
	{
		return day;
	}

	void increment()
	{
		int day_max = 0;
		switch (month)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			day_max = 31;
			break;

		case 4:
		case 6:
		case 9:
		case 11:
			day_max = 30;
			break;

		case 2:
			if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0)
				day_max = 29;
			else
				day_max = 28;
			break;
		}
		if (day < day_max)
			day++;
		else if (month < 12)
		{
			day = 1;
			month++;
		}
		else
		{
			day = 1;
			month = 1;
			year++;
		}
	}

	bool operator==(Date& d)
	{
		return (year == d.year && month == d.month && day == d.day);
	}

	bool operator>(Date& d)
	{
		return ((year > d.year) || (year == d.year && month > d.month) || (year == d.year && month == d.month && day > d.day));
	}

	bool operator>=(Date& d)
	{
		return ((year >= d.year) || (year == d.year && month >= d.month) || (year == d.year && month == d.month && day >= d.day));
	}

	bool operator<(Date& d)
	{
		return ((year < d.year) || (year == d.year && month < d.month) || (year == d.year && month == d.month && day < d.day));
	}

	bool operator<=(Date& d)
	{
		return ((year <= d.year) || (year == d.year && month <= d.month) || (year == d.year && month == d.month && day <= d.day));
	}

	bool operator!=(Date& d) {
		return (year != d.year || month != d.month || day != d.day);
	}

	int operator-(Date& d)
	{
		int n = 0;
		if (*this == d)
			n = 0;
		else if (*this >= d)
		{
			while (*this != d)
			{
				d.increment();
				n++;
			}
		}
		else
		{
			while (*this != d)
			{
				(*this).increment();
				n--;
			}

		}
		return n;
	}

};

bool sort_by_date(pair<string, Date> &p1, pair<string, Date> &p2)
{
	return p1.second < p2.second;
}

int main()
{
	map<string, Date>m_person;
	m_person["袁佳哲"] = Date(2001, 8, 21);
	m_person["徐荪睿"] = Date(2002, 5, 1);
	m_person["李云龙"] = Date(1923, 8, 7);
	m_person["李狗蛋"] = Date(1997, 1, 2);
	m_person["张大炮"] = Date(2002, 2, 28);
	m_person["李二狗"] = Date(1888, 7, 24);

	map<string, Date>::iterator it;
	
	vector<pair<string, Date> > v_person;
	for (it = m_person.begin(); it != m_person.end(); it++)
	{
		v_person.push_back(make_pair(it->first, it->second));
	}

	vector<pair<string, Date> >::iterator it2;
	cout << "名表如下" << endl;
	for (it2 = v_person.begin(); it2 != v_person.end(); it2++)
	{
		cout << "姓名：" << it2->first << "\t";
		cout << "出生日期：" 
			<< it2->second.getYear() << "年" 
			<< it2->second.getMonth() << "月" 
			<< it2->second.getDay() << "日" << endl;
	}

	sort(v_person.begin(), v_person.end(), sort_by_date);

	cout << endl;
	cout << "按出生日期排序如下：" << endl;
	for (it2 = v_person.begin(); it2 != v_person.end(); it2++)
	{
		cout << "姓名：" << it2->first << "\t";
		cout << "出生日期："
			<< it2->second.getYear() << "年"
			<< it2->second.getMonth() << "月"
			<< it2->second.getDay() << "日" << endl;
	}

	cout << endl << "下面进入查询功能：" << endl;
	string name;
	cout << "请输入要查询人的姓名：";
	cin >> name;
	it = m_person.find(name);
	if (it == m_person.end())
		cout << "没有这个人！" << endl;
	else
	{
		cout << "已找到对应人，信息如下：" << endl;
		cout << "姓名：" << it->first << "\t";
		cout << "出生日期："
			<< it->second.getYear() << "年"
			<< it->second.getMonth() << "月"
			<< it->second.getDay() << "日" << endl;
	}
		
	return 0;
}