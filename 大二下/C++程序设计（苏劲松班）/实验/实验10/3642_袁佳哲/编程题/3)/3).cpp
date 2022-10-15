//错误1：头文件错误：#include <iostream.h>
#include <iostream>

//错误2：没有写using namespace std;
using namespace std;

template <class T>
//错误4：min和C++自带的min函数冲突
T Min(T a, T b)
{
    if (a < b)
        return a;
    else
        return b;
}

void main()
{
    int i1 = 10, i2 = 20;
    double d1 = 3.5, d2 = 1.2;

    //错误3：使用全角单引号
    //char c1 = ’b’, c2 = ’x’;
    char c1 = 'b', c2 = 'x';


    cout << Min(i1, i2) << endl;
    cout << Min(d1, d2) << endl;

    //错误5：没有ci1这个参数
    //如果是i1，还会出现没有匹配的模板的错误
    //cout << Min(ci1, c2) << endl;

    //错误6：两个实参中间不加逗号，并且没有c12这个参数
    //cout << Min(i1c12) << endl;

    //错误7：没有匹配的模板
    //cout << Min(i1, d2) << endl;
    cout << Min<int>(i1, d2) << endl;
}
