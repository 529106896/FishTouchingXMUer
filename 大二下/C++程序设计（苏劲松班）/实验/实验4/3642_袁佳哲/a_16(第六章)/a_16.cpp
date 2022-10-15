#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <algorithm>

using namespace std;

class String
{
	char* str;
public:
	String()
	{
		str = NULL;
	}

	String(const char* p)
	{
		str = new char[strlen(p) + 1];
		strcpy(str, p);
	}

	~String()
	{
		delete[] str;
		str = NULL;
	}

	const char* get_str()
	{
		return str;
	}

	bool is_substring(const char* sub_str)
	{
		int len = strlen(sub_str);
		int len1 = strlen(str) - len;
		for (int i = 0; i <= len1; i++)
		{
			if (strncmp(sub_str, str + i, len) == 0)
				return true;
		}
		return false;
	}

	bool is_substring(const String& str)
	{
		return is_substring(str.str);
	}

	String substring(int start, int length)
	{
		char* temp = new char[length + 1];
		strncpy(temp, str + start, length);
		temp[length] = '\0';
		return temp;
	}

	int find_replace_str(const char* find_str, const char* replace_str)
	{
		int rep_times = 0;
		string str1 = str;
		string findstr1 = find_str;
		string replacestr1 = replace_str;

		int pos = str1.find(findstr1);

		while (pos != string::npos)
		{
			rep_times++;
			str1.replace(pos, findstr1.length(), replacestr1);
			pos = str1.find(findstr1, pos + findstr1.length());
		}

		cout << str1 << endl;
		return rep_times;
	}

	void remove_spaces()
	{
		string str1 = str;
		str1.erase(remove(str1.begin(), str1.end(), ' '), str1.end());
		cout << str1 << endl;
	}

	int to_int()
	{
		string str1 = "11223344";
		int temp = stoi(str1);
		return temp;
	}

	int to_int_other()
	{
		string str1 = "123 456";
		int temp = 0;
		for (int i = 0; str1[i]; i++)
		{
			if (str1[i] == ' ')
				continue;
			temp = temp * 10 + (str1[i] - '0');
		}
		return temp;
	}

	void to_lower_case()
	{
		string str1 = str;
		transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
		cout << str1 << endl;
	}
};

int main()
{
	String str("Xiamen Uni Versity");
	cout << "str是" << str.get_str() << endl;
	if (str.is_substring("Xiamen"))
		cout << "Xiamen是str的子串" << endl;
	cout << "str从0开始，长度为6的子串是" << str.substring(0, 6).get_str() << endl;
	cout << "把str中的Ver替换为Version：";
	int times = str.find_replace_str("Ver", "Version");
	cout << "替换了" << times << "次" << endl;
	cout << "删除str中的空格：";
	str.remove_spaces();
	cout << "把字符串11223344转换成数字11223344：" << str.to_int() << endl;
	cout << "把字符串123 456转换成数字123456：" << str.to_int_other() << endl;
	cout << "把str中的大写字母都转换成小写字母：";
	str.to_lower_case();
	cout << endl;
	return 0;
}