#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

bool caseIgnoredOrder(string a, string b)
{
	transform(a.begin(), a.end(), a.begin(), ::tolower);
	transform(b.begin(), b.end(), b.begin(), ::tolower);
	return a < b;
}

int main()
{
	ifstream in;
	
	in.open("123.txt", ios::in);
	
	if (!in)
	{
		cerr << "input file not open!" << endl;
		exit(-1);
	}

	string line;
	vector<string> words;

	cout << "源文件内容：" << endl;

	while (getline(in, line))
	{
		cout << line << endl;
		words.push_back(line);
	}

	sort(words.begin(), words.end(), caseIgnoredOrder);

	cout << endl;

	cout << "忽略大小写的排序：" << endl;
	ofstream out;
	out.open("123.txt", ios::out);
	for (vector<string>::iterator it = words.begin(); it != words.end(); it++)
	{
		out << *it << endl;
		cout << *it << endl;
	}

	in.close();

	return 0;
}