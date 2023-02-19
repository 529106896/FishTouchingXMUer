#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);

	//cout << a.size() << endl;
	//cout << sizeof(int) * a.size() << endl;

	int* b = new int[a.size()];
	memcpy(b, &a[0], a.size() * sizeof(int));



	for (int i = 0; b[i]; i++)
	{
		cout << b[i] << endl;
	}
	
	return 0;
}