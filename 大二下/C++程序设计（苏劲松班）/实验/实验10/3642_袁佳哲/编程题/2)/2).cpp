#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

template <class T>
T Min(T a, T b)
{
	return a < b ? a : b;
}

int main()
{
	cout << Min(5, 9) << endl;
	cout << Min(3.14, 6.28) << endl;
	cout << Min('A', 'b') << endl;
	cout << Min("China", "America") << endl;
	return 0;
}