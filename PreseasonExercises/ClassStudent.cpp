#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
	// our object s1 is not able to access these because they are private
	// they can however be accessed by our functions which are also part of the class
	string name;
	int grade;
	double sum = 0.0;
	double testScores[5];

public:
	// these functions are visible to our objects of Student
	void getName()
	{
		cout << "Enter this student's name: ";
		getline(cin, name);
	}
	void getGradeLevel()
	{
		cout << "Enter the student's grade level: ";
		cin >> grade;
	}
	void getTestScores()
	{
		for (int i = 0; i < 5; i++)
		{
			cout << "Enter the score for test " << i + 1 << ": ";
			cin >> testScores[i];
			sum = sum + testScores[i];
		}
	}
	double getAverage()
	{
		return sum / 5;
	}
};

int main()
{
	Student s1; // creates object of class Student

	// s1 is able to use these functions because they're public within Student
	s1.getName();
	s1.getGradeLevel();
	s1.getTestScores();
	
	cout << "Average of scores: " << s1.getAverage();

	return 0;
}