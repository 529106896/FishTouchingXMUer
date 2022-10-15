#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str1;
    getline(cin, str1);
    for (int i = str1.length() - 1; i >= 0; i--)
    {
        cout << str1[i];
    }
    cout << endl;

    return 0;
}

