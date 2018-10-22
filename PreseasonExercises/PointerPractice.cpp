#include <iostream>
using namespace std;

int main()
{
	int myVar = 20; 
	int *myPointer; // the * lets C++ know that we're declaring a pointer

	myPointer = &myVar; // & symbol gets a variables location in memory

	cout << "Value of myVar variable: ";
    cout << myVar << endl;

    // print the address stored in myPointer variable
    cout << "Address stored in myPointer variable: ";
    cout << myPointer << endl;

    // access the value at the address available in pointer
    cout << "Value of *myPointer variable: ";
    cout << *myPointer << endl;

    system("pause");
	return 0;
}