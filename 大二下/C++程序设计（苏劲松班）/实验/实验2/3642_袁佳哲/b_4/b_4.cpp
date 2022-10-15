#include <iostream>

using namespace std;

void convert(int n)
{
    int temp;
    temp = n / 10;
    if (temp != 0)
        convert(temp);
    putchar(n % 10 + '0');
}

int main()
{
    int n;
    cin >> n;
    convert(n);
    cout << endl;
    return 0;
}

