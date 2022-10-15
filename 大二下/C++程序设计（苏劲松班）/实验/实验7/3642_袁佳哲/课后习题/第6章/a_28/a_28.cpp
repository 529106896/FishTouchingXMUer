#include <iostream>
#include "INT.h"

using namespace std;

int main()
{
	INT test1("999", 3);
	INT test2("145", 3);
	INT test3("-888", 3);
	INT output1 = test1 + test2;
	cout << output1 << endl;
	INT output2 = test1 + 145;
	cout << output2 << endl;
	INT output3 = test1 - test2;
	cout << output3 << endl;
	INT output4 = test1 - 1000;
	cout << output4 << endl;
	string a = "786453216543156342186745310334132654";
	INT test_max("786453216543156342186745310334132654", 36);
	INT test4("1", 1);
	INT out_put_max = test_max + test4;
	cout << out_put_max << endl;
	//cout << output2 << endl;
	return 0;
}