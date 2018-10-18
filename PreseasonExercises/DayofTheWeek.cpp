#include <iostream>
using namespace std;

int main()
{
	int num1;

	cout << "Enter a number between 1 and 7 (this includes 1 and 7): " << endl;
	cin >> num1;

	switch (num1) //Tests the different values of num1
	{
	case 1: //if num1 is equal to 1 then:
		cout << "The first day of the week is Sunday." << endl;
		break; //Ends the commands following that the condition is met

	case 2:
		cout << "The second day of the week is Monday." << endl;
		break;

	case 3:
		cout << "The third day of the week is Tuesday." << endl;
		break;

	case 4:
		cout << "The fourth day of the week is Wednesday." << endl;
		break;

	case 5:
		cout << "The fifth day of the week is Thursday." << endl;
		break;

	case 6:
		cout << "The sixth day of the week is Friday." << endl;
		break;

	case 7:
		cout << "The seventh day of the week is Saturday." << endl;
		break;

	default:
		cout << "That does not correspond to a day of the week, restart." << endl;
		break;
	}

	system("pause");
	return 0;
}