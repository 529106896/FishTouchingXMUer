#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
	ifstream in;
	in.open("123.txt", ios::in);
	if (!in)
	{
		cerr << "file not open!" << endl;
		exit(-1);
	}

	string line;
	vector<string> lines;

	cout << "文档内容如下：" << endl;
	while (getline(in, line))
	{
		cout << line << endl;
		lines.push_back(line);
	}

	cout << endl;

	cout << "请输入要查找的子串：";
	string searchString;
	cin >> searchString;

	int times = 0;
	int row = 1;
	for (vector<string>::iterator it = lines.begin(); it != lines.end(); it++)
	{
		int pos = 0;
		string currentString = *it;

		while ((pos = currentString.find(searchString, pos)) != string::npos)
		{
			printf("第%d行 第%d列\n", row, pos + 1);
			times++;
			pos++;
		}

		row++;
	}
	if (times == 0)
		cout << "没有找到要查找的子串" << endl;
	else
		cout << "总共出现次数：" << times << endl;


	in.close();

	return 0;
}