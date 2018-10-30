#include <iostream>
using namespace std;

class Rectangle
{
private:
	double length, width; //2 doubles, only visible to members of the class

public:
	void setValues(double l, double w); //Function to set the length and width values
	double getArea() { return length * width; } //Returns the product of the 2

};

void Rectangle::setValues(double l, double w)
{
	length = l; //Sets the private class variable of length to the user input
	width = w; //Sets width equal to the users input
}

int main()
{
    double num1, num2; // makes 2 variables for user input    
	Rectangle rect1; //Creates an object of class Rectangle

    cout << "Enter two numbers, seperated by enter: ";
    cin >> num1;
    cin >> num2;

	rect1.setValues(num1, num2); //Passes in values for length and width

	cout << "Area of rectangle: " << rect1.getArea() << endl;

	system("pause");
	return 0;
}