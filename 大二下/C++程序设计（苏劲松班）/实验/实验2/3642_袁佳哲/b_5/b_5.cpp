#include <iostream>
#include <string>
#include <algorithm>

#define TOUPPER

using namespace std;

int main()
{
    string str;
    getline(cin, str);
#ifdef TOUPPER
    cout << "把当前字符串转换为大写" << endl;
    transform(str.begin(), str.end(), str.begin(), ::toupper);
#else
    transform(str.begin(), str.end(), str.begin(), ::tolower);
#endif // TOUPPER
    cout << str;

    return 0;
}

