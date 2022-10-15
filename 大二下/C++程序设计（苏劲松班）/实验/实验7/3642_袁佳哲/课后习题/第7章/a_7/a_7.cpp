#include <iostream>

using namespace std;

//时区（西12区——0时区——东12区）
enum TimeZone
{
	W12 = -12, W11, W10, W9, W8, W7, W6, W5, W4, W3, W2, W1, GMT, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11, E12
};
//
//struct TimeZone
//{
//	int W12 = -12;
//	int W11 = -11;
//	int W
//};

class Time
{
protected:
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

	void display() const
	{
		printf("%d时%d分%d秒\n", hour, min, sec);
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

	bool equal(Time other_time) const
	{
		if (hour == other_time.hour && min == other_time.min && this->sec == other_time.sec)
			return true;
		else
			return false;
	}

	bool less_than(Time other_time) const
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
};

class ExtTime : public Time
{
private:
	TimeZone timezone;

public:
	ExtTime()
	{
		timezone = GMT;
	}
	ExtTime(int h, int m, int s, TimeZone t) :Time(h, m, s)
	{
		timezone = t;
	}

	void set(int h, int m, int s ,TimeZone t)
	{
		Time::set(h, m, s);
		timezone = t;
	}

	void display() const
	{
		if (timezone < 0)
			printf("西%d区\t", -int(timezone));
		else if (timezone == 0)
			printf("GMT\t");
		else
			printf("西%d区\t", int(timezone));
		Time::display();
	}

	bool equal(const ExtTime other_time) const
	{
		Time t((hour + other_time.timezone - timezone + 24) % 24, min, sec);
		return t.equal(other_time);
	}

	bool less_than(const ExtTime other_time) const
	{
		Time t((hour + other_time.timezone - timezone + 24) % 24, min, sec);
		return t.less_than(other_time);
	}
};

int main()
{
	ExtTime t1(5,56,47,GMT);
	t1.display();
	ExtTime t2(5, 48, 14, W2);
	t2.display();
	if (t1.less_than(t2))
		cout << "t1比t2早" << endl;
	else
		cout << "t2比t1早" << endl;
	return 0;
}