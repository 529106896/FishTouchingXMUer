#include <iostream>
#include <cmath>

using namespace std;

class vector_TD
{
private:
	int x;	//在x轴上的分量
	int y;	//在y轴上的分量
	int z;	//在z轴上的分量

public:
	vector_TD()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	vector_TD(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void show()
	{
		if (x > 0)
			cout << x << "i" << " ";
		else if (x < 0)
			cout << x << "i" << " ";
		else;

		if (y > 0)
			cout << "+" << " " << y << "j" << " ";
		else if (y < 0)
			cout << y << "j" << " ";
		else;

		if (z > 0)
			cout << "+" << " " << z << "k" << endl;
		else if (y < 0)
			cout << z << "k" << endl;
		else;
	}

	bool operator>(vector_TD& v)
	{
		double t1 = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
		double t2 = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

		if (t1 > t2)
			return true;
		else
			return false;
	}

	bool operator<(vector_TD& v)
	{
		double t1 = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
		double t2 = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

		if (t1 < t2)
			return true;
		else
			return false;
	}
};

int main()
{
	vector_TD v1(-1,5,3);
	v1.show();
	vector_TD v2(2, 4, 1);
	v2.show();
	if (v1 < v2)
		cout << "v1 < v2" << endl;
	if (v1 > v2)
		cout << "v1 > v2" << endl;
}