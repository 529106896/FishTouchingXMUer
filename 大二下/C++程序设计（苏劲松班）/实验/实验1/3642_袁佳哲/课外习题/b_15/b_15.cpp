#include <iostream>

using namespace std;

struct n
{
    long num;
    struct n *next;
};

int main()
{  
    int n, i; 
    cin >> n;
    struct n *head , *p1, *p2, *p;
    p1 = p2 = new(struct n);

    for(i = 0; i<n; i++)
    {  
        cin >> p1->num;
        if(i == 0)  
            head = p1;
        else 
        {
            p2->next = p1;
            p2 = p2->next;
        }  
        p1 = new(struct n);
    }

    p2->next = NULL;
    p = head;

    while(p != NULL)
    {
        cout << p->num << " " << endl;
        p = p->next;
    }
    cout << endl;
    system("pause");
    return 0;
}
