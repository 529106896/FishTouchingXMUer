#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	int a[] = { 1,3,5,7,9,2,4,6,8,10 };
	int len = sizeof(a) / sizeof(int);
	sort(a, a + len);
	cout << "a数组升序排列输出：" << endl;
	for (int i = 0; i < len; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	vector<int> v(a, a + len);
	v.push_back(11);
	sort(v.rbegin(), v.rend());
	cout << "vector输降序排列输出：" << endl;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << "vector的容量：" << endl;
	cout << v.capacity() << endl;
	return 0;
}