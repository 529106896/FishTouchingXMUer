#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct student
{
	string sno;
	string name;
	double score1, score2, score3, score4, score5, score6, score7, score8;
	double avg;
};

bool greaterSort(student st1, student st2)
{
	return (st1.avg > st2.avg);
}

int main()
{
	vector<student> students;
	for (int i = 0; i < 4; i++)
	{
		student st;
		cin >> st.sno >> st.name >> st.score1 >> st.score2 >> st.score3 >> st.score4 >> st.score5 >> st.score6 >> st.score7 >> st.score8;
		st.avg = (st.score1 + st.score2 + st.score3 + st.score4 + st.score5 + st.score6 + st.score7 + st.score8) / 8.0;
		students.push_back(st);
	}
	sort(students.begin(), students.end(), greaterSort);
	for (int i = 0; i < students.size(); i++)
	{
		cout << students.at(i).sno << " " << students.at(i).name << " " << students.at(i).avg << endl;
	}
	return 0;
}