#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    string str1;
    cout << "请输入原句:" << endl;
    getline(cin, str1);
    cout << endl;
    cout << "str1原句是:" << endl << str1 << endl;
    char* str2 = new char[100];
    int j = 0;
    for (int i = 0; i < str1.length(); i++)
    {
        if (str1[1] != ' ')
        {
            str2[i] = str1[i] + 8;
            j++;
        }
        else
        {
            str2[i] = str1[i];
            j++;
        }
    }

    cout << endl;
    cout << "加密后的str2是:" << endl;
    for (int i = 0; i < j; i++)
    {
        cout << str2[i];
    }
    cout << endl;

    for (int i = 0; i < j; i++)
    {
        if (str2[i] == ' ')
            continue;
        else
            str2[i] -= 8;
    }

    cout << endl;

    cout << "解密后的str2是:" << endl;
    for (int i = 0; i < j; i++)
    {
        cout << str2[i];
    }
    cout << endl;

    int flag = 0;

    for (int i = 0; i < j; i++)
    {
        if (str1[i] == str2[i])
            continue;
        else
            flag++;
    }

    cout << endl;

    if (flag == 0)
        cout << "验证成功" << endl;
    else
        cout << "验证失败" << endl;

    return 0;
}

