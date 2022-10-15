#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	vector<int> v{ 1,2,3,4,5,6,7,8,9 };
	int sum = 0;
	for_each(v.begin(), v.end(), [&sum](int x) {if(x>4)sum += x; });
	cout << sum << endl;
	return 0;
}