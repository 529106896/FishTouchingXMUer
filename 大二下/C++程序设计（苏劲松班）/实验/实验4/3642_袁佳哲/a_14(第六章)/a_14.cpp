#include <iostream>

using namespace std;

class Time
{
private:
	int hour;		//时
	int min;		//分
	int sec;		//秒

public:
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
};

int main()
{
	Time t1(1, 20, 30);
	Time t2(0, 10, 59);
	t1.display();
	t2.display();
	if (t2.less_than(t1))
		cout << "t2比t1早" << endl;
	t2.increment();
	cout << "t2加一秒" << endl;
	t2.display();
	t2.set(23, 59, 59);
	t2.display();
	cout << "t2加一秒" << endl;
	t2.increment();
	t2.display();
	return 0;
}