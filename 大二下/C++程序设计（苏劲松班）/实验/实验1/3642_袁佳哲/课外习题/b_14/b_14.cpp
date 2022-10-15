#include <iostream>

using namespace std;

#define NULL 0

struct stud
{
    long  num;
    char name[10];
    float score;
    struct stud *next;
};
     
int n;

struct stud *create()                   
{
    struct stud *head,*p1,*p2;
    n = 0;
    p1 = p2 = new(struct stud);

    cin >> p1->num >> p1->name >> p1->score;

    head = NULL; 

    while(cin)
    {
        n = n + 1;
        if(n == 1) 
            head = p1;
        else 
        {
            p2->next = p1;
            p2 = p2->next;
        }
        p1 = new(struct stud);

        cin >> p1->num >> p1->name >> p1->score;
    }

    p2->next=NULL;
    return(head);
}

void outlink(struct stud* head)
{
    struct stud* p = head;
    while(p)
    {
        cout << p->num << " " << p->name << " " << p->score << endl;
        p = p->next;
    };
    cout << endl;
}

int main()
{
    cout << "按\"序号 姓名 分数\"的格式输入，按ctrl+z结束输入：" << endl;
    struct stud * head;
    head = create();
    outlink(head);
    system("pause");
    return 0;
}
