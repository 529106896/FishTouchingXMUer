#include <iostream>
using namespace std;

int find_replace_str(char str[], const char find_str[], const char replace_str[]) 
{
	int rep_times = 0;
	string str1 = str;
	string findstr1 = find_str;
	string replacestr1 = replace_str;

	int pos = str1.find(findstr1);

	while (pos != -1)
	{
		rep_times++;
		str1.replace(pos, findstr1.length(), replacestr1);
		pos = str1.find(findstr1);
	}

	cout << str1 << endl;
	return rep_times;
}
int main()
{
	char str[] = "Xiamen University";
	const char findstr[] = "ver";
	const char replacestr[] = "Version";
	printf("Replace \"%s\" in \"%s\" with \"%s\"\n",findstr, str, replacestr);
	int times = find_replace_str(str, findstr, replacestr);
	//cout << str << endl;
	cout << times << endl;
	return 0;
}