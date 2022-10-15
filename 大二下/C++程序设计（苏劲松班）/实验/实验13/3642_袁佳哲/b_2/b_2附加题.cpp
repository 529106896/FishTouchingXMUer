#include <iostream>
using namespace std;


class myException : public exception
{
public:
    const char* what() const throw()
    {
        return "除数为零！";
    }
};

double division(double a, double b)
{
    if (b == 0)
    {
        //throw就是抛出异常
        //throw 语句的操作数可以是任意的表达式，表达式的结果的类型决定了抛出的异常的类型
        throw "Division by zero condition!";
    }
    if (a < 0)
        throw - 1;
    if (a == 0)
    {
        exception e1;
        throw e1;
    }
    return (a / b);
}

int main()
{
    double x = 0;
    double y = 0;
    double z = 0;

    try 
    {
        cin >> x >> y;
        z = division(x, y);
        cout << z << endl;
    }
    //catch语句根据throw抛出的异常类型来捕获，根据上面的函数，如果被除数为0，由第一个catch来捕获
    //如果除数小于0，由第二个catch来捕获
    //在捕获异常的同时，还可以获取异常类型的值
    catch (const char* msg) 
    {
        cerr << msg << endl;
    }
    catch (int i)
    {
        cout << i << endl;
    }
    //从这里可以看到，catch除了一般的基本数据类型，还支持直接捕获异常类
    catch (exception)
    {
        cerr << "just test" << endl;
    }

    int a = 1, b = 0;
    try
    {
        if (b == 0)
            throw myException();
        int c = a / b;
    }
    //还可以抛出自定义类型（个人觉得c++的异常处理没有java的好用，java的这里不需要自定义一个异常类，甚至不需要写throw）
    catch (myException e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}