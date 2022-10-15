#include <iostream>

using namespace std;

class myString
{
private:
    string* str;
public:
    myString()
    {
        //如果用这种的，可以用自带的异常类去捕获
        str = new string[100000000000];

        //如果用这种的分配咨询，可以用自定义的抛出异常去捕获
        //str = new(std::nothrow) string[100000000000];
        if (!str)
            throw 'T';
    }
};

int main()
{
    try
    {
        myString test;
    }
    //用异常处理机制去捕获异常
    catch (const bad_alloc& e)
    {
        cout << "第一种异常处理方式" << endl;
    }
    catch (char errorCode)
    {
        printf("内存分配失败！错误代码%c\n", errorCode);
    }

    //另外一种处理方式
    //不推荐，无法快速捕获异常
    int* p = new int[100];
    if (p == NULL)
    {
        cout << "p内存分配失败！" << endl;
        exit(-1);

    }

    return 0;
}