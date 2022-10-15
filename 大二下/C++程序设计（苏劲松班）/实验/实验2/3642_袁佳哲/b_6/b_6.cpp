#include <iostream>

using namespace std;

double Fibonaci(int n)
{
    if (n == 1)
        return 1;
    if (n == 2)
        return 1;
    if (n > 2)
    {
        double temp1 = 1;
        double temp2 = 1;
        double result = 0;
        for (int i = 2; i < n; i++)
        {
            result = temp1 + temp2;
            temp1 = temp2;
            temp2 = result;
        }
        return result;
    }
}

int main()
{
    int n;
    cout.setf(ios::fixed, ios::floatfield);
    while (cin >> n)
        cout << "第n项为:" << Fibonaci(n) << endl;
    return 0;
}

