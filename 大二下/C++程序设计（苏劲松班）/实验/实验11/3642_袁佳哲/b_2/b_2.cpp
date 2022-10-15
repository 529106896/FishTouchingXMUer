#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
	string str = "uajnfhakjdawhraebwgndsm,fbmvhjsh,fkljfkjaegkhldjacxnvbjhfuhlkfnghbkkgdslk.fncxvbh,rkjelkjfjtr,kg,bfds";
	map<char, int> word;
	for (int i = 0; i < str.size(); i++)
	{
		map<char, int>::iterator it = word.find(str[i]);
		if (it != word.end())
		{
			int times = it->second;
			times++;
			word[str[i]] = times;
		}
		else
		{
			word[str[i]] = 1;
		}
	}
	for (map<char, int>::iterator it = word.begin(); it != word.end(); it++)
	{
		cout << "字符" << it->first << " " << it->second << "次" << endl;
	}

	return 0;
}