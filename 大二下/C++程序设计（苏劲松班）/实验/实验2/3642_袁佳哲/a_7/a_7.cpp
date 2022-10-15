#include <iostream>

using namespace std;

int digit(long n, int k)
{
    int result = 0;
    int i = 1;
    while(i<k)
    {
        n = n/10;
        i++;
    }
    result = n%10;
    return result;
}

int main()
{
    cout << digit(123456, 5) << endl;
    cout << digit(1234, 5) << endl;
    system("pause");
    return 0;
}