#include <iostream>
#include <cmath>

using namespace std;

class Point
{
private:
	double x;
	double y;

public:
	void set_x(int a);
	double get_x();
	void set_y(int b);
	double get_y();
	double r();
	double theta();
	double distance(const Point& p);
	Point relative(const Point& p);
	bool is_above_left(const Point& p);
};

void Point::set_x(int a)
{
	x = a;
}

double Point::get_x()
{
	return x;
}

void Point::set_y(int b)
{
	y = b;
}

double Point::get_y()
{
	return y;
}

double Point::r()
{
	return sqrt(x * x + y * y);
}

double Point::theta()
{
	return atan(y / x);
}

double Point::distance(const Point& p)
{
	return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
}

Point Point::relative(const Point& p)
{
	Point temp;
	temp.x = x - p.x;
	temp.y = y - p.y;
	return temp;
}

bool Point::is_above_left(const Point& p)
{
	if (x < p.x && y > p.y)
		return true;
	else
		return false;
}

int main()
{
	Point a, b;
	a.set_x(1);
	a.set_y(2);
	b.set_x(3);
	b.set_y(4);
	printf("a的直角坐标是(%lf, %lf)\n", a.get_x(), a.get_y());
	printf("b的直角坐标是(%lf, %lf)\n", b.get_x(), b.get_y());
	cout << "a点的极半径 = " << a.r() << endl;
	cout << "b点的极半径 = " << b.r() << endl;
	cout << "a的极角 = " << a.theta() << endl;
	cout << "b的极角 = " << b.theta() << endl;
	cout << "a与b的距离 = " << a.distance(b) << endl;
	printf("a与b的相对坐标是(%lf, %lf)\n", a.relative(b).get_x(), a.relative(b).get_y());
	if (a.is_above_left(b))
		cout << "a在b的左上方" << endl;
	else
		cout << "a不在b的左上方" << endl;
	return 0;
}
