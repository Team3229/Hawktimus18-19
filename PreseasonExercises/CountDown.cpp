#include <iostream>
using namespace std;

int main()
{
	int userNum, increment;

	cout << "Enter any number:" << endl;
	cin >> userNum;

	cout << "Now enter the increment to count down to 0 by:" << endl;
	cin >> increment;

	cout << "Counting down from " << userNum << " by " << increment << endl;
	for (int i = userNum; i >= 0; i = i - increment)
	{
		cout << i << endl;
	}
	cout << "Finished!" << endl;

	system("pause");
	return 0;
}