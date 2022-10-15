#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class student
{
private:
	string sNo;
	string sName;
	double sGrades[8];

public:
	student()
	{
		sNo = "";
		sName = "";
		memset(sGrades, 0, sizeof(8 * sizeof(double)));
	}

	void setNo(string number)
	{
		sNo = number;
	}

	void setName(string name)
	{
		sName = name;
	}

	void setGrades(double grades[])
	{
		for (int i = 0; i < 8; i++)
		{
			sGrades[i] = grades[i];
		}
	}

	string getNo()
	{
		return sNo;
	}

	string getName()
	{
		return sName;
	}

	double getAverageGrade()
	{
		double sum = 0;
		for (int i = 0; i < 8; i++)
		{
			sum += sGrades[i];
		}
		return sum / 8;
	}
};

bool bigToSmall(student& s1, student& s2)
{
	return s1.getAverageGrade() > s2.getAverageGrade();
}

int main()
{
	ifstream in;
	ofstream out;
	in.open("demo.txt", ios::in);
	out.open("students.txt", ios::out);
	if (!in)
	{
		cerr << "input file not open!" << endl;
		exit(-1);
	}
	if (!out)
	{
		cerr << "output file not open!" << endl;
		exit(-1);
	}

	string line;
	string temp;
	vector<student> students;

	cout << "学生的信息为：" << endl;
	while (getline(in, line))
	{
		cout << line << endl;
		stringstream input(line);
		vector<string> information;
		while (input >> temp)
			information.push_back(temp);

		student s;
		s.setNo(information[0]);
		s.setName(information[1]);
		
		int i = 0;
		double grades[8];
		for (vector<string>::iterator it = information.begin() + 2; it != information.end(); it++)
		{
			grades[i++] = atof((*it).c_str());
		}
		s.setGrades(grades);

		students.push_back(s);
	}

	sort(students.begin(), students.end(), bigToSmall);

	cout << endl;
	cout << "按平均成绩排名如下：" << endl;
	for (vector<student>::iterator it = students.begin(); it != students.end(); it++)
	{
		cout << (*it).getNo() << " " << (*it).getName() << " " << (*it).getAverageGrade() << endl;
		out << (*it).getNo() << " " << (*it).getName() << " " << (*it).getAverageGrade() << endl;
	}

	cout << endl;
	cout << "已将结果输出到\"students.txt\"" << endl;

	in.close();
	out.close();

	return 0;
}