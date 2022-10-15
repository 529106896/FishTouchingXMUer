#include <iostream>

using namespace std;

double H_1(int n, double x)//迭代方法
{
    int h0 = 1;
    int h1 = 2*x;
    int i = 1;
    int result = 0;

    if(n==0)
        return h0;
    else if(n==1)
        return h1;
    else
    {
        for(int i=2; i<=n; i++)
        {
            result = 2*x*h1 - 2*(i-1)*h0;
            h0 = h1;
            h1 = result;   
        }
        return result;
    }
}

double H_2(int n, double x)  //递归方法
{
    if(n==0)
        return 1;
    else if(n==1)
        return 2*x;
    else
    {
        return 2*x*H_2(n-1, x) - 2*(n-1)*H_2(n-2, x);
    }
}

int main()
{
    cout << H_1(0, 5) << " " << H_2(0, 5) << endl;
    cout << H_1(1, 2) << " " << H_2(1, 2) << endl;
    cout << H_1(2, 2) << " " << H_2(2, 2) << endl;
    cout << H_1(3, 3) << " " << H_2(3, 3) << endl;
    system("pause");
    return 0;
}