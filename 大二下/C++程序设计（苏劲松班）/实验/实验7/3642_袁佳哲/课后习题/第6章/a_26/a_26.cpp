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

	bool operator+=(int e)
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

	bool operator-=(int e)
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

	bool operator<=(IntSet& e)
	{
		Node* p = e.head;
		while (p != NULL)
		{
			if (!is_element(p->value))
				return false;
			p = p->next;
		}
		return true;
	}

	bool operator==(IntSet& e)
	{
		if (e.count == count && is_subset(e))
			return true;
		else
			return false;
	}

	bool operator!=(IntSet& e)
	{
		if (e.count != count || is_subset(e))
			return true;
		else
			return false;
	}

	IntSet operator|(const IntSet& s)
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

	IntSet operator&(const IntSet& s)
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

	IntSet operator-(const IntSet& s)
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

	IntSet set2;
	set2.insert(3);
	set2.insert(2);
	cout << "set2展示：";
	set2.display();

	//这里解释一下为什么set1<=set2会出现set2是set1的子集
	//首先<=是借助之前的is_sub实现的
	//set1.is_sub(set2)，从set2中挨个取出元素判断此元素是否属于set1
	//因此这里应该是set1 <= set2
	if (set1 <= set2)
	{
		cout << "set2是set1的子集" << endl;
	}

	cout << "向set2中插入1 4" << endl;
	set2.insert(1);
	set2.insert(4);
	cout << "set2展示：";
	set2.display();

	if (set1 == set2)
	{
		cout << "set1和set2相等" << endl;
	}

	cout << "从set2中去掉3" << endl;
	set2.remove(3);
	cout << "set2展示：";
	set2.display();

	if (set1 != set2)
	{
		cout << "set1和set2不相等" << endl;
	}

	cout << "向set2中插入5" << endl;
	set2.insert(5);
	cout << "set2展示：";
	set2.display();
	IntSet set3 = set1 | set2;
	cout << "计算set1和set2的并集set3" << endl;
	cout << "set3展示：";
	set3.display();

	cout << "从set2中去掉3" << endl;
	set2.remove(3);
	cout << "set2展示：";
	set2.display();
	IntSet set4 = set1 & set2;
	cout << "计算set1和set2的交集set4" << endl;
	cout << "set4展示：";
	set4.display();

	cout << "计算set1对set2的差集set5" << endl;
	IntSet set5 = set1 - set2;
	cout << "set5展示：";
	set5.display();

	cout << "向set1中加入10" << endl;
	set1 += 10;
	cout << "set1展示：";
	set1.display();

	cout << "从set1中删去10" << endl;
	set1 -= 10;
	cout << "set1展示：";
	set1.display();
	return 0;
}