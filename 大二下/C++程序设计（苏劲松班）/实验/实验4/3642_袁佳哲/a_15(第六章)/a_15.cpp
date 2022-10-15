#include <iostream>

using namespace std;

class Date
{
private:
	int year;
	int month;
	int day;

public:
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
		int day_max;
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
};

int main()
{
	Date d1(2001, 10, 15);
	d1.display_date();
	d1.increment();
	d1.display_date();
	d1.set_date(2001, 10, 31);
	d1.display_date();
	d1.increment();
	d1.display_date();
	d1.set_date(2001, 12, 31);
	d1.display_date();
	d1.increment();
	d1.display_date();
	return 0;
}