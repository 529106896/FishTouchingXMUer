#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//bool mycmp(int value1, int value2)
//{
//	return value1 < value2;
//}

template <typename T>
void printVec(T begin, T end)
{
	for (auto it = begin; it != end; it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

template<typename T>
void stable_qsort(T begin, T end)
{
	if (end - begin <= 1)
		return;
	auto start = *begin;
	//lambda表达式
	auto mid = stable_partition(begin, end, [start](const int& value) {return value < start; });
	if (mid > begin)
	{
		stable_qsort(begin, mid);
	}
	if (mid < end - 1)
	{
		stable_qsort(mid + 1, end);
	}
}

int main()
{
	vector<int> n{ 9,4,5,8,9,1,7,64,512,456,4,123,4654 };
	cout << "原数字序列：" << endl;
	printVec(n.begin(),n.end());
	stable_qsort(n.begin(), n.end());
	cout << "稳定的快速排序：" << endl;
	printVec(n.begin(), n.end());
	return 0;
}