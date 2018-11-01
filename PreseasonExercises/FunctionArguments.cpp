#include <iostream>
#include <string>
using namespace std;

string putTogether(string a, string b)
{
	return a + b;
}

int main()
{
	string user1, user2;
	cout << "Enter 2 strings, seperated by the ENTER key: ";
	cin >> user1;
	cin >> user2;
	
	// the function puts the 2 together, so just print the result of the function
	cout << putTogether(user1, user2);

	return 0;
}