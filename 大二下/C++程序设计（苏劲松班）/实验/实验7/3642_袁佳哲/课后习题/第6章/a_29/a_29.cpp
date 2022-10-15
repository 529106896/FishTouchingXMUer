#include <iostream>
#include <string>

using namespace std;

const int NUM = 2;

class A
{
private:
	static A* p_free;
	A* next;
	static char* p_block;

public:
	static void* operator new(size_t size);
	static void operator delete(void* p);
	static void free_blocks();
};

A* A::p_free = NULL;
char* A::p_block = NULL;
void* A::operator new(size_t size)
{
	A* p;
	if (p_free == NULL)
	{
		char* q = new char[sizeof(char*) + size * NUM];
		*(char**)q = p_block;
		p_block = q;

		p_free = (A*)(q + sizeof(char*));
		for (p = p_free; p != p_free + NUM - 1; p++)
		{
			p->next = p + 1;
		}
		p->next = NULL;
	}
	p = p_free;
	p_free = p_free->next;
	memset(p, 0, size);
	return p;
}

void A::operator delete(void* p)
{
	((A*)p)->next = p_free;
	p_free = (A*)p;
}

void A::free_blocks()
{
	while (p_block != NULL)
	{
		char* p = p_block;
		p_block = *(char**)p_block;
		delete[]p;
	}
}