#include <iostream>
using namespace std;

int main() 
{

	int a, b;
	cout << "Enter the value of A: ";
	cin >> a;
	cout << "Enter the value of B: ";
	cin >> b;

	// creates our two pointers
	int *ptrA = &a; // assigned address of a
	int *ptrB = &b;

	cout << "Value of ptrA is " << *ptrA << " sored in address " << ptrA << "\n";
	cout << "Value of ptrB is " << *ptrB << " sored in address " << ptrB << "\n";

	return 0;
}