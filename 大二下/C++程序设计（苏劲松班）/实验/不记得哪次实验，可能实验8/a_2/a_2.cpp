#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int main()
{
	FILE* in;
	in = fopen("source.txt", "rb");
	char data;
	int lines = 1;
	cout << "源文件source.txt内容展示如下：" << endl;
	while (!feof(in))
	{
		fread(&data, sizeof(char), 1, in);
		if (data == '\n')
			lines++;
		cout << data;
	}
	cout << endl;
	cout << "总行数：" << lines << endl;
	fclose(in);
	return 0;
}