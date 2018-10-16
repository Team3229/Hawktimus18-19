#include <iostream>
using namespace std;

int main()
{
	int num1, num2, num3, biggest;

	cout << "Enter 3 integers, pressing enter in-between:" << endl;
	cin >> num1;
	cin >> num2;
	cin >> num3;

	if (num1 > num2 && num1 > num3)
		biggest = num1;
	else if (num2 > num1 && num2 > num3)
		biggest = num2;
	else
		biggest = num3;

	cout << "The biggest is " << biggest << endl;

	system("pause");
	return 0;
}