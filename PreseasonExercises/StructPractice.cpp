#include <iostream>
#include <string>
using namespace std;

struct Person
{
	// all of the variables can be accessed through an object of Person
	int age;
	string name;
	char gender;
};

int main()
{
	Person p1; // creates our object of struct Person, named p1

	// filling the variables
	cout << "Enter this person's name: ";
	getline(cin, p1.name);
	cout << "Enter this person's age: ";
	cin >> p1.age;
	cout << "Enter this person's gender [M or F]: ";
	cin >> p1.gender;

	// displaying the results
	cout << "\nDisplaying Information" << endl;
	cout << "Name: " << p1.name << endl;
	cout << "Age: " << p1.age << endl;
	cout << "Gender: " << p1.gender << endl;

	return 0;
}