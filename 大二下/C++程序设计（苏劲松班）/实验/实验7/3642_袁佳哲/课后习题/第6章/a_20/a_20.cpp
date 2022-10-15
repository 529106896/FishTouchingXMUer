#include <stdio.h>
#include <malloc.h>

struct A 
{
	int x = 0;
	int y = 0;
	//void (*constructorWithoutParameter)(struct A* ptr);
	void (*A)(struct A * ptr, int i, int j);
	void (*f)(struct A* ptr, void h());
	void (*g)(struct A* ptr, int i);
	void (*h)();
}; 

//无参构造函数不需要手动调用，所以注释掉，直接把x，y的默认值设置为0
//void nonParameterConstructor(struct A* ptr)
//{
//	ptr->x = 0;
//	ptr->y = 0;
//};

//实现A(int i, int j) { x = i; y = j; }
void parameterConstructor(struct A* ptr, int i, int j)
{
	ptr->x = i;
	ptr->y = j;
}

//实现void f(){h(); .........}
void public_function_f(struct A* ptr, void h())
{
	h = ptr->h;
}

//实习void g(int i) { x = i; ...... }
void public_function_g(struct A* ptr, int i)
{
	ptr->x = i;
}

//实现void h()
void private_function_h()
{

};

void constructor(struct A* ptr)
{
	//ptr->constructorWithoutParameter = nonParameterConstructor;
	ptr->A = parameterConstructor;
	ptr->f = public_function_f;
	ptr->g = public_function_g;
	ptr->h = private_function_h;
}

int main()
{
	struct A class_A;
	constructor(&class_A);
	//class_A.constructorWithoutParameter(&class_A);
	printf("%d %d\n", class_A.x, class_A.y);
	class_A.A(&class_A, 5, 6);
	printf("%d %d\n", class_A.x, class_A.y);
	class_A.g(&class_A, 10);
	printf("%d\n", class_A.x);
	return 0;
}