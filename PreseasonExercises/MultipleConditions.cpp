#include <iostream>
using namespace std;

int main()
{
	bool isEven;
	int num1, num2;

	cout << "Enter an integer: ";
	cin >> num1;
	cout << "Now enter another integer: ";
	cin >> num2;

	// the modulo dividing lets us check if the number is even or odd
	if (num1 % 2 == 0) 
		isEven = true;
	else
		isEven = false;

	// the && acts as the word 'and'
	// this means both conditions must be true to get the result
	if (isEven == true && num1 > num2)
		cout << num1 << " is even and bigger than " << num2 << endl;
	else
		cout << "The 2 conditions weren't met." << endl;

	system("pause");
	return 0;
}