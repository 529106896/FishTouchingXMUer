#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const pair<string, int>& x, const pair<string, int>& y)
{
	return x.second > y.second;
}

int main()
{
	ifstream in("123.txt", ios::in);
	string str;
	map<string, int> words;
	while (!in.eof())
	{
		in >> str;
		str.erase(remove(str.begin(),str.end(),','));
		str.erase(remove(str.begin(), str.end(), '.'));
		map<string, int>::iterator it = words.find(str);
		if (it != words.end())
		{
			int times = it->second;
			times++;
			words[str] = times;
		}
		else
		{
			words[str] = 1;
		}
	}
	vector<pair<string, int> > wordsV;
	for (map<string, int>::iterator it = words.begin(); it != words.end(); it++)
	{
		wordsV.push_back(make_pair(it->first, it->second));
	}
	sort(wordsV.begin(), wordsV.end(), cmp);
	for (vector<pair<string, int> >::iterator it = wordsV.begin(); it != wordsV.end(); it++)
	{
		//cout << "单词 " << it->first << "		" << it->second << "次" << endl;
		printf("单词：%-12s%12d次\n", it->first.c_str(), it->second);
	}
	in.close();
	return 0;
}
