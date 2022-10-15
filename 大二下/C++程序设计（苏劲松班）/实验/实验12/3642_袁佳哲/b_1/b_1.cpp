#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>

using namespace std;

class finder
{
public:
	finder(const std::string& string) :cmp_string(string) {}
	bool  operator ()(const std::map< int, std::string>::value_type& pair)
	{
		return pair.second == cmp_string;
	}
private:
	const std::string& cmp_string;
};

int main()
{
	map<int, string> my_map;
	my_map.insert(make_pair(10, "china"));
	my_map.insert(make_pair(20, "usa"));
	my_map.insert(make_pair(30, "english"));
	my_map.insert(make_pair(40, "hongkong"));
	map<int, string>::iterator it = find_if(my_map.begin(), my_map.end(), finder("english"));
	if (it == my_map.end())
		cout << "Not Found!" << endl;
	else
		cout << it->first << " " << it->second << endl;
	return 0;
}
