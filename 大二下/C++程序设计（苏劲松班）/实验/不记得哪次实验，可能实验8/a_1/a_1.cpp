#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int main()
{
	FILE* in;
	FILE* out;
	in = fopen("source.txt", "rb");
	out = fopen("destination.txt", "wb");
	char data;
	cout << "源文件source.txt内容展示如下：" << endl;
	while (!feof(in))
	{
		fread(&data, sizeof(char), 1, in);
		fwrite(&data, sizeof(char), 1, out);
		cout << data;
	}
	cout << endl << endl;
	cout << "目的文件为destination.txt" << endl;
	fclose(in);
	fclose(out);
	return 0;
}