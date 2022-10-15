#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void check(double a, double b, double c)
{
	if (a + b <= c || a + c <= b || b + c <= a)
	{
		throw - 1;
	}
}


int main()
{
	double a, b, c;
	double p, area;
	vector<string> results;

	while (1)
	{
		try
		{
			cout << "请输入三条边的长度(输入0 0 0结束)：";
			cin >> a >> b >> c;
			if (a == 0)
				break;
			check(a, b, c);
			p = (a + b + c) / 2;
			area = sqrt(p * (p - a) * (p - b) * (p - c));
			cout << "当前三角形面积为：" << area << endl;
			string temp = "三边长：" + to_string(a) + " " + to_string(b) + " " + to_string(c) + " " + "面积：" + to_string(area);
			//cout << temp << endl;
			results.push_back(temp);
		}
		catch (int)
		{
			cout << "数据出错！两边之和应大于第三边！" << endl;
		}
	}

	string savePath;
	ofstream out;

	while (1)
	{
		try
		{
			cout << "请输入保存文件名：";
			cin >> savePath;
			out.open(savePath.c_str(), ios::out);
			if (!out)
				throw - 1;
			for (vector<string>::iterator it = results.begin(); it != results.end(); it++)
			{
				out << *it << endl;
			}
			cout << "结果保存至" << savePath << endl;
			break;
			//fstream out;
		}
		catch (int)
		{
			cout << "文件打开失败！请重新输入文件名！" << endl;
		}
	}

	

	return 0;
}