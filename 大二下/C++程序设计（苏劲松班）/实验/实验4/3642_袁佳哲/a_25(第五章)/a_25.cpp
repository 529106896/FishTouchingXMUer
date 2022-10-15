#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>

using namespace std;

const int NAME_LEN = 20;
const int TABLE_LEN = 100;

struct TableItem	//名表的元素类型
{
	char name[NAME_LEN];	//关键词
};

TableItem name_table[TABLE_LEN];

int binary_search(char key[], TableItem t[], int num_of_items)
{
	int index, first, last;
	first = 0;
	last = num_of_items - 1;
	while (first <= last)
	{
		index = (first + last) / 2;
		int r = strcmp(key, t[index].name);
		if (r == 0)			//key等于t[index].name
			return index;
		else if (r > 0)
			first = index + 1;	//要查找的值大于中间的元素，就在后半部分继续查找
		else
			last = index - 1;	//要查找的值小于中间的元素，就在前半部分继续查找
	}
	return -1;
}

int binary_search_other(char key[], TableItem t[], int first, int last)		//递归算法
{
	if (first <= last)
	{
		int index = (first + last) / 2;
		int r = strcmp(key, t[index].name);
		if (r == 0)
			return index;
		else if (r > 0)
			return binary_search_other(key, t, index + 1, last);
		else
			return binary_search_other(key, t, first, index -1);
	}
	return -1;
}

int main()
{
	strcpy(name_table[0].name, "Mike");
	strcpy(name_table[1].name, "Nicholas");
	strcpy(name_table[2].name, "Tom");
	strcpy(name_table[3].name, "Jerry");
	strcpy(name_table[4].name, "Trump");
	strcpy(name_table[5].name, "Obama");
	strcpy(name_table[6].name, "Jesus");
	strcpy(name_table[7].name, "Darkholm");
	strcpy(name_table[8].name, "Heriton");

	char key[] = "Obama";

	//for (int i = 0; i < 9; i++)
	//{
	//	cout << name_table[i].name << endl;
	//}

	int pos_1 = binary_search(key, name_table, 8);
	int pos_2 = binary_search_other(key, name_table, 0, 7);

	cout << pos_1 << endl;
	cout << pos_2 << endl;

	return 0;
}