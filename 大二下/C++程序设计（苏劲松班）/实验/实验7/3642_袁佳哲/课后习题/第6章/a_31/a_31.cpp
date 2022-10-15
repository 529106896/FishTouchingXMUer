#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>

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

	String(const String& s)
	{
		str = new char[strlen(s.str) + 1];
		strcpy(str, s.str);
	}

	~String()
	{
		delete[] str;
		str = NULL;
	}

	String f()
	{
		String t("1234");
		return t;
	}

	//编译程序发现t是即将消亡的对象，把它编译成调用转移构造函数。
	//对象t消亡时不需要归还空间，等待返回值对象消亡才归还。

	//转移构造函数
	String(String&& x)
	{
		str = x.str;
		x.str = NULL;
	}

	//转移赋值函数
	String& operator=(String&& x)
	{
		if (&x == this)
			return *this;
		delete[]str;
		str = x.str;
		x.str = NULL;
		return *this;
	}
};

int main()
{
	String a = "abcd";
	a = a.f();
}