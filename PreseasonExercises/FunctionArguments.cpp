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
	cout << "Enter a strings, then press ENTER: ";
	getline(cin, user1); 
	// getline is similar to cin, except it allows the user to put spaces
	// as the name suggests, it grabs what's in the entire line
	cout << "Enter another string: ";
	getline(cin, user2);
	
	// the function puts the 2 together, so just print the result of the function
	cout << "Resulting string = " << putTogether(user1, user2);

	return 0;
}