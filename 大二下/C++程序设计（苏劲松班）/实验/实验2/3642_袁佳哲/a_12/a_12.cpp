#include <iostream>

using namespace std;

int path(int n)
{
    if(n == 1)
        return 0;
    if(n == 2)
        return 1;
    else if(n == 3)
        return 2;
    else if(n == 4)
        return 4;
    else
    {
        if(n%2!=0)
            return path(n-1) + path(n-2);
        else
            return path(n-1) + path(n-2) + path(n-3);
    }
}

int main()
{
    int n;
    while(cin >> n)
    {
        cout << "1->" << n << " path is " << path(n) << endl;
    }
    system("pause");
    return 0;
}
