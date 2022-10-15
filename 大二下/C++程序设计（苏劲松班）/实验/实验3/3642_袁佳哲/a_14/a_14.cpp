#include <iostream>

using namespace std;

int squezze(char s1[], const char s2[])
{
	int sum = 0;
	int i, j, k;
	for (i = 0; s1[i]; i++)
	{
		for (j = 0; s2[j]; j++)
		{
			if (s1[i] == s2[j])
			{
				sum++;
				for (k = i + 1; s1[k]; k++)
				{
					s1[k - 1] = s1[k];
				}
				s1[k - 1] = '\0';
			}
		}
	}
	return sum;
}

int main()
{
	char s1[] = "Xiamen University";
	int count = squezze(s1, "Uni");
	cout << s1 << endl;
	cout << count << endl;
	return 0;
}