#include <iostream>

using namespace std;

struct Node
{
	int value;
	Node* next;
};

class IntSet
{
private:
	int count;
	Node* head;

public:
	IntSet();	//构造函数
	IntSet(const IntSet& s);
	~IntSet();
	bool is_empty() const;	//判断是否为空集
	int size() const;	//获取元素个数
	bool is_element(int e) const;	//判断e是否属于集合
	bool is_subset(const IntSet& s) const;	//判断集合是否属于s
	bool is_equal(const IntSet& s) const;	//判断集合是否相等
	bool insert(int e);	//将e加入到集合中，成功返回true，失败返回false
	bool remove(int e);	//把e从集合中删除，成功返回true，失败返回false
	void display() const;	//显示集合中的所有元素
	IntSet union2(const IntSet& s) const;	//计算集合的并集
	IntSet intersection2(const IntSet& s) const;	//计算集合的交集
	IntSet difference2(const IntSet& s) const;	//计算集合的差集
};

IntSet::IntSet()
{
	count = 0;
	head = NULL;
}

IntSet::IntSet(const IntSet& s)
{
	head = NULL;
	count = 0;
	Node* p = s.head;
	while (p != NULL)
	{
		insert(p->value);
		p = p->next;
	}
}

IntSet::~IntSet()
{
	Node* temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
	count = 0;
}

bool IntSet::is_empty() const
{
	if (count == 0)
		return true;
	else
		return false;
}

int IntSet::size() const
{
	return count;
}

bool IntSet::is_element(int e) const
{
	Node* p = head;
	while (p != NULL)
	{
		if (p->value == e)
			return true;
		p = p->next;
	}
	return false;
}

bool IntSet::is_subset(const IntSet& s) const
{
	Node* p = s.head;
	while (p != NULL)
	{
		if (!is_element(p->value))
			return false;
		p = p->next;
	}
	return true;
}

bool IntSet::is_equal(const IntSet& s) const
{
	if (s.count == count && is_subset(s))
		return true;
	else
		return false;
}

bool IntSet::insert(int e)
{
	if (!is_element(e))
	{
		Node* p = new Node;
		p->value = e;
		p->next = head;
		head = p;
		count++;
		return true;
	}
	else
		return false;
}

bool IntSet::remove(int e)
{
	if (is_element(e))
	{
		if (head->value == e)
		{
			Node* p = head;
			head = head->next;
			delete p;
		}
		else
		{
			Node* p = head;
			while (p->next != NULL)
			{
				if (p->next->value == e)
				{
					Node* temp = p->next;
					p->next = temp->next;
					delete temp;
					break;
				}
				p = p->next;
			}
		}
		count--;
		return true;
	}
	else
		return false;
}

void IntSet::display() const
{
	Node* p = head;
	while (p != NULL)
	{
		cout << p->value << " ";
		p = p->next;
	}
	cout << endl;
}

IntSet IntSet::union2(const IntSet& s) const
{
	IntSet temp_set(s);
	Node* p = head;
	while (p != NULL)
	{
		if (!temp_set.is_element(p->value))
			temp_set.insert(p->value);
		p = p->next;
	}
	return temp_set;
}

IntSet IntSet::intersection2(const IntSet& s) const
{
	IntSet temp_set;
	Node* p = head;
	while (p != NULL)
	{
		if (s.is_element(p->value))
			temp_set.insert(p->value);
		p = p->next;
	}
	return temp_set;
}

IntSet IntSet::difference2(const IntSet& s) const
{
	IntSet temp_set;
	Node* p = head;
	while (p != NULL)
	{
		if (!s.is_element(p->value))
			temp_set.insert(p->value);
		p = p->next;
	}
	return temp_set;
}

int main()
{
	IntSet set1;
	set1.insert(1);
	set1.insert(2);
	set1.insert(3);
	set1.insert(4);
	cout << "set1展示：";
	set1.display();
	cout << "set1 Length is " << set1.size() << endl;
	set1.remove(1);
	cout << "set1展示：";
	set1.display();
	cout << "set1 Length is " << set1.size() << endl;
	if (set1.is_element(2))
		cout << "1是set1的元素" << endl;
	IntSet set2;
	set2.insert(3);
	set2.insert(2);
	cout << "set2展示：";
	set2.display();
	if (set1.is_subset(set2))
		cout << "set2是set1的子集" << endl;
	set2.insert(4);
	cout << "set2展示：";
	set2.display();
	if (set1.is_equal(set2))
		cout << "set2和set1相等" << endl;
	set2.insert(5);
	set2.insert(6);
	set1.insert(1);
	cout << "set2展示：";
	set2.display();
	cout << "set1展示：";
	set1.display();
	cout << "set1和set2的并集：";
	set1.union2(set2).display();
	cout << "set1和set2的交集：";
	set1.intersection2(set2).display();
	cout << "set1对set2的差集：";
	set1.difference2(set2).display();
	cout << "set2对set1的差集：";
	set2.difference2(set1).display();
	return 0;
}