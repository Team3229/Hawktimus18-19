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

	cout << "Now enter the requested operation for the 2 numbers (+, -, *, /, %)" << endl;
	cin >> choice;

	if (choice == '+')
		answer = num1 + num2;
	else if (choice == '-')
		answer = num1 - num2;
	else if (choice == '*')
		answer = num1 * num2;
	else if (choice == '/')
		answer = num1 / num2;
	else if (choice == '%') //% dividing only works with integers, so we need to convert
		answer = int(num1) % int(num2); //The int() function converts the data type to integer
	else
		choice = 'i';

	if (choice == 'i')
		cout << "Invalid operation, restart the program." << endl;
	else
		cout << num1 << choice << num2 << "=" << answer << endl;

	system("pause");
	return 0;
}