#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
	map<double, string> student;
	student[99] = "李云龙";
	student[59] = "张大炮";
	student[85] = "李贵林";
	student[45] = "潘子";
	student[79] = "宋亮";
	student[34] = "嘎子";
	student[66] = "曾鸣";
	int sum = 0;
	for_each(student.begin(), student.end(), [&sum](map<double, string>::reference a)
		{
			if (a.first < 60)
				cout << a.second << "的成绩是" << a.first << "，不及格" << endl;
			sum += a.first;
		});
	cout << "平均分是" << sum / student.size() << endl;

	cout << endl;

	//map默认按key值升序排列，所以不用sort了，直接反向遍历即可
	for (map<double, string>::reverse_iterator it = student.rbegin(); it != student.rend(); it++)
	{
		cout << it->second << " " << "成绩：" << it->first << endl;
	}
	return 0;
}