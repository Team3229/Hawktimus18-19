#include <iostream>
#include <string>
using namespace std;

int main()
{
	double num1, num2, answer;
	char choice;

	cout << "Enter 2 numbers, press enter in-between the first and second." << endl;
	cin >> num1;
	cin >> num2;

	cout << "Now enter the requested operation for the 2 numbers (+, -, *, /)" << endl;
	cin >> choice;

	if (choice == '+')
		answer = num1 + num2;
	else if (choice == '-')
		answer = num1 - num2;
	else if (choice == '*')
		answer = num1 * num2;
	else if (choice == '/')
		answer = num1 / num2;
	else
		choice = 'i';

	if (choice == 'i')
		cout << "Invalid operation, restart the program." << endl;
	else
		cout << num1 << choice << num2 << "=" << answer << endl;

	system("pause");
	return 0;
}