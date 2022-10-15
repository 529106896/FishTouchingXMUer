#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

class phoneBook
{
private:
	int no;
	string name;
	string job;
	string phone;
	bool initialized;

public:
	phoneBook() 
	{ 
		no = 0;
		initialized = false; 
	};
	bool data_is_ok() { return initialized; };
	friend istream& operator >>(istream& in, phoneBook& x);
	friend ostream& operator <<(ostream& out, phoneBook& x);
};

istream& operator >>(istream& in, phoneBook& x)
{
	if (&in == &cin)
		cout << "请输入序号、姓名、单位、电话号码（以序号-1结束）：" << endl;
	in >> x.no;
	if (in.eof() || x.no == -1)
	{
		x.initialized = false;
		return in;
	}
	in >> x.name;
	in >> x.job;
	in >> x.phone;
	x.initialized = true;
	return in;
}

ostream& operator <<(ostream& out, phoneBook& x)
{
	out << x.no << " " << x.name << " " << x.job << " " << x.phone << endl;
	return out;
}

int main()
{
	ofstream out("123.txt", ios::out);
	//out.seekp(ios::end);
	if (!out)
	{
		cerr << "No such file" << endl;
		return -1;
	}
	phoneBook pb;
	cin >> pb;
	while (pb.data_is_ok())
	{
		//cout << pb << endl;
		cout << "输入成功！" << endl;
		out << pb << endl;
		cin >> pb;
	}
	out.close();
	return 0;
}
