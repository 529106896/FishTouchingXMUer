#include <iostream>

using namespace std;

//时间类
class Time
{
private:
	int hour;		//时
	int min;		//分
	int sec;		//秒

public:
	Time()
	{
		hour = 0;
		min = 0;
		sec = 0;
	}
	Time(int h, int m, int s)
	{
		hour = h;
		min = m;
		sec = s;
	}

	void set(int h, int m, int s)
	{
		hour = h;
		min = m;
		sec = s;
	}

	void display()
	{
		printf("现在时间是：%d时%d分%d秒\n", hour, min, sec);
	}

	void increment()
	{
		if (sec == 59)
		{
			if (min == 59)
			{
				if (hour == 23)
				{
					hour = 0;
					min = 0;
					sec = 0;
				}
				else
				{
					hour++;
					min = 0;
					sec = 0;
				}
			}
			else
			{
				min++;
				sec = 0;
			}
		}
		else
			sec++;
	}

	bool equal(Time& other_time)
	{
		if (hour == other_time.hour && min == other_time.min && this->sec == other_time.sec)
			return true;
		else
			return false;
	}

	bool less_than(Time& other_time)
	{
		if (hour < other_time.hour)
			return true;
		else if (hour == other_time.hour)
		{
			if (min < other_time.min)
				return true;
			else if (min == other_time.min)
			{
				if (sec < other_time.sec)
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}

	bool operator==(Time& t)
	{
		if (hour == t.hour && min == t.min && sec == t.sec)
			return true;
		else
			return false;
	}

	bool operator!=(Time& t)
	{
		if (hour != t.hour || min != t.min || sec != t.sec)
			return true;
		else
			return false;
	}

	bool operator>(Time& t)
	{
		if (hour > t.hour || (hour == t.hour && min > t.min) || (hour == t.hour && min == t.min && sec > t.sec))
			return true;
		else
			return false;
	}

	bool operator>=(Time& t)
	{
		if (hour >= t.hour || (hour == t.hour && min >= t.min) || (hour == t.hour && min == t.min && sec >= t.sec))
			return true;
		else
			return false;
	}

	bool operator<(Time& t)
	{
		//if (hour > t.hour || (hour == t.hour && min > t.min) || (hour == t.hour && min == t.min && sec > t.sec) || (hour == t.hour && min == t.min && sec == t.sec))
		if(*this > t || *this == t)
			return false;
		else
			return true;
	}

	bool operator <=(Time& t)
	{
		//if (hour > t.hour || (hour == t.hour && min > t.min) || (hour == t.hour && min == t.min && sec > t.sec))
		if(*this > t)
			return false;
		else 
			return true;
	}

	Time& operator++()
	{
		int hourAdd = 0;
		int minAdd = 0;
		int secAdd = 1;
		if (sec + secAdd < 60)
			sec += secAdd;
		else
		{
			sec += secAdd;
			minAdd++;
		}

		if (min + minAdd < 60)
			min += minAdd;
		else
		{
			min += minAdd;
			hourAdd++;
		}

		if (hour + hourAdd < 24)
			hour += hourAdd;
		else
		{
			hour += hourAdd;
			hour = hour + hourAdd - 24;
		}

		return *this;
	}

	Time& operator+=(int s)
	{
		int hourAdd = s / 3600;
		int minAdd = (s - hourAdd * 3600) / 60;
		int secAdd = s - hourAdd * 3600 - minAdd * 60;
		if (sec + secAdd < 60)
			sec += secAdd;
		else
		{
			sec += secAdd;
			minAdd++;
		}

		if (min + minAdd < 60)
			min += minAdd;
		else
		{
			min += minAdd;
			hourAdd++;
		}

		if (hour + hourAdd < 24)
			hour += hourAdd;
		else
		{
			hour += hourAdd;
			hour = hour + hourAdd - 24;
		}

		return *this;
	}

	int operator-(Time& t)
	{
		int s = (hour - t.hour) * 3600 + (min - t.min) * 60 + sec - t.sec;
		return s;
	}
};

//日期类
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

	void display_date()
	{
		printf("今天是%d年%d月%d日\n", year, month, day);
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

class TimeWithDate
{
private:
	Date date;
	Time time;

public:
	TimeWithDate(int year, int mon, int day, int hour, int min, int sec)
	{
		date = Date(year, mon, day);
		time = Time(hour, min, sec);
	}

	bool operator == (TimeWithDate& td)
	{
		return ((date == td.date) && (time == td.time));
	}

	bool operator != (TimeWithDate& td)
	{
		return ((date != td.date) || (time != td.time));
	}

	bool operator >(TimeWithDate& td)
	{
		return ((date > td.date) || (date == td.date && time > td.time));
	}

	bool operator >=(TimeWithDate& td)
	{
		return ((date >= td.date) || (date == td.date && time >= td.time));
	}

	bool operator <(TimeWithDate& td) {
		return ((date < td.date) || (date == td.date && time < td.time));
	}

	bool operator <=(TimeWithDate& td) {
		return ((date <= td.date) || (date == td.date && time <= td.time));
	}

	TimeWithDate& operator+=(int s)
	{
		int dayAdd = s / 86400;
		s = s - dayAdd * 86400;

		for (int i = 0; i < dayAdd; i++)
		{
			date.increment();
		}

		time += s;
		return *this;
	}

	int operator-(TimeWithDate& td)
	{
		int dayGap = date - td.date;
		int secGap = time - td.time;
		int s = dayGap * 86400 + secGap;
		return s;
	}

	void show()
	{
		date.display_date();
		time.display();
	}
};

int main()
{
	TimeWithDate td1(2021, 4, 29, 22, 43, 36);
	TimeWithDate td2(2021, 4, 28, 22, 43, 37);
	cout << td1 - td2 << endl;

	td1.show();
	td1 += 25;
	td1.show();

	if (td1 > td2)
	{
		cout << "td1比td2大" << endl;
	}

	//cout << td2 - td1 << endl;
	return 0;
}
