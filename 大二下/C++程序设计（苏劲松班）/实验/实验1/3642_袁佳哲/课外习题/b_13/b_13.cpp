#include <iostream>

using namespace std;

typedef struct aa
{
    int data;
    struct aa *next;
}NODE;

NODE *Createlink(int n, int m)
{
    NODE *h = NULL, *p, *s;
    int i;
    p = new(NODE);
    h = p;
    p->next = NULL;
    for(i = 1; i<=n; i++)
    {
        s = new(NODE);
        s->data = rand() % m;
        s->next = p->next;
        p->next = s;
        p = p->next;
    }
    return h;
}

void outlink(NODE *h)
{
    NODE *p = h->next;
    cout << "The list: head";
    while(p)
    {
        cout << "->" << p->data;
        p = p->next;
    }
    cout << endl;
}

int main()
{
    NODE *head;
    head = Createlink(8, 22);
    outlink(head);
    system("pause");
    return 0;
}