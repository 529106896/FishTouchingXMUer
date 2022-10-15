#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class IntSet
{
private:
	vector<int> v;

public:
	IntSet(){}
	IntSet(const IntSet& s)
	{
		this->v = s.v;
	}
	~IntSet()
	{
		v.clear();
	}
	bool is_empty() const
	{
		return v.empty();
	}
	int size() const
	{
		return (int)v.size();
	}
	bool insert(int e)
	{
		v.push_back(e);
		if (find(v.begin(), v.end(), e) != v.end())
			return true;
		else
			return false;
	}
	bool is_element(int e) const
	{
		if (find(v.begin(), v.end(), e) != v.end())
			return true;
		else
			return false;
	}
	void display()
	{
		if (v.size() == 0)
			return;
		vector<int>::iterator it;
		for (it = v.begin(); it != v.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	bool is_subset(const IntSet& s)
	{
		vector<int>v1 = v;
		vector<int>v2 = s.v;
		sort(v1.begin(), v1.end());
		sort(v2.begin(), v2.end());
		vector<int>::iterator it1;
		vector<int>::iterator it2;
		for (it1 = v1.begin(), it2 = v2.begin(); it1 != v1.end(); it1++, it2++)
		{
			if (*it1 == *it2)
				continue;
			else
				return false;
		}
		//cout << "第一个集合是第二个集合的子集" << endl;
		return true;
	}
	bool remove(int e)
	{
		if (find(v.begin(), v.end(), e) == v.end())
		{
			cout << "No such element! Delete Error!" << endl;
			return false;
		}
		else
		{
			vector<int>::iterator it = find(v.begin(), v.end(), e);
			v.erase(it);
			return true;
		}
	}
	IntSet union2(const IntSet& s) const
	{
		vector<int>v1 = v;
		vector<int>v2 = s.v;
		sort(v1.begin(), v1.end());
		sort(v2.begin(), v2.end());
		vector<int>result;
		set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
		IntSet resultSet;
		resultSet.v = result;
		return resultSet;
	}
	IntSet intersection2(const IntSet& s) const
	{
		vector<int>v1 = v;
		vector<int>v2 = s.v;
		sort(v1.begin(), v1.end());
		sort(v2.begin(), v2.end());
		vector<int>result;
		set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
		IntSet resultSet;
		resultSet.v = result;
		return resultSet;
	}
	IntSet difference2(const IntSet& s) const
	{
		vector<int>v1 = v;
		vector<int>v2 = s.v;
		vector<int>result;
		vector<int>::iterator it1 = v1.begin();
		for (; it1 != v1.end(); it1++)
		{
			if (find(v2.begin(), v2.end(), *it1) == v2.end())
			{
				result.push_back(*it1);
			}
		}
		IntSet resultSet;
		resultSet.v = result;
		return resultSet;
	}
};

int main()
{
	IntSet s1;
	IntSet s2;
	s1.insert(1);
	s1.insert(2);
	s1.insert(3);
	s1.display();
	s2.insert(2);
	s2.insert(4);
	s2.insert(9);
	s2.insert(1);
	s2.insert(5);
	s2.display();
	//if (s1.is_subset(s2))
	//{
	//	cout << "s1是s2的子集" << endl;
	//}
	//else
	//	cout << "s1不是s2的子集" << endl;
	//s2.display();
	//s2.remove(5);
	//s2.display();
	s1.union2(s2).display();
	s1.intersection2(s2).display();
	s1.difference2(s2).display();
	return 0;
}