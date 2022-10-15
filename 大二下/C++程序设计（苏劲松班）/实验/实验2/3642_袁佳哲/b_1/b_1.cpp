#include <iostream>
#include <cctype>

using namespace std;

int main()
{
    char *str1 = new char[100];
    char *str2 = new char[100];
    cin >> str1;
    int j = 0;

    for(int i=0; str1[i]; i++)
    {
        if(!ispunct(str1[i]))
        {
            str2[j] = str1[i];
            j++;
        }
    }

    for(int i=0; i<j; i++)
        cout << str2[i];
    cout << endl;
    
    delete [] str1;
    delete [] str2;
    system("pause");
    return 0;
}
